#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
#include <pthread.h>
#include <unistd.h>
#include "memoria.h"
#include "conio.h"
#include <time.h>

#define QTD_PROCESSOS 100
#define QTD_LINHAS 32
#define QTD_COLUNAS 32

/*Defini maquina de estados de um Processo*/
typedef enum {
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

pthread_mutex_t mutex;

static int bits_livres = QTD_LINHAS * QTD_COLUNAS;

int memoria[QTD_LINHAS][QTD_COLUNAS];

static Processo processos[QTD_PROCESSOS];

int fragmentacao_interna;

int grau_multiprogramacao;

int terminar_print;

void simulacao_memoria_paginada()
{
	int i;
    srand((unsigned long long)time(NULL));

    /* Cria fila de processos */
	for(i = 0; i < QTD_PROCESSOS; i++) {
		iniciar_Processo(i);
        //textbackground(8);
		printf("processo %d, tamanho:%d, tempo:%d\n", i + 1, processos[i].tam, processos[i].temp);
        //textbackground(0);
	}
	textbackground(0);

	/* Inicia gerenciamento de memoria */
    gerenciamento_memoria();
    print_info();
}

void iniciar_Processo(int i)
{
    int tam = 10 + rand() % 20;
    int temp = 100 + rand() % 200;
	processos[i].tam = tam;
	processos[i].temp = temp;
	processos[i].estado = PRONTO;

	lst_init(&processos[i].tabela_pag); //Inicia lista de pagina
}

void print_info() {
    printf("\n\nFragmentacao Interna: %d k\n", fragmentacao_interna);
    printf("\n\nGrau Multiprogramacao Maximo: %d processos\n", grau_multiprogramacao);
}

/* Função que aloca o processo na memória */
void gerenciamento_memoria() // ESCALONADOR
{
    int k = 0;
    pthread_t thread_monitor, thread_print;
    int flag_monitor, flag_print;

    flag_monitor = pthread_create(&thread_monitor, NULL, monitor_memoria, NULL);
    if (flag_monitor != false) printf("Erro na criacao da Thread Monitor\n");

    flag_print = pthread_create(&thread_print, NULL, print_thread, NULL);
    if (flag_print != false) printf("Erro na criacao da Thread Print\n");

    while (k < QTD_PROCESSOS) {
        int i, j, l;
        if (processos[k].tam <= bits_livres) {
            int paginas = ceil(processos[k].tam / 4.0);
            fragmentacao_interna += (paginas * 4) - processos[k].tam;
            /* Mutex */
            pthread_mutex_lock(&(mutex));
            bits_livres -= paginas * 4;
            pthread_mutex_unlock(&(mutex));
            /* Fim do mutex */
            int tamanho = processos[k].tam;

            for (i = 0; i < QTD_LINHAS; i++) {
                for (j = 0; j < QTD_COLUNAS; j += 4) {
                    if (!memoria[i][j]) {
                        lst_ins(&processos[k].tabela_pag, &memoria[i][j]);
                        for (l = j; l < j + 4; l++) {
                            if (tamanho > 0) {
                                pthread_mutex_lock(&(mutex));
                                memoria[i][l] = k+1;
                                tamanho--;
                                pthread_mutex_unlock(&(mutex));
                            }
                            else {
                                break;
                            }
                        }
                        paginas--;
                    }
                    if (paginas == 0) {
                        i = QTD_LINHAS;
                        break;
                    }
                }
            }
            processos[k].estado = EXECUTANDO;

            k++;
        }
        else {
            sleep(400);
        }
    }
    pthread_join(thread_monitor,NULL);
    pthread_join(thread_print,NULL);
}

/* Função que executa o processo na memória */
void * monitor_memoria()
{
    int i, grau, count = 0;
    while (count < QTD_PROCESSOS) {
        grau = 0;
        for (i = 0; i < QTD_PROCESSOS; i++) {
            if (processos[i].estado == EXECUTANDO) {
                processos[i].temp--;
                grau++;
                if (processos[i].temp == 0) {
                    processos[i].estado = TERMINOU;
                    count++;
                    /* Mutex */
                    pthread_mutex_lock(&(mutex));
                    desaloca(i);    // Verificar se vai precisar de mutex
                    bits_livres += (ceil(processos[i].tam / 4.0)) * 4;//go do
                    pthread_mutex_unlock(&(mutex));
                    /* Fim do Mutex */
                }
            }
            else if (processos[i].estado == PRONTO) {
                break;
            }
        }
        if (grau > grau_multiprogramacao) {
            grau_multiprogramacao = grau;
        }
        sleep(200);
    }
    terminar_print = 1; // Váriavel para controlar a parada da thread_print
}

void desaloca(int indice_proc)
{
    lst_ptr aux = processos[indice_proc].tabela_pag;
    int i;
    lst_ptr aux_2;
    while (aux != NULL) {
        for (i = 0; i < 4; i++) {
            *(aux->dado) = NULL;
             aux->dado++;
        }
        aux_2 = aux;
        aux = aux->prox;
        free(aux_2);
    }
}

/* Thread para prints da memória */
void * print_thread()
{
    while (terminar_print != 1) {
        print();
        sleep(3000);
    }
    print();
}

/* Printa a matriz da memória */
void print()
{
    int i, j, count = 0;
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < QTD_LINHAS; i++) {
        for (j = 0; j < QTD_COLUNAS; j++) {
           if (!memoria[i][j]) {
                if ((j != QTD_COLUNAS && (j % 4 == 0 || j == 0)) || count > 0) {
                    if (count == 0) {
                        count  = 4;
                    }
                    count--;
                    textbackground(2);
                    printf("[ @ ]");
                    textbackground(0);
                } else {
                    textbackground(4);
                    printf("[ @ ]");
                    textbackground(0);
                }
           } else {
               printf("[%3d]", memoria[i][j]);
           }
           textbackground(0);
           printf(" ");
        }
        textbackground(0);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    //system("pause");
    //system("cls");
}
