#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include "cores.h"
#include <string.h>
#include<math.h>
#include<time.h>



void jogo(int **matriz, Mat valores, User usuario){



    if(posicoesLivres(matriz, valores) == 1){
        printf(BOLD(RED("Você perdeu!")));
    }

    //IMPRESSÃO
    imprimeCabecalho(usuario);
    printf("\n");
    imprimeMatriz(matriz, valores);

    


}


void imprimeCabecalho(User usuario){

    printf("\n\n");
    for(int i =0; i< 60; i++){

        printf(TAB_HOR);


    }
    printf("\nUsuário: %s", usuario.nome);
    printf(TAB_VER "Score: %d", usuario.score);
    printf(TAB_VER "Trades: %d", usuario.trades);
    printf(TAB_VER "undoMoves: %d\n", usuario.undoMoves);


}

int posicoesLivres(int **matriz, Mat valores){

    for(int i =0; i<valores.n; i++){

        for(int j =0; j< valores.m; j++){

            if(matriz[i][j] == 0){
                return 0;
            }

        }

    } 

    return 1;

}