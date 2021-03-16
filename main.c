/**
 * @file   main.c
 * @brief  Função main.
 * @author João Victor MArtins
 * @date   19/11/2020
 */
//Inclusões
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "conhecimento.h"
#include "erros.h"
#include "tipos.h"
#include "perfil.h"
#include "postagens.h"
#include "Curtidas.h"
#include "CaraLivroT.h"

#define ACAO_SAIR_CARA_LIVRO                    ( 0 + 0 )
#define ACAO_ABRIR_GERENCIAMENTO_DE_PERFIS      ( 0 + 1 )
#define ACAO_ABRIR_GERENCIAMENTO_DE_SEGUIDORES  ( 0 + 2 )
#define ACAO_ABRIR_GERENCIAMENTO_DE_POSTAGEM    ( 0 + 3 )
#define ACAO_VISITAR_PERFIL                     ( 0 + 4 )
#define ACAO_ABRIR_JOGO_DA_MEMORIA              ( 0 + 5 )

int main() {
	itemListaPerfil_t* item, *item2, *item3, *item4, *item5, *item6;
	itemListaPerfil_t* copiaPerfil = NULL;
	listaPerfis_t* lista;
	itemListapostagem_t* itemP;
	int i;
	bool_t boole;
	listapostagens_t* listaP;
	grafo_t* grafo;
	//adjacencia_t* copia;
	bool_t erro;
	TabelaHashCurtidas_t* tabela;
	itemListaCurtidas_t* itemC = criaitemlistaCurtidas(VERDADEIRO, 00);
	listaP = CriaListaPostagensVazia();
	uint32_t ID, IDPerfilVisitado;
	int acao = 1;

	lista = CriaListaVazia();
	grafo = CriaGrafo(MAXITENSHASH);
	tabela = CriaTabela();
	listaP = CriaListaPostagensVazia();


	printf("Bem vindo ao CaraLivro, a rede social mais amada pelo Leandro Maia.\n");
	while (acao != 0) {
		printf("|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
		printf("|Selecione um modulo da nossa rede social para abrir:\n\n\n"
			"|[1] GERENCIAMENTO DE PERFIS     - Modulo em que se pode cadastrar um novo perfil, procurar um perfil no sistema, apagar e procurar um perfil                                     |\n"
			"|[2] GERENCIAMENTO DE SEGUIDORES - Modulo onde voce pode seguir um perfil, deixar de seguir, ver quem voce segue e ver quem segue voce                                            |\n"
			"|[3] GERENCIAMENTO DE POSTAGEM   - Nesse modulo você pode fazer uma postagem em sua conta, apagar uma postagem em sua conta e visualizar e procurar todas as postagens no sistema |\n"
			"|[4] ABRIR UM PERFIL             - Nesse modulo voce pode ir ao perfil (usando o ID deste perfil) ver e curtir suas postagens, bem como ver seus amigos em comum                  |\n"
			"|[5] JOGO                        - Modulo adicional onde voce pode jogar o jogo da memoria                                                                                        |\n"
			"|[0] SAIR                        - Caso queira nos deixar :(:(:(:(                                                                                                                |\n"
			"|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
		scanf("%d", &acao);
		if ((acao != (1)) && (acao != (0))) {
			printf("LOGIN: ");
			scanf("%d", &ID);

			erro = listaPerfis_procura(lista, ID, &copiaPerfil);

			//if (erro == SUCESSO) {
				//break;
			//}
			if (erro != SUCESSO)
			{
				printf("Perfil nao encontrado\n");
				printf("Voltando ao menu Inicial.....\n");
			}

			//acao = 6;
			//Checa se a ação escolhida precisa ou não de um login
			//No caso o gerenciamento de um perfil, que é feito po um user adm, e o
			while ((acao != 1) && (acao != 0))
			{

				switch (acao)
				{
				case ACAO_ABRIR_GERENCIAMENTO_DE_SEGUIDORES:
					MenuConhecimentos(grafo, copiaPerfil, lista);
					break;
				case ACAO_ABRIR_GERENCIAMENTO_DE_POSTAGEM:
					MenuPostagem(copiaPerfil->Postagens, ID);
					break;
				case ACAO_VISITAR_PERFIL:
					EntraremumPerfil(lista, copiaPerfil, grafo);
					printf("Digite o ID do perfil: ");
					scanf("%d", &IDPerfilVisitado);
					MenuCurtidas(copiaPerfil->Postagens, ID, IDPerfilVisitado);
					break;
				default:
					printf("Acao invalida, voltando para o menu inicial\n");
					break;
				}
				printf("|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
				printf("|Selecione um modulo da nossa rede social para abrir:\n\n\n"
					"|[1] GERENCIAMENTO DE PERFIS     - Modulo em que se pode cadastrar um novo perfil, procurar um perfil no sistema, apagar e procurar um perfil                                     |\n"
					"|[2] GERENCIAMENTO DE SEGUIDORES - Modulo onde voce pode seguir um perfil, deixar de seguir, ver quem voce segue e ver quem segue voce                                            |\n"
					"|[3] GERENCIAMENTO DE POSTAGEM   - Nesse modulo você pode fazer uma postagem em sua conta, apagar uma postagem em sua conta e visualizar e procurar todas as postagens no sistema |\n"
					"|[4] ABRIR UM PERFIL             - Nesse modulo voce pode ir ao perfil (usando o ID deste perfil) ver e curtir suas postagens, bem como ver seus amigos em comum                  |\n"
					"|[5] JOGO                        - Modulo adicional onde voce pode jogar o jogo da memoria                                                                                        |\n"
					"|[0] SAIR                        - Caso queira nos deixar :(:(:(:(                                                                                                                |\n"
				    "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
				scanf("%d", &acao);
			}
		}
		else {
			if (acao == ACAO_ABRIR_GERENCIAMENTO_DE_PERFIS) {
				MenuPerfil(lista);
			}
			else {
				printf("Obrigado por usar nossa rede social. Até mais []=[]=[]=[]=[]\n");
				return SUCESSO;
			}
		}

	}
	return SUCESSO;
}