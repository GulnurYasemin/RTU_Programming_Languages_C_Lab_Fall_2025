/*
 * week4_1_dynamic_array.c
 * Author: [Your Name]
 * Student ID: [Your ID]
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Students should allocate memory for an integer array, fill it with data,
 *   compute something (sum & average), and then free the memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;  // pointer for dynamic array

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    //  Allocate memory for n integers using malloc
    arr = (int *)malloc(n * sizeof(int));

    //  Check allocation success
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    //  Read n integers from user input and store in array
    printf("Enter %d integers: ", n);
    long long sum = 0;  // long long avoids overflow for large sums
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    //  Compute average
    double average = (double)sum / n;

    //  Print the results
    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    //  Free allocated memory
    free(arr);

    return 0;
}
