/**
 * @file   conhecimento.h
 * @brief  Arquivo com as implentações de conhecimento.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#pragma once

#ifndef __GRAFOSLISTA_H__
#define __GRAFOSLISTA_H__
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "erros.h"
#include "perfil.h"

#define EXPLORADO    ( 5 + 0 )
#define NAOEXPLORADO ( 4 + 0 )
#define ERRO_IDPERFIL_INVALIDO ( 3 + 0 )

typedef int TIPODADO;


#define GRAFO_ITEM_NAO_ENCONTRADO (1)
#define ERRO_GRAFO_NAO_INICIALIZADO (1 + 1)
#define ERRO_VERTICE_INEXISTENTE (1 + 2)


//Definições do menu de conhecimentos
#define ACAO_SAIR_MENU_CONHECIMENTOS (   0   )
#define ACAO_SEGUIR_PERFIL           ( 0 + 1 )
#define ACAO_DEIXAR_DE_SEGUIR_PERFIL ( 0 + 2 )
#define ACAO_VER_QUEM_SIGO           ( 0 + 3 )
#define ACAO_VER_QUEM_ME_SEGUE       ( 0 + 4 )





struct grafo_s
{
	int nVertices;
	int nArestas;
	listaPerfis_t* itemListaPerfil;
};

typedef struct grafo_s grafo_t;


grafo_t* CriaGrafo(int nVertices);

erro_t CriaAresta(grafo_t* grafo, int Verti, int Vertf, dadosItem_t* peso);
erro_t desfazAresta(grafo_t* grafo, int Verti, int Vertf, itemListaPerfil_t** copia);
void imprimegrafo(grafo_t* grafo);
erro_t Profundidade(grafo_t* grafo, int i, cor_t* cores, TIPODADO Busca, itemListaPerfil_t** copia);
erro_t BuscaemProfundidade(grafo_t* grafo, TIPODADO busca, itemListaPerfil_t** copia);
erro_t VisitaVerticeEspecifico(grafo_t* grafo, int vertice);
void VisitaLargura(grafo_t* grafo, int i, int* explora, int N);
erro_t Largura(grafo_t* grafo, uint32_t IDPerfilAtivado);
void MenuConhecimentos(grafo_t* grafo, itemListaPerfil_t* perfil, listaPerfis_t* lista);



#endif // !__GRAFOSLISTA_H__


