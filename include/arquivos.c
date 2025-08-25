#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include <string.h>

//Salvo a matriz atual no binário(usado para desfazer movimentos)
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

//Para desfazer movimentos, lê o binário
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

//Verifica se há um arquivo binário iniciado(para desfazer movimentos)
int lerTam(){
    int retorno;
    FILE *arquivo = fopen("atual.dat", "rb");
    if(arquivo != NULL){
        fread(&retorno, sizeof(int), 1, arquivo);

    }else{
        return 0;
    }

    fclose(arquivo);
    return retorno;


}

void salvarJogo(int **matriz, int **ultimaMat ,Mat valores, User *usuario, char NomeArqu[27]){

    FILE *arquivo = fopen(NomeArqu, "w");

    fprintf(arquivo, "%d %d %d \n", valores.m, usuario->undoMoves, usuario->trades);
    fprintf(arquivo, "%d %s \n", usuario->score, usuario->nome);

    for(int i =0; i < valores.m; i++){

        for(int j = 0; j < valores.n; j++){
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");

    }

    for(int i = 0; i < valores.m; i++){

        for(int j =0; j < valores.n; j++){

            fprintf(arquivo, "%d ", ultimaMat[i][j]);


        }
        fprintf(arquivo, "\n");

    }

    fclose(arquivo);

}

int carregarJogo(int **matriz, User *usuario, char nomeArqu[27]){
    //char lixo;
    int tamAqui;
    int **mat2;
    FILE *arquivo = fopen(nomeArqu, "rb");
    fscanf(arquivo, "%d %d %d", &tamAqui, &usuario->undoMoves, &usuario->trades);
    fscanf(arquivo, "%d ", &usuario->score);
    fgets(usuario->nome, sizeof(usuario->nome), arquivo);
    for(int i =0; i < tamAqui; i++){

        for(int j =0; j < tamAqui; j++){

            fscanf(arquivo, "%d ", &matriz[i][j]);

        }
        //fscanf(arquivo, "%c", &lixo);

    }
    Mat valoresAqui = {tamAqui, tamAqui};
    mat2 = criaMatriz(valoresAqui);

    for(int i =0; i < tamAqui; i++){

        for(int j =0; j < tamAqui; j++){

            fscanf(arquivo, "%d ", &mat2[i][j]);

        }
        //fscanf(arquivo, "%c", &lixo);

    }

    salvarMatAtual(mat2, valoresAqui, usuario);

    fclose(arquivo);
    liberaMatriz(mat2, tamAqui);
    return tamAqui;
    
}