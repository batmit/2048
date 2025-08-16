#include<stdio.h>
#include<stdlib.h>
#include "../include/funcoes.h"
#include<time.h>
#include<math.h>

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
                inicializaMatriz(matriz, choice, 0);
                jogo(matriz, choice, &usuario_novo);


                liberaMatriz(matriz, choice.n);
                break;
            case 'J':
                int tam = lerTam();
                if(tam){
                    Mat volta = {tam, tam};
                    matriz = criaMatriz(volta);
                    User usuario_volta = {"New_User", 0, 0, 0};
                    lerDat(matriz, &usuario_volta);
                    jogo(matriz, volta, &usuario_volta);

                    liberaMatriz(matriz, tam);
                }else{
                    limparTerminal();
                    printf("\nERRO\nVocê ainda não tem um jogo iniciado");
                }



                break;
            default:
                break;
        }

    }

        




    return 0;
}