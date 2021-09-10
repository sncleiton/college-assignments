#ifndef G
#define G

#include <stdio.h>
#include <stdlib.h>

#define INF 999999	//definindo infinito

typedef struct
{
	int x;			//coordenadas de um ponto
	int y;

}ponto;

typedef struct
{
	ponto p;
	int peso;		//peso com relação ao adjacente
	int n;			//quantos pontos no vetor;

}vetor;


typedef struct
{
	int m;			//dimensão em y
	int n;			//dimensão em x
	vetor *atalho;	//coordenadas dos atalhos na pista
	//vetor *atadja;	//adjacentes aos atalhos
	int **mapa;		//mapa da pista

}grafo;


/**
 * @brief     Libera memória alocada para matriz 
 *
 * @param[grafo*]  g     matriz a ser liberada
 *
 * @return     void
 */
void Gratis_matriz(grafo *g);


/**
 * @brief      Aloca memória para matriz e lê mapa
 *
 * @param[grafo*] g   matriz que representa o mapa
 * @param[in]  m    dimensão do mapa
 * @param[in]  n     dimensão do mapa
 * @param[FILE*] entrada  arquivo de entrada
 *
 * @return     void
 */
void Faz_matriz(grafo *g, int m, int n,FILE* entrada);

/**
 * @brief      Calcula adjacentes a uma posição no mapa considerando o modelo cinemático do robô
 *
 * @param[vetor*] adj  vetor onde será armazenado os adjacentes
 * @param[ponto]  v    ponto a ser avaliado
 * @param[grafo*] g   matriz que representa o mapa
 * @param[in] rx  restrição cinemática em x
 * @param[in] ry  restrição cinemática em y
 *
 * @return     void
 */
void Adjacentes(vetor *adj, ponto v, grafo *g, int rx, int ry);

/**
 * @brief      teste se necessário utilizar algorítmo de caminho mínimo
 *
 * @param[grafo*] g   matriz que representa o mapa
 * @param[ponto]  part    ponto de partida
 * @param[ponto]  cheg    ponto de chegada
 *
 * @return  -1 se saída inalcansável, -2 se partida é um portal para chegada, -3 se tudo bem
 */
int Test_sanida(grafo *g, ponto part, ponto cheg);



#endif
