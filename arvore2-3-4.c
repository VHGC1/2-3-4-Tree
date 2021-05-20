/**********************************************************************
    * Implementacao Arvore 2-3-4 em C Insercao, Busca e Remocao       *
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
#include "arvore2-3-4.h"


void inserir(int chave){
	struct no *novono;
	int upChave;
	enum facilitador valor;
	
	valor = ins(root, chave, &upChave, &novono);
	
	if (valor == Duplicar)
		printf("Valor ja inserido\n");
	if (valor == InserirIsso){
		
		struct no *uproot = root;
		root = malloc(sizeof(struct no));
		
		root->n = 1;
		root->chaves[0] = upChave;
		root->p[0] = uproot;
		root->p[1] = novono;
	}
}

enum facilitador ins(struct no *ptr, int chave, int *upChave, struct no **novono){
	struct no *novoPtr, *ultimoPtr;
	int pos, i, n, dividirPos;
	int novaChave, ultimachave;
	
	enum facilitador valor;
	
	if (ptr == NULL){
		*novono = NULL;
		*upChave = chave;
		return InserirIsso;
	}

	n = ptr->n;
	pos = buscaPos(chave, ptr->chaves, n);
	
	if (pos < n && chave == ptr->chaves[pos])
		return Duplicar;
	valor = ins(ptr->p[pos], chave, &novaChave, &novoPtr);
	
	if (valor != InserirIsso)
		return valor;
	
	if (n < M - 1){
		pos = buscaPos(novaChave, ptr->chaves, n);
		
		for (i = n; i>pos; i--){
			ptr->chaves[i] = ptr->chaves[i - 1];/*Mudando a chave e o ponteiro para inserir nova chave*/
			ptr->p[i + 1] = ptr->p[i];
		}
		
		ptr->chaves[pos] = novaChave;
		ptr->p[pos + 1] = novoPtr;
		++ptr->n; /*incrementando o numero de chaves no no*/
		return sucesso;
	}
	 
	if (pos == M - 1){
		ultimachave = novaChave;
		ultimoPtr = novoPtr;
	}

	else { /*Se as chaves nos nos são maximas e a posicao do no a ser inserido é a ultima*/
		ultimachave = ptr->chaves[M - 2];
		ultimoPtr = ptr->p[M - 1];
		
		for (i = M - 2; i>pos; i--){
			ptr->chaves[i] = ptr->chaves[i - 1];
			ptr->p[i + 1] = ptr->p[i];
		}
		ptr->chaves[pos] = novaChave;
		ptr->p[pos + 1] = novoPtr;
	}
	dividirPos = (M - 1) / 2;
	(*upChave) = ptr->chaves[dividirPos];

	(*novono) = malloc(sizeof(struct no));/*No direito apos divisão*/
	ptr->n = dividirPos; /*Número de chaves para o no dividido a esquerda*/
	(*novono)->n = M - 1 - dividirPos;/*Numero de chaves para o no dividido a direita*/
	for (i = 0; i < (*novono)->n; i++){
		(*novono)->p[i] = ptr->p[i + dividirPos + 1];
		if (i < (*novono)->n - 1)
			(*novono)->chaves[i] = ptr->chaves[i + dividirPos + 1];
		else
			(*novono)->chaves[i] = ultimachave;
	}
	(*novono)->p[(*novono)->n] = ultimoPtr;
	return InserirIsso;
}

void imprimir(struct no *ptr, int vazio){
	if (ptr){
		int i;
		for (i = 1; i <= vazio; i++)
			printf(" ");
		for (i = 0; i < ptr->n; i++)
			printf("%d ", ptr->chaves[i]);
		printf("\n");
		for (i = 0; i <= ptr->n; i++)
			imprimir(ptr->p[i], vazio + 10);
	}
}

void busca(int chave){
	int pos, i, n;
	struct no *ptr = root;
	
	printf("busca o caminho :\n");
	
	while (ptr){
		n = ptr->n;
		for (i = 0; i < ptr->n; i++)
			printf(" %d", ptr->chaves[i]);
		printf("\n");
		pos = buscaPos(chave, ptr->chaves, n);
		if (pos < n && chave == ptr->chaves[pos]){
			printf("Chave %d encontrada na posicao %d do ultimo no impresso\n", chave, i);
			return;
		}
		ptr = ptr->p[pos];
	}
	printf("A chave %d nao esta disponivel\n", chave);
}

int buscaPos(int cahve, int *chaveAuxiliar, int n){
	int pos = 0;
	while (pos < n && cahve > chaveAuxiliar[pos])
		pos++;
	return pos;
}

void DeletarNo(int chave){
	struct no *uproot;
	enum facilitador valor;

	valor = del(root, chave);
	
	switch (valor){
		case erroBusca:
			printf("A chave %d nao esta disponivel\n", chave);
			break;
		case menorChave:
			uproot = root;
			root = root->p[0];
			free(uproot);
			break;
	}
}

enum facilitador del(struct no *ptr, int chave){
	int pos, i, pivot, n, min;
	int *chaveAuxiliar;
	enum facilitador valor;
	struct no **p, *lptr, *rptr;

	if (ptr == NULL)
		return erroBusca;
	/*Atribui valores do no*/
	n = ptr->n;
	chaveAuxiliar = ptr->chaves;
	p = ptr->p;
	min = (M - 1) / 2;/*Numero minimo de chaves*/

	pos = buscaPos(chave, chaveAuxiliar, n); //Procura a chave para deletar
	// p e uma folha
	if (p[0] == NULL){
		if (pos == n || chave < chaveAuxiliar[pos])
			return erroBusca;
		/*Troca chaves e ponteiros da esquerda*/
		for (i = pos + 1; i < n; i++){
			chaveAuxiliar[i - 1] = chaveAuxiliar[i];
			p[i] = p[i + 1];
		}
		return --ptr->n >= (ptr == root ? 1 : min) ? sucesso : menorChave;
	}
	  
	if (pos < n && chave == chaveAuxiliar[pos]){ //se achar a chave e o p não for uma folha
		struct no *qp = p[pos], *qp1;
		int nchave;
		
		while (1){
			nchave = qp->n;
			qp1 = qp->p[nchave];
			if (qp1 == NULL)
				break;
			qp = qp1;
		}
		chaveAuxiliar[pos] = qp->chaves[nchave - 1];
		qp->chaves[nchave - 1] = chave;
	}
	
	valor = del(p[pos], chave);
	
	if (valor != menorChave)
		return valor;

	if (pos > 0 && p[pos - 1]->n > min){
		pivot = pos - 1; /*pivot para o no esquerdo e direito*/
		lptr = p[pivot];
		rptr = p[pos];
		/*Atribui valores para o no direito*/
		rptr->p[rptr->n + 1] = rptr->p[rptr->n];
		for (i = rptr->n; i>0; i--){
			rptr->chaves[i] = rptr->chaves[i - 1];
			rptr->p[i] = rptr->p[i - 1];
		}
		rptr->n++;
		rptr->chaves[0] = chaveAuxiliar[pivot];
		rptr->p[0] = lptr->p[lptr->n];
		chaveAuxiliar[pivot] = lptr->chaves[--lptr->n];
		return sucesso;
	}
	 //if (posn > min)
	if (pos < n && p[pos + 1]->n > min){
		pivot = pos; /*pivot para o no esquerdo e direito*/
		lptr = p[pivot];
		rptr = p[pivot + 1];
		/*atribui valores para o no esquerdo*/
		lptr->chaves[lptr->n] = chaveAuxiliar[pivot];
		lptr->p[lptr->n + 1] = rptr->p[0];
		chaveAuxiliar[pivot] = rptr->chaves[0];
		lptr->n++;
		rptr->n--;
		for (i = 0; i < rptr->n; i++){
			rptr->chaves[i] = rptr->chaves[i + 1];
			rptr->p[i] = rptr->p[i + 1];
		}
		rptr->p[rptr->n] = rptr->p[rptr->n + 1];
		return sucesso;
	}

	if (pos == n)
		pivot = pos - 1;
	else
		pivot = pos;

	lptr = p[pivot];
	rptr = p[pivot + 1];
	/*fundi o no esquerdo com o direito*/
	lptr->chaves[lptr->n] = chaveAuxiliar[pivot];
	lptr->p[lptr->n + 1] = rptr->p[0];
	for (i = 0; i < rptr->n; i++){
		lptr->chaves[lptr->n + 1 + i] = rptr->chaves[i];
		lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
	}
	lptr->n = lptr->n + rptr->n + 1;
	free(rptr); /*remove o no direito*/
	for (i = pos + 1; i < n; i++)
	{
		chaveAuxiliar[i - 1] = chaveAuxiliar[i];
		p[i] = p[i + 1];
	}
	return --ptr->n >= (ptr == root ? 1 : min) ? sucesso : menorChave;
}

/* Função para imprimir cada chave na arvore em ordem */

void inorder(struct no *ptr) {
	if (ptr) {
		if (ptr->n >= 1) {
			inorder(ptr->p[0]);
			printf("%d ", ptr->chaves[0]);
			inorder(ptr->p[1]);
			if (ptr->n == 2) {
				printf("%d ", ptr->chaves[1]);
				inorder(ptr->p[2]);
			}
		}
	}
}

