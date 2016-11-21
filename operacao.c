struct Operacao {
  int id;
  char nome[101];
};

struct Operacoes
{
  struct Operacao *operacao;
  struct Operacoes *next;
};

void insert_operacao(struct Operacoes *cabeca, struct Operacao *e)
{
  /*
   * Inserção Operacoes inicio.
   */

  struct Operacoes *new = malloc(sizeof(struct Operacoes));
  new->operacao = e;

  new->next = cabeca->next;
  cabeca->next = new;
}

void append_operacao(struct Operacoes *cabeca, struct Operacao *e)
{

  /*
   * Inserção Operacoes fim.
   */

  struct Operacoes *aux = cabeca;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  struct Operacoes *ultimo = malloc(sizeof(struct Operacoes));
  ultimo->operacao = e;

  aux->next = ultimo;
}

struct Operacao *getOperacaoInvalida()
{
  // Cria uma nova operação.
  struct Operacao *new = malloc(sizeof(struct Operacao));

  // Preenche com dados referêntes à operação inválida.
  new->id = -1;
  strcpy(new->nome, "Desconhecida");

  // Retorna a operação recem criada.
  return new;
}

struct Operacao *getOperacao(struct Operacoes *operacoes, int id_operacao)
{
  // Percorre a lista de operações.
  for(struct Operacoes *aux = operacoes->next; aux != NULL; aux = aux->next)
    // Verifica se a operação atual corresponde à operação desejada.
    if (aux->operacao->id == id_operacao)
      // Retorna a operação desejada.
      return aux->operacao;

  return getOperacaoInvalida();
}

int find_operacao(struct Operacoes *cabeca, struct Operacao *e)
{
  struct Operacoes *aux;
  for(aux = cabeca->next; aux != NULL; aux = aux->next)
    if(aux->operacao->id == e->id)
      return 1;
  return 0;
}
