#include <stdio.h>
 
#define MAX_NUM 10
#define NUM 7

int main(void) {
    asm("l.debug");
    int f1 = 0, f2 = 1, fi = 1;
    int i = 1;
    int result;
    do {
        result += (i == NUM) * fi;
        fi = f1 + f2;
        f1 = f2;
        f2 = fi;
    } while (++i != MAX_NUM);
    printf("fib(%d) = %d\n", NUM, result);
    asm("l.debug");
    return 0;
}
