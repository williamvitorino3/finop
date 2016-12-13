/**
  * Autor = William Vitorino.
**/

struct Transacao_cartao_credito
{
  int id_conta, qtde_parcelas;
  char descricao[10001];
  double valor;
  struct tm data_compra;
};


struct Transacoes_cartao_credito
{
  struct Transacao_cartao_credito *transacao_cartao_credito;
  struct Transacoes_cartao_credito *next;
};

void insert_Transacoes_cartao_credito(struct Transacoes_cartao_credito *cabeca, struct Transacao_cartao_credito *e)
{
  /*
   * Inserção no inicio.
   */

  struct Transacoes_cartao_credito *new = malloc(sizeof(struct Transacoes_cartao_credito));
  new->transacao_cartao_credito = e;

  new->next = cabeca->next;
  cabeca->next = new;
}

int len_Transacoes_cartao_credito(struct Transacoes_cartao_credito *cabeca)
{
  int len = 0;

  for(struct Transacoes_cartao_credito *aux = cabeca; aux->next != NULL; len++, aux = aux->next);

  return len;
}

void append_Transacoes_cartao_credito(struct Transacoes_cartao_credito *cabeca, struct Transacao_cartao_credito *e)
{

  /*
   * Inserção no fim.
   */

  struct Transacoes_cartao_credito *aux = cabeca;

  for(;aux->next != NULL; aux = aux->next)
  {
    if(dias(aux->next->transacao_cartao_credito->data_compra) >= dias(e->data_compra))
    {
      break;
    }
  }
  struct Transacoes_cartao_credito *ultimo = malloc(sizeof(struct Transacoes_cartao_credito));
  ultimo->transacao_cartao_credito = e;
  ultimo->next = aux->next;
  aux->next = ultimo;
}

int parcelaAtual(struct Transacao_cartao_credito *transacao, struct tm *dataAtual)
{
  /**
    * Calcula a parcela em que a dívida se encontra.
  **/

  /// Subitrai a data da compra da data atual e retorna a quantidade de meses.
  int meses = (dataAtual->tm_mon + dataAtual->tm_year*12) -
              (transacao->data_compra.tm_mon + transacao->data_compra.tm_year*12);

  return meses;
}

int parcelasRestantes(struct Transacao_cartao_credito *transacao, struct tm *dataAtual)
{
  /**
    * Calcula a quantidade de parcelas que faltam para quitar a dívida.
  **/

  /*
  Subitrai a quantidade de messes da data atual, menos o mês referênta à compra,
  da quantidade de meses da data da última parcela.
  */
  int parcelas = (transacao->data_compra.tm_year*12 + transacao->data_compra.tm_mon
                + transacao->qtde_parcelas) - (dataAtual->tm_year*12 + dataAtual->tm_mon-1);
  return parcelas;
}

void print_Transacao_cartao_credito(FILE *out, struct Transacao_cartao_credito *cartao, struct tm *dataCliente)
{
  /**
    * Mostra no formato especificado a transação de cartão de crédito recebida.
  **/

  fprintf(out, "|   %2d/%2d/%4d   | %24s\t%3d / %2d | R$ %+10.2lf |\n", cartao->data_compra.tm_mday, cartao->data_compra.tm_mon, cartao->data_compra.tm_year, cartao->descricao, parcelaAtual(cartao, dataCliente), cartao->qtde_parcelas, (cartao->valor/cartao->qtde_parcelas));
}

void print_Transacoes_cartao_credito(FILE *out, struct Transacoes_cartao_credito *cabeca, struct tm *dataCliente)
{
  /**
    * Mostra todas as transações de cartão de crédito da lista recebida.
  **/

  fprintf(out, "|----------------|-----------------------------------|---------------|\n");
  for(struct Transacoes_cartao_credito *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    print_Transacao_cartao_credito(out, aux->transacao_cartao_credito, dataCliente);
  }
  fprintf(out, "|----------------|-----------------------------------|---------------|\n");
}

double valorFatura(struct Transacao_cartao_credito *conta)
{
  /**
    * Calcula o valor restante da transação de cartão de crédito à ser pago.
  **/

  return conta->valor/conta->qtde_parcelas;
}
