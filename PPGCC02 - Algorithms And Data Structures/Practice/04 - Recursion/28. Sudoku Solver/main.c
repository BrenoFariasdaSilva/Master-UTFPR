/*
 * Description: Recursive Sudoku Solver using backtracking.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

#define N 9

/*
 * Prints the Sudoku board.
 */
void printBoard(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
}

/*
 * Checks if placing num at board[row][col] is valid.
 */
int isSafe(int board[N][N], int row, int col, int num) {
	// Check row
	for (int x = 0; x < N; x++) {
		if (board[row][x] == num) return 0;
	}

	// Check column
	for (int x = 0; x < N; x++) {
		if (board[x][col] == num) return 0;
	}

	// Check 3x3 subgrid
	int startRow = row - row % 3;
	int startCol = col - col % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[startRow + i][startCol + j] == num) return 0;
		}
	}

	return 1;
}

/*
 * Recursive function to solve Sudoku board using backtracking.
 * Returns 1 if solved, 0 otherwise.
 */
int solveSudoku(int board[N][N], int row, int col) {
	if (row == N - 1 && col == N) {
		return 1; // Reached end successfully
	}

	if (col == N) {
		row++;
		col = 0;
	}

	if (board[row][col] != 0) {
		return solveSudoku(board, row, col + 1);
	}

	for (int num = 1; num <= 9; num++) {
		if (isSafe(board, row, col, num)) {
			board[row][col] = num;
			if (solveSudoku(board, row, col + 1)) return 1;
		}
		board[row][col] = 0; // Backtrack
	}

	return 0; // Trigger backtracking
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int board[N][N] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

	if (solveSudoku(board, 0, 0)) {
		printf("Sudoku solved:\n");
		printBoard(board);
	} else {
		printf("No solution exists.\n");
	}

	return 0;
}
