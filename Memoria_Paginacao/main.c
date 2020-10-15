/*
 * main.c
 *
 * Programa que simula uma mem�ria paginada.
 *
 * Felipe Ferreira Nascimento (Ci�ncia da Computa��o)
 * Gabriel Romano Godoi Pereira (Ci�ncia da Computa��o)
 * Jaime Mathias de Lara Bueno (Ci�ncia da Computa��o)
 * Marcus Vinicius de Souza Olimpio da Silva (Ci�ncia da Computa��o)
 * Willy Pestana Filho (Ci�ncia da Computa��o)
 * Willian Carlos Pontes da Costa(Ci�ncia da Computa��o)
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
