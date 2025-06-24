/*
 * Description: Recursive Maze Solver (Rat in a Maze problem).
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

#define N 4

/*
 * Prints the solution matrix.
 */
void printSolution(int sol[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", sol[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * Checks if x, y is a valid move inside maze and not blocked.
 */
int isSafe(int maze[N][N], int x, int y) {
	return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

/*
 * Recursive function to solve the maze problem.
 * Returns 1 if path found, else 0.
 */
int solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]) {
	if (x == N-1 && y == N-1) {
		sol[x][y] = 1;
		return 1;
	}

	if (isSafe(maze, x, y)) {
		sol[x][y] = 1;

		// Move right
		if (solveMazeUtil(maze, x, y + 1, sol))
			return 1;

		// Move down
		if (solveMazeUtil(maze, x + 1, y, sol))
			return 1;

		// Backtrack
		sol[x][y] = 0;
	}
	return 0;
}

/*
 * Solves the maze problem using recursion.
 */
void solveMaze(int maze[N][N]) {
	int sol[N][N] = {0};

	if (solveMazeUtil(maze, 0, 0, sol)) {
		printf("Path found:\n");
		printSolution(sol);
	} else {
		printf("No path found.\n");
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int maze[N][N] = {
		{1, 0, 0, 0},
		{1, 1, 0, 1},
		{0, 1, 0, 0},
		{1, 1, 1, 1}
	};

	solveMaze(maze);

	return 0;
}
