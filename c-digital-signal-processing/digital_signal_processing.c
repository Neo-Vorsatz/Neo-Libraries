// Digial Signal Processing Library, for processing signals
// Implementation file
// by Neo Vorsatz
// Last updated: 30 May 2026

#include <math.h>
#include "digital_signal_processing.h"

/* EDIT WITH MACROS ================================*/

#ifndef PI
  #define PI 3.14159265358979323846 //Same value in math.h, but defined locally
#endif

/*================================*/

#include "../c-data-handling/data_handling.h"
#include "../c-complex-numbers/complex_numbers.h"

/* SIGNALS ================================*/

//Sets the members of a signal struct
void dsNewSignal(signal *write, const double *samples, unsigned int used_len, unsigned int max_len) {
  write->samples = samples;
  write->used_len = used_len;
  write->max_len = max_len;
}

//Sets a signal to a pulse
bool dsSigPulse(signal *write, double height, unsigned int width, unsigned int delay) {
  //For each sample before the pulse
  for (unsigned int i=0; i<delay; i++) {
    //Set sample to 0
    write->samples[i] = 0.0;
  }
  //Assume nothing goes wrong
  bool success = true;
  //Detemine length
  if (delay+width>write->max_len) {
    success = false;
    write->used_len = write->max_len;
  } else {
    write->used_len = delay+width;
  }
  //For each sample in the pulse
  for (unsigned int i=delay; i<write->used_len; i++) {
    //Set sample to height
    write->samples[i] = height;
  }
  //Return
  return success;
}

//Sets a signal to an impulse
bool dsSigImpulse(signal *write, double size, unsigned int delay) {
  return dsSigPulse(write, size, 1, delay);
}

//Sets a signal to a step
bool dsSigStep(signal *write, double height, unsigned int delay) {
  //Set new length
  write->used_len = write->max_len;
  //Assume nothing goes wrong
  bool success = true;
  //If the step starts too late
  if (delay>=write->max_len) {
    success = false;
    delay = write->max_len;
  }
  //For each sample before the step
  for (unsigned int i=0; i<delay; i++) {
    //Set sample to 0
    write->samples[i] = 0.0;
  }
  //For each sample in the step
  for (unsigned int i=delay; i<write->max_len; i++) {
    //Set sample to height
    write->samples[i] = height;
  }
  //Return
  return success;
}

//Sets a signal to a ramp
bool dsSigRamp(signal *write, double slope, unsigned int delay) {
  //Set new length
  write->used_len = write->max_len;
  //Assume nothing goes wrong
  bool success = true;
  //If the step starts too late
  if (delay>=write->max_len) {
    success = false;
    delay = write->max_len;
  }
  //For each sample before the ramp
  for (unsigned int i=0; i<delay; i++) {
    //Set sample to 0
    write->samples[i] = 0.0;
  }
  //For each sample in the ramp
  double height = 0.0;
  for (unsigned int i=delay; i<write->max_len; i++) {
    //Increase height by slope
    height += slope;
    //Set sample to the increased height
    write->samples[i] = height;
  }
  //Return
  return success;
}

//Adds two signals
bool dsAddSignals(signal *write, const signal *read1, const signal *read2) {
  //Assume nothing goes wrong
  bool success = true;
  //Get the length of the longer signal
  unsigned int len;
  if (read1->used_len>read2->used_len) {
    len = read1->used_len;
  } else {
    len = read2->used_len;
  }
  //Limit the length
  if (len>write->max_len) {
    len = write->max_len;
    success = false;
  }
  //Update used length
  write->used_len = len;
  //For each sample
  for (unsigned int i=0; i<len; i++) {
    //Set the sample to 0
    write->samples[i] = 0.0;
    //Add the first signal
    if (i<read1->used_len) {
      write->samples[i] += read1->samples[i];
    }
    //Add the second signal
    if (i<read2->used_len) {
      write->samples[i] += read2->samples[i];
    }
  }
  //Return
  return success;
}

//Shifts a signal
bool dsTimeShift(signal *write, const signal *read, int shift) {
  //Assume nothing goes wrong
  bool success = true;
  //Copy samples
  double copy[read->used_len];
  for (unsigned int i=0; i<read->used_len; i++) {
    copy[i] = read->samples[i];
  }
  //Transfer each sample
  for (unsigned int i=0; i<read->used_len; i++) {
    //Check if sample is shifted too forward
    if (i+shift<0) {
      continue;
    }
    //Check if sample is shifted too backward
    if (i+shift>=write->max_len) {
      success = false;
      break;
    }
    //Transfer sample
    write->samples[i+shift] = copy[i];
  }
  //Clear new empty samples
  for (unsigned int i=0; i<shift; i++) {
    write->samples[i] = 0.0;
  }
  //Calculate used length
  if (read->used_len+shift<0) {
    write->used_len = 0;
  } else if (success) {
    write->used_len = read->used_len+shift;
  } else {
    write->used_len = write->max_len;
  }
  //Return
  return success;
}

//Convolves two signals
bool dsConvolve(signal *write, const signal *read1, const signal *read2) {
  //Assume nothing goes wrong
  bool success = true;
  //Copy first signal
  double copy1[read1->used_len];
  for (unsigned int i=0; i<read1->used_len; i++) {
    copy1[i] = read1->samples[i];
  }
  //Copy second signal
  double copy2[read2->used_len];
  for (unsigned int i=0; i<read2->used_len; i++) {
    copy2[i] = read2->samples[i];
  }
  //Calculate length
  unsigned int len = read1->used_len+read2->used_len-1;
  if (len>write->max_len) {
    success = false;
    len = write->max_len;
  }
  //Initialise values
  for (unsigned int i=0; i<len; i++) {
    write->samples[i] = 0.0;
  }
  //Convolve
  for (unsigned int i=0; i<read1->used_len; i++) {
    for (unsigned int j=0; j<read2->used_len; j++) {
      if (i+j>=len) {
        continue;
      }
      write->samples[i+j] += copy1[i]*copy2[j];
    }
  }
  //Write used length
  write->used_len = len;
  //Return
  return success;
}

/*================================*/
/* SYSTEMS ================================*/

//Sets the members of a system struct
void dsNewSystem(system *write, const signal *impulse_response, const signal *history) {
  write->imp_resp = *impulse_response;
  write->history = *history;
}

//Applies a system to a signal
bool dsApplySystem(signal *write, system *sys, const signal *sig, bool remember) {
  //Extend the signal with the system's history
  unsigned int ext_len = sys->history.used_len+sig->used_len;
  double extended_samples[ext_len];
  for (unsigned int i=0; i<sys->history.used_len; i++) {
    extended_samples[i] = sys->history.samples[i];
  }
  for (unsigned int i=0; i<sig->used_len; i++) {
    extended_samples[sys->history.used_len+i] = sig->samples[i];
  }
  signal ext_sig = {extended_samples, ext_len, ext_len};
  //Update the history of the system
  if (remember) {
    if (ext_len>sys->history.max_len) {
      dsTimeShift(&sys->history, &ext_sig, -ext_len+sys->history.max_len);
      sys->history.used_len = sys->history.max_len;
    } else {
      dsTimeShift(&sys->history, &ext_sig, 0); //Copy
      sys->history.used_len = ext_len;
    } 
  }
  //Convolve the extended signal with the impulse response
  return dsConvolve(write, &ext_sig, &sys->imp_resp);
}

//Resets the history of a system
void dsResetSystem(system *sys) {
  sys->history.used_len = 0;
}

//Sets a system to a scaling constant
bool dsSysScaling(system *write, double scaling) {
  return dsSigPulse(&write->imp_resp, scaling, 1, 0);
}

//Sets a system to a delay
bool dsSysDelay(system *write, unsigned int delay, double scaling) {
  return dsSigPulse(&write->imp_resp, scaling, 1, delay);
}

//Sets a system to an integrator
bool dsSysIntegrator(system *write, double scaling) {
  return dsSigStep(&write->imp_resp, scaling, 0);
}

//Sets a system to a differentiator
bool dsSysDifferentiator(system *write, double scaling) {
  bool success = dsSigPulse(&write->imp_resp, -scaling, 1, 1);
  write->imp_resp.samples[0] = scaling;
  return success;
}

//Sets a system to a moving average filter
bool dsSysMovingAverage(system *write, unsigned int width) {
  return dsSigPulse(&write->imp_resp, 1.0/width, width, 0);
}

//Sets a system to a first-order lowpass filter
bool dsSysLowpass(system *write, double gain, double cutoff, double sample_rate) {
  /*
  First-order lowpass filter has impulse response
  h(t) = K*w*e^(-w*t)
  where K is the gain, and w is the cutoff frequency.
  An increased sampling_rate decreases the effect of w,
  in the context of discrete-time.
  */
  if (write->imp_resp.max_len<1) {
    return false;
  }
  //Calculate the discrete w
  double w = cutoff/sample_rate;
  //Calculate e raised to the power of -w
  double e2w = exp(-w);
  //Set the initial value at t=0
  write->imp_resp.samples[0] = gain*w;
  //Decay the rest of the impulse response
  for (unsigned int i=1; i<write->imp_resp.max_len; i++) {
    write->imp_resp.samples[i] = write->imp_resp.samples[i-1]*e2w;
  }
  //Set the used length
  write->imp_resp.used_len = write->imp_resp.max_len;
  //Return
  return true;
}

//Sets a system to a first-order highpass filter
bool dsSysHighpass(system *write, double gain, double cutoff, double sample_rate) {
  /*
  First-order highpass filter has impulse response
  h(t) = K*d(t)-K*w*e^(-w*t)
  where K is the gain, d(t) is the Dirac-delta, and w is the cutoff frequency.
  An increased sampling_rate decreases the effect of w,
  in the context of discrete-time.
  */
  if (write->imp_resp.max_len<1) {
    return false;
  }
  //Create a negative lowpass filter
  dsSysLowpass(write, -gain, cutoff, sample_rate);
  //Add the Dirac-delta
  write->imp_resp.samples[0] += gain;
  //Return
  return true;
}

//Adds two systems
bool dsAddSystems(system *write, system *read1, system *read2) {
  //Assume nothing goes wrong
  bool success = true;
  //Add impulse responses
  if (!dsAddSignals(&write->imp_resp, &read1->imp_resp, &read2->imp_resp)) {
    success = false;
  }
  //Add history
  if (!dsAddSignals(&write->history, &read1->history, &read2->history)) {
    success = false;
  }
  //Return
  return true;
}

//Cascades two systems
bool dsCascade(system *write, system *read1, system *read2) {
  //Clear the history
  write->history.used_len = 0;
  //Convolve the impulse responses
  return dsConvolve(&write->imp_resp, &read1->imp_resp, &read2->imp_resp);
}

/*================================*/
/* ELECTRICITY ================================*/

//Returns the Direct-Current component of a signal
double dsDC(const signal *read) {
  //Call the dhMean function
  return dhMean(read->samples, read->used_len);
}

//Removes the Direct-Current offset from a signal
bool dsAC(signal *write, const signal *read) {
  //Assume nothing goes wrong
  bool success = true;
  //Determine length
  if (read->used_len>write->max_len) {
    success = false;
    write->used_len = write->max_len;
  } else {
    write->used_len = read->used_len;
  }
  //Get the DC component
  double dc = dhMean(read->samples, read->used_len);
  //For each data point
  for (unsigned int i=0; i<write->used_len; i++) {
    //Subtract the DC offset
    write->samples[i] = read->samples[i]-dc;
  }
  //Return
  return success;
}

//Gets the power of the signal at each time step
bool dsPower(signal *write, const signal *read) {
  //Assume nothing goes wrong
  bool success = true;
  //Determine length
  if (read->used_len>write->max_len) {
    success = false;
    write->used_len = write->max_len;
  } else {
    write->used_len = read->used_len;
  }
  //For each data point
  for (unsigned int i=0; i<write->used_len; i++) {
    //Calculate the power
    write->samples[i] = read->samples[i]*read->samples[i];
  }
  //Return
  return success;
}

//Returns the total energy of a signal
double dsEnergy(const signal *read) {
  //Create a signal for the power
  double samples[read->used_len];
  signal power;
  dsNewSignal(&power, samples, 0, read->used_len);
  //Get the power of the signal
  dsPower(&power, read);
  //Return the sum of the power
  return dhSum(power.samples, power.used_len);
}

//Gets the cumulative sum of energy of a signal
bool dsCumSumEnergy(signal *write, signal *read) {
  //Get the power of the signal
  bool success = dsPower(write, read);
  //Get the cumulative sum of the power
  dhCumSum(write->samples, write->samples, write->used_len);
  //Return
  return success;
}

//Returns the average power of a signal
double dsAvgPower(const signal *read) {
  //Create a signal for the power
  double samples[read->used_len];
  signal power;
  dsNewSignal(&power, samples, 0, read->used_len);
  //Get the power of the signal
  dsPower(&power, read);
  //Return the mean/average/expected value of the power
  return dhMean(power.samples, power.used_len);
}

//Returns the Alternating-Current Root-Mean-Square of a signal
double dsACRMS(const signal *read) {
  //Call the dhStdDev function
  return dhStdDev(read->samples, read->used_len);
}

//Returns the Root-Mean-Square of a signal
double dsRMS(const signal *read) {
  //The RMS is the square-root of the average power
  return sqrt(dsAvgPower(read));
}

//Returns the Direct-Current power of a signal
double dsDCPower(const signal *read) {
  //Get the DC component
  double dc = dhMean(read->samples, read->used_len);
  //Return the power of the DC component
  return dc*dc;
}

//Returns the Alternating-Current power of a signal
double dsACPower(const signal *read) {
  //Call the dhVar function
  return dhVar(read->samples, read->used_len);
}

/*================================*/
/* FOURIER ================================*/



/*================================*/