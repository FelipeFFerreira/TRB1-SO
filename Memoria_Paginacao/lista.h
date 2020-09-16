/* listaord.h
 * Defini��o do TAD para representar uma lista ordenada implementada
 * de forma encadeada e prot�tipo das opera��es sobre esse TAD.
 * 24/04/2019
 */

#ifndef _LISTAORD_H
#define _LISTAORD_H
#include <stdbool.h>

typedef int * lst_info;
typedef struct lst_no * lst_ptr;
struct lst_no {
    lst_info dado;
    lst_ptr prox;
};

/* inicializa a lista ordenada */
void lst_init(lst_ptr *);

/* insere um novo elemento na lista ordenada */
void lst_ins(lst_ptr *, lst_info);

/* remove um elemento da lista ordenada */
bool lst_rem(lst_ptr *, lst_info);

/* procura e devolve o ponteiro para o n� da lista
 * que cont�m um valor, ou NULL, caso o valor n�o
 * seja localizado */
lst_ptr lst_find(lst_ptr, lst_info);

/* imprime os elementos da lista ordenada */
void lst_print(lst_ptr);

/* destr�i uma lista ordenada */
void lst_kill(lst_ptr *);

#endif
