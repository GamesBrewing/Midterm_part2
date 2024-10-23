#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

#define NUM_THREADS 4


// Check if it is safe to place the queen
bool isSafe(int board[], int row, int col, int n) {
    for (int i = 0; i < col; i++) {
        if (board[i] == row || abs(board[i] - row) == abs(i - col)) {
            return false;
        }
    }
    return true;
}

//print the placed queen
void solveNQueensUtil(int board[], int col, int n) {
    if (col >= n) {
        #pragma omp critical
        for (int i = 0; i < n; i++) {
            printf("%d ", board[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[col] = i;
            solveNQueensUtil(board, col + 1, n);
            board[col] = -1; // backtrack
        }
    }
    return;
}

//Handle multiple rows in parallel
void* solveNQueensParallel(int n, int start_row, int end_row) {
    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = start_row; i <= end_row; i++) {
        int *board = (int *)malloc(n * sizeof(int));
        if (board == NULL) {
            fprintf (stderr, "Memory allocation failed.\n");
            
        }
        
        // Initialize board
        for (int j  = 0; j < n; j++){ 
            board[j] = -1;
        }
        if (isSafe(board, i, 0, n)){
            board[0] = i;
            solveNQueensUtil(board, 1, n);
            
        }
        free(board);
    }
    return 0;
}

int main() {
    int n = 15;
    
    // Calculate rows/thread
    int rows_per_thread = n / NUM_THREADS;
    int extra_rows = n % NUM_THREADS;

    // Each thread will have its own board to avoid race conditions
    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < NUM_THREADS; i++) {
        int start_row = i * rows_per_thread;
        int end_row = (i + 1) * rows_per_thread - 1;
         
         // Add extra rows to the last thread
        if (i == NUM_THREADS - 1) {
            end_row += extra_rows;
        }
        solveNQueensParallel( n, start_row, end_row);
        

    }

    return 0;
}
