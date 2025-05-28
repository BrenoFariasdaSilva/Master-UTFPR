/*
 * Description: Recursively evaluate the value of a mathematical expression represented as a binary tree.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free

/*
 * Definition of the expression tree node.
 * value: if the node is a leaf, it holds a number.
 * op: if the node is an internal node, it holds an operator ('+', '-', '*', '/').
 * left: pointer to the left child node.
 * right: pointer to the right child node.
 */
typedef struct ExprNode {
	char op;
	double value;
	struct ExprNode *left;
	struct ExprNode *right;
} ExprNode;

/*
* Recursively evaluates the expression tree.
* node: pointer to the root node of the expression tree.
* return: the result of evaluating the expression tree.
*/
double evaluate(ExprNode *node) {
	if (!node->left && !node->right) {
		// Leaf node: return the value
		return node->value;
	}

	// Evaluate left and right subtrees recursively
	double left_val = evaluate(node->left);
	double right_val = evaluate(node->right);

	// Apply the operator in the current node
	switch (node->op) {
		case '+': return left_val + right_val;
		case '-': return left_val - right_val;
		case '*': return left_val * right_val;
		case '/': 
			if (right_val == 0) {
				printf("Error: Division by zero!\n");
				exit(EXIT_FAILURE);
			}
			return left_val / right_val;
		default:
			printf("Error: Unknown operator '%c'\n", node->op);
			exit(EXIT_FAILURE);
	}
}

/*
* Utility function to create a leaf node with a value.
*/
ExprNode* create_value_node(double val) {
	ExprNode *node = (ExprNode*) malloc(sizeof(ExprNode));
	node->op = 0;
	node->value = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/*
* Utility function to create an operator node with left and right children.
*/
ExprNode* create_op_node(char op, ExprNode *left, ExprNode *right) {
	ExprNode *node = (ExprNode*) malloc(sizeof(ExprNode));
	node->op = op;
	node->left = left;
	node->right = right;
	return node;
}

/*
* Main function of the program.
* argc: number of arguments passed on program call.
* argv: array with the arguments passed on program call.
* return: program execution status (0: no errors, otherwise: error code).
*/
int main(int argc, char *argv[]) {
	// Example expression: (3 + 5) * (10 - 2)
	ExprNode *left = create_op_node('+', create_value_node(3), create_value_node(5));
	ExprNode *right = create_op_node('-', create_value_node(10), create_value_node(2));
	ExprNode *root = create_op_node('*', left, right);

	double result = evaluate(root);
	printf("Result of the expression: %lf\n", result);

	// Free allocated memory
	free(left->left);
	free(left->right);
	free(left);
	free(right->left);
	free(right->right);
	free(right);
	free(root);

	return 0;
}
