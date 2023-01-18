#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

typedef struct {
  int dia;
  int mes;
  int ano;
}
data;
typedef struct {
  char categoria[30];
  char codigo[10];
  data aquisicao;
  int quantidade;
  float custo;
  float valor;
  char nome[30];
}
roupas;
typedef struct {
  char nomeCli[50];
  char codigoCli[8];
  char CPF[15];
  char telefoneCli[15];
  char enderecoCli[50];
  data nascimentoCli;
}
clientes;
typedef struct {
  char nome[50];
  char codigo[5];
  char telefone[15];
  char Empresa[30];
  char email[30];
  char CNPJ[20];
}
fornecedor;

typedef struct {
  char codVenda[6];
  int quantV;
  float valorT;
  clientes cod;
  roupas code;
}
venda;

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
void ListarClientes();
void editar_dadosCli();
void pesquisarCliente();
void pesquisarCodigo();
void buscarCPF();

//fun?oes referente ao fornecedor
void gerenciarFornecedor();
void cadastrarFornecedor();
void listarFornecedores();

// funcoes referentes a vendas
void gerenciarVendas();
void cadastrarVendas();
void listarVendas();

int main() {
  setlocale(LC_ALL, "Portuguese");

  int opc;
  do {
    cabecalho();
    printf("1 - gerenciar roupas\n");
    printf("2 - gerenciar cliente\n");
    printf("3 - gerenciar fornecedor\n");
    printf("4 - cadastrar vendas\n");
    printf("5 - Sair\n");

    printf("\ndigite a op?ao desejada: \n");
    scanf("%d", & opc);

    switch (opc) {

    case 1:
      GerenciarRoupas();
      break;
    case 2:
      gerenciarCliente();
      break;
    case 3:
      gerenciarFornecedor();
      break;
    case 4:
      gerenciarVendas();
      break;
    case 5:
      printf("ate logo!!");
      getch();
      break;
    default:
      printf("opçao invalida!");
      getch();
    }

  } while (opc != 5);

  return 0;
}

void cabecalho() {
  system("cls");
  printf("-------------------------------------------\n");
  printf("ADMINISTRAÇAO DA LOJA\n");
  printf("-------------------------------------------\n\n");

}

void GerenciarRoupas() {
  int op;

  do {
    system("cls");
    printf("-------------------ROUPAS-------------------\n");
    printf("1.Cadastrar uma nova peça roupa\n");
    printf("2.Remover uma peça do estoque\n");
    printf("3.Atualizar informa?ao da peça \n");
    printf("4.Pesquisar por nome\n");
    printf("5.Pesquisar por categoria\n");
    printf("6.Pesquisar por codigo\n");
    printf("7.Listar peças de roupas disponiveis\n");
    printf("8.Sair\n");
    printf("-------------------------------------------\n");

    printf("\nescolha uma op?ao: ");
    scanf("%d", & op);

    switch (op) {

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

  } while (op != 8);
}

void inserirDados() {
  FILE * estoque;
  estoque = fopen("Roupas.txt", "ab");

  roupas rp;

  if (estoque == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    cabecalho();
    do {
      fflush(stdin);
      printf("\n");
      printf("digite o nome da pe?a: ");
      fgets(rp.nome, 30, stdin);

      fflush(stdin);
      printf("insira a categoria: ");
      fgets(rp.categoria, 30, stdin);

      fflush(stdin);
      printf("insira o codigo: ");
      fgets(rp.codigo, 10, stdin);

      printf("insira a data de aquisiçao (dd mm aaaa): ");
      scanf("%d%d%d", & rp.aquisicao.dia, & rp.aquisicao.mes, & rp.aquisicao.ano);

      printf("insira a quantidade: ");
      scanf("%d", & rp.quantidade);

      printf("insira o custo: ");
      scanf("%f", & rp.custo);

      printf("insira o valor: ");
      scanf("%f", & rp.valor);
      printf("------------------------------------\n");

      printf("peça cadastrada com sucesso!");

      getch();

      fwrite( & rp, sizeof(roupas), 1, estoque);

      printf("\ndeseja continuar (s/n)?\n");

    } while (getche() == 's');
    fclose(estoque);
  }
}

void listarEstoque() {

  FILE * estoque;
  estoque = fopen("Roupas.txt", "rb");
  roupas rp;

  cabecalho();
  if (estoque == NULL) {
    printf("problemas na abertura do arquivo");
  } else {

    while (fread( & rp, sizeof(roupas), 1, estoque) == 1) {
      printf("------------------------------------\n");
      printf("nome: %s", rp.nome);
      printf("categoria: %s", rp.categoria);
      printf("codigo: %s", rp.codigo);
      printf("data de aquisiçao: %d/%d/%d\n", rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
      printf("quantidade: %d\n", rp.quantidade);
      printf("custo: %.2f\n", rp.custo);
      printf("valor: %.2f\n", rp.valor);
      printf("------------------------------------\n");
    }

  }
  fclose(estoque);
  getch();
}

void pesquisarRoupas() {

  FILE * estoque;
  roupas rp;
  char nome[30];

  cabecalho();
  estoque = fopen("Roupas.txt", "rb");
  if (estoque == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    fflush(stdin);
    printf("insira o nome da roupa que deseja pesquisar:");
    fgets(nome, 30, stdin);

    while (fread( & rp, sizeof(roupas), 1, estoque) == 1) {
      if (strcmp(nome, rp.nome) == 0) {
        printf("\n");

        printf("-----------------ITEM---------------\n");
        printf("nome: %s", rp.nome);
        printf("categoria: %s", rp.categoria);
        printf("codigo: %s", rp.codigo);
        printf("data de aquisiçao: %d/%d/%d\n", rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
        printf("quantidade: %d\n", rp.quantidade);
        printf("custo: %.2f\n", rp.custo);
        printf("valor: %.2f\n", rp.valor);
        printf("------------------------------------\n");

      }
    }
    if (strcmp(nome, rp.nome) != 0) {
      printf("nome nao encontrado\n");
    }
  }
  fclose(estoque);
  getch();
}

void pesquisarCategoria() {

  FILE * estoque;
  roupas rp;
  char ctg[30];

  cabecalho();
  estoque = fopen("Roupas.txt", "rb");
  if (estoque == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    fflush(stdin);
    printf("insira a categoria que deseja pesquisar:");
    fgets(ctg, 30, stdin);

    while (fread( & rp, sizeof(roupas), 1, estoque) == 1) {
      if (strcmp(ctg, rp.categoria) == 0) {
        printf("\n");

        printf("-----------------ITEM---------------\n");
        printf("nome: %s", rp.nome);
        printf("categoria: %s", rp.categoria);
        printf("codigo: %s", rp.codigo);
        printf("data de aquisiçao: %d/%d/%d\n", rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
        printf("quantidade: %d\n", rp.quantidade);
        printf("custo: %.2f\n", rp.custo);
        printf("valor: %.2f\n", rp.valor);
        printf("------------------------------------\n");

      }
    }
    if (strcmp(ctg, rp.categoria) != 0) {
      printf("categoria nao encontrada");
    }
  }
  fclose(estoque);
  getch();
}

void buscarCodigo() {
  FILE * estoque;
  roupas rp;
  char id[10];

  cabecalho();
  estoque = fopen("Roupas.txt", "rb");
  if (estoque == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    fflush(stdin);
    printf("insira o codigo da roupa que deseja buscar:");
    fgets(id, 10, stdin);

    while (fread( & rp, sizeof(roupas), 1, estoque) == 1) {
      if (strcmp(id, rp.codigo) == 0) {
        printf("\n");

        printf("-----------------ITEM---------------\n");
        printf("nome: %s", rp.nome);
        printf("categoria: %s", rp.categoria);
        printf("codigo: %s", rp.codigo);
        printf("data de aquisiçao: %d/%d/%d\n", rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
        printf("quantidade: %d\n", rp.quantidade);
        printf("custo: %.2f\n", rp.custo);
        printf("valor: %.2f\n", rp.valor);
        printf("------------------------------------\n");

      }
    }
    if (strcmp(id, rp.codigo) != 0) {
      printf("codigo nao encontrado");
    }
  }
  fclose(estoque);
  getch();
}

void editar_dados() {
  FILE * estoque;
  FILE * tempR;
  roupas rp;
  char id[10];

  estoque = fopen("Roupas.txt", "rb");
  tempR = fopen("tempR.txt", "wb");

  if (estoque == NULL && tempR == NULL) {
    printf("Nao foi possivel abrir o arquivo\n");
    getch();
  } else {
    system("cls");
    cabecalho();
    fflush(stdin);
    printf("Digite o codigo da roupa que pretende editar: ");
    fgets(id, 10, stdin);

    while (fread( & rp, sizeof(roupas), 1, estoque) == 1) {
      if (strcmp(id, rp.codigo) == 0) {

        printf("-----------------ITEM---------------\n");
        printf("nome: %s", rp.nome);
        printf("categoria: %s", rp.categoria);
        printf("codigo: %s", rp.codigo);
        printf("data de aquisi?ao: %d/%d/%d\n", rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
        printf("quantidade: %d\n", rp.quantidade);
        printf("custo: %.2f\n", rp.custo);
        printf("valor: %.2f\n", rp.valor);
        printf("------------------------------------\n");
      } else {
        fwrite( & rp, sizeof(roupas), 1, tempR);
      }
    }
  }
  fclose(estoque);
  fclose(tempR);
  fflush(stdin);

  printf("Tem a certeza que pretende alterar os dados da roupa? (s/n)\n");
  if (getche() == 's') {
    if (remove("Roupas.txt") == 0 && rename("tempR.txt", "Roupas.txt") == 0) {
      FILE * estoque;
      roupas rp;

      estoque = fopen("Roupas.txt", "ab");
      printf("\ndigite o novo nome da pe?a: ");
      fgets(rp.nome, 30, stdin);

      fflush(stdin);
      printf("insira a nova categoria: ");
      fgets(rp.categoria, 30, stdin);

      fflush(stdin);
      printf("insira o novo codigo: ");
      fgets(rp.codigo, 10, stdin);

      printf("insira a data de aquisi?ao (dd mm aaaa): ");
      scanf("%d%d%d", & rp.aquisicao.dia, & rp.aquisicao.mes, & rp.aquisicao.ano);

      printf("insira a nova quantidade: ");
      scanf("%d", & rp.quantidade);

      printf("insira o novo custo: ");
      scanf("%f", & rp.custo);

      printf("insira o novo valor: ");
      scanf("%f", & rp.valor);
      printf("------------------------------------\n");
      fwrite( & rp, sizeof(roupas), 1, estoque);

      printf("\n\nRoupa alterada com sucesso!\n");
    } else {
      remove("tempR.txt");
    }
  }
  fclose(tempR);
  fclose(estoque);
  getch();
}

void excluirItem() {
  FILE * estoque;
  FILE * temp;

  roupas rp;
  char id[10];

  estoque = fopen("Roupas.txt", "rb"); //abrir em modo rb leitura binaria
  temp = fopen("tempR.txt", "wb"); //abrir em modo wb ele limpa e grava binario

  if (estoque == NULL && temp == NULL) {
    printf("Problemas na abertura do arquivo!\n");
    getch();
  } else {
    cabecalho();
    fflush(stdin);
    printf("Digite o codigo da roupa a deletar: ");
    fgets(id, 10, stdin);

    while (fread( & rp, sizeof(roupas), 1, estoque) == 1) {
      if (strcmp(id, rp.codigo) == 0) {

        printf("-----------------ITEM---------------\n");
        printf("nome: %s", rp.nome);
        printf("categoria: %s", rp.categoria);
        printf("codigo: %s", rp.codigo);
        printf("data de aquisiçao: %d/%d/%d\n", rp.aquisicao.dia, rp.aquisicao.mes, rp.aquisicao.ano);
        printf("quantidade: %d\n", rp.quantidade);
        printf("custo: %.2f\n", rp.custo);
        printf("valor: %.2f\n", rp.valor);
        printf("------------------------------------\n");

      } else {
        fwrite( & rp, sizeof(roupas), 1, temp); //gravando os dados no arquivo temp
      }
    }
    fclose(estoque); //fechar o estoque
    fclose(temp); //fechar o temp
    fflush(stdin);

    printf("Deseja deletar (s/n)? ");
    if (getche() == 's') {
      //vamos remover o arquivo "Roupas.txt" e renomear o arquivo "tempR.txt" para "Roupas.txt"
      if (remove("Roupas.txt") == 0 && rename("tempR.txt", "Roupas.txt") == 0) { //verifica se as operacoes foram realizadas com sucesso!
        printf("\nOperacao realizada com sucesso!");
      } else {
        remove("tempR.txt"); //remover o arquivo tempR se a condicao foi "n" na hora de deletar
      }
    }
    fclose(temp);
    fclose(estoque);
    getch();
  }
}

void gerenciarCliente() {

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

    printf("\nSelecione a op?ao desejada: ");
    scanf("%d", & op);

    switch (op) {

    case 1:
      inserirDadosCli();
      break;
    case 2:
      excluirCliente();
      break;
    case 3:
      editar_dadosCli();
      break;
    case 4:
      pesquisarCliente();
      break;
    case 5:
      pesquisarCodigo();
      break;
    case 6:
      buscarCPF();
      break;
    case 7:
      ListarClientes();
      break;

    case 8:
      printf("ate mais!");
      getch();
      break;

    default:
      printf("op?ao invalida!");
      getch();

    }

  } while (op != 8);
}

void inserirDadosCli() {
  FILE * CLIENTE;
  CLIENTE = fopen("clientes.txt", "ab");
  clientes Cli;

  do {

    fflush(stdin);
    printf("nome do cliente: ");
    fgets(Cli.nomeCli, 50, stdin);

    fflush(stdin);
    printf("CPF (000.000.000-00):");
    fgets(Cli.CPF, 15, stdin);

    fflush(stdin);
    printf("codigo: ");
    fgets(Cli.codigoCli, 8, stdin);

    fflush(stdin);
    printf("telefone: ");
    fgets(Cli.telefoneCli, 15, stdin);

    fflush(stdin);
    printf("data de nascimento: ");
    scanf("%d %d %d", & Cli.nascimentoCli.dia, & Cli.nascimentoCli.mes, & Cli.nascimentoCli.ano);

    fflush(stdin);
    printf("endere?o: ");
    fgets(Cli.enderecoCli, 50, stdin);

    fwrite( & Cli, sizeof(clientes), 1, CLIENTE);

    printf("\ndeseja continuar (s/n)?\n");

  } while (getche() == 's');
  fclose(CLIENTE);
}

void excluirCliente() {
  FILE * CLIENTE;
  FILE * temp;

  clientes Cli;
  char id[8];

  CLIENTE = fopen("clientes.txt", "rb");
  temp = fopen("tempcli.txt", "wb");

  if (CLIENTE == NULL && temp == NULL) {
    printf("Problemas na abertura do arquivo!\n");
    getch();
  } else {
    cabecalho();
    fflush(stdin);
    printf("Digite o codigo do cliente que deseja remover: ");
    fgets(id, 8, stdin);

    while (fread( & Cli, sizeof(clientes), 1, CLIENTE) == 1) {
      if (strcmp(id, Cli.codigoCli) == 0) {

        printf("---------------CLIENTE-------------\n");
        printf("nome:%s\n", Cli.nomeCli);
        printf("CPF:%s\n", Cli.CPF);
        printf("codigo:%s\n", Cli.codigoCli);
        printf("data de nascimento:%d/%d/%d\n", Cli.nascimentoCli.dia, Cli.nascimentoCli.mes, Cli.nascimentoCli.ano);
        printf("telefone: %s", Cli.telefoneCli);
        printf("endereço: %s\n", Cli.enderecoCli);
        printf("------------------------------------\n");

      } else {
        fwrite( & Cli, sizeof(clientes), 1, temp);
      }
    }
    fclose(CLIENTE);
    fclose(temp);
    fflush(stdin);

    printf("Deseja remover (s/n)? ");
    if (getche() == 's') {

      if (remove("clientes.txt") == 0 && rename("tempcli.txt", "clientes.txt") == 0) { //verifica se as operacoes foram realizadas com sucesso!
        printf("\nOperacao realizada com sucesso!");
      } else {
        remove("tempcli.txt");
      }
    }
    fclose(temp);
    fclose(CLIENTE);
    getch();
  }
}

void ListarClientes() {
  FILE * CLIENTE;
  CLIENTE = fopen("clientes.txt", "rb");

  clientes Cli;

  cabecalho();
  if (CLIENTE == NULL) {
    printf("problemas na abertura do arquivo");
  } else {

    while (fread( & Cli, sizeof(clientes), 1, CLIENTE) == 1) {
      printf("------------------------------------\n");
      printf("nome:%s\n", Cli.nomeCli);
      printf("CPF:%s\n", Cli.CPF);
      printf("codigo:%s\n", Cli.codigoCli);
      printf("data de nascimento:%d/%d/%d\n", Cli.nascimentoCli.dia, Cli.nascimentoCli.mes, Cli.nascimentoCli.ano);
      printf("telefone: %s", Cli.telefoneCli);
      printf("endereço: %s\n", Cli.enderecoCli);
      printf("------------------------------------\n");
    }

  }
  fclose(CLIENTE);
  getch();
}

void editar_dadosCli() {
  FILE * CLIENTE;
  FILE * tempcli;
  clientes Cli;
  char id[8];

  CLIENTE = fopen("clientes.txt", "rb");
  tempcli = fopen("tempclientes.txt", "wb");

  if (CLIENTE == NULL && tempcli == NULL) {
    printf("Nao foi possivel abrir o arquivo\n");
    getch();
  } else {
    system("cls");
    cabecalho();
    fflush(stdin);
    printf("Digite o codigo do cliente que pretende editar: ");
    fgets(id, 10, stdin);

    while (fread( & Cli, sizeof(clientes), 1, CLIENTE) == 1) {
      if (strcmp(id, Cli.codigoCli) == 0) {

        printf("---------------CLIENTE-------------\n");
        printf("nome:%s\n", Cli.nomeCli);
        printf("CPF:%s\n", Cli.CPF);
        printf("codigo:%s\n", Cli.codigoCli);
        printf("data de nascimento:%d/%d/%d\n", Cli.nascimentoCli.dia, Cli.nascimentoCli.mes, Cli.nascimentoCli.ano);
        printf("telefone: %s", Cli.telefoneCli);
        printf("endereço: %s\n", Cli.enderecoCli);
        printf("------------------------------------\n");
      } else {
        fwrite( & Cli, sizeof(clientes), 1, tempcli);
      }
    }
  }
  fclose(CLIENTE);
  fclose(tempcli);
  fflush(stdin);

  printf("Tem a certeza que pretende alterar os dados do cliente? (s/n)\n");
  if (getche() == 's') {
    if (remove("clientes.txt") == 0 && rename("tempclientes.txt", "clientes.txt") == 0) {
      FILE * CLIENTE;
      clientes Cli;

      CLIENTE = fopen("clientes.txt", "ab");

      fflush(stdin);
      printf("nome do cliente: ");
      fgets(Cli.nomeCli, 50, stdin);

      fflush(stdin);
      printf("CPF (000.000.000-00):");
      fgets(Cli.CPF, 15, stdin);

      fflush(stdin);
      printf("codigo: ");
      fgets(Cli.codigoCli, 8, stdin);

      fflush(stdin);
      printf("telefone: ");
      fgets(Cli.telefoneCli, 15, stdin);

      fflush(stdin);
      printf("data de nascimento: ");
      scanf("%d %d %d", & Cli.nascimentoCli.dia, & Cli.nascimentoCli.mes, & Cli.nascimentoCli.ano);

      fflush(stdin);
      printf("endereço: ");
      fgets(Cli.enderecoCli, 50, stdin);
      printf("------------------------------------\n");
      fwrite( & Cli, sizeof(clientes), 1, CLIENTE);

      printf("\n Dados alterados com sucesso!\n");
    } else {
      remove("tempclientes.txt");
    }
  }
  fclose(tempcli);
  fclose(CLIENTE);
  getch();
}

void pesquisarCliente() {
  FILE * CLIENTE;
  clientes Cli;
  char nome[50];

  cabecalho();
  CLIENTE = fopen("clientes.txt", "rb");
  if (CLIENTE == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    fflush(stdin);
    printf("insira o nome do cliente que deseja pesquisar:");
    fgets(nome, 50, stdin);

    while (fread( & Cli, sizeof(clientes), 1, CLIENTE) == 1) {
      if (strcmp(nome, Cli.nomeCli) == 0) {
        printf("\n");
        printf("---------------CLIENTE-------------\n");
        printf("nome:%s\n", Cli.nomeCli);
        printf("CPF:%s\n", Cli.CPF);
        printf("codigo:%s\n", Cli.codigoCli);
        printf("data de nascimento:%d/%d/%d\n", Cli.nascimentoCli.dia, Cli.nascimentoCli.mes, Cli.nascimentoCli.ano);
        printf("telefone: %s", Cli.telefoneCli);
        printf("endere?o: %s\n", Cli.enderecoCli);
        printf("------------------------------------\n");

      }
    }
    if (strcmp(nome, Cli.nomeCli) != 0) {
      printf("nome nao encontrado\n");
    }
  }
  fclose(CLIENTE);
  getch();
}

void pesquisarCodigo() {
  FILE * CLIENTE;
  clientes Cli;
  char cod[50];

  cabecalho();
  CLIENTE = fopen("clientes.txt", "rb");
  if (CLIENTE == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    fflush(stdin);
    printf("insira o nome do cliente que deseja pesquisar:");
    fgets(cod, 8, stdin);

    while (fread( & Cli, sizeof(clientes), 1, CLIENTE) == 1) {
      if (strcmp(cod, Cli.codigoCli) == 0) {
        printf("\n");
        printf("---------------CLIENTE-------------\n");
        printf("nome:%s\n", Cli.nomeCli);
        printf("CPF:%s\n", Cli.CPF);
        printf("codigo:%s\n", Cli.codigoCli);
        printf("data de nascimento:%d/%d/%d\n", Cli.nascimentoCli.dia, Cli.nascimentoCli.mes, Cli.nascimentoCli.ano);
        printf("telefone: %s", Cli.telefoneCli);
        printf("endere?o: %s\n", Cli.enderecoCli);
        printf("------------------------------------\n");

      }
    }
    if (strcmp(cod, Cli.codigoCli) != 0) {
      printf("codigo nao encontrado\n");
    }
  }
  fclose(CLIENTE);
  getch();
}
void buscarCPF() {
  FILE * CLIENTE;
  clientes Cli;
  char cpf[15];

  cabecalho();
  CLIENTE = fopen("clientes.txt", "rb");
  if (CLIENTE == NULL) {
    printf("problemas na abertura do arquivo");
  } else {
    fflush(stdin);
    printf("insira o nome do cliente que deseja pesquisar:");
    fgets(cpf, 15, stdin);

    while (fread( & Cli, sizeof(clientes), 1, CLIENTE) == 1) {
      if (strcmp(cpf, Cli.CPF) == 0) {
        printf("\n");
        printf("---------------CLIENTE-------------\n");
        printf("nome:%s\n", Cli.nomeCli);
        printf("CPF:%s\n", Cli.CPF);
        printf("codigo:%s\n", Cli.codigoCli);
        printf("data de nascimento:%d/%d/%d\n", Cli.nascimentoCli.dia, Cli.nascimentoCli.mes, Cli.nascimentoCli.ano);
        printf("telefone: %s", Cli.telefoneCli);
        printf("endere?o: %s\n", Cli.enderecoCli);
        printf("------------------------------------\n");

      }
    }
    if (strcmp(cpf, Cli.CPF) != 0) {
      printf("CPF nao encontrado\n");
    }
  }
  fclose(CLIENTE);
  getch();
}

void gerenciarFornecedor() {

  int op;

  do {
    system("cls");
    printf("----------------FORNECEDOR-----------------\n");
    printf("1.Cadastrar fornecedor\n");
    printf("2.Listar fornecedor\n");
    printf("3.Sair\n");
    printf("-------------------------------------------\n");

    printf("\nescolha uma op?ao: ");
    scanf("%d", & op);

    switch (op) {

    case 1:
      cadastrarFornecedor();
      break;
    case 2:
      listarFornecedores();
      break;
    case 3:
      printf("até mais!!");
      getch();
      break;

    default:
      printf("opçao invalida!");
      getch();

    }

  } while (op != 3);
}
void cadastrarFornecedor() {
  FILE * fornecedores;
  fornecedor f[5];
  int i;

  fornecedores = fopen("fornecedorl.txt", "ab");

  if (fornecedores == NULL) {
    printf("erro na abertura do arquivo\n");
    getch();
  } else {
    cabecalho();
    printf("cadastrar 5 fornecedores\n\n ");
    for (i = 0; i < 5; i++) {

      printf("-------------------------------------------\n");
      fflush(stdin);
      printf("nome do fornecedor: ");
      fgets(f[i].nome, 50, stdin);

      fflush(stdin);
      printf("codigo: ");
      fgets(f[i].codigo, 5, stdin);

      fflush(stdin);
      printf("telefone:");
      fgets(f[i].telefone, 15, stdin);

      fflush(stdin);
      printf("empresa fornecedora: ");
      fgets(f[i].Empresa, 30, stdin);

      fflush(stdin);
      printf("e-mail da empresa : ");
      fgets(f[i].email, 30, stdin);

      fflush(stdin);
      printf("CNPJ da empresa: ");
      fgets(f[i].CNPJ, 20, stdin);
      printf("-------------------------------------------\n");

      fwrite( & f[i], sizeof(fornecedor), 1, fornecedores);

      printf("fornecedor cadastrado com sucesso");
    }

  }
  fclose(fornecedores);
}
void listarFornecedores() {
  FILE * fornecedores;
  fornecedor f[5];
  int i;
  fornecedores = fopen("fornecedorl.txt", "rb");
  if (fornecedores == NULL) {
    printf("erro na abertura do arquivo!");
    getch();
  } else {
    for (i = 0; i < 5; i++) {
      fread( & f[i], sizeof(fornecedor), 1, fornecedores);
      printf("-----------------FORNECEDOR--------------\n");
      printf("nome do fornecedor:%s\n", f[i].nome);
      printf("codigo:%s\n", f[i].codigo);
      printf("telefone:%s\n", f[i].telefone);
      printf("empresa:%s\n", f[i].Empresa);
      printf("email:%s\n", f[i].email);
      printf("CNPJ:%s\n", f[i].CNPJ);
      printf("-------------------------------------------\n");
    }
  }
  fclose(fornecedores);
  getch();
}

void gerenciarVendas() {
  int op;

  do {
    system("cls");
    cabecalho();
    printf("----------------VENDAS-----------------\n");
    printf("1.Cadastrar venda\n");
    printf("2.Listar vendas\n");
    printf("3.Sair\n");
    printf("-------------------------------------------\n");

    printf("\nescolha uma opçao: ");
    scanf("%d", & op);

    switch (op) {

    case 1:
      cadastrarVendas();
      break;
    case 2:
      listarVendas();
      break;
    case 3:
      printf("até mais!!");
      getch();
      break;

    default:
      printf("opçao invalida!");
      getch();

    }

  } while (op != 3);
}

void cadastrarVendas() {

  FILE * vendas;
  venda venda;
  vendas = fopen("vendas.txt", "ab");

  if (vendas == NULL) {
    printf("erro na abertura do arquivo");
    getch();
  } else {

    do {

      fflush(stdin);
      printf("insira o codigo da venda:");
      fgets(venda.codVenda, 6, stdin);

      fflush(stdin);
      printf("insira a quantidade: ");
      scanf("%d", & venda.quantV);

      fflush(stdin);
      printf("insira o codigo do cliente:");
      fgets(venda.cod.codigoCli, 8, stdin);

      fflush(stdin);
      printf("insira o codigo do produto: ");
      fgets(venda.code.codigo, 10, stdin);

      fflush(stdin);
      printf("valor total da venda: ");
      scanf("%f", & venda.valorT);

      fwrite( & venda, sizeof(venda), 1, vendas);

      printf("deseja continuar? (s/n)\n");
    } while (getche() == 's');
    fclose(vendas);
  }
}
void listarVendas() {
  FILE * vendas;
  vendas = fopen("vendas.txt", "rb");
  venda venda;

  cabecalho();
  if (vendas == NULL) {
    printf("problemas na abertura do arquivo");
  } else {

    while (fread( & venda, sizeof(venda), 1, vendas) == 1) {
      printf("----------------VENDA---------------\n");
      printf("codigo da venda: %s\n", venda.codVenda);
      printf("quantidade: %d\n", venda.quantV);
      printf("codigo do cliente: %s", venda.cod.codigoCli);
      printf("codigo da roupa: %s", venda.code.codigo);
      printf("valor total: %.2f\n", venda.valorT);
      printf("------------------------------------\n");
    }
  }
  fclose(vendas);
  getch();
}
