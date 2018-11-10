#include <stdio.h>

void imprimeMatriz(float Media[501][501]){
	for(int x = 0; x < 501; x++){
		for(int y = 0; y < 501; y++){
			printf("%f | ", Media[x][y]);
		}
		printf("\n");
	}
}

void main()
{
	FILE *arq;
  	char Linha[100];
  	char *result;
  	int x, y;
  	float asd;
	float Media[501][501] = {0};
  	// Abre um arquivo TEXTO para LEITURA
  	arq = fopen("grafo_500.g", "rt");
  	if (arq == NULL)  // Se houve erro na abertura
  	{
    	printf("Problemas na abertura do arquivo\n");
     	return;
  	}
	while (!feof(arq)){
		printf("Iniciando ");
		fscanf(arq, "%c", &Linha);
		if(strcmp(Linha, "#") == 0){
			printf("Aqui");
		}
	}
  	while (!feof(arq))
  	{
    	fscanf(arq, "%i", &x); 
		fscanf(arq, "%i", &y);
		fscanf(arq, "%f", &asd);
		fscanf(arq, "%c", &Linha); // Le resto do arquivo '\n'
		Media[x][y] = asd;
  	}
	// imprimeMatriz(Media);
  	fclose(arq);
}