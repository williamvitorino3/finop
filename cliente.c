struct Cliente
{
  int id;
  char nome[1001], cpf[15], telefone[21], municipio[101], estado[3];
};

struct Clientes
{
  struct Cliente *cliente;
  struct Clientes *next;
};

void insert_cliente(struct Clientes *cabeca, struct Cliente *e)
{
  /**
    * Inserção Clientes inicio.
   **/

  struct Clientes *new = malloc(sizeof(struct Clientes));
  new->cliente = e;

  new->next = cabeca->next;
  cabeca->next = new;
}

void append_cliente(struct Clientes *cabeca, struct Cliente *e)
{

  /*
   * Inserção Clientes fim.
   */

  struct Clientes *aux = cabeca;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  struct Clientes *ultimo = malloc(sizeof(struct Clientes));
  ultimo->cliente = e;

  aux->next = ultimo;
}

void append_sorted_cliente(struct Clientes *cabeca, struct Cliente *e)
{
  /*
   * Inserção ordenada.
   */

  struct Clientes *aux = cabeca;
  while (aux->next != NULL && aux->next->cliente->id <= e->id)
  {
    aux = aux->next;
  }

  struct Clientes *Clientesvo = malloc(sizeof(struct Clientes));
  Clientesvo->cliente = e;
  Clientesvo->next = aux->next;
  aux->next = Clientesvo;
}

int find_cliente(struct Clientes *cabeca, int id)
{
  struct Clientes *aux;
  for(aux = cabeca->next; aux != NULL; aux = aux->next)
    if(aux->cliente->id == id)
      return 1;
  return 0;
}

struct Cliente *getCliente(struct Clientes *lista, int id)
{
  for(struct Clientes *aux = lista->next; aux != NULL; aux = aux->next)
    if (aux->cliente->id == id)
      return aux->cliente;
}

void print_cliente(struct Clientes *cabeca)
{
  for(struct Clientes *aux = cabeca->next; aux != NULL; printf("%s | %s\n", aux->cliente->nome, aux->cliente->estado), aux = aux->next);
}
