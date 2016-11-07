#include <stdlib.h>

struct Transacao
{
  int id_operacao, id_conta_origem, id_conta_destino;
  char data[101];
  double valor;
};

struct Transacoes
{
  struct Transacao *transacao;
  struct Transacoes *next;
};

void insert_transacao(struct Transacoes *cabeca, struct Transacao *e)
{
  /*
   * Inserção Transacoes inicio.
   */

  struct Transacoes *new = malloc(sizeof(struct Transacoes));
  new->transacao = e;

  new->next = cabeca->next;
  cabeca->next = new;
}

void append_transacao(struct Transacoes *cabeca, struct Transacao *e)
{

  /*
   * Inserção Transacoes fim.
   */

  struct Transacoes *aux = cabeca;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  struct Transacoes *ultimo = malloc(sizeof(struct Transacoes));
  ultimo->transacao = e;
  ultimo->next = NULL;

  aux->next = ultimo;
}

void append_sorted_transacao(struct Transacoes *cabeca, struct Transacao *e)
{

  /*
   * Inserção Transacoes fim.
   */

  struct Transacoes *aux = cabeca;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  struct Transacoes *ultimo = malloc(sizeof(struct Transacoes));
  ultimo->transacao = e;
  ultimo->next = NULL;

  aux->next = ultimo;
}

double getSaldo(struct Transacoes *cabeca, int id_conta)
{
  double saldo = 0.0;
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    if(aux->transacao->id_conta_origem == id_conta)
    {
      saldo -= aux->transacao->valor;
    }else if(aux->transacao->id_conta_destino == id_conta)
    {
      saldo += aux->transacao->valor;
    }
    /*
    saldo += ( (aux->transacao->id_conta_origem == id_conta) ? (aux->transacao->valor*(-1)) :
    ( (aux->transacao->id_conta_destino) ? aux->transacao->valor : 0 ) );
    */
  }
  return saldo;
}

void print_transacao(struct Transacao *transacao)
{
    printf("|\t%s\t|\t%s\t|\t %.2lf\t\t|\n", transacao->data, (transacao->id_operacao == 1 ? "saque\t" : (transacao->id_operacao == 2 ? "depósito" : "tranferência")), transacao->valor);
}

void print_transacoes(struct Transacoes *cabeca)
{
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    print_transacao(aux->transacao);
  }
}
