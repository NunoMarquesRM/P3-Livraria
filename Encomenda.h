typedef struct Encomenda {
	int id;
	int ClienteNIF;
	int LivroISBN;
	char DataEncomenda[10];
	int UnidadesEncomendadas;
	float PrecoTotal;
}ENCOMENDA;

struct NodoFila {
	ENCOMENDA Elemento;
	struct NodoFila *Prox;
};

typedef struct NodoFila *PNodoFila;

PNodoFila CriarNodoFila(ENCOMENDA X){
	PNodoFila P;
	P = (PNodoFila) malloc(sizeof(struct NodoFila));
	if (P == NULL){
		return NULL;
	}
	P->Elemento = X;
	P->Prox = NULL;
	return P;
}

int FilaVazia(PNodoFila Fila){
	if (Fila == NULL)
		return 1;
	else
		return 0;
}

PNodoFila Juntar(ENCOMENDA X, PNodoFila Fila){
	PNodoFila Novo, PAnt;
	Novo = CriarNodoFila(X);
	if (Novo == NULL){
		return Fila;
	}
	if (FilaVazia(Fila)){
		Fila = Novo;
		return Fila;
	}
	PAnt = Fila;
	while(PAnt->Prox != NULL){
		PAnt = PAnt->Prox;
	}
	PAnt->Prox = Novo;
	return Fila;
}

void ListarEncomenda(ENCOMENDA X){
	printf("\n__Encomenda__\n");
	printf("Id:                    %d\n",X.id);
	printf("NIF do Cliente:        %d\n",X.ClienteNIF);
	printf("ISBN do Livro:         %d\n",X.LivroISBN);
	printf("Data da Encomenda:     %s\n",X.DataEncomenda);
	printf("Unidades Encomendadas: %d\n",X.UnidadesEncomendadas);
	printf("Preço Total:           %.2f\n",X.PrecoTotal);
}

void MostrarFila(PNodoFila Q){
	while (Q != NULL){
		ListarEncomenda(Q->Elemento);
		Q = Q->Prox;
	}
}

PNodoFila LibertarNodoFila(PNodoFila P){ 
	free(P);
	P = NULL;
	return P;
}

PNodoFila Remover(PNodoFila Fila){
	PNodoFila P;
	P = Fila;
	Fila = Fila->Prox;
	P = LibertarNodoFila(P);
	return Fila;
}

PNodoFila RemoverEncomenda(PNodoFila Fila, int id){
	PNodoFila Q = Fila;
	PNodoFila Aux = NULL;

	while (Q != NULL){
		if(Q->Elemento.id != id){
			Aux = Juntar(Q->Elemento, Aux);
		}
		Q = Q->Prox;
	}
	return Aux;
}
// Dá return do id da última encomenda
int UltimoIDEncomenda(PNodoFila Q){
	while (Q != NULL){
		if(Q->Prox == NULL){
			return Q->Elemento.id;
		}
		Q = Q->Prox;
	}
	return 0;
}
// Verifica se a lista de compras contem um id da encomenda apresentado
// 1 se encontra, 0 senão existir
int TemEncomenda(PNodoFila Q, int id){
	while (Q != NULL){
		if(Q->Elemento.id == id){
			return 1;
		}
		Q = Q->Prox;
	}
	return 0;
}
// Numero Total Livros Vendidos
int LivrosVendidos(PNodoFila Q){
	int c = 0;
	while (Q != NULL){
		c = c + Q->Elemento.UnidadesEncomendadas;
		Q = Q->Prox;
	}
	return c;
}
