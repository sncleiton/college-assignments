#include "d.h"

/**
 * @detail adaptada de Projeto de Algoritmos - Nívio Ziviane função responsável porrefazer o heap após remoção
 */
void Refaz(int esq, int dir, vetor* a, int** peso)
{
	int i = esq, j,sinal;
			ponto x;
			
	j= i*2; x = a[i].p;
	
	
	while(j<=dir)
	{
		if(j<dir)
		{

			if(peso[a[j].p.x][a[j].p.y]>peso[a[j+1].p.x][a[j+1].p.y])
			{
				j++;
			}
		}
		if(peso[x.x][x.y] <= peso[a[j].p.x][a[j].p.y])
		{
			j = dir+1;

		}else{
			a[i].p = a[j].p;
			i=j; j=i*2;
		}
	}
	a[i].p = x;
}

/**
 * @detail adaptada de Projeto de Algoritmos - Nívio Ziviane função responsável por ordenar o vetor com heapsort
 */
void Constroi(vetor *a, int** peso)
{
	int esq, n = a[0].n;
	esq = n/2 +1;
	while(esq > 1)
	{
		esq--;
		Refaz(esq, n, a, peso);
	}

}

/**
 * @detail adaptada de Projeto de Algoritmos - Nívio Ziviane função responsável por retirar menor elemento do heap
 */
ponto Retira_min(vetor *a, int** peso)
{
	ponto retorno;

	retorno = a[1].p;
	a[1].p = a[a[0].n].p;
	a[0].n--;

	Refaz(1, a[0].n, a, peso);
	
	return retorno;
}
/**
 * @detail adaptada de Projeto de Algoritmos - Nívio Ziviane função responsável por atualizar peso em heap e refazer se necessário
 * precondição novo peso é menor
 */
void Atualiza_peso(int i, int npeso, vetor* a, int** peso, int** indices)
{
	ponto x;
	
	peso[a[i].p.x][a[i].p.y] = npeso;
	while(i>1 && peso[a[i/2].p.x][a[i/2].p.y] > peso[a[i].p.x][a[i].p.y])
	{
		x = a[i/2].p;
		a[i/2].p = a[i].p;
		a[i].p = x;
		indices[x.x][x.y]=i;
		i /= 2;
		indices[a[i].p.x][a[i].p.y] = i;
	}
}



/**
 * @detail: djkstra: adaptado para lidar com coordenadas
 *
 */
int Dijkstra(grafo *g, ponto partida, ponto chegada, int rx, int ry)
{

	int i=1, alt, sinal=0;
	int **pesos, **indices;
	ponto **anterior, aux;
	vetor *adj,*heaqueue,*atadja;
	
	//alocando memória para vetores e matrizes
	adj = malloc(sizeof(int)*5*g->n*g->m);
	atadja = malloc(sizeof(int)*5*g->n*g->m);
	heaqueue = malloc(sizeof(int)*5*g->n*g->m);
	anterior = malloc(sizeof(ponto*)*g->n);
	pesos = malloc(g->n*sizeof(int*));
	indices = malloc(g->n*sizeof(int*));

	for(aux.x=0; aux.x<g->n; aux.x++)
	{
		pesos[aux.x] = malloc(g->m*sizeof(int));
		indices[aux.x] = malloc(g->m*sizeof(int));
		anterior[aux.x] = malloc(g->m*sizeof(ponto));
		///mesmo que eu ande pelo vale das alocações e atribuições
		///simultâneas o segmentation fault não me atinjira 
		for(aux.y=0; aux.y<g->m; aux.y++)
		{
			pesos[aux.x][aux.y] = INF;
			anterior[aux.x][aux.y].x = -1;
			anterior[aux.x][aux.y].y = -1;
			heaqueue[i].p = aux;
			indices[aux.x][aux.y]=i;

			i++;
		}
	}
	heaqueue[0].n = i-1;
	///peso da partida até ele mesmo é zero.
	pesos[partida.x][partida.y]=0;

	///construamos o heap no vetor
	Constroi(heaqueue, pesos);

	///enquanto ainda houverem vértices no heap...
	while(heaqueue[0].n>1)
	{
		///...retira o menor do heap.
		aux = Retira_min(heaqueue, pesos);

		///caso não seja atalho...
		if(g->mapa[aux.x][aux.y]!=0)
		{
			///...encontra adjacentes
			Adjacentes(adj, aux, g, rx, ry);

			///para todos adjacentes, faz.
			for(i = 0; i<adj[0].n; i++)
			{
				///auxiliar alt <-- peso atual mais peso com relação a adjacente
				alt = pesos[aux.x][aux.y]+ adj[i].peso;
				///se alt for menor que o peso atual....
				if(alt < pesos[adj[i].p.x][adj[i].p.y])
				{
					///..alt agora é o novo melhor/menor peso.
					Atualiza_peso(indices[adj[i].p.x][adj[i].p.y], alt, heaqueue, pesos, indices);
					///se alt agora é o melhor e menor peso então ele está no caminho de alguém(vértice) até o inicial
					anterior[adj[i].p.x][adj[i].p.y] = aux;
					///não queremos o caminho a partir de todos os vértices, então se encontrar o caminho para o
					/// ponto de chegada pode parar
					if(aux.x == chegada.x && aux.y == chegada.y)
					{
						///isso vai fazer parar
						heaqueue[0].n = 0;
					}
				}
			}
		}else{
			///se é atalho e sinal=false...
			if(sinal==0)
			{
				//...calcula os adjacentes do atalho.
				Adjacentes(atadja, aux, g, rx, ry);
				///os adjacentes de todos os atalhos são os mesmos
				///só precisa ser calculado uma vez, sinal=true;
				sinal = 1;
			}
			///continua normal, para todos adjacentes, faz.
			for(i = 0; i<atadja[0].n; i++)
			{
				alt = pesos[aux.x][aux.y]+ atadja[i].peso;
		
				if(alt < pesos[atadja[i].p.x][atadja[i].p.y])
				{
					/// atualiza peso.
					Atualiza_peso(indices[atadja[i].p.x][atadja[i].p.y], alt, heaqueue, pesos, indices);

					anterior[atadja[i].p.x][atadja[i].p.y] = aux;
				
					if(aux.x == chegada.x && aux.y == chegada.y)
					{
						heaqueue[0].n = 0;
					}
				}
			}
		}

	}

	///alt útil é auxiliar para retornar a resposta
	alt = pesos[chegada.x][chegada.y];

	///Gratis_Dijkstra libera memória alocada para função dijkstra
	for(i=0; i<g->n; i++)
	{
		free(pesos[i]);
		free(anterior[i]);
		free(indices[i]);

	}
	free(indices);
	free(pesos);
	free(anterior);
	free(heaqueue);
	free(adj);
	free(atadja);

	return alt;
}
