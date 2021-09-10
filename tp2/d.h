#ifndef D
#define D

#include"grafo.h"


/**
 * @brief   algorítmo para caminho mínimo Dijkstra
 *
 * @param[grafo*] g   matriz que representa o mapa
 * @param[ponto]  partida    ponto de partida
 * @param[ponto]  chegada    ponto de chegada
 * @param[in]  rx    limitação cinemática em x
 * @param[in]  ry    limitação cinemática em y
 *
 * @return  peso até chegada
 */
int Dijkstra(grafo *g, ponto partida, ponto chegada, int rx, int ry);


#endif
