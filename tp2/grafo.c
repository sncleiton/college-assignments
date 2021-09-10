#include "grafo.h"

/**
 * @detail Através de um 'for' libera memória alocada para o mapa
 */
void Gratis_matriz(grafo *g)
{
	int i;

		///libera toda memória alocada para a matriz
	free(g->atalho);
	for(i=0; i<g->n; i++)
	{
		///liberando...
		free(g->mapa[i]);
	}
	free(g->mapa);
		///...liberada
}

/**
 * @detail aloca memória e lê dados do mapa
 */
void Faz_matriz(grafo *g, int m, int n, FILE* entrada)
{
	int i=0,j,k=0;
	int aux;

	//alocar memória para matriz
	g->atalho = malloc((n*m+2)*sizeof(vetor));
	g->atalho[0].n= 0;


	g->mapa = malloc((n+1)*sizeof(int*));

	for(i=0;i<n;i++)
	{
		g->mapa[i] = malloc((m+1)*sizeof(int));
		for(j=0; j<m; j++)
		{
				fscanf(entrada,"%i",&aux);
				
				if(aux==0)
				{
					//céulas com zero tem peso infinito
					g->mapa[i][j]=INF;
				}else if(aux == -1)
				{
					//atalho, salva posição em vetor de atalhos e aumenta número de atalhos
					g->mapa[i][j] = 0;
					g->atalho[k].p.x = i;
					g->atalho[k].p.y = j;
					k++;
					
				}else{
					g->mapa[i][j] = aux;
				}
		}
	}

	g->atalho[0].n= k;	
	g->m = m;
	g->n = n;
}


/**
 * @detail Esse algoritmo complicado funciona assim:
 *
 * 1. caso a restrição cinemática seja [0,0] seleciona as
 * celulas do mapa acima a baixo a esquerda e a direita,em
 * outros casos a posição atual é somada a restrição e caso seja
 * uma posição válida é adicionada como adjacente;
 *
 * 2. verifica os dos caminhos possíveis para que o robô alcanse 
 * a adjacente, e salva o menor como peso para uso do dijkstra;
 *
 * 3. todas adjacentes e pesos das adjacentes são salvas no
 * vetor 'adj'.
 *
 */
void Adjacentes(vetor *adj, ponto v, grafo *g, int rx, int ry)
{
	int i=0,j,k, aux=0, vezes=1,sinal=0, prox=0;

	if(g->mapa[v.x][v.y]==0)
	{
		//caso ponto v seja um atalho terão que ser calculados adjacentes de todos atalhos
		//sinal indica nos próximos processos se é célula atalho ou não
		sinal = 1;
		vezes = g->atalho[0].n;
	}

	//quando não há resrtições o cálculo de adjacente é um pouco diferente
	if(rx==0&&ry==0)
	{
		//vezes normalmente será 1
		while(vezes)
		{
			if(sinal)
			{
				v.x = g->atalho[prox].p.x;
				v.y = g->atalho[prox].p.y;
			}
			//verifica se condidado a adjacente é uma posição válida se sim...
			if(g->n > v.x+1)
			{
				if((!sinal||g->mapa[v.x+1][v.y]))
				{
					//...é adicionado na lista de adjacentes...
					adj[i].peso = 0;
					adj[i].p.x= v.x+1;
					adj[i].p.y= v.y;
					//...e seu peso é calculado.
					adj[i].peso += g->mapa[v.x][v.y] + g->mapa[v.x+1][v.y];

					i++;
				}
			}

			//verifica se condidado a adjacente é uma posição válida caso sim...
			if(v.x-1 >= 0)
			{
				if((!sinal||g->mapa[v.x-1][v.y]))
				{
					adj[i].peso = 0;
					adj[i].p.x= v.x-1;
					adj[i].p.y= v.y;

					adj[i].peso += g->mapa[v.x][v.y] + g->mapa[v.x-1][v.y];

					i++;
				}
			}

			//verifica se condidado a adjacente é uma posição válida caso sim...
			if(g->m > v.y+1)
			{
				if((!sinal||g->mapa[v.x][v.y+1]))
				{
					adj[i].peso = 0;
					adj[i].p.x= v.x;
					adj[i].p.y= v.y+1;

					adj[i].peso += g->mapa[v.x][v.y] + g->mapa[v.x][v.y+1];

					i++;
				}
			}

			//verifica se condidado a adjacente é uma posição válida caso sim...
			if(v.y-1 >= 0)
			{
				if((!sinal||g->mapa[v.x][v.y-1]))
				{
					adj[i].peso = 0;
					adj[i].p.x= v.x;
					adj[i].p.y= v.y-1;


					adj[i].peso += g->mapa[v.x][v.y] + g->mapa[v.x][v.y-1];

					i++;
				
				}
			}

			prox++;
			vezes--;
		}
	}

	while(vezes)
	{
		if(sinal)
		{
			v.x = g->atalho[prox].p.x;
			v.y = g->atalho[prox].p.y;
		}
			//verifica se condidado a adjacente é uma posição válida caso sim...
		if(g->n>v.x+rx && v.x+rx>=0 && g->m>v.y+ry&& v.y+ry>=0)
		{
			if((!sinal||g->mapa[v.x+rx][v.y+ry]))
			{
				//...é adicionado na lista de adjacentes...
				adj[i].peso = 0;
				adj[i].p.x= v.x+rx;
				adj[i].p.y= v.y+ry;
				
				//...e seu peso é calculado.
				for(j=1; j<=rx; j++)
				{
					aux+= g->mapa[v.x+j-1][v.y] + g->mapa[v.x+j][v.y];
				}
				j--;
				for(k=1; k<=ry; k++)
				{
					aux+= g->mapa[v.x+j][v.y+k-1] + g->mapa[v.x+j][v.y+k];

				}
				//dois caminhos diferentes são possíveis até o nó adjacente....
				k=j=0;
		
				for(k=1; k<=ry; k++)
				{
					adj[i].peso += g->mapa[v.x][v.y+k-1] + g->mapa[v.x][v.y+k];
				}

				///...os dois camiinhos são calculados....
				k--;
				for(j=1; j<=rx; j++)
				{
					adj[i].peso += g->mapa[v.x+j-1][v.y+k] + g->mapa[v.x+j][v.y+k];
				}

				///...e o menor é salvo como peso do adjacente.
				if(aux<adj[i].peso)
				{
					adj[i].peso = aux;
				}
					
				k=j=aux=0;
				i++;
			}
		}

		//verifica se condidado a adjacente é uma posição válida.
		if(g->n>v.x-rx && v.x-rx>=0 && g->m>v.y+ry && v.y+ry>=0)
		{
			if((!sinal||g->mapa[v.x-rx][v.y+ry]))
			{
				adj[i].peso = 0;
				adj[i].p.x= v.x-rx;
				adj[i].p.y= v.y+ry;
				
				for(j=1; j<=rx; j++)
				{
					aux+= g->mapa[v.x-j+1][v.y] + g->mapa[v.x-j][v.y];
				}
				j--;
				for(k=1; k<=ry; k++)
				{
					aux+= g->mapa[v.x-j][v.y+k-1] + g->mapa[v.x-j][v.y+k];
				}
				
				k=j=0;
				
				
				for(k=1; k<=ry; k++)
				{
					adj[i].peso += g->mapa[v.x][v.y+k-1] + g->mapa[v.x][v.y+k];
				}
					k--;
				for(j=1; j<=rx; j++)
				{
					adj[i].peso += g->mapa[v.x-j+1][v.y+k] + g->mapa[v.x-j][v.y+k];
				}
				
				if(aux<adj[i].peso)
				{
					adj[i].peso = aux;
				}
				i++;
			}
		}
		
		//verifica se condidado a adjacente é uma posição válida.
		if(g->n>v.x+rx && v.x+rx>=0 && g->m>v.y-ry && v.y-ry>=0)
		{
			if((!sinal||g->mapa[v.x+rx][v.y-ry]))
			{
				adj[i].peso = 0;
				adj[i].p.x= v.x+rx;
				adj[i].p.y= v.y-ry;
				
				for(j=1; j<=rx; j++)
				{
					aux+= g->mapa[v.x+j-1][v.y] + g->mapa[v.x+j][v.y];
				}
					j--;
				for(k=1; k<=ry; k++)
				{
					aux+= g->mapa[v.x+j][v.y-k+1] + g->mapa[v.x+j][v.y-k];
				}
				
				k=j=0;
				
				
				for(k=1; k<=ry; k++)
				{
					adj[i].peso += g->mapa[v.x][v.y-k+1] + g->mapa[v.x][v.y-k];
				}
				k--;
				for(j=1; j<=rx; j++)//maybe <=
				{
					adj[i].peso += g->mapa[v.x+j-1][v.y-k] + g->mapa[v.x+j][v.y-k];
				}
			
				if(aux<adj[i].peso)
				{
					adj[i].peso = aux;
				}
			
				k=j=aux=0;
				i++;
			}
		}
		
		//verifica se condidado a adjacente é uma posição válida.
		if(g->n>v.x-rx && v.x-rx>=0 && g->m>v.y-ry && v.y-ry>=0)
		{
			if((!sinal||g->mapa[v.x-rx][v.y-ry]))
			{
				adj[i].peso = 0;
				adj[i].p.x= v.x-rx;
				adj[i].p.y= v.y-ry;
				
				for(j=1; j<=rx; j++)
				{
					aux+= g->mapa[v.x-j+1][v.y] + g->mapa[v.x-j][v.y];
				}
				j--;
				for(k=1; k<=ry; k++)
				{
					aux+= g->mapa[v.x-j][v.y-k+1] + g->mapa[v.x-j][v.y-k];
				}
				
				k=j=0;
				
				
				for(k=1; k<=ry; k++)
				{
					adj[i].peso += g->mapa[v.x][v.y-k+1] + g->mapa[v.x][v.y-k];
				}
				k--;
				for(j=1; j<=rx; j++)
				{
					adj[i].peso += g->mapa[v.x-j+1][v.y-k] + g->mapa[v.x-j][v.y-k];
				}
				
				if(aux<adj[i].peso)
				{
					adj[i].peso = aux;
				}
				
				k=j=aux=0;
				i++;
			}
		}
			vezes--;
			prox++;
	}

	//numero de adjacentes entre 1 e 4 no caso de não atalho
	adj[0].n=i;

}
	
/**
 * @detail testes antes de executar algoritmo de menor caminho:
 */
int Test_sanida(grafo *g, ponto part, ponto cheg)
{
	//se chegada igual partida
	if((g->mapa[part.x][part.y]==0 && g->mapa[cheg.x][cheg.y]==0)||(part.x==cheg.x && part.y==cheg.y))
	{
		return -2;
	}else if(g->mapa[cheg.x][cheg.y]==INF||g->mapa[part.x][part.y]==INF)
	{
		//se chegada inalcansável
		return -1;
	}
	
	//tudo certo
	return -3;
}
	
	

















