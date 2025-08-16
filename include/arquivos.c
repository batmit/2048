#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"


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

int lerDat(int **matriz, User *usuario){
    int linhas, colunas, valor;
    FILE *arquivo = fopen("atual.dat", "rb");
    if(arquivo == NULL){
        return 1;
    }
    fread(&linhas, sizeof(int), 1, arquivo);
    fread(&colunas, sizeof(int), 1, arquivo);

    for(int i =0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            fread(&valor, sizeof(int), 1, arquivo);
            matriz[i][j] = valor;
        }
            
    }

    fread(&usuario->score, sizeof(int), 1, arquivo);
    fread(&usuario->trades, sizeof(int), 1, arquivo);

    fread(&usuario->undoMoves, sizeof(int), 1, arquivo);


    fclose(arquivo);
    return 0;
}

int lerTam(){
    int retorno;
    FILE *arquivo = fopen("atual.dat", "rb");

    fread(&retorno, sizeof(int), 1, arquivo);

    fclose(arquivo);
    return retorno;


}