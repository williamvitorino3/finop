/**
  * Autor = William Vitorino.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tempo.c"
#include "structs.c"
#include "read.c"

/// TODO: Terminar a logo;
char teste[] = "\\ \\    /\\    / /\n \\ \\  /  \\  / /\n  \\ \\/ /\\ \\/ /\n   \\  /  \\  /\n    \\/    \\/";

int getOpcao()
{
  /**
    * Representação de menu principal.
    * Pega o valor referênte à opção desejada e retorna.
  **/

  int op;
  printf("\nEscolha uma opção:\n1 - Listar clientes por estado.\n2 - Saldo atual do cliente.\n3 - Listar saldo dos cliente\n4 - Extrato mês atual\n5 - Extrato mês anterior\n6 - Fatura do cartão de crédito\n0 - Sair\n>>> ");
  scanf("%d", &op);
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

void filtroEstado(struct Clientes *clientes, struct Contas *contas, char *estado)
{
  /**
    * Representa a listagem dos clientes por estado.
  **/

  printf("|---------------|-----------------------|-----------------------|-----------------------|-----------------------|---------------|\n");
  printf("|\tid\t|\tnome\t\t|\tCPF\t\t|\ttelefone\t|\tmunicípio\t|     contas    |\n");
  printf("|---------------|-----------------------|-----------------------|-----------------------|-----------------------|---------------|\n");

  /// Percorre a lista de clientes
  for(struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    /// Se o estado corresponder ao desejado.
    if (strcmp(aux->cliente->estado, estado) == 0)
    {
      /// Mostra o cliente no formato pré definido.
      printf("|\t%d\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t\t|\t%d\t|\n", aux->cliente->id, aux->cliente->nome, aux->cliente->cpf, aux->cliente->telefone, aux->cliente->municipio, qtdContas(contas, aux->cliente->id));
    }
  }
  printf("|---------------|-----------------------|-----------------------|-----------------------|-----------------------|---------------|\n");
}

void getEstado(struct Clientes *clientes, struct Contas *contas)
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

  filtroEstado(clientes, contas, estado);
}

double getSaldoTotalPorMes(struct Contas *cabeca, struct Transacoes *transacoes, int id_cliente, int mes_atual)
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
      saldo += getSaldoMensal(transacoes, aux->conta->id, mes_atual);
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
  printf("\t%s\t\t\tR$ %5.2lf \t\t\n", cliente->nome, getSaldoTotal(cabeca, transacoes, cliente->id));
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
      printf("\tR$ %5.2lf\t|\n", getSaldo(transacoes, aux->conta->id));
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
    if (getSaldoTotal(contas, transacoes, aux->next->cliente->id) > getSaldoTotal(contas, transacoes, e->id))
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

  printf("|\t%s\t\t|\t%s\t\t|\tR$ %.2lf \t|\n", cliente->nome, cliente->cpf, getSaldoTotal(contas, transacoes, cliente->id));
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

  struct Clientes *temp = malloc(sizeof(struct Clientes));
  temp->next = NULL;

  char bordas[] = "|-------------------------------|-------------------------------|-----------------------|\n";

  printf("%s",bordas);

  /// Percorre a lista de clientes.
  for (struct Clientes *aux = clientes->next; aux != NULL; aux = aux->next)
  {
    /// Mostra os dados do cliente no formato especificado.
    append_sorted_cliente(contas, transacoes, temp, aux->cliente);
    ///printf("|\t%s\t\t|\t%s\t\t|\tR$ %.2lf \t|\n", aux->cliente->nome, aux->cliente->cpf, getSaldoTotal(contas, transacoes, aux->cliente->id));
  }
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

void print_extrato(struct Cliente *cliente, struct Contas *contas, int numero_conta, struct Transacoes *transacoes, struct Operacoes *operacoes, struct tm *dataAtual)
{
  /**
    * Representa a listagem das transações realizadas pelo cliente no mês atual.
  **/
  printf("%d\n", dataAtual->tm_year);
  /// Borda da tabela à ser mostrada.
  char borda[] = "|-----------------------|-----------------------|-----------------------|\n";

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

  printf("%s", borda);
  /// Mostra o somatório do saldo das transações com data anteriore ao mês atual.
  printf("|\tSaldo Anterior\t|\t\t\t|\t %.2lf\t\t|\n", getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual));
  printf("%s", borda);

  /// Mostra a lista de transações
  print_transacoes(new, operacoes);

  /// Mostra o somatório do saldo das transações com data referênte ao mês atual.
  printf("%s", borda);
  printf("|\tSaldo Atual\t|\t\t\t|\t %.2lf\t\t|\n", (getSaldoTotalPorMes(contas, transacoes, cliente->id, dataAtual->tm_mon) + getSaldoTotalMesAnterior(contas, transacoes, cliente->id, dataAtual) ));
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

  fprintf(extrato, "\n|---------------|-------------------------|-----------|\n");

  /// Imprime o nome do cliente.
  fprintf(extrato, "|                      %s                 |\n", cliente->nome);

  /// Imprime a lista de transações.
  print_Transacoes_cartao_credito(extrato ,dividas, dataCliente);

  /// Imprime o valor mínimo à pagar por mês.
  fprintf(extrato, "|  Valor Mínimo |                         | R$%7.2lf |\n", valorTotalFatura(dividas, dataCliente)*0.1);

  /// Imprime o valor máximo à pagar por mês.
  fprintf(extrato, "|  Valor Máximo |                         | R$%7.2lf |\n", valorTotalFatura(dividas, dataCliente));
  fprintf(extrato, "|---------------|-------------------------|-----------|\n");

  /// Fecha o arquivo do extrato.
  fclose(extrato);
}

int main()
{
    printf("%s\n\n", teste);
  /// Abertura do arquivo.
  FILE *file = fopen("arquivo.txt", "r");

  /// Estruturas para armazenar os dados do arquivo.
  struct Clientes *clientes = malloc(sizeof(struct Clientes));
  struct Contas *contas = malloc(sizeof(struct Contas));
  struct Operacoes *operacoes = malloc(sizeof(struct Operacoes));
  struct Transacoes *transacoes = malloc(sizeof(struct Transacoes));
  struct Transacoes_cartao_credito *transacoes_cartao = malloc(sizeof(struct Transacoes_cartao_credito));

  /// Lê as estruturas do arquivo.
  readCliente(file, clientes);
  readConta(file, contas);
  readOperacoes(file, operacoes);
  readTransacao(file, transacoes);
  readTransacoes_cartao_credito(file, transacoes_cartao);

  printf("\rLeitura do arquivo concluída...                                    \n");

  /// Laço proncipal do projeto.
  while (1)
  {
    switch (getOpcao())
    {
      case 1:
        /// Listagem de clientes por estado.
        getEstado(clientes, contas);
        break;
      case 2:
        /// Saldo atual do cliente.
        print_saldo(contas, transacoes, inputCliente(clientes));
        break;
      case 3:
        /// Listagem do saldo dos clientes.
        listarSaldoCLientes(clientes, contas, transacoes);
        break;
      case 4:
        /// Extrato bancário (mês atual).
        print_extrato(inputCliente(clientes), contas, inputConta(contas), transacoes, operacoes, getMesAtual());
        break;
      case 5:
        /// Extrato bancário (mês anterior).
        print_extrato(inputCliente(clientes), contas, inputConta(contas), transacoes, operacoes, inputMesAtual());
        break;
      case 6:
        /// Por o valor máximo para só os valores do mês.
        fatura_cartao(inputCliente(clientes), transacoes_cartao, contas, inputMesAtual());
        break;
      default:
        fclose(file);
        printf("Vllw... Fllw...\n");
        return 0;
    }
  }

  return 0;
}
