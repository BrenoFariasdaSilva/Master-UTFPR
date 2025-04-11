/*
 * Descrição: Exercício da plataforma Spoj encontrado em: https://br.spoj.com/problems/OBITETRI/.
 * Autor: Breno Farias da Silva.
 * Data: 04/04/2025.
 *
 * OBITETRI - Tetris
 * A sua turma do colégio resolveu organizar um campeonato de tetris. Após discussão sobre as regras, 
 * ficou definido que cada aluno jogaria um total de 12 partidas. Das 12 pontuações obtidas por um aluno, 
 * a maior e a menor são descartadas, e as demais são somadas, resultando na pontuação final do aluno.
 *
 * Tarefa
 * Como você possui conhecimentos de programação, acabou sendo designado pela turma para escrever um 
 * programa para imprimir a classificação final do campeonato, a partir das pontuações de cada jogador.
 *
 * Entrada
 * A entrada é composta de vários conjuntos de teste. A primeira linha de um conjunto de testes contém 
 * um número inteiro J, que indica o número de jogadores que participaram do campeonato. A seguir, para 
 * cada jogador há duas linhas na entrada: a primeira possui o nome do jogador (formado apenas por letras, 
 * sendo apenas a inicial em maiúscula, e com no máximo 15 letras), e a segunda possui as 12 pontuações que 
 * o jogador obteve, separadas por espaço. As pontuações são inteiros entre 0 e 1000. O final da entrada é 
 * indicado por um conjunto de teste com J = 0.
 *
 * Saída
 * Para cada conjunto de teste, o seu programa deve escrever uma linha contendo o identificador do conjunto 
 * de teste, no formato “Teste n”, onde n é numerado sequencialmente a partir de 1. A seguir, o seu programa 
 * deve escrever a classificação final no campeonato, utilizando uma linha para cada participante. Cada linha 
 * deve conter três informações, separadas por um espaço em branco: a classificação do jogador, a sua pontuação 
 * final, e o seu nome. A classificação de um jogador é igual a 1 mais o número de jogadores que obtiveram 
 * pontuação maior do que a sua. Em caso de empate, os jogadores devem ser ordenados em ordem alfabética. 
 * Depois de toda a classificação, deve ser deixada uma linha em branco. O formato do exemplo de saída abaixo 
 * deve ser seguido rigorosamente.
 *
 * EXEMPLO:
 * Entrada:
 * 4
 * Zezinho
 * 100 123 133 333 400 300 129 200 360 340 200 600
 * Luizinho
 * 60 50 120 250 170 190 190 220 260 270 290 300
 * Carlinhos
 * 10 10 20 10 10 10 10 20 20 20 20 20
 * Joaozinho
 * 200 300 400 400 500 500 500 600 650 650 700 810
 * 3
 * Pedrinho
 * 100 100 200 200 300 300 400 400 500 500 600 600
 * Huguinho
 * 50 100 200 200 300 300 500 500 400 400 600 700
 * Zezinho
 * 100 100 100 100 100 100 100 100 100 100 100 100
 * 0
 *
 * Saída:
 * Teste 1
 * 1 5200 Joaozinho
 * 2 2518 Zezinho
 * 3 2020 Luizinho
 * 4 150 Carlinhos
 *
 * Teste 2
 * 1 3500 Huguinho
 * 1 3500 Pedrinho
 * 3 1000 Zezinho
 *
 * Restrições:
 * 0 <= J <= 1000 (J = 0 apenas para indicar final da entrada)
 * 0 <= pontuação em uma partida <= 1000
 * 1 <= tamanho dos nomes, em número de letras <= 15
 */

// Compile: gcc 02-Spoj-OBITETRI.c -o 02-Spoj-OBITETRI
// Run: ./02-Spoj-OBITETRI < 02-Spoj-OBITETRI.txt

#include <stdio.h> // Printf, scanf
#include <string.h> // Funções para manipulação de strings: strlen, strcpy, strcat, strcmp.
#include <stdlib.h> // Funções para conversão de tipos: atoi, atof, strtol, strtod.

#pragma pack(1) // Alinhamento de 1 byte.

typedef struct {
	char name[16]; // Tamanho do nome ë 15 + caracter de término da string.
	unsigned short int scores[12]; // Limite máximo de pontuações.
	unsigned short int minMaxPlayerScores[2] = {0,0}; // {Index Min, Index Max};
	unsigned short int totalPlayerScore = 0; // Soma da pontuação do player.
} Player;

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(void) {
	unsigned int numPlayers;
	int testNum = 1;
	while (scanf("%u", &numPlayers), numPlayers > 0) { // Enquanto o input não for 0, então continua pegando a pontuação dos jogadores
		for (unsigned int i = 0; i < numPlayers; i++) { // Para cada jogador:
			scanf("%s", name); // Lê o nome
			for (int j = 0; j < 12; j++) { // Lê as 12 pontuações
				scanf("%hu", &scores[j]); // Lê a pontuação atual
				if (scores[j] < minMaxPlayerScores[0] || minMaxPlayerScores[0] == 0) { // Se a pontuação atual for menor que a menor pontuação ou se a menor pontuação for 0
					minMaxPlayerScores[0] = j; // Atualiza o índice da menor pontuação
				} else if (scores[j] > minMaxPlayerScores[1]) { // Se a pontuação atual for maior que a maior pontuação
					minMaxPlayerScores[0] = j; // Atualiza o índice da maior pontuação
				}
				totalPlayerScore += scores[j]; // Soma a pontuação atual ao total
			}
		}

		totalPlayerScore -= (scores[minMaxPlayerScores[0]] + scores[minMaxPlayerScores[1]]); // Remove a menor e a maior pontuação do total
	}

	return 0;
}
