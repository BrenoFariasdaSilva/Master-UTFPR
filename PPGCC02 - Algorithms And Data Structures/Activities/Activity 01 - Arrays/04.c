#include <stdio.h>
#include <ctype.h>

#define SIZE 8

/**
 * Retorna se a coordenada está dentro do tabuleiro.
 */
int isInside(int row, int col) {
	return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

/**
 * Verifica se o destino é válido (vazio ou contém inimigo).
 */
int isValidTarget(char board[SIZE][SIZE], int r, int c, char piece) {
	if (!isInside(r, c)) return 0;
	if (board[r][c] == '.') return 1;
	return isupper(piece) != isupper(board[r][c]);
}

/**
 * Imprime o tabuleiro formatado.
 */
void printBoard(char board[SIZE][SIZE]) {
	printf("  A B C D E F G H\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", 8 - i);
		for (int j = 0; j < SIZE; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

/**
 * Funções de movimentação por peça
 */
void showPeao(char board[SIZE][SIZE], int r, int c, char piece) {
	int dir = isupper(piece) ? -1 : 1;
	int startRow = isupper(piece) ? 6 : 1;

	if (isInside(r + dir, c) && board[r + dir][c] == '.')
		printf("Peão %c (%d,%d) -> (%d,%d)\n", piece, r, c, r + dir, c);

	if (r == startRow && board[r + dir][c] == '.' && board[r + 2*dir][c] == '.')
		printf("Peão %c (%d,%d) -> (%d,%d)\n", piece, r, c, r + 2*dir, c);

	for (int dc = -1; dc <= 1; dc += 2) {
		int nr = r + dir, nc = c + dc;
		if (isInside(nr, nc) && board[nr][nc] != '.' && isupper(piece) != isupper(board[nr][nc]))
			printf("Peão %c captura (%d,%d) -> (%d,%d)\n", piece, r, c, nr, nc);
	}
}

void showCavalo(char board[SIZE][SIZE], int r, int c, char piece) {
	int moves[8][2] = {
		{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
		{1, -2}, {1, 2}, {2, -1}, {2, 1}
	};
	for (int i = 0; i < 8; i++) {
		int nr = r + moves[i][0], nc = c + moves[i][1];
		if (isValidTarget(board, nr, nc, piece))
			printf("Cavalo %c (%d,%d) -> (%d,%d)\n", piece, r, c, nr, nc);
	}
}

void showRei(char board[SIZE][SIZE], int r, int c, char piece) {
	for (int dr = -1; dr <= 1; dr++) {
		for (int dc = -1; dc <= 1; dc++) {
			if (dr == 0 && dc == 0) continue;
			int nr = r + dr, nc = c + dc;
			if (isValidTarget(board, nr, nc, piece))
				printf("Rei %c (%d,%d) -> (%d,%d)\n", piece, r, c, nr, nc);
		}
	}
}

void showDesloca(char board[SIZE][SIZE], int r, int c, char piece, int dirs[8][2], int dirCount, int limitada) {
	for (int i = 0; i < dirCount; i++) {
		int dr = dirs[i][0], dc = dirs[i][1];
		int steps = 1;
		while (1) {
			int nr = r + dr*steps, nc = c + dc*steps;
			if (!isInside(nr, nc)) break;
			if (board[nr][nc] == '.') {
				printf("%c (%d,%d) -> (%d,%d)\n", piece, r, c, nr, nc);
			} else {
				if (isupper(piece) != isupper(board[nr][nc]))
					printf("%c captura (%d,%d) -> (%d,%d)\n", piece, r, c, nr, nc);
				break;
			}
			if (limitada) break;
			steps++;
		}
	}
}

void showTorre(char board[SIZE][SIZE], int r, int c, char piece) {
	int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
	showDesloca(board, r, c, piece, dirs, 4, 0);
}

void showBispo(char board[SIZE][SIZE], int r, int c, char piece) {
	int dirs[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
	showDesloca(board, r, c, piece, dirs, 4, 0);
}

void showDama(char board[SIZE][SIZE], int r, int c, char piece) {
	int dirs[8][2] = {
		{-1,0},{1,0},{0,-1},{0,1},
		{-1,-1},{-1,1},{1,-1},{1,1}
	};
	showDesloca(board, r, c, piece, dirs, 8, 0);
}

/**
 * Mapeia a peça e chama função correspondente.
 */
void showMoves(char board[SIZE][SIZE], int r, int c, char piece) {
	switch (toupper(piece)) {
		case 'P': showPeao(board, r, c, piece); break;
		case 'T': showTorre(board, r, c, piece); break;
		case 'C': showCavalo(board, r, c, piece); break;
		case 'B': showBispo(board, r, c, piece); break;
		case 'D': showDama(board, r, c, piece); break;
		case 'R': showRei(board, r, c, piece); break;
	}
}

/**
 * Função principal
 */
int main() {
	char board[SIZE][SIZE];

	printf("Digite o tabuleiro (8 linhas com 8 caracteres):\n");
	printf("Use '.' para casas vazias. Use letras em português (P,T,C,B,D,R).\n");
	printf("Maiúsculas para brancas, minúsculas para pretas.\n");

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			scanf(" %c", &board[i][j]);

	printBoard(board);

	printf("\nJogadas possíveis:\n");
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != '.')
				showMoves(board, i, j, board[i][j]);
		}

	return 0;
}
