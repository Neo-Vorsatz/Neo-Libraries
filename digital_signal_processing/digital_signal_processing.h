// Digial Signal Processing Library, for processing signals
// Header file
// by Neo Vorsatz
// Last updated: 29 May 2026

//Header guard
#ifndef DIGITAL_SIGNAL_PROCESSING_H
#define DIGITAL_SIGNAL_PROCESSING_H

//Includes
#include <stdbool.h>

//C++ compatibility
#ifdef __cplusplus
  extern "C" {
#endif

/* TYPE DEFINITIONS ================================*/

//Structure for signals
typedef struct{
  double *samples; //Pointer to array of samples
  unsigned int used_len; //Number of samples
  unsigned int max_len; //Maximum number of samples
} signal;

//Structure for a system
typedef struct{
  signal imp_resp; //Impulse response
  signal history; //Past inputs
} system;

/*================================*/
/* SYSTEMS ================================*/



/*================================*/
/* ELECTRICITY ================================*/

/**
 * @param read A pointer to the signal
 * 
 * @return The Direct-Current component of a signal
 */
double dsDC(const signal *read);

/**
 * @brief Removes the Direct-Current offset from a signal
 * 
 * @param write A pointer to where the modified signal will be written
 * @param read A pointer to the signal
 * 
 * @return 1 (true) if the process was successful, otherwise 0 (false) if there was not enough memory in 'write'
 */
bool dsAC(signal *write, const signal *read);

/**
 * @brief Gets the power of the signal at each time step
 * 
 * @param write A pointer to where the power of the signal will be written
 * @param read A pointer to the signal
 * 
 * @return 1 (true) if the process was successful, otherwise 0 (false) if there was not enough memory in 'write'
 */
bool dsPower(signal *write, const signal *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The total energy of a signal
 */
double dsEnergy(const signal *read);

/**
 * @brief Gets the cumulative sum of energy of a signal
 * 
 * @param write A pointer to where the cumulative sum of energy will be written
 * @param read A pointer to the signal
 * 
 * @return 1 (true) if the process was successful, otherwise 0 (false) if there was not enough memory in 'write'
 */
bool dsCumSumEnergy(signal *write, signal *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The average power of a signal
 */
double dsAvgPower(const signal *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Alternating-Current Root-Mean-Square of a signal
 */
double dsACRMS(const signal *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Root-Mean-Square of a signal
 */
double dsRMS(const signal *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Direct-Current power of a signal
 */
double dsDCPower(const signal *read);

/**
 * @param read A pointer to the signal
 * 
 * @return The Alternating-Current power of a signal
 */
double dsACPower(const signal *read);

/*================================*/
/* FOURIER ================================*/



/*================================*/

#ifdef __cplusplus
  }
#endif

#endif