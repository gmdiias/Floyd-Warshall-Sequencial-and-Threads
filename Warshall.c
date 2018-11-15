#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/*
*	Trabalho de Compiladores Floyd Warshall
*	Alunos:
*		Frank Tamborelli		RA:
*		Gustavo Mendonca Dias	RA: 88410
*		Matheus Colares 		RA: 
*		Tatiane Paz				RA: 
*/

#define MIN(x, y) (((x) < (y)) ? (x) : (y)) // Calcula minimo entre dos valores
#define CAMINHOARQUIVO "Teste/grafo_500.g" // Define caminho do arquivo

float **mat;
float **matB;
int tamMatriz;
int i, j, k;

// Funcao para alocar matriz na memoria
float **alocmat(int lin, int col){
	float **m;
	m=(float**)malloc(sizeof(float*)*lin);
	for(i=0;i<lin;i++){
		m[i]=(float*)malloc(sizeof(float)*col);
	}
	return m;
}

void inicializaMatriz(int tamMatriz, float **mat){
	for(i=1;i<tamMatriz;i++){
		for(j=1;j<tamMatriz;j++){
			if(i == j) {
				mat[i][j] = 0;
			}
			else {
				mat[i][j] = 99999;
			}
		}
	}
}

void imprimeMatriz(){
	for(i=1;i<tamMatriz;i++){
		for(j=1;j<tamMatriz;j++){
			printf("%f \t", mat[i][j]);
		}
		printf("\n");
	}
}

void *thread_hello(void *arg){
	int coluna;
	int linha = (int)arg;
	printf("executando thread k = %i, linha = %i, coluna = %i\n", k, linha, coluna);
	for(coluna=1; coluna<tamMatriz; coluna++){
		mat[linha][coluna] = MIN(mat[linha][coluna], matB[linha][k] + matB[k][coluna]);
	}
	pthread_exit(0);
}

// Calcula menor caminho entre os vertices da matriz
void floydWarshall(){
	pthread_t *t=(pthread_t*)malloc(tamMatriz*sizeof(pthread_t));
	for(k=1; k<tamMatriz; k++){
		matB = mat;
		printf("%i\n", k);
		for(i=1; i<tamMatriz; i++){
			printf("criei a thread %i\n", i);
			pthread_create(&t[i],NULL,thread_hello,(void*)i);
		}
		for(i=1; i<tamMatriz; i++){
			pthread_join(t[i],NULL);
		}
	}
}

int main(){
	FILE *arquivo;
	char linha[100], penultimaLinha[100];
	int posX, posY;
  	float peso;

	// Realiza a abertura do arquivo
	if ((arquivo = fopen(CAMINHOARQUIVO, "r")) == NULL){
        printf("Erro na abertura do arquivo \n");
        exit(1);
    }
    
	// Obtem tamanho da matriz
	do {
		strcpy(penultimaLinha, linha);
		fgets(linha, 100, arquivo);
	} while (strcmp(linha, "#arestas\n") != 0);

	tamMatriz = atoi(penultimaLinha)+1; // Transforma tamanho da matriz para int

	// Aloca memoria para matrizes
	mat=alocmat(tamMatriz,tamMatriz);
	matB=alocmat(tamMatriz,tamMatriz);

	// Inicializa as matrizes
	inicializaMatriz(tamMatriz, mat);
	inicializaMatriz(tamMatriz, matB);

	// Realiza a leitura dos pesos de cada vertice
	while (!feof(arquivo)){
    	fscanf(arquivo, "%i", &posX); 
		fscanf(arquivo, "%i", &posY);
		fscanf(arquivo, "%f", &peso);
		fgets(linha, 100, arquivo);
		mat[posX][posY] = peso;
  	}

	floydWarshall(tamMatriz, mat, matB);

	imprimeMatriz(tamMatriz, mat);

}