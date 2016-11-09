struct tm *getMesAtual()
{
  struct tm *hoje; //estrutura para armazenar data e hora.
  time_t segundos;
  time(&segundos); //obtém a hora em segundos.
  hoje = localtime(&segundos); //converte horas em segundos.
  hoje->tm_mon;//+=1
  return hoje;
}

struct tm *inputMesAtual()
{
  struct tm *hoje; //estrutura para armazenar data e hora.
  printf("Digite a data desejada(mm/yyyy):\n>>> ");
  scanf("%d/%d\n", &hoje->tm_mon, &hoje->tm_year);
  return hoje;
}
