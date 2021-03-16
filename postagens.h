/**
 * @file   postagens.h
 * @brief  Arquivo com as implentações de postagens.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#pragma once

#ifndef __POSTAGENS_H__
#define __POSTAGENS_H__

//inclusões
#include "tipos.h"
#include "erros.h"
#include "Curtidas.h"
//#include "conhecimento.h"

//Constantes
#define TAMANHOMAXIMOTITULOPOSTAGEM ( 40 + 0)
#define TAMANHOMAXIMOTEXTOPOSTAGEM  (140 + 0)   //Mesma limitação de caracteres daquela rede social do passarinho azul lá
#define TAMANHOMAXIMONOMECIDADE     ( 29 + 0)    //Numero de caracteres da cidade brasileira com maior número de caracteres
                                             //(São José do Vale do Rio Preto)
#define NUMERO_ITENS_POSTEGENS_IMPRESSOS ( 0 + 5 ) 

//Constantes das funções principais
#define ERRO_LISTA_POSTAGENSVAZIA      ( 0 + 1 )
#define ERRO_POSTAGEM_NAO_ENCONTRADA   ( 0 + 2 ) 
#define ERRO_POSTAGEM_NAO_INICIALIZADA ( 0 + 3 )

//Constantes do menu
#define ACAO_SAIR_MENU_POSTAGENS (0 + 0)
#define ACAO_FAZ_POSTAGEM        (0 + 1)
#define ACAO_REMOVER_POSTAGEM    (0 + 2)
#define ACAO_VISUALIZA_POSTAGENS (0 + 3)
#define ACAO_PROCURA_POSTAGENS   (0 + 4)

//Estrutura que contém os dados guardados pelos membros da lista de perfis

struct dadospostagem_s {
	uint32_t idPerfil;
	uint32_t idPostagem;
	char titulo[TAMANHOMAXIMOTITULOPOSTAGEM];
	char texto[TAMANHOMAXIMOTEXTOPOSTAGEM];
};

typedef struct dadospostagem_s dadospostagem_t;

/* Tipos */


typedef struct itemListapostagem_s {
	dadospostagem_t* dados;
	TabelaHashCurtidas_t* tabelaQuemCurtiu;
	struct itemListapostagem_s* proximo;
	int vertice;
}itemListapostagem_t;

struct listapostagens_s {
	itemListapostagem_t* primeiro;
	int nItens;
};

/// Tipo "Lista"
typedef struct listapostagens_s listapostagens_t;


itemListapostagem_t* CriaItemListaPostagens(char Titulo[TAMANHOMAXIMOTITULOPOSTAGEM], char Texto[TAMANHOMAXIMOTEXTOPOSTAGEM], uint32_t id);
listapostagens_t* CriaListaPostagensVazia();
erro_t ListaPostagens_InserenoFinal(listapostagens_t* lista, itemListapostagem_t* novoItem);
void itemPostagemimprime(itemListapostagem_t* item);
void itemPostagemimprimeSimples(itemListapostagem_t* item, uint32_t ID);
erro_t listaPostagensimprime(listapostagens_t* lista);
erro_t listaPostagensimprimeNpostagens(listapostagens_t* lista, uint32_t ID);
bool_t listaPostagens_remove(listapostagens_t* lista, uint32_t info);
erro_t listaPostagens_procura(listapostagens_t* lista, uint32_t info, itemListapostagem_t** copia);
itemListapostagem_t* listaPostagens_procuraeRetorna(listapostagens_t* lista, uint32_t info, itemListapostagem_t** copia);
uint32_t geraIDPostagem(void);
void MenuPostagem(listapostagens_t* lista, uint32_t item);
//void MenuPostagem(listapostagens_t* lista, itemListaPerfil_t* item);


#endif // !__POSTAGENS_H__
