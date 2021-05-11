#include <stdio.h>
#include "tree.c"

int main(){

	int key;
	int op;

	while (op != 5){
		printf("1.Inserir\n");
		printf("2.Deletar\n");
		printf("3.Buscar\n");
		printf("4.Imprimir\n");
		printf("5.Sair\n");
		printf("Digitar op: ");
		scanf("%d", &op);

		switch (op){
			case 1:
				printf("Insira o valor: ");
				scanf("%d", &key);
				insert(key);
				break;
			case 2:
				printf("Insira o valor: ");
				scanf("%d", &key);
				DelNode(key);
				break;
			case 3:
				printf("Insira o valor: ");
				scanf("%d", &key);
				search(key);
				break;
			case 4:
				imprimir(root, 0);
				//imprimir1(root);
				break;
			case 5:
				exit(1);
			}
		}
		return 0;
	}