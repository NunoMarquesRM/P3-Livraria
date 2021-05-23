#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#include "Livros.h"
//#include "Cliente.h"
//#include "Encomenda.h"

void menuFicheiro(){
	int n;
	
	while(true){
		
		printf("\n ____________________________________\n");
		printf("|          Menu de Ficheiros         |\n");
		printf("|                                    |\n");
		printf("|	1. Novo Ficheiro             |\n");
		printf("|	2. Guardar Ficheiro          |\n");
		printf("|	3. Abrir Ficheiro            |\n");
		printf("|	0. Sair                      |\n");
		printf("|____________________________________|\n");
		
		printf("Opção: s");
		scanf("%d",&n);
		
		
		// Menu Principal
		switch (n){
			
		    case 1:
				//NovoFicheiro();
		    	break;
		
		    case 2:
				//AbrirFicheiro();
		    	break;
		    
		    case 3:
				//GuardarFicheiro();
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
	// No futuro esta variavel tem de estar no main e ser
	// mandada como parametro
	int c = 0;
	PNodo Head = NULL, Tail = NULL;

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
				c++;
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
				printf("|__________________________________|\n");
				printf("Opção: ");
				scanf("%d",&opcao);

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
	int n;
	
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
				//InserirCliente();
		    	break;
		
		    case 2:
		    	// Dado o NIF
				//RemoverCliente();
		    	break;
		    
		    case 3:
		    	// Dado o NIF
				//AlterarCliente();
		      	break;
		    
		    case 4:
		    	//NIF, Nome, Morada(dada uma frase, mostrar os clientes com esta frase na morada)
		    	// Consultar a Lista de Compras dum cliente dado o NIF ou qq coisa - Pode ser usando um Vetor
				//ConsultarCliente();
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
	int n;
	
	while(true){
		
		printf("\n ______________________________________\n");
		printf("|          Menu de Encomendas          |\n");
		printf("|                                      |\n");
		printf("|	1. Inserir Encomenda           |\n");
		printf("|	2. Remover Encomenda           |\n");
		printf("|	0. Sair                        |\n");
		printf("|______________________________________|\n");
		
		printf("Opção: ");
		scanf("%d",&n);
		
		// Menu Principal
		switch (n){
			
			// Filas!!
		    case 1:
		    	// Produto, Data de Compra, N�mero de Unidades Compradas, Pre�o total
				//InserirEncomenda();
		    	break;
		
		    case 2:
		    	// Implica atualizar a lista de compras do cliente
		    	//
				//RemoverEncomenda();
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
	int n;
	
	while(true){
		
		printf("\n _______________________________________________________________________________\n");
		printf("|                               Menu de Operações				|\n");
		printf("|                                    						|\n");
		//Obrigatorio Acrescentar no Minimo mais 4 Operacoes enquadradas com o Problema
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
				//LivrosVendidos();
		    	break;
		
		    case 2:
				//UltimaCompra();
		    	break;
		    
		    case 3:
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
				//ClienteMaisLivros();
		    	break;
		    	
		    case 8:
				//ClientesDecCompras();
		    	break;	
		    
		    case 9:
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

void main(){
	
    setlocale(LC_ALL, "Portuguese");
	int n;
	
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
