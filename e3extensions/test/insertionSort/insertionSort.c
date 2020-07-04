/* insertion sort ascending order */
#include <stdio.h>
 
// swap if the second is greater
void minswp(int *x, int *y) {
    if (*x < *y) {
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }
}

int gfun(int x, int y) {
    return (x <= 0) ? 0 : y;
}

#if 1

int main(void) {
    asm("l.debug");
    int n = 10, i, j;
    int array[10] = { 4, 2, 5, 9, 1, 0, 4, 3, 9, 8 };

    for (i = 1 ; i < n; i++) {
        j = i;
        while (j != 0) {
            int x = array[j-1];
            int y = array[j];

            int diff = gfun(x-y, x-y) + gfun(y-x, y-x);
            int max = gfun(x-y, x) + gfun(y-x, y);
            max += (x == y) * x; // if x == y set max to x
            int min = max - diff;

            array[j-1] = min;
            array[j] = max;
            j--;
        }
    }

    for (i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
    asm("l.debug");
    return 0;
}

#else

int main(void) {
    int n = 20, j;
    int array[20] = { 4, 2, 5, 7, 1, 0, 11, 3, 9, 8, 4, 5, 6, 1, 2, 3, 7, 9, 10, 2 };
    int *arrayPrev = array;
    int *arrayCur = array;

    int i = 1;
    outer_loop:
        j = i;
        arrayCur = array + i;
        inner_loop:
            arrayPrev = arrayCur-1;
            minswp(arrayCur, arrayPrev);
            j--;
            arrayCur--;
        if (j != 0) goto inner_loop;
        i++;
    if (i != n) goto outer_loop;

    for (i = 0; i < n; i++)
        printf("%d  ", array[i]);
    printf("\n");
    return 0;
}

#endif
