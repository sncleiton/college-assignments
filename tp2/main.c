#include "d.h"


int Termina(int retorno, grafo *g, FILE* entrada)
{
	if(retorno==(-3))
	{
		///se aqui então, continua normalmente
		return 0;
	}else if(retorno == -2)
	{
		//resposta 0
		printf("%i\n",(0));

	}else if(retorno < INF|| retorno==(-1))
	{
		printf("%i\n",retorno);
	}else{
		printf("%i\n",(-1));
	}

	///Gratis_matriz libera toda memória alocada para o mapa/matriz
	Gratis_matriz(g);
	fclose(entrada);

	///se aqui, é hora de terminar o programa.
	return 1;
}


void main(int argc, char* argv[])
{

	grafo g;
	int m,n,retorno=0;
	FILE *entrada;

	///leremos o mapa
	entrada = fopen(argv[1],"r");
	
	fscanf(entrada,"%i %i\n",&m,&n);

	///aloca memoria para matriz-mapa
	Faz_matriz(&g,m,n,entrada);

	///na matriz o eixo Y cresce para baixo, sendo assim alguns
	/// ajustes são feitos
	ponto part, cheg;
	part.x=atoi(argv[3]);cheg.x=atoi(argv[5]);
	part.y=atoi(argv[2]);cheg.y=atoi(argv[4]);


	if(Termina(Test_sanida(&g,part,cheg), &g, entrada))
	{
		///se termina retorna 1 hora de terminar programa
		return;
	}

	///caso passou por test_sanida executar dijkstra
	Termina(Dijkstra(&g, part, cheg, atoi(argv[7]), atoi(argv[6])), &g, entrada);

	return;

}




















