#ifndef FUNCOES_H

#define FUNCOES_H


#ifndef MAX
#define MAX 64
#endif

// Struct
typedef struct {
    
    int n, m;

}Mat;

typedef struct{
    char nome[MAX];
    int score, trades, undoMoves;
}User;

//funcoes adversas
char conversorMM(char letra);
void limpar_buffer(void);
void limparTerminal(void);

//menu
char imprimeMenu(void);
char lerMenu(void);
void sairJogo(void);
Mat novoJogo(void);

//jogo(no arquivo jogar)
void jogo(int **matriz, Mat valores, User *usuario);
void imprimeCabecalho(User cabecalho);
int posicoesLivres(int **matriz, Mat valores, int **posicoesLivresMat);
int sorteiaN(int **matriz, Mat valores, int **posicoesLivresMat);
int jogarparaCima(int**mat, Mat valores, User *usuario);
int jogarparaBaixo(int **matriz, Mat valores, User *usuario);
int jogarparaDireita(int **matriz, Mat valores, User *usuario);
int jogarparaEsquerda(int **matriz, Mat valores, User *usuario);

//matriz
int **criaMatriz(Mat valores);
void liberaMatriz(int **matriz, int n);
void imprimeMatriz(int **matriz, Mat valores);
void inicializaMatriz(int **matriz, Mat valores, int valor);
void impressaoPersonalizada(int n);

#endif