#include <stdio.h>
#include "tree.h"
#include <stdbool.h>

void insert(int key){
	struct no *newnode;
	int upKey;
	enum KeyStatus value;

	value = ins(root, key, &upKey, &newnode);

	if (value == Duplicate)
		printf("Valor já foi inserido\n");
	if (value == InsertIt){
		
		struct no *uproot = root;
		root = malloc(sizeof(struct no));

		root->n = 1;
		root->keys[0] = upKey;
		root->p[0] = uproot;
		root->p[1] = newnode;
	}
}

enum KeyStatus ins(struct no *ptr, int key, int *upKey, struct no **newnode){
	struct no *newPtr, *lastPtr;
	
	int pos, i, n, splitPos;
	int newKey, lastKey;
	
	enum KeyStatus value;
	
	if (ptr == NULL){
		*newnode = NULL;
		*upKey = key;
		return InsertIt;
	}
	n = ptr->n;
	pos = searchPos(key, ptr->keys, n);
	
	if (pos < n && key == ptr->keys[pos])
		return Duplicate;
	value = ins(ptr->p[pos], key, &newKey, &newPtr);
	
	if (value != InsertIt)
		return value;
	
	if (n < M - 1){
		
		pos = searchPos(newKey, ptr->keys, n);
		
		for (i = n; i>pos; i--){
			ptr->keys[i] = ptr->keys[i - 1]; /*Mudando a chave e o ponteiro para inserir nova chave*/
			ptr->p[i + 1] = ptr->p[i];
		}
		
		ptr->keys[pos] = newKey;
		ptr->p[pos + 1] = newPtr;
		++ptr->n; /*mudando o numero de chaves em no*/
		return Success;
	}
	 /*Se as chaves nos nós forem maximo e a posição for a ultima pra ser inserida no no*/
	if (pos == M - 1){
		lastKey = newKey;
		lastPtr = newPtr;
	}
	/*Se as chaves em no foram maximo e a posição do no não for pra ser inserida no ultimo*/
	else{  
		lastKey = ptr->keys[M - 2];
		lastPtr = ptr->p[M - 1];
		for (i = M - 2; i>pos; i--){
			ptr->keys[i] = ptr->keys[i - 1];
			ptr->p[i + 1] = ptr->p[i];
		}
		ptr->keys[pos] = newKey;
		ptr->p[pos + 1] = newPtr;
	}
	splitPos = (M - 1) / 2;
	(*upKey) = ptr->keys[splitPos];

	(*newnode) = malloc(sizeof(struct no));/*no direito despois do split*/
	ptr->n = splitPos; /*numero de chaves para o no esquerdo dividido*/
	(*newnode)->n = M - 1 - splitPos;/*numero de chaves para o no direito dividido*/ 
	for (i = 0; i < (*newnode)->n; i++){
		(*newnode)->p[i] = ptr->p[i + splitPos + 1];
		if (i < (*newnode)->n - 1)
			(*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
		else
			(*newnode)->keys[i] = lastKey;
	}
	(*newnode)->p[(*newnode)->n] = lastPtr;
	return InsertIt;
}

void imprimir(struct no *ptr, int blanks){
	if (ptr){
		int i;
		for (i = 1; i <= blanks; i++)
			printf(" ");
		for (i = 0; i < ptr->n; i++)
			printf("%d ", ptr->keys[i]);
		printf("\n");
		for (i = 0; i <= ptr->n; i++)
			imprimir(ptr->p[i], blanks + 10);
	}
}

void search(int key){
	int pos, i, n;
	struct no *ptr = root;
	printf("Search path:\n");
	while (ptr){
		n = ptr->n;
		for (i = 0; i < ptr->n; i++)
			printf(" %d", ptr->keys[i]);
		printf("\n");
		pos = searchPos(key, ptr->keys, n);
		if (pos < n && key == ptr->keys[pos]){
			
			printf("Chave %d encontrada na posicao %d do ultimo no impresso\n", key, i);
			return;
		}
		ptr = ptr->p[pos];
	}
	printf("Chave %d não disponivel\n", key);
}

int searchPos(int key, int *key_arr, int n){
	int pos = 0;
	while (pos < n && key > key_arr[pos])
		pos++;
	return pos;
}

void DelNode(int key){
	struct no *uproot;
	enum KeyStatus value;
	
	value = del(root, key);
	
	switch (value){
		case SearchFailure:
			printf("Chave %d não disponivel\n", key);
			break;
		case LessKeys:
			uproot = root;
			root = root->p[0];
			free(uproot);
			break;
	}
}

enum KeyStatus del(struct no *ptr, int key){
	int pos, i, pivot, n, min;
	int *key_arr;
	enum KeyStatus value;
	struct no **p, *lptr, *rptr;

	if (ptr == NULL)
		return SearchFailure;
	/*atribui valores de no*/
	n = ptr->n;
	key_arr = ptr->keys;
	p = ptr->p;
	min = (M - 1) / 2;/*Numero minimo de chaves*/

	pos = searchPos(key, key_arr, n); //procura a chave a ser deletada
	// p é uma folha
	if (p[0] == NULL){
		if (pos == n || key < key_arr[pos])
			return SearchFailure;
		/*troca chaves e ponteiros da esquerda*/
		for (i = pos + 1; i < n; i++){
			key_arr[i - 1] = key_arr[i];
			p[i] = p[i + 1];
		}
		return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
	}

	 //se achar a chave e o p não for uma folha
	if (pos < n && key == key_arr[pos]){
		struct no *qp = p[pos], *qp1;
		int nkey;
		
		while (1){
			nkey = qp->n;
			qp1 = qp->p[nkey];
			if (qp1 == NULL)
				break;
			qp = qp1;
		}
		key_arr[pos] = qp->keys[nkey - 1];
		qp->keys[nkey - 1] = key;
	}
	value = del(p[pos], key);
	if (value != LessKeys)
		return value;

	if (pos > 0 && p[pos - 1]->n > min){
		pivot = pos - 1; /*pivot para o no esquerdo e direito*/
		lptr = p[pivot];
		rptr = p[pos];
		/*atribui valores para o no direito*/
		rptr->p[rptr->n + 1] = rptr->p[rptr->n];
		for (i = rptr->n; i>0; i--){
			rptr->keys[i] = rptr->keys[i - 1];
			rptr->p[i] = rptr->p[i - 1];
		}
		rptr->n++;
		rptr->keys[0] = key_arr[pivot];
		rptr->p[0] = lptr->p[lptr->n];
		key_arr[pivot] = lptr->keys[--lptr->n];
		return Success;
	}
	 //if (posn > min)
	if (pos < n && p[pos + 1]->n > min){
		pivot = pos; /*pivot para o no esquerdo e direito*/
		lptr = p[pivot];
		rptr = p[pivot + 1];
		/*atribui valores para o no esquerdo*/
		lptr->keys[lptr->n] = key_arr[pivot];
		lptr->p[lptr->n + 1] = rptr->p[0];
		key_arr[pivot] = rptr->keys[0];
		lptr->n++;
		rptr->n--;
		for (i = 0; i < rptr->n; i++)
		{
			rptr->keys[i] = rptr->keys[i + 1];
			rptr->p[i] = rptr->p[i + 1];
		}
		rptr->p[rptr->n] = rptr->p[rptr->n + 1];
		return Success;
	}

	if (pos == n)
		pivot = pos - 1;
	else
		pivot = pos;

	lptr = p[pivot];
	rptr = p[pivot + 1];
	/*fundi o no esquerdo com o direito*/
	lptr->keys[lptr->n] = key_arr[pivot];
	lptr->p[lptr->n + 1] = rptr->p[0];
	for (i = 0; i < rptr->n; i++){
		lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
		lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
	}
	lptr->n = lptr->n + rptr->n + 1;
	free(rptr); /*remove o no direito*/
	for (i = pos + 1; i < n; i++){
		key_arr[i - 1] = key_arr[i];
		p[i] = p[i + 1];
	}
	return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}
/* Função para imprimir cada chave na arvore em ordem */
void inorder(struct no *ptr) {
	if (ptr) {
		if (ptr->n >= 1) {
			inorder(ptr->p[0]);
			printf("%d ", ptr->keys[0]);
			inorder(ptr->p[1]);
			if (ptr->n == 2) {
				printf("%d ", ptr->keys[1]);
				inorder(ptr->p[2]);
			}
		}
	}
}
/* Função que retorna o numero total de chaves na arvore */
int totalKeys(struct no *ptr) {
	if (ptr) {
		int count = 1;
		if (ptr->n >= 1) {
			count += totalKeys(ptr->p[0]);
			count += totalKeys(ptr->p[1]);
			if (ptr->n == 2) count += totalKeys(ptr->p[2]) + 1;
		}
		return count;
	}
	return 0;
}
