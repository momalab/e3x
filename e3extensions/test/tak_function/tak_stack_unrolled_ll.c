#include <stdio.h>
#include <assert.h>

#define MAX_NUM 9
#define ITERATIONS 8

int tak(int x, int y, int z) {
    while (x > y) {
        int oldx = x, oldy = y;
        x = tak(x - 1, y, z);
        y = tak(y - 1, z, oldx);
        if (x <= y) 
            break;
        z = tak(z - 1, oldx, oldy);
    }
    return z;
}

int gfun(int x, int y) {
    return (x <= 0) ? 0 : y;
}

int main(void) {
    int stack[256];
    int stack_ptr = 0;
    int ret_pos;
    int i = 0;
    do {
        int j = 0;
        do {
            int k = 0;
            do {
                /* Tak function */
                int x = i, y = j, z = k, iter = ITERATIONS;
                int sel, ret_val;
                tak_function: {               
                    sel = gfun(x-y, 1);     // sel = x > y;
                    while_iter:
                    if (!iter) goto end_while_iter;
                        iter--;
                        int oldx = (1 - sel) * oldx + sel * x;
                        int oldy = (1 - sel) * oldy + sel * y;

                        // stack, recurse and unstack vars
                        stack[stack_ptr] = oldx;    stack[stack_ptr + 1] = oldy;
                        stack[stack_ptr + 2] = x;   stack[stack_ptr + 3] = y;
                        stack[stack_ptr + 4] = z;   stack[stack_ptr + 5] = sel;
                        stack[stack_ptr + 6] = iter; stack[stack_ptr + 7] = 1;
                        stack_ptr += 8;
                        x--;
                        goto tak_function; // x = tak(x - 1, y, z);
                        tak_ret_1:
                        ret_val = z; // z is the returned result from tak
                        stack_ptr -= 7;
                        oldx =  stack[stack_ptr];   oldy = stack[stack_ptr + 1];
                        x = stack[stack_ptr + 2];   y = stack[stack_ptr + 3];
                        z = stack[stack_ptr + 4];   sel = stack[stack_ptr + 5];
                        iter = stack[stack_ptr + 6];
                        x =  (1 - sel) * x + sel * ret_val; // x = (1 - sel) * x + sel * tak_unrolled(x - 1, y, z, iter);

                        // stack, recurse and unstack vars
                        stack[stack_ptr] = oldx;    stack[stack_ptr + 1] = oldy;
                        stack[stack_ptr + 2] = x;   stack[stack_ptr + 3] = y;
                        stack[stack_ptr + 4] = z;   stack[stack_ptr + 5] = sel;
                        stack[stack_ptr + 6] = iter; stack[stack_ptr + 7] = 2;
                        stack_ptr += 8;
                        x = y-1; y = z; z = oldx;
                        goto tak_function; //  y = tak(y - 1, z, oldx);
                        tak_ret_2:
                        ret_val = z; // z is the returned result from tak
                        stack_ptr -= 7;
                        oldx =  stack[stack_ptr];   oldy = stack[stack_ptr + 1];
                        x = stack[stack_ptr + 2];   y = stack[stack_ptr + 3];
                        z = stack[stack_ptr + 4];   sel = stack[stack_ptr + 5];
                        iter = stack[stack_ptr + 6];
                        y = (1 - sel) * y + sel * ret_val; // y = (1 - sel) * y + sel * tak_unrolled(y - 1, z, oldx, iter);

                        sel = gfun(x-y, 1);     // sel = x > y;

                        // stack, recurse and unstack vars
                        stack[stack_ptr] = oldx;    stack[stack_ptr + 1] = oldy;
                        stack[stack_ptr + 2] = x;   stack[stack_ptr + 3] = y;
                        stack[stack_ptr + 4] = z;   stack[stack_ptr + 5] = sel;
                        stack[stack_ptr + 6] = iter; stack[stack_ptr + 7] = 3;
                        stack_ptr += 8;
                        x = z-1; y = oldx; z = oldy;
                        goto tak_function; //  y = tak(y - 1, z, oldx);
                        tak_ret_3:
                        ret_val = z; // z is the returned result from tak
                        stack_ptr -= 7;
                        oldx =  stack[stack_ptr];   oldy = stack[stack_ptr + 1];
                        x = stack[stack_ptr + 2];   y = stack[stack_ptr + 3];
                        z = stack[stack_ptr + 4];   sel = stack[stack_ptr + 5];
                        iter = stack[stack_ptr + 6];
                        z = (1 - sel) * z + sel * ret_val; // z = (1 - sel) * z + sel * tak_unrolled(z - 1, oldx, oldy, iter);
                        goto while_iter;
                    end_while_iter:
                    /* find the "return pointer" */
                    ret_pos = 0;
                    if (stack_ptr != 0) {
                        ret_pos = stack[stack_ptr-1];
                        stack_ptr--;
                    }
                    if (ret_pos == 1) goto tak_ret_1;
                    if (ret_pos == 2) goto tak_ret_2;
                    if (ret_pos == 3) goto tak_ret_3;
                    // printf("%d\n", z);
                    assert(z == tak(i, j, k));
                }
                /* End of Tak function */
                k++;
            } while (k <= MAX_NUM);
            j++;
        } while (j <= MAX_NUM);
        i++;
    } while (i <= MAX_NUM);

    return 0;
}
