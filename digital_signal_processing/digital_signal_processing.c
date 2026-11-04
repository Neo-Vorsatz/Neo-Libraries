/*
    Digital Signal Processing Library, for processing signals
    Implementation file
    Author: Neo Vorsatz
    Last updated: 4 November 2026
*/

// IMPORTS ================================

// External
#include <math.h>

// Internal
#include "digital_signal_processing.h"
#include "complex_numbers.h"
#include "data_handling.h"

// EDITABLE MACROS ================================

#ifndef PI
    #define PI 3.14159265358979323846 // same value in math.h, but defined locally
    #define __PI_WAS_UNDEFINED_BY_USER // note that PI was not defined by the user
#endif

// SIGNALS ================================

void dsNewSignal(dsSignal_t *write, const double *samples, unsigned int used_len, unsigned int max_len) {
    write->samples = samples;
    write->used_len = used_len;
    write->max_len = max_len;
}

bool dsSigPulse(dsSignal_t *write, double height, unsigned int width, unsigned int delay) {
    // For each sample before the pulse
    for (unsigned int i=0; i<delay; i++) {
        // Set sample to 0
        write->samples[i] = 0.0;
    }
    // Assume nothing goes wrong
    bool success = true;
    // Determine length
    if (delay + width > write->max_len) {
        success = false;
        write->used_len = write->max_len;
    } else {
        write->used_len = delay + width;
    }
    // For each sample in the pulse
    for (unsigned int i=delay; i<write->used_len; i++) {
        // Set sample to height
        write->samples[i] = height;
    }
    // Return
    return success;
}

bool dsSigImpulse(dsSignal_t *write, double size, unsigned int delay) {
    return dsSigPulse(write, size, 1, delay);
}

bool dsSigStep(dsSignal_t *write, double height, unsigned int delay) {
    // Set new length
    write->used_len = write->max_len;
    // Assume nothing goes wrong
    bool success = true;
    // If the step starts too late
    if (delay >= write->max_len) {
        success = false;
        delay = write->max_len;
    }
    // For each sample before the step
    for (unsigned int i=0; i<delay; i++) {
        // Set sample to 0
        write->samples[i] = 0.0;
    }
    // For each sample in the step
    for (unsigned int i=delay; i<write->max_len; i++) {
        // Set sample to height
        write->samples[i] = height;
    }
    // Return
    return success;
}

bool dsSigRamp(dsSignal_t *write, double slope, unsigned int delay) {
    // Set new length
    write->used_len = write->max_len;
    // Assume nothing goes wrong
    bool success = true;
    // If the step starts too late
    if (delay >= write->max_len) {
        success = false;
        delay = write->max_len;
    }
    // For each sample before the ramp
    for (unsigned int i=0; i<delay; i++) {
        // Set sample to 0
        write->samples[i] = 0.0;
    }
    // For each sample in the ramp
    double height = 0.0;
    for (unsigned int i=delay; i<write->max_len; i++) {
        // Increase height by slope
        height += slope;
        // Set sample to the increased height
        write->samples[i] = height;
    }
    // Return
    return success;
}

bool dsAddSignals(dsSignal_t *write, const dsSignal_t *read1, const dsSignal_t *read2) {
    // Assume nothing goes wrong
    bool success = true;
    // Get the length of the longer signal
    unsigned int len;
    if (read1->used_len > read2->used_len) {
        len = read1->used_len;
    } else {
        len = read2->used_len;
    }
    // Limit the length
    if (len > write->max_len) {
        len = write->max_len;
        success = false;
    }
    // Update used length
    write->used_len = len;
    // For each sample
    for (unsigned int i=0; i<len; i++) {
        // Set the sample to 0
        write->samples[i] = 0.0;
        // Add the first signal
        if (i < read1->used_len) {
            write->samples[i] += read1->samples[i];
        }
        // Add the second signal
        if (i < read2->used_len) {
            write->samples[i] += read2->samples[i];
        }
    }
    // Return
    return success;
}

bool dsTimeShift(dsSignal_t *write, const dsSignal_t *read, int shift) {
    // Assume nothing goes wrong
    bool success = true;
    // Copy samples
    double copy[read->used_len];
    for (unsigned int i=0; i<read->used_len; i++) {
        copy[i] = read->samples[i];
    }
    // Transfer each sample
    for (unsigned int i=0; i<read->used_len; i++) {
        // Check if sample is shifted too forward
        if (i + shift < 0) {
            continue;
        }
        // Check if sample is shifted too backward
        if (i + shift >= write->max_len) {
            success = false;
            break;
        }
        // Transfer sample
        write->samples[i + shift] = copy[i];
    }
    // Clear new empty samples
    for (unsigned int i=0; i<shift; i++) {
        write->samples[i] = 0.0;
    }
    // Calculate used length
    if (read->used_len + shift < 0) {
        write->used_len = 0;
    } else if (success) {
        write->used_len = read->used_len + shift;
    } else {
        write->used_len = write->max_len;
    }
    // Return
    return success;
}

bool dsConvolve(dsSignal_t *write, const dsSignal_t *read1, const dsSignal_t *read2) {
    // Assume nothing goes wrong
    bool success = true;
    // Copy first signal
    double copy1[read1->used_len];
    for (unsigned int i=0; i<read1->used_len; i++) {
        copy1[i] = read1->samples[i];
    }
    // Copy second signal
    double copy2[read2->used_len];
    for (unsigned int i=0; i<read2->used_len; i++) {
        copy2[i] = read2->samples[i];
    }
    // Calculate length
    unsigned int len = read1->used_len + read2->used_len - 1;
    if (len > write->max_len) {
        success = false;
        len = write->max_len;
    }
    // Initialise values
    for (unsigned int i=0; i<len; i++) {
        write->samples[i] = 0.0;
    }
    // Convolve
    for (unsigned int i=0; i<read1->used_len; i++) {
        for (unsigned int j=0; j<read2->used_len; j++) {
            if (i + j >= len) {
                continue;
            }
            write->samples[i + j] += copy1[i] * copy2[j];
        }
    }
    // Write used length
    write->used_len = len;
    // Return
    return success;
}

// SYSTEMS ================================

void dsNewSystem(dsSystem_t *write, const dsSignal_t *impulse_response, const dsSignal_t *history) {
    write->imp_resp = *impulse_response;
    write->history = *history;
}

bool dsApplySystem(dsSignal_t *write, dsSystem_t *sys, const dsSignal_t *sig, bool remember) {
    // Extend the signal with the system's history
    unsigned int ext_len = sys->history.used_len + sig->used_len;
    double extended_samples[ext_len];
    for (unsigned int i=0; i<sys->history.used_len; i++) {
        extended_samples[i] = sys->history.samples[i];
    }
    for (unsigned int i=0; i<sig->used_len; i++) {
        extended_samples[sys->history.used_len+i] = sig->samples[i];
    }
    dsSignal_t ext_sig = {extended_samples, ext_len, ext_len};
    // Update the history of the system
    if (remember) {
        if (ext_len > sys->history.max_len) {
            dsTimeShift(&sys->history, &ext_sig, -ext_len + sys->history.max_len);
            sys->history.used_len = sys->history.max_len;
        } else {
            dsTimeShift(&sys->history, &ext_sig, 0); // copy
            sys->history.used_len = ext_len;
        } 
    }
    // Convolve the extended signal with the impulse response
    return dsConvolve(write, &ext_sig, &sys->imp_resp);
}

void dsResetSystem(dsSystem_t *sys) {
    sys->history.used_len = 0;
}

bool dsSysScaling(dsSystem_t *write, double scaling) {
    return dsSigPulse(&write->imp_resp, scaling, 1, 0);
}

bool dsSysDelay(dsSystem_t *write, unsigned int delay, double scaling) {
    return dsSigPulse(&write->imp_resp, scaling, 1, delay);
}

bool dsSysFiniteIntegrator(dsSystem_t *write, double scaling) {
    return dsSigStep(&write->imp_resp, scaling, 0);
}

bool dsSysDifferentiator(dsSystem_t *write, double scaling) {
    bool success = dsSigPulse(&write->imp_resp, -scaling, 1, 1);
    write->imp_resp.samples[0] = scaling;
    return success;
}

bool dsSysMovingAverage(dsSystem_t *write, unsigned int width) {
    return dsSigPulse(&write->imp_resp, 1.0 / width, width, 0);
}

bool dsSysLowpass(dsSystem_t *write, double gain, double cutoff, double sample_rate) {
    /*
        First-order lowpass filter has impulse response
        h(t) = K*w*e^(-w*t)
        where K is the gain, and w is the cutoff frequency.
        An increased sampling_rate decreases the effect of w,
        in the context of discrete-time.
    */
    if (write->imp_resp.max_len < 1) {
        return false;
    }
    // Calculate the discrete w
    double w = cutoff / sample_rate;
    // Calculate e raised to the power of -w
    double e2w = exp(-w);
    // Set the initial value at t=0
    write->imp_resp.samples[0] = gain*w;
    // Decay the rest of the impulse response
    for (unsigned int i=1; i<write->imp_resp.max_len; i++) {
        write->imp_resp.samples[i] = write->imp_resp.samples[i - 1] * e2w;
    }
    // Set the used length
    write->imp_resp.used_len = write->imp_resp.max_len;
    // Return
    return true;
}

bool dsSysHighpass(dsSystem_t *write, double gain, double cutoff, double sample_rate) {
    /*
        First-order highpass filter has impulse response
        h(t) = K*d(t)-K*w*e^(-w*t)
        where K is the gain, d(t) is the Dirac-delta, and w is the cutoff frequency.
        An increased sampling_rate decreases the effect of w,
        in the context of discrete-time.
    */
    if (write->imp_resp.max_len < 1) {
        return false;
    }
    // Create a negative lowpass filter
    dsSysLowpass(write, -gain, cutoff, sample_rate);
    // Add the Dirac-delta
    write->imp_resp.samples[0] += gain;
    // Return
    return true;
}

bool dsAddSystems(dsSystem_t *write, dsSystem_t *read1, dsSystem_t *read2) {
    // Assume nothing goes wrong
    bool success = true;
    // Add impulse responses
    if (!dsAddSignals(&write->imp_resp, &read1->imp_resp, &read2->imp_resp)) {
        success = false;
    }
    // Add history
    if (!dsAddSignals(&write->history, &read1->history, &read2->history)) {
        success = false;
    }
    // Return
    return success;
}

bool dsCascade(dsSystem_t *write, dsSystem_t *read1, dsSystem_t *read2) {
    // Clear the history
    write->history.used_len = 0;
    // Convolve the impulse responses
    return dsConvolve(&write->imp_resp, &read1->imp_resp, &read2->imp_resp);
}

// ELECTRICITY ================================

double dsDC(const dsSignal_t *read) {
    // Call the dhMean function
    return dhMean(read->samples, read->used_len);
}

bool dsAC(dsSignal_t *write, const dsSignal_t *read) {
    // Assume nothing goes wrong
    bool success = true;
    // Determine length
    if (read->used_len>write->max_len) {
        success = false;
        write->used_len = write->max_len;
    } else {
        write->used_len = read->used_len;
    }
    // Get the DC component
    double dc = dhMean(read->samples, read->used_len);
    // For each data point
    for (unsigned int i=0; i<write->used_len; i++) {
        //Subtract the DC offset
        write->samples[i] = read->samples[i] - dc;
    }
    // Return
    return success;
}

bool dsPower(dsSignal_t *write, const dsSignal_t *read) {
    // Assume nothing goes wrong
    bool success = true;
    // Determine length
    if (read->used_len>write->max_len) {
        success = false;
        write->used_len = write->max_len;
    } else {
        write->used_len = read->used_len;
    }
    // For each data point
    for (unsigned int i=0; i<write->used_len; i++) {
        // Calculate the power
        write->samples[i] = read->samples[i] * read->samples[i];
    }
    // Return
    return success;
}

double dsEnergy(const dsSignal_t *read) {
    // Create a signal for the power
    double samples[read->used_len];
    dsSignal_t power;
    dsNewSignal(&power, samples, 0, read->used_len);
    // Get the power of the signal
    dsPower(&power, read);
    // Return the sum of the power
    return dhSum(power.samples, power.used_len);
}

bool dsCumSumEnergy(dsSignal_t *write, dsSignal_t *read) {
    // Get the power of the signal
    bool success = dsPower(write, read);
    // Get the cumulative sum of the power
    dhCumSum(write->samples, write->samples, write->used_len);
    // Return
    return success;
}

double dsAvgPower(const dsSignal_t *read) {
    // Create a signal for the power
    double samples[read->used_len];
    dsSignal_t power;
    dsNewSignal(&power, samples, 0, read->used_len);
    // Get the power of the signal
    dsPower(&power, read);
    // Return the mean/average/expected value of the power
    return dhMean(power.samples, power.used_len);
}

double dsACRMS(const dsSignal_t *read) {
    // Call the dhStdDev function
    return dhStdDev(read->samples, read->used_len);
}

double dsRMS(const dsSignal_t *read) {
    // The RMS is the square-root of the average power
    return sqrt(dsAvgPower(read));
}

double dsDCPower(const dsSignal_t *read) {
    // Get the DC component
    double dc = dhMean(read->samples, read->used_len);
    // Return the power of the DC component
    return dc*dc;
}

double dsACPower(const dsSignal_t *read) {
    // Call the dhVar function
    return dhVar(read->samples, read->used_len);
}

// FOURIER ================================



// ================================

#ifdef __PI_WAS_UNDEFINED_BY_USER // if PI was not defined by the user
    #undef PI
    #undef __PI_WAS_UNDEFINED_BY_USER
#endif
