#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define QTD_PROCESSOS 200
#define QTD_LINHAS 32
#define QTD_COLUNAS 32

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
    lst_ptr tabela_pag;
}Processo;

int bits_livres;

int memoria[QTD_LINHAS][QTD_COLUNAS];

static Processo processos[QTD_PROCESSOS];

simulacao_memoria_paginada()
{
	int i, j;
	for (i = 0; i < QTD_LINHAS; i++) {
        for (j = 0; j < QTD_COLUNAS; j++) {
            memoria[i][j] = NULL;
        }
    }

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

	lst_init(processos[i].tabela_pag);
}

void gerenciamento_memoria()
{
    while (1) {
        int k = 0, i, j, l;
        if (processos[k].tam <= bits_livres) {  // Pode ser que seja melhor trabalhar com frames_livres
            double aux = (processos[k].tam / 4);
            int paginas = aux; // go to
            //int paginas = (aux % 1) == 0 ? aux : aux + 1; // go to
            /* Mutex */
            bits_livres -= paginas * 4;
            /* Fim do mutex */
            int tamanho = processos[k].tam;

            for (i = 0; i < QTD_LINHAS; i++) {
                for (j = 0; j < QTD_COLUNAS; j += 4) {
                    if (memoria[i][j] == NULL) {
                        lst_inserir(processos[k].tabela_pag, &memoria[i][j]);
                        for (l = j; l < j + 4; l++) {
                            if (tamanho > 0) {
                                memoria[i][l] = k;  /* Talvez precise de mutex */
                                tamanho--;
                            }
                            else {
                                break;
                            }
                        }
                        paginas--;
                    }
                    if (paginas == 0) {
                        break;
                    }
                }
                if (paginas == 0) {
                    break;
                }
            }
            k++;
        }
        else {
            //sleep(3000);
        }
    }
}
