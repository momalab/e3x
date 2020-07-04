#include <stdio.h>

#define MAXNUM 100

int main(void) {
    int p, q, x;
    p = 1;

candidate_loop:
    if (++p == MAXNUM) return 0;
    q = 1;
    next_div_loop:
        q++;
        x = p;
        if (x <= q) printf("%d ",p);
        dec_x_loop:
            x -= q;
            if (x <= 0) goto x_leq;
            goto dec_x_loop;
            x_leq:
                if (x == 0) goto candidate_loop;
                else goto next_div_loop;
        goto dec_x_loop;
}
