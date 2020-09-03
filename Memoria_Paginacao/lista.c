
/* lista.c */

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void lst_init(lst_ptr * l)
{
    if((*l = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    (*l)->prox = (*l)->ant = *l;
    (*l)->dado = 0;
}

int lst_len(lst_ptr l)
{
    return l->dado;
}

void lst_inserir(lst_ptr l, lst_info val) {
	lst_ptr n, p;
	if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
		printf("Error ao inserir na Lista [Alocacao de memoria]");
		exit(1);;
	}
	n->dado = val;
    p = l;
    while (p->prox != l && val > p->prox->dado) {
        p = p->prox;
    }
    n->prox = p->prox;
    n->ant = p;
    p->prox->ant = n;
    p->prox = n;
    ++l->dado;
}

bool lst_remover(lst_ptr l, int k, lst_info * val)
{
	if((l->dado > 0) && (k >= 0 && k < l->dado)) {
        lst_ptr p = l;
        if(k == l->dado - 1) {
            p = l->ant;
            l->ant->ant->prox = l;
            l->ant = l->ant->ant;
        }
        else {
            int i;
            for(i = 0; i < k + 1; i++) {
                p = p->prox;
            }
            p->prox->ant = p->ant;
            p->ant->prox = p->prox;
        }
        *val = p->dado;
        free(p);
        --l->dado;
        return true;
    }
    return false;
}

lst_info lst_get(lst_ptr l)
{
    if(l->ant != l)return l->ant->dado;
    return -1;
}

lst_info lst_first(lst_ptr l)
{
    if(l->prox != l)return l->prox->dado;
    return -1;
}

void lst_print_cresc(lst_ptr l)
{
    lst_ptr p = l->prox;
    printf("[ ");
    while (p != l) {
        printf("%d,", p->dado);
        p = p->prox;
    }
    printf("\b ]\n");
}

void lst_printf_dec(lst_ptr l)
{
    lst_ptr p = l->ant;
    printf("[ ");
    while (p != l) {
        printf("%d,", p->dado);
        p = p->ant;
    }
    printf("\b ]\n");
}





