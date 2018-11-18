#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

/*
*	Trabalho de Compiladores Floyd Warshall
*	Alunos:
*		Frank Tamborelli		RA: 94116
*		Gustavo Mendonca Dias	RA: 88410
*		Matheus Colares 		RA: 92760
*		Tatiane Paz				RA: 85
*/

#define MIN(x, y) (((x) < (y)) ? (x) : (y)) // Calcula minimo entre dos valores
#define CAMINHOARQUIVO "Teste/grafo_1500.g" // Define caminho do arquivo

// Funcao para alocar matriz na memoria
float **alocmat(int lin, int col){
	int i;
	float **m;
	m=(float**)malloc(sizeof(float*)*lin);
	for(i=0;i<lin;i++){
		m[i]=(float*)malloc(sizeof(float)*col);
	}
	return m;
}

void inicializaMatriz(int tamMatriz, float **mat){
	int i, j;
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

void imprimeMatriz(int tamMatriz, float **mat){
	int i, j;
	for(i=1;i<tamMatriz;i++){
		for(j=1;j<tamMatriz;j++){
			printf("%f \t", mat[i][j]);
		}
		printf("\n");
	}
}

// Calcula menor caminho entre os vertices da matriz
void floydWarshall(int tamMatriz, float **mat, float **matB){
	int i, j, k;
	for(k=1; k<tamMatriz; k++){
		matB = mat;
		// printf("%i\n", k);
		for(i=1; i<tamMatriz; i++){
			for(j=1; j<tamMatriz; j++){
				mat[i][j] = MIN(matB[i][j], matB[i][k] + matB[k][j]);
			}
		}
	}
}

int main(){
	FILE *arquivo;
	char linha[100], penultimaLinha[100];
	int k, i, j, tamMatriz, posX, posY;
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
	float **mat=alocmat(tamMatriz,tamMatriz);
	float **matB=alocmat(tamMatriz,tamMatriz);

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
	struct timeval  tv1, tv2;
	gettimeofday(&tv1, NULL);

	floydWarshall(tamMatriz, mat, matB);

	gettimeofday(&tv2, NULL);

	imprimeMatriz(tamMatriz, mat);
	
	printf("Tempo de Execucao do Floyd Warshall paralelo: %.2fs, para essa performance foram utilizado o paralelo.\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

}