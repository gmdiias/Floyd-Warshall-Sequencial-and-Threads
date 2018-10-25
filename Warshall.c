#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int main(){

	int matriz[3][3];
	
	int i,k;
	
	for(i=0; i<3; i++){
		for(k=0; k<3; k++){
			matriz[i][k]= 9999;
	    }
	}
	
	for(i=0; i<3; i++){
		for(k=0; k<3; k++){
			printf("%d |", matriz[i][k]);
	    }
	    printf("\n");
	}
}
