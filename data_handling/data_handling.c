/*
    Data Handling Library, for processing data
    Implementation file
    Author: Neo Vorsatz
    Last updated: 4 November 2026
*/

// IMPORTS ================================

// External
#include <math.h>
#include <string.h>

// Internal
#include "data_handling.h"

// SUMMING ================================

double dhSum(const double data[], unsigned int length) {
    // Initialise the sum
    double sum = 0.0;
    // For each data point
    for (unsigned int i=0; i<length; i++) {
        // Add the data point to the sum
        sum += data[i];
    }
    // Return the sum
    return sum;
}

void dhCumSum(double write[], const double data[], unsigned int length) {
    // Initialise the sum
    double sum = 0.0;
    // For each data point
    for (unsigned int i=0; i<length; i++) {
        // Add the data point to the sum
        sum += data[i];
        // Write the cumulative sum to the corresponding index
        write[i] = sum;
    }
}

// SORTING ================================

void dhCopy(double write[], const double data[], unsigned int length) {
    // If the pointers aren't identical
    if (write != data) {
        // Call memcpy
        memcpy(write, data, length*sizeof(double));
    } 
}

/**
 * @brief Recursively sort a range of an array using the quick sort algorithm
 * 
 * @param array The array to sort
 * @param low The lower bound of the range to sort
 * @param high The upper bound of the range to sort
 */
static void qsort_recursive(double array[], int low, int high) {
    if (low < high) {
        // Choose last element in the range as the pivot
        double pivot = array[high];
        // Index of the new partition
        int part_i = low;
        // For each element within the partition range, except the last element
        for (unsigned int i=low; i<high; i++) {
            // If this element is smaller than the pivot
            if (array[i] < pivot) {
                // Place this element left of the new partition, via a swap
                double temp = array[part_i];
                array[part_i] = array[i];
                array[i] = temp;
                // Increment the index of the new partition
                part_i++;
            }
        }
        // Place the pivot at the new partition, via a swap
        array[high] = array[part_i];
        array[part_i] = pivot;
        // Recursively sort the elements before the pivot
        qsort_recursive(array, low, part_i - 1);
        // Recursively sort the elements after the pivot
        qsort_recursive(array, part_i + 1, high);
    }
}

void dhQuickSort(double write[], const double data[], unsigned int length) {
    // Copy the contents from the source to the destination
    dhCopy(write, data, length);
    // Call the recursive function
    qsort_recursive(write, 0, length - 1);
}

/**
 * @brief Recursively sort an array using the merge sort algorithm
 * 
 * @param array The array to sort
 * @param temp  A temporary buffer to build the filtered range
 * @param low The lower bound of the range to sort
 * @param high The upper bound of the range to sort
 */
static void msort_recursive(double array[], double temp[], int low, int high) {
    // If the range is not empty
    if (low<high) {
        // Calculate the midpoint
        int mid = (low + high) / 2;
        // Recursively sort the first half of elements
        msort_recursive(array, temp, low, mid);
        // Recursively sort the second half of elements
        msort_recursive(array, temp, mid+1, high);
        
        // Index for the first half
        int i_1st = low;
        // Index fo the second half
        int i_2nd  = mid + 1;
        // Index for the merged array
        int i_merge = low;
        // While both first and second arrays have elements left
        while (i_1st <= mid && i_2nd <= high) {
            // If the first half has a smaller element than the second
            if (array[i_1st] < array[i_2nd]) {
                // Add the element from the first half
                temp[i_merge++] = array[i_1st++];
            } else {
                // Add the element from the second half
                temp[i_merge++] = array[i_2nd++];
            }
        }
        // While there are remaining elements from the first half
        while (i_1st <= mid) {
            // Add the element from the first half
            temp[i_merge++] = array[i_1st++];
        }
        // While there are remaining elements from the second half
        while (i_2nd <= high) {
            // Add the element from the second half
            temp[i_merge++] = array[i_2nd++];
        }

        // Copy the sorted range into the original array
        dhCopy(array + low, temp + low, high - low + 1);
    }
}

void dhMergeSort(double write[], const double data[], unsigned int length) {
    // Copy the contents from the source to the destination
    dhCopy(write, data, length);
    // Create temporary array for merging
    double temp[length]; // TODO: fix so that stack size remains consistent
    // Call the recursive function
    msort_recursive(write, temp, 0, length - 1);
}

void dhReverse(double write[], const double data[], unsigned int length) {
    // Create temporary array for reversing
    double temp[length];
    // For each element in the original array
    for (unsigned int i=0; i<length; i++) {
        // Copy the element from the original array to the temporary array
        temp[length - 1 - i] = data[i];
    }
    // For each element in the temporary array
    for (unsigned int i=0; i<length; i++) {
        // Copy the element from the temporary array to the output
        write[i] = temp[i];
    }
}

// STATISTICS ================================

double dhMin(const double data[], unsigned int length) {
    // If there are no elements
    if (length < 1) {
        // Return 0 as the minimum
        return 0.0;
    }

    // Assume the minimum is the first value
    double min = data[0];
    // For each data point other than the first
    for (unsigned int i=1; i<length; i++) {
        // If this value is less than the minimum
        if (data[i] < min) {
            // Update the minimum
            min = data[i];
        }
    }
    return min;
}

double dhMax(const double data[], unsigned int length) {
    // If there are no elements
    if (length < 1) {
        // Return 0 as the maximum
        return 0.0;
    }

    // Assume the maximum is the first value
    double max = data[0];
    // For each data point other than the first
    for (unsigned int i=1; i<length; i++) {
        // If this value is more than the maximum
        if (data[i] > max) {
            // Update the maximum
            max = data[i];
        }
    }
    return max;
}

double dhMean(const double data[], unsigned int length) {
    // If there are no elements
    if (length < 1) {
        // Return 0 as the mean
        return 0.0;
    }

    // Get the sum
    double sum = dhSum(data, length);
    // Return the average
    return sum / length;
}

double dhAvg(const double data[], unsigned int length) {
    // Call the dhMean function
    return dhMean(data, length);
}

double dhExpectedValue(const double data[], unsigned int length) {
    // Call the dhMean function
    return dhMean(data, length);
}

double dhVar(const double data[], unsigned int length) {
    //If there are no elements
    if (length < 1) {
        // Return 0 as the variance
        return 0.0;
    }

    // Initialise sum of square-differences
    double sumSqrDiff = 0.0;
    // Get the mean/average/expected value
    double mean = dhMean(data, length);
    // For each data point
    for (unsigned int i=0; i<length; i++) {
        // Get the difference
        double diff = data[i] - mean;
        // Add the squared difference to the sum
        sumSqrDiff += diff * diff;
    }

    // Return the mean/average/expected value of the squared difference
    return sumSqrDiff / length;
}

double dhStdDev(const double data[], unsigned int length) {
    // The standard deviance is the square-root of the variance
    return sqrt(dhVar(data, length));
}

double dhMedianSorted(const double sortedData[], unsigned int length) {
    // If there are no elements
    if (length < 1) {
        // Return 0 as the median
        return 0.0;
    }

    // Find the middle index
    int middle = length / 2;
    // If there are an even number of data values
    if (length % 2 == 0) {
        // Calculate the median
        double median = (sortedData[middle - 1] + sortedData[middle]) / 2;
        // Return the median
        return median;
    }
    //Return the value at the middle index
    return sortedData[middle];
}

double dhMedian(const double data[], unsigned int length) {
    // Declare an array for the sorted data
    double sortedData[length];
    // Sort the data
    dhMergeSort(sortedData, data, length);
    // Return the median of the sorted data
    return dhMedianSorted(sortedData, length);
}

double dhLowerQuartileSorted(const double sortedData[], unsigned int length) {
    // If there are no elements
    if (length < 1) {
        // Return 0 as the lower quartile
        return 0.0;
    }
    // If there's only 1 element
    if (length < 2) {
        // Return the only element
        return sortedData[0];
    }

    // Find the middle index
    int middle = length / 2;
    // Return the median of the lower half of data
    return dhMedianSorted(sortedData, middle);
}

double dhLowerQuartile(const double data[], unsigned int length) {
    // Declare an array for the sorted data
    double sortedData[length];
    // Sort the data
    dhMergeSort(sortedData, data, length);
    // Return the lower quartile of the sorted data
    return dhLowerQuartileSorted(sortedData, length);
}

double dhUpperQuartileSorted(const double sortedData[], unsigned int length) {
    // If there are no elements
    if (length < 1) {
        // Return 0 as the upper quartile
        return 0.0;
    }
    // If there's only 1 element
    if (length < 2) {
        // Return the only element
        return sortedData[0];
    }

    // Find the middle index
    int middle = length / 2;
    // Find the starting index of the upper half of data
    const double* start = sortedData + middle;
    // If there are an odd number of data values
    if (length % 2 != 0) {
        // Skip over the middle value (median)
        start++;
    }
    //Return the median of the upper half of data
    return dhMedianSorted(start, middle);
}

double dhUpperQuartile(const double data[], unsigned int length) {
    // Declare an array for the sorted data
    double sortedData[length];
    // Sort the data
    dhMergeSort(sortedData, data, length);
    // Return the upper quartile of the sorted data
    return dhUpperQuartileSorted(sortedData, length);
}
