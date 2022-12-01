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
	char categoria[30];
	char codigo[10];
	data aquisicao;
	int quantidade;
	float custo;
	float valor;
	char nome[30];
} roupas;

typedef struct {
	char nomeCli[50];
	char codigoCli[5];
	char CPF[13];
	char telefoneCli[15];
	char enderecoCli[50];
	data nascimentoCli;
} clientes;

void cabecalho();

// funcoes que administram as acoes relacionadas as roupas
void GerenciarRoupas();
void inserirDados();
void listarEstoque();
void pesquisarRoupas();
void pesquisarCategoria();
void buscarCodigo();
void editar_dados();
void excluirItem();

// funcoes que administram as acoes relacionadas ao cliente
void gerenciarCliente();
void inserirDadosCli();
void excluirCliente();

int main (){
  setlocale(LC_ALL, "Portuguese");

	  int opc;
  do {
     cabecalho();
  	printf("1 - gerenciar roupas\n");
  	printf("2 - gerenciar cliente\n");
  	printf("3 - gerenciar fornecedor\n");
  	printf("4 - cadastrar vendas\n");
  	printf("5 - Sair\n");

  	printf("\ndigite a opçao desejada: \n");
  	scanf("%d", &opc);

  	switch(opc){

      case 1:
      	GerenciarRoupas();
      break;

      case 2:
        gerenciarCliente();
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

void GerenciarRoupas(){


	int op;

	do {
		system("cls");
		printf("-------------------ROUPAS-------------------\n");
		printf("1.Cadastrar uma nova peça roupa\n");
		printf("2.Remover uma peça do estoque\n");
		printf("3.Atualizar informaçao da peça \n");
		printf("4.Pesquisar por nome\n");
		printf("5.Pesquisar por categoria\n");
		printf("6.Pesquisar por codigo\n");
		printf("7.Listar peças de roupas disponiveis\n");
		printf("8.Sair\n");
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
      	listarEstoque();
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
	estoque = fopen("Roupas.txt","ab");
	
	roupas rp;
	
		if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		cabecalho();
		
		do {
			fflush(stdin);
			printf("\n");
			printf("digite o nome da peça: ");
			fgets(rp.nome,30,stdin);
			
			fflush(stdin);
			printf("insira a categoria: ");
			fgets(rp.categoria,30,stdin);

			fflush(stdin);
			printf("insira o codigo: ");
			fgets(rp.codigo,10,stdin);

			printf("insira a data de aquisiçao (dd mm aaaa): ");
			scanf("%d%d%d", &rp.aquisicao.dia, &rp.aquisicao.mes, &rp.aquisicao.ano);

			printf("insira a quantidade: ");
			scanf("%d", &rp.quantidade);

			printf("insira o custo: ");
			scanf("%f", &rp.custo);

			printf("insira o valor: ");
			scanf("%f", &rp.valor);
			printf("------------------------------------\n");

			printf("peça cadastrada com sucesso!");
	
			getch();

			fwrite(&rp, sizeof(roupas),1,estoque);

			printf("\ndeseja continuar (s/n)?\n");
			
		}while(getche() == 's');
		fclose(estoque);
    }
}

void listarEstoque(){
	
	FILE *estoque;
	estoque = fopen("Roupas.txt","rb");
	
	roupas rp;
	
	cabecalho();
		if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		
		while (fread(&rp, sizeof(roupas),1,estoque)==1){
			printf("------------------------------------\n");
			printf("nome: %s", rp.nome);
			printf("categoria: %s", rp.categoria);
			printf("codigo: %s", rp.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
			printf("quantidade: %d\n", rp.quantidade);
			printf("custo: %.2f\n", rp.custo);
			printf("valor: %.2f\n", rp.valor);
			printf("------------------------------------\n");
		}
		
   }fclose(estoque);
   getch();
}

void pesquisarRoupas(){
	
	FILE *estoque;
	roupas rp;
	char nome[30];
	
	cabecalho();
	estoque = fopen("Roupas.txt","rb");
		if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		fflush(stdin);
		printf("insira o nome da roupa que deseja pesquisar:");
		fgets(nome,30,stdin);
		
		while(fread(&rp, sizeof(roupas),1,estoque) == 1){
			if (strcmp(nome,rp.nome)==0){
			printf("\n");

			printf("-----------------ITEM---------------\n");
			printf("nome: %s", rp.nome);
			printf("categoria: %s", rp.categoria);
			printf("codigo: %s", rp.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
			printf("quantidade: %d\n", rp.quantidade);
			printf("custo: %.2f\n", rp.custo);
			printf("valor: %.2f\n", rp.valor);
			printf("------------------------------------\n");

			}
		}
		if(strcmp(nome,rp.nome)!=0){
		    printf("nome nao encontrado\n");
     	}
	}
	fclose(estoque);
	getch();
}

void pesquisarCategoria(){
			
	FILE *estoque;
	roupas rp;
	char ctg[30];
	
	cabecalho();
	estoque = fopen("Roupas.txt","rb");
		if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		fflush(stdin);
		printf("insira a categoria que deseja pesquisar:");
		fgets(ctg,30,stdin);
		
		while(fread(&rp, sizeof(roupas),1,estoque) == 1){
			if (strcmp(ctg,rp.categoria)==0){
			printf("\n");

			printf("-----------------ITEM---------------\n");
			printf("nome: %s", rp.nome);
			printf("categoria: %s", rp.categoria);
			printf("codigo: %s", rp.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
			printf("quantidade: %d\n", rp.quantidade);
			printf("custo: %.2f\n", rp.custo);
			printf("valor: %.2f\n", rp.valor);
			printf("------------------------------------\n");

			}
		}
	  	if(strcmp(ctg,rp.categoria)!=0){
	       	printf("categoria nao encontrada");
		}
	}
	fclose(estoque);
	getch();
}

void buscarCodigo(){
	FILE *estoque;
	roupas rp;
	char id[10];
	
	cabecalho();
	estoque = fopen("Roupas.txt","rb");
		if (estoque == NULL){
		printf("problemas na abertura do arquivo");
	}
	else {
		fflush(stdin);
		printf("insira o codigo da roupa que deseja buscar:");
		fgets(id,10,stdin);
		
		while(fread(&rp, sizeof(roupas),1,estoque) == 1){
			if (strcmp(id,rp.codigo)==0){
			printf("\n");

			printf("-----------------ITEM---------------\n");
			printf("nome: %s", rp.nome);
			printf("categoria: %s", rp.categoria);
			printf("codigo: %s", rp.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
			printf("quantidade: %d\n", rp.quantidade);
			printf("custo: %.2f\n", rp.custo);
			printf("valor: %.2f\n", rp.valor);
			printf("------------------------------------\n");

			}
		}
		if(strcmp(id,rp.codigo)!= 0){
	     	printf("codigo nao encontrado");
			 }
	}
	fclose(estoque);
	getch();
}

void editar_dados()
{
	FILE* estoque;
    FILE* tempR;
    roupas rp;
    char id[10];

	estoque = fopen("Roupas.txt","rb");
	tempR = fopen("tempR.txt","wb");

    if(estoque == NULL && tempR == NULL)
    {
	    printf("Não foi possível abrir o arquivo\n");
	    getch();
    }
    else
    {
    	system("cls");
    	cabecalho();
    	fflush(stdin);
    	printf("Digite o codigo da roupa que pretende editar: ");
    	fgets(id,10,stdin);

    	while(fread(&rp, sizeof(roupas), 1, estoque) == 1)
    	{
        	if(strcmp(id, rp.codigo) == 0)
        	{
	           
			printf("-----------------ITEM---------------\n");
			printf("nome: %s", rp.nome);
			printf("categoria: %s", rp.categoria);
			printf("codigo: %s", rp.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
			printf("quantidade: %d\n", rp.quantidade);
			printf("custo: %.2f\n", rp.custo);
			printf("valor: %.2f\n", rp.valor);
			printf("------------------------------------\n");
        	}
	        else
	        {
	            fwrite(&rp, sizeof(roupas), 1, tempR);
	        }
	    }
	}
        fclose(estoque);
        fclose(tempR);
        fflush(stdin);
        
        printf("Tem a certeza que pretende alterar os dados da roupa? (s/n)\n");
	  	if(getche() == 's')
	    {
	        if(remove("Roupas.txt") == 0 && rename ("tempR.txt", "Roupas.txt") == 0)
	            {
	            	FILE* estoque;
					roupas rp;
					
					estoque = fopen("Roupas.txt", "ab");
	                printf("\ndigite o novo nome da peça: ");
		         	fgets(rp.nome,30,stdin);
			
		        	fflush(stdin);
		        	printf("insira a nova categoria: ");
		        	fgets(rp.categoria,30,stdin);

		         	fflush(stdin);
		        	printf("insira o novo codigo: ");
		        	fgets(rp.codigo,10,stdin);

		        	printf("insira a data de aquisiçao (dd mm aaaa): ");
		        	scanf("%d%d%d", &rp.aquisicao.dia, &rp.aquisicao.mes, &rp.aquisicao.ano);

		        	printf("insira a nova quantidade: ");
		        	scanf("%d", &rp.quantidade);

		         	printf("insira o novo custo: ");
		        	scanf("%f", &rp.custo);

		        	printf("insira o novo valor: ");
		         	scanf("%f", &rp.valor);
		        	printf("------------------------------------\n");
					fwrite(&rp, sizeof(roupas), 1, estoque);
					
					printf("\n\nRoupa alterada com sucesso!\n");
	            }
	        else
	            {
	                remove("tempR.txt");
	            }
	    }
	    fclose(tempR);
	    fclose(estoque);
	    getch();
 	}
 	
void excluirItem(){
 FILE* estoque;
 FILE* temp;
 
 roupas rp;
 char id[10];
 
 estoque = fopen("Roupas.txt","rb");//abrir em modo rb leitura binaria
 temp = fopen("tempR.txt","wb");//abrir em modo wb ele limpa e grava binario
 
 if(estoque==NULL && temp==NULL){
  printf("Problemas na abertura do arquivo!\n");
  getch();
 }
 else{
  cabecalho();
  fflush(stdin);
  printf("Digite o codigo da roupa a deletar: ");
  fgets(id,10,stdin);
  
  while(fread(&rp,sizeof(roupas),1,estoque)==1){
   if(strcmp(id,rp.codigo)==0){
    
    		printf("-----------------ITEM---------------\n");
			printf("nome: %s", rp.nome);
			printf("categoria: %s", rp.categoria);
			printf("codigo: %s", rp.codigo);
			printf("data de aquisiçao: %d/%d/%d\n",rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
			printf("quantidade: %d\n", rp.quantidade);
			printf("custo: %.2f\n", rp.custo);
			printf("valor: %.2f\n", rp.valor);
			printf("------------------------------------\n");
    
   }
   else{
    fwrite(&rp,sizeof(roupas),1,temp);//gravando os dados no arquivo temp
   }
  }
  fclose(estoque);//fechar o estoque
  fclose(temp);//fechar o temp
  fflush(stdin);
  
  printf("Deseja deletar (s/n)? ");
  if(getche()=='s'){
   //vamos remover o arquivo "Roupas.txt" e renomear o arquivo "tempR.txt" para "Roupas.txt"
   if(remove("Roupas.txt")==0 && rename ("tempR.txt","Roupas.txt")==0){//verifica se as operacoes foram realizadas com sucesso!
    printf("\nOperacao realizada com sucesso!");
   }
   else{
    remove("tempR.txt");//remover o arquivo tempR se a condicao foi "n" na hora de deletar
   }
  }
  fclose(temp);
  fclose(estoque);
  getch();
 } 
}

void gerenciarCliente(){
	
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


		printf("\nSelecione a opçao desejada: ");

		scanf("%d", &op);

		switch(op){

      case 1:
      	inserirDadosCli();
      break;

      case 2:
      	excluirCliente();
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
          printf("opçao invalida!");
          getch();

		}

	}while(op !=8 );

}

void inserirDadosCli() {
	FILE *CLIENTE;
	CLIENTE = fopen("clientes.txt","ab");
	clientes Cli;
	
	do {
		
		fflush(stdin);
		printf("nome do cliente: ");
		fgets(Cli.nomeCli, 50, stdin);
		
		fflush(stdin);
		printf("CPF (000000000-00):");
		fgets(Cli.CPF,13,stdin);
		
		fflush(stdin);
		printf("codigo: ");
		fgets(Cli.codigoCli,5,stdin);
		
		fflush(stdin);
		printf("telefone: ");
		fgets(Cli.telefoneCli,15,stdin);
		
		fflush(stdin);
		printf("data de nascimento: ");
		scanf("%d %d %d", &Cli.nascimentoCli.dia, &Cli.nascimentoCli.mes, &Cli.nascimentoCli.ano);
		
		fflush(stdin);
		printf("endereço: ");
		fgets(Cli.enderecoCli,50,stdin);
		
		fwrite(&Cli, sizeof(clientes), 1, CLIENTE);
		
		printf("\ndeseja continuar (s/n)?\n");

	}while(getche() == 's');
	fclose(CLIENTE);
}

void excluirCliente(){
 FILE* CLIENTE;
 FILE* tempCli;
 
 clientes Cli;
 char cpf[13];
 
 CLIENTE = fopen("clientes.txt","rb");//abrir em modo rb leitura binaria
 tempCli = fopen("tempCli.txt","wb");//abrir em modo wb ele limpa e grava binario
 
 if(CLIENTE==NULL && tempCli==NULL){
  printf("Problemas na abertura do arquivo!\n");
  getch();
 }
 else{
  cabecalho();
  fflush(stdin);
  printf("Digite o CPF do cliente que deseja remover: ");
  fgets(cpf,13,stdin);
  
  while(fread(&Cli,sizeof(roupas),1,CLIENTE)==1){
   if(strcmp(cpf,Cli.CPF)==0){
    
    		printf("-----------------CLIENTE---------------\n");
			printf("nome: %s\n", Cli.nomeCli);
			printf("CPF: %s\n",Cli.CPF);
			printf("codigo: %s\n",Cli.codigoCli );
			printf("telefone: %s\n",Cli.telefoneCli );
			printf("data de nascimento: %d/%d/%d\n",Cli.nascimentoCli.dia,Cli.nascimentoCli.mes,Cli.nascimentoCli.ano);
			printf("endereço: %s \n",Cli.enderecoCli);
			printf("------------------------------------\n");
    
   }
   else{
    fwrite(&Cli,sizeof(clientes),1,tempCli);
   }
  }
  fclose(CLIENTE);
  fclose(tempCli);
  fflush(stdin);
  
  printf("Deseja deletar o/a cliente (s/n)? ");
  if(getche()=='s'){
   if(remove("clientes.txt") == 0 && rename ("tempCli.txt","clientes.txt")==0)
   {
    printf("\nOperacao realizada com sucesso!");
   }
   else{
    remove("tempCli.txt");
   }
  }
  fclose(tempCli);
  fclose(CLIENTE);
  getch();
 } 
	
}




