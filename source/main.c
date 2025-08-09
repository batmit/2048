#include<stdio.h>
#include<stdlib.h>
#include "../include/funcoes.h"


int main(){

    while(1){
        
        char answer = imprimeMenu();
        
        switch (answer){
            case 'R':
                sairJogo();
                break;
            case 'N':
                Mat choice = novoJogo();
                int **matriz = criaMatriz(choice);
                inicializaMatriz(matriz, choice);
                jogo(matriz, choice);


                liberaMatriz(matriz, choice.n);
                break;
            default:
                break;
        }

    }

        




    return 0;
}