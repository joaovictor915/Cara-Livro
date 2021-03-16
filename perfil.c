/**
 * @file   perfil.c
 * @brief  Arquivo com as implentações de perfil.h.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "perfil.h"
#include "erros.h"
#include "tipos.h"
#include "postagens.h"
#include "conhecimento.h"
/*Função que inicializa o item de perfis da lista
 * @param           item : Apontador para o item da lista de perfis a ser iniciado
 * @param           id   : Codigo unico que identifico o perfil
 * @param           nome: Vetor de caracteres que contém o nome do PErfil criado
 * @param           cidade: Vetor de cracteres que contém o nome da cidade onde o usuário mora
 * @param           email: Vetor de caracteres que contém o email do usuário que está criando um perfil
 * @param           telefone: inteiro sem sinal que contém o número de telefone do usuário
 */
static void InitItemPerfil(itemListaPerfil_t* item, int id, char nome[TAMANHOMAXIMONOMEPERFIL],
	char cidade[TAMANHOMAXIMONOMECIDADE], char email[TAMANHOMAXIMOEMAIL], uint32_t telefone) {
	dadosItem_t* dados = (dadosItem_t*)malloc(sizeof(dadosItem_t));


	dados->id = id;
	strcpy(dados->nome, nome);
	strcpy(dados->Cidade, cidade);
	strcpy(dados->email, email);
	dados->telefone = telefone;

	item->dados = dados;
	item->proximo = NULL;
	item->vertice = id;
	item->Postagens = CriaListaPostagensVazia();

}


/*Função que cria o item da lista perfis 
 * @param           id   : Codigo unico que identifico o perfil
 * @param           nome: Vetor de caracteres que contém o nome do PErfil criado
 * @param           cidade: Vetor de cracteres que contém o nome da cidade onde o usuário mora
 * @param           email: Vetor de caracteres que contém o email do usuário que está criando um perfil
 * @param           telefone: inteiro sem sinal que contém o número de telefone do usuário
 * @return          ponteiro para o local onde o item foi colocado e inicializado
 */

itemListaPerfil_t* CraItemLista(char nome[TAMANHOMAXIMONOMEPERFIL], char cidade[TAMANHOMAXIMONOMECIDADE],
	char email[TAMANHOMAXIMOEMAIL], uint32_t id, uint32_t telefone) {
	itemListaPerfil_t* item = (itemListaPerfil_t*)malloc(sizeof(itemListaPerfil_t));

	InitItemPerfil(item, id, nome, cidade, email, telefone);

	return item;
}

/*Função que inicializa a lista de perfis vazia
 *@param            item: Apontador para a lista de perfis a ser inicializada
 */

static void InitLista(listaPerfis_t * item) {

	item->primeiro = NULL;
	item->nItens = 0;

}


/*Funçaõ que cria a lista inicialmente vazia
 *@return            item: Apontador para o local da memória onde a lista de perfis foi alocada
 */
listaPerfis_t* CriaListaVazia() {
	listaPerfis_t* item = (listaPerfis_t*)malloc(sizeof(listaPerfis_t));

	InitLista(item);

	return item;
}

/*Função que insere um novo item na lista, sempre na ultima posição
 *@param          lista: Apontador para a lista de perfi onde o novo item deve ser colocado
 *@param          novoItem: apontador para o novo item a ser colocado na lista
 */

erro_t ListaPerfis_InserenoFinal(listaPerfis_t* lista, itemListaPerfil_t* novoItem) {
	int i;
	itemListaPerfil_t* atual;

	if (novoItem == NULL) {
		return ERRO_PERFIL_NAO_INICIALIZADO;
	}


	if (lista->nItens == 0) {
		novoItem->proximo = lista->primeiro;
		lista->primeiro = novoItem;
		lista->nItens++;
	}
	else{

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


/*Função que imprime os componentes de um item da lista de perfis
 *@param:           item: Apontador para o item Perfil a ser impresso
 */
void itemimprime(itemListaPerfil_t* item) {
	dadosItem_t* dados = item->dados;
	printf("ID: @%06d\n NOME: %-40s\nCIDADE: %-29s\EMAIL %-41s\nTELEFONE %-09d\n", dados->id, dados->nome, dados->Cidade, dados->email,  dados->telefone);


}


/*Funçaõ que imprime todos os perfis existentes a lista de perfis
 *@param             lista: Apontador para a lista a ser impressa      
 *
 ***/
erro_t listaPerfisimprime(listaPerfis_t* lista) {
	itemListaPerfil_t* atual;
	itemListaPerfil_t* proximo = lista->primeiro;

	printf("Numero de perfis existentes na rede social : %d\n", lista->nItens);
	printf("Imprimindo dados dos perfis.........\n"\
		"\n----------------------------------------------------\n");

	if (proximo == NULL) {
		return ERRO_LISTA_PERFISVAZIA;
	}

	// Imprime posicao e o valor de cada item da lista
	while (proximo != NULL) {

		// Controla os links da lista
		atual = proximo;
		proximo = atual->proximo;

		itemimprime(atual);
	}
	printf("Fim da impressao\n");
	printf("\n----------------------------------------------------------------------------\n");

	return SUCESSO;
}


bool_t listaPerfis_remove(listaPerfis_t* lista, uint32_t info) {

	itemListaPerfil_t* anterior = NULL;
	itemListaPerfil_t* atual = lista->primeiro;

	// Percore os elementos da lista procurando aquele cuja informação é a desejada
	while (atual != NULL) {
		if (atual->dados->id == info) break;
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
erro_t listaPerfis_procura(listaPerfis_t* lista, uint32_t info, itemListaPerfil_t** copia) {

	itemListaPerfil_t* anterior = NULL;
	itemListaPerfil_t* atual = lista->primeiro;

	// Percore os elementos da lista procurando aquele cuja informação é a desejada
	while (atual != NULL) {
		if (atual->dados->id == info) break;
		anterior = atual;
		atual = atual->proximo;
	}

	// Verifica se o item foi encontrado, ou seja, se o atual não é nulo
	if (atual == NULL) { return ERRO_PERFIL_NAO_ENCONTRADO; }

	// Se chegou aqui é porque encontrou o item desejado e ele está no atual
	*copia = atual;


	return SUCESSO;
}



//Função reposável por gerar o ID de cada perfil, um código unico que é diferente para todos os perfis
//@return O codigo do perfil
uint32_t geraIDPerfil(void) {
	static uint32_t codPerfil = 0;
	return codPerfil++;
}

/*
 *
 *
 */
static void MenucadastroPerfil(itemListaPerfil_t** Perfil) {
	char nome[TAMANHOMAXIMONOMEPERFIL];
    char cidade[TAMANHOMAXIMONOMECIDADE];
	char email[TAMANHOMAXIMOEMAIL];
	uint32_t telefone;
	uint32_t ID;
	int verifica = 0;

	printf("Começando a criar seu perfil......\n");

	while (verifica != 1)
	{
		getchar();
		printf("Digite seu nome completo: ");
		fgets(nome, TAMANHOMAXIMONOMEPERFIL, stdin);
		nome[strlen(nome) - 1] = '\0';
		printf("Digite seu email: ");
		fgets(email, TAMANHOMAXIMOEMAIL, stdin);
		email[strlen(email) - 1] = '\0';
		printf("Digite sua cidade: ");
		fgets(cidade, TAMANHOMAXIMONOMECIDADE, stdin);
		cidade[strlen(cidade) - 1] = '\0';
		printf("Digite seu numero de telefone (09 digitos): ");
		scanf("%d", &telefone);
		printf("NOME: %-40s\nEmail: %-41s\nCIDADE: %-29s\nTELEFONE %09d\n", nome, email, cidade, telefone);
		printf("Os dados conferem com o desejado?\n"
			"[1] SIM\n"
			"[0] NAO\n");
		scanf("%d", &verifica);
	}

	//gera o codigo unico do perfil

	ID = geraIDPerfil();

	//Se chegou até aqui é porque o usuario inseriu seus dados como desejado
	//Cria o perfil com os dados fornecidos pelo usuário
	*Perfil = CraItemLista(nome, cidade, email, ID, telefone);

}

/*
 *
 *
 *
 */

static void MenuremovePerfil(listaPerfis_t* lista) {
	uint32_t ID;
	bool_t bool;

	printf("Digite o ID do perfil que deseja remover\n");
	scanf("%d", &ID);
	bool = listaPerfis_remove(lista, ID);
	if (bool == FALSO) {
		printf("Esse perfil nao existe nesta rede social garotx :/\n");
	}
	else {
		printf("Perfil apagado com sucesso, caso queira voltar estaremos te esperando ;)\n");
	}
}

/*
 *
 *
 */

static void MenuprocuraPerfil(listaPerfis_t* lista ) {
	uint32_t ID;
	itemListaPerfil_t* copia;
	erro_t erro;

	printf("Digite o ID do perfil que deseja procurar\n");
	scanf("%d", &ID);
	erro = listaPerfis_procura(lista, ID, &copia);
	if (erro == ERRO_PERFIL_NAO_ENCONTRADO) {
		printf("Esse perfil nao existe nesta rede social garotx :/\n");
	}
	else {
		printf("Item Enontrado......\n");
		itemimprime(copia);
	}
}


/*
 *
 *
 */
void MenuPerfil(listaPerfis_t * lista) {
	int acao = 1;
	//bool_t bool;
	erro_t erro;
	itemListaPerfil_t* item = NULL;


	while (acao != 0) {
		printf("Selecione a operacao que deseja realizar\n"
			"[01] Criar novo perfil\n"
			"[02] Apagar um perfil\n"
			"[03] Ver todos os perfis existentes no sistema\n"
			"[04] Procurar por um perfil\n"
			"[00] Sair do Menu de gerenciamento de perfis\n");
		scanf("%d", &acao);

		switch (acao) {
		case ACAO_CADASTRO_PERFIL:
			MenucadastroPerfil(&item);
			ListaPerfis_InserenoFinal(lista, item);
			printf("Perfil criado com sucesso\n");
			break;

		case ACAO_REMOVER_PERFIL:
			MenuremovePerfil(lista);
			printf("Perfil de ID %d deletado\n", 1);
			break;

		case ACAO_VISUALIZA_PERFIS:
			erro = listaPerfisimprime(lista);
			if (erro == ERRO_LISTA_PERFISVAZIA) {
				printf("Cri Cri Cri\n"
					"Nao existe nenhum usuario cadastrado nesta rede social ze\n");
			}
			else {
				printf("Acao concluida.\n");
			}
			break;

		case ACAO_PROCURA_PERFIS:
			MenuprocuraPerfil(lista);
			break;

		case ACAO_SAIR_MENU_PERFIL:
			break;

		default:
			printf("Acao selecionada invalida\n");
			break;
		}
	}

	printf("Fechando o Menu de gerenciamento de perfis..........\n");
}




