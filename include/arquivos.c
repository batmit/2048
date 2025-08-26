// Daniel Matos Falcão
//21.1.4008
#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include <string.h>
#include "cores.h"
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

// SALVAR O JOGO NO ARQUIVO
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

// CARREGA O JOGO NO ARQUIVO
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

// LE O RANKING
int rankingDatLer(void){
    char fim;
    int quatro, cinco, seis;
    FILE *arquivoLer = fopen("ranking.dat", "rb");
    if(arquivoLer == NULL){
        printf("ERRO");
        return 1;
    }

    fread(&quatro, sizeof(int), 1, arquivoLer);
    fread(&cinco, sizeof(int), 1, arquivoLer);
    fread(&seis, sizeof(int), 1, arquivoLer);

    printf(BOLD(YELLOW("\n\nValores do ranking: \n")));

    if(quatro > 0){
        printf("\n\n%d valores 4x4:\n", quatro);

        int *valoresQuatro;
        char **quatroMat;
        quatroMat = malloc(quatro * sizeof(char*));
        valoresQuatro = malloc(quatro * sizeof(int));
        for(int i = 0; i < quatro; i++){
            quatroMat[i] = malloc(29 * sizeof(char));
        }

        for(int i = 0; i < quatro; i++){
            fread(quatroMat[i], sizeof(char), 29, arquivoLer);
            fread(&valoresQuatro[i], sizeof(int), 1, arquivoLer);
            printf("%s %d\n", quatroMat[i], valoresQuatro[i]);

        }

        for(int i = 0; i < quatro; i++){
            free(quatroMat[i]);
        }
        free(quatroMat);
        free(valoresQuatro);

    }
    if(cinco > 0){
        printf("\n\n%d valores 5x5:\n", cinco);

        int *valoresCinco;
        char **cincoMat;
        cincoMat = malloc(cinco * sizeof(char*));
        valoresCinco = malloc(cinco * sizeof(int));
        for(int i = 0; i < cinco; i++){
            cincoMat[i] = malloc(29 * sizeof(char));
        }

        for(int i = 0; i < cinco; i++){
            fread(cincoMat[i], sizeof(char), 29, arquivoLer);
            fread(&valoresCinco[i], sizeof(int), 1, arquivoLer);
            printf("%s %d\n", cincoMat[i], valoresCinco[i]);

        }

        for(int i = 0; i < cinco; i++){
            free(cincoMat[i]);
        }
        free(cincoMat);
        free(valoresCinco);

    }

    if(seis > 0){
        printf("\n\n%d valores 6x6:\n", seis);

        int *valoresSeis;
        char **seisMat;
        seisMat = malloc(seis * sizeof(char*));
        valoresSeis = malloc(seis * sizeof(int));
        for(int i = 0; i < seis; i++){
            seisMat[i] = malloc(29 * sizeof(char));
        }

        for(int i = 0; i < seis; i++){
            fread(seisMat[i], sizeof(char), 29, arquivoLer);
            fread(&valoresSeis[i], sizeof(int), 1, arquivoLer);
            printf("%s %d\n", seisMat[i], valoresSeis[i]);

        }

        for(int i = 0; i < seis; i++){
            free(seisMat[i]);
        }
        free(seisMat);
        free(valoresSeis);

    }

    printf("\nDigite qualquer tecla para continuar: ");
    scanf("%c", &fim);

    fclose(arquivoLer);
    return 0;

}

// ATUALIZA O RANKING
int rankingDatAtualizar(User usuario, Mat matrizValues){

    int quatro, cinco, seis;
    // PRIMEIRAMENTE EU LEIO TODOS OS VALORE E COLOCO NUM VETOR NUMÉRICO E NUM VETOR DE STRINGS
    FILE *arquivoLerTudo = fopen("ranking.dat", "rb");
    if(arquivoLerTudo == NULL){
        printf("ERRO");
        return 1;
    }
    


    fread(&quatro, sizeof(int), 1, arquivoLerTudo);
    fread(&cinco, sizeof(int), 1, arquivoLerTudo);
    fread(&seis, sizeof(int), 1, arquivoLerTudo);

    int total = quatro+cinco+seis;

    char **totalNomes = malloc(total * sizeof(char*));
    for(int i = 0; i < total; i++){
        totalNomes[i] =  malloc(29 * sizeof(char));
        memset(totalNomes[i], 0, 29);
    }
    int *totalValues = malloc(total * sizeof(int));

    for(int i = 0; i < total; i++){
        fread(totalNomes[i], sizeof(char), 29, arquivoLerTudo);
        fread(&totalValues[i], sizeof(int), 1, arquivoLerTudo);  
    }
    fclose(arquivoLerTudo);

    //=================================================================
    //agora eu crio vetores individuais para cada valor, 4x4, 5x5, 6x6
    FILE *arquivoLer = fopen("ranking.dat", "rb");
    if(arquivoLer == NULL){
        printf("ERRO");
        return 1;
    }
    fread(&quatro, sizeof(int), 1, arquivoLer);
    fread(&cinco, sizeof(int), 1, arquivoLer);
    fread(&seis, sizeof(int), 1, arquivoLer);

    int *valoresQuatro;
    char **quatroMat;
    quatroMat = malloc(quatro * sizeof(char*));
    valoresQuatro = malloc(quatro * sizeof(int));
    for(int i = 0; i < quatro; i++){
        quatroMat[i] = malloc(29 * sizeof(char));
        memset(quatroMat[i], 0, 29);
    }

    for(int i = 0; i < quatro; i++){
        fread(quatroMat[i], sizeof(char), 29, arquivoLer);
        fread(&valoresQuatro[i], sizeof(int), 1, arquivoLer);

    }


  

    int *valoresCinco;
    char **cincoMat;
    cincoMat = malloc(cinco * sizeof(char*));
    valoresCinco = malloc(cinco * sizeof(int));
    for(int i = 0; i < cinco; i++){
        cincoMat[i] = malloc(29 * sizeof(char));
        memset(cincoMat[i], 0, 29);
    }

    for(int i = 0; i < cinco; i++){
        fread(cincoMat[i], sizeof(char), 29, arquivoLer);
        fread(&valoresCinco[i], sizeof(int), 1, arquivoLer);

    }



    int *valoresSeis;
    char **seisMat;
    seisMat = malloc(seis * sizeof(char*));
    valoresSeis = malloc(seis * sizeof(int));
    for(int i = 0; i < seis; i++){
        seisMat[i] = malloc(29 * sizeof(char));
        memset(seisMat[i], 0, 29);

    }

    for(int i = 0; i < seis; i++){
        fread(seisMat[i], sizeof(char), 29, arquivoLer);
        fread(&valoresSeis[i], sizeof(int), 1, arquivoLer);

    }

    fclose(arquivoLer);
    

    FILE *arquivoEscrever =  fopen("ranking.dat", "wb");
    if(arquivoEscrever == NULL){
        printf("ERRO");
        return 1;
    }
    if(matrizValues.n == 4 && quatro < 10){
        quatro++;
        fwrite(&quatro, sizeof(int), 1, arquivoEscrever);
        fwrite(&cinco, sizeof(int), 1, arquivoEscrever);
        fwrite(&seis, sizeof(int), 1, arquivoEscrever);

        quatro--;
        int cont = 0;
        while(1){
            
            if(cont == quatro){
                break;
            }

            if(valoresQuatro[cont] <= usuario.score){

                break;

            }


            cont++;

        }

        for(int i = 0; i < cont; i++){
            fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
            fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
        }

        fwrite(usuario.nome, sizeof(char), 29, arquivoEscrever);
        fwrite(&usuario.score, sizeof(int), 1, arquivoEscrever);

        for(int i = cont; i < total; i++){
            fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
            fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 
        }


    }else if(matrizValues.n == 4 && quatro == 10){
        fwrite(&quatro, sizeof(int), 1, arquivoEscrever);
        fwrite(&cinco, sizeof(int), 1, arquivoEscrever);
        fwrite(&seis, sizeof(int), 1, arquivoEscrever);
        int cont = 0;
        while(1){

            if(cont == quatro){
                break;
            }
            if(valoresQuatro[cont] <= usuario.score){

                break;

            }


            cont++;

        }
        if(cont == quatro){

            for(int i = 0; i < total; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

        }else{

        
            for(int i = 0; i < cont; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

            fwrite(usuario.nome, sizeof(char), 29, arquivoEscrever);
            fwrite(&usuario.score, sizeof(int), 1, arquivoEscrever);
            for(int i = cont; i < quatro -1; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 

            }

            for(int i = quatro ; i < total; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 

            }


        }



    }else if(matrizValues.n == 5 && cinco < 10){
        cinco++;
        fwrite(&quatro, sizeof(int), 1, arquivoEscrever);
        fwrite(&cinco, sizeof(int), 1, arquivoEscrever);
        fwrite(&seis, sizeof(int), 1, arquivoEscrever);
        cinco--;

        int cont = 0;

        while(1){
            if(cont == cinco){
                break;
            }

            if(valoresCinco[cont] <= usuario.score){
                break;
            }

            cont++;

        }

        for(int i = 0; i < quatro + cont; i++){
            fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
            fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
        }
        fwrite(usuario.nome, sizeof(char), 29, arquivoEscrever);
        fwrite(&usuario.score, sizeof(int), 1, arquivoEscrever);
        for(int i = quatro + cont; i < total; i++){
            fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
            fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 
        }

    }else if(matrizValues.n == 5 && cinco == 10){

        fwrite(&quatro, sizeof(int), 1, arquivoEscrever);
        fwrite(&cinco, sizeof(int), 1, arquivoEscrever);
        fwrite(&seis, sizeof(int), 1, arquivoEscrever);
        int cont = 0;
        while(1){
            if(cont == cinco){
                break;
            }
            if(valoresCinco[cont] <= usuario.score){

                break;

            }


            cont++;

        }
        if(cont == cinco){
                for(int i = 0; i < total; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

        }else{
            for(int i = 0; i < quatro+cont; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

            fwrite(usuario.nome, sizeof(char), 29, arquivoEscrever);
            fwrite(&usuario.score, sizeof(int), 1, arquivoEscrever);
                
            for(int i = quatro + cont; i < quatro+cinco -1; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 

            }
            for(int i = quatro + cinco; i < total ; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 

            }

        }




    }else if(matrizValues.n == 6 && seis < 10){

        seis++;
        fwrite(&quatro, sizeof(int), 1, arquivoEscrever);
        fwrite(&cinco, sizeof(int), 1, arquivoEscrever);
        fwrite(&seis, sizeof(int), 1, arquivoEscrever);
        seis--;

        int cont = 0;

        while(1){
            
            if(cont == seis){
                break;
            }
            if(valoresSeis[cont] <= usuario.score){
                break;


            }
            
            cont++;
        }

        for(int i = 0; i < quatro + cont + cinco; i++){
            fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
            fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
        }
        fwrite(usuario.nome, sizeof(char), 29, arquivoEscrever);
        fwrite(&usuario.score, sizeof(int), 1, arquivoEscrever);
        for(int i = quatro + cont + cinco; i < total; i++){
            fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
            fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 
        }



    } else if(matrizValues.n == 6 && seis == 10){


        fwrite(&quatro, sizeof(int), 1, arquivoEscrever);
        fwrite(&cinco, sizeof(int), 1, arquivoEscrever);
        fwrite(&seis, sizeof(int), 1, arquivoEscrever);
        int cont = 0;
        while(1){
            if(cont == seis){
                break;
            }
            if(valoresSeis[cont] <= usuario.score){

                break;

            }


            cont++;

        } if(cont == seis){
            for(int i = 0; i < total; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

        }else{
            for(int i = 0; i < cinco + quatro+cont; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

            fwrite(usuario.nome, sizeof(char), 29, arquivoEscrever);
            fwrite(&usuario.score, sizeof(int), 1, arquivoEscrever);
            
            for(int i = cinco+quatro+cont; i < cinco + quatro+seis -1; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever);
            }

            for(int i = cinco +quatro + seis; i < total; i++){
                fwrite(totalNomes[i], sizeof(char), 29, arquivoEscrever);
                fwrite(&totalValues[i], sizeof(int), 1, arquivoEscrever); 

            }


        }





    }


    for(int i = 0; i < quatro; i++){
        free(quatroMat[i]);
    }
    free(quatroMat);
    free(valoresQuatro);

    
    for(int i = 0; i < cinco; i++){
        free(cincoMat[i]);
    }
    free(cincoMat);
    free(valoresCinco);

    
    for(int i = 0; i < seis; i++){
        free(seisMat[i]);
    }
    free(seisMat);
    free(valoresSeis);

    for(int i = 0; i < total; i++){
        free(totalNomes[i]);
    }
    free(totalNomes);
    free(totalValues);

 

    fclose(arquivoEscrever);

    return 0;
    
}