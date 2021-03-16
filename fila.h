/**
 * @file   fila.h
 * @brief  Arquivo com as implentações de Fila.
 * @author João Victor MArtins
 * @date   17/11/2020
 */

#pragma once

#ifndef __FILA_H__
#define __FILA_H__

 // Bibliotecas a serem utilizadas

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "erros.h"
#include "tipos.h"

// Definições

#define ERRO_FILA_VAZIA (2)
#define ERRO_FILA_CHEIA (3)
#define TAMANHO_MAXIMO_VETOR (5)

//Structs

typedef struct registro_s {
	int chave;

}registro_t;

typedef struct elemento_s {
	registro_t dado;
	struct elemento_s* prox;

}TElemento, * aponta_t;

typedef struct  fila_s {
	aponta_t inicio;
	aponta_t Fim;

}fila_t;

// Filas
void InicializaFila(fila_t* Fila);
int Tamanho(fila_t* Fila);
erro_t AddNaFila(fila_t* Fila, registro_t dado);
erro_t TiraDaFila(fila_t* Fila, registro_t* dado);
#endif // !__FILA_H__