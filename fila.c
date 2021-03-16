/**
 * @file   fila.c
 * @brief  Arquivo com as implentações de Fila.
 * @author João Victor MArtins
 * @date   17/11/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "erros.h"
#include "tipos.h"
#include "fila.h"

void InicializaFila(fila_t *fila) {
	fila->Fim = NULL;
	fila->inicio = NULL;
}

int Tamanho(fila_t* Fila) {
	aponta_t endereco = Fila->inicio;
	int tamanho = 0;

	while (endereco != NULL) {
		tamanho++;
		endereco = endereco->prox;
	}
	return tamanho;
}

erro_t AddNaFila(fila_t* Fila, registro_t dado) {
	aponta_t novo = (aponta_t)malloc(sizeof(TElemento));

	novo->dado = dado;
	novo->prox = NULL;

	if (Fila->inicio == NULL) {
		Fila->inicio = novo;
	}
	else {
		Fila->Fim->prox = novo;
	}
	Fila->Fim = novo;

	return SUCESSO;
}

erro_t TiraDaFila(fila_t* Fila, registro_t* dado) {
	if (Fila->inicio == NULL) {
		return ERRO_FILA_VAZIA;
	}

	*dado = Fila->inicio->dado;

	aponta_t apagar = Fila->inicio;

	Fila->inicio = Fila->inicio->prox;
	free(apagar);

	if (Fila->inicio == NULL) {
		Fila->Fim = NULL;
	}
	return SUCESSO;
}