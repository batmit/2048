#include<stdio.h>
#include<stdlib.h>
#include "../include/funcoes.h"
#include<time.h>
#include<math.h>
#include<string.h>
int main(){
    int **matriz;
    Mat tamanhoMat = {0, 0};
    int **matrizBackUp;
    Mat backUp = {6, 6};
    matrizBackUp = criaMatriz(backUp);
    inicializaMatriz(matrizBackUp, backUp, 0);
    User usuario = {"New_User", 0, 0, 0};
    User usuarioLixo = {"New_User", 0, 0, 0};
    int arquivoBinario = lerTam();
    if(arquivoBinario){

        lerDat(matrizBackUp, &usuarioLixo);

    }

    while(1){
        
        char answer = imprimeMenu();
        
        switch (answer){
            case 'R':
                sairJogo();
                break;
            case 'N':
                Mat choice = novoJogo();
                matriz = criaMatriz(choice);
                inicializaMatriz(matriz, choice, 0);
                jogo(matriz, choice, &usuario, 1);

                clonarMatrizBackUp(matrizBackUp, matriz, choice);
                liberaMatriz(matriz, choice.n);
                tamanhoMat = choice;
                break;
            case 'J':

                int tam = lerTam();
                if(tam){
                    Mat tamforever = {0,0};
                    if(tamanhoMat.n != 0 ){
                        tamforever.n = tamanhoMat.n;
                        tamforever.m =  tamanhoMat.m;
                    }else{
                        tamforever.n = tam;
                        tamforever.m = tam;

                    }
                    matriz = criaMatriz(tamforever);
                    int **posicoesLivresClone;
                    posicoesLivresClone = criaMatriz(backUp);
                    //User usuario_volta = {"New_User", 0, 0, 0};
                    //if(posicoesLivres(matrizBackUp, backUp, posicoesLivresClone) != 36){
                        clonarMatrizBackUp(matriz, matrizBackUp, tamforever);

                    //}else{
                    //    lerDat(matriz, &usuario);

                    //}
                    jogo(matriz, tamforever, &usuario, 0);
                    liberaMatriz(posicoesLivresClone, 6);

                    clonarMatrizBackUp(matrizBackUp, matriz, tamforever);

                    liberaMatriz(matriz, tam);
                }else{
                    limparTerminal();
                    printf("\nERRO\nVocê ainda não tem um jogo iniciado");
                }



                break;
            
            case 'A':
                Ajuda();
                break;

            case 'S':
                int tam2 = lerTam();
                if(tam2){
                    Mat compTam;
                    if(tamanhoMat.n != 0 ){
                        compTam.n = tamanhoMat.n;
                        compTam.m =  tamanhoMat.m;
                    }else{
                        compTam.n = tam2;
                        compTam.m = tam2;

                    }
                   //Mat compTam = {tam2, tam2};

                    printf("Deseja salvar o jogo(Sim, Não)?: ");
                    int verify1 = verificarSimNao();

                    if(verify1 == 0){
                        char nomeArquivo[27];
                        limpar_buffer();
                        if(!strcmp(usuario.nome, "New_User")){

                            printf("Digite seu nome de usuário: ");
                            fgets(usuario.nome, 27, stdin);
                            eliminaBarran(usuario.nome);

                        }
                        printf("Digite o nome do arquivo(sem a extensão): ");
                        fgets(nomeArquivo, 27, stdin);
                        eliminaBarran(nomeArquivo);
                        strcat(nomeArquivo, ".txt");
                        int **comp;
                        comp = criaMatriz(compTam);
                        lerDat(comp, &usuarioLixo);    

                        salvarJogo(matrizBackUp, comp, compTam, &usuario,nomeArquivo);
                        liberaMatriz(comp, tam2);    
                    }
  
                }else{
                    limparTerminal();
                    printf("\nERRO\nVocê ainda não tem um jogo iniciado");                    
                }
                break;  
                
            case 'C':
                limparTerminal();
                char nomeArquivo[27];
                printf("Digite o nome do arquivo que se encontra o jogo(sem txt): ");
                fgets(nomeArquivo, 27, stdin);
                int tamanho;
                eliminaBarran(nomeArquivo);
                strcat(nomeArquivo, ".txt");
                FILE *arquivo = fopen(nomeArquivo, "r");
                if(arquivo != NULL){
                    fscanf(arquivo, "%d", &tamanho);
                    Mat tamanhoMat = {tamanho, tamanho};

                    matriz = criaMatriz(tamanhoMat);

                    carregarJogo(matriz, &usuario,nomeArquivo);
                    jogo(matriz, tamanhoMat, &usuario, 0);
                    clonarMatrizBackUp(matrizBackUp, matriz, tamanhoMat);
                    liberaMatriz(matriz, tamanho);
                }else{
                    limparTerminal();
                    printf("\nERRO\nNão foi encontrado nenhum arquivo com esse nome");                    
                }
                fclose(arquivo);



                break;
            default:
                break;
            
        }

    }
       


    liberaMatriz(matrizBackUp, 6);

    return 0;
}