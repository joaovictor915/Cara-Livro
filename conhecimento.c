/**
 * @file   conhecimento.c
 * @brief  Arquivo com as implentações de Fila.
 * @author João Victor MArtins
 * @date   17/11/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "conhecimento.h"
#include "erros.h"
//#include "perfil.h"
#include "fila.h"
#include "tipos.h"


typedef int bool;
typedef int TIPODADO;

#define BRANCO (0)
#define AMARELO (0 + 1)
#define VERMELHO (0 + 2)

/*
 *

itemPerfil_t* CriaAdj(int num, int peso) {
	itemListaPerfil_t* item = (itemListaPerfil_t*)malloc(sizeof(itemListaPerfil_t));

	InitAdj(item, num, peso);

	return item;
}
*/

/***

listaPerfis_t* CriaVert(itemListaPerfil_t* adj) {
	listaPerfis_t* item = (listaPerfis_t*)malloc(sizeof(listaPerfis_t));

	item->primeiro = adj;

	return item;
}*/

/*Função que inicializa o grafo de perfis
 *@param grafo: Apontador para o grafo que sera inicializado
 *@param nVertices: Numero de Usuario maximo permitido (1000)
 * 
 */
static void Initgrafo(grafo_t* grafo, int nVertices) {
	int i;


	grafo->nVertices = nVertices;
	grafo->nArestas = 0;
	grafo->itemListaPerfil = (listaPerfis_t*)malloc(nVertices * sizeof(listaPerfis_t));

	//inicializa cada uma dos vertices (perfis) do grafo com o valor nulo
	for (i = 0; i < nVertices; i++) {
		grafo->itemListaPerfil[i].primeiro = NULL;
	}
}

/*Função que Cria o grafo de perfis
 *@param nVertices: Numero de vertices que deve ter o grafo
 *@return grafo: Apontador para o lugar da memória onde foi alocado o espaço para a estrutura grafo
 */
grafo_t* CriaGrafo(int nVertices) {
	int i;

	grafo_t* grafo;

	grafo = (grafo_t*)malloc(sizeof(grafo_t));

	//Inicializa o grafo
	Initgrafo(grafo, nVertices);

	//Faz com que o numero de itens em todos os vertices (item perfis) do grafo tenham nItens igual a zero
	for (i = 0; i < nVertices; i++) {
		grafo->itemListaPerfil[i].nItens = 0;
	}

	return grafo;
}


/*Função que cria um relacionamento entre um perfil e outro (perfil X passa a seguir o perfil Y)
 *@param grafo: Apontado para o grafo de perfis
 *@param Verti: ID do perfil que está criando um relacionamento com o outro, que corresponde ao vertice do grafo onde estao todos os relacionamentps desse perfil
 *@param Vertf: ID do perfil que está "sendo seguido", correspondente ao vertice do grafo que corresponde a este perfil
 *@param peso : dados do perfil que serão inseridos na lista de adjacência
 *@return novo: retorna o apontador para o Perfil criado 
 */
erro_t CriaAresta(grafo_t* grafo, int Verti, int Vertf, dadosItem_t* peso) {
	itemListaPerfil_t* novo = CraItemLista(peso->nome, peso->Cidade, peso->email, peso->id, peso->telefone);
	//Verifica se o numero de vertices é igual a zero, ou seja, nenhuma relação pode ser estabelecida
	if (grafo->nVertices == 0) {
		return ERRO_GRAFO_NAO_INICIALIZADO;
	}
	//Verifica se os IDs passados não excedem o permitido, ou que faltam
	if ((Verti > grafo->nVertices) || (Vertf > grafo->nVertices)) {
		return ERRO_VERTICE_INEXISTENTE;
	}

	//Cria o relacionamento e a insere no grafo
	novo->proximo = grafo->itemListaPerfil[Verti].primeiro;

	grafo->itemListaPerfil[Verti].primeiro = novo;

	grafo->itemListaPerfil[Verti].nItens++;

	grafo->nArestas++;

	return SUCESSO;
}

/*Função que desfaz um relacionamento entre um Perfil X e um Perfil Y (Unfollow)
 *@param grafo: Apontado para o grafo de perfis
 *@param Verti: ID do perfil que está destruindo um relacionamento com o outro, que corresponde ao vertice do grafo onde estao todos os relacionamentps desse perfil
 *@param Vertf: ID do perfil que está "deixando de ser seguido", correspondente ao vertice do grafo que corresponde a este perfil
 *@param copia: Variavel que guarda a copia do perfil que foi buscado
 * 
 */
erro_t desfazAresta(grafo_t* grafo, int Verti, int Vertf, itemListaPerfil_t** copia) {
	itemListaPerfil_t* novo = grafo->itemListaPerfil[Verti].primeiro;
	itemListaPerfil_t* aux = NULL;
	erro_t erro;

	//Confere se o grafo tem um numero de vertices valido
	if (grafo->nVertices == 0) {
		return ERRO_GRAFO_NAO_INICIALIZADO;
	}
	//Confere se os IDs passados sao validos, ou seja dentro do intervalo de 0 a 999
	if ((Verti > grafo->nVertices) || (Vertf > grafo->nVertices)) {
		return ERRO_VERTICE_INEXISTENTE;
	}

	//Vai até o vertice correspondente ao perfil que quer deixar de seguir o outro
	erro = BuscaemProfundidade(grafo, Vertf, &aux);


	//Remove o perfil Y da lista de perfis que eram seguidos pelo perfil X
	listaPerfis_remove(grafo->itemListaPerfil, aux->dados->id);

	//Guarda o valor que estava em aux (perfil que recebeu unfollow) na variável copia
	*copia = aux;

	//Se chegou até aqui é porque deu tudo certo 
	return SUCESSO;

}

/*Função que imprime todos os itens do grafo
 *@param grafo: apontador para o grafo onde estão os perfis a serem impressos
 *
 */

void imprimegrafo(grafo_t* grafo) {
	int i;
	itemListaPerfil_t* adj;

	//Enquanto i estiver dentro da faixa de vertices maxima do grafo
	for (i = 0; i < grafo->nVertices; i++) {

		//adj é igual ao primeiro perfil da lista de perfis do grafo
		adj = grafo->itemListaPerfil[i].primeiro;
		printf("%d:  ", i);
		//Enquanto não for um valor nulo, imprime os perfis presentes na lista
		while (adj != NULL) {
			itemimprime(grafo->itemListaPerfil[i].primeiro);

			//Controla o link da lista
			adj = adj->proximo;
		}

		//quebra de linha pra ficar organizado ;)
		printf("\n");
	}
}
/*Função que realiza a busca no grafo de perfis a fum de encontrar um item com o ID fornecido
 *@param grafo: Apontador para o grafo onde a busca sera feita
 *@param i    : Posicao no grafo onde se encontra o perfil buscado
 *@param Busca: Tipo de dado a ser buscado, neste caso o ID do perfil
 *@param copia   : Endereço onde sera armazenada a cópia do perfil que foi encontrado
 *@return        : Codigo de errro da função
 */
erro_t Profundidade(grafo_t* grafo, int i, cor_t* cores, TIPODADO Busca, itemListaPerfil_t** copia) {
	itemListaPerfil_t* adj = grafo->itemListaPerfil[i].primeiro;

	//Como o vertice é recem visitado, recebe a cor amarela
	cores[i] = AMARELO;

	
	while (adj != NULL) {
		//Se o vertice onde se encontra pode se perfil for diferente de nulo
		if (cores[adj->vertice] == BRANCO) {
			//Checa se os IDs batem 
			if (adj->dados->id == Busca) {

				//guarda na variavel copia o valor do perfil entrado
				*copia = adj;

				//Imprime os perfis da lista de 
				itemimprime(copia);
				return SUCESSO;
			}
			//recursivo uhuuu
			Profundidade(grafo, adj->vertice, cores, Busca, copia);
		}
		//Controla os links da listaa
		adj = adj->proximo;
	}

	//Se chegou aqui é porque todos os vertices foram visitados e o item não foi encontrado
	cores[i] = VERMELHO;

	//retorna codigo de erro para item não encontrado no grafo
	return GRAFO_ITEM_NAO_ENCONTRADO;
}


/*Função que realiza a busca em profundidade
 *@param grafo: apontador para o grafo de perfis onde o perfil é procurado
 *@param busca: Tipo do dado que serve como parâmetro para ser buscado, neste caso, o ID do perfil
 *@param copia: Variável que contém o endereço de onde será guardada uma cópia do perfil encontrado
 *@return     : codigo de erro 
 */

erro_t BuscaemProfundidade(grafo_t* grafo, TIPODADO busca, itemListaPerfil_t** copia) {
	int i;
	cor_t* cores = (cor_t*)malloc(grafo->nVertices * sizeof(cor_t));

	for (i = 0; i < grafo->nVertices; i++) {
		cores[i] = BRANCO;
	}
	for (i = 0; i < grafo->nVertices; i++) {
		if (cores[i] == BRANCO) {
			if (Profundidade(grafo, i, cores, busca, copia) == SUCESSO);

		}
	}

	return GRAFO_ITEM_NAO_ENCONTRADO;
}

/*Função que visita um vetice especifico do grafo, ou seja, vê todos aqueles a quem o Perfil de ID correspondente a posição no grafo segue
 *@param grafo: Apontador para o grafo de PErfis
 *@param vertice: ID do Perfil que corresponde a posição no grafo onde estão guardados os perfis a que ele segue
 */

erro_t VisitaVerticeEspecifico(grafo_t* grafo, int vertice) {
	itemListaPerfil_t* adj = grafo->itemListaPerfil[vertice].primeiro;

	if (grafo->nVertices == 0) {
		return ERRO_GRAFO_NAO_INICIALIZADO;
	}

	while (adj != NULL)
	{
		itemimprime(adj);
		adj = adj->proximo;
	}
	return SUCESSO;
}

/*Função que visita a largura do grafo
 *@param grafo   : estrutura do tipo grafo_t a ter sua largura visitada (serve para definir a distancia em vertices entre um verticce e outro
 *@param i       : largura a ser visitada  
 *@param explora : parametro que explora todos os itens do grafo
 *@param GrauExigido: N amigos em comum passados pelo usuário, limitação de até onde vai a busca
 */
void VisitaLargura(grafo_t* grafo, int i, int* explora, int N) {
	int grau;
	grau = 0;
	fila_t Fila;
	registro_t* aux = (registro_t*)malloc(sizeof(registro_t));
	itemListaPerfil_t* aresta = grafo->itemListaPerfil->primeiro;

	explora[i] = EXPLORADO;
	InicializaFila(&Fila);
	aux->chave = i;
	AddNaFila(&Fila, *aux);

	while (Fila.inicio) {

		//Tira o item que está sendo visitado da fila, e salva seus dados em uma copia
		TiraDaFila(&Fila, aux);

		while (aresta) {
			//Explora as arestas
			if (explora == EXPLORADO) {
				explora[aresta->vertice] = NAOEXPLORADO;
				aux->chave = aresta->vertice;

				//imprime o dados do item encontrado
				printf("@%06d\t: ", grafo->itemListaPerfil->primeiro->dados->id);
				printf("%s\n", grafo->itemListaPerfil->primeiro->dados->nome);

				//adiciona o aux, que agora tem novo valor a fila
				AddNaFila(&Fila, *aux);
			}
			aresta = aresta->proximo;
		}

		// Limita até onde vai a busca, o N definido pelo programador
		grau++;
		if (grau == N) {
			break;
		}
	}
	free(aux);
}

/*Função que realiza a busca em largura, que serve para mostrar os N perfis de proximidade N entre um perfil X e outro Y
 *@param grafo: estrutura do tipo grafo
 *@param IDPerfilAtivo: ID do perfil que está realizando a busca, para o qual se deve falar os N perfis de proximidade com o outro
 * @return : codigo de erro para a busca
 */

erro_t Largura(grafo_t* grafo, uint32_t IDPerfilAtivo) {
	bool_t* explora = (int*)malloc(grafo->nVertices * sizeof(int*));
	int i, GrauExigido;
	uint32_t PosPerfilAtivado;
	int VerifValidez = -1;

	//Grau exigido definido pelo programador
	GrauExigido = 2;

	//Testa se o ID está dentro da faixa válda
	for (i = 0; i < grafo->nVertices; i++) {
		if (grafo->itemListaPerfil == NULL) return ERRO_GRAFO_NAO_INICIALIZADO;
		if (grafo->itemListaPerfil->primeiro == NULL) return ERRO_GRAFO_NAO_INICIALIZADO;
		if (grafo->itemListaPerfil->primeiro->dados->id == IDPerfilAtivo) {
			// Pega a posição no vetor para depois percorrê-la novamente
			PosPerfilAtivado = i;
			VerifValidez = 1;
			break;
		}
		if (i > IDPerfilAtivo) {
			return ERRO_PERFIL_NAO_ENCONTRADO;
		}
	}
	//Se o valor do verifica nao foi alterado significa que nenhum dos itens foi encontrado
	if (VerifValidez == -1) {
		return ERRO_PERFIL_NAO_ENCONTRADO;
	}

	for (i = 0; i < grafo->nVertices; i++) {
		explora[i] = NAOEXPLORADO;
	}
	VisitaLargura(grafo, i, explora[PosPerfilAtivado], GrauExigido);

	return SUCESSO;
}



/*Função que faz todas as operações necessárias ao menu de Conhecimentos
 *@param grafo: Apontador para o grafo de perfis
 *@param perfil: Perfil Ativo no momento
 *@param lista: lista que contém todos os perfis existentes no sistema
 */

void MenuConhecimentos(grafo_t* grafo, itemListaPerfil_t* perfil, listaPerfis_t* lista) {
	itemListaPerfil_t* Quemestaseguindo = perfil;
	itemListaPerfil_t* Quemestasendoseguido = NULL;
	int acao = 1, aux;
	erro_t erro;
	uint32_t ID;

	while (acao!=0)
	{
		printf("Bem vindo ao menu de conhecimentos, aqui voce pode escolher seguir, deixar de seguir, e ver quem o perfil segue\n");
		printf("Selecione o que deseja fazer\n"
			"[1] Seguir um Perfil\n"
			"[2] Deixar de seguir um Perfil\n"
		    "[3] Ver quem voce segue\n"
		    "[0] Sair\n");
		scanf("%d", &acao);

		switch (acao) {
		case ACAO_SEGUIR_PERFIL:
			printf("Quer que a lista de perfis existentes seja impressa para conferir o ID do usuario que deseja seguir\n?"
				"[0] NAO\n"
				"[1] SIM\n");
			scanf("%d", &aux);
			if (aux == VERDADEIRO) {
				listaPerfisimprime(lista);
			}
			printf("Digite o ID do perfil que deseja seguir: ");
			scanf("%d", &ID);
			erro = listaPerfis_procura(lista, ID, &Quemestasendoseguido);
			CriaAresta(grafo, Quemestaseguindo->vertice, ID, Quemestasendoseguido->dados);
			printf("Agora voce segue o perfil de ID %d\n", ID);
			break;

		case ACAO_DEIXAR_DE_SEGUIR_PERFIL:
			printf("Quer que a lista de perfis existentes seja impressa para conferir o ID do usuario que deseja seguir?\n"
				"[0] NAO\n"
				"[1] SIM\n");
			scanf("%d", &aux);
			if (aux == VERDADEIRO) {
				listaPerfisimprime(lista);
			}
			printf("Digite o ID do perfil que deseja seguir: ");
			scanf("%d", &ID);
			erro = listaPerfis_procura(lista, ID, &Quemestasendoseguido);
			desfazAresta(grafo, Quemestaseguindo->vertice, ID, &Quemestasendoseguido);
			break;

		case ACAO_VER_QUEM_SIGO:
			printf("Numero de pessoas que voce segue: %d\n", grafo->itemListaPerfil[Quemestaseguindo->dados->id].nItens);

			erro = VisitaVerticeEspecifico(grafo, Quemestaseguindo->dados->id);
			break;

		case ACAO_SAIR_MENU_CONHECIMENTOS:
			break;
		default:
			printf("Acao invalida\n");
			break;
		}




	}
}










