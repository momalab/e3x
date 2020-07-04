#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define X 9999

/************************************************************
** Array intersection without Branches on Encrypted values
*************************************************************
************************************************************************************************
** For every element in the first array, check every element in the second. 
** Return an array of the same size. The two arrays must have equal sizes. If not, the smallest 
** should be padded with X's.
***********************************************************************************************/

#if 1

int* intersect(int arr1[], int arr2[], int size) {
    int *res = calloc(size, sizeof(int));
    int *exist = calloc(size, sizeof(int));

    for (int i = 0; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {
            int eq = (arr1[i] == arr2[j]) ? 1 : 0;
            exist[i] += eq;
            res[i] += eq * arr1[i];
            arr1[i] += eq * X;
            arr2[j] += eq * X;
        }
    }
    for (int i = 0 ; i < size ; i++) {
        res[i] = (1-exist[i]) * X + exist[i] * res[i];
    }
    return res;
}

#else

int* intersect(int arr1[], int arr2[], int size) {
    int i = 0, j = 0, eq;
    int *res = calloc(size, sizeof(int));
    int *exist = calloc(size, sizeof(int));
    int *res_bu = res, *exist_bu = exist, *arr2_bu = arr2;

    outer:
        j = 0;
        arr2 = arr2_bu;
        inner:
            eq = (*arr1 == *arr2) ? 1 : 0;
            *res += eq * *arr1;             // res[i] += eq * arr1[i];
            *exist += eq;                     // exist[i] += eq;
            *arr2 += eq * X;
            *arr1 += eq * X;
            j++;
            arr2++;
        if (j < size) goto inner;
        i++;
        arr1++;
        res++;
        exist++;
    if (i < size) goto outer;

/* compute the final result */
    int ex, nex, tmp, r1,r2;
    i = 0;
    exist = exist_bu;
    res = res_bu;
    comp_res:
        ex = *exist;
        nex = 1 - ex;
        tmp = *res;
        r1 = ex * tmp;
        r2 = nex * X;
        *res = r1 + r2;
        i++;
        res++;
        exist++;
    if (i < size) goto comp_res;

    return res_bu;
}

#endif


int main(void) {
#if 1
    int arr1[10] = { 1, 1, 1, 2, 3, X, X, X, X, X };
    int arr2[10] = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1 };
#else
    int arr1[10] = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1 };
    int arr2[10] = { 1, 1, 1, 2, 3, X, X, X, X, X };
#endif

    int m = sizeof(arr1) / sizeof(int);
    int n = sizeof(arr2) / sizeof(int);
    assert(m == n);
    int size = m;
    int *res = intersect(arr1, arr2, size);
    for (int i = 0 ; i < size ; i++)
        if (res[i] == X)
            printf("X  ");
        else
            printf("%d  ", res[i]);
    printf("\n");

    return 0;
}
