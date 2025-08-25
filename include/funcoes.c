#include<stdio.h>
#include<stdlib.h>
#include "funcoes.h"
#include "cores.h"
#include <string.h>
#include<time.h>
#include<math.h>

// FUNÇÕES ADVERSAS
void limpar_buffer(void){
   int ch;
   while ((ch = getchar()) != '\n' && ch != EOF);
}

char conversorMM(char letra){

    if(letra >='a' && letra <='z'){
        letra = letra - ('a' - 'A');
    }

    return letra;

}

void limparTerminal(void){
    system("clear");
}

//Função que verifica se o usuário vai digitar sim ou não corretamente
int verificarSimNao(void){
    while (1){
        char saida[100];
        scanf("%s", saida);
        int tam = strlen(saida);
        for(int i=0; i < tam; i++){
            saida[i] = conversorMM(saida[i]);
        }
        
        if(!strcmp(saida, "SIM")){
            return 0;
        } else if(!strcmp(saida, "NãO") || !strcmp(saida, "NAO")){
            limpar_buffer();
            return 1;
        } else{
            printf(BOLD(RED("\nMensagem inválida\n :")));
            limpar_buffer();
        }
    }
    

}

void eliminaEspacos(char *comando, int tam){

    for(int i =0; i < tam; i++){
        if(comando[i] == ' '){

            for(int j = i; j < (tam -1); j++){
                comando[j] = comando[j+1];
            }
            tam--;
            i = 0;
        }
    }

}

void eliminaBarran(char text[27]){

    int tam = strlen(text);

    if(text[tam -1] == '\n'){
        text[tam -1] = '\0';
    }
    

}



//TUDO RELACIONADO AO MENU
char imprimeMenu(void){

    
    
    printf(BG_BLACK(WHITE(BOLD("\n------------------2048---------------------"))));

    printf(BOLD(RED("\n(R) - Sair")));
    printf(BOLD(BLUE("\n(N) - Novo jogo")));
    printf(CYAN(BOLD("\n(J) - Continuar o jogo atual")));
    printf(BOLD(MAGENTA("\n(C) - Carregar um jogo salvo")));
    printf(BOLD("\n(S) - Salvar o jogo atual"));
    printf(GREEN("\n(M) - Mostrar o ranking"));
    printf(BOLD(YELLOW("\n(A) - Ajudar com as instruções de como jogar\n: ")));
    
    return lerMenu();

}

char lerMenu(void){

    char answer;
    char extra;
    
    while(1){
        
        if(scanf("%c", &answer) != 1){
            printf(BOLD(RED("ERRO")));
        };

        if(scanf("%c", &extra) == 1 && extra !='\n'){
            
            printf(BOLD(RED("\nERRO\nDigite apenas 1 caractere\n: ")));
            limpar_buffer();

        }else{

            answer = conversorMM(answer);
        
            if(answer == 'R' || answer == 'N' || answer == 'J' || answer == 'C' || answer == 'S' || answer == 'M' || answer == 'A'){
                break;
            }else{
                printf(BOLD(RED("\nVocê digitou um valor inválido, digite novamente\n: ")));
                
            }


        }
        

        
        

    }
    limparTerminal();
    return answer;


}

void sairJogo(void){

    while (1){
        char saida[10];

        printf("\nTem certeza que deseja sair?(Sim/Não): ");
        scanf("%s", saida);
        int tam = strlen(saida);
        for(int i=0; i < tam; i++){
            saida[i] = conversorMM(saida[i]);
        }
        
        if(!strcmp(saida, "SIM")){
            printf("\nObrigado por Jogar\nEXIT\n");
            exit(0);
        } else if(!strcmp(saida, "NãO") || !strcmp(saida, "NAO")){
            limpar_buffer();
            break;
        } else{
             printf(BOLD(RED("\nMensagem inválida")));
           limpar_buffer();
        }
    }
    


}

Mat novoJogo(void){
    Mat escolha;
    int choice = 0;
    char extra;
    while (choice < 4 || choice > 6){

        printf(BG_BLACK(WHITE(BOLD("\n-------------Iniciar Novo Jogo------------"))));
        printf("\n(4) Jogo padrão 4x4");
        printf("\n(5) Jogo 5x5");
        printf("\n(6)Jogo 6x6\n: ");
        
        scanf("%d", &choice);
        if( choice < 4 || choice > 6){
            printf(BOLD(RED("\nERRO\nVocê digitou um valor inválido\n")));
        }

        if(scanf("%c", &extra) == 1 && extra !='\n'){
            
            printf(BOLD(RED("\nERRO\nDigite apenas 1 valor\n")));
            limpar_buffer();

        } 

        

    }

    escolha.n = choice;
    escolha.m = choice;
    limparTerminal();
    return escolha;


 
    
}

void Ajuda(void){
    char lixo;
    limparTerminal();
    printf(BOLD("\n\nO jogo\n"));
    printf("O 2048 clássico é jogado em um tabuleiro de 4 x 4, com peças numéricas que deslizam suavemente quando o jogador as move em um dos quatro sentidos disponíveis: para cima, para baixo, à esquerda e à direita.");
    printf("\nA cada movimento, um novo número aparece aleatoriamente em um local vazio no tabuleiro (com um valor de 2 ou 4).");

    printf("\nAs peças (blocos) deslizam o mais longe possível na direção escolhida até que eles sejam interrompidos por qualquer outro bloco ou a borda do tabuleiro. Se duas peças do mesmo número colidem durante a movimentaçao, elas irão se fundir e a posição terá o valor total das duas peças que colidiram.");

    printf("\nA peça resultante não pode se fundir com outra peça novamente na mesma jogada. Blocos com pontuação maior possuem cores diferentes.");
    printf(BOLD("\nRegras"));
    printf("\nO jogo começa com duas posições aleatórias do tabuleiro preenchidas. A cada jogada, o jogador deve escolher uma direção (para cima, para baixo, para a esquerda ou para a direita).");

    printf("\nDigite qualquer tecla para continuar... ");
    scanf("%c", &lixo);
    limpar_buffer();
}


//TUDO RELACIONADO A MATRIZ

int **criaMatriz(Mat valores){

    int **matriz;

    matriz = malloc(valores.n * sizeof(int*));
    for(int i = 0; i < valores.n; i++){
        matriz[i] = malloc(valores.m * sizeof(int));
    }

    return matriz;

}

void liberaMatriz(int **matriz, int n){

    for(int i=0; i<n; i++){

        free(matriz[i]);

    }
    free(matriz);

}

void imprimeMatriz(int **matriz, Mat valores){
    char letras[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int num[6] = {1, 2, 3, 4, 5, 6};
    int cont = 0;
    printf("     ");
    for(int i=0; i< (valores.m* 8); i++){
        if(i % 8 == 0){
            printf("%d", num[cont]);
            cont++;
        }else{
            printf(" ");
        }
        
    }

    printf("\n   "TAB_TL);
    for(int i=1; i< (valores.m* 8); i++){
        if(i % 8 == 0){
            printf(TAB_TJ);
        }else{
            printf(TAB_HOR);


        }
        
    }
    printf(TAB_TR "\n");

    for(int i =0; i< valores.n; i++){
        printf(" %c ", letras[i]);
        for(int j =0; j< valores.m; j++){

            printf(TAB_VER " ");
            
            impressaoPersonalizada(matriz[i][j]);
            
        }
        printf(TAB_VER);

        if(i < valores.n - 1){
            printf("\n   ");
            printf(TAB_ML);
            for(int z = 1; z < (valores.m)*8 ; z++){
                if(z % 8 == 0){
                    printf(TAB_ML);
                }else{
                    printf(TAB_HOR);

                }
            }
            printf(TAB_MR "\n");

        }

    }
    printf("\n   "TAB_BL);
    for(int i=1; i< (valores.m*8); i++){
        if(i % 8 == 0){
            printf(TAB_BJ);
        }else{
            printf(TAB_HOR);
        }
        
    }
    printf(TAB_BR);

}

void inicializaMatriz(int **matriz, Mat valores, int valor){

    for(int i =0; i< valores.n; i++){

        for(int j =0; j< valores.m; j++){

            matriz[i][j] = valor;            

        }

    }
    

}


void impressaoPersonalizada(int n){


    if(n == 0){

        printf("      ");

    }else if(n == 2){
        printf(BLACK(BG_WHITE("   2  ")));
    }else if(n == 4){
        printf(BLACK(BG_CYAN("   4  ")));
    }else if(n == 8){
        printf(WHITE(BG_GREEN("   8  ")));
    } else if(n == 16){
        printf(WHITE(BG_MAGENTA("  16  ")));
    }else if(n == 32){
        printf(WHITE(BG_BLACK("  32  ")));
    }else if(n == 64){
        printf(WHITE(BG_RED("  64  ")));
    }else if(n == 128){
        printf(BLACK(BG_GREEN("  128 ")));
    }else if(n == 256 ){
        printf(WHITE(BG_CYAN("  256 ")));
    }else if(n == 512){
        printf(BLUE(BG_RED("  512 ")));
    }else if(n == 1024){
        printf(" %d ", n);
    }else if(n == 2048){
        printf(" %d ", n);

    }else if(n == 4096){
        printf(" %d ", n);

    }else if(n == 8192){
        printf(" %d ", n);

    }else{
        printf("%d", n);

    }

}

int comparaMatriz(int **matriz1, int **matriz2, Mat valores){
    int comp =0;

    for(int i =0; i < valores.n; i++){
        for(int j =0; j < valores.m; j++){

            if(matriz1[i][j] == matriz2[i][j]){
                comp++;
            }

        }
    }

    if(comp == (valores.n * valores.m)){
        return 0;
    }else{
        return 1;
    }


}

//Passa a matriz para a matriz BackUp na main
void clonarMatrizBackUp(int **clonarMatrizBackUp, int **matriz, Mat valores){

    for(int i =0; i < valores.m; i++){

        for(int j =0; j < valores.n; j++){

            clonarMatrizBackUp[i][j] = matriz[i][j];

        }

    }

}


void clonarMatriz(int **matriz, Mat valores, int **matrizClone){

    for(int i =0; i < valores.n; i++){

        for(int j = 0; j < valores.m; j++){
            
            matrizClone[i][j] = matriz[i][j];

        }

    }

    


}

int verificaVitoria(int **matriz, Mat valores){

    for(int i = 0; i < valores.n; i++){

        for(int j = 0; j < valores.m; j++){
            if(matriz[i][j] == 2048){
                return 0;
            }
        }

    }
    return 1;

}


/* INICIA O ARQUIVO BINÁRIO UTILIZADO PARA CARREGAR O JOGO ATUAL
void inicializarAtualDat(void){

    int **matriz;
    User lixo = {"New_User", 0, 0, 0};
    Mat testando = {6, 6};
    matriz = criaMatriz(testando);
    inicializaMatriz(matriz, testando, 0);
    salvarMatAtual(matriz, testando, &lixo);


    liberaMatriz(matriz, 6);


}*/