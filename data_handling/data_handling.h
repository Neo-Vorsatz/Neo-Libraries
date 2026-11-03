// Data Handling Library, for processing data
// Header file
// by Neo Vorsatz
// Last updated: 27 December 2025

//Header guard
#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

//C++ compatibility
#ifdef __cplusplus
  extern "C" {
#endif

/* SUMMING ================================*/

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The sum of an array of data values
 */
double dhSum(const double data[], unsigned int length);

/**
 * @brief Gets the cumulative sum of an array of data values
 * 
 * @param write A pointer to where the cumulative sum will be written
 * @param data A pointer to the array of data values
 * @param length The number of data values
 */
void dhCumSum(double write[], const double data[], unsigned int length);

/*================================*/
/* SORTING ================================*/

/**
 * @brief Copies an array of data into another array
 * 
 * @param write A pointer to where the copy will be written
 * @param data A pointer to the array of data values
 * @param length The number of data values
 */
void dhCopy(double write[], const double data[], unsigned int length);

/**
 * @brief Sorts an array of data in ascending order using the Quick Sort algorithm
 * 
 * @param write A pointer to where the sorted data will be written
 * @param data A pointer to the array of data values
 * @param length The number of data values
 */
void dhQuickSort(double write[], const double data[], unsigned int length);

/**
 * @brief Sorts an array of data in ascending order using the Merge Sort algorithm
 * 
 * @param write A pointer to where the sorted data will be written
 * @param data A pointer to the array of data values
 * @param length The number of data values
 */
void dhMergeSort(double write[], const double data[], unsigned int length);

/**
 * @brief Reverses an array of data
 * 
 * @param write A pointer to where the reversed array will be written
 * @param data A pointer to the array of data values
 * @param length The number of data values
 */
void dhReverse(double write[], const double data[], unsigned int length);

/*================================*/
/* STATISTICS ================================*/

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The smallest value in an array of data values
 */
double dhMin(const double data[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The largest value in an array of data values
 */
double dhMax(const double data[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The mean/average/expected value of an array of data values
 */
double dhMean(const double data[], unsigned int length);

/**
 * @brief Does the same thing as the dhMean function
 * 
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The mean/average/expected value of an array of data values
 */
double dhAvg(const double data[], unsigned int length);

/**
 * @brief Does the same thing as the dhMean function
 * 
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The mean/average/expected value of an array of data values
 */
double dhExpectedValue(const double data[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The varience of an array of data values, assuming the data represents the population
 */
double dhVar(const double data[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The standard deviance of an array of data values, assuming the data represents the population
 */
double dhStdDev(const double data[], unsigned int length);

/**
 * @param sortedData A pointer to the sorted array of data values
 * @param length The number of data values
 * 
 * @return The median of a sorted array of data values
 */
double dhMedianSorted(const double sortedData[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The median of an array of data values
 */
double dhMedian(const double data[], unsigned int length);

/**
 * @param sortedData A pointer to the sorted array of data values
 * @param length The number of data values
 * 
 * @return The lower quartile of a sorted array of data values
 */
double dhLowerQuartileSorted(const double sortedData[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The lower quartile of an array of data values
 */
double dhLowerQuartile(const double data[], unsigned int length);

/**
 * @param sortedData A pointer to the sorted array of data values
 * @param length The number of data values
 * 
 * @return The upper quartile of a sorted array of data values
 */
double dhUpperQuartileSorted(const double sortedData[], unsigned int length);

/**
 * @param data A pointer to the array of data values
 * @param length The number of data values
 * 
 * @return The upper quartile of an array of data values
 */
double dhUpperQuartile(const double data[], unsigned int length);

/*================================*/

#ifdef __cplusplus
  }
#endif

#endif