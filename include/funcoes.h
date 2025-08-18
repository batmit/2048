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
int verificarSimNao(void);
void eliminaEspacos(char *comando, int tam);

void eliminaBarran(char text[27]);


//menu
char imprimeMenu(void);
char lerMenu(void);
void sairJogo(void);
Mat novoJogo(void);
void Ajuda(void);


//jogo(no arquivo jogar)
void jogo(int **matriz, Mat valores, User *usuario, int sorteiaYN);
void imprimeCabecalho(User cabecalho);
int posicoesLivres(int **matriz, Mat valores, int **posicoesLivresMat);
int sorteiaN(int **matriz, Mat valores, int **posicoesLivresMat);
int jogarparaCima(int**mat, Mat valores, User *usuario, int printar);
int jogarparaBaixo(int **matriz, Mat valores, User *usuario, int printar);
int jogarparaDireita(int **matriz, Mat valores, User *usuario, int printar);
int jogarparaEsquerda(int **matriz, Mat valores, User *usuario, int printar);
//void salvarMatAtual(int **matriz, Mat valores);
void trocaPos(int **matriz, Mat valores, char resposta[20]);



//matriz
int **criaMatriz(Mat valores);
void liberaMatriz(int **matriz, int n);
void imprimeMatriz(int **matriz, Mat valores);
void inicializaMatriz(int **matriz, Mat valores, int valor);
void impressaoPersonalizada(int n);
int comparaMatriz(int **matriz1, int **matriz2, Mat valores);

void clonarMatriz(int **matriz, Mat valores, int **matrizClone);
int verificaVitoria(int **matriz, Mat valores);

//ARQUIVOS

void salvarMatAtual(int **matriz, Mat valores, User *usuario);
int lerDat(int **matriz, User *usuario);
int lerTam(void);

void salvarJogo(int **matriz, int **ultimaMat ,Mat valores, User *usuario, char NomeArqu[27]);

#endif