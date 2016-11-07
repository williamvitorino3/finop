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
  printf("Escolha uma opção:\n1 - Listar clientes por estado.\n2 - Saldo atual do cliente.\n3 - Listar saldo dos cliente\n4 - Extrato mês atual\n0 - Sair\n>>> ");
  scanf("%d", &op);
  return (op >= 0 && op<= 4 ? op : getOpcao());
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

void print_saldo(struct Contas *cabeca, struct Transacoes *transacoes, struct Cliente *cliente)
{
  /**
    * Representa a listagem do saldo atual do cliente em cada conta.
  **/
  struct Contas *aux = cabeca->next;
  double saldo = 0;
  printf("|-------------------------------------------------------|\n");
  printf("\t%s\t\t\tR$ %.2lf \t\t\n", cliente->nome, getSaldoTotal(cabeca, transacoes, cliente->id));
  printf("|-------------------------------------------------------|\n");

  while (aux != NULL)
  {
    if (aux->conta->id_cliente == cliente->id)
    {
      print_conta(aux->conta);
      printf("\tR$ %.2lf\t|\n", getSaldo(transacoes, aux->conta->id));
    }
    aux = aux->next;
  }
  printf("|-------------------------------------------------------|\n");
}

struct Cliente *inputCliente(struct Clientes *clientes)
{
  /**
    * Recebe do usuário o numero de um ciente.
  **/
  char cpf[15];
  setbuf(stdin, NULL);
  printf("Digite o CPF do cliente:\n>>> ");
  scanf("%s", cpf);
  setbuf(stdin, NULL);
  return (find_cliente(clientes, cpf) ? getCliente(clientes, cpf) : inputCliente(clientes));
}

void listarSaldoCLientes(struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Representa a listagem de todos os clientes com o saldo de cada cliente.
  **/
  printf("|-------------------------------|-------------------------------|-----------------------|\n");
  for (struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    printf("|\t%s\t\t|\t%s\t\t|\tR$ %.2lf \t|\n", aux->cliente->nome, aux->cliente->cpf, getSaldoTotal(contas, transacoes, aux->cliente->id));
  }
  printf("|-------------------------------|-------------------------------|-----------------------|\n");
}

int inputConta(struct Contas *contas)
{
  /**
    * Recebe do usuário o numero de um ciente.
  **/
  int numero_conta;
  setbuf(stdin, NULL);
  printf("Digite o número da conta:\n>>> ");
  scanf("%d", &numero_conta);
  setbuf(stdin, NULL);
  return (find_conta(contas, numero_conta) ? numero_conta : inputConta(contas));
}

void print_extrato_atual(struct Cliente *cliente, struct Contas *contas, int numero_conta, struct Transacoes *transacoes, struct Transacoes_cartao_credito *tranzacoes_cartao)
{
  /**
    * Representa a listagem das transações realizadas pelo cliente no mês atual.
  **/
  for(struct Contas *aux = contas->next; aux != NULL; aux = aux->next)    // Percorre a lista de contas.
  {
    if(aux->conta->numero_conta == numero_conta && cliente->id == aux->conta->id_cliente)    // Verifica o numero da conta.
    {
      for(struct Transacoes *lista = transacoes->next; lista != NULL; lista = lista->next)    // Percorre a lista de transações.
      {
        if (lista->transacao->id_conta_origem == aux->conta->id || lista->transacao->id_conta_destino == aux->conta->id)  // Verifica se o id da conta bate com o id de origem ou de destino da transacao.
        {
          print_transacao(lista->transacao);
        }
      }/* Transações de cartão de crédito.
      for (struct Transacoes_cartao_credito *cartao = tranzacoes_cartao->next; cartao != NULL; cartao = cartao->next)
      {
        if (cartao->transacao_cartao_credito->id_conta == aux->conta->id)
        {
          print_Transacao_cartao_credito(cartao->transacao_cartao_credito);
        }
      }*/
    }
  }
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


  /* Laço proncipal do projeto.*/
  while (1)
  {
    switch (getOpcao())
    {
      case 1:
        getEstado(clientes, contas);
        break;
      case 2:
        print_saldo(contas, transacoes, inputCliente(clientes));
        break;
      case 3:
        listarSaldoCLientes(clientes, contas, transacoes);
        break;
      case 4:
        print_extrato_atual(inputCliente(clientes), contas, inputConta(contas), transacoes, tranzacoes_cartao);
        break;
      default:
        fclose(file);
        printf("Vllw... Fllw...\n");
        return 0;
    }
  }

  return 0;
}
