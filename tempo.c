struct tm *getMesAtual()
{
  struct tm *hoje; //estrutura para armazenar data e hora.
  time_t segundos;
  time(&segundos); //obtém a hora em segundos.
  hoje = localtime(&segundos); //converte a hora de segundos para struct tm.
  hoje->tm_mon+=1;  // Atuliza o mês.
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
