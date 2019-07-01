#ifndef h
#define h


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define INFI 9998


#define PRETO 2
#define BRANCO 1
#define NON 0

int DIR[8] = {-11, -10, -9, -1, 1, 9, 10, 11};


//v[0] = p1; v[1]= p2


//utilidade de um tabuleiro, diferença entre peças do jogador e do adversário
// menos o número de jogadas restantes para o adversário
int utilidade(short* v, short* tabuleiro);

// diferença entre peças do jogador e do adversário
int diferencaPecas(short* v, short* tabuleiro);

//copia um tabuleiro para outro.
void copiaTabuleiro(short* original, short* copia);

//exibe tabuleiro na tela.
void mostraTabuleiro(short* tabuleiro);

//cria tabuleiro com peças iniciais postas.
short* inicializaTabuleiro(short* tabuleiro);

//função usada pela função "movimentoValido" se sinal=1 faz a jogada da 
//variável "jogada". Se sinal=0, somente se jogada capturaria peça adversária.
int trem(int jogada, short* v ,short* tabuleiro, short sinal);

//verifica se movimento é possível e válido, se sim, o faz.
int movimentoValido(int jogada, short* v, short* tabuleiro, short simul);

//verifica se resta alguma jogada válida no tabuleiro para um jogador específico
int restaJogada(short* v, short* tabuleiro);

//armazena jogadas possíveis para jogador específico
int* armazenaJogadasValidas(short* v, short* tabuleiro);

//escolhe jogada da iA de valor máximo para a iA
int maxValueKAI(short* tabuleiro, int profAtual, int profundidade, short* v);

//escolhe jogada do adversário de valor mínimo para a iA
int minValueKAI(short* tabuleiro, int profAtual, int profundidade, short* v);

//AlphaBetha miniMax, "maxValueKAI"
int alphaBeta(short* tabuleiro, int profundidade, short* v);


#endif
