#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 
// Function to insert and merge intervals
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc((intervalsSize + 1) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((intervalsSize + 1) * sizeof(int));
    int count = 0;
    int i = 0;

    // Add all intervals before newInterval (non-overlapping)
    while (i < intervalsSize && intervals[i][1] < newInterval[0]) {
        result[count] = (int*)malloc(2 * sizeof(int));
        result[count][0] = intervals[i][0];
        result[count][1] = intervals[i][1];
        (*returnColumnSizes)[count] = 2;
        count++;
        i++;
    }

    // Merge overlapping intervals
    while (i < intervalsSize && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = (intervals[i][0] < newInterval[0]) ? intervals[i][0] : newInterval[0];
        newInterval[1] = (intervals[i][1] > newInterval[1]) ? intervals[i][1] : newInterval[1];
        i++;
    }

    // Add the merged newInterval
    result[count] = (int*)malloc(2 * sizeof(int));
    result[count][0] = newInterval[0];
    result[count][1] = newInterval[1];
    (*returnColumnSizes)[count] = 2;
    count++;

    // Add remaining intervals
    while (i < intervalsSize) {
        result[count] = (int*)malloc(2 * sizeof(int));
        result[count][0] = intervals[i][0];
        result[count][1] = intervals[i][1];
        (*returnColumnSizes)[count] = 2;
        count++;
        i++;
    }

    *returnSize = count;
    return result;
}

int main() {
    int intervals1[][2] = {{1, 3}, {6, 9}};
    int* intervals1Ptrs[] = {intervals1[0], intervals1[1]};
    int intervals1ColSize = 2;
    int newInterval1[] = {2, 5};
    int returnSize1;
    int* returnColumnSizes1;
    int** result1 = insert(intervals1Ptrs, 2, &intervals1ColSize, newInterval1, 2, &returnSize1, &returnColumnSizes1);
    printf("Input: intervals = [[1,3],[6,9]], newInterval = [2,5]\n");
    printf("Output: [");
    for (int i = 0; i < returnSize1; ++i) {
        printf("[%d,%d]", result1[i][0], result1[i][1]);
        if (i < returnSize1 - 1) printf(",");
    }
    printf("]\n");
    for (int i = 0; i < returnSize1; ++i) {
        free(result1[i]);
    }
    free(result1);
    free(returnColumnSizes1);

    int intervals2[][2] = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    int* intervals2Ptrs[] = {intervals2[0], intervals2[1], intervals2[2], intervals2[3], intervals2[4]};
    int intervals2ColSize = 2;
    int newInterval2[] = {4, 8};
    int returnSize2;
    int* returnColumnSizes2;
    int** result2 = insert(intervals2Ptrs, 5, &intervals2ColSize, newInterval2, 2, &returnSize2, &returnColumnSizes2);
    printf("Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]\n");
    printf("Output: [");
    for (int i = 0; i < returnSize2; ++i) {
        printf("[%d,%d]", result2[i][0], result2[i][1]);
        if (i < returnSize2 - 1) printf(",");
    }
    printf("]\n");
    for (int i = 0; i < returnSize2; ++i) {
        free(result2[i]);
    }
    free(result2);
    free(returnColumnSizes2);

    return 0;
}
