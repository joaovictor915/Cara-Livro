/**
 * @file   CaraLivroT.h
 * @brief  Arquivo com as implentações de CaraLivroT.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#pragma once
#ifndef __CARA_LIVRO_H__
#define __CARA_LIVRO_H__
 #include "erros.h"
#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "fila.h"
#include "perfil.h"
#include "postagens.h"
#include "conhecimento.h"
#include "Curtidas.h"

void EntraremumPerfil(listaPerfis_t* listaPerfis, itemListaPerfil_t* itemPerfil, grafo_t* grafoPerfis);
void MenuCurtidas(listapostagens_t* lista, uint32_t IDPerfilAtivo, uint32_t IDPerfilPostagem);


#endif // !__CARA_LIVRO_H__

