#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define QTD_PROCESSOS 200

/*Defini maquina de estados de um Processo*/
typedef enum  {
	PRONTO =1 ,
	EXECUTANDO,
	TERMINOU,
}ESTADOS_PROCESSO;

/*Defini Processo*/
typedef struct {
    int tam;
    int temp;
    ESTADOS_PROCESSO estado;
    int * pos_tabela;
}Processo;

static Processo processos[QTD_PROCESSOS];

simulacao_memoria_paginada()
{
	int i;
	for(i = 0; i < QTD_PROCESSOS; i++) {
		iniciar_Processo(i);
	}
    gerenciamento_memoria();

}

void iniciar_Processo(int i)
{
	processos[i].tam = rand();
	processos[i].temp = rand();
	processos[i].estado = PRONTO;
}

void gerenciamento_memoria()
{

}

