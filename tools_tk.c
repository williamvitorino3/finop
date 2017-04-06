#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tempo.c"
#include "structs.c"
#include "read.c"

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

void print_saldo(FILE *file, struct Contas *cabeca, struct Transacoes *transacoes, struct Cliente *cliente)
{
  /**
    * Representa a listagem do saldo atual do cliente em cada conta.
  **/

  /// Mostra o nome do cliente e o saldo total das contas.
  printf("%s, %+5.2lf\n", cliente->nome, getSaldoTotal(cabeca, transacoes, cliente->id));

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

void writeSaldoCLientes(FILE *file, struct Clientes *clientes, struct Contas *contas, struct Transacoes *transacoes)
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
  print_clientes(file, temp, contas, transacoes);
}

void write_transacoes(FILE *file, struct Transacoes *cabeca, struct Operacoes *operacoes)
{
  /**
    * Percorre a lista de transações e
    * mostra os detalhes de cada transação.
  **/

  for(struct Transacoes *aux = cabeca->next; aux != NULL; aux = aux->next)
  {
    printf("|\t%d/%d/%d\t|\t%15s\t\t|\t%+5.2lf\t\t|\n", aux->transacao->data.tm_mday, aux->transacao->data.tm_mon, aux->transacao->data.tm_year, getOperacao(operacoes, aux->transacao->id_operacao)->nome, aux->transacao->valor);
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
        if (lista->transacao->data.tm_mon == dataAtual->tm_mon && (lista->transacao->id_conta_origem == aux->conta->id || lista->transacao->id_conta_destino == aux->conta->id))
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
  fprintf(file, "%s, R$ %+.2lf\n", "Saldo Atual", (getSaldoTotalPorMes(contas, transacoes, cliente->id, dataAtual->tm_mon) + getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual) ));

  /// Limpa a lista de transações auxiliar criada.
  garbageColector(new);
}
