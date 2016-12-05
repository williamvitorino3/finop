/**
  * Autor = William Vitorino.
**/

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

int find_cliente(struct Clientes *cabeca, char cpf[], int echo)
{
  for(struct Clientes *aux = cabeca->next; aux != NULL; aux = aux->next)
    if(!strcmp(aux->cliente->cpf, cpf))
    {
      return 1;
    }
  if(echo)
    printf("CPF Inexistente.\n");
  return 0;
}

struct Cliente *getCliente(struct Clientes *lista, char *cpf)
{
  for(struct Clientes *aux = lista->next; aux != NULL; aux = aux->next)
  {
    if(!strcmp(aux->cliente->cpf, cpf))
      return aux->cliente;
    }
  return malloc(sizeof(struct Cliente));
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
  return (find_cliente(clientes, cpf, 1) ? getCliente(clientes, cpf) : inputCliente(clientes));
}
