#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {
	int NIF;
	char Nome[100];
	char Morada[100];
	int Telefone;
	char ListaCompras[100];
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