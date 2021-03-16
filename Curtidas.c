/**
 * @file   Curtidas.c
 * @brief  Arquivo com as implentações de Curtidas.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "erros.h"
#include "perfil.h"
#include "Curtidas.h"

uint32_t hashCod(uint32_t ID) {
    return ID;
}


TabelaHashCurtidas_t* CriaTabela() {
    TabelaHashCurtidas_t* novoItem = (TabelaHashCurtidas_t*)malloc(sizeof(TabelaHashCurtidas_t));
    int i;

    if (novoItem == NULL) {
        return NULL;
    }

    novoItem->SubDivisoes = MAXITENSHASH;

    novoItem->PostagensCurtidas = (itemListaCurtidas_t**)malloc(MAXITENSHASH * sizeof(itemListaCurtidas_t*));

    for (i = 0; i < MAXITENSHASH; i++) {
       novoItem->PostagensCurtidas[i] = NULL;

    }




    return novoItem;
}

static void itemlistaInit(itemListaCurtidas_t* item, bool_t boole, uint32_t ID) {
    item->proximo = NULL;
    item->anterior = NULL;
    item->CurtiuouNaocurtiu = boole;
    item->id = ID;

}

ListaCurtidas_t* CriaListaCurtidas() {
    ListaCurtidas_t* lista = (ListaCurtidas_t*)malloc(sizeof(ListaCurtidas_t));
    lista->Primeiro = NULL;
    lista->nItens = 0;
    lista->Ultimo = NULL;


    return lista;
}



itemListaCurtidas_t* criaitemlistaCurtidas(bool_t boole, uint32_t ID) {
    itemListaCurtidas_t* item = (itemListaCurtidas_t*)malloc(sizeof(itemListaCurtidas_t));

    itemlistaInit(item, boole, ID);

    return item;
}



void InicializaTabela(TabelaHashCurtidas_t* tabela,uint32_t ID, bool_t boole) {
    uint32_t Conjunto = hashCod(ID);

    itemListaCurtidas_t* novoItem;

    itemListaCurtidas_t* aux;

    novoItem = criaitemlistaCurtidas(boole, ID);


    if (tabela->PostagensCurtidas[Conjunto] == NULL) {
        tabela->PostagensCurtidas[Conjunto] = novoItem;
    }
    else {
        aux = tabela->PostagensCurtidas[Conjunto];

        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        aux->proximo = novoItem;

        novoItem->anterior = aux;

        tabela->PostagensCurtidas[Conjunto] = novoItem;
    }
}

erro_t ListaCurtidas_InserenoFinal(ListaCurtidas_t* lista, itemListaCurtidas_t* novoItem) {
    uint32_t i;
    itemListaCurtidas_t* atual;

    if (novoItem == NULL) {
        return ERRO_LISTA_CURTIDAS_VAZIA;
    }


    if (lista->nItens == 0) {
        novoItem->proximo = lista->Primeiro;
        lista->Primeiro = novoItem;
        lista->nItens++;
    }
    else {

        atual = lista->Primeiro;

        for (i = 0; i < (lista->nItens - 1); i++) {
            atual = atual->proximo;
        }
        novoItem->proximo = atual->proximo;
        atual->proximo = novoItem;
        lista->nItens++;
    }

    return SUCESSO;
}

erro_t RemoveTabelaCurtidas(TabelaHashCurtidas_t* Tabela, uint32_t ID) {
    int Conjunto = ID;
    itemListaCurtidas_t* atual = NULL, * proximo = NULL;

    if (Tabela->PostagensCurtidas[Conjunto] == NULL) return ERRO_LISTA_CURTIDAS_VAZIA;

    proximo = Tabela->PostagensCurtidas[Conjunto];

    while (proximo != NULL) {
        if (ID == proximo->id) {
            if (proximo->proximo == NULL) {

                free(proximo);
                Tabela->PostagensCurtidas[Conjunto] = proximo;

            }
            else {
                proximo = proximo->proximo;
                Tabela->PostagensCurtidas[Conjunto] = proximo;

            }
            return SUCESSO;;
        }

        proximo = proximo->proximo;
    }

    return 0;
}

erro_t ProcuraNaTabelaHAsh(TabelaHashCurtidas_t* tabela, uint32_t ID, itemListaCurtidas_t** copia) {
    itemListaCurtidas_t* aux;
    int Conjunto = ID;

    if (tabela == NULL) {
        ERRO_TABELA_CURTIDAS_VAZIA;
    }
    if ((ID < 0) || (ID > (MAXITENSHASH - 1))) {
        ERRO_ID_INVALIDO;
    }

    aux = tabela->PostagensCurtidas[Conjunto];


    while (aux != NULL)
    {
        if (aux->id== ID)
        {
            *copia = aux;

            return SUCESSO;
        }

        aux = aux->proximo;
    }

  
    //Se  chegou ate aqui é porque o item nao foi encontrado
    return ERRO_ITEM_CURTIDA_NAO_ENCONTRADO;
}


bool_t CurtiuNaoCurtiu(TabelaHashCurtidas_t * tabela, uint32_t ID) {
    itemListaCurtidas_t* item;

    if (ProcuraNaTabelaHAsh(tabela, ID, &item) == SUCESSO) {
        return VERDADEIRO;
    }
    else {
        return FALSO;
    }
}


erro_t imprimeTabelahash(TabelaHashCurtidas_t* tabela) {
    int i;
    itemListaCurtidas_t* aux;
    if (tabela == NULL) {
        return ERRO_TABELA_CURTIDAS_VAZIA;
    }
    for (i = 0; i < MAXITENSHASH; i++) {
        if (tabela->PostagensCurtidas[i] == NULL) return ERRO_TABELA_CURTIDAS_VAZIA;
        aux = tabela->PostagensCurtidas[i];
        while (aux != NULL)
        {

            if (CurtiuNaoCurtiu(tabela, aux->id)== VERDADEIRO) {
                
                printf("S2 @%-06d\n", aux->id);

            }
            else {
               
            }
            aux = aux->proximo;
        }
    }
    printf("\n");

    return SUCESSO;
}









