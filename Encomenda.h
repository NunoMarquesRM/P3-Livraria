typedef struct Encomenda {
	struct Livro.ISBN;
	struct Cliente.NIF;
	char[10] DataEncomenda;
	char[10] DataCompra;
	char[10] DataVenda;	
	int UnidadesEncomendadas;
	float PrecoTotal;
}ENCOMENDA;
