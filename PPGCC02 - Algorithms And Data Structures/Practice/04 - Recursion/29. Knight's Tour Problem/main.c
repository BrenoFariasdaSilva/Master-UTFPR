/*
 * Description: Knight's Tour Problem using recursion and backtracking.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

#define N 8

/*
 * Prints the chessboard with the knight's move sequence.
 */
void printBoard(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%2d ", board[i][j]);
		}
		printf("\n");
	}
}

/*
 * Checks if (x, y) is a valid move inside the chessboard and not visited.
 */
int isSafe(int x, int y, int board[N][N]) {
	return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

/*
 * Recursive function to perform the Knight's Tour using backtracking.
 * movei: current move number.
 * x, y: current knight's position.
 * board: chessboard with move numbers.
 * xMove, yMove: arrays with possible knight moves.
 * Returns 1 if a solution is found, 0 otherwise.
 */
int solveKTUtil(int x, int y, int movei, int board[N][N], int xMove[], int yMove[]) {
	if (movei == N * N) return 1;

	for (int k = 0; k < 8; k++) {
		int next_x = x + xMove[k];
		int next_y = y + yMove[k];
		if (isSafe(next_x, next_y, board)) {
			board[next_x][next_y] = movei;
			if (solveKTUtil(next_x, next_y, movei + 1, board, xMove, yMove)) return 1;
			board[next_x][next_y] = -1; // Backtracking
		}
	}
	return 0;
}

/*
 * Solves the Knight's Tour problem and prints the solution.
 */
void solveKnightTour() {
	int board[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			board[i][j] = -1;

	// Possible moves for a knight
	int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

	board[0][0] = 0; // Start from first cell

	if (solveKTUtil(0, 0, 1, board, xMove, yMove)) {
		printf("Knight's Tour solution:\n");
		printBoard(board);
	} else {
		printf("No solution exists.\n");
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	solveKnightTour();
	return 0;
}
