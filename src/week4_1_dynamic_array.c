/*
 * week4_1_dynamic_array.c
 * description: Dynamic array using malloc
 */
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int n;
    int *arr = NULL;
    int sum = 0;
    double average;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) !=1 || n <=0) {
        printf("Invalid size.\n");
        return 1;
    }
    //allocate memory for the array
    arr = malloc((size_t)n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter %d integers: ", n);
    //red numbers and calculate sum
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) !=1) {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
        sum += arr[i];
    }
    average = (double)sum / n;

    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", average);

    //free allocated memory
    free(arr);
    return 0;
}