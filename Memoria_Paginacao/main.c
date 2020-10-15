/*
 * main.c
 *
 * Programa que simula uma memória paginada.
 *
 * Felipe Ferreira Nascimento (Ciência da Computação)
 * Gabriel Romano Godoi Pereira (Ciência da Computação)
 * Jaime Mathias de Lara Bueno (Ciência da Computação)
 * Marcus Vinicius de Souza Olimpio da Silva (Ciência da Computação)
 * Willy Pestana Filho (Ciência da Computação)
 * Willian Carlos Pontes da Costa(Ciência da Computação)
 *
 * Disciplina: Sistemas Operacionais II
 *
 * Professor: Marcio Luiz Piva
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

int main()
{
    printf("TRB1-SO Gerenciamento De Memoria Por Paginacao!\n");
    simulacao_memoria_paginada();
    return 0;
}
