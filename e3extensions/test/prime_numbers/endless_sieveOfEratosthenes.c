#include <stdio.h>

#define N 50
#define N_SUCC (N+1)
#define MAX_N 300
/********************************************************
** Create a boolean array "prime[0..n]" and initialize
** all entries it as true. A value in prime[i] will
** finally be false if i is Not a prime, else true.
********************************************************/
#if 1

void sieveOfEratosthenes(int *prime, int base) {
    for (int i = 0 ; i < N+1 ; i++)         // re-initialize the array
        prime[i] = 1;
    for (int p = 2 ; p*p < N+1 + base ; p++) {
        int i = 2*p;
        while (i < base) i += p;
        for ( ; i < N+1 + base ; i += p) {  // Update all multiples of p
            prime[i - base] = 0;
        }
    }
    for (int p = 0 ; p < N ; p++)           // Print all prime numbers
        printf("%d ", (p+base) * prime[p]);
    printf("\n");
}

int main(void) {
    int prime[N+1];
    int base = 0;
    do {
        sieveOfEratosthenes(prime, base);
        base += N;
    } while (base < MAX_N);
    return 0;
}

#else

/********************************************************
** A low level implementation of the above function
********************************************************/

int main(void) {
    int prime[N+1];
    int *p_ptr_bu = prime;
    int base = 0;
    do {
        int i = 0;
        init_loop:
            prime[i] = 1;
            i++;
        if (i != N_SUCC) goto init_loop;

        int x, p = 2;
        int *primeOuter = p_ptr_bu + p;
        int *primeInner;
        outer_loop:
            i = p; i += p;
            inc_i_loop:
            if (base - i <= 0) goto inner_loop;
                i += p;
            goto inc_i_loop;
            inner_loop:
                primeInner = p_ptr_bu + i - base;
                *primeInner = 0;
                i += p;
            if (i < N+1+base) goto inner_loop;
            primeOuter++;
            p++;
        if (p*p < N+1+base) goto outer_loop;

        p = 0;
        print_loop:
            printf("%d ", (p + base) * p_ptr_bu[p]);
            p++;
        if (p != N) goto print_loop;

        // printf("\n");
        base += N;
    } while (base <= MAX_N);

    return 0;
}

#endif
