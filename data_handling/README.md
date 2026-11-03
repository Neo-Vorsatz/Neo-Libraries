# C Data Handling
## Overview
This module is for handling data and performing statistical calculations in C.<br>
Some functionality this module offers is:
- Getting the cumulative sum of data
- Sorting data in ascending order, or reversing the order
- Getting the mean, variance and standard deviation of a set of data

## Features
This module was designed with the intention of being embedded-friendly:
- Minimal memory footprint
- No dynamic memory usage (no `malloc` and `free`)
- Low namespace pollution (uses `dh` prefix)

## Quick Start
```c
#include <stdio.h>
#include "data_handling.h"

int main() {
  double data[] = {1.0, 5.2, 7.3, 0.0, 2.9, 5.2, 13.4};
  unsigned int length = sizeof(data)/sizeof(data[0]);
  
  double sortedData[length];
  dhQuickSort(sortedData, data, length);

  printf("Sorted Data: {");
  for (unsigned int i=0; i<length-1; i++) {
      printf("%.3f, ", sortedData[i]);
  }
  printf("%.3f}", sortedData[length-1]);
  
  return 0;
}
```

## Installation & Dependencies
Copy the header and implementation files anywhere where your C-compiler can find it (such as in the same directory as your main file). Then import the module like you would any other module, using `#include`.

This module has the following dependencies:<br>
Standard: `math.h`<br>
This Repository: None

## API Reference
### Functions
<details>
<summary>Click to view all Summing functions</summary>

`double dhSum(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the sum of an array of data values.

`void dhCumSum(double write[], const double data[], unsigned int length);`<br>
Gets the cumulative sum of an array of data values.<br>
Takes a pointer to where the cumulative sum will be written, a pointer to the array of data values, and the number of data values.

</details>

<details>
<summary>Click to view all Sorting functions</summary>

`void dhCopy(double write[], const double data[], unsigned int length);`<br>
Copies an array of data into another array.<br>
Takes a pointer to where the copy will be written, a pointer to the array of data values, and the number of data values.

`void dhQuickSort(double write[], const double data[], unsigned int length);`<br>
Sorts an array of data in ascending order using the Quick Sort algorithm.<br>
Takes a pointer to where the sorted data will be written, a pointer to the array of data values, and the number of data values.

`void dhMergeSort(double write[], const double data[], unsigned int length);`<br>
Sorts an array of data in ascending order using the Merge Sort algorithm.<br>
Takes a pointer to where the sorted data will be written, a pointer to the array of data values, and the number of data values.

`void dhReverse(double write[], const double data[], unsigned int length);`<br>
Reverses an array of data.<br>
Takes a pointer to where the reversed array will be written, a pointer to the array of data values, and the number of data values.

</details>

<details>
<summary>Click to view all Statistics functions</summary>

`double dhMin(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the smallest value in an array of data values.

`double dhMax(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the largest value in an array of data values.

`double dhMean(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the mean/average/expected value of an array of data values.

`double dhAvg(const double data[], unsigned int length);`<br>
Does the same thing as the `dhMean` function.<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the mean/average/expected value of an array of data values.

`double dhExpectedValue(const double data[], unsigned int length);`<br>
Does the same thing as the `dhMean` function.<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the mean/average/expected value of an array of data values.

`double dhVar(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the varience of an array of data values.

`double dhStdDev(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the standard deviance of an array of data values.

`double dhMedianSorted(const double sortedData[], unsigned int length);`<br>
Takes a pointer to the sorted array of data values, and the number of data values.<br>
Returns the median of a sorted array of data values.

`double dhMedian(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the median of an array of data values.

`double dhLowerQuartileSorted(const double sortedData[], unsigned int length);`<br>
Takes a pointer to the sorted array of data values, the number of data values.<br>
Returns the lower quartile of a sorted array of data values.

`double dhLowerQuartile(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the lower quartile of an array of data values.

`double dhUpperQuartileSorted(const double sortedData[], unsigned int length);`<br>
Takes a pointer to the sorted array of data values, and the number of data values.<br>
Returns the upper quartile of a sorted array of data values.

`double dhUpperQuartile(const double data[], unsigned int length);`<br>
Takes a pointer to the array of data values, and the number of data values.<br>
Returns the upper quartile of an array of data values.

</details>