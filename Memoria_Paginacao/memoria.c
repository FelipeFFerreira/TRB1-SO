#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
#include <pthread.h>
#include <unistd.h>
#include "memoria.h"
#include <windows.h>


#define QTD_PROCESSOS 200
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

void simulacao_memoria_paginada()
{
	int i; //tirei o j

	/*
	for (i = 0; i < QTD_LINHAS; i++) {
        for (j = 0; j < QTD_COLUNAS; j++) {
            memoria[i][j] = NULL;
        }
    }
    */

    /* Cria fila de processos */
	for(i = 0; i < QTD_PROCESSOS; i++) {
		iniciar_Processo(i);
        //textbackground(8);
		printf("processo %d, tamanho:%d, tempo:%d\n", i + 1, processos[i].tam, processos[i].temp);
        //textbackground(0);
	}
	textbackground(0);

	/* Inicia gerencia de memeoria */
    gerenciamento_memoria();

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

}

/* Função que aloca o processo na memória */
void gerenciamento_memoria() // ESCALONADOR
{
    int k = 0;
    pthread_t thread_monitor;
    int flag_monitor;
    flag_monitor = pthread_create(&thread_monitor, NULL, monitor_memoria, NULL);
    if(flag_monitor != false)printf("Erro na criacao da Thread Monitor\n");
    while (k < QTD_PROCESSOS) { // FAZER UMA VERIFICAÇÃO PARA PARAR O WHILE, CASO O QTD_PROCESSOS JÁ TENHA SIDO ATINGIDO
        int  i, j, l;
        if (processos[k].tam <= bits_livres) {  // Pode ser que seja melhor trabalhar com frames_livres
            int paginas = ceil(processos[k].tam / 4.0);
            /* Mutex */
            pthread_mutex_lock(&(mutex));
            bits_livres -= paginas * 4;
            pthread_mutex_unlock(&(mutex));
            /* Fim do mutex */
            int tamanho = processos[k].tam;

            for (i = 0; i < QTD_LINHAS; i++) {
                for (j = 0; j < QTD_COLUNAS; j += 4) {
                    if (!memoria[i][j]) { //estava memoria[i][j] == NULL
                        lst_ins(&processos[k].tabela_pag, &memoria[i][j]);
                        for (l = j; l < j + 4; l++) {
                            if (tamanho > 0) {
                                pthread_mutex_lock(&(mutex));
                                memoria[i][l] = k+1;  /* Talvez precise de mutex */
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
                /*
                if (paginas == 0) {
                    break;
                }*/
            }
            processos[k].estado = EXECUTANDO;   // Muda o estado do processo após alocar tudo

            k++;                               // Vai pro prox processo
        }
        else {
            Sleep(400);
        }
    }
    pthread_join(thread_monitor,NULL); //para
}

/* Função que executa o proecsso na memória */
void * monitor_memoria() {
    int count = 0;
    while (count < QTD_PROCESSOS) {
        int i;
        for (i = 0; i < QTD_PROCESSOS; i++) {
            if (processos[i].estado == EXECUTANDO) {
                processos[i].temp--;
                int tempo_proc_atual = processos[i].temp;
                if (processos[i].temp == 0) {
                    processos[i].estado = TERMINOU;
                    count++;
                    pthread_mutex_lock(&(mutex));
                    desaloca(i);    // Verificar se vai precisar de mutex
                    bits_livres += (ceil(processos[i].tam / 4.0)) * 4;//go do
                    pthread_mutex_unlock(&(mutex));
                }
            }
            else if (processos[i].estado == PRONTO) {
                //print();
                break;
            }
        }
        Sleep(300);
        print();
    }
}

void desaloca(int indice_proc) {
    //printf("\n%d", indice_proc);
    lst_ptr aux = processos[indice_proc].tabela_pag;
    int i;
    lst_ptr aux_2;
    while (aux != NULL) {
        for (i = 0; i < 4; i++) {
            int conteudo = *(aux->dado);
            *(aux->dado) = NULL;
             aux->dado++;
        }
        aux_2 = aux;
        aux = aux->prox;
        free(aux_2);    // go to
    }
}

void print() {
    int i, j;
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < QTD_LINHAS; i++) {
        for (j = 0; j < QTD_COLUNAS; j++) {
           if (!memoria[i][j]) {
                //if (j != QTD_COLUNAS && j % 4 == 0) {
                    //textbackground(2);
                   // printf("[ @ ]");
                   // textbackground(0);
                //} else {
                    textbackground(4);
                    printf("[ @ ]");
                    textbackground(0);

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



