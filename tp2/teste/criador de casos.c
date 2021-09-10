#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>     /* assert */



/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    // Chop off all of the values that would cause skew...
    long end = RAND_MAX / n; // truncate skew
    assert (end > 0L);
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}


void main()
{
	int n,m,atalhos,bloqueios,
		**mapa;
	int i,j;
	
	FILE* saida;
	
	saida = fopen("SAIDaCHOU.txt","w");
	scanf("%i %i %i %i",&n,&m,&atalhos,&bloqueios);
	
	srand((unsigned int)time(NULL));
	mapa = malloc(n*sizeof(int*));
	for(i=0; i<m; i++)
	{
		mapa[i] = malloc(m*sizeof(int));
		for(j=0; j<m; j++)
		{

			mapa[i][j] = randint(600)+1;
		}
	}
	
	srand((unsigned int)time(NULL)+i);
	for(i=0;i<atalhos;i++)
	{
		mapa[randint(n)][randint(m)]=-1;
	}
	

	for(j=0;j<bloqueios;j++)
	{
		srand((unsigned int)time(NULL)+j);
		mapa[rand()%n][rand()%m]=0;
	}
	
	if(m<10&&n<11)
	{
		for(i=0; i<n; i++)
		{
			for(j=0;j<m;j++)
			{
				printf(" %i ",mapa[i][j]);
			}
			printf("\n");
		}
	}
	
	fprintf(saida,"%i %i\n",n,m);
	for(i=0; i<n; i++)
	{
		for(j=0;j<m;j++)
		{
			fprintf(saida,"%i ",mapa[i][j]);
		}
		fprintf(saida, "\n");
	}
	
	
}
