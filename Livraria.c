#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#include "Livros.h"
#include "Cliente.h"


PNodo Head, Tail;
PNodoAB TCliente;
PNodoFila FEncomendas;

void menuFicheiro(){
	int n;
	FILE *fpE, *fpL, *fpC;
	PNodoFila FE;
	PNodo LIVROS;
	char infos[500];
	char *in;
	while(true){
		printf("\n ____________________________________\n");
		printf("|          Menu de Ficheiros         |\n");
		printf("|                                    |\n");
		printf("|	1. Novo Ficheiro             |\n");
		printf("|	2. Guardar Ficheiro          |\n");
		printf("|	3. Abrir Ficheiro            |\n");
		printf("|	0. Sair                      |\n");
		printf("|____________________________________|\n");
		printf("Opção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			case 1:
				fpE = fopen("encomenda.txt","w");
				fpL = fopen("livros.txt","w");
				fpC = fopen("cliente.txt","w");
				fclose(fpE);
				fclose(fpL);
				fclose(fpC);
				printf("\nFicheiros criados com Sucesso!\n");
				break;
			case 2:
				fpE = fopen("encomenda.txt","w");
				fpL = fopen("livros.txt","w");
				fpC = fopen("cliente.txt","w");
				// Ficheiro das encomendas.txt
				FE = FEncomendas;
				while(FE != NULL){
					fprintf(fpE,"%d,%d,%d,%s,%d,%.2f\n",FE->Elemento.id,FE->Elemento.ClienteNIF,FE->Elemento.LivroISBN,FE->Elemento.DataEncomenda,FE->Elemento.UnidadesEncomendadas,FE->Elemento.PrecoTotal);
					FE = FE->Prox;
				}
				fclose(fpE);
				// Ficheiro dos livros.txt
				LIVROS = Head;
				while(LIVROS != NULL){
					fprintf(fpL,"%d,%s,%s,%s,%s,%s,%d,%s,%.2f,%d\n",LIVROS->Elemento.ISBN,LIVROS->Elemento.Titulo,LIVROS->Elemento.Idioma,LIVROS->Elemento.PrimeiroAutor,LIVROS->Elemento.SegundoAutor,LIVROS->Elemento.Editora,LIVROS->Elemento.Ano,LIVROS->Elemento.AreaCientifica,LIVROS->Elemento.Preco,LIVROS->Elemento.Quantidade);
					LIVROS = LIVROS->Prox;
				}
				fclose(fpL);
				// Ficheiro dos cLientes.txt
				SaveFile(TCliente, fpC);
				fclose(fpC);
				printf("\nFicheiros guardados com Sucesso!\n");
				break;
			case 3:
				// Ficheiro Encomendas
				fpE = fopen("encomenda.txt","r");
				int ch = 0;
				int lines = 1;
				while ((ch = fgetc(fpE)) != EOF){
					if (ch == '\n')
						lines++;
				}
				fclose(fpE);

				fpE = fopen("encomenda.txt","r");
				char s[2] = ",";
				ENCOMENDA ENC;
				int num;
				while(lines != 0){
					num = 1;
					fscanf(fpE," %s",infos);
					//printf("%s\n",infos);
					in = strtok(infos, s);
					while( in != NULL ) {
						if(num == 1){
							ENC.id = atoi(in);
							num++;
						}
						else if(num == 2){
							ENC.ClienteNIF = atoi(in);
							num++;
						}
						else if(num == 3){
							ENC.LivroISBN = atoi(in);
							num++;
						}
						else if(num == 4){
							strcpy(ENC.DataEncomenda,in);
							num++;
						}
						else if(num == 5){
							ENC.UnidadesEncomendadas = atoi(in);
							num++;
						}
						else if(num == 6){
							ENC.PrecoTotal = atof(in);
							FEncomendas = Juntar(ENC, FEncomendas);
						}
						in = strtok(NULL, s);
					}
					lines--;
				}
				fclose(fpE);

				// Ler ficheiro Livros
				fpL = fopen("livros.txt","r");
				ch = 0;
				lines = 1;
				while ((ch = fgetc(fpE)) != EOF){
					if (ch == '\n')
						lines++;
				}
				fclose(fpL);
				
				fpL = fopen("livros.txt","r");
				
				LIVRO LIV;
				while(lines != 0){
					num = 1;
					//fscanf(fpE," %s",infos);
					printf("%s\n",infos);
					in = strtok(infos, s);
					while( in != NULL ) {
						if(num == 1){
							LIV.ISBN = atoi(in);
							num++;
						}
						else if(num == 2){
							strcpy(LIV.Titulo,in);
							num++;
						}
						else if(num == 3){
							strcpy(LIV.Idioma,in);
							num++;
						}
						else if(num == 4){
							strcpy(LIV.PrimeiroAutor,in);
							num++;
						}
						else if(num == 5){
							strcpy(LIV.SegundoAutor,in);
							num++;
						}
						else if(num == 6){
							strcpy(LIV.Editora,in);
							num++;
						}
						else if(num == 7){
							LIV.Ano = atoi(in);
							num++;
						}
						else if(num == 8){
							strcpy(LIV.AreaCientifica,in);
							num++;
						}
						else if(num == 9){
							LIV.Preco = atof(in);
							num++;
						}
						else if(num == 10){
							LIV.Quantidade = atoi(in);
							if(Head == NULL){
								InserirPrimeiroElemento(&Head, &Tail, LIV);
							}
							else{
								Head = InserirCabeca(Head, LIV);
							}
						}
						in = strtok(NULL, s);
					}
					lines--;
				}
				fclose(fpL);

				//fpC = fopen("cliente.txt","r");
				
				//fclose(fpC);
				printf("\nOperação realizada com Sucesso!\n");
				break;
			case 0:
				break;
			default:
				printf("\nIntroduza um numero valido!\n");
				break;
		}
		if(n == 0){
			break;
		}
	}
}

void menuLivros(){
	int n, opcao, isbn, consultarTMP;
	char consultarTMPChar[100];

	while(true){
		printf("\n __________________________________\n");
		printf("|          Menu de Livros          |\n");
		printf("|                                  |\n");
		printf("|	1. Inserir Livro           |\n");
		printf("|	2. Remover Livro           |\n");
		printf("|	3. Alterar Livro           |\n");
		printf("|	4. Consultar Livro         |\n");
		printf("|	0. Sair                    |\n");
		printf("|__________________________________|\n");
		printf("Opção: ");
		scanf("%d",&n);
		// Menu Principal
		switch (n){
			
			LIVRO X;
			// Tem de ser com Listas Ligadas
			case 1:
				printf("Introduza o ISBN do livro: \n");
				scanf("%d",&X.ISBN);
				printf("Introduza o Titulo do livro: \n");
				scanf(" %[^\n]%*c", X.Titulo);
				printf("Introduza o Idioma do livro: \n");
				scanf(" %[^\n]%*c",X.Idioma);
				printf("Introduza o Primeiro Autor do livro: \n");
				scanf(" %[^\n]%*c",X.PrimeiroAutor);
				printf("Introduza o Segundo Autor do livro: \n");
				scanf(" %[^\n]%*c",X.SegundoAutor);
				printf("Introduza a Editora do livro: \n");
				scanf(" %[^\n]%*c",X.Editora);
				printf("Introduza o Ano de lançamento do livro: \n");
				scanf("%d",&X.Ano);
				printf("Introduza a Área Cientifica do livro: \n");
				scanf(" %[^\n]%*c",X.AreaCientifica);
				printf("Introduza o Preço do livro: \n");
				scanf("%f",&X.Preco);
				printf("Introduza a Quantidade deste livro em stock: \n");
				scanf("%d",&X.Quantidade);

				if(Head == NULL){
					InserirPrimeiroElemento(&Head, &Tail, X);
				}
				else{
					Head = InserirCabeca(Head, X);
				}
				break;
			case 2:
				printf("Introduza o ISBN do Livro a remover:");
				scanf("%d", &isbn);
				RemoverLivro(&Head,&Tail, isbn);
				break;
			case 3:
				printf("Introduza o ISBN do Livro a alterar:");
				scanf("%d", &isbn);

				LIVRO LR;
				LR.ISBN = isbn;
				PNodo P = Head;

				if (ConsultarCabeca(Head, LR) == 1){
					while(P != NULL){
						if (CompararElementosISBN(P->Elemento, LR) == 0){
							printf("Introduza o Titulo do livro: \n");
							scanf(" %[^\n]%*c",LR.Titulo);
							printf("Introduza o Idioma do livro: \n");
							scanf(" %[^\n]%*c",LR.Idioma);
							printf("Introduza o Primeiro Autor do livro: \n");
							scanf(" %[^\n]%*c",LR.PrimeiroAutor);
							printf("Introduza o Segundo Autor do livro: \n");
							scanf(" %[^\n]%*c",LR.SegundoAutor);
							printf("Introduza a Editora do livro: \n");
							scanf(" %[^\n]%*c",LR.Editora);
							printf("Introduza o Ano de lançamento do livro: \n");
							scanf("%d",&LR.Ano);
							printf("Introduza a Área Cientifica do livro: \n");
							scanf(" %[^\n]%*c",LR.AreaCientifica);
							printf("Introduza o Preço do livro: \n");
							scanf("%f",&LR.Preco);
							printf("Introduza a Quantidade deste livro em stock: \n");
							scanf("%d",&LR.Quantidade);
							
							// Remove o livro da lista original
							RemoverLivro(&Head,&Tail, isbn);
							// Adiciona o livro editado à lista original
							if(Tamanho(Head) == 0){
								// Se a lista estiver vazia
								InserirPrimeiroElemento(&Head, &Tail, LR);
							}
							else{
								// Se houver mais que um elemento na lista
								Head = InserirCabeca(Head, LR);
							}
						}
						P = P->Prox;
					}
				}
				break;
			case 4:
				printf("\n __________________________________\n");
				printf("|    Menu de Consulta de Livros    |\n");
				printf("|                                  |\n");
				printf("|	 1. ISBN                   |\n");
				printf("|	 2. Título                 |\n");
				printf("|	 3. Idioma                 |\n");
				printf("|	 4. Primeiro Autor         |\n");
				printf("|	 5. Segundo Autor          |\n");
				printf("|	 6. Editora                |\n");
				printf("|	 7. Ano de Publicação      |\n");
				printf("|	 8. Área Científica        |\n");
				printf("|	 9. Igual Preço (€)        |\n");
				printf("|	10. Inferior Preço (€)     |\n");
				printf("|	11. Superior Preço (€)     |\n");
				printf("|	12. Mostrar todos          |\n");
				printf("|__________________________________|\n");
				printf("Opção: ");
				scanf("%d",&opcao);
				// Menu secundário da Opção 4 do menu principal
				switch(opcao){
					case 1:
						printf("ISBN do Livro a consultar: ");
						scanf("%d", &consultarTMP);
						ListarISBN(Head, consultarTMP);
						break;
					case 2:
						printf("Título do Livro a consultar: ");
						scanf(" %[^\n]%*c", consultarTMPChar);
						ListarTitulo(Head, consultarTMPChar);
						break;
					case 3:
						printf("Título do Idioma a consultar: ");
						scanf(" %[^\n]%*c", consultarTMPChar);
						ListarIdioma(Head, consultarTMPChar);
						break;
					case 4:
						printf("Primeiro Autor a consultar: ");
						scanf(" %[^\n]%*c", consultarTMPChar);
						ListarPAutor(Head, consultarTMPChar);
						break;
					case 5:
						printf("Segundo Autor a consultar: ");
						scanf(" %[^\n]%*c", consultarTMPChar);
						ListarSAutor(Head, consultarTMPChar);
						break;
					case 6:
						printf("Editora a consultar: ");
						scanf("%s", consultarTMPChar);
						ListarEditora(Head, consultarTMPChar);
						break;
					case 7:
						printf("Ano de Publicação do Livro a consultar: ");
						scanf("%d", &consultarTMP);
						ListarAno(Head, consultarTMP);
						break;
					case 8:
						printf("Área Científica a consultar: ");
						scanf("%s", consultarTMPChar);
						ListarAreaCientifica(Head, consultarTMPChar);
						break;
					case 9:
						printf("Igual Preço (€) do Livro a consultar: ");
						scanf("%d", &consultarTMP);
						ListarPreco(Head, consultarTMP, 0);
						break;
					// Trabalho Extra
					case 10:
						printf("Inferior Preço (€) do Livro a consultar: ");
						scanf("%d", &consultarTMP);
						ListarPreco(Head, consultarTMP, -1);
						break;
					// Trabalho Extra
					case 11:
						printf("Superior Preço (€) do Livro a consultar: ");
						scanf("%d", &consultarTMP);
						ListarPreco(Head, consultarTMP, 1);
						break;
					// Trabalho Extra
					case 12:
						Listar(Head);
						break;
					default:
						printf("\nIntroduza um número válido!\n");
						break;
				}
				break;
			case 0:
				break;
			default:
				printf("\nIntroduza um número válido!\n");
				break;
		}
		if(n == 0){
			break;
		}
	}
}

void menuClientes(){
	int n, opcao;
	CLIENTE CL, CCL, CLAUX;
	
	while(true){
		printf("\n ____________________________________\n");
		printf("|          Menu de Clientes          |\n");
		printf("|                                    |\n");
		printf("|	1. Inserir Cliente           |\n");
		printf("|	2. Remover Cliente           |\n");
		printf("|	3. Alterar Cliente           |\n");
		printf("|	4. Consultar Cliente         |\n");
		printf("|	0. Sair                      |\n");
		printf("|____________________________________|\n");
		
		printf("Opção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			// Arvore Binaria de Pesquisa Balanceada!
			case 1:
				printf("Introduza o NIF: \n");
				scanf("%d",&CL.NIF);
				printf("Introduza o Nome: \n");
				scanf(" %[^\n]%*c", CL.Nome);
				printf("Introduza a Morada: \n");
				scanf(" %[^\n]%*c", CL.Morada);
				printf("Introduza o Telefone: \n");
				scanf("%d",&CL.Telefone);
				CL.ListaCompras = NULL;

				if(PesquisarABP(TCliente, CL) == 0){
					TCliente = InserirABP(TCliente, CL);
					TCliente = CriarABPEquilibradaIB(TCliente);
				}
				break;
			case 2:
				printf("Introduza o NIF do Cliente a remover: ");
				scanf("%d",&CL.NIF);
				if(PesquisarABP(TCliente, CL) == 1){
					TCliente = RemoverABP(TCliente, CL);
					TCliente = CriarABPEquilibradaIB(TCliente);
				}
				else{
					printf("O Cliente não existe!");
				}
				break;
			case 3:
				printf("Introduza o NIF do Cliente a modificar: ");
				scanf("%d",&CL.NIF);
				if(PesquisarABP(TCliente, CL) == 1){
					CLAUX = PesquisarClienteAlterar(TCliente, CL);
					TCliente = RemoverABP(TCliente, CL);
					TCliente = CriarABPEquilibradaIB(TCliente);
					printf("\nIntroduza o Nome: \n");
					scanf(" %[^\n]%*c", CL.Nome);
					printf("Introduza a Morada: \n");
					scanf(" %[^\n]%*c", CL.Morada);
					printf("Introduza o Telefone: \n");
					scanf("%d",&CL.Telefone);
					CL.ListaCompras = CLAUX.ListaCompras;

					TCliente = InserirABP(TCliente, CL);
					TCliente = CriarABPEquilibradaIB(TCliente);
				}
				else{
					printf("O Cliente não existe!");
				}
				break;
			case 4:
				printf("\n __________________________________\n");
				printf("|   Menu de Consulta de Clientes   |\n");
				printf("|                                  |\n");
				printf("|	 1. NIF                    |\n");
				printf("|	 2. Nome                   |\n");
				printf("|	 3. Morada                 |\n");
				printf("|	 4. Telefone               |\n");
				printf("|	 5. Mostrar Todos          |\n");
				printf("|__________________________________|\n");
				printf("Opção: ");
				scanf("%d",&opcao);
				// Menu secundário da Opção 4 do menu principal
				switch(opcao){
					case 1:
						printf("NIF do cliente a consultar: ");
						scanf("%d", &CCL.NIF);
						ListarNIF(TCliente, CCL);
						break;
					case 2:
						printf("Nome do cliente a consultar: ");
						scanf(" %[^\n]%*c", CCL.Nome);
						ListarNome(TCliente, CCL);
						break;
					case 3:
						printf("Morada do cliente a consultar: ");
						scanf(" %[^\n]%*c", CCL.Morada);
						ListarMorada(TCliente, CCL);
						break;
					case 4:
						printf("Telefone do cliente a consultar: ");
						scanf("%d", &CCL.Telefone);
						ListarTelefone(TCliente, CCL);
						break;
					// Trabalho Extra
					case 5:
						printf("\n");
						ListarEmOrdemAB(TCliente);
						break;
					default:
						printf("\nIntroduza um número válido!\n");
						break;
				}
				break;
			case 0:
				break;
			default:
				printf("\nIntroduza um número válido!\n");
				break;
		}
		if(n == 0){
			break;
		}
	}
}

void menuEncomendas(){
	int n, nif, isbn, quantidade, id;
	float precoTotalAux;
	ENCOMENDA ENC, ENCAUX;
	CLIENTE C, CAUX;
	LIVRO L;
	
	while(true){
		printf("\n ______________________________________\n");
		printf("|          Menu de Encomendas          |\n");
		printf("|                                      |\n");
		printf("|	1. Inserir Encomenda           |\n");
		printf("|	2. Remover Encomenda           |\n");
		printf("|	3. Consultar Encomendas        |\n");
		printf("|	0. Sair                        |\n");
		printf("|______________________________________|\n");
		printf("Opção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			case 1:
				printf("Introduza o NIF do Cliente: \n");
				scanf("%d",&nif);
				C.NIF = nif;

				if(PesquisarABP(TCliente, C) == 1){
					CAUX = PesquisarClienteAlterar(TCliente, C);
					ENC.ClienteNIF = nif;
					printf("Introduza o ISBN do Livro: \n");
					scanf("%d",&isbn);
					L.ISBN = isbn;

					if(TemLivro(Head,L) == 1){
						ENC.LivroISBN = isbn;
						printf("Introduza o número de unidades a encomendar: \n");
						scanf("%d",&quantidade);
						L = ProcurarLivro(Head, L);
						if(L.Quantidade-quantidade >= 0){
							if(FilaVazia(FEncomendas) == 1){
								ENC.id = 1;
							}
							else{
								ENC.id = UltimoIDEncomenda(FEncomendas) + 1;
							}
							// Alteração da quantidade de livros
							L.Quantidade = L.Quantidade-quantidade;
							ENC.UnidadesEncomendadas = quantidade;
							// Remove o livro da lista original
							RemoverLivro(&Head,&Tail, L.ISBN);
							// Adiciona o livro editado à lista original
							if(Tamanho(Head) == 0){
								// Se a lista estiver vazia
								InserirPrimeiroElemento(&Head, &Tail, L);
							}
							else{
								// Se houver mais que um elemento na lista
								Head = InserirCabeca(Head, L);
							}
							// Cálculo do Preço total da compra
							precoTotalAux = L.Preco * quantidade;
							ENC.PrecoTotal = precoTotalAux;
							// Datas da Encomenda
							printf("Introduza a Data da Encomenda (Formato: '10-03-2021'): \n");
							scanf(" %[^\n]%*c", ENC.DataEncomenda);
							
							FEncomendas = Juntar(ENC, FEncomendas);
							
							// Remove e equilibra
							TCliente = RemoverABP(TCliente, C);
							TCliente = CriarABPEquilibradaIB(TCliente);
							// Adiciona a nova encomenda
							CAUX.ListaCompras = Juntar(ENC,CAUX.ListaCompras);
							// Adiciona o Cliente com a nova encomenda
							TCliente = InserirABP(TCliente, CAUX);
							TCliente = CriarABPEquilibradaIB(TCliente);
						}
						else{
							printf("Não é possível encomendar este número de unidades!\n");
						}
					}
					else{
						printf("Livro não existe!\n");
					}
				}
				else{
					printf("Cliente não existe!\n");
				}
				break;
			case 2:
				printf("Introduza o NIF do Cliente: \n");
				scanf("%d",&nif);
				C.NIF = nif;

				if(PesquisarABP(TCliente, C) == 1){
					CAUX = PesquisarClienteAlterar(TCliente, C);
					printf("\n--Lista de Encomendas do Cliente--\n");
					MostrarFila(CAUX.ListaCompras);
					ENC.ClienteNIF = nif;
					printf("\nIntroduza o id da Encomenda: \n");
					scanf("%d",&id);

					if(TemEncomenda(CAUX.ListaCompras, id) == 1){
						CAUX.ListaCompras = RemoverEncomenda(CAUX.ListaCompras, id);
						FEncomendas = RemoverEncomenda(FEncomendas, id);
						// Remove e equilibra
						TCliente = RemoverABP(TCliente, C);
						TCliente = CriarABPEquilibradaIB(TCliente);
						// Adiciona o Cliente com a lista de encomendas atualizada
						TCliente = InserirABP(TCliente, CAUX);
						TCliente = CriarABPEquilibradaIB(TCliente);
					}
					else{
						printf("O id da encomenda não existe!\n");
					}
				}
				else{
					printf("Cliente não existe!\n");
				}
				break;
			// Trabalho Extra
			case 3:
				MostrarFila(FEncomendas);
				break;
			case 0:
				break;
			default:
				printf("\nIntroduza um número válido!\n");
				break;
		}
		if(n == 0){
			break;
		}
	}
}

void menuOperacoes(){
	int n, i;
	int numVendidos;
	CLIENTE C;
	// Variáveis case 9
	int anos[25][2] = {0};
	PNodo livr = Head;
	int verificar = 0;

	while(true){
		//Obrigatorio Acrescentar no Minimo mais 4 Operacoes enquadradas com o Problema
		printf("\n _______________________________________________________________________________\n");
		printf("|                               Menu de Operações				|\n");
		printf("|                                    						|\n");
		printf("|	1.  Consultar o número de livros vendidos				|\n");
		printf("|	2.  Consultar a data da última compra de um livro    		        |\n");
		printf("|	3.  Consultar o número de livros comprados por um dado cliente          |\n");
		printf("|	4.  Consultar os K livros mais recentes de uma dada Área Científica     |\n");
		printf("|	5.  Consultar os K livros mais vendidos num dado período    	        |\n");
		printf("|	6.  Consultar a Área Científica com mais livros     		        |\n");
		printf("|	7.  Consultar o cliente com mais livros comprados     		        |\n");
		printf("|	8.  Consultar os clientes por ordem decrescente do número de compras	|\n");
		printf("|	9.  Consultar o Ano com mais publicações    			        |\n");
		printf("|	10. Consultar o cliente que gastou mais dinheiro num dado período       |\n");
		printf("|	11. Consultar o desperdício de memória    			        |\n");
		printf("|	0.  Sair                    				        	|\n");
		printf("|_______________________________________________________________________________|\n");
		printf("Opção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			case 1:
				numVendidos = LivrosVendidos(FEncomendas);
				printf("\nLivros Vendidos: %d\n",numVendidos);
				break;
			case 2:
				//UltimaCompra();
				break;
			case 3:
				ListarNIFNOME(TCliente);
				printf("\nNIF do Cliente:\n");
				scanf("%d",&C.NIF);
				if(PesquisarABP(TCliente, C) == 1){
					ListarListaCompras(TCliente, C);
				}
				else{
					printf("Cliente não existe!\n");
				}
				//LivrosComprados();
				break;
			case 4:
				//LivrosMaisRecentes();
				break;
			case 5:
				//LivrosMaisVendidos();
				break;
			case 6:
				//AreaCMaisLivros();
				break;
			case 7:
				printf("\nCliente com Livros mais comprados:\n");
				//ClienteLivrosMaisVendidos(TCliente);
				break;
			case 8:
				//ClientesDecCompras();
				break;
			case 9:
				// Percorre a lista dos livros e guarda os anos numa matriz auxiliar (anos)
				// 
				while(livr != NULL){
					verificar = 0;
					for (i = 0; i < 25; i++){
						if(anos[i][0] == livr->Elemento.Ano){
							verificar = 1;
							anos[i][1] = anos[i][1] + 1;
						}
					}
					if(verificar == 0){
						for (i = 0; i < 25; i++){
							if(anos[i][0] == 0){
								anos[i][0] = livr->Elemento.Ano;
								anos[i][1] = anos[i][1] + 1;
							}
						}
					}
					livr = livr->Prox;
				}
				int anoF = 0, anoAux = 0, aux1 = 0, aux = 0;
				
				for (i = 0; i < 25; i++){
					if(anos[i][0] != 0){
						anoAux = anos[i][0];
						aux = anos[i][1];
						if(aux > aux1){
							anoF = anoAux;
							aux1 = aux;
						}
					}
				}

				printf("\nO ano com mais publicações é: %d", anoF);
				//AnoMaisPub();
				break;
			case 10:
				//ClienteMaisGastou();
				break;
			case 11:
				//DesperdicioMemoria();
				break;
			case 0:
				break;
			default:
				printf("\nIntroduza um número válido!\n");
				break;
		}
		if(n == 0){
			break;
		}
	}
}

void main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int n;
	Head = NULL, Tail = NULL;
	TCliente = NULL;
	FEncomendas = NULL;

	while(true){
		
		printf("\n ____________________________________\n");
		printf("|           Menu Principal           |\n");
		printf("|                                    |\n");
		printf("|	1. Menu de Ficheiros         |\n");
		printf("|	2. Menu de Livros            |\n");
		printf("|	3. Menu de Clientes          |\n");
		printf("|	4. Menu de Encomendas        |\n");
		printf("|	5. Menu de Operações         |\n");
		printf("|	0. Sair                      |\n");
		printf("|____________________________________|\n");
		printf("\nOpção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			case 1:
				menuFicheiro();
				break;
			case 2:
				menuLivros();
				break;
			case 3:
				menuClientes();
				break;
			case 4:
				menuEncomendas();
				break;
			case 5:
				menuOperacoes();
				break;
			case 0:
				break;
			default:
				printf("\nIntroduza um número válido!\n");
				break;
		}
		if(n == 0){
			break;
		}
	}
}
