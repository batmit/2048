#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void eliminaEspacos(char *comando, int tam){

    for(int i =0; i < tam; i++){
        if(comando[i] == ' '){

            for(int j = i; j < (tam -1); j++){
                comando[j] = comando[j+1];
            }
            tam--;
        }
    }

}

int main(){

    char vetor[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

    char resposta[20] = "ABCDEF";

    if(resposta[4] <= vetor[5-1] && resposta[4] >= 'A'){

        printf("Deu");

    }


}