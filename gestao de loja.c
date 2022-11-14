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
	char nome[50];
	char categoria[50];
	char codigo[7];
	data aquisicao;
	int quantidade;
	float custo;
	float valor;
} produtos;

produtos pdt;

void cabecalho();

//funçoes que gerenciam as açoes relacionadas às roupas
void GerenciarRoupas();
void inserirDados();
void ListarEstoque();
void pesquisarRoupas();
void excluirItem();
void pesquisarCategoria();
void editar_dados();
void buscarCodigo();

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

  	printf("\ndigite a opçao desejada: \n");
  	scanf("%d", &opc);

  	switch(opc){

      case 1:
      	GerenciarRoupas();
      break;

      case 2:
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
      	printf("opçao invalida!");
          getch();
	  }

  } while(opc != 5);

	return 0;
}

void cabecalho(){
	system("cls");
	printf("-------------------------------------------\n");
	printf("ADMINISTRAÇAO DA LOJA\n");
	printf("-------------------------------------------\n\n");

}

void GerenciarRoupas (){


	int op;

	do {
		system("cls");
		printf("-------------------ROUPAS-------------------\n");
		printf("1.Cadastrar uma nova peça roupa\n");
		printf("2.remover uma peça do estoque\n");
		printf("3.atualizar informaçao da peça \n");
		printf("4.pesquisar por nome\n");
		printf("5.pesquisar por categoria\n");
		printf("6.pesquisar por codigo\n");
		printf("7.listar peças de roupas disponiveis\n");
		printf("8.sair\n");
		printf("-------------------------------------------\n");


		printf("\nescolha uma opçao: ");
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
     	printf("até mais!!");
      	getch();
      break;

      default:
          printf("opçao invalida!");
          getch();

		}

	}while(op !=8 );


}

void inserirDados(){
	FILE *estoque;
	int contProd;

	estoque = fopen("Roupas_Disponiveis.txt", "ab");

	if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		
		printf("insira a quantidade de roupas que deseja cadastrar:\n");
		scanf("%d", &contProd);
		cabecalho();
		int i;
		
		for( i = 0; i < contProd; i++){
			
			fflush(stdin);
			printf(" insira o nome da peça: ");
			gets(pdt.nome);

			fflush(stdin);
			printf("insira a categoria: ");
			gets(pdt.categoria);

			fflush(stdin);
			printf("insira o codigo: ");
			gets(pdt.codigo);

			printf("insira a data de aquisiçao: ");
			scanf("%d%d%d", &pdt.aquisicao.dia, &pdt.aquisicao.mes, &pdt.aquisicao.ano);

			printf("insira a quantidade: ");
			scanf("%d", &pdt.quantidade);

			printf("insira o custo: ");
			scanf("%f", &pdt.custo);

			printf("insira o valor: ");
			scanf("%f", &pdt.valor);
			

			fwrite(&pdt, sizeof(produtos),1,estoque);
		
		}
		fclose(estoque);
	}

}

void ListarEstoque(){
	FILE *estoque;

	estoque = fopen("Roupas_Disponiveis.txt", "rb");

	cabecalho();
	if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		while (fread(&pdt, sizeof(produtos),1,estoque )==1){
			printf("nome: %s\n", pdt.nome);
			printf("categoria: %s\n", pdt.categoria);
			printf("codigo: %s\n", pdt.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
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
	FILE *estoque;
	char nome[50];

	estoque = fopen("Roupas_Disponiveis.txt", "rb");

	cabecalho();
	if ( estoque == NULL){
		printf("problemas na abertura do arquivo!\n");
	}
	else {
		fflush(stdin);
		printf("digite o nome a pesquisar: ");
		gets(nome);

		while( fread(&pdt, sizeof(produtos),1,estoque) == 1){
			if(strcmp(nome, pdt.nome) == 0){
			printf("\n");

			printf("-----------------ITEM---------------\n");
			printf("nome: %s\n", pdt.nome);
			printf("categoria: %s\n", pdt.categoria);
			printf("codigo: %s\n", pdt.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
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
	FILE *estoque;
	FILE *estoqueTemp;
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
		FILE *estoque;
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
			printf("data de aquisiçao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
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
	    printf("Não foi possível abrir o arquivo\n");
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
			printf("data de aquisiçao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
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
        
        printf("Tem a certeza que pertende alterar os dados deste/s contactos(S/N)? ");
	  	if(getche() == 'S')
	    {
	        if(remove("Roupas_Disponiveis.txt") == 0 && rename ("temp.txt", "Roupas_Disponiveis.txt") == 0)
	            {
	            	FILE* estoque;
					
					estoque = fopen("Roupas_Disponiveis.txt", "ab");
	            	
	         	printf("\n--------------ALTERAÇAO------------\n");
			fflush(stdin);
			printf(" insira o nome da peça: ");
			gets(pdt.nome);

			fflush(stdin);
			printf("insira a categoria: ");
			gets(pdt.categoria);
			
			fflush(stdin);
			printf("insira o novo codigo: ");
			gets(pdt.codigo);

			printf("insira a nova quantidade: ");
			scanf("%d", &pdt.quantidade);
		
		     printf("insira nova data de aquisiçao: ");
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

/*void ordenar(char v[][50], int tamanho){
	int i,j;
	char auxiliar[50];
     for (i = 0; i < tamanho - 1; i++){
     	for(j = i+1; j< tamanho; j++){
     		if(strcmp(v[i],v[j]) > 0){
     			strcpy(auxiliar,v[i]);
     			strcpy(v[i],v[j]);
     			strcpy(v[j],auxiliar);
			}
		}
	}

}*/

void buscarCodigo(){
	
	
	FILE *estoque;
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
			printf("data de aquisiçao: %d/%d/%d\n",pdt.aquisicao.dia, pdt.aquisicao.mes, pdt.aquisicao.ano);
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

