#include "d.h"
#include <time.h>

int Termina(int retorno, grafo *g, FILE* entrada)
{
	if(retorno==(-3))
	{
		return 0;
	}else if(retorno == -2)
	{
		printf("%i\n",(0));

	}else if(retorno < INF|| retorno==(-1))
	{
		printf("%i\n",retorno);
	}else{
		printf("%i\n",(-1));
	}

	return 1;
}







void main(int argc, char* argv[])
{
	grafo g;
	int m,n,retorno=0;
	FILE *entrada;

	entrada = fopen(argv[1],"r");
	
	fscanf(entrada,"%i %i\n",&m,&n);

	Faz_matriz(&g,m,n,entrada);
	
	
	

	ponto part, cheg;
	part.x=atoi(argv[3]);cheg.x=atoi(argv[5]);
	part.y=atoi(argv[2]);cheg.y=atoi(argv[4]);


	if(Termina(Test_sanida(&g,part,cheg), &g, entrada))
	{
		return;
	}

	clock_t start, end;
 	double cpu_time_used;
	start = clock();


	Termina(Dijkstra(&g, part, cheg, atoi(argv[7]), atoi(argv[6])), &g, entrada);

	end = clock();
 	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n\t%f\n",cpu_time_used);

	Gratis_matriz(&g);
	fclose(entrada);
	
	return;
/*
	vetor v[5];
	int **p,i;
	
	p = malloc(4*sizeof(int*));
	for(i = 0; i<4; i++)
	{
		p[i] = malloc(4*sizeof(int));
	}
	
	v[0].n = 4;

	v[1].p.x=0;	v[2].p.x=0;	v[3].p.x=1;	v[4].p.x=1;
	v[1].p.y=0;	v[2].p.y=1;	v[3].p.y=0;	v[4].p.y=1;
	p[0][0]=10;	p[0][1]=5;	p[1][0]=8;	p[1][1] =1;
	
	Constroi(v,p);
	
	for(i=1;i<5;i++)
	{
		printf("%i\t",p[v[i].p.x][v[i].p.y]);
	}
	
	Atualiza_peso(4, 100, v, p);
	
	v[0].p = Retira_min(v,p);
	printf("\n");

	for(i=1;i<5;i++)
	{
		printf("%i\t",p[v[i].p.x][v[i].p.y]);
	}
	
	//printf("\n%i\t",p[v[0].p.x][v[0].p.x]);
*/
}




















