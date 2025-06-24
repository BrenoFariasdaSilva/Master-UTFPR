/*
 * Description: Generates all subsets (power set) of a given set using recursion.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursively generates and prints all subsets of the set.
 * set: array representing the input set.
 * subset: array representing the current subset.
 * n: total number of elements in the set.
 * index: current index in the input set.
 * subsetSize: current size of the subset being built.
 */
void generateSubsets(int set[], int subset[], int n, int index, int subsetSize) {
	if (index == n) {
		printf("{ ");
		for (int i = 0; i < subsetSize; i++) {
			printf("%d ", subset[i]);
		}
		printf("}\n");
		return;
	}

	// Include the current element
	subset[subsetSize] = set[index];
	generateSubsets(set, subset, n, index + 1, subsetSize + 1);

	// Exclude the current element
	generateSubsets(set, subset, n, index + 1, subsetSize);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter the number of elements in the set: ");
	scanf("%d", &n);

	int set[n];
	int subset[n];

	printf("Enter %d elements:\n", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &set[i]);
	}

	printf("\nSubsets:\n");
	generateSubsets(set, subset, n, 0, 0);

	return 0;
}
