#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
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

#define NTH 4
#define MIN(x, y) (((x) < (y)) ? (x) : (y)) // Calcula minimo entre dos valores;
#define CAMINHOARQUIVO "Teste/grafo_1500.g" // Define caminho do arquivo;

// Variaiveis Globais;
float **mat;
int linhasThreads, tamMatriz;
pthread_barrier_t mybarrier;

// Funcao para alocar matriz na memoria;
float **alocmat(int lin, int col){
	int i;
	float **m;
	m=(float**)malloc(sizeof(float*)*lin);
	for(i=0;i<lin;i++){
		m[i]=(float*)malloc(sizeof(float)*col);
	}
	return m;
}

// Funcao para inicializar pesos da matrizes;
void inicializaMatriz(int tamMatriz, float **mat){
	int i, j;
	for(i=1;i<tamMatriz;i++){
		for(j=1;j<tamMatriz;j++){
			if(i == j) {
				mat[i][j] = 0;
			}
			else {
				mat[i][j] = 999999;
			}
		}
	}
}

// Funcao para mostrar a matriz para o usuario;
void imprimeMatriz(int tamMatriz, float **mat){
	int i, j;
	for(i=1;i<tamMatriz;i++){
		for(j=1;j<tamMatriz;j++){
			printf("%f \t", mat[i][j]);
		}
		printf("\n");
	}
}

// Thread com Floyd Warshall
void *thread_Warshall(void *arg){
	int tid = (int)arg;
	int i, j, k;
	int maxLinha = ((int)arg+1) * linhasThreads;
	int minLinha = maxLinha - linhasThreads + 1;
	float **matB = alocmat(tamMatriz,tamMatriz);
	for(k=1;k<tamMatriz;k++){
		matB = mat;
		for(i=minLinha; i<=maxLinha; i++){
			for(j=1; j<tamMatriz; j++){
				mat[i][j] = MIN(matB[i][j], matB[i][k] + matB[k][j]);
			}
		}
		pthread_barrier_wait(&mybarrier);
	}
}

int main(){
	FILE *arquivo;
	char linha[100], penultimaLinha[100];
	int i, posX, posY;
  	float peso;

	// Realiza a abertura do arquivo
	if ((arquivo = fopen(CAMINHOARQUIVO, "r")) == NULL){
        printf("Erro na abertura do arquivo. Por favor verifique o caminho do arquivo. \n");
        exit(1);
    }

	printf("Arquivo localizado com sucesso.\nExecutando leitura do arquivo e configuracoes iniciais ...\n");
    
	// Obtem tamanho da matriz
	do {
		strcpy(penultimaLinha, linha);
		fgets(linha, 100, arquivo);
	} while (strcmp(linha, "#arestas\n") != 0);

	tamMatriz = atoi(penultimaLinha)+1; // Transforma tamanho da matriz para int

	mat=alocmat(tamMatriz,tamMatriz);

	// Inicializa a matriz
	inicializaMatriz(tamMatriz, mat);

	// Realiza a leitura dos pesos de cada vertice
	while (!feof(arquivo)){
    	fscanf(arquivo, "%i", &posX); 
		fscanf(arquivo, "%i", &posY);
		fscanf(arquivo, "%f", &peso);
		fgets(linha, 100, arquivo);
		mat[posX][posY] = peso;
  	}

	linhasThreads = (tamMatriz-1) / NTH;

	printf("Leitura realizada com sucesso.\n");
	printf("Iniciando algoritmo Floyd Warshall ...\n");
	struct timeval  tv1, tv2;
	gettimeofday(&tv1, NULL);
	pthread_t t[NTH];
	pthread_barrier_init(&mybarrier, NULL, NTH);
	for(i=0;i<NTH;i++){
		pthread_create(&t[i],NULL,thread_Warshall,(void*)i);
	}

	for(i=0;i<NTH;i++){
		pthread_join(t[i], NULL);
	}
	gettimeofday(&tv2, NULL);
	printf("Execucao Floyd Warshall concluida.\nApresentando resultados ...\n");

	imprimeMatriz(tamMatriz, mat);

	printf("Tempo de Execucao do Floyd Warshall paralelo: %.2fs, para essa performance foram utilizadas %i threads.\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec), NTH);
	pthread_exit(NULL);
}
