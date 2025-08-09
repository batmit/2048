#ifndef FUNCOES_H

#define FUNCOES_H


// Struct
typedef struct {
    
    int n, m;

}Mat;

//funcoes adversas
char conversorMM(char letra);
void limpar_buffer(void);

//menu
char imprimeMenu(void);
char lerMenu(void);
void sairJogo(void);
Mat novoJogo(void);

//jogo
void jogo(int **matriz, Mat valores);

//matriz
int **criaMatriz(Mat valores);
void liberaMatriz(int **matriz, int n);
void imprimeMatriz(int **matriz, Mat valores);
void inicializaMatriz(int **matriz, Mat valores);
void impressaoPersonalizada(int n);

#endif