//nova função main
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

//Algoritmo Viviane
struct sTipoFila{
       int info;
       struct sTipoFila* prox;
       };

typedef struct sTipoFila TipoFila;

TipoFila* cria_fila(void)
{
       return NULL;
}

TipoFila* insere (TipoFila *l, int dado)
{
       TipoFila *novo; //novo elemento
       TipoFila *ant = NULL; //ponteiro auxiliar para a posição anterior
       TipoFila *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoFila*) malloc(sizeof(TipoFila));

       /*insere a informação no novo nodo*/
       novo->info = dado;
       novo->prox = NULL;

       /*achando o final da fila*/
       while (ptaux!=NULL)
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }

       /*encaeia o elemento*/
       if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
       {
               novo->prox = l;
               l = novo;
       }
       else
           ant->prox = novo;

       return l;
}

int vazia (TipoFila* l)
{
     if (l == NULL) return 1;
     else return 0;
}

int removeFila(TipoFila **l)
{
    TipoFila *rem = *l;
    int aux;

    if (!vazia(*l))
    {
      aux = (*l)->info;
      *l = (*l)->prox;
      free(rem);
      return (aux);
    }
    else return -1;
}
//Fim algoritmo viviane

//v é vertice de partida (por exemplo 0), max é o numero total de vertices do grafo e id é o que é colocado no arrey
void DFS (int **grafo, int v, int max, int *vis, int id, int boleano)
//Método DFS
{
    vis[v]= id;
    // se boleano = true, então pede-se os componentes conexos, caso contrario vai ser as distancias.
    if (boleano == true)
    {
    	for(int w = 1; w<=max ; w++)    //percorre os vértices adjacentes a v
    	{
    		if (grafo[v][w]== 1 && vis[w] == -1)  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
    		{
    			DFS(grafo, w, max, vis, id, true); //chamada recursiva para o vértice adjacente a v
    		}
    	}
    }
    if (boleano == false)
    {
    	id = id + 1;
    	for (int w = 0; w<=max; w++)
    	{
    		if (grafo[v][w] == 1 && (vis[w] == -1))
    		{
    			DFS(grafo, w, max, vis, id, false);
    		}
    		//else if (vis[w] == 0 || vis[w] == -1)
    		//{
    			//printf("aqui\n");
    			//vis[w] = -1;
    			//DFS(grafo, w, max, vis, id, false);
    		//}
    	}
    }
      
}

//v é vertice de partida (por exemplo 0) e max é o numero total de vertices do grafo
void BFS (int **grafo, int v, int max, int *vis, int id, int boleano)
//Método BFS
{
    int w;
    TipoFila *FV;
    TipoFila *TV;
    int count = 1;

    FV = cria_fila();
    FV = insere(FV,v);
    vis[v]= id;
    // se boleano = true, então pede-se os componentes conexos, caso contrario vai ser as distancias.
    if (boleano == false)
    {
    	TV =cria_fila();
    	while(!vazia(FV))
    	{
    		id ++;
    		while(!vazia(FV))
    		{
    			v = removeFila(&FV);
    			for (w = 1; w <=max; w++)	//percorre os vértices adjacentes a v
    			{
    				if (grafo[v][w] == 1 && vis[w] == -1)	//encontra um vértice adjacente a c que ainda não tenha sito visitado
    				{
    					TV = insere(TV, w);
    					vis[w] = id;
    				
    				}
    			}
    		}
    		id ++;
    		while (!vazia(TV))
    		{
    			v = removeFila(&TV);
    			for (w = 1; w<=max; w++)
    			{
    				if (grafo[v][w] == 1 && vis[w] == -1)
    				{
    					FV = insere(FV, w);
    					vis[w] = id;
    				}
    			}
    		}
    	}
    }
    else if (boleano == true)
    {
    	while (!vazia(FV))
    	{
       		v = removeFila(&FV);
       		for(w = 1; w<=max ; w++)    //percorre os vértices adjacentes a v
          		if ((grafo[v][w]== 1) && (vis[w]==-1))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
          		{
              		FV = insere(FV,w);
              		vis[w]= id;
           		}

    	}
    }
    
}

int componentes(int **grafo, int vertices, int boleano)//boleano é para saber se é ou DFS
////método de cálculo de componentes conexos dos grafos em BFS e DFS
{
	int id =0;
	int v;
	int visitados[vertices];
	
	for (int v = 0; v < vertices; v++)
		visitados[v] = -1;
	
	//caso seja false faz a busca dos componentes em BFS caso contrario DFS
	if (boleano == false)
	{
		for (v = 0; v < vertices; v++)
		{
			if (visitados[v] == -1)
				BFS(grafo, v, vertices, visitados, id++, true);
		}

	}
	else if (boleano == true)
	{
		for (v = 0; v < vertices; v++)
		{
			if(visitados[v] == -1)
				DFS(grafo, v, vertices, visitados, id++, true);
		}
	}
	return id;
}

void dist(int **grafo, int vertices, int boleano, int *distancia)
//método de calculo de distancia dos grafos em BFS e DFS
{
	int id = 0;
	int v;
	//Se for true busca a distância com DFS caso contratio BFS
	for (v = 0; v < vertices; v++)
	{
		distancia[v] = -1;
	}
	if (boleano == true)
	{
		DFS(grafo, 0, vertices, distancia, id, false);
	}
	if (boleano == false)
	{
		BFS(grafo, 0, vertices, distancia, id, false);
	}

}
//

int** alocarMatriz (int v)
//recebe o numero de vertices do grafo para alocar uma matriz quadrada
//inicializa com 0
{
	int i, j;
	int **matriz;

	matriz=(int**)malloc(v*sizeof(int*)); //aloca as linhas da matriz
	if(matriz==NULL)
	{
		printf("ERRO: memoria insuficiente\n");
		return (NULL);
	}
	for(i=0;i<v;i++)
	{
		matriz[i]=(int*)malloc(v*sizeof(int)); //aloca as colunas
		if(matriz[i]==NULL)
		{
			printf("ERRO: memoria insuficiente\n");
			return (NULL);
		}
		for(j=0;j<v;j++) //inicializa com 0
			matriz[i][j]=0;
	}
	return matriz;	//devolve o ponteiro para a matriz alocada
}

int** liberarMatriz (int v, int** matriz)
//Da um "free" em todos os elementos da matriz
{
	int i;
	for(i=0;i<v;i++)
		free(matriz[i]);
	free(matriz);
	return (NULL);
}



int main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	FILE * arquivo;
	int vertices,arestas;
	int i,j, algoritmo;
	int **grafo, **visitados;
	int componentes_conexos;

	char bfs[5]="-bfs";
	char dfs[5]="-dfs";
	char c[3]="-c";
	char d[3]="-d";

	if (argc!=4) //se o usuario passou numero errado de parametros
	{
		printf ("parametros invalidos\n");
		return 1;
	}
	else
	{
		arquivo=fopen(argv[3], "r");
		if (arquivo==NULL) //se nao conseguiu abrir o arquivo;
		{
			printf ("erro ao abrir o arquivo\n");
			return 1;
		}
		else //arquivo de entrada ok;
		{
			//printf("abriu o arquivo\n");
			//rewind(arquivo) seta a posição corrente para o inicio do arquivo;

			fscanf(arquivo,"%d %d ",&vertices,&arestas);
			//printf("%d %d", vertices, arestas);
			grafo=alocarMatriz(vertices);


			//feof(arquivo) verdadeiro se chegou no final, falso cc.
			while(!feof(arquivo))
			{
				fscanf(arquivo,"%d %d ",&i,&j);
				grafo[i][j]=1;
				grafo[j][i]=1; 
			}
			fclose(arquivo);
			int distancia[vertices];

			if((strcmp(bfs,argv[1])==0))
			{
				if((strcmp(c,argv[2])==0))
				{
					componentes_conexos = componentes(grafo, vertices, false);
					printf("%d ", componentes_conexos);
				}
				else if ((strcmp(d,argv[2])==0))
					//chamar distancia com bfs
				{
					dist(grafo, vertices, false, distancia);
					for (int i = 0; i < vertices; ++i)
					{
						printf("%d ",distancia[i]);
					}
				}
				else 
				{
					printf("parametro invalido\n");
				}
			}
			else if ((strcmp(dfs,argv[1])==0))
			{
				if((strcmp(c,argv[2])==0))
				{
					componentes_conexos = componentes(grafo, vertices, true);
					printf("%d ", componentes_conexos);
				}

				else if ((strcmp(d,argv[2])==0))
				{
					//chamar distancia com dfs
					dist(grafo, vertices, true, distancia);

					for (int cont = 0; cont<vertices;cont++)
					{
						printf("%d ",distancia[cont]);	
					}
				}
					
				else
					printf("parametro invalido\n");
			}
			else 
				printf("parametro invalido\n");




			grafo=liberarMatriz(vertices,grafo);
		}
	}
	return 0;
}