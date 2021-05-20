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
#include "arvore2-3-4.c"

main(){
  int chave, op, num, i;

  while(op != 5){
    printf("[ 1 ] imprimirArvore\n");
    printf("[ 2 ] InserirValor\n");
    printf("[ 3 ] BuscaValor\n");
    printf("[ 4 ] Remover\n");
    printf("[ 5 ] Sair\n");

    printf("Digitar op:");
    scanf("%d", &op);
    
    switch(op){
      case 1:
      	printf("A arvore eh :\n");
        imprimir(root, 0);
        break;
    
      case 2:
        printf("Entrar com a chave : ");
        scanf("%d", &chave); 
        inserir(chave);
        break;
      	
   	  case 3:
   	  		printf("Entrar com a chave : ");
        scanf("%d", &chave); 
        busca(chave);
        break;
   	  	
   	  case 4:
   	  	printf("Entrar com a chave : ");
        scanf("%d", &chave); 
        DeletarNo(chave);
        break;
   	  case 5:
        exit(1);	 	
   } 	  	
 }
}
