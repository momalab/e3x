#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#define ROWS 7
#define COLS ROWS

int gl_sol_cnt = 0;

int gfun(int x, int y) {
    return (x <= 0) ? 0 : y;
}

int colsSafe(int **board, int rows, int cols) {
    int isSafe = 1;
    for (int j = 0 ; j < cols ; j++) {
        int colsum = 0;
        for (int i = 0 ; i < rows ; i++) {
            colsum += board[i][j];
        }
        isSafe = isSafe * colsum;
    }
    return isSafe > 0 ? 1 : 0;
}

int diagsSafe(int **board, int size) {
    int safe = 1;
    for (int k = 0 ; k < size * 2 ; k++) {
        int p_sum = 0; // primary diagonals sum
        int s_sum = 0; // secondary diagonals sum
        for (int j = 0 ; j <= k ; j++) {
            int i = k - j;
            int jj = size-1 - j; // secondary
            if (i < size && j < size) {
                p_sum += board[i][j];
                s_sum += board[i][jj];
            }
        }
        if (p_sum > 1 || s_sum > 1) return 0;
    }
    return safe;
}

int boardSafe(int **board, int rows, int cols) {
    return colsSafe(board, rows, cols) && diagsSafe(board, rows);
}

void encodeSol(uint64_t **all_sols, int **solution, int size, int sol_num) {
    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {
            all_sols[i][j] += (((uint64_t)1) << sol_num) * solution[i][j];
        }
    }
}

void decodeSols(uint64_t **all_sols, int size, int sol_num) {
    for (int sol = 1 ; sol <= sol_num ; sol++) {
        for (int i = 0 ; i < size ; i++) {
            for (int j = 0 ; j < size ; j++) {
                if (all_sols[i][j] & (((uint64_t)1) << sol)) printf("Q ");
                else printf("_ ");
            }
            printf("\n");
        }
        printf("\n");
    }
}

void permuteRows(uint64_t **all_sols, int **array, int depth) {
    if (depth == ROWS) {
        if (boardSafe(array, ROWS, COLS)) { // a solution found
            gl_sol_cnt++;
            encodeSol(all_sols, array, ROWS, gl_sol_cnt);
        }
        return;
    }
    for (int i = 0; i < COLS; i++) {
        permuteRows(all_sols, array, depth+1);
        array[depth][i] = 0;
        array[depth][(i+1) % COLS] = 1;
    }
}

int main(void) {
    int **array = malloc(ROWS * sizeof(int *));
    uint64_t **all_sols = malloc(ROWS * sizeof(uint64_t *));
    for (int i = 0 ; i < ROWS ; i++) {
        array[i] = calloc(COLS, sizeof(int));
        all_sols[i] = calloc(COLS, sizeof(uint64_t));
        for (int j = 0 ; j < COLS ; j++) {
            array[i][j] = j == 0;
        }
    }
    
    permuteRows(all_sols, array, 0);
    
    decodeSols(all_sols, ROWS, gl_sol_cnt);
    printf("%d-Queens have %d solutions\n", ROWS, gl_sol_cnt);

    return 0;
}

