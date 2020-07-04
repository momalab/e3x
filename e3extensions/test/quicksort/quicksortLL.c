#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

int partition(int *arr, int l, int r) {
    int pivot = arr[l];
    int i = l;
    int p = r + 1;
    while (1) {
        do ++i; while (arr[i] <= pivot && i <= r);
        do --p; while (arr[p] > pivot);
        if (i >= p) break;
        swap(&arr[i], &arr[p]);
    }
    swap(&arr[l], &arr[p]);
    return p;
}

/** 
 * The above function implemented in low level C code, which is similar to CEAL.
 **/
int partitionLL(int arr[], int l, int r) {
    int pivot = arr[l];
    int *ptr1, *ptr2;
    int i = l;
    int p = r+1;
    int cond;
    while_true:
        ptr1 = arr;
        left_loop:
            i++;
            ptr1++;
            cond = 1;
            if (*ptr1 - pivot <= 0) goto if_cond1;
                cond = 0;
            if_cond1:
            if (i - r <= 0) goto if_cond2;
                cond = 0;
            if_cond2:
        if (cond) goto left_loop;
        ptr2 = arr + p;        
        right_loop:
            p--; 
            ptr2--;
            cond = *ptr2 > pivot;
        if (cond) goto right_loop;
        if (i >= p) goto break_loop;
        ptr1 = arr + i;
        ptr2 = arr + p;
        swap(ptr1, ptr2);
    goto while_true;
    break_loop:
    ptr1 = arr + l;
    ptr2 = arr + p;
    swap(ptr1, ptr2);
    return p;
}

void quickSort(int *arr, int l, int r) {
    if (l >= r) return;
    int p = partitionLL(arr, l, r);
    quickSort(arr, l, p-1);
    quickSort(arr, p+1, r);
}

void quickSortStack(int *arr, int l, int r) {
    int stack[r - l + 1];
    int stack_ptr = 0;
    stack[stack_ptr] = l;
    stack[stack_ptr + 1] = r;
    stack_ptr += 2;
    while (stack_ptr > 0) {                 // while stack not empty
        r = stack[stack_ptr - 1];
        l = stack[stack_ptr - 2];
        stack_ptr -= 2;
        int p = partition(arr, l, r);
        if (p - 1 > l) {
            stack[stack_ptr] = l;
            stack[stack_ptr + 1] = p - 1;
            stack_ptr += 2;
        }
        if (p + 1 < r) {
            stack[stack_ptr] = p + 1;
            stack[stack_ptr + 1] = r;
            stack_ptr += 2;
        }
    }
}

#if 0
int main(void) {
    int arr[] = { 7, 12, 3, 1, 20, 15, 5, 11, 9 };
    int size = sizeof(arr) / sizeof(int);
    printf("Unsorted array is:  ");
    for (int i = 0 ; i < size ; ++i)
        printf(" %d ", arr[i]);

    int stack_area[size];
    int *stack = stack_area;
    int *stack_bu = stack_area;
    int stack_ptr = 0;
    int *ptr1, *ptr2;
    int cond;

    int pivot, p, i;
    int l = 0;
    int r = size - 1;
    *stack = l;
    stack++;
    *stack = r;
    stack--;
    stack_ptr += 2;

    while_stack_not_empty:
        stack = stack_bu;
        stack += stack_ptr;
        stack--;
        r = *stack;
        stack--;
        l = *stack;
        stack_ptr -= 2;
        stack = stack_bu;

        // p = partition(arr, l, r);
        ptr1 = arr + l;
        pivot = *ptr1;
        i = l;
        p = r + 1;
        while_true:
            ptr1 = arr;
            left_loop:
                i++;
                ptr1++;
                cond = 1;
                if (*ptr1 - pivot <= 0) goto if_cond1;
                    cond = 0;
                if_cond1:
                if (i - r <= 0) goto if_cond2;
                    cond = 0;
                if_cond2:
            if (cond) goto left_loop;
            ptr2 = arr + p;        
            right_loop:
                p--; 
                ptr2--;
            if (pivot + 1 - *ptr2 <= 0) goto right_loop;
            if (p - i <= 0) goto break_loop;
            ptr1 = arr + i;
            ptr2 = arr + p;
            swap(ptr1, ptr2);
        goto while_true;
        break_loop:
        ptr1 = arr + l;
        ptr2 = arr + p;
        swap(ptr1, ptr2);
        // end of partition
        
        if (p - 1 - l <= 0) goto end_left;
            stack = stack_bu;
            stack += stack_ptr;
            *stack = l;
            stack++;
            *stack = p - 1;
            stack_ptr += 2;
        end_left:
        if (r - p - 1 <= 0) goto end_right;
            stack = stack_bu;
            stack += stack_ptr;
            *stack = p + 1;
            stack++;
            *stack = r;
            stack_ptr += 2;
        end_right:
    if (stack_ptr != 0) goto while_stack_not_empty;

    printf("\nSorted array is:  ");
    for (int i = 0 ; i < size ; ++i)
        printf(" %d ", arr[i]);
    printf("\n");
    return 0;
}
#else
int main(void) {
    int arr[] = { 7, 12, 3, 1, 20, 15, 5, 11, 9 };
    int size = sizeof(arr) / sizeof(int);
    printf("Unsorted array is:  ");
    for (int i = 0 ; i < size ; ++i)
        printf(" %d ", arr[i]);

    quickSort(arr, 0, size-1);

    printf("\nSorted array is:  ");
    for (int i = 0 ; i < size ; ++i)
        printf(" %d ", arr[i]);
    printf("\n");
    return 0;
}
#endif
