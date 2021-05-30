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

PNodoFila ficheirosAtualizaListaComprasCliente(char *in, CLIENTE CLI){
	char s[2] = ",";
	ENCOMENDA ENC;
	int num = 1;
	while( num != 7 ) {
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
			CLI.ListaCompras = Juntar(ENC, CLI.ListaCompras);
			num++;
		}
		if(num != 7){
			in = strtok(NULL, s);
		}
	}
	return CLI.ListaCompras;
}

void menuFicheiro(){
	int n;
	FILE *fpE, *fpL, *fpC;
	PNodoFila FE;
	PNodo LIVROS;
	char infos[500];
	char *in, *inAux;
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
				// Ficheiro dos clientes.txt
				SaveFile(TCliente, fpC);
				fclose(fpC);
				printf("\nFicheiros guardados com Sucesso!\n");
				break;
			case 3:
				// Ficheiro encomendas.txt
				fpE = fopen("encomenda.txt","r");
				int ch = 0;
				int lines = 0;
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
					fscanf(fpE," %[^\n]%*c",infos);
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
				lines = 0;
				while ((ch = fgetc(fpE)) != EOF){
					if (ch == '\n')
						lines++;
				}
				fclose(fpL);
				
				fpL = fopen("livros.txt","r");
				LIVRO LIV;
				while(lines != 0){
					num = 1;
					fscanf(fpL," %[^\n]%*c",infos);
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
				
				// Ler ficheiro Clientes
				fpC = fopen("cliente.txt","r");
				ch = 0;
				lines = 0;
				while ((ch = fgetc(fpC)) != EOF){
					if (ch == '\n')
						lines++;
				}
				fclose(fpC);
				
				fpC = fopen("cliente.txt","r");
				CLIENTE CLI;
				CLI.ListaCompras = NULL;
				ENCOMENDA ENCAUX;
				int count;
				while(lines != 0){
					num = 1;
					fscanf(fpC," %[^\n]%*c",infos);
					in = strtok(infos, s);
					while( in != NULL ) {
						if(num == 1){
							CLI.NIF = atoi(in);
							num++;
						}
						else if(num == 2){
							strcpy(CLI.Nome,in);
							num++;
						}
						else if(num == 3){
							strcpy(CLI.Morada,in);
							num++;
						}
						else if(num == 4){
							CLI.Telefone = atoi(in);
							num++;
						}
						else if(num == 5){
							CLI.ListaCompras = ficheirosAtualizaListaComprasCliente(in, CLI);
						}
						in = strtok(NULL, s);
					}
					lines--;
					TCliente = InserirABP(TCliente, CLI);
					TCliente = CriarABPEquilibradaIB(TCliente);
					CLI.ListaCompras = NULL;
				}
				fclose(fpC);
				printf("\nOperação realizada com Sucesso!\n");
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
				if(TemLivro(Head,X) == 0){
					if(Head == NULL){
						InserirPrimeiroElemento(&Head, &Tail, X);
					}
					else{
						Head = InserirCabeca(Head, X);
					}
				}
				else{
					printf("ERRO: Já se encontra um livro com esse ISBN!\n");
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
	int n, i, aux, num, numAux;
	int numVendidos;
	CLIENTE C;

	while(true){
		//Obrigatorio Acrescentar no Minimo mais 4 Operacoes enquadradas com o Problema
		printf("\n _______________________________________________________________________________\n");
		printf("|                               Menu de Operações				|\n");
		printf("|                                    						|\n");
		printf("|	1.  Consultar o número de livros vendidos num dado período de tempo	|\n");
		printf("|	2.  Consultar a data da última compra de um livro    		        |\n");
		printf("|	3.  Consultar o número de livros comprados por um dado cliente          |\n");
		printf("|	4.  Consultar os K livros mais recentes de uma dada Área Científica     |\n");
		printf("|	5.  Consultar os K livros mais vendidos num dado período    	        |\n");
		printf("|	6.  Consultar a Área Científica com mais livros     		        |\n");
		printf("|	7.  Consultar o cliente com mais livros comprados     		        |\n");
		printf("|	8.  Consultar os clientes por ordem decrescente do número de compras	|\n");
		printf("|	9.  Consultar o Ano com mais publicações    			        |\n");
		printf("|	10. Consultar o cliente que gastou mais dinheiro num dado período       |\n");
		printf("|	11. Consultar o desperdício de memória (Título)			        |\n");
		printf("|	12. Consultar o desperdício de memória (Área Científica) 	        |\n");
		printf("|	13.  Consultar o número total de livros vendidos			|\n");
		printf("|	0.  Sair                    				        	|\n");
		printf("|_______________________________________________________________________________|\n");
		printf("Opção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			case 1:
				printf("\nIntroduza a data inicial do período de dias:\n");
				printf("Mês: ");
				int mes11, mes22, ano11, ano22;
				scanf("%d",&mes11);
				printf("Ano: ");
				scanf("%d",&ano11);
				printf("\n\nIntroduza a data final do período de dias:\n");
				printf("Mês: ");
				scanf("%d",&mes22);
				printf("Ano: ");
				scanf("%d",&ano22);

				int clienteNIF[25][1] = {0};
				float clientePreco[25][1] = {0.0};
				PNodoFila CMLC6 = FEncomendas;
				int verificar7 = 0;
				// Percorre a lista das Encomendas e guarda os anos numa matriz auxiliar (anos)
				int dataMes1, dataAno1;
				char *in11;
				char txt1[10];
				char s1[2] = "-";
				while(CMLC6 != NULL){
					verificar7 = 0;
					//--retirar data: mes e ano das encomendas
					dataMes1 = 0;
					dataAno1 = 0;
					strcpy(txt1,CMLC6->Elemento.DataEncomenda);
					in11 = strtok(txt1,s1);
					in11 = strtok(NULL, s1);
					while(in11 != NULL){
						if(dataMes1 == 0){
							dataMes1 = atoi(in11);
						}
						else if(dataAno1 == 0){
							dataAno1 = atoi(in11);
						}
						in11 = strtok(NULL, s1);
					}
					//--termina o retirar data!
					// Se as seguintes condições se verificarem:
					// a encomenda foi feita neste período de dias
					if(ano11 <= dataAno1 && ano22 >= dataAno1){
						if(ano11 == dataAno1 && mes11 <= dataMes1 || ano22 == dataAno1 && mes22 >= dataMes1 || ano11 < dataAno1 && ano22 > dataAno1){
							for (i = 0; i < 25; i++){
								if(clienteNIF[i][0] == CMLC6->Elemento.ClienteNIF){
									verificar7 = 1;
									clientePreco[i][0] = clientePreco[i][0] + CMLC6->Elemento.PrecoTotal;
								}
							}
							if(verificar7 == 0){
								for (i = 0; i < 25; i++){
									if(clienteNIF[i][0] == 0){
										clienteNIF[i][0] = CMLC6->Elemento.ClienteNIF;
										clientePreco[i][0] = CMLC6->Elemento.PrecoTotal;
										i = 25;
									}
								}
							}
						}
					}
					CMLC6 = CMLC6->Prox;
				}
				break;
			case 2:
				printf("\nA última compra foi realizada em:\n");
				PNodoFila pf = FEncomendas;

				while(pf != NULL){
					if(pf->Prox == NULL){
						printf("%s",pf->Elemento.DataEncomenda);
					}
					pf = pf->Prox;
				}
				break;
			case 3:
				ListarAllNIFNOME(TCliente);
				printf("\nNIF do Cliente:\n");
				scanf("%d",&C.NIF);
				if(PesquisarABP(TCliente, C) == 1){
					ListarListaCompras(TCliente, C);
				}
				else{
					printf("Cliente não existe!\n");
				}
				break;
			case 4:
				printf("Introduza o K:\n");
				int kk;
				scanf("%d",&kk);
				char ac[100];
				printf("Introduza a Área Científica:\n");
				scanf(" %[^\n]%*c",ac);

				printf("\nOs K livros mais recentes de uma dada Área Científica são:\n");
				int anos[25][2] = {0};
				PNodo livr1 = Head;
				int verificar3 = 0;
				
				// Percorre a lista dos livros e guarda os anos numa matriz auxiliar (anos)
				while(livr1 != NULL){
					verificar3 = 0;
					for (i = 0; i < 25; i++){
						if(anos[i][0] == livr1->Elemento.Ano && strcmp(livr1->Elemento.AreaCientifica,ac) == 0){
							verificar3 = 1;
							anos[i][1] = anos[i][1] + 1;
						}
					}
					if(verificar3 == 0){
						for (i = 0; i < 25; i++){
							if(anos[i][0] == 0 && strcmp(livr1->Elemento.AreaCientifica,ac) == 0){
								anos[i][0] = livr1->Elemento.Ano;
								anos[i][1] = 1;
								i = 25;
							}
						}
					}
					livr1 = livr1->Prox;
				}
				int a1, b1;

				for (int x = 0; x < 25; ++x) {
					for (int y = x + 1; y < 25; ++y) {
						if (anos[x][0] < anos[y][0]) {
							a1 = anos[x][1];
							b1 = anos[x][0];

							anos[x][1] = anos[y][1];
							anos[x][0] = anos[y][0];

							anos[y][1] = a1;
							anos[y][0] = b1;
						}
					}
				}
				int y = 0;
				while(kk != 0){
					if(anos[y][1] == 0){
						y++;
					}
					else{
						anos[y][1] = anos[y][1] - 1;
						ListarACeANO(Head, ac, anos[y][0]);
						kk--;
					}
					if(y == 25){
						kk = 0;
					}
				}
				
				
				break;
			case 5:
				printf("\nIntroduza os k livros a aprensentar:\n");
				int kkk;
				scanf("%d",&kkk);
				printf("\nIntroduza a data inicial do período de dias:\n");
				printf("Mês: ");
				int mes1, mes2, ano1, ano2;
				scanf("%d",&mes1);
				printf("Ano: ");
				scanf("%d",&ano1);
				printf("\n\nIntroduza a data final do período de dias:\n");
				printf("Mês: ");
				scanf("%d",&mes2);
				printf("Ano: ");
				scanf("%d",&ano2);

				int clienteMaisLivrosComprados5[25][2] = {0};
				PNodoFila CMLC5 = FEncomendas;
				int verificar6 = 0;
				// Percorre a lista das Encomendas e guarda os anos numa matriz auxiliar (anos)
				int dataMes, dataAno;
				char *in;
				char txt[10];
				char s[2] = "-";
				while(CMLC5 != NULL){
					verificar6 = 0;
					//--retirar data: mes e ano das encomendas
					dataMes = 0;
					dataAno = 0;
					strcpy(txt,CMLC5->Elemento.DataEncomenda);
					in = strtok(txt,s);
					in = strtok(NULL, s);
					while(in != NULL){
						if(dataMes == 0){
							dataMes = atoi(in);
						}
						else if(dataAno == 0){
							dataAno = atoi(in);
						}
						in = strtok(NULL, s);
					}
					//--termina o retirar data!
					// Se as seguintes condições se verificarem:
					// a encomenda foi feita neste período de dias
					if(ano1 <= dataAno && ano2 >= dataAno){
						if(ano1 == dataAno && mes1 <= dataMes || ano2 == dataAno && mes2 >= dataMes || ano1 < dataAno && ano2 > dataAno){
							for (i = 0; i < 25; i++){
								if(clienteMaisLivrosComprados5[i][0] == CMLC5->Elemento.LivroISBN){
									verificar6 = 1;
									clienteMaisLivrosComprados5[i][1] = clienteMaisLivrosComprados5[i][1] + CMLC5->Elemento.UnidadesEncomendadas;
								}
							}
							if(verificar6 == 0){
								for (i = 0; i < 25; i++){
									if(clienteMaisLivrosComprados5[i][0] == 0){
										clienteMaisLivrosComprados5[i][0] = CMLC5->Elemento.LivroISBN;
										clienteMaisLivrosComprados5[i][1] = CMLC5->Elemento.UnidadesEncomendadas;
										i = 25;
									}
								}
							}
						}
					}
					CMLC5 = CMLC5->Prox;
				}
				int aa,bb;
				for (int x = 0; x < 25; ++x) {
					for (int y = x + 1; y < 25; ++y) {
						if (clienteMaisLivrosComprados5[x][1] < clienteMaisLivrosComprados5[y][1]) {
							aa = clienteMaisLivrosComprados5[x][1];
							bb = clienteMaisLivrosComprados5[x][0];

							clienteMaisLivrosComprados5[x][1] = clienteMaisLivrosComprados5[y][1];
							clienteMaisLivrosComprados5[x][0] = clienteMaisLivrosComprados5[y][0];

							clienteMaisLivrosComprados5[y][1] = aa;
							clienteMaisLivrosComprados5[y][0] = bb;
						}
					}
				}
				int zz = 0, teste = 0;

				while(teste != 1){
					ListarISBN(Head,clienteMaisLivrosComprados5[zz][0]);
					if(zz == (kkk - 1)){
						teste = 1;
					}
					zz++;
				}
				break;
			case 6:
				printf("\nA Área Científica com mais Livros é: \n");
				char arrayOfArraysOfChars[25][100] = {}; // array to hold multiple single arrays of characters
				int acL[25] = {0};
				PNodo caseSix = Head;
				int verificar1;
				while(caseSix != NULL){
					verificar1 = 0;
					for (int i = 0; i < 25; i++){
						if(strcmp(arrayOfArraysOfChars[i],caseSix->Elemento.AreaCientifica) == 0){
							verificar1 = 1;
							acL[i] = acL[i]+1;
						}
					}
					if(verificar1 == 0){
						for (int j = 0; j < 25; j++){
							if (strlen(arrayOfArraysOfChars[j]) == 0){
								strcpy(arrayOfArraysOfChars[j],caseSix->Elemento.AreaCientifica);
								acL[j] = 1;
								j = 25;
							}
							
						}
					}
					caseSix = caseSix->Prox;
				}
				int posicao = 0;
				numAux = 0;
				num = 0;
				for (int k = 0; k < 25; k++){
					numAux = acL[k];
					if(numAux > num){
						num = numAux;
						posicao = k;
					}
				}
				printf("%s\n",arrayOfArraysOfChars[posicao]);
				break;
			case 7:
				printf("\nCliente com mais Livros comprados: \n");
				int clienteMaisLivrosComprados[25][2] = {0};
				PNodoFila CMLC = FEncomendas;
				int verificar2 = 0;
				// Percorre a lista das Encomendas e guarda os anos numa matriz auxiliar (anos)
				while(CMLC != NULL){
					verificar2 = 0;
					for (i = 0; i < 25; i++){
						if(clienteMaisLivrosComprados[i][0] == CMLC->Elemento.ClienteNIF){
							verificar2 = 1;
							clienteMaisLivrosComprados[i][1] = clienteMaisLivrosComprados[i][1] + CMLC->Elemento.UnidadesEncomendadas;
						}
					}
					if(verificar2 == 0){
						for (i = 0; i < 25; i++){
							if(clienteMaisLivrosComprados[i][0] == 0){
								clienteMaisLivrosComprados[i][0] = CMLC->Elemento.ClienteNIF;
								clienteMaisLivrosComprados[i][1] = CMLC->Elemento.UnidadesEncomendadas;
								i = 25;
							}
						}
					}
					CMLC = CMLC->Prox;
				}
				int nif = 0, nifAux = 0;
				num = 0;
				numAux = 0;
				
				for (i = 0; i < 25; i++){
					if(clienteMaisLivrosComprados[i][0] != 0){
						nifAux = clienteMaisLivrosComprados[i][0];
						numAux = clienteMaisLivrosComprados[i][1];
						if(numAux > num){
							nif = nifAux;
							num = numAux;
						}
					}
				}
				CLIENTE C;
				C.NIF = nif;
				ListarNIFNOMEMaisLivrosComprados(TCliente,C);
				break;
			case 8:
				printf("\nClientes por ordem decrescente do número de compras:\n");
				int clienteMaisLivrosComprados1[25][2] = {0};
				PNodoFila CMLC1 = FEncomendas;
				int verificar4 = 0;
				// Percorre a lista das Encomendas e guarda os anos numa matriz auxiliar (anos)
				while(CMLC1 != NULL){
					verificar4 = 0;
					for (i = 0; i < 25; i++){
						if(clienteMaisLivrosComprados1[i][0] == CMLC1->Elemento.ClienteNIF){
							verificar4 = 1;
							clienteMaisLivrosComprados1[i][1] = clienteMaisLivrosComprados1[i][1] + CMLC1->Elemento.UnidadesEncomendadas;
						}
					}
					if(verificar4 == 0){
						for (i = 0; i < 25; i++){
							if(clienteMaisLivrosComprados1[i][0] == 0){
								clienteMaisLivrosComprados1[i][0] = CMLC1->Elemento.ClienteNIF;
								clienteMaisLivrosComprados1[i][1] = CMLC1->Elemento.UnidadesEncomendadas;
								i = 25;
							}
						}
					}
					CMLC1 = CMLC1->Prox;
				}
				int a,b;
				for (int x = 0; x < 25; ++x) {
					for (int y = x + 1; y < 25; ++y) {
						if (clienteMaisLivrosComprados1[x][1] < clienteMaisLivrosComprados1[y][1]) {
							a = clienteMaisLivrosComprados1[x][1];
							b = clienteMaisLivrosComprados1[x][0];

							clienteMaisLivrosComprados1[x][1] = clienteMaisLivrosComprados1[y][1];
							clienteMaisLivrosComprados1[x][0] = clienteMaisLivrosComprados1[y][0];

							clienteMaisLivrosComprados1[y][1] = a;
							clienteMaisLivrosComprados1[y][0] = b;
						}
					}
				}
				CLIENTE C1;
				for(int cc = 0; cc < 25; cc++){
					C1.NIF = clienteMaisLivrosComprados1[cc][0];
					ListarNIFNOMEMaisLivrosComprados(TCliente,C1);
				}
				break;
			case 9:
				printf("\nO ano com mais publicações é:");
				int anos5[25][2] = {0};
				PNodo livr = Head;
				int verificar = 0;
				// Percorre a lista dos livros e guarda os anos numa matriz auxiliar (anos)
				while(livr != NULL){
					verificar = 0;
					for (i = 0; i < 25; i++){
						if(anos5[i][0] == livr->Elemento.Ano){
							verificar = 1;
							anos5[i][1] = anos5[i][1] + 1;
						}
					}
					if(verificar == 0){
						for (i = 0; i < 25; i++){
							if(anos5[i][0] == 0){
								anos5[i][0] = livr->Elemento.Ano;
								anos5[i][1] = 1;
								i = 25;
							}
						}
					}
					livr = livr->Prox;
				}
				int anoF = 0, anoAux = 0, aux1 = 0;
				aux = 0;
				
				for (i = 0; i < 25; i++){
					if(anos5[i][0] != 0){
						anoAux = anos5[i][0];
						aux = anos5[i][1];
						if(aux > aux1){
							anoF = anoAux;
							aux1 = aux;
						}
					}
				}
				printf("\n%d", anoF);
				break;
			case 10:
				printf("\nIntroduza a data inicial do período de dias:\n");
				printf("Mês: ");
				int mes11, mes22, ano11, ano22;
				scanf("%d",&mes11);
				printf("Ano: ");
				scanf("%d",&ano11);
				printf("\n\nIntroduza a data final do período de dias:\n");
				printf("Mês: ");
				scanf("%d",&mes22);
				printf("Ano: ");
				scanf("%d",&ano22);

				int clienteNIF[25][1] = {0};
				float clientePreco[25][1] = {0.0};
				PNodoFila CMLC6 = FEncomendas;
				int verificar7 = 0;
				// Percorre a lista das Encomendas e guarda os anos numa matriz auxiliar (anos)
				int dataMes1, dataAno1;
				char *in11;
				char txt1[10];
				char s1[2] = "-";
				while(CMLC6 != NULL){
					verificar7 = 0;
					//--retirar data: mes e ano das encomendas
					dataMes1 = 0;
					dataAno1 = 0;
					strcpy(txt1,CMLC6->Elemento.DataEncomenda);
					in11 = strtok(txt1,s1);
					in11 = strtok(NULL, s1);
					while(in11 != NULL){
						if(dataMes1 == 0){
							dataMes1 = atoi(in11);
						}
						else if(dataAno1 == 0){
							dataAno1 = atoi(in11);
						}
						in11 = strtok(NULL, s1);
					}
					//--termina o retirar data!
					// Se as seguintes condições se verificarem:
					// a encomenda foi feita neste período de dias
					if(ano11 <= dataAno1 && ano22 >= dataAno1){
						if(ano11 == dataAno1 && mes11 <= dataMes1 || ano22 == dataAno1 && mes22 >= dataMes1 || ano11 < dataAno1 && ano22 > dataAno1){
							for (i = 0; i < 25; i++){
								if(clienteNIF[i][0] == CMLC6->Elemento.ClienteNIF){
									verificar7 = 1;
									clientePreco[i][0] = clientePreco[i][0] + CMLC6->Elemento.PrecoTotal;
								}
							}
							if(verificar7 == 0){
								for (i = 0; i < 25; i++){
									if(clienteNIF[i][0] == 0){
										clienteNIF[i][0] = CMLC6->Elemento.ClienteNIF;
										clientePreco[i][0] = CMLC6->Elemento.PrecoTotal;
										i = 25;
									}
								}
							}
						}
					}
					CMLC6 = CMLC6->Prox;
				}
				float aaa,bbb;
				for (int x = 0; x < 25; ++x) {
					for (int y = x + 1; y < 25; ++y) {
						if (clientePreco[x][0] < clientePreco[y][0]) {
							aaa = clientePreco[x][0];
							bbb = clienteNIF[x][0];

							clientePreco[x][0] = clientePreco[y][0];
							clienteNIF[x][0] = clienteNIF[y][0];

							clientePreco[y][0] = aaa;
							clienteNIF[y][0] = bbb;
						}
					}
				}
				int egg = clienteNIF[0][0];
				CLIENTE Cegg;
				Cegg.NIF = egg;
				ListarNIFNOMEMaisLivrosComprados(TCliente, Cegg);
				break;
			case 11:
				printf("\nEm relação ao campo Título dos Livros o desperdício de memória é:\n");
				PNodo L1 = Head;
				aux = 0;
				num = 0;
				while(L1 != NULL){
					aux = 50 - strlen(L1->Elemento.Titulo);
					num = num + aux;
					L1 = L1->Prox;
				}
				printf("%d",num);
				break;
			case 12:
				printf("\nEm relação ao campo Área Científica dos Livros o desperdício de memória é:\n");
				PNodo L2 = Head;
				aux = 0;
				num = 0;
				while(L2 != NULL){
					aux = 50 - strlen(L2->Elemento.AreaCientifica);
					printf("AUX: %d\n", aux);
					num = num + aux;
					L2 = L2->Prox;
				}
				printf("%d",num);
				break;
			case 13:
				numVendidos = LivrosVendidos(FEncomendas);
				printf("\nLivros Vendidos: %d\n",numVendidos);
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
