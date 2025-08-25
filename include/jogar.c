#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include "cores.h"
#include <string.h>
#include<math.h>
#include<time.h>


// FUnção do jogo em sí
void jogo(int **matriz, Mat valores, User *usuario, int sorteiaYN, int *terminou){
    
    int **posicoesLivresMat, sair = 0, jogadasInvalidas ;

    Mat posicoesLivresStruct = {valores.n*valores.n, 3};
    srand(time(NULL));
    char comando[20];
    User usuarioLixo = {"Lixo", 0, 0, 0};
    int **matrizClone;

    matrizClone = criaMatriz(valores);


    posicoesLivresMat = criaMatriz(posicoesLivresStruct);
    inicializaMatriz(posicoesLivresMat, posicoesLivresStruct, 37);
    if(posicoesLivres(matriz, valores, posicoesLivresMat) == valores.n*valores.n){
        sorteiaN(matriz, valores, posicoesLivresMat);
        //salvarMatAtual(matriz, valores, usuario);

    }


    while(1){

        jogadasInvalidas = 0;

        //VERIFICAR VITÓRIA
        if(verificaVitoria(matriz, valores) == 0 && *terminou == 0){
            *terminou = 1;

            printf("=======================================================================");
            printf(BOLD(YELLOW("\n\nMEUS PARABÉNS, VOCÊ GANHOU!\n")));
            printf("Deseja salvar o jogo(Sim, Não)?: ");
            int verify1 = verificarSimNao();

            if(verify1 == 0){
                limpar_buffer();
                char nomeArquivo[27];
                if(!strcmp(usuario->nome, "New_User")){

                    printf("Digite seu nome de usuário: ");
                    fgets(usuario->nome, 27, stdin);
                    eliminaBarran(usuario->nome);

                }
                printf("Digite o nome do arquivo(sem a extensão): ");
                fgets(nomeArquivo, 27, stdin);
                eliminaBarran(nomeArquivo);
                strcat(nomeArquivo, ".txt");
                int **comp;
                comp = criaMatriz(valores);
                lerDat(comp, &usuarioLixo);    

                salvarJogo(matriz, comp, valores, usuario,nomeArquivo);
                liberaMatriz(comp, valores.n);
            }

            printf("Deseja continuar(Sim, Não)?: ");
            int verify = verificarSimNao();                

            if(verify == 1){
                sair =1;
                //sorteiaYN =0;
                break;
            }else{
                limpar_buffer();
                limparTerminal();
                imprimeCabecalho(*usuario);
                printf("\n");
                imprimeMatriz(matriz, valores);
            }

            rankingDatAtualizar(*usuario, valores);

        }




        

        //IMPRESSÃO
        limparTerminal();
        if(sorteiaYN){
            sorteiaN(matriz, valores, posicoesLivresMat);
            if(valores.n == 6){
                //SE FOR 6X6
                sorteiaN(matriz, valores, posicoesLivresMat);

            }

        }

        //SE FOR A PRIMEIRA VEZ VAI SALVAR A MATRIZ NO ARQUIVO BINÁRIO
        if(posicoesLivres(matriz, valores, posicoesLivresMat) == (valores.n*valores.n) -2){
            //sorteiaN(matriz, valores, posicoesLivresMat);
            salvarMatAtual(matriz, valores, usuario);

        }

        imprimeCabecalho(*usuario);
        printf("\n");
        imprimeMatriz(matriz, valores);

        //VERIFICANDO CONDIÇÕES DE DERROTA

        clonarMatriz(matriz, valores, matrizClone);

        if(jogarparaBaixo(matrizClone, valores, &usuarioLixo, 0) == 1) {
            jogadasInvalidas++;
        }
        clonarMatriz(matriz, valores, matrizClone);
        if(jogarparaCima(matrizClone, valores, &usuarioLixo, 0) == 1){
            jogadasInvalidas++;
        }
        clonarMatriz(matriz, valores, matrizClone);

        if(jogarparaDireita(matrizClone, valores, &usuarioLixo, 0) == 1){
            jogadasInvalidas++;
        }
        clonarMatriz(matriz, valores, matrizClone);

        if(jogarparaEsquerda(matrizClone, valores, &usuarioLixo, 0) == 1){
            jogadasInvalidas++;
        }
        
        if(jogadasInvalidas == 4){

            if(usuario->undoMoves == 0 && usuario->trades == 0){
                printf(BOLD(RED("\nNão há jogadas válidas, você perdeu\n")));    
            
                printf("Deseja salvar o jogo(Sim, Não)?: ");
                int verify1 = verificarSimNao();

                if(verify1 == 0){
                    char nomeArquivo[27];
                    limpar_buffer();
                    if(!strcmp(usuario->nome, "New_User")){

                        printf("Digite seu nome de usuário: ");
                        fgets(usuario->nome, 27, stdin);
                        eliminaBarran(usuario->nome);

                    }
                    printf("Digite o nome do arquivo(sem a extensão): ");
                    fgets(nomeArquivo, 27, stdin);
                    eliminaBarran(nomeArquivo);
                    strcat(nomeArquivo, ".txt");
                    int **comp;
                    comp = criaMatriz(valores);
                    lerDat(comp, &usuarioLixo);    

                    salvarJogo(matriz, comp, valores, usuario,nomeArquivo);
                    liberaMatriz(comp, valores.n);
                    rankingDatAtualizar(*usuario, valores);
                }
                //COLOCAR AQUI 1 PARA SIM E 0 PARA NAO
                sair = 1;
                break;
            }            
            if(usuario->undoMoves > 0){
                printf(BOLD(BLUE("VOcê ainda pode voltar uma jogada")));
            }
            if(usuario->trades > 0){
                printf(BOLD(BLUE("Você ainda pode fazer uma troca")));
            }
                    
        }



        while(!sair){

            printf("\n<a, d, s, w> - <u> - <t pos1 pos2>\nV(Voltar ao menu inicial)\n: ");
            fgets(comando, 20, stdin);
            comando[0] = conversorMM(comando[0]);
            if(comando[0] == 'W'){
                if(temAlgoDepois(comando)){
                    clonarMatriz(matriz, valores, matrizClone);
                    if(jogarparaCima(matrizClone, valores, &usuarioLixo, 0) == 0){
                        salvarMatAtual(matriz, valores, usuario);
                        jogarparaCima(matriz, valores, usuario, 1);
                        sorteiaYN = 1;
                        break;

                    }else{
                        limparTerminal();
                        printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                        imprimeCabecalho(*usuario);
                        printf("\n");
                        imprimeMatriz(matriz, valores);
                    }


                }else{

                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores);
                }

        
            }else if(comando[0] == 'V'){
                //sorteiaYN = 0;
                sair = 1;
                break;
            }else if(comando[0] == 'A'){

                if(temAlgoDepois(comando)){
                    clonarMatriz(matriz, valores, matrizClone);
                    if(jogarparaEsquerda(matrizClone, valores, &usuarioLixo, 1) == 0){
                        salvarMatAtual(matriz, valores, usuario);
                        jogarparaEsquerda(matriz, valores, usuario, 1);
                        sorteiaYN = 1;
                        break;

                    }else{
                        limparTerminal();
                        printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                        imprimeCabecalho(*usuario);
                        printf("\n");
                        imprimeMatriz(matriz, valores);
                    }
                }else{

                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores);

                }


            }else if(comando[0] == 'S'){
                clonarMatriz(matriz, valores, matrizClone);
                if(jogarparaBaixo(matrizClone, valores, &usuarioLixo, 1) == 0){
                    salvarMatAtual(matriz, valores, usuario);
                    jogarparaBaixo(matriz, valores, usuario, 1);
                    sorteiaYN = 1;
                    break;

                }else{

                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores);
                }
            }else if(comando[0] == 'D'){

                if(temAlgoDepois(comando)){
                    clonarMatriz(matriz, valores, matrizClone);
                    if(jogarparaDireita(matrizClone, valores, &usuarioLixo, 1) == 0){
                        salvarMatAtual(matriz, valores, usuario);
                        sorteiaYN = 1;
                        jogarparaDireita(matriz, valores, usuario, 1);
                        break;
                    }else{

                        limparTerminal();
                        printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                        imprimeCabecalho(*usuario);
                        printf("\n");
                        imprimeMatriz(matriz, valores);
                    }


                }else{

                    limparTerminal();
                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores);                  

                }


            }else if(comando[0] == 'T'){
                
                if(temAlgoDepois(comando)){

                    if(verificaTrocaPos(comando)){
                    int tam_comando = strlen(comando);
                    eliminaEspacos(comando, tam_comando);
                    char vetLetras[7] = {'A', 'B', 'C', 'D', 'E', 'F'};
                    char vetNum[7] = {'1', '2', '3', '4', '5', '6'};
                    comando[1] = conversorMM(comando[1]);
                    comando[3] = conversorMM(comando[3]);
                    if(usuario->trades > 0 && comando[1] >='A' && comando[1] <= vetLetras[valores.m -1] && comando[3] >= 'A' && comando[3] <= vetLetras[valores.m -1] && comando[2] >= '1' && comando[2] <= vetNum[(valores.m -1)] && comando[4] >= '1' && comando[4] <= vetNum[(valores.m -1)]){
                        salvarMatAtual(matriz, valores, usuario);
                        trocaPos(matriz, valores, comando, usuario);
                        sorteiaYN = 0;
                        usuario->trades--;

                        break;

                    }else{
                        limparTerminal();

                        printf(BOLD(RED("\nERRO\nJogada inválidaALI\n")));
                        imprimeCabecalho(*usuario);
                        printf("\n");
                        imprimeMatriz(matriz, valores);
                        //printf("%s", comando);
                    }


                }else{
                    
                    limparTerminal();

                    printf(BOLD(RED("\nERRO\nJogada inválidaALI\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores);
                   // printf("%s", comando);


                }


                }else{
                    limparTerminal();

                    printf(BOLD(RED("\nERRO\nJogada inválida\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores);

                }

                
            }else if(comando[0] == 'U'){
                if(temAlgoDepois(comando)){
                    if(usuario->undoMoves > 0){
                        int **matrizComp;
                        matrizComp = criaMatriz(valores);
                        lerDat(matrizComp, &usuarioLixo);

                        if(comparaMatriz(matriz, matrizComp, valores)){
                            lerDat(matriz, usuario);
                            sorteiaYN = 0;
                            usuario->undoMoves--;
                            liberaMatriz(matrizComp, valores.n);

                            break;

                        
                        }else{
                            limparTerminal();
                            printf(BOLD(RED("\nJogada inválida, não existe arquivo salvo com a jogada anterior\n")));
                            imprimeCabecalho(*usuario);
                            printf("\n");
                            imprimeMatriz(matriz, valores);
                        }

                        liberaMatriz(matrizComp, valores.n);




                    }else{
                        limparTerminal();
                        printf(BOLD(RED("\nJogada inválida, você não tem movimentos de volta\n")));
                        imprimeCabecalho(*usuario);
                        printf("\n");
                        imprimeMatriz(matriz, valores);
                    }

                }else{

                    limparTerminal();
                    printf(BOLD(RED("\nJogada inválida, você não tem movimentos de volta\n")));
                    imprimeCabecalho(*usuario);
                    printf("\n");
                    imprimeMatriz(matriz, valores); 

                }

            }else{
                limparTerminal();
                printf(BOLD(RED("\nERRO\nValor digitado não está na lista de funções\n")));
                imprimeCabecalho(*usuario);
                printf("\n");
                imprimeMatriz(matriz, valores);


            }

            if(sair){
                break;
            }





                
        }



        if(sair){
            //salvarMatAtual(matriz, valores, usuario);
            //  ANALISE SE APENAS TIRANDO ISSO JÁ É SUFICIENTE
            // VOCÊ ESTÁ QUERENDO SALVAR NO TXT O JOGO ANTERIOR ATRAVES DA PPAGINA MAIN
            // PENSAR EM QUANDO SAIR DO JOGO DELETAR TUDO DO ARQUIVO BINÁRIO
            //imprimeMatriz(matriz, valores);
            break;
        }



    }


    liberaMatriz(matrizClone, valores.n);
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

//FUNÇÃO DE SORTEIO, QUE USA A FUNÇÃO POSIÇÕES LIVRES
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


int jogarparaCima(int **matriz, Mat valores, User *usuario, int printar){

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
        if(printar == 1){
            printf(BOLD(RED("Jogada inválida")));

        }
        return 1;
    }else{
        return 0;
    }
}

int jogarparaBaixo(int **matriz, Mat valores, User *usuario, int printar){


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
        if(printar == 1){
            printf(BOLD(RED("Jogada inválida")));

        }
        return 1;
    }else{
        return 0;
    }
}



int jogarparaDireita(int **matriz, Mat valores, User *usuario, int printar){

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
        if(printar == 1){
            printf(BOLD(RED("Jogada inválida")));

        }
        return 1;
    }else{
        return 0;
    }
}

int jogarparaEsquerda(int **matriz, Mat valores, User *usuario, int printar){

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
        if(printar == 1){
            printf(BOLD(RED("Jogada inválida")));

        }
        return 1;
    }else{
        return 0;
    }
}

void trocaPos(int **matriz, Mat valores, char resposta[20], User *usuario){

    char vetor[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int m1 = atoi(&resposta[2]);
    int m2 = atoi(&resposta[4]);
    int reserva = 0;
    for(int i =0; i < valores.n; i++){

        for(int j = 0; j < valores.m; j++){

            if(resposta[1] == vetor[i] && resposta[3] == vetor[j]){
                
                if(matriz[i][m1 - 1] != 0 && matriz[j][m2 - 1] != 0){
                    reserva = matriz[i][m1 - 1];
                    matriz[i][m1 - 1] = matriz[j][m2 -1]; 
                    matriz[j][m2 - 1] = reserva;


                }else{

                    printf(BOLD(RED("\nMensagem inválida\n :")));
                    usuario->trades++;

                    limpar_buffer();


                }
                

                //printf("DEU %d %d %d %d %d %d", i, m1, j, m2, matriz[i][m1], matriz[j][m2]);

            }


        }

    }

    if(reserva == 0){
        printf(BOLD(RED("\nERRO\nJogada inválida\n")));

    }

    
}

//VERIFICA SE EXISTE ALGUM ESPAÇO VAZIO APÓS A LETRA SER DIGITADA NA TROCA DE POSIÇÃO
int verificaTrocaPos(char resposta[20]){

    char vetLetras[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char vetLetrasM[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    //int salva = 0;

    for(int i = 0; resposta[i] != '\0'; i++){
        
        for(int j = 0; j < 6; j++){

            if(resposta[i] == vetLetras[j] || resposta[i] == vetLetrasM[j]){
                if(resposta[i+1] == ' '){
                    return 0;
                }
            }


        }

    }

    return 1;



}

//Função que verifica se o usuário digitou apenas um caractere ou não
int temAlgoDepois(char comando[20]){
    
    for(int i = 1; comando[i] != '\0'; i++){

        if(comando[i] != ' ' && comando[i] !='\n'){

            return 0;


        }

    }

    return 1;


}