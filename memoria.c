#include <stdio.h>
#include <stdlib.h>
#define QTD_PROCESSOS 200


typedef enum  {
	PRONTO =1 ,
	EXECUTANDO,
	TERMINOU,
}ESTADOS_PROCESSO;

ESTADOS_PROCESSO estados;

typedef struct {
    int tam;
    int temp;
    ESTADOS_PROCESSO estado;
    int * pos_tabela;
}Processo;

int memoria_fisica[32][32];

void iniciar_Processo(int);

Processo processos[QTD_PROCESSOS];

int main()
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
