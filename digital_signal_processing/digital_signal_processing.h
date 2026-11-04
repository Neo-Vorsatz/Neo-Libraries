/*
    Digital Signal Processing Library, for processing signals
    Header file
    Author: Neo Vorsatz
    Last updated: 4 November 2026
*/

// Header guard
#ifndef DIGITAL_SIGNAL_PROCESSING_H
#define DIGITAL_SIGNAL_PROCESSING_H

// IMPORTS ================================

// External
#include <stdbool.h>

// C++ COMPATIBILITY ================================

#ifdef __cplusplus
    extern "C" {
#endif

// TYPES ================================

// Structure for signals
typedef struct{
    double *samples; // pointer to array of samples
    unsigned int used_len; // number of samples
    unsigned int max_len; // maximum number of samples
} dsSignal_t;

// Structure for systems
typedef struct{
    dsSignal_t imp_resp; // impulse response
    dsSignal_t history; // past inputs
} dsSystem_t;

// SYSTEMS ================================



// ELECTRICITY ================================

/**
 * @param read A pointer to the signal
 * 
 * @return The Direct-Current component of a signal
 */
double dsDC(const dsSignal_t *read);

/**
 * @brief Removes the Direct-Current offset from a signal
 * 
 * @param write A pointer to where the modified signal will be written
 * @param read A pointer to the signal
 * 
 * @return `true` if the process was successful, otherwise `false` if there was not enough memory in 'write'
 */
bool dsAC(dsSignal_t *write, const dsSignal_t *read);

/**
 * @brief Gets the power of the signal at each time step
 * 
 * @param write A pointer to where the power of the signal will be written
 * @param read A pointer to the signal
 * 
 * @return `true` if the process was successful, otherwise `false` if there was not enough memory in 'write'
 */
bool dsPower(dsSignal_t *write, const dsSignal_t *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The total energy of a signal
 */
double dsEnergy(const dsSignal_t *read);

/**
 * @brief Gets the cumulative sum of energy of a signal
 * 
 * @param write A pointer to where the cumulative sum of energy will be written
 * @param read A pointer to the signal
 * 
 * @return `true` if the process was successful, otherwise `false` if there was not enough memory in 'write'
 */
bool dsCumSumEnergy(dsSignal_t *write, dsSignal_t *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The average power of a signal
 */
double dsAvgPower(const dsSignal_t *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Alternating-Current Root-Mean-Square of a signal
 */
double dsACRMS(const dsSignal_t *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Root-Mean-Square of a signal
 */
double dsRMS(const dsSignal_t *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Direct-Current power of a signal
 */
double dsDCPower(const dsSignal_t *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Alternating-Current power of a signal
 */
double dsACPower(const dsSignal_t *read);

// FOURIER ================================



// ================================

#ifdef __cplusplus
    }
#endif

#endif
