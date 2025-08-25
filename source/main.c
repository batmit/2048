#include<stdio.h>
#include<stdlib.h>
#include "../include/funcoes.h"
#include<time.h>
#include<math.h>
#include<string.h>
int main(){
    int **matriz;
    Mat tamanhoMat = {0, 0};
    int **matrizBackUp; // usada para carregar jogo atual, é sempre atualizada pela função clonar
    int terminou = 0; // para ver se o usuário ja terminou ou não
    Mat backUp = {6, 6};
    matrizBackUp = criaMatriz(backUp);
    inicializaMatriz(matrizBackUp, backUp, 0);
    User usuario = {"New_User", 0, 0, 0};
    User usuarioLixo = {"New_User", 0, 0, 0};// várias funções pedem usuário por parâmetro, aí eu crio o lixo só pra não atrapalhar
    int arquivoBinario = lerTam();
    if(arquivoBinario){
        lerDat(matrizBackUp, &usuarioLixo); 

    }

    while(1){
        
        char answer = imprimeMenu();
        
        switch (answer){
            case 'R':
                salvarMatAtual(matrizBackUp, tamanhoMat, &usuario);
                sairJogo();
                break;
            case 'N':
                Mat choice = novoJogo();

                printf("\nDigite seu nome de usuário: ");
                fgets(usuario.nome, 64, stdin);
                eliminaBarran(usuario.nome);
                matriz = criaMatriz(choice);
                inicializaMatriz(matriz, choice, 0);
                jogo(matriz, choice, &usuario, 1, &terminou);

                clonarMatrizBackUp(matrizBackUp, matriz, choice);
                liberaMatriz(matriz, choice.n);
                tamanhoMat = choice;
                break;
            case 'J':
                //se tiver jogo salvo no arquivo binário
                int tam = lerTam();
                if(tam){
                    Mat tamforever = {0,0};
                    //Se o jogo já tiver iniciado com tamanho definido
                    if(tamanhoMat.n != 0 ){
                        tamforever.n = tamanhoMat.n;
                        tamforever.m =  tamanhoMat.m;
                    }else{
                        tamforever.n = tam;
                        tamforever.m = tam;
                        tamanhoMat = tamforever;
                    }

                    matriz = criaMatriz(tamforever);
                    //Crio o clone só para verificar se tem posições livres
                    int **posicoesLivresClone;
                    posicoesLivresClone = criaMatriz(tamforever);

                    //if(posicoesLivres(matrizBackUp, tamforever, posicoesLivresClone) != (tamforever.n*tamforever.n)){
                    clonarMatrizBackUp(matriz, matrizBackUp, tamforever);

                    //}else{
                    //    lerDat(matriz, &usuario);
                    //}


                    jogo(matriz, tamforever, &usuario, 0, &terminou);
                    liberaMatriz(posicoesLivresClone, tamforever.n);

                    clonarMatrizBackUp(matrizBackUp, matriz, tamforever);

                    liberaMatriz(matriz, tamforever.n);
                }else{
                    limparTerminal();
                    printf("\nERRO\nVocê ainda não tem um jogo iniciado");
                }



                break;
            
            case 'A':
                Ajuda();
                break;

            case 'S':
                int tam2 = lerTam(); // ve se tem arquivo binário iniciado
                if(tam2){
                    Mat compTam;
                    // mesma verificação se já tem um jogo iniciado com tamanho definido
                    if(tamanhoMat.n != 0 ){
                        compTam.n = tamanhoMat.n;
                        compTam.m =  tamanhoMat.m;
                    }else{
                        compTam.n = tam2;
                        compTam.m = tam2;

                    }

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
                        //Matriz que pega a última jogada
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
                    jogo(matriz, tamanhoMat, &usuario, 0, &terminou);
                    clonarMatrizBackUp(matrizBackUp, matriz, tamanhoMat);
                    liberaMatriz(matriz, tamanho);
                    fclose(arquivo);

                }else{
                    limparTerminal();
                    printf("\nERRO\nNão foi encontrado nenhum arquivo com esse nome");                    
                }



                break;
            case 'M':
                rankingDatLer();
                limpar_buffer();
            default:
                break;
            
        }

    }
       


    liberaMatriz(matrizBackUp, 6);

    return 0;
}