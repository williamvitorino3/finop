struct Conta
{
  int id, numero_conta, variacao, id_cliente;
};

struct Contas
{
  struct Conta *conta;
  struct Contas *next;
};

void insert_conta(struct Contas *cabeca, struct Conta *e)
{
  /*
   * Inserção Contas inicio.
   */

  struct Contas *new = malloc(sizeof(struct Contas));
  new->conta = e;

  new->next = cabeca->next;
  cabeca->next = new;
}

void append_conta(struct Contas *cabeca, struct Conta *e)
{

  /*
   * Inserção Contas fim.
   */

  struct Contas *aux = cabeca;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  struct Contas *ultimo = malloc(sizeof(struct Contas));
  ultimo->conta = e;

  aux->next = ultimo;
}

void append_sorted_conta(struct Contas *cabeca, struct Conta *e)
{
  /*
   * Inserção ordenada.
   */

  struct Contas *aux = cabeca;
  while (aux->next != NULL && aux->next->conta->id <= e->id)
  {
    aux = aux->next;
  }

  struct Contas *Contasvo = malloc(sizeof(struct Contas));
  Contasvo->conta = e;
  Contasvo->next = aux->next;
  aux->next = Contasvo;
}

int find_conta(struct Contas *cabeca, int numero_conta)
{
  /**
    * Verifica se uma conta realmente existe.
  **/
  struct Contas *aux;
  for(aux = cabeca->next; aux != NULL; aux = aux->next)
    if(aux->conta->numero_conta == numero_conta)
      return 1;
  printf("Conta inesistente...\n");
  return 0;
}

struct Conta *getConta(struct Contas *lista, int numero_conta)
{
  printf("Numero da Conta: %d\n", numero_conta);
  for(struct Contas *aux = lista->next; aux != NULL; aux = aux->next)
  {
    if(aux->conta->numero_conta == numero_conta)
      return aux->conta;
    }
  return malloc(sizeof(struct Conta));
}

void print_conta(struct Conta *conta)
{
  /**
    * Mostra informações de uma conta.
  **/
  printf("|\t%d\t|\t%d\t|", conta->numero_conta, conta->variacao);
}

void print_contas(struct Contas *cabeca)
{
  /**
    * Mostra informacoes de todas as contas.
  **/
  for(struct Contas *aux = cabeca->next; aux != NULL; print_conta(aux->conta), aux = aux->next);
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
