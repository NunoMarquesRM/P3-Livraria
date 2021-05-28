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
	printf("ISBN:                %d\n",X.ISBN);
	printf("Titulo:              %s\n",X.Titulo);
	printf("Idioma:              %s\n",X.Idioma);
	printf("Primeiro Autor:      %s\n",X.PrimeiroAutor);
	printf("Segundo Autor:       %s\n",X.SegundoAutor);
	printf("Editora:             %s\n",X.Editora);
	printf("Ano:                 %d\n",X.Ano);
	printf("Área Científica:     %s\n",X.AreaCientifica);
	printf("Preço:               %.2f\n",X.Preco);
	printf("Quantidade em stock: %d\n",X.Quantidade);
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

int CompararElementosISBN (LIVRO X, LIVRO Y){
	if (X.ISBN > Y.ISBN)
		return 1;
	if (X.ISBN < Y.ISBN)
		return -1;
	return 0;
}

PNodo Procurar (PNodo Head, LIVRO X){
	PNodo P = Head;
	while (CompararElementosISBN(P->Elemento, X) != 0)
		P = P->Prox; 
	return P;
}

// Procurar por Livro
// Se encontrar return 1
// Senão encontrar return 0
int TemLivro(PNodo Head, LIVRO L){
	PNodo P = Head;
	int c = 0;
	while (P != NULL){
		if(CompararElementosISBN(P->Elemento, L) == 0){
			c = 1;
		}
		P = P->Prox;
	}
	return c;
}
// Procurar por Livro
// Encontra sempre, porque a função anterior já foi utilizada no main
// Retorna o Livro
LIVRO ProcurarLivro(PNodo Head, LIVRO L){
	PNodo P = Head;
	while (P != NULL){
		if(CompararElementosISBN(P->Elemento, L) == 0){
			return P->Elemento;
		}
		P = P->Prox;
	}
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
	while (CompararElementosISBN(P->Elemento, X) != 0 && P->Prox != NULL)
		P = P->Prox; 
	if (CompararElementosISBN(P->Elemento, X) == 0)
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
			if(CompararElementosISBN((*Head)->Elemento,LR) == 0){
				*Head = RemoverCabeca(*Head);
			}
			else{
				if(CompararElementosISBN((*Tail)->Elemento,LR) == 0){
					*Tail = RemoverCauda(*Tail);
				}
				else{
					*Head = RemoverMeio(*Head, LR);
				}
			}
		}
	}
}
// Consultar ISBN
void ListarISBN (PNodo Head, int isbn){
	PNodo P = Head;
	LIVRO X;
	X.ISBN = isbn;
	while(P != NULL){
		if(CompararElementosISBN(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
		}
		P = P->Prox;
	}
}
// Consultar Ano
int CompararElementosAno (LIVRO X, LIVRO Y){
	if (X.Ano > Y.Ano)
		return 1;
	if (X.Ano < Y.Ano)
		return -1;
	return 0;
}

void ListarAno (PNodo Head, int ano){
	PNodo P = Head;
	LIVRO X;
	X.Ano = ano;
	while(P != NULL){
		if(CompararElementosAno(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
		}
		P = P->Prox;
	}
}
// Consultar Preco
int CompararElementosPreco (LIVRO X, LIVRO Y){
	if (X.Preco > Y.Preco)
		return 1;
	if (X.Preco < Y.Preco)
		return -1;
	return 0;
}

void ListarPreco (PNodo Head, int preco, int flag){
	PNodo P = Head;
	LIVRO X;
	X.Preco = preco;
	while(P != NULL){
		if(CompararElementosPreco(P->Elemento, X) == 0 && flag == 0){
			ConsultarLivro(P->Elemento);
		}
		if(CompararElementosPreco(P->Elemento, X) == -1 && flag == -1){
			ConsultarLivro(P->Elemento);
		}
		if(CompararElementosPreco(P->Elemento, X) == 1 && flag == 1){
			ConsultarLivro(P->Elemento);
		}
		P = P->Prox;
	}
}
// Consultar Titulo
int CompararElementosTitulo (LIVRO X, LIVRO Y){
	if (strstr(X.Titulo, Y.Titulo) == NULL){
		return 1;
	}
	return 0;
}

void ListarTitulo (PNodo Head, char *tmp){
	PNodo P = Head;
	LIVRO X;
	
	strcpy(X.Titulo,tmp);
	int c = 0;
	while(P != NULL){
		if(CompararElementosTitulo(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
			c++;
		}
		P = P->Prox;
	}
	if(c == 0){
		printf("Não existe!");
	}
}
// Consultar Idioma
int CompararElementosIdioma (LIVRO X, LIVRO Y){
	if (strstr(X.Idioma, Y.Idioma) == NULL){
		return 1;
	}
	return 0;
}

void ListarIdioma (PNodo Head, char *tmp){
	PNodo P = Head;
	LIVRO X;
	
	strcpy(X.Idioma,tmp);
	int c = 0;
	while(P != NULL){
		if(CompararElementosIdioma(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
			c++;
		}
		P = P->Prox;
	}
	if(c == 0){
		printf("Não existe!");
	}
}
// Consultar Primeiro Autor
int CompararElementosPAutor (LIVRO X, LIVRO Y){
	if (strstr(X.PrimeiroAutor, Y.PrimeiroAutor) == NULL){
		return 1;
	}
	return 0;
}

void ListarPAutor (PNodo Head, char *tmp){
	PNodo P = Head;
	LIVRO X;
	
	strcpy(X.PrimeiroAutor,tmp);
	int c = 0;
	while(P != NULL){
		if(CompararElementosPAutor(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
			c++;
		}
		P = P->Prox;
	}
	if(c == 0){
		printf("Não existe!");
	}
}
// Consultar Segundo Autor
int CompararElementosSAutor (LIVRO X, LIVRO Y){
	if (strstr(X.SegundoAutor, Y.SegundoAutor) == NULL){
		return 1;
	}
	return 0;
}

void ListarSAutor (PNodo Head, char *tmp){
	PNodo P = Head;
	LIVRO X;
	
	strcpy(X.SegundoAutor,tmp);
	int c = 0;
	while(P != NULL){
		if(CompararElementosSAutor(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
			c++;
		}
		P = P->Prox;
	}
	if(c == 0){
		printf("Não existe!");
	}
}
// Consultar Editora
int CompararElementosEditora (LIVRO X, LIVRO Y){
	if (strstr(X.Editora, Y.Editora) == NULL){
		return 1;
	}
	return 0;
}

void ListarEditora (PNodo Head, char *tmp){
	PNodo P = Head;
	LIVRO X;
	
	strcpy(X.Editora,tmp);
	int c = 0;
	while(P != NULL){
		if(CompararElementosEditora(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
			c++;
		}
		P = P->Prox;
	}
	if(c == 0){
		printf("Não existe!");
	}
}
// Consultar Area Cientifica
int CompararElementosAreaCientifica (LIVRO X, LIVRO Y){
	if (strstr(X.AreaCientifica, Y.AreaCientifica) == NULL){
		return 1;
	}
	return 0;
}

void ListarAreaCientifica (PNodo Head, char *tmp){
	PNodo P = Head;
	LIVRO X;
	
	strcpy(X.AreaCientifica,tmp);
	int c = 0;
	while(P != NULL){
		if(CompararElementosAreaCientifica(P->Elemento, X) == 0){
			ConsultarLivro(P->Elemento);
			c++;
		}
		P = P->Prox;
	}
	if(c == 0){
		printf("Não existe!");
	}
}
