#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tempo.c"
#include "structs.c"
#include "read.c"

int getOpcao()
{
  /**
    * Representação de menu principal.
    * Pega o valor referênte à opção desejada e retorna.
  **/

  int op;
  printf("\nEscolha uma opção:\n[ 1 ] - Listar clientes por estado.\t[ 2 ] - Saldo atual do cliente.\n[ 3 ] - Listar saldo dos cliente\t[ 4 ] - Extrato mês atual\n[ 5 ] - Extrato mês anterior\t\t[ 6 ] - Fatura do cartão de crédito\n[ 0 ] - Sair\n>>> ");
  scanf("%d", &op);
  fflush(stdout);
  return (op >= 0 && op<= 6 ? op : getOpcao());
}

int qtdContas(struct Contas *cabeca, int id_cliente)
{
  /**
    * Retorna a quentidade de contas referêntes à um determinado cliente.
  **/

  /// Contador.
  int qtd = 0;

  /// Percorre a lista de contas.
  for(struct Contas *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /// Se a conta corresponder à conta desejada.
    if (aux->conta->id_cliente == id_cliente)
    {
      /// Incrementa o contador;
      qtd++;
    }
  }

  /// Retorna a quantidade de contas.
  return qtd;
}

void filtroEstado(FILE *file, struct Clientes *clientes, struct Contas *contas, char *estado)
{
  /**
    * Representa a listagem dos clientes por estado.
  **/
  char borda[] = "|---------------|---------------------------------------|-----------------------|-----------------------|-------------------------------|---------------|";
  fprintf(file, "%s\n", borda);
  fprintf(file, "|\tid\t|\t\tnome\t\t\t|\t%7s\t\t|\ttelefone\t|\t\tmunicípio\t|     contas\t|\n", "CPF");
  fprintf(file, "%s\n", borda);

  /// Percorre a lista de clientes
  for(struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    /// Se o estado corresponder ao desejado.
    if (strcmp(aux->cliente->estado, estado) == 0)
    {
      /// Mostra o cliente no formato pré definido.
      fprintf(file, "|\t%d\t|\t%30s\t|%20s\t|%20s\t|\t%19s\t|\t%d\t|\n", aux->cliente->id, aux->cliente->nome, aux->cliente->cpf, aux->cliente->telefone, aux->cliente->municipio, qtdContas(contas, aux->cliente->id));
    }
  }
  fprintf(file, "%s\n", borda);
}

void getEstado(FILE *file, struct Clientes *clientes, struct Contas *contas)
{
  /**
    * Pega o estado do cliente e manda para o filtro de clientes por estado.
  **/

  char estado[3];
  printf("Digite a sigla do estado:\n>>> ");
  scanf("%s", estado);

  /// Converte a string lida em maiúscula.
  estado[0] = toupper(estado[0]);
  estado[1] = toupper(estado[1]);

  filtroEstado(file, clientes, contas, estado);
}

double getSaldoTotalPorMes(struct Contas *cabeca, struct Transacoes *transacoes, int id_cliente, int mes_atual, int ano_atual)
{
  /**
    * Calcula o saldo total do cliente pelo mês atual.
  **/

  /// Variável que armazena o somatório do saldo das contas.
  double saldo = 0;

  /// Percorre a lista de contas.
  for(struct Contas *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /// Se a conta corresponder à conta desejada.
    if (aux->conta->id_cliente == id_cliente)
    {
      /// Adiciona o saldo da conta ao somatório do saldo das contas.
      saldo += getSaldoMensal(transacoes, aux->conta->id, mes_atual, ano_atual);
    }
  }

  /// Retorna o somatório do saldo das contas.
  return saldo;
}

double getSaldoTotalMesAnterior(struct Contas *contas, struct Transacoes *transacoes, int id_cliente, struct tm *data_limite)
{
  /**
    * Calcula o saldo total do cliente.
  **/

  /// Variável pra armasenar o somatório do saldo das contas.
  double saldo = 0;

  /// Percorre a lista de contas.
  for(struct Contas *aux = contas->next; aux != NULL; aux = aux->next)
  {
    /// Verifica se a conta atual corresponde com a conta desejada.
    if (aux->conta->id_cliente == id_cliente)
    {
      /// Soma o saldo das transações com data anterior ao mês atual.
      saldo += getSaldoMesAnterior(transacoes, aux->conta->id, data_limite);
    }
  }

  /// Retorna o somatório do saldo.
  return saldo;
}

double getSaldoTotal(struct Contas *cabeca, struct Transacoes *transacoes, int id_cliente)
{
  /**
    * Calcula o saldo total do cliente.
  **/

  /// Variável pra armasenar o somatório do saldo das contas.
  double saldo = 0;

  /// Percorre a lista de contas.
  for(struct Contas *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /// Verifica se a conta atual corresponde com a conta desejada.
    if (aux->conta->id_cliente == id_cliente)
    {
      /// Soma o saldo das transações com data referênta ao mês atual.
      saldo += getSaldo(transacoes, aux->conta->id);
    }
  }

  /// Retorna o somatório do saldo.
  return saldo;
}


void print_saldo(struct Contas *cabeca, struct Transacoes *transacoes, struct Cliente *cliente)
{
  /**
    * Representa a listagem do saldo atual do cliente em cada conta.
  **/

  /// Mostra o nome do cliente e o saldo total das contas.
  printf("|-------------------------------------------------------|\n");
  printf("\t%s\t\t\tR$ %+5.2lf \t\t\n", cliente->nome, getSaldoTotal(cabeca, transacoes, cliente->id));
  printf("|-------------------------------------------------------|\n");

  /// Percorre a lista de contas.
  for(struct Contas *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /// Verifica se a conta atual corresponde com a conta desejada.
    if (aux->conta->id_cliente == cliente->id)
    {
      /// Mostra a conta no formato padrão.
      print_conta(aux->conta);
      /// Mostra o saldo da conta atual.
      printf("\tR$ %+5.2lf\t|\n", getSaldo(transacoes, aux->conta->id));
    }
  }
  printf("|-------------------------------------------------------|\n");
}

void append_sorted_cliente(struct Contas *contas, struct Transacoes *transacoes, struct Clientes *clientes, struct Cliente *e)
{
  /**
    * Função especial para inserção ordenada de clientes a partir do saldo.
  **/

  if(find_cliente(clientes, e->cpf, 0))  /// Se o cliente já existir na lista.
  {
    return; /// Sai da função.
  }

  struct Clientes *aux = clientes;  /// Extrutura auxiliar para percorrer a lista de clientes.

  for(; aux->next != NULL; aux = aux->next) /// Percorre a lista de clientes.
  {
    /// Se o saldo do cliente atual for maio que o saldo do cliente a ser inserido.
    if (getSaldoTotal(contas, transacoes, aux->next->cliente->id) < getSaldoTotal(contas, transacoes, e->id))
    {
      /// Sai do laço.
      break;
    }
  }

  /// Cria um novo nó para a lista de clientes.
  struct Clientes *new = malloc(sizeof(struct Clientes));

  /// Adiciona o cliente recebido no nó recemcirado.
  new->cliente = e;

  /// Troca as referências.
  new->next = aux->next;
  aux->next = new;
}

void print_cliente(struct Cliente *cliente, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Mostra o cliente recebido no formato específico.
  **/

  printf("|%25s\t|\t%s\t\t|\tR$ %+.2lf \t|\n", cliente->nome, cliente->cpf, getSaldoTotal(contas, transacoes, cliente->id));
}

void print_clientes(struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Percorre a lista de clientes e mostra cada cliente.
  **/

  for(struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    print_cliente(aux->cliente, contas, transacoes);
  }
}

void listarSaldoCLientes(struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Representa a listagem de todos os clientes com o saldo de cada cliente.
  **/
  printf("Listando clientes.\n");
  struct Clientes *temp = malloc(sizeof(struct Clientes));
  temp->next = NULL;
  int len_clientes = length_cliente(clientes);
  printf("Total de Clientes: %d\n", len_clientes);

  char bordas[] = "|-------------------------------|-------------------------------|-----------------------|\n";

  /// Percorre a lista de clientes.
  for (struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    printf("\rCarregando %d -> %.2lf %%", length_cliente(temp), (100.0*length_cliente(temp))/len_clientes);
    fflush(stdout);
    append_sorted_cliente(contas, transacoes, temp, aux->cliente);
    ///printf("|\t%s\t\t|\t%s\t\t|\tR$ %.2lf \t|\n", aux->cliente->nome, aux->cliente->cpf, getSaldoTotal(contas, transacoes, aux->cliente->id));
  }

  /// Mostra os dados do cliente no formato especificado.
  printf("\n%s",bordas);
  print_clientes(temp, contas, transacoes);
  printf("%s",bordas);
}

struct Transacao *negative(struct Transacao *origem)
{
  /*
    * Reescreve a transação com o valor negativo.
  */

  /// Cria uma a transação de destino da cópia;
  struct Transacao *destino = malloc(sizeof(struct Transacao));

  /// Cópia os campos essenciais da transação horigem para a destino.
  destino->id_operacao = origem->id_operacao;
  destino->data = origem->data;
  destino->valor = origem->valor * -1;

  /// Retorna a transação recemcriada.
  return destino;
}

double saldo(struct Transacoes *cabeca)
{
  /**
    * Calcula o saldo acumulado das transações.
  **/

  /* Variável que guarda o saldo acumulado. */
  double saldo = 0.0;
  /* Percorre a lista de Transações. */
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
      /* Soma o valor do saldo acumulado. */
      saldo += aux->transacao->valor;
  }

  /* Retorna o saldo acumulado. */
  return saldo;
}

double saldoAterior(struct Transacoes *cabeca, struct tm *data)
{
  /**
    * Calcula o saldo acumulado das transações.
  **/

  /* Variável que guarda o saldo acumulado. */
  double saldo = 0.0;
  /* Percorre a lista de Transações. */
  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    if (((cabeca->transacao->data.tm_year-1)*12 + cabeca->transacao->data.tm_mon) > ((data->tm_year-1)*12 + data->tm_mon))
    {
      /* Soma o valor do saldo acumulado. */
      saldo += aux->transacao->valor;
    }
  }

  /* Retorna o saldo acumulado. */
  return saldo;
}

void print_extrato(struct Cliente *cliente, struct Contas *contas, int numero_conta, struct Transacoes *transacoes, struct Operacoes *operacoes, struct tm *dataAtual)
{
  /**
    * Representa a listagem das transações realizadas pelo cliente no mês atual.
  **/

  /// Borda da tabela à ser mostrada.
  char borda[] = "|-----------------------|-------------------------------|-----------------------|\n";

  /// Lista de transações auxiliar.
  struct Transacoes *new = malloc(sizeof(struct Transacoes));
  new->next = NULL;   /// Essa linha é M-U-I-T-O importante!!!

  /// Percorre a lista de contas.
  for(struct Contas *aux = contas->next; aux != NULL; aux = aux->next)
  {
    /// Verifica o numero da conta.
    if(aux->conta->numero_conta == numero_conta && cliente->id == aux->conta->id_cliente)
    {
      /// Percorre a lista de transações.
      for(struct Transacoes *lista = transacoes->next; lista != NULL; lista = lista->next)
      {
        /// Verifica se o id da conta bate com o id de origem ou de destino da
        /// transacao e se a transação está na data prevista.
        if (lista->transacao->data.tm_year == dataAtual->tm_year && lista->transacao->data.tm_mon == dataAtual->tm_mon && (lista->transacao->id_conta_origem == aux->conta->id || lista->transacao->id_conta_destino == aux->conta->id))
        {
          /// Verifica se à necessidade de inversão do sinal do valor da transação.
          if(lista->transacao->id_conta_origem == aux->conta->id)
            /// Adiciona na lista uma cópia da transação com o sinal do valor negativo.
            append_sorted_transacao(new, negative(lista->transacao));
          else
            /// Adiciona a transação original na lista.
            append_sorted_transacao(new, lista->transacao);
        }
      }
    }
  }

  printf("%s", borda);
  /// Mostra o somatório do saldo das transações com data anteriore ao mês atual.
  printf("|\t%15s\t\t\t\t\t\t R$ %+10.2lf\t|\n", "Saldo Anterior", getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual));
  printf("%s", borda);

  /// Mostra a lista de transações
  print_transacoes(new, operacoes);

  /// Mostra o somatório do saldo das transações com data referênte ao mês atual.
  printf("%s", borda);
  printf("|\t%15s\t\t\t\t\t\t R$ %+10.2lf\t|\n", "Saldo Atual", (saldo(new) + getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual) ));
  printf("%s", borda);

  /// Limpa a lista de transações auxiliar criada.
  garbageColector(new);
}

double valorTotalFatura(struct Transacoes_cartao_credito *cartao, struct tm *dataCliente)
{
  /**
    * Calcula o valor total da fatura
  **/
  double total = 0.0;
  for(struct Transacoes_cartao_credito *aux = cartao->next; aux != NULL; aux = aux->next)
  {
    total += valorFatura(aux->transacao_cartao_credito);
  }

  return total;
}

int validaData(struct Transacao_cartao_credito *transacao, struct tm *dataAtual)
{
  /**
    * Verifica se a data da atual está dentro do periodo de validade da compra.
  **/

  /// Data de início da transação.
  long long int intervalo_inf = transacao->data_compra.tm_year*12 + transacao->data_compra.tm_mon;

  /// Data de termino da transação.
  long long int intervalo_sup = transacao->data_compra.tm_year*12 + transacao->data_compra.tm_mon + transacao->qtde_parcelas;

  /// Data atual.
  long long int now = dataAtual->tm_year*12 + dataAtual->tm_mon;

  return (intervalo_inf < now && now <= intervalo_sup);
}

void fatura_cartao(struct Cliente *cliente, struct Transacoes_cartao_credito *cartao, struct Contas *contas, struct tm *dataCliente)
{
  /**
    * Representa o detalhamento das compras realizadas pelo cliente.
  **/

  /// Lista que guarda as transações do cartão de crédito do cliente determinado.
  struct Transacoes_cartao_credito *dividas = malloc(sizeof(struct Transacoes_cartao_credito));
  dividas->next = NULL;

  /// Percorre a lista de contas.
  for(struct Contas *aux = contas->next; aux != NULL; aux = aux->next)
  {
    /// Verificase a conta atual refere-se ao cliente desejado.
    if(aux->conta->id_cliente == cliente->id)
    {
      /// Percorre a lista de transações de cartão de crédito.
      for(struct Transacoes_cartao_credito *cartao_aux = cartao->next;
        cartao_aux != NULL; cartao_aux = cartao_aux->next)
      {
        /// Se a transação for referênte à conta previamente selecionada.
        if(cartao_aux->transacao_cartao_credito->id_conta == aux->conta->id
        && validaData(cartao_aux->transacao_cartao_credito, dataCliente))
        {
          /// Adiciona a transação na lista de transações referêntes ao cliente selecionado.
          append_Transacoes_cartao_credito(dividas, cartao_aux->transacao_cartao_credito);
        }
      }
    }
  }

  /// Abre o arquivo paraa impreção do extrato.
  FILE *extrato = fopen("extrato.txt", "w");

  /// Limpa o arquivo.
  fflush(extrato);

  fprintf(extrato, "\n|----------------|-----------------------------------|---------------|\n");

  /// Imprime o nome do cliente.
  fprintf(extrato, "                               %s                          \n", cliente->nome);

  /// Imprime a lista de transações.
  print_Transacoes_cartao_credito(extrato ,dividas, dataCliente);

  /// Imprime o valor mínimo à pagar por mês.
  fprintf(extrato, "|  Valor Mínimo  |                                   | R$ %10.2lf |\n", valorTotalFatura(dividas, dataCliente)*0.1);

  /// Imprime o valor máximo à pagar por mês.
  fprintf(extrato, "|  Valor Máximo  |                                   | R$ %10.2lf |\n", valorTotalFatura(dividas, dataCliente));
  fprintf(extrato, "|----------------|-----------------------------------|---------------|\n");

  /// Fecha o arquivo do extrato.
  fclose(extrato);
}


/// Interação com a interface

void writeEstado(FILE *file, struct Clientes *clientes, struct Contas *contas, char *estado)
{
  /**
    * Representa a listagem dos clientes por estado.
  **/

  /// Percorre a lista de clientes
  for(struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    /// Se o estado corresponder ao desejado.
    if (strcmp(aux->cliente->estado, estado) == 0)
    {
      /// Mostra o cliente no formato pré definido.
      fprintf(file, "%d,%s,%s,%s,%s,%d\n", aux->cliente->id, aux->cliente->nome, aux->cliente->cpf, aux->cliente->telefone, aux->cliente->municipio, qtdContas(contas, aux->cliente->id));
    }
  }
}

void write_conta(FILE *file, struct Conta *conta)
{
  /**
    * Mostra informações de uma conta.
  **/
  fprintf(file, "%d, %d", conta->numero_conta, conta->variacao);
}

void write_saldo(FILE *file, struct Contas *cabeca, struct Transacoes *transacoes, struct Cliente *cliente)
{
  /**
    * Representa a listagem do saldo atual do cliente em cada conta.
  **/

  /// Mostra o nome do cliente e o saldo total das contas.
  fprintf(file, "%s, %+5.2lf\n", cliente->nome, getSaldoTotal(cabeca, transacoes, cliente->id));

  /// Percorre a lista de contas.
  for(struct Contas *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    /// Verifica se a conta atual corresponde com a conta desejada.
    if (aux->conta->id_cliente == cliente->id)
    {
      /// Mostra a conta no formato padrão.
      write_conta(file, aux->conta);
      /// Mostra o saldo da conta atual.
      fprintf(file, ", R$ %+5.2lf\n", getSaldo(transacoes, aux->conta->id));
    }
  }
}

void write_cliente(FILE *file, struct Cliente *cliente, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Mostra o cliente recebido no formato específico.
  **/

  fprintf(file, "%s, %s, R$ %+.2lf\n", cliente->nome, cliente->cpf, getSaldoTotal(contas, transacoes, cliente->id));
}

void write_clientes(FILE *file, struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Percorre a lista de clientes e mostra cada cliente.
  **/

  for(struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    write_cliente(file, aux->cliente, contas, transacoes);
  }
}

void writeSaldoClientes(FILE *file, struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
{
  /**
    * Representa a listagem de todos os clientes com o saldo de cada cliente.
  **/
  struct Clientes *temp = malloc(sizeof(struct Clientes));
  temp->next = NULL;
  int len_clientes = length_cliente(clientes);

  /// Percorre a lista de clientes.
  for (struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    append_sorted_cliente(contas, transacoes, temp, aux->cliente);
    ///printf("|\t%s\t\t|\t%s\t\t|\tR$ %.2lf \t|\n", aux->cliente->nome, aux->cliente->cpf, getSaldoTotal(contas, transacoes, aux->cliente->id));
  }

  /// Mostra os dados do cliente no formato especificado.
  write_clientes(file, temp, contas, transacoes);
}

void write_transacoes(FILE *file, struct Transacoes *cabeca, struct Operacoes *operacoes)
{
  /**
    * Percorre a lista de transações e
    * mostra os detalhes de cada transação.
  **/

  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    fprintf(file, "%d/%d/%d, %s, %.2lf\n", aux->transacao->data.tm_mday, aux->transacao->data.tm_mon, aux->transacao->data.tm_year, getOperacao(operacoes, aux->transacao->id_operacao)->nome, aux->transacao->valor);
  }
}

void write_extrato(FILE *file, struct Cliente *cliente, struct Contas *contas, int numero_conta, struct Transacoes *transacoes, struct Operacoes *operacoes, struct tm *dataAtual)
{
  /**
    * Representa a listagem das transações realizadas pelo cliente no mês atual.
  **/

  /// Lista de transações auxiliar.
  struct Transacoes *new = malloc(sizeof(struct Transacoes));
  new->next = NULL;   /// Essa linha é M-U-I-T-O importante!!!

  /// Percorre a lista de contas.
  for(struct Contas *aux = contas->next; aux != NULL; aux = aux->next)
  {
    /// Verifica o numero da conta.
    if(aux->conta->numero_conta == numero_conta && cliente->id == aux->conta->id_cliente)
    {
      /// Percorre a lista de transações.
      for(struct Transacoes *lista = transacoes->next; lista != NULL; lista = lista->next)
      {
        /// Verifica se o id da conta bate com o id de origem ou de destino da
        /// transacao e se a transação está na data prevista.
        if (lista->transacao->data.tm_year == dataAtual->tm_year && lista->transacao->data.tm_mon == dataAtual->tm_mon && (lista->transacao->id_conta_origem == aux->conta->id || lista->transacao->id_conta_destino == aux->conta->id))
        {
          /// Verifica se à necessidade de inversão do sinal do valor da transação.
          if(lista->transacao->id_conta_origem == aux->conta->id)
            /// Adiciona na lista uma cópia da transação com o sinal do valor negativo.
            append_sorted_transacao(new, negative(lista->transacao));
          else
            /// Adiciona a transação original na lista.
            append_sorted_transacao(new, lista->transacao);
        }
      }
    }
  }

  /// Mostra o somatório do saldo das transações com data anteriore ao mês atual.
  fprintf(file, "%s, R$ %+.2lf\n", "Saldo Anterior", getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual));

  /// Mostra a lista de transações
  write_transacoes(file, new, operacoes);

  /// Mostra o somatório do saldo das transações com data referênte ao mês atual.
  fprintf(file, "%s, R$ %+.2lf\n", "Saldo Atual", (saldo(new) + getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual) ));
  
  /// Limpa a lista de transações auxiliar criada.
  garbageColector(new);
}
