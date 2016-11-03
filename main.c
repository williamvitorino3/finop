#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"
#include "read.c"


int getOpcao()
{
  /**
    * Representação de menu principal. Pega o valor referênte à opção desejada
    * e retorna;
  **/
  int op;
  printf("Escolha uma opção:\n1 - Listar clientes por estado.\n2 - Saldo atual do cliente.\n3 - Listar saldo dos cliente\n0 - Sair\n>>> ");
  scanf("%d", &op);
  return (op >= 0 && op<= 3 ? op : getOpcao());
}

int qtdContas(struct Contas *cabeca, int id_cliente)
{
  /**
    * Retorna a quentidade de contas referêntes à um determinado cliente.
  **/
  int qtd = 0;

  struct Contas *aux = cabeca->next;

  while (aux != NULL)
  {
    if (aux->conta->id_cliente == id_cliente)
    {
      qtd++;
    }
    aux = aux->next;
  }
  return qtd;
}

void filtroEstado(struct Clientes *clientes, struct Contas *contas, char *estado)
{
  /**
    * Representa a listagem dos clientes por estado.
  **/
  printf("|---------------|-----------------------|-----------------------|-----------------------|---------------|---------------|\n");
  for(struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    if (strcmp(aux->cliente->estado, estado) == 0)
    {
      /* id do cliente, nome, CPF, telefone, município e quantedade de contas */
      printf("|\t%d\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\t%d\t|\n", aux->cliente->id, aux->cliente->nome, aux->cliente->cpf, aux->cliente->telefone, aux->cliente->municipio, qtdContas(contas, aux->cliente->id));
    }
  }
  printf("|---------------|-----------------------|-----------------------|-----------------------|---------------|---------------|\n");
}

void getEstado(struct Clientes *clientes, struct Contas *contas)
{
  /**
    * Pega o estado do cliente e manda para o filtro de clientes por estado.
  **/
  char estado[3];
  printf("Digite a sigla do estado:\n>>> ");
  scanf("%s", estado);
  filtroEstado(clientes, contas, estado);
}

double getSaldoTotal(struct Contas *cabeca, struct Transacoes *transacoes, int id_cliente)
{
  /**
    * Calcula o saldo total do cliente.
  **/


  double saldo = 0;

  for(struct Contas *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    if (aux->conta->id_cliente == id_cliente)
    {
      saldo += getSaldo(transacoes, aux->conta->id);
    }
  }
  return saldo;
}

void print_saldo(struct Contas *cabeca, struct Transacoes *transacoes, struct Clientes *clientes, int id_cliente)
{
  /**
    * Representa a listagem do saldo atual do cliente em cada conta.
  **/
  struct Contas *aux = cabeca->next;
  double saldo = 0;
  printf("|-------------------------------------------------------|\n");
  printf("\t%s\t\t\tR$ %.2lf\t\t\n", getCliente(clientes, id_cliente)->nome, getSaldoTotal(cabeca, transacoes, id_cliente));
  printf("|-------------------------------------------------------|\n");

  while (aux != NULL)
  {
    if (aux->conta->id_cliente == id_cliente)
    {
      print_conta(aux->conta);
      printf("\tR$ %.2lf\t|\n", getSaldo(transacoes, aux->conta->id));
    }
    aux = aux->next;
  }
  printf("|-------------------------------------------------------|\n");
}

int inputCliente(struct Clientes *clientes)
{
  /**
    * Recebe do usuário o numero de um ciente.
  **/
  int id;
  printf("Digite o numero do cliente:\n>>> ");
  scanf("%d", &id);
  return (find_cliente(clientes, id) ? id : inputCliente(clientes));
}

void listarSaldoCLientes(struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Representa a listagem de todos os clientes com o saldo de cada cliente.
  **/
  printf("|-------------------------------|-----------------------|\n");
  for (struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    printf("|\t%s\t\t|\tR$ %.3lf\t|\n", aux->cliente->nome, getSaldoTotal(contas, transacoes, aux->cliente->id));
  }
  printf("|-------------------------------|-----------------------|\n");
}

int main()
{
  /**
    * Abertura do arquivo.
  **/
  FILE *file = fopen("arquivo.txt", "r");

  /* Estruturas para armazenar os dados do arquivo. */
  struct Clientes *clientes = malloc(sizeof(struct Clientes));
  struct Contas *contas = malloc(sizeof(struct Contas));
  struct Operacoes *operacoes = malloc(sizeof(struct Operacoes));
  struct Transacoes *transacoes = malloc(sizeof(struct Transacoes));
  struct Transacoes_cartao_credito *tranzacoes_cartao = malloc(sizeof(struct Transacoes_cartao_credito));

  printf("Lendo arquivo, por favor aguarde...\n");
  /* Lê as estruturas do arquivo. */
  readTransacao(file, transacoes);
  readConta(file, contas);
  readCliente(file, clientes);
  readTransacoes_cartao_credito(file, tranzacoes_cartao);

  /* Laço proncipal do projeto. */
  while (1)
  {
    switch (getOpcao()) {
      case 1:
        getEstado(clientes, contas);
        break;
      case 2:
        print_saldo(contas, transacoes, clientes, inputCliente(clientes));
        break;
      case 3:
        listarSaldoCLientes(clientes, contas, transacoes);
        break;
      default:
        fclose(file);
        printf("Vllw... Fllw...\n");
        return 0;
    }
  }
  return 0;
}
