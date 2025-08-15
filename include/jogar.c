#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include "cores.h"
#include <string.h>
#include<math.h>
#include<time.h>



void jogo(int **matriz, Mat valores, User *usuario){
    int **posicoesLivresMat, sair = 0;
    Mat posicoesLivresStruct = {valores.n*valores.n, 3};
    srand(time(NULL));
    char comando[20];

    posicoesLivresMat = criaMatriz(posicoesLivresStruct);
    inicializaMatriz(posicoesLivresMat, posicoesLivresStruct, 37);
    if(posicoesLivres(matriz, valores, posicoesLivresMat) == valores.n*valores.n){
        sorteiaN(matriz, valores, posicoesLivresMat);
    }

    while(posicoesLivres(matriz, valores, posicoesLivresMat) != 0){
        limparTerminal();
        //IMPRESSÃO
        sorteiaN(matriz, valores, posicoesLivresMat);
        imprimeCabecalho(*usuario);
        printf("\n");
        imprimeMatriz(matriz, valores);

        while(1){
            printf("\n<a, d, s, w> - <u> - <t pos1, pos2>\nV(Voltar ao menu inicial)\n: ");
            fgets(comando, 20, stdin);
            comando[0] = conversorMM(comando[0]);
            if(comando[0] == 'W'){
                if(jogarparaCima(matriz, valores, usuario) == 1){
                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeMatriz(matriz, valores);
                }else{
                    break;
                }
            }else if(comando[0] == 'V'){
                sair = 1;
                break;
            }else if(comando[0] == 'A'){
                if(jogarparaEsquerda(matriz, valores, usuario) == 1){
                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeMatriz(matriz, valores);
                }else{
                    break;
                }
            }else if(comando[0] == 'S'){
                if(jogarparaBaixo(matriz, valores, usuario) == 1){
                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeMatriz(matriz, valores);
                }else{
                    break;
                }
            }else if(comando[0] == 'D'){
                if(jogarparaDireita(matriz, valores, usuario) == 1){
                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeMatriz(matriz, valores);
                }else{
                    break;
                }                
            }else if(comando[0] == 'T'){
                printf("T");
                break;
            }else if(comando[0] == 'U'){
                printf("U");
                break;
            }else{
                limparTerminal();
                printf(BOLD(RED("\nERRO\nValor digitado não está na lista de funções\n")));
                imprimeMatriz(matriz, valores);


            }

            if(sair){
                break;
            }



                
            }

            if(sair){
                break;
            }


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


int jogarparaCima(int **matriz, Mat valores, User *usuario){

    int cont = 0;
    int **valoresReservados;
    valoresReservados = criaMatriz(valores);

    inicializaMatriz(valoresReservados, valores, 0);

    for(int i = 1; i < valores.n; i++){
        for(int j = 0; j < valores.m; j++){

            if(matriz[i][j] != 0 && matriz[i-1][j] == 0)
            {
                matriz[i-1][j] = matriz[i][j];
                matriz[i][j] = 0;
                if(valoresReservados[i][j] != 0 && valoresReservados[i-1][j] == 0){
                    valoresReservados[i-1][j] = valoresReservados[i][j];
                    valoresReservados[i][j] = 0;
                }

                j = 0; 
                i = 1;
                cont ++;
                if(matriz[i][j] != 0 && matriz[i-1][j] == 0){
                    matriz[i-1][j] = matriz[i][j];
                    matriz[i][j] = 0;
                    if(valoresReservados[i][j] != 0 && valoresReservados[i-1][j] == 0){
                        valoresReservados[i-1][j] = valoresReservados[i][j];
                        valoresReservados[i][j] = 0;
                    }
                    cont++;
                }else if(matriz[i][j] == matriz[i -1][j] && matriz[i][j] != 0 && valoresReservados[i-1][j] == 0 && valoresReservados[i][j] == 0){
                    matriz[i-1][j] = matriz[i][j] * 2;
                    if(matriz[i-1][j] == 512){
                        usuario->trades++;
                    }else if(matriz[i-1][j] == 256){
                        usuario->undoMoves++;
                    }
                    usuario->score+= matriz[i-1][j];

                    matriz[i][j] = 0;
                    valoresReservados[i -1 ][j] = 1;
                    cont++;
                }
            }else if(matriz[i][j] == matriz[i -1][j] && matriz[i][j] != 0 && valoresReservados[i-1][j] == 0 && valoresReservados[i][j] == 0){
                matriz[i-1][j] = matriz[i][j] * 2;
                if(matriz[i-1][j] == 512){
                    usuario->trades++;
                }else if(matriz[i-1][j] == 256){
                    usuario->undoMoves++;
                }
                usuario->score+= matriz[i-1][j];
                matriz[i][j] = 0;   
                valoresReservados[i-1][j] = 1;
                i = 1;
                j = 0;
                cont++;
            }
            

        }
    }
    liberaMatriz(valoresReservados, valores.n);
    if (cont == 0){
        printf(BOLD(RED("Jogada inválida")));
        return 1;
    }else{
        return 0;
    }
}

int jogarparaBaixo(int **matriz, Mat valores, User *usuario){


    int cont = 0;
    int **valoresReservados;
    valoresReservados = criaMatriz(valores);

    inicializaMatriz(valoresReservados, valores, 0);

    for(int i = (valores.n-2); i >= 0; i--){
        for(int j = 0; j < valores.m; j++){

            if(matriz[i][j] != 0 && matriz[i+1][j] == 0)
            {
                matriz[i+1][j] = matriz[i][j];
                matriz[i][j] = 0;
                if(valoresReservados[i][j]!=0 && valoresReservados[i+1][j] == 0){
                    valoresReservados[i+1][j] = valoresReservados[i][j];
                    valoresReservados[i][j] = 0;
                }

                j = 0; 
                i = valores.n-2;
                cont ++;
                if(matriz[i][j] != 0 && matriz[i+1][j] == 0){
                    matriz[i+1][j] = matriz[i][j];
                    matriz[i][j] = 0;
                    if(valoresReservados[i][j]!=0 && valoresReservados[i+1][j] == 0){
                        valoresReservados[i+1][j] = valoresReservados[i][j];
                        valoresReservados[i][j] = 0;
                    }
                    cont++;
                }else if(matriz[i][j] == matriz[i +1][j] && matriz[i][j] != 0 && valoresReservados[i][j] == 0 && valoresReservados[i+1][j] == 0){
                    matriz[i+1][j] = matriz[i][j] * 2;
                    if(matriz[i+1][j] == 512){
                        usuario->trades++;
                    }else if(matriz[i+1][j] == 256){
                        usuario->undoMoves++;
                    }
                    usuario->score+= matriz[i+1][j];
                    matriz[i][j] = 0;
                    valoresReservados[i+1][j] = 1;
                    cont++;
                }
            }else if(matriz[i][j] == matriz[i +1][j] && matriz[i][j] != 0 && valoresReservados[i][j] == 0 && valoresReservados[i+1][j] == 0){
                matriz[i+1][j] = matriz[i][j] * 2;
                if(matriz[i+1][j] == 512){
                    usuario->trades++;
                }else if(matriz[i+1][j] == 256){
                    usuario->undoMoves++;
                }
                usuario->score+= matriz[i+1][j];

                matriz[i][j] = 0;
                valoresReservados[i+1][j] = 1;
                i = valores.n-2;
                j = 0;
                cont++;
            }
            

        }
    }
    liberaMatriz(valoresReservados, valores.n);
    if (cont == 0){
        printf(BOLD(RED("Jogada inválida")));
        return 1;
    }else{
        return 0;
    }
}



int jogarparaDireita(int **matriz, Mat valores, User *usuario){

    int cont = 0;
    int **valoresReservados;
    valoresReservados = criaMatriz(valores);

    inicializaMatriz(valoresReservados, valores, 0);

    for(int i = 0; i < valores.n; i++){
        for(int j = (valores.m-2); j >= 0; j--){

            if(matriz[i][j] != 0 && matriz[i][j+1] == 0)
            {
                matriz[i][j+1] = matriz[i][j];
                matriz[i][j] = 0;

                if(valoresReservados[i][j] != 0 && valoresReservados[i][j+1] == 0){
                    valoresReservados[i][j+1] = valoresReservados[i][j];
                    valoresReservados[i][j] = 0;
                }

                j = valores.m-2; 
                i = 0;
                cont ++;
                if(matriz[i][j] != 0 && matriz[i][j+1] == 0){
                    matriz[i][j+1] = matriz[i][j];
                    matriz[i][j] = 0;
                    if(valoresReservados[i][j] != 0 && valoresReservados[i][j+1] == 0){
                        valoresReservados[i][j+1] = valoresReservados[i][j];
                        valoresReservados[i][j] = 0;
                    }
                    cont++;
                }else if(matriz[i][j] == matriz[i][j+1] && matriz[i][j] != 0 && valoresReservados[i][j] == 0 && valoresReservados[i][j+1] == 0){
                    matriz[i][j+1] = matriz[i][j] * 2;
                    if(matriz[i][j+1] == 512){
                        usuario->trades++;
                    }else if(matriz[i][j+1] == 256){
                        usuario->undoMoves++;
                    }
                    usuario->score+= matriz[i][j+1];
                    matriz[i][j] = 0;
                    valoresReservados[i][j+1] = 1;
                    cont++;
                }
            }else if(matriz[i][j] == matriz[i][j+1] && matriz[i][j] != 0 && valoresReservados[i][j] == 0 && valoresReservados[i][j+1] == 0){
                matriz[i][j+1] = matriz[i][j] * 2;
                if(matriz[i][j+1] == 512){
                    usuario->trades++;
                }else if(matriz[i][j+1] == 256){
                    usuario->undoMoves++;
                }
                usuario->score+= matriz[i][j+1];

                matriz[i][j] = 0;
                valoresReservados[i][j+1] = 1;
                i = 0;
                j = valores.m-2;
                cont++;
            }
            

        }
    }
    liberaMatriz(valoresReservados, valores.n);
    if (cont == 0){
        printf(BOLD(RED("Jogada inválida")));
        return 1;
    }else{
        return 0;
    }
}

int jogarparaEsquerda(int **matriz, Mat valores, User *usuario){

    int cont = 0;
    int **valoresReservados;
    valoresReservados = criaMatriz(valores);

    inicializaMatriz(valoresReservados, valores, 0);

    for(int i = 0; i < valores.n; i++){
        for(int j = 1; j < valores.m; j++){

            if(matriz[i][j] != 0 && matriz[i][j-1] == 0)
            {
                matriz[i][j-1] = matriz[i][j];
                matriz[i][j] = 0;

                if(valoresReservados[i][j] != 0 && valoresReservados[i][j-1] == 0){
                    valoresReservados[i][j-1] = valoresReservados[i][j];
                    valoresReservados[i][j] = 0;
                }

                j = 1; 
                i = 0;
                cont ++;
                if(matriz[i][j] != 0 && matriz[i][j-1] == 0){
                    matriz[i][j-1] = matriz[i][j];
                    matriz[i][j] = 0;
                    if(valoresReservados[i][j] != 0 && valoresReservados[i][j-1] == 0){
                        valoresReservados[i][j-1] = valoresReservados[i][j];
                        valoresReservados[i][j] = 0;
                    }
                    cont++;
                }else if(matriz[i][j] == matriz[i][j-1] && matriz[i][j] != 0 && valoresReservados[i][j] == 0 && valoresReservados[i][j-1] == 0){
                    matriz[i][j-1] = matriz[i][j] * 2;
                    if(matriz[i][j-1] == 512){
                        usuario->trades++;
                    }else if(matriz[i][j-1] == 256){
                        usuario->undoMoves++;
                    }
                    usuario->score+= matriz[i][j-1];
                    matriz[i][j] = 0;
                    valoresReservados[i][j-1] = 1;
                    cont++;
                }
            }else if(matriz[i][j] == matriz[i][j-1] && matriz[i][j] != 0 && valoresReservados[i][j] == 0 && valoresReservados[i][j-1] == 0){
                matriz[i][j-1] = matriz[i][j] * 2;
                if(matriz[i][j-1] == 512){
                    usuario->trades++;
                }else if(matriz[i][j-1] == 256){
                    usuario->undoMoves++;
                }
                usuario->score+= matriz[i][j-1];

                matriz[i][j] = 0;
                valoresReservados[i][j-1] = 1;
                i = 0;
                j = 1;
                cont++;
            }
            

        }
    }
    liberaMatriz(valoresReservados, valores.n);
    if (cont == 0){
        printf(BOLD(RED("Jogada inválida")));
        return 1;
    }else{
        return 0;
    }
}