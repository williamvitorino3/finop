/**
  * Autor = William Vitorino.
**/

struct tm *getMesAtual()
{
  struct tm *hoje; //estrutura para armazenar data e hora.
  time_t segundos;
  time(&segundos); //obtém a hora em segundos.
  hoje = localtime(&segundos); //converte a hora de segundos para struct tm.
  hoje->tm_mon += 1;  // Atuliza o mês, pois começa a contar do mês 0.
  hoje->tm_year += 1900;    // Atualiza o ano, pq começa a contar de 1900.
  return hoje;
}

struct tm *inputMesAtual()
{
  struct tm *hoje = malloc(sizeof(struct tm)); //estrutura para armazenar data e hora.
  printf("Digite a data desejada(mm/yyyy):\n>>> ");
  scanf("%d/%d", &hoje->tm_mon, &hoje->tm_year);
  setbuf(stdin, NULL);
  return hoje;
}

struct tm *castMesAtual(char *mes, char *ano)
{
  struct tm *hoje = malloc(sizeof(struct tm)); //estrutura para armazenar data e hora.
  hoje->tm_mon = atoi(mes);
  hoje->tm_year = atoi(ano);
  return hoje;
}
