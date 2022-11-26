#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

typedef struct{
	int dia;
	int mes;
	int ano;
}data;
typedef struct {
	char categoria[50];
	char codigo[10];
	data aquisicao;
	int quantidade;
	float custo;
	float valor;
	char nome[50];
} produtos;
produtos pdt;

typedef struct {
	char nomeCli[50];
	char codigoCli[5];
	char CPF[12];
	char telefoneCli[15];
	char enderecoCli[50];
	data nascimentoCli;
} cliente;
cliente Cli;

void cabecalho();

//funÁoes que gerenciam as aÁoes relacionadas as roupas


void GerenciarRoupas();
void inserirDados();
void ListarEstoque();
void pesquisarRoupas();
void excluirItem();
void pesquisarCategoria();
void editar_dados();
void buscarCodigo();


//funÁoes que gereciam as aÁoes relacionadas ao cliente

void CadastrarCliente();
void inserirDadosCli();

int main (){
  setlocale(LC_ALL, "Portuguese");

	  int opc;
  do {
     cabecalho();
  	printf("1 - gerenciar roupas\n");
  	printf("2 - cadastrar cliente\n");
  	printf("3 - cadastrar fornecedor\n");
  	printf("4 - cadastrar vendas\n");
  	printf("5 - Sair\n");

  	printf("\ndigite a opÔøΩao desejada: \n");
  	scanf("%d", &opc);

  	switch(opc){

      case 1:
      	GerenciarRoupas();
      break;

      case 2:
      	 CadastrarCliente();
      break;

      case 3:
      break;

      case 4:
      break;

      case 5:
      	printf("ate logo!!");
      	getch();
      break;

      default:
      	printf("op√ßao invalida!");
          getch();
	  }

  } while(opc != 5);

	return 0;
}

void cabecalho(){
	system("cls");
	printf("-------------------------------------------\n");
	printf("ADMINISTRA√áAO DA LOJA\n");
	printf("-------------------------------------------\n\n");

}

void GerenciarRoupas (){


	int op;

	do {
		system("cls");
		printf("-------------------ROUPAS-------------------\n");
		printf("1.Cadastrar uma nova pe√ßa roupa\n");
		printf("2.Remover uma pe√ßa do estoque\n");
		printf("3.Atualizar informa√ßao da pe√ßa \n");
		printf("4.Pesquisar por nome\n");
		printf("5.Pesquisar por categoria\n");
		printf("6.Pesquisar por codigo\n");
		printf("7.Listar pe√ßas de roupas disponiveis\n");
		printf("8.Sair\n");
		printf("-------------------------------------------\n");


		printf("\nescolha uma op√ßao: ");
		scanf("%d", &op);

		switch(op){

      case 1:
      	inserirDados();
      break;

      case 2:
      	excluirItem();
      break;

      case 3:
          editar_dados();
      break;

      case 4:
      	pesquisarRoupas();
      break;

      case 5:
      	pesquisarCategoria();
      break;

      case 6:
      	buscarCodigo();

      break;

      case 7:
      	ListarEstoque();
      break;

       case 8:
     	printf("at√© mais!!");
      	getch();
      break;

      default:
          printf("op√ßao invalida!");
          getch();

		}

	}while(op !=8 );


}

void inserirDados(){
	FILE* estoque;
	FILE* estoque2;
	produtos pdtLeitura;

	estoque = fopen("Roupas_Disponiveis.txt", "ab");

	if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		cabecalho();
		do {

			fflush(stdin);
			printf("------------------------------------\n");

			printf("insira o nome da peÁa: ");

			printf("insira o nome da pe√ßa: ");

			fgets(pdt.nome,50,stdin);

			fflush(stdin);
			printf("insira a categoria: ");
			fgets(pdt.categoria,50,stdin);

			fflush(stdin);
			printf("insira o codigo: ");

			fgets(pdt.codigo,10,stdin);
			
		estoque2 = fopen("Roupas_Disponiveis.txt", "rb");
		   	if(estoque2 == NULL){
				printf("Problemas na abertura do arquivo.");
			}
			else {
				while(fread(&pdtLeitura, sizeof(produtos),1, estoque2) == 1){
					if(strcmp(pdt.codigo,pdtLeitura.codigo) == 0){
						printf("o codigo ja est· no sistema.\n");

			          }
						return ;
					}
                   
				}
				fclose(estoque);
			printf("insira a data de aquisiÁao (dd mm aaaa): ");

			gets(pdt.codigo);

			printf("insira a data de aquisi√ßao (dd mm aaaa): ");
			scanf("%d%d%d", &pdt.aquisicao.dia, &pdt.aquisicao.mes, &pdt.aquisicao.ano);

			printf("insira a quantidade: ");
			scanf("%d", &pdt.quantidade);

			printf("insira o custo: ");
			scanf("%f", &pdt.custo);

			printf("insira o valor: ");
			scanf("%f", &pdt.valor);
			printf("------------------------------------\n");

			printf("peÁa cadastrada com sucesso!");
	
			getch();

			fwrite(&pdt, sizeof(produtos),1,estoque);

			printf("\ndeseja continuar (s/n)?\n");

        } while (getche() == 's');
         fclose(estoque);
			}


		}




void ListarEstoque(){
	FILE* estoque;

	estoque = fopen("Roupas_Disponiveis.txt", "rb");

	cabecalho();
	if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {

		while (fread(&pdt, sizeof(produtos),1,estoque )==1){
			printf("------------------------------------\n");
			printf("nome: %s", pdt.nome);
			printf("categoria: %s", pdt.categoria);
			printf("codigo: %s", pdt.codigo);
			printf("data de aquisiÁao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
			printf("quantidade: %d\n", pdt.quantidade);
			printf("custo: %.2f\n", pdt.custo);
			printf("valor: %.2f\n", pdt.valor);
			printf("------------------------------------\n");
		}
	}
	fclose(estoque);
	getch();

}

void pesquisarRoupas(){
	FILE* estoque;
	char nome[50];

	estoque = fopen("Roupas_Disponiveis.txt", "rb");

	cabecalho();
	if ( estoque == NULL){
		printf("problemas na abertura do arquivo!\n");
	}
	else {
		fflush(stdin);
		printf("digite o nome a pesquisar: ");
		fgets(nome,50,stdin);

		while( fread(&pdt, sizeof(produtos),1,estoque) == 1){
			if(strcmp(nome, pdt.nome) == 0){
			printf("\n");

			printf("-----------------ITEM---------------\n");
			printf("nome: %s\n", pdt.nome);
			printf("categoria: %s\n", pdt.categoria);
			printf("codigo: %s\n", pdt.codigo);
			printf("data de aquisi√ßao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
			printf("quantidade: %d\n", pdt.quantidade);
			printf("custo: %.2f\n", pdt.custo);
			printf("valor: %.2f\n", pdt.valor);
			printf("------------------------------------\n");

			}
		}

	}
	fclose(estoque);
	getch();
}

void excluirItem(){
	FILE* estoque;
	FILE* estoqueTemp;
	char id[7];

	cabecalho();
	estoque = fopen("Roupas_Disponiveis.txt", "rb");
	estoqueTemp = fopen("Roupas_DisponiveisTemp.txt", "ab");

	if( estoque == NULL || estoqueTemp == NULL){
		printf("problema na abertura do arquivo!");
	}
	else {
		fflush(stdin);
		printf("digite o codigo do item que deseja remover:  ");
		gets(id);

		while(fread(&pdt, sizeof(produtos),1, estoque) == 1) {
			if (strcmp(id,pdt.codigo) != 0){
				fwrite(&pdt, sizeof(produtos),1, estoqueTemp);
			}
		}

	}
	fclose(estoque);
	fclose(estoqueTemp);
	remove("Roupas_Disponiveis.txt");
	rename("Roupas_DisponiveisTemp.txt","Roupas_Disponiveis.txt" );
	printf("item excluido!\n");
	getch();

}

void pesquisarCategoria(){
		FILE* estoque;
	     char aux[50];

	estoque = fopen("Roupas_Disponiveis.txt", "rb");

	cabecalho();
	if ( estoque == NULL){
		printf("problemas na abertura do arquivo!\n");
    }
     else {
		fflush(stdin);
		printf("digite a categoria que deseja  pesquisar: ");
		gets(aux);

		while( fread(&pdt, sizeof(produtos),1,estoque) == 1){
			if(strcmp(aux, pdt.categoria) == 0){
			printf("\n");
			printf("-----------------ITEM---------------\n");
			printf("nome: %s\n", pdt.nome);
			printf("categoria: %s\n", pdt.categoria);
			printf("codigo: %s\n", pdt.codigo);
			printf("data de aquisi√ßao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
			printf("quantidade: %d\n", pdt.quantidade);
			printf("custo: %.2f\n", pdt.custo);
			printf("valor: %.2f\n", pdt.valor);
			printf("------------------------------------\n");
			}

	}
	fclose(estoque);
	getch();
  }
}

void editar_dados()
{
    FILE* estoque;
    FILE* temp;
    produtos pdt;
    char id[7];

	estoque = fopen("Roupas_Disponiveis.txt","rb+");
	temp = fopen("temp.txt","wb");

    if(estoque== NULL && temp == NULL)
    {
	    printf("N„o foi possivel abrir o arquivo\n");
	    getch();
    }
    else
    {
    	cabecalho();
    	fflush(stdin);
    	printf("Digite o codigo do item que deseja editar: ");
    	gets(id);

    	while(fread(&pdt, sizeof(produtos), 1, estoque) == 1)
    	{
        	if(strcmp(id, pdt.codigo) == 0)
        	{
	          printf("-----------------ITEM---------------\n");
			printf("nome: %s\n", pdt.nome);
			printf("categoria: %s\n", pdt.categoria);
			printf("codigo: %s\n", pdt.codigo);
			printf("data de aquisi√ßao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
			printf("quantidade: %d\n", pdt.quantidade);
			printf("custo: %.2f\n", pdt.custo);
			printf("valor: %.2f\n", pdt.valor);
			printf("------------------------------------\n");
        	}
	        else
	        {
	            fwrite(&pdt, sizeof(produtos), 1, temp);
	        }
	    }
        fclose(estoque);
        fclose(temp);
        fflush(stdin);

        printf("Deseja iniciar a altera√ßao dos dados(s/n)? ");
	  	if(getche() == 's')
	    {
	        if(remove("Roupas_Disponiveis.txt") == 0 && rename ("temp.txt", "Roupas_Disponiveis.txt") == 0)
	            {
	            	FILE* estoque;

					estoque = fopen("Roupas_Disponiveis.txt", "ab");

	         	printf("\n--------------ALTERA√áAO------------\n");
			fflush(stdin);
			printf(" insira o nome da peÁa: ");
			fflush(stdin);
			
			printf("insira a categoria: ");
			gets(pdt.categoria);

			fflush(stdin);
			printf("insira o novo codigo: ");
			gets(pdt.codigo);

			printf("insira a nova quantidade: ");
			scanf("%d", &pdt.quantidade);

		     printf("insira nova data de aquisi√ßao: ");
			scanf("%d%d%d", &pdt.aquisicao.dia, &pdt.aquisicao.mes, &pdt.aquisicao.ano);

			printf("insira o novo custo: ");
			scanf("%f", &pdt.custo);

			printf("insira o novo valor: ");
			scanf("%f", &pdt.valor);

               fwrite(&pdt, sizeof(produtos),1, estoque);
			printf("\n item alterado com sucesso");
	            }
	        else
	            {
	                remove("temp.txt");
	            }
	    }
	    fclose(temp);
	    fclose(estoque);
	    getch();
 	}
}


void buscarCodigo(){


	FILE* estoque;
  char id[7];

	estoque = fopen("Roupas_Disponiveis.txt", "rb");

	cabecalho();
	if ( estoque == NULL){
		printf("problemas na abertura do arquivo!\n");
    }
     else {
		fflush(stdin);
		printf("digite o codigo que deseja  pesquisar: ");
		gets(id);

		while( fread(&pdt, sizeof(produtos),1,estoque) == 1){
			if(strcmp(id, pdt.codigo) == 0){
			printf("codigo encontrado\n");

			printf("-----------------ITEM---------------\n");
			printf("nome: %s\n", pdt.nome);
			printf("categoria: %s\n", pdt.categoria);
			printf("codigo: %s\n", pdt.codigo);
			printf("data de aquisi√ßao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
			printf("quantidade: %d\n", pdt.quantidade);
			printf("custo: %.2f\n", pdt.custo);
			printf("valor: %.2f\n", pdt.valor);
			printf("------------------------------------\n");
			}

			if (strcmp(id, pdt.codigo) != 0 ){
				printf("codigo nao encontrado\n");
			}


	}
	fclose(estoque);
	getch();
  }
}

void CadastrarCliente(){
	
	int op;

	do {
		system("cls");
		printf("-------------------ROUPAS-------------------\n");
		printf("1.Cadastrar cliente\n");
		printf("2.Remover cliente\n");
		printf("3.Alterar dados do cliente \n");
		printf("4.Pesquisar por nome\n");
		printf("5.Pesquisar por codigo\n");
		printf("6.Pesquisar por CPF\n");
		printf("7.Listar clientes\n");
		printf("8.Sair\n");
		printf("-------------------------------------------\n");


		printf("\nSelecione a opÁao desejada: ");

		scanf("%d", &op);

		switch(op){

      case 1:
      	inserirDadosCli();
      break;

      case 2:
      	//excluirCliente();
      break;

      case 3:
         // editar_dadosCli();
      break;

      case 4:
      	//pesquisarCliente();
      break;

      case 5:
      	//pesquisarCodigo();
      break;

      case 6:
      //	buscarCPF();

      break;

      case 7:
      //	ListarClientes();
      break;

       case 8:
     	printf("ate mais!");
      	getch();
      break;

      default:
          printf("opÁao invalida!");
          getch();

		}

	}while(op !=8 );


}

void inserirDadosCli() {
	FILE *CLIENTE;
	CLIENTE = fopen("clientes_cadastrados.txt","ab");
	
	do {
		
		fflush(stdin);
		printf("Inserir o nome do cliente: ");
		fgets(Cli.nomeCli, 50, stdin);
		
		fflush(stdin);
		printf("Inserir o CPF do cliente: ");
		fgets(Cli.CPF,12,stdin);
		
		fflush(stdin);
		printf("Inserir o codigo do cliente: ");
		fgets(Cli.codigoCli,5,stdin);
		
		fflush(stdin);
		printf("Inserir o telefone do cliente: ");
		fgets(Cli.telefoneCli,15,stdin);
		
		fflush(stdin);
		printf("Inserir a data de nascimento dos cliente: ");
		scanf("%d %d %d", &Cli.nascimentoCli.dia, &Cli.nascimentoCli.mes, &Cli.nascimentoCli.ano);
		
		fwrite(&Cli, sizeof(cliente), 1, CLIENTE);
		
		printf("\ndeseja continuar (s/n)?\n");

	}while(getche() == 's');
	fclose(CLIENTE);
}


