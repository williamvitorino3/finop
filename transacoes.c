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

  aux->next = ultimo;
}

double getSaldo(struct Transacoes *cabeca, int id_conta)
{
  double saldo = 0.0;
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    saldo += ( (aux->transacao->id_conta_origem == id_conta) ? -aux->transacao->valor :
             ( (aux->transacao->id_conta_destino) ? aux->transacao->valor : 0 ) );
  }
  return saldo;
}

void print_transacao(struct Transacoes *cabeca)
{
  for(struct Transacoes *aux = cabeca->next; aux != NULL; printf("%d\n", aux->transacao->id_operacao), aux = aux->next);
}
