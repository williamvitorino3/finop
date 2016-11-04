#include <stdlib.h>

/**
  * Autor = William Vitorino.
**/

void readCliente(FILE *file, struct Clientes *lista)
{
  /**
    * Lê os clientes do arquivo e armasena na lista passada por parâmetro.
  **/
  struct Cliente *cliente = malloc(sizeof(struct Cliente));   // Estrutura de cada cliente.

  char linha[10001];    // Linha do arquivo.

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
  while(fscanf(file, "%d, %[A-z ], %[^,], %[^,], %[^,], %[^;];", &cliente->id, cliente->nome, cliente->cpf, cliente->telefone, cliente->municipio, cliente->estado) == 6)
  {
    //printf("%d, %s, %s, %s, %s, %s;\n", cliente->id, cliente->nome, cliente->cpf, cliente->telefone, cliente->municipio, cliente->estado);
    append_cliente(lista, cliente);
    cliente = malloc(sizeof(struct Cliente));
  }
  //free(cliente);  // Se eu limpar isso vai sair da lista também...
}

void readConta(FILE *file, struct Contas *contas)
{
  struct Conta *conta = malloc(sizeof(struct Conta));   // Estrutura de cada conta.
  char linha[10001];    // Linha do arquivo.

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
    insert_conta(contas, conta);
    conta = malloc(sizeof(struct Conta));
    //printf("%d, %d, %d, %d;\n", conta->id, conta->numero_conta, conta->variacao, conta->id_cliente);
  }
}
/*
void readOperacoes(FILE *file, struct Operacao *lista)
{
  struct Operacao *operacao = malloc(sizeof(struct Operacao));
  char linha[10001];
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
    insert_operacao(lista, operacao);
    printf("%d, %s;\n", operacao->id, operacao->nome);
  }
}
*/
void readTransacao(FILE *file, struct Transacoes *lista)
{
  /**
    * Preenche a lista de operações de acordo com os dados do arquivo.
  **/
  struct Transacao *transacao = malloc(sizeof(struct Transacao));
  char linha[10001];
  /// Procura o cabeçalho das Transacoes.
  do
  {
    if(feof(file))
    {
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*transacoes*"));

  /// Lê as transações e as adiciona na lista.
  while (fscanf(file, "%[^,], %d, %d, %d, %lf;\n", transacao->data, &transacao->id_operacao, &transacao->id_conta_origem, &transacao->id_conta_destino, &transacao->valor) == 5)
  {
    //printf("%s, %d, %d, %d, %.2lf;\n", transacao->data, transacao->id_operacao, transacao->id_conta_origem, transacao->id_conta_destino, transacao->valor);
    insert_transacao(lista, transacao);
    transacao = malloc(sizeof(struct Transacao));
  }
}

void readTransacoes_cartao_credito(FILE *file, struct Transacoes_cartao_credito *lista)
{
  /**
    * Preenche a lista de tranzações de cartão de crédito de acordo com os dados do arquivo.
  **/
  struct Transacao_cartao_credito *divida = malloc(sizeof(struct Transacao_cartao_credito));
  char linha[10001];
  do
  {
  if(feof(file))
  {
    file = fopen("arquivo.txt", "r");
  }
    fscanf(file, "%s\n", linha);
  }while(strcmp(linha, "*transacoes_cartao_credito*"));
  while (fscanf(file, "%[^,], %d, %[^,], %d, %lf;\n", divida->data_compra, &divida->id_conta, divida->descricao, &divida->qtde_parcelas, &divida->valor) == 5)
  {
    insert_Transacoes_cartao_credito(lista, divida);
    //printf("%s, %d, %s, %d, %lf;\n", divida->data_compra, divida->id_conta, divida->descricao, divida->qtde_parcelas, divida->valor);
  }
}
