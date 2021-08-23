#include <stdio.h>
#include <stdlib.h>

double cont=0; //Variável contadora

//Função para conferir se duas rainhas estão em posição de ataque ou não
int confere(int n, int **tab, int l, int c) 
{   
	//Verifica se duas rainhas estão na mesma coluna
    for (int i = 0; i < l; i++)
        if (tab[i][c] == 1)
            return 0;
 
 	//Verifica se duas rainhas estão na mesma diagonal (sentido \)
    for (int i = l, j = c; i >= 0 && j >= 0; i--, j--)
        if (tab[i][j] == 1)
            return 0;
 
 	//Verifica se duas rainhas estão na mesma diagonal (sentido /)
    for (int i = l, j = c; i >= 0 && j < n; i--, j++)
        if (tab[i][j] == 1)
            return 0;
        
    //Se não estiverem em posição de ataque   
    return 1;
}


void nRainhas(FILE *arq, int n, int **tab, int lin)
{
	/*Se chegou à ultima linha do tabuleiro, as rainhas estarão posicionadas corretamente,
	então a solução é impressa no arquivo e a variável cont é incrementada */
    if(lin==n)
    {
        cont++;
        fputs("\n\n", arq);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                fprintf(arq, "%d", tab[i][j]);
            fputs("\n", arq);
        }
        return;
    }
    
    //Testando a rainha em cada casa da linha atual
    for(int i=0; i<n; i++) //i controla o indíce da coluna da matriz
    {
    	//Se duas rainhas não estiverem em posição de ataque
        if(confere(n, tab, lin, i))
        {
        	//É colocada uma rainha (1) na casa atual
            tab[lin][i]= 1;
            //A função chama a si mesma para tentar colocar a próxima rainha na linha seguinte
            nRainhas(arq, n, tab, lin + 1);
            //Volta e remove a rainha da casa atual (0)
            tab[lin][i]= 0;
        }
    }
    
}

int main()
{   
    FILE *arq;
    int **tab, n;
    
    //Entrada
    do{
        printf("Entre com o tamanho do tabuleiro: ");
        scanf("%d", &n);
    }while(n<4 || n>32);
    
    //Alocando linhas da matriz com malloc
    tab = (int**)malloc(n*sizeof(int*));
    
    //Alocando colunas com malloc e zerando a matriz
    for(int i=0; i<n; i++)
    {
        tab[i] = (int*)malloc(n*sizeof(int));
        for(int j=0; j<n; j++)
            tab[i][j]=0;
    }
    
    //Abertura do arquivo para escrita e chamada da função nRainhas
    arq= fopen("rainha.out", "w");
    nRainhas(arq, n, tab, 0);
    //Volta o ponteiro no inicio do arquivo e imprime número de soluções
    rewind(arq);
    fprintf(arq, "%.0lf", cont);
    fclose(arq); //Fechamento do arquivo

    return 0;
}
