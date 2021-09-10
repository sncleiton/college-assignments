#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/**
 * @brief   função recursiva para cálculo de custo mínimo
 *
 * @param[short] signal   indica se será colocado no index 0 ou 1
 * @param[char*]  best    vetor que indica em que espaços colocar quebra
 * @param[int]  index    em que indice será colocado 0 ou 1 nessa iteração
 * @param[char*]  str    vetor onde é armazenado o texto a ser avaliado
 * @param[int*]  L    max numéro de chars em uma linha
 * @param[int*]  H    max numéro de linhas em uma página
 * @param[int*]  x    parâmetro para c´alculo de custo da iteração
 * @param[int*]  k    parâmetro para c´alculo de custo da iteração
 * @param[int*]  minimum    custo mínimo calculado até o momento
 * @param[char*]  where    posições a se colocar quebra para mínimo custo
 * @param[int]  n_spaces    número de espaços no texto
 *
 * @return  void, where e minimum contém a solução
 */
void Brute_force(short signal, char *best, int index, char *str, int *L,
int *H, int *x, int* k, int *minimum, char *where, int n_spaces)
{
	int auxiliary = 0;
	//caso o indice do espaço a ser visitado for maior que o
	//número de espaços terminar função
	if(index == n_spaces)
	{
		return;
	}else if(index == n_spaces-1)
	{
		//indica que é uma folha e deve ser calculado.
		auxiliary = 1;
	}

	//singal ser três indica que essa é a primeira chamada da função.
	if(signal == 3)
	{
		//strings que serão utilizadas para calcular todas as configurações
		//de colocar ou não quebra de espaços

		//chamando recusivamente brute_force signal = 1 e indice = 0
		Brute_force(0 ,best, 0, str, L, H, x, k, minimum, where, n_spaces);

		memset(best, '0', n_spaces);

		//chamando recusivamente brute_force signal = 0 e indice = 0
		Brute_force(1 ,  best, 0, str, L, H, x, k, minimum, where, n_spaces);

		return;
	}

	//signal ser 1 indica que no indice atual
	//será colocada uma quebra de linha
	if(signal==1)
	{
		best[index]='1';
	}else{
		best[index]='0';
	}

	//signal agora será usado como auxiliar
	int aux = signal;
	signal = 0;

	//variiáveis para cálculo do custo
	int i,			 //variável auxiar
		line_size=0, //número de caracteres
		cost=0,		 //custo
		m=-1,		//indice para vetor de espaços
		modl=1;		//núermo de linhas ocupadas até o momento

	if(auxiliary)
	{
	//para toda posição do texto verificar se deve ou não colocar quebra
	//de ao mesmo tempo que calcula o custo.
		for(i=0; str[i]!='\0'; i++)
		{
	
			if(str[i]==' ')
			{
				m++;
				if(best[m]=='1')
				{
	
					cost+=pow((*L)-line_size,(*x));
					//caso desrespeite o tamanho da página custo é infinito e 
					//certamente não é menor que o mínimo atual.
					if(modl>(*H))
					{
						signal =2;
						break;
					}
					modl++;
					line_size=-1;
				}
			}
	
			line_size++;
			//caso desrespeite o maximo de caracteres por linha custo é infinito
			//e certamente não é menor que o mínimo atual.
			if(line_size>(*L))
			{
				signal =1;
				break;
			}
		}	
		line_size--;
		//se nem o tamnho da página ou linha foram desrespeitados...
		if(!signal)
		{
			//calcula custo
			cost+=pow((*L)-line_size,(*x));
			cost=(*k)*(pow((*H)-modl,(*x))+cost);
			//se custo for menor que o mínimo até o momento...
			if(cost<(*minimum))
			{
				//mínimo agora igual a custo
				(*minimum) = cost;
				strcpy(where,best);
			}
		}

		//chama recursivamente a função duas vezes colocando no pŕoximo index
		// 1 ou 0 para cálculo de custo.
	
	}

	if(signal<2)
	{
		Brute_force(0 ,best, index+1, str, L, H,
					x, k, minimum, where, n_spaces);

		if(aux==1)
		{
			best[index]= '1';
		}else{
			best[index] = '0';
		}
		Brute_force(1 , best, index+1, str, L, H,
					x, k, minimum, where, n_spaces);
	}
	return;	
}


/**
 * @brief   função responsável por chamar a função de força bruta
 *
 * @param[FILE*] output   saida onde será impressa a solução
 * @param[FILE*]  text    texto de entrada
 * @param[int*]  L    max numéro de chars em uma linha
 * @param[int*]  H    max numéro de linhas em uma página
 * @param[int*]  x    parâmetro para c´alculo de custo da iteração
 * @param[int*]  k    parâmetro para c´alculo de custo da iteração
 *
 * @return  void, imprime a solução
 */
void Call_bruteforce(FILE* output, FILE* text, int L, int H, int x, int k)
{
	int n_spaces=0,			//número de espaços no texto
		i=0, j,				//auxiliares
							//variável para armazenar custo mínimo
		minimum = k*pow(H,x)+H*k*pow(L,x);

	char aux,		//auxiliar
		*str,		//armazena o texto
		*where,		//vetor que indica onde deverão ser colocadas as quebras
		*best;		//de linha no fim do programa

	//alocando memória para armazenar texto
	str = calloc(H*(L+2),sizeof(char));
	//lendo o texto do arquivo de entrada
	while(fscanf(text,"%c",&aux) != EOF)
	{
		str[i]=aux;
		i++;
		if(aux==' ')
		{
			//salvando o número de espaços no texto
			n_spaces++;
		}
	}

	n_spaces++;
	str[i] = '\0';

	//alocando vetor que armazenará solução
	where = calloc((n_spaces+1),sizeof(char));
	best = calloc((n_spaces+1),sizeof(char));
	where[n_spaces-1]='\0';
	best[n_spaces-1]='\0';

	//chamada do método de força bruta
	Brute_force(3, best, 0, str, &L, &H,
					&x, &k, &minimum, where, n_spaces);

	//salvar em arquivo de saída solução alcansada
	fprintf(output,"%i\n",minimum);
	j=-1;
	for(i=0; str[i]!='\0'; i++)
	{
		//caso no texto original a posição for correspondente a um espaços
		//perguntar ao vetor solução se deve ser substituido ou não por
		//quebra de linha
		if(str[i]==' ')
		{
			j++;
			if(where[j]=='1')
			{
				fprintf(output, "\n");	
			}else{

				fprintf(output, "%c", str[i]);
			}
		}else{

				fprintf(output, "%c", str[i]);
		}
	}

	//desaloca memória
	free(str);
	free(where);

	return;
}

/**
 * @brief   calcula o custo mínimo pelo método Guloso
 *
 * @param[FILE*] output   saida onde será impressa a solução
 * @param[FILE*]  text    texto de entrada
 * @param[int*]  L    max numéro de chars em uma linha
 * @param[int*]  H    max numéro de linhas em uma página
 * @param[int*]  x    parâmetro para c´alculo de custo da iteração
 * @param[int*]  k    parâmetro para c´alculo de custo da iteração
 *
 * @return  void, imprime a solução
 */
void Greedy(FILE* output, FILE* text, int L, int H, int x, int k)
{
	int line_size=0,	//número de caracteres na linha atual até o momento
		modl=1,			//quantidade de linhas utilizadas até o momento
		cost=0,			//cálculo do custo
		aux;			//variável auxiliar

	long unsigned strsize;	//tamanho da string lida no texto
	char *str;				//vetor que armazenaŕa palavra lida no momento
	char **matrix;			//matriz que armazena texto solução

	//tamanho máximo da palavra é o tamanho máximo da linha
	str = calloc(L,sizeof(char));

	//alocando memória para matriz da solução com tamanho máximo da página
	matrix = calloc(H+1,sizeof(char*));
	for(aux=1; aux<H+1; aux++)
	{
		matrix[aux]=calloc(L+2,sizeof(char));
	}

	fscanf(text,"%s",str);	//lê string
	strsize = strlen(str);	//calcula tamanho da string lida

	if(line_size+strsize <= L)	//se palavra couber na linha
	{
		strcat(matrix[modl],str);	//inserir palavra e 
		line_size+=strlen(str);		//adicionar tamanho da linha
	}

	//enquanto texto não acabou lê string
	while(fscanf(text,"%s",str) != EOF)
	{
		strsize = strlen(str);	//calcula tamanho da string lida

		if(line_size+strsize+1 <= L) //se palavra e um espaço couber na linha
		{
			matrix[modl][line_size] = ' ';
			strcat(matrix[modl],str);
			//inserir palavra e espaço
			line_size+=strsize+1;
			//incrementar tamanho da linha atual

		}else{
			//caso não caiba na linha,
			//adiciona quebra de linha
			matrix[modl][line_size] = '\n';
			matrix[modl][line_size+1] = '\0';
			//incrementa número de linhas
			modl++;
			//insere palavra na matrix de saída
			strcat(matrix[modl],str);
			//calcula o custo até o momento
			cost+=pow(L-line_size,x);
			//reinicia o número de caracteres na linha
			line_size=strsize;
		}
	}

	//fim do processo
	//calcula custo final
	cost+=pow(L-line_size,x);
	cost=k*(pow(H-modl,x)+cost);

	//escreve solução no arquivo de saída
	fprintf(output,"%i\n",cost);

	for(aux=1;aux<H+1;aux++)
	{
		if(strlen(matrix[aux])>0)
		{
			fprintf(output,"%s",matrix[aux]);
		}
		free(matrix[aux]);
	}

	//libera memória alocada para o processo.
	free(str);
	free(matrix);

	return;
}


/**
 * @brief 
 */
int main(int argc, char* argv[])
{
	int L,	//número máximo de caracteres em uma linha
		H,	//número máximo de linhas na página
		x,k;//parâmetros para cálculo do custo

	FILE *text, *output;

	text = fopen(argv[2],"r+");	//arquivo de texto de entrada
	output = fopen(argv[3],"w+");//arquivo de texto para saída

	//lendo parâmetros
	fscanf(text,"%i %i\n%i %i\n",&L,&H,&x,&k);

	//verificar qual método utilizar
	if(!(strcmp(argv[1],"-d")))
	{
		printf("Prezado cliente, lamentamos informar que tal funcionalidade");
		printf("ainda não é suportada pelo nosso sistema.\n");
		printf("Tenha certeza de que nossa equipe está trabalhando ");
		printf("incessantemente para estabelecer o serviço referido o mais ");
		printf("rápido possível.\nAgradecemos a compreensão.\n");
		//prog_dinam();

	}else if(!(strcmp(argv[1],"-g")))
	{
		//método guloso.
		Greedy(output ,text ,L ,H ,x ,k);

	}else if(!(strcmp(argv[1],"-b")))
	{
		//método força bruta.
		Call_bruteforce(output ,text ,L ,H ,x ,k);
	}else{

		printf("Prezado cliente, lamentamos informar que tal funcionalidade");
		printf("ainda não é suportada pelo nosso sistema.\n");
		printf("Tenha certeza de que nossa equipe está trabalhando ");
		printf("incessantemente para estabelecer o serviço referido o mais ");
		printf("rápido possível.\nAgradecemos a compreensão.\n");
	}

	fclose(text);
	fclose(output);

	return 0;
}
