#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"


void salvarMatAtual(int **matriz, Mat valores){
        FILE *arquivo;
        arquivo = fopen("atual.dat", "wb");
        fwrite(&valores.n, sizeof(int), 1, arquivo);
        fwrite(&valores.m, sizeof(int), 1, arquivo);

        for(int i =0; i < valores.n; i++){
            for(int j = 0; j < valores.m; j++){
                fwrite(&(matriz[i][j]), sizeof(int), 1,arquivo);

            }
        }
    fflush(arquivo);
    fclose(arquivo);

}

void lerDat(int **matriz){
    int linhas, colunas, valor;
    FILE *arquivo = fopen("atual.dat", "rb");

    fread(&linhas, sizeof(int), 1, arquivo);
    fread(&colunas, sizeof(int), 1, arquivo);

    for(int i =0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            fread(&valor, sizeof(int), 1, arquivo);
            matriz[i][j] = valor;
        }
            
    }

    fclose(arquivo);

}