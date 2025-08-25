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

/*int rankingDatLer(void){

    int quatro, cinco, seis, cont = 0;
    long salvarPosicao;
    char letras;
    FILE *arquivoLer = fopen("ranking.dat", "rb");
    if(arquivoLer == NULL){
        printf("ERRO");
        return 1;
    }

    fread(&quatro, sizeof(int), 1, arquivoLer);
    fread(&cinco, sizeof(int), 1, arquivoLer);
    fread(&seis, sizeof(int), 1, arquivoLer);
    

    printf("Ranking Atualizado: \n");

    if(quatro > 0){
        char **vetQuatro;
        char **quatroNum;
        quatroNum = malloc(quatro * sizeof(char*));
        vetQuatro = malloc(quatro * sizeof(char*));
        for(int j = 0; j < quatro; j++){
            cont = 0;
            salvarPosicao = ftell(arquivoLer);

        
            while(1){
                fread(&letras, sizeof(char), 1, arquivoLer);
                if(letras != '\0'){
                    cont++;    
                }else{
                    cont++;
                    break;
                }
            }

            vetQuatro[j] = malloc(cont * sizeof(char));
            fseek(arquivoLer, salvarPosicao, SEEK_SET);
        
            fread(vetQuatro[j], sizeof(char), cont, arquivoLer);

            cont = 0;
            salvarPosicao = ftell(arquivoLer);

        
            while(1){
                fread(&letras, sizeof(char), 1, arquivoLer);
                if(letras < '1' && letras >'9'){
                    break;    
                }else{
                    cont++;
                }
            }
            
            quatroNum[j] = malloc(cont * sizeof(char));

            fseek(arquivoLer, salvarPosicao, SEEK_SET);


            fread(quatroNum[j], sizeof(char), cont, arquivoLer);



        }
        printf("Top %d de 4x4: \n", quatro);

        for(int i = 0; i < quatro; i++){

            printf("%s %s\n", vetQuatro[i], quatroNum[i]);
            free(vetQuatro[i]);

        }

        free(vetQuatro);
        free(quatroNum);


    }

    if(cinco > 0){
        char **vetCinco;
        char **cincoNum;
        cincoNum = malloc(cinco * sizeof(char*));
        vetCinco = malloc(cinco * sizeof(char*));
        for(int j = 0; j < cinco; j++){
            cont = 0;
            salvarPosicao = ftell(arquivoLer);

        
            while(1){
                fread(&letras, sizeof(char), 1, arquivoLer);
                if(letras != '\0'){
                    cont++;    
                }else{
                    cont++;
                    break;
                }
            }

            vetCinco[j] = malloc(cont * sizeof(char));
            fseek(arquivoLer, salvarPosicao, SEEK_SET);
        
            fread(vetCinco[j], sizeof(char), cont, arquivoLer);
            
            cont = 0;
            salvarPosicao = ftell(arquivoLer);

        
            while(1){
                fread(&letras, sizeof(char), 1, arquivoLer);
                if(letras < '1' && letras >'9'){
                    break;    
                }else{
                    cont++;
                }
            }
            
            cincoNum[j] = malloc(cont * sizeof(char));

            fseek(arquivoLer, salvarPosicao, SEEK_SET);


            fread(cincoNum[j], sizeof(char), cont, arquivoLer);


        }

        printf("Top %d de 5x5: \n", cinco);

        for(int i = 0; i < cinco; i++){

            printf("%s %s\n", vetCinco[i], cincoNum[i]);
            free(vetCinco[i]);
        }
        free(vetCinco);
        free(cincoNum);


    }

    if(seis > 0){
        char **vetSeis;
        char **seisNum;
        seisNum = malloc(seis * sizeof(char*));
        vetSeis = malloc(seis * sizeof(char*));
        for(int j = 0; j < seis; j++){
            
            cont = 0;
            salvarPosicao = ftell(arquivoLer);

        
            while(1){
                fread(&letras, sizeof(char), 1, arquivoLer);
                if(letras != '\0'){
                    cont++;    
                }else{
                    cont++;
                    break;
                }
            }

            vetSeis[j] = malloc(cont * sizeof(char));
            fseek(arquivoLer, salvarPosicao, SEEK_SET);
        
            fread(vetSeis[j], sizeof(char), cont, arquivoLer);
            
            cont = 0;
            salvarPosicao = ftell(arquivoLer);

        
            while(1){
                fread(&letras, sizeof(char), 1, arquivoLer);
                if(letras < '1' && letras >'9'){
                    break;    
                }else{
                    cont++;
                }
            }
            
            seisNum[j] = malloc(cont * sizeof(char));

            fseek(arquivoLer, salvarPosicao, SEEK_SET);


            fread(seisNum[j], sizeof(char), cont, arquivoLer);


        }

        printf("Top %d de 6x6: \n", seis);

        for(int i = 0; i < seis; i++){

            printf("%s %s\n", vetSeis[i], seisNum[i]);
            free(vetSeis[i]);
        }
        free(vetSeis);
        free(seisNum);


    }

    fclose(arquivoLer);

    return 0;


}*/

int rankingDatLer(){
    
    int quatro, cinco, seis;
    FILE *arquivoLer = fopen("ranking.dat", "rb");
    if(arquivoLer == NULL){
        printf("ERRO");
        return 1;
    }

    fread(&quatro, sizeof(int), 1, arquivoLer);
    fread(&cinco, sizeof(int), 1, arquivoLer);
    fread(&seis, sizeof(int), 1, arquivoLer);

    printf("Valores do ranking: \n");

    if(quatro > 0){
        printf("%d valores 4x4:\n", quatro);

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
        printf("%d valores 5x5:\n", cinco);

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
        printf("%d valores 6x6:\n", seis);

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

    fclose(arquivoLer);
    return 0;

}

int rankingDatAtualizar(User usuario, Mat matrizValues){

    int quatro, cinco, seis;
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


void escreverRanking(void){

    int num = 4, pontuacao = 3932156;
    char string1[] = "Penelope 'Penny' Hofstadter";
    char string2[] = "George Boole";
    char string3[] = "Albert Einstein";
    char string4[] = "Stephen Hawking";
    char string5[] = "Carl Friedrich Gauss";
    char string6[] = "Isaac Newton";

    FILE *arquivo = fopen("ranking.dat", "wb");

    fwrite(&num, sizeof(int), 1, arquivo);
    num = 0;
    fwrite(&num, sizeof(int), 1, arquivo);
    num = 2;
    fwrite(&num, sizeof(int), 1, arquivo);

    fwrite(&string1, sizeof(char), 29, arquivo);
    fwrite(&pontuacao, sizeof(int), 1, arquivo);
    pontuacao = 99072;
    fwrite(&string2, sizeof(char), 29, arquivo);
    fwrite(&pontuacao, sizeof(int), 1, arquivo);
    pontuacao = 78708;
    fwrite(&string3, sizeof(char), 29, arquivo);
    fwrite(&pontuacao, sizeof(int), 1, arquivo);
    pontuacao = 47652;
    fwrite(&string4, sizeof(char), 29, arquivo);
    fwrite(&pontuacao, sizeof(int), 1, arquivo);
    pontuacao = 212992;
    fwrite(&string5, sizeof(char), 29, arquivo);
    fwrite(&pontuacao, sizeof(int), 1, arquivo);
    pontuacao = 78708;
    fwrite(&string6, sizeof(char), 29, arquivo);
    fwrite(&pontuacao, sizeof(int), 1, arquivo);



}

int main(){

    //User usuario = {"DanielFals", 100, 0, 0};
    //Mat matriz = {5, 5};
    
    //escreverRanking();
    //rankingDatAtualizar(usuario, matriz);
    //rankingDatAtualizar(usuario, matriz);


    rankingDatLer();


}