/**
 * @file   perfil.h
 * @brief  Arquivo com as implentações de perfil.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#pragma once

#ifndef __PERFIL_H__
#define __PERFIL_H__

//inclusões
#include "tipos.h"
#include "erros.h"
#include "postagens.h"
//#include "conhecimento.h"

//Constantes
#define TAMANHOMAXIMONOMEPERFIL ( 40 + 0)
#define TAMANHOMAXIMOEMAIL (40 + 1)
#define TAMANHOMAXIMONOMECIDADE (29 + 0) //Numero de caracteres da cidade brasileira com maior número de caracteres
										//(São José do Vale do Rio Preto)

//Constantes das funções principais
#define ERRO_LISTA_PERFISVAZIA ( 0 + 1)
#define ERRO_PERFIL_NAO_ENCONTRADO ( 0 + 2)
#define ERRO_PERFIL_NAO_INICIALIZADO (0 + 3)

//Constantes do menu
#define ACAO_SAIR_MENU_PERFIL (0 + 0)
#define ACAO_CADASTRO_PERFIL  (0 + 1)
#define ACAO_REMOVER_PERFIL   (0 + 2)
#define ACAO_VISUALIZA_PERFIS (0 + 3)
#define ACAO_PROCURA_PERFIS   (0 + 4)

//Estrutura que contém os dados guardados pelos membros da lista de perfis

struct dadosItem_s {
	uint32_t id;
	char nome[TAMANHOMAXIMONOMEPERFIL];
	char email[TAMANHOMAXIMOEMAIL];
	uint32_t telefone;
	char Cidade[TAMANHOMAXIMONOMECIDADE];
};
typedef struct dadosItem_s dadosItem_t;

/* Tipos */





typedef struct itemListaPerfil_s {
	dadosItem_t* dados;
    listapostagens_t* Postagens;
	struct itemListaPerfil_s* proximo;
	int vertice;
}itemListaPerfil_t;

struct listaPerfis_s {
	itemListaPerfil_t* primeiro;
	int nItens;
};

/// Tipo "Lista"
typedef struct listaPerfis_s listaPerfis_t;




itemListaPerfil_t* CraItemLista(char nome[TAMANHOMAXIMONOMEPERFIL], char cidade[TAMANHOMAXIMONOMECIDADE], char email[TAMANHOMAXIMOEMAIL], uint32_t id, uint32_t telefone);



listaPerfis_t* CriaListaVazia();
erro_t ListaPerfis_InserenoFinal(listaPerfis_t* lista, itemListaPerfil_t* novoItem);
void itemimprime(itemListaPerfil_t* item);
erro_t listaPerfisimprime(listaPerfis_t* lista);
bool_t listaPerfis_remove(listaPerfis_t* lista, uint32_t info);
erro_t listaPerfis_procura(listaPerfis_t* lista, uint32_t info, itemListaPerfil_t** copia);
uint32_t geraIDPerfil(void);
void MenuPerfil(listaPerfis_t* lista);

//void EntraremumPerfil(listaPerfis_t* listaPerfis, itemListaPerfil_t* itemPerfil, grafo_t* grafoPerfis);

#endif // !__PERFIL_H__

