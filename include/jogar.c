#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include "cores.h"
#include <string.h>
#include<math.h>
#include<time.h>



void jogo(int **matriz, Mat valores, User usuario){
    int **posicoesLivresMat;
    Mat posicoesLivresStruct = {valores.n*valores.n, 3};
    srand(time(NULL));


    posicoesLivresMat = criaMatriz(posicoesLivresStruct);
    inicializaMatriz(posicoesLivresMat, posicoesLivresStruct, 37);
    

    while(!sorteiaN(matriz, valores, posicoesLivresMat)){
        //IMPRESSÃO
        imprimeCabecalho(usuario);
        printf("\n");
        imprimeMatriz(matriz, valores);

    }

    
    liberaMatriz(posicoesLivresMat, posicoesLivresStruct.n);






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

int posicoesLivres(int **matriz, Mat valores, int **posicoesLivresMat){
    int cont = 0;
    for(int i =0; i<valores.n; i++){

        for(int j =0; j< valores.m; j++){

            if(matriz[i][j] == 0){

                posicoesLivresMat[cont][0] = cont;
                posicoesLivresMat[cont][1] = i;
                posicoesLivresMat[cont][2] = j;  
                cont++;
            }

        }

    } 

    return cont;
}

int sorteiaN(int **matriz, Mat valores, int **posicoesLivresMat){
    
    int cont = posicoesLivres(matriz, valores, posicoesLivresMat);

    if(cont != 0){

        int sorteio = rand() % cont;
        int sorteio_dois_quatro = (rand() % 100) + 1;
        if(valores.n == 4){
            if (sorteio_dois_quatro <= 90){
                sorteio_dois_quatro = 2;
            }else {
                sorteio_dois_quatro = 4;
            }
        }else if(valores.n == 5){
            if(sorteio_dois_quatro <= 85){
                sorteio_dois_quatro = 2;
            }else{
                sorteio_dois_quatro = 4;
            }
        }else{
            if(sorteio_dois_quatro <= 80){
                sorteio_dois_quatro = 2;
            }else{
                sorteio_dois_quatro = 4;
            }
        }

        matriz[posicoesLivresMat[sorteio][1]][posicoesLivresMat[sorteio][2]] = sorteio_dois_quatro;
        return 0;
    }else{
        return 1;
    }



}