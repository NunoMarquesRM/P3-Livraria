#include <stdio.h>
#include <stdlib.h>
#include "Encomenda.h"

typedef struct Cliente {
	int NIF;
	char Nome[100];
	char Morada[100];
	int Telefone;
	PNodoFila ListaCompras;
}CLIENTE;

struct NodoAB {
	CLIENTE  Elemento;
	struct NodoAB *Esquerda;
	struct NodoAB *Direita;
};

typedef struct NodoAB *PNodoAB;

PNodoAB CriarAB(){ 
	PNodoAB T;
	T = NULL;
	return T;
}

PNodoAB CriarNodoAB(CLIENTE X){
	PNodoAB P = (PNodoAB) malloc(sizeof(struct NodoAB));
	if (P == NULL)
		return  NULL;
	P->Elemento = X;
	P->Esquerda = NULL;
	P->Direita = NULL;
	return P;
}

int NumeroNodosAB (PNodoAB T) {
	int  e, d;
	if (T == NULL)
		return 0;
	e = NumeroNodosAB(T->Esquerda);
	d = NumeroNodosAB(T->Direita);
	return (e + d + 1);
}

int CompararElementosNIF (CLIENTE X, CLIENTE Y){
	if (X.NIF > Y.NIF)
		return 1;
	if (X.NIF < Y.NIF)
		return -1;
	return 0;
}

PNodoAB InserirABP (PNodoAB T, CLIENTE X){
	if (T == NULL) {
		T = CriarNodoAB(X);
		return T;
	}
	if (CompararElementosNIF(X, T->Elemento) == -1)   // X.NIF < (T->Elemento).NIF)
		T->Esquerda = InserirABP(T->Esquerda, X);
	else
		T->Direita = InserirABP(T->Direita, X);
	return T;
}

void ABPEqInsercaoBinaria (PNodoAB *TE, CLIENTE L[], int inicio, int fim) {
	int  meio;
	if (inicio > fim){
		return ;
	}
	if (inicio == fim){
		*TE = InserirABP(*TE, L[inicio]);
		return;
	}
	meio = (inicio + fim) / 2;
	*TE = InserirABP(*TE, L[meio]);
	ABPEqInsercaoBinaria(TE, L, inicio, meio-1);
	ABPEqInsercaoBinaria(TE, L, meio+1, fim);
}

void CriarSequenciaEmOrdem (PNodoAB T, CLIENTE L[], int *N){
	if (T != NULL){
		CriarSequenciaEmOrdem(T->Esquerda, L, N);
		L[*N] = T->Elemento;
		*N = (*N) + 1;
		CriarSequenciaEmOrdem(T->Direita, L, N);
	}
}

PNodoAB CriarABPEquilibradaIB (PNodoAB T){
	CLIENTE *Lista;
	PNodoAB TE;
	int  N = 0, Num;
	TE = CriarAB();
	Num = NumeroNodosAB(T);
	if (T == NULL){
		return NULL;
	}
	Lista = (CLIENTE *) malloc(Num * sizeof(CLIENTE));
	if (Lista == NULL){
		return NULL;
	}
	CriarSequenciaEmOrdem(T, Lista, &N);
	ABPEqInsercaoBinaria(&TE, Lista, 0, N-1);
	return TE;
}

int PesquisarABP (PNodoAB T, CLIENTE X){   // 0 = nao existe; 1 = existe
	if (T == NULL)
		return 0;
	if (CompararElementosNIF(X, T->Elemento) == 0)
		return 1;
	if (CompararElementosNIF(X, T->Elemento) == -1)   // X.NIF < (T->Elemento).NIF)
		return PesquisarABP(T->Esquerda, X);
	else
		return PesquisarABP(T->Direita, X);
}

//Pesquisar por Cliente
CLIENTE PesquisarClienteAlterar(PNodoAB T, CLIENTE C){
	if (T == NULL)
		return T->Elemento;
	if (CompararElementosNIF(C, T->Elemento) == 0)
		return T->Elemento;
	if (CompararElementosNIF(C, T->Elemento) == -1)   // X.NIF < (T->Elemento).NIF)
		return PesquisarClienteAlterar(T->Esquerda, C);
	else
		return PesquisarClienteAlterar(T->Direita, C);
}

void MostrarCliente (CLIENTE X){
	printf("%d  \n", X.NIF);
	printf("%s  \n", X.Nome);
	printf("%s  \n", X.Morada);
	printf("%d  \n", X.Telefone);
	printf("%s  \n", X.ListaCompras);
}

void ListarEmOrdemAB (PNodoAB T) {
	if (T != NULL) {
		ListarEmOrdemAB(T->Esquerda);
		MostrarCliente(T->Elemento);
		ListarEmOrdemAB(T->Direita);
	}
}
// Remover
PNodoAB LibertarNodoAB(PNodoAB P){
	P->Esquerda = NULL;
	P->Direita = NULL;
	free(P);
	P = NULL;
	return P;
}

PNodoAB SubstituirNodoDireita (PNodoAB T, CLIENTE *X){
	PNodoAB  PAux;
	if (T->Esquerda == NULL) {
		*X = T->Elemento;
		PAux = T;
		T = T->Direita;
		PAux = LibertarNodoAB(PAux);
		return T;
	}
	T->Esquerda = SubstituirNodoDireita(T->Esquerda, X);
	return T;
}
/*
PNodoAB SubstituirNodoEsquerda (PNodoAB T, CLIENTE *X){
	PNodoAB  PAux;
	if (T->Direita == NULL) {
		*X = T->Elemento;
		PAux = T;
		T = T->Esquerda;
		PAux = LibertarNodoAB(PAux);
		return  T;
	}
	T->Direita = SubstituirNodoEsquerda(T->Direita, X);
	return T;
}
*/
PNodoAB RemoverNodoABP (PNodoAB T){
	PNodoAB  R;
	CLIENTE  X;
	if (T->Esquerda == NULL && T->Direita == NULL) {   // T é uma folha
		T = LibertarNodoAB(T);
		return T;
	}
	if (T->Esquerda == NULL) {  // só um filho direito 
		R = T;
		T = T->Direita;
		R = LibertarNodoAB(R);
		return T;
	}
	if (T->Direita == NULL) {  // só um filho esquerdo
		R = T;
		T = T->Esquerda;
		R = LibertarNodoAB(R);
		return T;
	}
	// 2 filhos (1º caso): remover o nodo sucessor (nodo mais à esquerda da subárvore direita) e copiar a sua informação
	T->Direita = SubstituirNodoDireita(T->Direita, &X);
	// 2 filhos (2º caso): remover o nodo antecessor (nodo mais à direita da subárvore esquerda) e copiar a sua informação
	//  T->Esquerda = SubstituirNodoEsquerda(T->Esquerda, &X);  // 2º caso
	T->Elemento = X;
	return T;
}

PNodoAB RemoverABP (PNodoAB T, CLIENTE X) {
	if (CompararElementosNIF(X, T->Elemento) == 0) {
		T = RemoverNodoABP(T);
		return T;
	}
	if (CompararElementosNIF(X, T->Elemento) == -1)
		T->Esquerda = RemoverABP(T->Esquerda, X);
	else
		T->Direita = RemoverABP(T->Direita, X);
	return T;
}

// Consultar NIF
void ListarNIF (PNodoAB T, CLIENTE X) {
	if (T != NULL) {
		if (CompararElementosNIF(X, T->Elemento) == 0)
			MostrarCliente(T->Elemento);
		if (CompararElementosNIF(X, T->Elemento) == -1) // X.NIF < (T->Elemento).NIF)
			return ListarNIF(T->Esquerda, X);
		else
			return ListarNIF(T->Direita, X);
	}
}
// Consultar Nome
int CompararElementosNome(CLIENTE X, CLIENTE Y){
	if (strstr(X.Nome, Y.Nome) == NULL){
		return 1;
	}
	return 0;
}

void ListarNome(PNodoAB T, CLIENTE C){
	if(T != NULL){
		ListarNome(T->Esquerda, C);
		if (CompararElementosNome(T->Elemento, C) == 0) {
			MostrarCliente(T->Elemento);
		}
		ListarNome(T->Direita, C);
	}
}
// Consultar Morada
int CompararElementosMorada(CLIENTE X, CLIENTE Y){
	if (strstr(X.Morada, Y.Morada) == NULL){
		return 1;
	}
	return 0;
}

void ListarMorada(PNodoAB T, CLIENTE C){
	if(T != NULL){
		ListarMorada(T->Esquerda, C);
		if (CompararElementosMorada(T->Elemento, C) == 0) {
			MostrarCliente(T->Elemento);
		}
		ListarMorada(T->Direita, C);
	}
}
// Consultar Telefone
int CompararElementosTelefone (CLIENTE X, CLIENTE Y){
	if (X.NIF == Y.NIF){
		return 0;
	}
	return 1;
}

void ListarTelefone(PNodoAB T, CLIENTE C){
	if(T != NULL){
		ListarTelefone(T->Esquerda, C);
		if (CompararElementosTelefone(T->Elemento, C) == 0) {
			MostrarCliente(T->Elemento);
		}
		ListarTelefone(T->Direita, C);
	}
}

