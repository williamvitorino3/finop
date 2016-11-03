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
/*
void append_sorted_operacao(struct Operacao *cabeca, struct Operacao *e)
{
  /*
   * Inserção ordenada.
   *//*

  struct Operacoes *aux = cabeca;
  while (aux->next != NULL && aux->next->operacao->id <= e->id)
  {
    aux = aux->next;
  }

  struct Operacao *Operacao = malloc(sizeof(struct Operacoes));
  Operacao->operacao = e;
  Operacao->next = aux->next;
  aux->next = Operacao;
}*/

int find_operacao(struct Operacoes *cabeca, struct Operacao *e)
{
  struct Operacoes *aux;
  for(aux = cabeca->next; aux != NULL; aux = aux->next)
    if(aux->operacao->id == e->id)
      return 1;
  return 0;
}
