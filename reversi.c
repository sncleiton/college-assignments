#include "reversi.h"

/*#define PRETO 2
#define BRANCO 1
#define NON 0
*/
//int DIR[8] = {-11, -10, -9, -1, 1, 9, 10, 11};


//v[0] = p1; v[1]= p2


int IAplay=0;
int ALPHA, BETA;


void mostraTabuleiro(short* tabuleiro)
{

    short i = 0;

    printf("   1 2 3 4 5 6 7 8 \n");
    for (int lin=1; lin<9; lin++)
    {
        printf("%d  ", lin);

        for (int col=1; col<9; col++)
        {
            i = tabuleiro[col + (10 * lin)];
            if(i==PRETO)
            {
                printf("P ");
            }else if(i==BRANCO)
            {
                printf("B ");
            }else{
                printf("º ");
            }
        }
        printf("\n");
    }
}


short* inicializaTabuleiro(short* tabuleiro)
{
    tabuleiro = (short*)calloc(10*10,sizeof(short)); //Add access it by arr[i*M + j]

    tabuleiro[44] = tabuleiro[55] = BRANCO;
    tabuleiro[45] = tabuleiro[54] = PRETO;

    return tabuleiro;//////
}

int trem(int jogada, short* v ,short* tabuleiro, short sinal)
{
    int c , j = 0;
    int dirs[8];

    for(int i=0; i<8; i++)
    {
        c = jogada + DIR[i];
    
        if(tabuleiro[c]==v[1])
        {
            //c = c + DIR[i];
            while(tabuleiro[c]==v[1])
            {
                c = c + DIR[i];
            }

            if(tabuleiro[c]==v[0])
            {
                if(!sinal)
                {
                    return 1;
                }
                dirs[j] = DIR[i];
                j++;
            }
        }
    }
    
    
    
    if(!sinal)
    {
        return 0;
    }

    tabuleiro[jogada] = v[0];
 
    for(int i=0; i<j; i++)
    {
        c = jogada + dirs[i];
    
        while(tabuleiro[c] == v[1])
        {
            tabuleiro[c] = v[0];
            
            c = c + dirs[i];
        }
    }
    
    return 0;
}



int movimentoValido(int jogada, short* v, short* tabuleiro, short simul)
{
    int i=0;

    if(!((jogada > 10) && (jogada < 89) && (jogada%10 > 0) && (jogada%10 < 9)))
    {
        return i;
    }


    if(tabuleiro[jogada] == NON)
    {
        i = trem(jogada, v, tabuleiro, 0);
    }

    if(i&&(!simul))
    {
        trem(jogada, v, tabuleiro, 1); //fazer jogada
    }else{
        return i;
    }
    
    return i;
    
}


int restaJogada(short* v, short* tabuleiro)
{
    int jogada = 11;
    
    
    while(jogada<89)
    {
        if(movimentoValido(jogada, v, tabuleiro, 1))
        {
            return 1;
        }
        jogada++;
    }
    
    return 0;
}



int* armazenaJogadasValidas(short* v, short* tabuleiro)
{
    int jogada, *jogadas;
    jogadas = calloc(65,sizeof(short));
    //jogadas[0]=0;

    int i=0;
    for(jogada = 11; jogada< 89; jogada++)
    {
        if(movimentoValido(jogada, v, tabuleiro, 1))
        {
            i++;
            jogadas[i] = jogada;

        }
    }

    jogadas[0] = i;
    
    return jogadas;
}


int alphaBeta(short* tabuleiro, int profundidade, short* v)
{
    int U;

    ALPHA = (-1)*INFI;
    BETA = INFI;

    U = maxValueKAI(tabuleiro, 0, profundidade, v);

    return U;
}



int maxValueKAI(short* tabuleiro, int profAtual, int profundidade, short* v)
{
    if(profundidade <= profAtual)
    {
        return utilidade(tabuleiro, v);
    }

    int U = (-1)*INFI;
    int Z = 0;

    int* sucessores;

    sucessores = armazenaJogadasValidas(v, tabuleiro);

    short n[2];

    n[1] = v[0];
    
    n[0] = v[1];


    if(profAtual==0)
    {
        IAplay = sucessores[1];
    }

    for(int i=1; i<=sucessores[0]; i++)
    {
        short* board = NULL;
        
        board = inicializaTabuleiro(board);
        
        copiaTabuleiro(tabuleiro, board);

        movimentoValido(sucessores[i], v, board, 0);
        
        Z =  minValueKAI(board, profAtual+1, profundidade, n);
        
        free(board);//
        
        if( Z > U)
        {
            U = Z;
            
            if(profAtual == 0)
            {

                IAplay = sucessores[i];
            }
        }
        
        if(U >= BETA)
        {
            printf("\n\nPODAS PRA VC\n\n");
            free(sucessores);
            return U;
        }
        
        if(U > ALPHA)
        {
            ALPHA = U;
        }

    }

    free(sucessores);
    
    return U;
}





int minValueKAI(short* tabuleiro, int profAtual, int profundidade, short* v)
{
    if(profundidade <= profAtual)
    {
        return (-1)*utilidade(tabuleiro, v);
    }

    int U = INFI;
    int Z = 0;

    int* sucessores;

    sucessores = armazenaJogadasValidas(v, tabuleiro);

    short n[2];

    n[1] = v[0];
    
    n[0] = v[1];


    for(int i=1; i<=sucessores[0]; i++)
    {
        short* board = NULL;
        
        board = inicializaTabuleiro(board);
        
        copiaTabuleiro(tabuleiro, board);

        movimentoValido(sucessores[i], v, board, 0);
        
        Z =  maxValueKAI(board, profAtual+1, profundidade, n);

        free(board);

        if( Z < U)
        {
            U = Z;
        }

        if(U <= ALPHA)
        {
            free(sucessores);
            return U;
        }
        
        if(U < BETA)
        {
            BETA = U;
        }

    }

    free(sucessores);
    
    return U;
}




void copiaTabuleiro(short* original, short* copia)
{
    for(int i=0; i<(10*10); i++)
    {
        copia[i] = original[i];
    }
}


int diferencaPecas(short* v, short* tabuleiro)
{
    int U = 0;
  
    for(int i=1; i<89; i++)
    {
        if(tabuleiro[i] == v[0])
        {
            U++;
        }else if(tabuleiro[i] == v[1])
        {
            U--;
        }
    }

    return U;
}

int utilidade(short* v, short* tabuleiro)
{
    int U1 = 0, U2 = 0;
    int* lixo = NULL;
    short n[2] = {0,0};

    n[0] = v[1];
    n[1] = v[0];

    U1 = diferencaPecas(v, tabuleiro);

    lixo = armazenaJogadasValidas(n, tabuleiro);

    U2 = lixo[0];

    free(lixo);
    
    if(U2==0)
    {
        return INFI;
    }

    return (U1-(0.7*U2));
}


int main()
{
    int jogadaP1;
    short* board = NULL;
    short n[2];
    short v[2] = {0,0};

    n[1] = v[0] = PRETO;
    n[0] = v[1] = BRANCO;

    printf("\tBem vindo ao jogo Reversi\n");

    board = inicializaTabuleiro(board);

    int nonfire;
    int jaKabo =0;
    
    int profMax = 14; ///////

    printf("\ninsira posição da jogada concatenando as coordenadas.\n");
    printf("exemplo: (2 , 3) é 23\n\n");

    while(1)
    {

        mostraTabuleiro(board);
        
        nonfire = 1;

        if(restaJogada(v, board))
        {
            while(nonfire)
            {
                printf("\nSua vez!\n");
   
                scanf("%d", &jogadaP1);
            
                if(!movimentoValido(jogadaP1, v, board, 1))
                {
                    printf("movimento inválido\n");
                }else{
                    movimentoValido(jogadaP1, v, board, 0);
                    nonfire =0;
                }
            }
            
            jaKabo = 0;

        }else{
            printf("\nNão restam jogadas válidas, Passas sua vez.\n\n");
            
            jaKabo++;
            
            if(jaKabo>1)
            {
                if(diferencaPecas(v, board) < 0)
                {
                    printf("\n\n\tVocê Venceu!\n");
                }else{
                    printf("\n\n\tVocê Perdeu!\n");
                }
                
                free(board);
                return 0;
            }

        }

        mostraTabuleiro(board);

        printf("\nvez da IA\n");

        if(restaJogada(n, board))
        {
            
            alphaBeta( board, profMax, n);

            printf("\nIA jogou: %d\n\n",IAplay);
            movimentoValido(IAplay, n, board, 0);
            
            jaKabo = 0;

        }else{
            jaKabo++;
            if(jaKabo>1)
            {
                if(diferencaPecas(v, board) < 0)
                {
                    printf("\n\n\tVocê Venceu!!!\n");
                }else{
                    printf("\n\n\tVocê Perdeu!\n");
                }

                free(board);
                return 0;
            }
        }
    }
    
    free(board);
    return 0;

}


