#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// TODO Problemas encontrados na é q a matriz comeca em 0 e vai ate 500
// TODO Deve ser implementado um metodo para resetar a matriz

float **alocmat(int lin, int col){
	int i;
	float **m;
	m=(float**)malloc(sizeof(float*)*lin);
	for(i=0;i<lin;i++){
		m[i]=(float*)malloc(sizeof(float)*col);
	}
	return m;
}

void imprimeMatriz(int tamMatriz, float matriz[tamMatriz][tamMatriz]){
	int posX, posY;
	for(posX = 0; posX < tamMatriz; posX++){
		for(posY = 0; posY < tamMatriz; posY++){
			printf("%f | ", matriz[posX][posY]);
		}
		printf("\n");
	}
}

int importarArquivo(){
	
	FILE *arquivo;
	char nomeArquivo[20] = "grafo_500.g";
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

	tamMatriz = atoi(penultimaLinha); // Transforma tamanho da matriz para int
	printf("Tamanho matriz: %i", tamMatriz);
	
	float matriz[tamMatriz+1][tamMatriz+1];

	//float **mat=alocmat(tamMatriz,tamMatriz);
	
	while (!feof(arquivo)){
    	fscanf(arquivo, "%i", &posX); 
		fscanf(arquivo, "%i", &posY);
		fscanf(arquivo, "%f", &peso);
		fgets(linha, 100, arquivo);
		matriz[posX][posY] = peso;
  	}
	
	imprimeMatriz(tamMatriz, matriz);
  	fclose(arquivo);
	printf("\n\n");
}
 
 int main(){
 	importarArquivo();
 }