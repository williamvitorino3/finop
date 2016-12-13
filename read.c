/**
  * Autor = William Vitorino.
**/


/// Guarda a animação do carregamento da leitura.
char status[] = {'\\', '/'};

/// Guarda a posição da amimação à ser mostrada.
int pos = 0;

void lendo(char str[])
{
  char quebra[] = "                                   ";
  printf("\rLendo %s %c %d %s", str, status[(pos%2)], ++pos, quebra);
  fflush(stdout);
}

void readCliente(FILE *file, struct Clientes *lista)
{
  /**
    * Lê os clientes do arquivo e armasena na lista passada por parâmetro.
  **/
  struct Cliente *cliente = malloc(sizeof(struct Cliente));   // Estrutura de cada cliente.

  char linha[10001];    // Linha do arquivo.
  pos = 0;
  /* Procura o cabeçalho referênta à cliente. */
  do
  {
    if(feof(file))
    {
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*cliente*"));

  /* Lê os clientes do arquivo e os adiciona na lista. */
  while(fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^;];", &cliente->id, cliente->nome, cliente->cpf, cliente->telefone, cliente->municipio, cliente->estado) == 6)
  {
    lendo("Clientes");
    //printf("%d, %s, %s, %s, %s, %s;\n", cliente->id, cliente->nome, cliente->cpf, cliente->telefone, cliente->municipio, cliente->estado);
    append_cliente(lista, cliente);
    cliente = malloc(sizeof(struct Cliente));
  }
  printf("\n");
}

void readConta(FILE *file, struct Contas *contas)
{
  struct Conta *conta = malloc(sizeof(struct Conta));   // Estrutura de cada conta.
  char linha[10001];    // Linha do arquivo.
  pos = 0;
  /* Procura o cabeçalho referênta à cliente. */
  do
  {
    if(feof(file))
    {
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*conta*"));

  /* Lê as contass do arquivo e as adiciona na lista. */
  while(fscanf(file, "%d, %d, %d, %d;", &conta->id, &conta->numero_conta, &conta->variacao, &conta->id_cliente) == 4)
  {
    lendo("Contas");
    insert_conta(contas, conta);
    //printf("%d, %d, %d, %d;\n", conta->id, conta->numero_conta, conta->variacao, conta->id_cliente);
    conta = malloc(sizeof(struct Conta));
  }
  printf("\n");
}

void readOperacoes(FILE *file, struct Operacoes *lista)
{
  struct Operacao *operacao = malloc(sizeof(struct Operacao));
  char linha[10001];
  pos = 0;
  do
  {
    if(feof(file))
    {
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*operacao*"));

  while (fscanf(file, "%d, %[^;];", &operacao->id, operacao->nome) == 2)
  {
    lendo("Operações");
    insert_operacao(lista, operacao);
    //printf("%d, %s;\n", operacao->id, operacao->nome);
    operacao = malloc(sizeof(struct Operacao));
  }
  printf("\n");
}

void readTransacao(FILE *file, struct Transacoes *lista)
{
  /**
    * Preenche a lista de operações de acordo com os dados do arquivo.
  **/
  struct Transacao *transacao = malloc(sizeof(struct Transacao));
  char linha[10001];
  pos = 0;
  /// Procura o cabeçalho das Transacoes.
  do
  {
    // Se acabar o arquivo.
    if(feof(file))
    {
      fclose(file);
      // Reabre o arquivo.
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*transacoes*"));
  // Lê as transações e as adiciona na lista.
  while (fscanf(file, "%d/%d/%d, %d, %d, %d, %lf;\n", &transacao->data.tm_mday, &transacao->data.tm_mon, &transacao->data.tm_year, &transacao->id_operacao, &transacao->id_conta_origem, &transacao->id_conta_destino, &transacao->valor) == 7)
  {
    lendo("Transações");
    //printf("%d/%d/%d, %d, %d, %d, %.2lf;\n", transacao->data.tm_mday, transacao->data.tm_mon, transacao->data.tm_year, transacao->id_operacao, transacao->id_conta_origem, transacao->id_conta_destino, transacao->valor);

    /// Insere as transações no início da lista.
    insert_transacao(lista, transacao);
    //append_sorted_transacao(lista, transacao);

    /// Muda a referência da struct de leitura.
    transacao = malloc(sizeof(struct Transacao));
  }
  printf("\n");
}

void readTransacoes_cartao_credito(FILE *file, struct Transacoes_cartao_credito *lista)
{
  /**
    * Preenche a lista de tranzações de cartão de crédito de acordo com os dados do arquivo.
  **/
  struct Transacao_cartao_credito *divida = malloc(sizeof(struct Transacao_cartao_credito));
  char linha[10001];
  pos = 0;
  do
  {
    if(feof(file))
    {
        file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*transacoes_cartao_credito*"));

  while (fscanf(file, "%d/%d/%d, %d, %[^,], %d, %lf;\n", &divida->data_compra.tm_mday, &divida->data_compra.tm_mon, &divida->data_compra.tm_year, &divida->id_conta, divida->descricao, &divida->qtde_parcelas, &divida->valor) == 7)
  {
    lendo("Transações de Cartão de Crédito");
    insert_Transacoes_cartao_credito(lista, divida);
    //printf("%s, %d, %s, %d, %lf;\n", divida->data_compra, divida->id_conta, divida->descricao, divida->qtde_parcelas, divida->valor);
    divida = malloc(sizeof(struct Transacao_cartao_credito));
  }
  printf("\n");
}
