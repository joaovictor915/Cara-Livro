/**
 * @file   Curtidas.h.c
 * @brief  Arquivo com as implentações de Curtidas.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#pragma once

#ifndef __CURTIDAS_H__
#define __CURTIDAS_H__

#define MAXITENSHASH                     ( 1000  )
#define ERRO_LISTA_CURTIDAS_VAZIA        (  -1   )
#define ERRO_ITEM_CURTIDA_NAO_ENCONTRADO (   3   )
#define ERRO_TABELA_CURTIDAS_VAZIA       ( 1 + 1 )

//#include "postagens.h"
#include "erros.h"
#include "tipos.h"
//#include "conhecimento.h"



// Struct contendo as informações da Lista
typedef struct itemListaCurtidas_s {
	bool_t CurtiuouNaocurtiu;
	uint32_t id;
	struct itemListaCurtidas_s* proximo;
	struct itemListaCurtidas_s* anterior;

}itemListaCurtidas_t;

//Struct contendo a lista 
typedef struct ListaCurtidas_s {
	uint32_t nItens;
	itemListaCurtidas_t* Primeiro;
	itemListaCurtidas_t* Ultimo;
}ListaCurtidas_t;

// Struct contendo as informações da tabela Hash
typedef struct TabelaHashCurtidas_s {
	uint32_t SubDivisoes;
	itemListaCurtidas_t** PostagensCurtidas;
}TabelaHashCurtidas_t;

//struct contato_t* vetorhash[MAXITENSHASH];

struct contato_t* contato;

struct contato_t* dummy;


TabelaHashCurtidas_t* CriaTabela();
ListaCurtidas_t* CriaListaCurtidas();
itemListaCurtidas_t* criaitemlistaCurtidas(bool_t boole, uint32_t ID);
void InicializaTabela(TabelaHashCurtidas_t* tabela, uint32_t ID, bool_t boole);
erro_t ListaCurtidas_InserenoFinal(ListaCurtidas_t* lista, itemListaCurtidas_t* novoItem);
//erro_t ListaCurtidas_InserenoFinal(ListaCurtidas_t* lista, itemListaCurtidas_t* novoItem);
erro_t RemoveTabelaCurtidas(TabelaHashCurtidas_t* Tabela, uint32_t ID);
erro_t ProcuraNaTabelaHAsh(TabelaHashCurtidas_t* tabela, uint32_t ID, itemListaCurtidas_t** copia);
bool_t CurtiuNaoCurtiu(TabelaHashCurtidas_t* tabela, uint32_t ID);
erro_t imprimeTabelahash(TabelaHashCurtidas_t* tabela);

/*
uint_32 hashCod(char chave);
uint_32 converte(char c);
TabelaHash_t* CriaTabela();
contato_t* criaitemlista(char nome[TAMMAXLETERASNOME], char endereco[TAMMAXLETRASENDERECO], uint_32 numero);
void InicializaTabela(TabelaHash_t* tabela, char* Nome, char* endereco, uint_32 numero);
void RemoveTabelaString(TabelaHash_t* Tabela, char nome[TAMMAXLETERASNOME]);
void ProcuraNaTabelaHAsh(TabelaHash_t* tabela, char nome[TAMMAXLETERASNOME], contato_t* copia);
void imprimeTabelahash(TabelaHash_t* tabela);
*/
#endif // !__CURTIDAS_H__

