#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void gerenciamento_memoria() // ESCALONADOR
{
    while (1) { // FAZER UMA VERIFICA��O PARA PARAR O WHILE, CASO O QTD_PROCESSOS J� TENHA SIDO ATINGIDO
        int k = 0, i, j, l;
        if (processos[k].tam <= bits_livres) {  // Pode ser que seja melhor trabalhar com frames_livres
            int paginas = ceil(processos[k].tam / 4);
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
            processos[k].estado = EXECUTANDO;   // Muda o estado do processo ap�s alocar tudo

            k++;                               // Vai pro prox processo
        }
        else {
            //sleep(3000);
        }
    }
}


void monitor_memoria() {
    while (1) {
        int i;
        for (i = 0; i < QTD_PROCESSOS; i++) {
            if (processos[i].estado == EXECUTANDO) {
                processos[i].temp--;
                if (processos[i].temp == 0) {
                    processos[i].estado = TERMINOU;
                    desaloca(i);    // Verificar se vai precisar de mutex
                    bits_livres += (ceil(processos[k].tam / 4)) * 4;
                }
            }
            else if (processos[i].estado == PRONTO) {
                break;
            }
        }
        sleep(3000);
    }
}

void desaloca(int indice_proc) {
    lst_ptr aux = processos[indice_proc].tabela_pag
    int i;
    lst_ptr aux_2;
    while (aux != NULL) {
        for (i = 0; i < 4; i++) {
            *(aux.dado) = NULL;
            aux++;
        }
        aux_2 = aux;
        aux = aux.prox;
        free(aux_2);    // go to
    }
}



