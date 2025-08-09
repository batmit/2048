#include<stdio.h>
#include<stdlib.h>
#include "../include/funcoes.h"

int main(){
    int **matriz;
    while(1){
        
        char answer = imprimeMenu();
        
        switch (answer){
            case 'R':
                sairJogo();
                break;
            case 'N':
                Mat choice = novoJogo();
                User usuario_novo = {"New_User", 0, 0, 0};
                matriz = criaMatriz(choice);
                inicializaMatriz(matriz, choice);
                jogo(matriz, choice, usuario_novo);


                liberaMatriz(matriz, choice.n);
                break;
            default:
                break;
        }

    }

        




    return 0;
}