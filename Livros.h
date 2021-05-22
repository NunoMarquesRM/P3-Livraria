#include <stdio.h>
#include <stdlib.h>

typedef struct Livro{
	int ISBN;
	char Titulo[100];
	char Idioma[100];
	char PrimeiroAutor[100];
	char SegundoAutor[100];
	char Editora[100];
	int Ano;
	char AreaCientifica[100];
	float Preco;
	int Quantidade;	
}LIVRO;

struct Nodo{
	LIVRO Elemento;
	struct Nodo *Prox;
	struct Nodo *Ant;
};
typedef struct Nodo *PNodo;

PNodo CriarNodo (LIVRO X){
	PNodo P;
	P = (PNodo)malloc(sizeof(struct Nodo));
	if (P == NULL)
		return NULL;
	P->Elemento = X;
	P->Prox = NULL;
	P->Ant = NULL;
	return P;
}

void InserirPrimeiroElemento (PNodo *Head, PNodo *Tail, LIVRO X){
	PNodo P;
	P = CriarNodo(X);
	if (P != NULL){
		*Head = P;
		*Tail = P;
	}
}

PNodo InserirCabeca (PNodo Head, LIVRO X){
	PNodo P;
	P = CriarNodo(X);
	if (P == NULL)
		return Head;
	P->Prox = Head;
	Head->Ant = P;
	Head = P;
	return Head;
}

void ConsultarLivro(LIVRO X){
	printf("%d  \n",X.ISBN);
	printf("%s  \n",X.Titulo);
	printf("%s  \n",X.Idioma);
	printf("%s  \n",X.PrimeiroAutor);
	printf("%s  \n",X.SegundoAutor);
	printf("%s  \n",X.Editora);
	printf("%d  \n",X.Ano);
	printf("%s  \n",X.AreaCientifica);
	printf("%.2f  \n",X.Preco);
	printf("%d  \n",X.Quantidade);
}

void Listar (PNodo Head){
	PNodo P = Head;
	while (P != NULL){
		ConsultarLivro(P->Elemento);
		P = P->Prox;
	}
}

int Tamanho (PNodo Head){
	PNodo P = Head;
	int  tam = 0; 
	while (P != NULL){
		tam++;
		P = P->Prox;
	} 
	return tam;
}


// Funções de Remover
PNodo LibertarNodo (PNodo P){ 
	free(P);
	P = NULL;
	return P;
}

int CompararElementos (LIVRO X, LIVRO Y){
	if (X.ISBN > Y.ISBN)
		return 1;
	if (X.ISBN < Y.ISBN)
		return -1;
	return 0;
}

PNodo Procurar (PNodo Head, LIVRO X){
	PNodo P = Head;
	while (CompararElementos(P->Elemento, X) != 0)
		P = P->Prox; 
	return P;
}

void RemoverUnicoElemento (PNodo *Head, PNodo *Tail){ 
	PNodo P = *Head;
	*Head = NULL;
	*Tail = NULL;
	P = LibertarNodo(P); 
}

PNodo RemoverCabeca (PNodo Head){ 
	PNodo P = Head;
	Head->Prox->Ant = NULL;
	Head = Head->Prox;
	P = LibertarNodo(P); 
	return Head;
}

PNodo RemoverCauda (PNodo Tail){ 
	PNodo P = Tail;
	Tail->Ant->Prox = NULL;
	Tail = Tail->Ant;
	P = LibertarNodo(P); 
	return Tail;
}

PNodo RemoverMeio (PNodo Head, LIVRO X){ 
	PNodo P;
	P = Procurar(Head, X);
	P->Ant->Prox = P->Prox;
	P->Prox->Ant = P->Ant;
	P = LibertarNodo(P); 
	return Head;
}

int ConsultarCabeca (PNodo Head, LIVRO X){
	PNodo P = Head;
	if (Head == NULL)
		return 0;
	while (CompararElementos(P->Elemento, X) != 0 && P->Prox != NULL)
		P = P->Prox; 
	if (CompararElementos(P->Elemento, X) == 0)
		return 1;
	return 0;
} 

void RemoverLivro(PNodo *Head, PNodo *Tail, int isbn){
	LIVRO LR;
	LR.ISBN = isbn;
	
	if(ConsultarCabeca(*Head, LR) == 1){
		// Lista com um único elemento
		if(*Head == *Tail){
			RemoverUnicoElemento(Head,Tail);
		}
		else{
			if(CompararElementos((*Head)->Elemento,LR) == 0){
				*Head = RemoverCabeca(*Head);
			}
			else{
				if(CompararElementos((*Tail)->Elemento,LR) == 0){
					*Tail = RemoverCauda(*Tail);
				}
				else{
					*Head = RemoverMeio(*Head, LR);
				}
			}
		}
	}
}

