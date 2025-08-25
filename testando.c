#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "include/funcoes.h"

void salvarMatAtual(int **matriz, Mat valores, User *usuario){
    FILE *arquivo;
    arquivo = fopen("atual.dat", "wb");
    fwrite(&valores.n, sizeof(int), 1, arquivo);
    fwrite(&valores.m, sizeof(int), 1, arquivo);

    for(int i =0; i < valores.n; i++){
        for(int j = 0; j < valores.m; j++){
            fwrite(&(matriz[i][j]), sizeof(int), 1,arquivo);

        }
    }
    
    fwrite(&usuario->score, sizeof(int), 1, arquivo);
    fwrite(&usuario->trades, sizeof(int), 1, arquivo);
    fwrite(&usuario->undoMoves, sizeof(int), 1, arquivo);


    
    fflush(arquivo);
    fclose(arquivo);

}

void inicializaMatriz(int **matriz, Mat valores, int valor){

    for(int i =0; i< valores.n; i++){

        for(int j =0; j< valores.m; j++){

            matriz[i][j] = valor;            

        }

    }
    

}

void liberaMatriz(int **matriz, int n){

    for(int i=0; i<n; i++){

        free(matriz[i]);

    }
    free(matriz);

}

int **criaMatriz(Mat valores){

    int **matriz;

    matriz = malloc(valores.n * sizeof(int*));
    for(int i = 0; i < valores.n; i++){
        matriz[i] = malloc(valores.m * sizeof(int));
    }

    return matriz;

}


int main(){

    int **matriz;
    User lixo = {"New_User", 0, 0, 0};
    Mat testando = {6, 6};
    matriz = criaMatriz(testando);
    inicializaMatriz(matriz, testando, 0);
    salvarMatAtual(matriz, testando, &lixo);


    liberaMatriz(matriz, 6);


}