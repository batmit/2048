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