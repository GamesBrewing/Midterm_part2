#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 4

pthread_mutex_t print_lock; // Mutex for safe printing :)

typedef struct {
    int* board;
    int n;
    int col;
    int start_row;
    int end_row;
} ThreadData;

bool isSafe(int board[], int row, int col, int n) {
    for (int i = 0; i < col; i++) {
        if (board[i] == row || abs(board[i] - row) == abs(i - col)) {
            return false;
        }
    }
    return true;
}

void solveNQueensUtil(int board[], int col, int n) {
    if (col >= n) {
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
}

// Complete this function
void* solveNQueensParallel(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int* board = data->board;
    int n = data->n;
    int col = data->col;
    int start_row = data->start_row;
    int end_row = data->end_row;

    // complete this 
}

int main() {
    int n = 7;
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Initialize mutex for thread-safe printing


    // Each thread will have its own board to avoid race conditions
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].board = (int*)malloc(n * sizeof(int));
        if (thread_data[i].board == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        // Initialize board
        for (int j = 0; j < n; j++) {
            thread_data[i].board[j] = -1;
        }
        thread_data[i].n = n;
        thread_data[i].col = 0;
    }

    // Split the first row's work among threads


    // Create threads and distribute rows among them

        // Make sure to handle extra rows for some threads (if n is not divisible by NUM_THREADS)


    // Wait for all threads to complete and free memory for each thread


    // Destroy the mutex after all threads have finished


    return 0;
}
