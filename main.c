#include <stdio.h>
#include <stdlib.h>

#include "default_tools.c"

int project(struct Clientes *clientes, struct Contas *contas, struct Operacoes *operacoes, struct Transacoes *transacoes, struct Transacoes_cartao_credito *transacoes_cartao)
{
  while (1)
  {
    switch (getOpcao())
    {
      case 1:
        /// Listagem de clientes por estado.
        getEstado(stdout, clientes, contas);
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
        printf("Vllw... Fllw...\n");
        return 0;
    }
  }
}

int main(int argc, char *argv[ ])
{
  //system("./logo.sh");
  // Abertura do arquivo.
  FILE *file = fopen("arquivo-menor.txt", "r");

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


  file = fopen("buffer.csv", "w");

  /// Implementação das chamadas de função via linha de comando.
  if (argc > 1)
  {
    /// 1° Clientes por estado.
    if (!strcmp(argv[1], "clientes_estado"))
    {
      if (argc-2 == 1)
      {
        printf("Aqui\n");
        writeEstado(file, clientes, contas, argv[2]);
      }
    }else
    /// 2° Saldo de um cliente
    if (!strcmp(argv[1], "cliente_saldo"))
    {
      if (argc-2 == 1)
      {
        write_saldo(file, contas, transacoes, getCliente(clientes, argv[2]));
      }
    }else
    /// 3° Saldo de todos os clientes
    if (!strcmp(argv[1], "clientes_lista"))
    {
      if (argc-2 == 0)
      {
        writeSaldoClientes(file, clientes, contas, transacoes);
      }
    }else
    /// 4° Extrato do mês atual
    if (!strcmp(argv[1], "extrato_atual"))
    {
      if (argc-2 == 2)
      {
        write_extrato(file, getCliente(clientes, argv[3]), contas, atoi(argv[2]), transacoes, operacoes, getMesAtual());
      }
    }else
    /// 5° Extato do mes específico.
    if (!strcmp(argv[1], "extrato"))
    {
      printf("extrato\n");
      if (argc-2 == 4)
      {
        write_extrato(file, getCliente(clientes, argv[3]), contas, atoi(argv[2]), transacoes, operacoes, castMesAtual(argv[4], argv[5]));
      }
    }else if (!strcmp(argv[1], "fatura"))
    {
      if (argc-2 == 3)
      {
        fatura_cartao(getCliente(clientes, argv[2]), transacoes_cartao, contas, castMesAtual(argv[3], argv[4]));
      }
      printf("Fatura Impressa!\n");
    }
    fclose(file);
    return 0;
  }

  fclose(file);

  return project(clientes, contas, operacoes, transacoes, transacoes_cartao);
}
