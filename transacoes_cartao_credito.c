struct Transacao_cartao_credito
{
  int id_conta, qtde_parcelas;
  char data_compra[101],descricao[10001];
  double valor;
};


struct Transacoes_cartao_credito
{
  struct Transacao_cartao_credito *transacoes_cartao_credito;
  struct Transacoes_cartao_credito *next;
};

void insert_Transacoes_cartao_credito(struct Transacoes_cartao_credito *cabeca, struct Transacao_cartao_credito *e)
{
  /*
   * Inserção no inicio.
   */

  struct Transacoes_cartao_credito *new = malloc(sizeof(struct Transacoes_cartao_credito));
  new->transacoes_cartao_credito = e;

  new->next = cabeca->next;
  cabeca->next = new;
}

void append_Transacoes_cartao_credito(struct Transacoes_cartao_credito *cabeca, struct Transacao_cartao_credito *e)
{

  /*
   * Inserção no fim.
   */

  struct Transacoes_cartao_credito *aux = cabeca;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  struct Transacoes_cartao_credito *ultimo = malloc(sizeof(struct Transacoes_cartao_credito));
  ultimo->transacoes_cartao_credito = e;

  aux->next = ultimo;
}

void print_Transacoes_cartao_credito(struct Transacoes_cartao_credito *cabeca)
{
  for(struct Transacoes_cartao_credito *aux = cabeca->next; aux != NULL; printf("%s\n", aux->transacoes_cartao_credito->descricao), aux = aux->next);
}
