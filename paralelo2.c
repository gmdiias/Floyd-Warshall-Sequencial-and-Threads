#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NTH 2
#define MIN(x, y) (((x) < (y)) ? (x) : (y)) // Calcula minimo entre dos valores
#define CAMINHOARQUIVO "Teste/grafo_1500.g" // Define caminho do arquivo

int arrive[NTH];
int cont[NTH];
int tamMatriz = 0;
float **mat;
int linhasThreads = 0;
pthread_barrier_t mybarrier;

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

void *do_job(void *arg){
	int tid = (int)arg;
	int i, j, k;
	int maxLinha = ((int)arg+1) * linhasThreads;
	int minLinha = maxLinha - linhasThreads + 1;
	float **matB = alocmat(tamMatriz,tamMatriz);
	//imprimeMatriz(tamMatriz, matB);
	for(k=1;k<tamMatriz;k++){
		matB = mat;
		//printf("sou uma thread cuido da linha %i ate a %i na altura %i tamanho %i \n", minLinha, maxLinha, k, tamMatriz);
		for(i=minLinha; i<=maxLinha; i++){
			for(j=1; j<tamMatriz; j++){
				mat[i][j] = MIN(matB[i][j], matB[i][k] + matB[k][j]);
			}
		}
		//printf("Aguardando barreira\n");
		pthread_barrier_wait(&mybarrier);
		//printf("Passando barreira\n");
		if(minLinha == 1){
		 	printf("%i\n", k);
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

	mat=alocmat(tamMatriz,tamMatriz);

	// Inicializa as matrizes
	inicializaMatriz(tamMatriz, mat);


	// Realiza a leitura dos pesos de cada vertice
	while (!feof(arquivo)){
    	fscanf(arquivo, "%i", &posX); 
		fscanf(arquivo, "%i", &posY);
		fscanf(arquivo, "%f", &peso);
		fgets(linha, 100, arquivo);
		mat[posX][posY] = peso;
  	}
    // imprimeMatriz(tamMatriz, matB);

	linhasThreads = (tamMatriz-1) / NTH;
	clock_t Ticks[2];
	Ticks[0] = clock();
	pthread_t t[NTH];
	int n, i;
	pthread_barrier_init(&mybarrier, NULL, NTH);
	for(i=0;i<NTH;i++){
		arrive[i]=0;
		cont[i]=0;
		pthread_create(&t[i],NULL,do_job,(void*)i);
	}
	// for(n=0;n<tamMatriz-1;n++){
	// 	for(i=0;i<NTH;i++){
	// 		while(arrive[i]!=1);
	// 		arrive[i]=0;
	// 	}
	// 	// printf("%i\n", n);
	// 	matB = mat;
	// 	for(i=0;i<NTH;i++){
	// 		cont[i]=1;
	// 	}
	// }		

	for(i=0;i<NTH;i++){
		pthread_join(t[i], NULL);
	}
	Ticks[1] = clock();
	double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	printf("Tempo gasto: %g ms.", Tempo);
	getchar();
	imprimeMatriz(tamMatriz, mat);

	pthread_exit(NULL);

}
