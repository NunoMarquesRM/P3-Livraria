typedef struct Encomenda {
	int ClienteNIF;
	int LivroISBN;
	char DataEncomenda[20];
	int UnidadesEncomendadas;
	float PrecoTotal;
}ENCOMENDA;

struct NodoFila {
	ENCOMENDA Elemento;
	struct NodoFila *Prox;
};

typedef struct NodoFila *PNodoFila;

PNodoFila CriarNodoFila (ENCOMENDA X){
	PNodoFila P;
	P = (PNodoFila) malloc(sizeof(struct NodoFila));
	if (P == NULL){
		return NULL;
	}
	P->Elemento = X;
	P->Prox = NULL;
	return P;
}

int FilaVazia (PNodoFila Fila){
	if (Fila == NULL)
		return 1;
	else
		return 0;
}

PNodoFila Juntar (ENCOMENDA X, PNodoFila Fila){
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
	printf("NIF do Cliente:        %d\n",X.ClienteNIF);
	printf("ISBN do Livro:         %d\n",X.LivroISBN);
	printf("Data da Encomenda:     %s\n",X.DataEncomenda);
	printf("Unidades Encomendadas: %d\n",X.UnidadesEncomendadas);
	printf("Preço Total:           %.2f\n",X.PrecoTotal);
}

void MostrarFila (PNodoFila Q){
	while (Q != NULL){
		ListarEncomenda(Q->Elemento);
		Q = Q->Prox;
	}
}