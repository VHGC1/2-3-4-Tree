/**********************************************************************
    * Implementacao Arvore 2-3-4 em C++ Insercao, Busca e Remocao     *
    * Estrutura de dados II                                           *
    * Professor: William Roberto Malvezzi                             *
    * UNICEUB - 20/05/2021 - Brasilia-DF                              *
    *                                                                 *
    * Team: Brian Danilo - Engenharia de Computacao                   *
    *       Vitor Hugo  - Engenharia de computacao                    *
    *https://github.com/YGAO008/2-3-4--Tree/blob/master/2-3-4%20Tree.c*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define M 3


struct no {
	int n; /* n < M Numero de chaves no no sera sempre menor que a ordem da arvore B*/
	int chaves[M - 1]; /*matriz de chaves*/
	struct no *p[M]; /* (n + 1 ponteiros estar o em uso) */
}*root = NULL;

enum facilitador { Duplicar, erroBusca, sucesso, InserirIsso, menorChave };

void inserir(int chave);
void imprimir(struct no *root, int);
void DeletarNo(int x);
void busca(int x);
enum facilitador ins(struct no *r, int x, int* y, struct no** u);
int buscaPos(int x, int *chaveAuxiliar, int n);
enum facilitador del(struct no *r, int x);
void inorder(struct no *ptr);


