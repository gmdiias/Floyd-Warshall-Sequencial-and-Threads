#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

float **alocmat(int lin, int col){
	int i;
	float **m;
	m=(float**)malloc(sizeof(float*)*lin);
	for(i=0;i<lin;i++){
		m[i]=(float*)malloc(sizeof(float)*col);
	}
	return m;
}

int main(){
	int k,i,j,m,n;
	FILE *arquivo;
	char nomeArquivo[20] = "grafo.g";
	char linha[100], penultimaLinha[100];
  	int posX, posY, tamMatriz;
  	float peso;

	// Realiza a abertura do arquivo
	if ((arquivo = fopen(nomeArquivo, "r")) == NULL){
        printf("Erro na abertura do arquivo \n");
        exit(1);
    }
    
	// Obtem tamanho da matriz
	do {
		strcpy(penultimaLinha, linha);
		fgets(linha, 100, arquivo);
	} while (strcmp(linha, "#arestas\n") != 0);

	tamMatriz = atoi(penultimaLinha)+1; // Transforma tamanho da matriz para int
	printf("Tamanho matriz: %i", tamMatriz);

	float **mat=alocmat(tamMatriz,tamMatriz);
	float **matB=alocmat(tamMatriz,tamMatriz);
	for(i=0;i<tamMatriz;i++){
		for(j=0;j<tamMatriz;j++){
			mat[i][j]=99999;
			// printf("%d,%d=%f\n",i,j,mat[i][j]);
		}
	}
	for(i=0;i<tamMatriz;i++){
		for(j=0;j<tamMatriz;j++){
			matB[i][j]=99999;
			// printf("%d,%d=%f\n",i,j,mat[i][j]);
		}
	}
	printf("\n");

	while (!feof(arquivo)){
    	fscanf(arquivo, "%i", &posX); 
		fscanf(arquivo, "%i", &posY);
		fscanf(arquivo, "%f", &peso);
		fgets(linha, 100, arquivo);
		mat[posX][posY] = peso;
  	}

	for(k=1; k<tamMatriz; k++){
		matB = mat;
		for(i=1; i<tamMatriz; i++){
			for(j=1; j<tamMatriz; j++){
				mat[i][j] = MIN(matB[i][j], matB[i][k] + matB[k][j]);
			}
		}
	}

	for(i=1;i<tamMatriz;i++){
		for(j=1;j<tamMatriz;j++){
			printf("%f \t",mat[i][j]);
		}
		printf("\n");
	}

}