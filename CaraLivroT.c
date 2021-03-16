/**
 * @file   CaraLivroT.c
 * @brief  Arquivo com as implenta��es de CaraLivroT.
 * @author Jo�o Victor MArtins
 * @date   17/11/2020
 */
#include "erros.h"
#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "perfil.h"
#include "postagens.h"
#include "conhecimento.h"
#include "Curtidas.h"
#include "CaraLivroT.h"


void EntraremumPerfil(listaPerfis_t* listaPerfis, itemListaPerfil_t* itemPerfil, grafo_t* grafoPerfis) {
	uint32_t ID, IDPerfilAtivo = itemPerfil->dados->id;
	itemListaCurtidas_t* item, * copia, * perfilqueeadentrado;
	itemListaPerfil_t* copiaIP;
	listapostagens_t* listaP;
	itemListapostagem_t* copiaP = NULL;
	TabelaHashCurtidas_t* tabelaP;
	bool_t curtiu;
	erro_t erro;
	int verifica;
	int i;
	//erro_t erro;

	//Pergunta ao usu�rio o ID do perfil que ele deseja entrar
	printf("Digite o ID do perfil que deseja visitar\n");
	scanf("%d", &ID);
	//Procura o perfil com este ID na lista de perfis
	erro = listaPerfis_procura(listaPerfis, ID, &copiaIP);

	//Caso esse perfil exista na lista de perfis (n�o seja nulo) ele far� o que est� dentro do if
	if (erro == SUCESSO) {

		//imprime os N perfis de proximidade com o usuario
		erro = Largura(grafoPerfis, IDPerfilAtivo);
		//ListaP � a c�pia da lista de postagens do perfil que o usu�rio escolheu visitar
		listaP = copiaIP->Postagens;
		//imprime os dados do perfil
		itemimprime(copiaIP);
		//imprime as N primeiras postagens do perfil selecionado pelo user
		listaPostagensimprimeNpostagens(listaP, IDPerfilAtivo);

		//Pergunta ao usuario se ele deseja detalhar alguma postagem
		printf("Deseja imprimir detalhadamente cada alguma postagem?:\n"
		       "[1] SIM\n"
		       "[Qualquer outro numero] NAO\n");
		scanf("%d", &verifica);


		if (verifica == VERDADEIRO) {
			//Perfunta o ID da postagem que ele deseja imprimir com detalhes
			printf("Digite o ID da postagem que deseja imprimir detalhadamente");
			scanf("%d", &ID);
			//Procura a postagem com esse ID na listab de postagens do perfil visitado e caso essa postagem exista no perfil, imprime-a com seus detalhes
			erro = listaPostagens_procura(listaP, ID, &copiaP);

			if (erro == SUCESSO) {
				itemPostagemimprime(copiaP);
			}
			else
			{
				printf("ID de postagem inexistente\n");
			}
		}
		verifica = 1;


	}

	//imprimeTabelahash(item->Postagens->primeiro->tabelaQuemCurtiu);



}
void MenuCurtidas(listapostagens_t* lista, uint32_t IDPerfilAtivo, uint32_t IDPerfilPostagem) {
	int verifica = 1;
	erro_t erro;
	uint32_t ID;
	itemListapostagem_t* copia = NULL, * copia2;
	TabelaHashCurtidas_t* tabelaP;

	//Enquanto o verifica for diferente de 0 o usuario quer curtir uma postagem
	while (verifica != 0)
	{
		//Perfunta ao usu�rio se ele quer curtir alguma postagem
		printf("Deseja curtir alguma postagem deste perfil?\n"
			"[1] SIM\n"
			"[0] NAO");
		scanf("%d", &verifica);

		//Caso ele queira curtir alguma postagem, pergunta ao usu�rio o ID da postagem que deseja curtir
		//Caso essa postagem exista na lista de postagens do perfil visitado, o perfil atual curte essa postagem
		if (verifica == VERDADEIRO) {
			printf("Digite o ID da postagem que deseja curtir\n");
			scanf("%d", &ID);
			copia2 = listaPostagens_procuraeRetorna(lista, ID, &copia);

			if (copia2 != NULL) {

				//A tabela a ser inserida a curtida � a tabela de curtidas da postagem que foi guardada na variavel copia
				tabelaP = copia->tabelaQuemCurtiu;
				InicializaTabela(tabelaP, IDPerfilAtivo, VERDADEIRO);

				//Faz com que o valor original na tabela da postagem que foi curtida seja igual a nova Tabela
				//A unica diferen�a desta tabela para a antiga � que est� cont�m o item rec�m inserido
				copia2->tabelaQuemCurtiu = tabelaP;
			}
		}
	}
}