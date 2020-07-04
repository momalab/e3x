#include <stdio.h>
#include <assert.h>

#define MAX_NUM 10
#define ITERATIONS MAX_NUM-1

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

#if 0

/*
 * Variable "iter" will not be encrypted
 */
int tak_unrolled(int x, int y, int z, int iter) {
    int sel = gfun(x-y, 1);     // sel = x > y;
    while (iter--) {
        int oldx = (1 - sel) * oldx + sel * x;
        int oldy = (1 - sel) * oldy + sel * y;
        x = (1 - sel) * x + sel * tak_unrolled(x - 1, y, z, iter);
        y = (1 - sel) * y + sel * tak_unrolled(y - 1, z, oldx, iter);
        sel = gfun(x-y, 1);     // sel = x > y;
        z = (1 - sel) * z + sel * tak_unrolled(z - 1, oldx, oldy, iter);
    }
    return z;
}

int main(void) {
    for (int i = 0 ; i <= MAX_NUM ; i++) {
        for (int j = 0 ; j <= MAX_NUM ; j++) {
            for (int k = 0 ; k <= MAX_NUM ; k++) {
                int x = tak(i, j, k);
                printf("%d %d %d : %d\n", i, j, k, x);
                assert(x == tak_unrolled(i, j, k, ITERATIONS));
            }
        }
    }
    return 0;
}

#else

void stackVars(int *stack, int *stack_ptr, int oldx, int oldy, int x, int y, int z, int sel, int iter, int ret_pos) {
    stack[*stack_ptr] = oldx;    
    stack[*stack_ptr + 1] = oldy;
    stack[*stack_ptr + 2] = x;   
    stack[*stack_ptr + 3] = y;
    stack[*stack_ptr + 4] = z;   
    stack[*stack_ptr + 5] = sel;
    stack[*stack_ptr + 6] = iter; 
    stack[*stack_ptr + 7] = ret_pos;
    *stack_ptr += 8;
}

void unstackVars(int *stack, int *stack_ptr, int *oldx, int *oldy, int *x, int *y, int *z, int *sel, int *iter) {
    *stack_ptr -= 7;
    *oldx =  stack[*stack_ptr];
    *oldy = stack[*stack_ptr + 1];
    *x = stack[*stack_ptr + 2];
    *y = stack[*stack_ptr + 3];
    *z = stack[*stack_ptr + 4];
    *sel = stack[*stack_ptr + 5];
    *iter = stack[*stack_ptr + 6];
}

int main(void) {
    int stack[256];
    int stack_ptr = 0;

    for (int i = 0 ; i <= MAX_NUM ; i++) {
        for (int j = 0 ; j <= MAX_NUM ; j++) {
            for (int k = 0 ; k <= MAX_NUM ; k++) {

                /* Tak function */
                int x = i, y = j, z = k, iter = ITERATIONS;
                int sel, ret_val;
                tak_function: {               
                    sel = x > y;
                    while (iter--) {
                        int oldx = (1 - sel) * oldx + sel * x;
                        int oldy = (1 - sel) * oldy + sel * y;

                        // stack, recurse and unstack vars
                        stackVars(stack, &stack_ptr, oldx, oldy, x, y, z, sel, iter, 1);
                        x--;
                        goto tak_function; // x = tak(x - 1, y, z);
                        tak_ret_1:
                        ret_val = z; // z is the returned result from tak
                        unstackVars(stack, &stack_ptr, &oldx, &oldy, &x, &y, &z, &sel, &iter);
                        x =  (1 - sel) * x + sel * ret_val; // x = (1 - sel) * x + sel * tak_unrolled(x - 1, y, z, iter);

                        // stack, recurse and unstack vars
                        stackVars(stack, &stack_ptr, oldx, oldy, x, y, z, sel, iter, 2);
                        x = y-1; y = z; z = oldx;
                        goto tak_function; //  y = tak(y - 1, z, oldx);
                        tak_ret_2:
                        ret_val = z; // z is the returned result from tak
                        unstackVars(stack, &stack_ptr, &oldx, &oldy, &x, &y, &z, &sel, &iter);
                        y = (1 - sel) * y + sel * ret_val; // y = (1 - sel) * y + sel * tak_unrolled(y - 1, z, oldx, iter);

                        // update sel
                        sel = x > y;

                        // stack, recurse and unstack vars
                        stackVars(stack, &stack_ptr, oldx, oldy, x, y, z, sel, iter, 3);
                        x = z-1; y = oldx; z = oldy;
                        goto tak_function; //  y = tak(y - 1, z, oldx);
                        tak_ret_3:
                        ret_val = z; // z is the returned result from tak
                        unstackVars(stack, &stack_ptr, &oldx, &oldy, &x, &y, &z, &sel, &iter);
                        z = (1 - sel) * z + sel * ret_val; // z = (1 - sel) * z + sel * tak_unrolled(z - 1, oldx, oldy, iter);
                    }
                    /* find the "return pointer" */
                    int ret_pos = 0;
                    if (stack_ptr == 0) goto ret_pos_zero;
                        stack_ptr--;
                        ret_pos = stack[stack_ptr];
                    ret_pos_zero:
                    if (ret_pos == 1) goto tak_ret_1;
                    if (ret_pos == 2) goto tak_ret_2;
                    if (ret_pos == 3) goto tak_ret_3;
                    // printf("%d ", z);
                    assert(z == tak(i, j, k));
                }
                /* End of Tak function */

            }
        }
    }

    return 0;
}

#endif
