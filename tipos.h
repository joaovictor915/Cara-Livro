/**
 * @file   tipos.h
 * @brief  Arquivo com a definição de tipos globais.
 * @author João Victor MArtins
 * @date   2020-02-19
 */

#pragma once

#ifndef __TIPOS_h__
#define __TIPOS_h__

 /// Definição de verdadeiro e falso
#define VERDADEIRO (1== 1)
#define FALSO      (!VERDADEIRO)


/// Representação de um tipo booleano
typedef unsigned char bool_t;

//Tipo criado para erros
typedef unsigned int erro_t;

//tipo criado para representar um inteiro sem sinal
typedef unsigned int uint32_t;

//tipo criado para guardar as cores
typedef unsigned int cor_t;




#endif // __TIPOS_h__