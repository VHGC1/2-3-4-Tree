#include <stdio.h>
#include <stdlib.h>
#define M 3

struct no {
	int n; /* n < M No. of keys in no will always less than order of B tree */
	int keys[3]; 
	struct no *p[4]; 
}*root = NULL;

enum KeyStatus { Duplicate, SearchFailure, Success, InsertIt, LessKeys };

void insert(int key);
void imprimir(struct no *root, int);
void DelNode(int x);
void search(int x);
enum KeyStatus ins(struct no *r, int x, int* y, struct no** u);
int searchPos(int x, int *key_arr, int n);
enum KeyStatus del(struct no *r, int x);
void eatline(void);
void inorder(struct no *ptr);