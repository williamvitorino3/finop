/**
  * Autor = William Vitorino.
**/

long long int dias(struct tm data)
{
  long long int tempo = (data.tm_year * 365) + ((data.tm_mon-1) * 30) + data.tm_mday;
  return tempo;
}

struct Transacao
{
  int id_operacao, id_conta_origem, id_conta_destino;
  struct tm data;
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
   * Inserção de Transacoes ordenada por data.
   */

  struct Transacoes *aux = cabeca;
  for(; aux->next != NULL; aux = aux->next)
  {
    if (dias(aux->next->transacao->data) >= dias(e->data))
      break;
  }
  struct Transacoes *ultimo = malloc(sizeof(struct Transacoes));
  ultimo->transacao = e;
  ultimo->next = aux->next;

  aux->next = ultimo;
}

double getSaldo(struct Transacoes *cabeca, int id_conta)
{
  /**
    * Calcula o saldo acumulado das transações referêntes à conta.
  **/

  /* Variável que guarda o saldo acumulado. */
  double saldo = 0.0;
  /* Percorre a lista de Transações. */
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /* Verifica se a conta corresponde à conta origem da transação. */
    if(aux->transacao->id_conta_origem == id_conta)
    {
      /* Subtrai o valor do saldo acumulado. */
      saldo -= aux->transacao->valor;
    }
      /* Verifica se a conta corresponde à conta destino da transação. */
      else if(aux->transacao->id_conta_destino == id_conta)
    {
      /* Soma o valor do saldo acumulado. */
      saldo += aux->transacao->valor;
    }
  }

  /* Retorna o saldo acumulado. */
  return saldo;
}

double getSaldoMensal(struct Transacoes *cabeca, int id_conta, int mes, int ano)
{
  /**
    * Calcula o saldo acumulado das transações referêntes à conta.
  **/

  /* Variável que guarda o saldo acumulado. */
  double saldo = 0.0;

  /* Percorre a lista de Transações. */
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /* Verifica se o més corresponde ao passado por paramentro. */
    if (aux->transacao->data.tm_mon == mes)
    {
      /* Verifica se a conta corresponde à conta origem da transação. */
      if(aux->transacao->id_conta_origem == id_conta)
      {
        /* Subtrai o valor do saldo acumulado. */
        saldo -= aux->transacao->valor;
      }
        /* Verifica se a conta corresponde à conta destino da transação. */
        else if(aux->transacao->id_conta_destino == id_conta)
      {
        /* Soma o valor do saldo acumulado. */
        saldo += aux->transacao->valor;
      }
    }
  }

  /* Retorna o saldo acumulado. */
  return saldo;
}

double getSaldoMesAnterior(struct Transacoes *cabeca, int id_conta, struct tm *data_limite)
{
  /**
    * Calcula o saldo acumulado das transações referêntes à conta.
  **/

  /* Variável que guarda o saldo acumulado. */
  double saldo = 0.0;

  /* Percorre a lista de Transações. */
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /* Verifica se o mês é menor ou igual ao passado por paramentro. && aux->transacao->data.tm_year <= data_limite->tm_year*/
    if ((aux->transacao->data.tm_mon+(aux->transacao->data.tm_year-1)*12) < (data_limite->tm_mon+(data_limite->tm_year-1)*12))
    {
      /* Verifica se a conta corresponde à conta origem da transação. */
      if(aux->transacao->id_conta_origem == id_conta)
      {
        /* Subtrai o valor do saldo acumulado. */
        saldo -= aux->transacao->valor;
      }
        /* Verifica se a conta corresponde à conta destino da transação. */
        else if(aux->transacao->id_conta_destino == id_conta)
      {
        /* Soma o valor do saldo acumulado. */
        saldo += aux->transacao->valor;
      }
    }
  }

  /* Retorna o saldo acumulado. */
  return saldo;
}

void print_transacao(struct Transacao *transacao, struct Operacoes *operacoes)
{
  /**
    * Mostra os detalhes de uma transação.
  **/
  printf("|\t%d/%d/%d\t|\t%15s\t\t|\t%+5.2lf\t\t|\n", transacao->data.tm_mday, transacao->data.tm_mon, transacao->data.tm_year, getOperacao(operacoes, transacao->id_operacao)->nome, transacao->valor);
}

void print_transacoes(struct Transacoes *cabeca, struct Operacoes *operacoes)
{
  /**
    * Percorre a lista de transações e
    * mostra os detalhes de cada transação.
  **/

  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    print_transacao(aux->transacao, operacoes);
  }
}

void garbageColector(struct Transacoes *lista)
{
  // Percorre a lista inteira.
  while (lista->next != NULL)
  {
    // Salva a refeência do próximo nó da lista.
    struct Transacoes *prox = lista->next;
    // Limpa o nó atual;
    free(lista);
    // Passa para o próximo nó da lista.
    lista = prox;
  }
}
