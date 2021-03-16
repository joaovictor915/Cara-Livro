/**
 * @file   postagens.c
 * @brief  Arquivo com as implentações de postagens.h.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "perfil.h"
#include "postagens.h"
#include "erros.h"
#include "tipos.h"

/*Função que inicializa o item de Postagens da lista
 * @param           item : Apontador para o item da lista de Postagens a ser iniciado
 * @param           id   : Codigo unico que identifico o Postagem
 * @param           nome: Vetor de caracteres que contém o nome do Postagem criado
 * @param           cidade: Vetor de cracteres que contém o nome da cidade onde o usuário mora
 * @param           email: Vetor de caracteres que contém o email do usuário que está criando um Postagem
 * @param           telefone: inteiro sem sinal que contém o número de telefone do usuário
 */
static void InitItemPostagem(itemListapostagem_t* item, uint32_t id, char titulo[TAMANHOMAXIMOTITULOPOSTAGEM],
	char texto[TAMANHOMAXIMOTEXTOPOSTAGEM]) {
	dadospostagem_t* dados = (dadospostagem_t*)malloc(sizeof(dadospostagem_t));

	dados->idPerfil = id;
	dados->idPostagem = geraIDPostagem();
	strcpy(dados->texto, texto);
	strcpy(dados->titulo, titulo);

	item->tabelaQuemCurtiu = CriaTabela();
	item->dados = dados;
	item->proximo = NULL;
	item->vertice = id;
	//item->tabelaQuemCurtiu = CriaTabela();
}


/*Função que cria o item da lista Postagens
 * @param           id   : Codigo unico que identifico o Postagem
 * @param           nome: Vetor de caracteres que contém o nome do Postagem criado
 * @param           cidade: Vetor de cracteres que contém o nome da cidade onde o usuário mora
 * @param           email: Vetor de caracteres que contém o email do usuário que está criando um Postagem
 * @param           telefone: inteiro sem sinal que contém o número de telefone do usuário
 * @return          ponteiro para o local onde o item foi colocado e inicializado
 */

itemListapostagem_t* CriaItemListaPostagens(char Titulo[TAMANHOMAXIMOTITULOPOSTAGEM], char Texto[TAMANHOMAXIMOTEXTOPOSTAGEM],
                                   uint32_t id) {
	itemListapostagem_t* item = (itemListapostagem_t*)malloc(sizeof(itemListapostagem_t));

	InitItemPostagem(item, id, Titulo, Texto);

	return item;
}

/*Função que inicializa a lista de Postagens vazia
 *@param            item: Apontador para a lista de Postagens a ser inicializada
 */

static void InitLista(listapostagens_t* item) {

	item->primeiro = NULL;
	item->nItens = 0;

}


/*Funçaõ que cria a lista inicialmente vazia
 *@return            item: Apontador para o local da memória onde a lista de Postagens foi alocada
 */
listapostagens_t* CriaListaPostagensVazia() {
	listapostagens_t* item = (listapostagens_t*)malloc(sizeof(listapostagens_t));

	InitLista(item);

	return item;
}

/*Função que insere um novo item na lista, sempre na ultima posição
 *@param          lista: Apontador para a lista de perfi onde o novo item deve ser colocado
 *@param          novoItem: apontador para o novo item a ser colocado na lista
 */

erro_t ListaPostagens_InserenoFinal(listapostagens_t* lista, itemListapostagem_t* novoItem) {
	int i;
	itemListapostagem_t* atual;

	if (novoItem == NULL) {
		return ERRO_POSTAGEM_NAO_INICIALIZADA;
	}


	if (lista->nItens == 0) {
		novoItem->proximo = lista->primeiro;
		lista->primeiro = novoItem;
		lista->nItens++;
	}
	else {

		atual = lista->primeiro;

		for (i = 0; i < (lista->nItens - 1); i++) {
			atual = atual->proximo;
		}
		novoItem->proximo = atual->proximo;
		atual->proximo = novoItem;
		lista->nItens++;
	}

	return SUCESSO;
}


/*Função que imprime os componentes de um item da lista de Postagens
 *@param:           item: Apontador para o item Postagem a ser impresso
 */
void itemPostagemimprime(itemListapostagem_t* item) {
	dadospostagem_t* dados = item->dados;
	printf("\t@%d\t\nTITULO: %-40s\nTEXTO%-140sID DA POSTAGEM: %-09d\n",dados->idPerfil, dados->titulo, dados->texto, dados->idPostagem);

	printf("Quem Curtiu:\n");
	imprimeTabelahash(item->tabelaQuemCurtiu);
}


void itemPostagemimprimeSimples(itemListapostagem_t* item, uint32_t ID) {
	dadospostagem_t* dados = item->dados;
	bool_t ver;
	printf("\t@%09d\t\nTITULO: %-40s\nTEXTO: %-140s\nID DA POSTAGEM: %-09d\n", dados->idPerfil, dados->titulo, dados->texto, dados->idPostagem);
	if (CurtiuNaoCurtiu(item->tabelaQuemCurtiu, ID) == VERDADEIRO) {
		printf("S2 Voce curtiu essa postagem\n");
	}
}

/*Funçaõ que imprime todos os Postagens existentes a lista de Postagens
 *@param             lista: Apontador para a lista a ser impressa
 *
 ***/
erro_t listaPostagensimprime(listapostagens_t* lista) {
	itemListapostagem_t* atual;
	itemListapostagem_t* proximo = lista->primeiro;

	printf("Numero de postagens existentes na rede social : %d\n", lista->nItens);
	printf("Imprimindo dados das Postagens.........\n"\
		"\n----------------------------------------------------\n");

	if (proximo == NULL) {
		return ERRO_LISTA_POSTAGENSVAZIA;
	}

	// Imprime posicao e o valor de cada item da lista
	while (proximo != NULL) {

		// Controla os links da lista
		atual = proximo;
		proximo = atual->proximo;

		itemPostagemimprime(atual);
	}
	printf("Fim da impressao\n");
	printf("\n----------------------------------------------------------------------------\n");

	return SUCESSO;
}

/*Funçaõ que imprime todos os Postagens existentes a lista de Postagens
 *@param             lista: Apontador para a lista a ser impressa
 *
 ***/
erro_t listaPostagensimprimeNpostagens(listapostagens_t* lista, uint32_t ID) {
	itemListapostagem_t* atual;
	int i = 0;
	itemListapostagem_t* proximo = lista->primeiro;

	printf("Imprimindo dados das Postagens.........\n"\
		"\n----------------------------------------------------\n");

	if (proximo == NULL) {
		return ERRO_LISTA_POSTAGENSVAZIA;
	}

	// Imprime posicao e o valor de cada item da lista
	while ((proximo != NULL) &&(i < NUMERO_ITENS_POSTEGENS_IMPRESSOS)) {
		//Controla o numero maximo de postagens a serem impressos

		atual = proximo;
		proximo = atual->proximo;

		itemPostagemimprimeSimples(atual, ID);
		//controla o numero maximo de postagens a ser impresso
		i++;
	}
	printf("Fim da impressao\n");
	printf("\n----------------------------------------------------------------------------\n");

	return SUCESSO;
}

bool_t listaPostagens_remove(listapostagens_t* lista, uint32_t info) {

	itemListapostagem_t* anterior = NULL;
	itemListapostagem_t* atual = lista->primeiro;

	// Percore os elementos da lista procurando aquele cuja informação é a desejada
	while (atual != NULL) {
		if (atual->dados->idPostagem == info) break;
		anterior = atual;
		atual = atual->proximo;
	}

	// Verifica se o item foi encontrado, ou seja, se o atual não é nulo
	if (atual == NULL) { return FALSO; }

	// Se chegou aqui é porque encontrou o item desejado e ele está no atual
	// Se o anterior é nulo, então é porque o item encontrado é o primeiro da lista ...
	if (anterior == NULL) {
		lista->primeiro = atual->proximo;
	}
	// ... senão, então ele pode estar em qualquer lugar, mas garantidamente não é o primeiro
	else {
		anterior->proximo = atual->proximo;
	}

	// Se chegou até aqui é porque o item foi removido corretamente da cadeia
	free(atual);
	lista->nItens--;
	return VERDADEIRO;
}

/*
 *
 *
 */
erro_t listaPostagens_procura(listapostagens_t* lista, uint32_t info, itemListapostagem_t** copia) {

	itemListapostagem_t* anterior = NULL;
	itemListapostagem_t* atual = lista->primeiro;

	// Percore os elementos da lista procurando aquele cuja informação é a desejada
	while (atual != NULL) {
		if (atual->dados->idPostagem == info) break;
		anterior = atual;
		atual = atual->proximo;
	}

	// Verifica se o item foi encontrado, ou seja, se o atual não é nulo
	if (atual == NULL) { return ERRO_POSTAGEM_NAO_ENCONTRADA; }

	// Se chegou aqui é porque encontrou o item desejado e ele está no atual
	*copia = atual;


	return SUCESSO;
}

itemListapostagem_t* listaPostagens_procuraeRetorna(listapostagens_t* lista, uint32_t info, itemListapostagem_t** copia) {

	itemListapostagem_t* anterior = NULL;
	itemListapostagem_t* atual = lista->primeiro;

	// Percore os elementos da lista procurando aquele cuja informação é a desejada
	while (atual != NULL) {
		if (atual->dados->idPostagem == info) break;
		anterior = atual;
		atual = atual->proximo;
	}

	// Verifica se o item foi encontrado, ou seja, se o atual não é nulo
	if (atual == NULL) { return NULL; }

	// Se chegou aqui é porque encontrou o item desejado e ele está no atual
	*copia = atual;


	return atual;
}



//Função reposável por gerar o ID de cada Postagem, um código unico que é diferente para todos os Postagens
//@return O codigo do Postagem
uint32_t geraIDPostagem(void) {
	static uint32_t codPostagem = 0;
	return codPostagem++;
}

/*
 *
 *
 */
static void MenucadastroPostagem(itemListapostagem_t** Postagem, uint32_t ID) {
	char titulo[TAMANHOMAXIMOTITULOPOSTAGEM];
	char texto[TAMANHOMAXIMOTEXTOPOSTAGEM];
	int verifica = 0;

	printf("Começando a criar sua Postagem......\n");

	while (verifica != 1)
	{
		getchar();
		printf("Digite o titulo da sua postagem: ");
		fgets(titulo, TAMANHOMAXIMOTITULOPOSTAGEM, stdin);
		titulo[strlen(titulo) - 1] = '\0';
		printf("Digite o texto da sua postagem: ");
		fgets(texto, TAMANHOMAXIMOTEXTOPOSTAGEM, stdin);
		titulo[strlen(texto) - 1] = '\0';


		printf("Titulo: %-40s\nTexto: %-140s\n ", titulo, texto);

		printf("Os dados conferem com o desejado?\n"
			"[1] SIM\n"
			"[0] NAO\n");
		scanf("%d", &verifica);
	}
	//gera um codigo de postagem unico paea cada post
	//Se chegou até aqui é porque o usuario inseriu seus dados como desejado
	//Cria o Postagem com os dados fornecidos pelo usuário
	*Postagem = CriaItemListaPostagens(titulo, texto, ID);

	
}

/*
 *
 *
 *
 */

static void MenuremovePostagem(listapostagens_t* lista) {
	uint32_t ID;
	bool_t bool;

	printf("Digite o ID do Postagem que deseja remover\n");
	scanf("%d", &ID);
	bool = listaPostagens_remove(lista, ID);
	if (bool == FALSO) {
		printf("Esse Postagem nao existe nesta rede social garotx :/\n");
	}
	else {
		printf("Postagem apagado com sucesso, caso queira voltar estaremos te esperando ;)\n");
	}
}

/*
 *
 *
 ***/
static void MenuProcuraPostagem(listapostagens_t* lista) {
	uint32_t ID;
	bool_t bool;
	itemListapostagem_t* copia;


	printf("Digite o ID da postagem que deseja procurar\n");
	scanf("%d", &ID);
	bool = listaPostagens_procura(lista, ID, &copia);
	if (bool == FALSO) {
		printf("Nao existe postagem com esse ID\n");
	}
	else {
		itemPostagemimprime(copia);
	}
}

/*
 *
 *
 */
void MenuPostagem(listapostagens_t* lista, uint32_t item) {
	int acao = 1;
	//bool_t bool;
	erro_t erro;
	itemListapostagem_t* iteminsere = NULL;


	while (acao != 0) {
		printf("Selecione a operacao que deseja realizar\n"
			"[01] Criar nova Postagem\n"
			"[02] Apagar uma Postagem\n"
			"[03] Ver todas as Postagens existentes no sistema\n"
			"[04] Procurar por uma Postagem\n"
			"[00] Sair do Menu de gerenciamento de Postagens\n");
		scanf("%d", &acao);

		switch (acao) {
		case ACAO_FAZ_POSTAGEM:
			MenucadastroPostagem(&iteminsere, item);
			ListaPostagens_InserenoFinal(lista, iteminsere);
			printf("Postagem criado com sucesso\n");
			break;

		case ACAO_REMOVER_POSTAGEM:
			MenuremovePostagem(lista);
			printf("Postagem de ID %d deletado\n", 1);
			break;

		case ACAO_VISUALIZA_POSTAGENS:
			erro = listaPostagensimprime(lista);
			if (erro == ERRO_LISTA_POSTAGENSVAZIA) {
				printf("Cri Cri Cri\n"
					"Nao existe nenhum usuario cadastrado nesta rede social ze\n");
			}
			else {
				printf("Acao concluida.\n");
			}
			break;

		case ACAO_PROCURA_POSTAGENS:
			MenuProcuraPostagem(lista);
			break ;

		case ACAO_SAIR_MENU_POSTAGENS:
			break;

		default:
			printf("Acao selecionada invalida\n");
			break;
		}
	}

	printf("Fechando o Menu de gerenciamento de Postagens..........\n");
}


