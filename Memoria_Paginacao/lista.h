/* lista.h
 * Definição do TAD lista ordenada com operacos Get(obter ultimo elemento)
 * First(obter primeiro elemento) e remocao da K-essima posicao. Utilizando tecnicas de encadeamento duplo.
 */

#ifndef _LISTA_H
#define _LISTA_H
#include <stdbool.h>

typedef int * lst_info;
typedef struct lst_no * lst_ptr;
struct lst_no {
    lst_ptr ant;
    lst_info dado;
    lst_ptr prox;
};

/* função que inicializa a lista */
void lst_init(lst_ptr *);

/* função que retorna o tamanho da lista */
int lst_len(lst_ptr);

/* função que insere um novo nó na lista ordenada */
void lst_inserir(lst_ptr, lst_info);

/* função que remove um nó da k-essima posicao da lista ordenada */
bool lst_remover(lst_ptr, int, lst_info *);

/* função que imprime a lista em ordem crescente */
void lst_print_cresc(lst_ptr);

/* função que imprime a lista em ordem decrescente */
void lst_printf_dec(lst_ptr);

/* função que obtem o ultimo elemento da lista */
lst_info lst_get(lst_ptr);

/* função que obtem o primeiro elemento da lista */
lst_info lst_first(lst_ptr);


#endif

