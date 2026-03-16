/*
 * Description: Solves the N-Queens problem using recursion and backtracking.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdbool.h> // bool, true, false

#define MAX 10 // Maximum board size supported

/*
 * Prints the board configuration.
 * board: array where index represents row and value represents column of queen.
 * n: size of the board (n x n).
 */
void printBoard(int board[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i] == j) {
				printf("Q ");
			} else {
				printf(". ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * Checks if a queen can be placed at row without attacking others.
 * board: current board configuration.
 * row: current row to check.
 * col: column to check.
 * return: true if safe, false otherwise.
 */
bool isSafe(int board[], int row, int col) {
	for (int i = 0; i < row; i++) {
		// Check same column or diagonals
		if (board[i] == col || 
		    board[i] - i == col - row || 
		    board[i] + i == col + row) {
			return false;
		}
	}
	return true;
}

/*
 * Recursively solves the N-Queens problem.
 * board: current board configuration.
 * row: current row to place a queen.
 * n: size of the board (n x n).
 * return: number of valid solutions found.
 */
int solveNQueens(int board[], int row, int n) {
	if (row == n) {
		printBoard(board, n);
		return 1;
	}

	int count = 0;
	for (int col = 0; col < n; col++) {
		if (isSafe(board, row, col)) {
			board[row] = col;
			count += solveNQueens(board, row + 1, n);
		}
	}

	return count;
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter the number of queens (N <= %d): ", MAX);
	scanf("%d", &n);

	if (n <= 0 || n > MAX) {
		printf("Invalid board size.\n");
		return 1;
	}

	int board[MAX]; // board[i] represents the column of queen in row i

	printf("\nSolutions:\n\n");
	int solutions = solveNQueens(board, 0, n);

	printf("Total solutions: %d\n", solutions);

	return 0;
}
