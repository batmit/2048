#include<stdio.h>
#include<stdlib.h>
//#include "funcoes.h"

int salvarMatAtual();

int main(){

    FILE *arquivo;
    arquivo = fopen("atual.dat", "wb");
    int i = 10;
    if(arquivo == NULL){
        perror("Erro ao abrir o arquivo");
            
    }



    fwrite(&i, sizeof(int), 1, arquivo);
    

    fclose(arquivo);
    int res = salvarMatAtual();
    printf("%d", res);

    return 0;
}

int salvarMatAtual(){
        FILE *arquivo;
        arquivo = fopen("atual.dat", "rb");
        int c;
        fread(&c, sizeof(int), 1, arquivo);
        fclose(arquivo);
        return c;
}