#include <stdio.h>

unsigned int randaux();

// Verifica se o input está entre o valor mínimo e máximo
void verifInput(int *var, int min, int max);

// Pula os aleatórios de <randaux()>
void pularAleatorios(int saltos);

// Preenche o tabuleiro com os números de <randaux()> (após pular aleatórios)
void criarTabuleiro(int *tabuleiro, int tamanho);

// Mostra o tabuleiro no formato correto
void mostrarTabuleiro(int *tabuleiro, int tamanho);

// Altera o tabuleiro de acordo com a jogada, retorna 1 se valer, retorna 0 se for invalida
int verifJogada(int *tabuleiro, int tamanho, int jogadaNum, int inicio, int casas);

// Verifica se há "X" no tabuleiro
int verifCasas(int *tabuleiro, int tamanho);

// Altera os valores do tabuleiro (ímpar - par e vice-versa)
void alterarTabuleiro(int *tabuleiro, int tamanho, int inicio, int casas);

void jogar(int *tabuleiro, int tamanho);

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// MAIN /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
  int tabuleiro[100] = {0};
  int tabuleiroTamanho;
  int saltos; // Números aleatórios a pular
  int jogando = 1;

  printf("Tamanho do tabuleiro: ");
  scanf("%d", &tabuleiroTamanho);

  verifInput(&tabuleiroTamanho, 1, 100);

  printf("Números aleatórios a pular: ");
  scanf("%d", &saltos);

  while (saltos < 0)
  {
    printf("O número de saltos tem que ser positivo ou 0.\n");
    scanf("%d", &saltos);
  }

  pularAleatorios(saltos);

  criarTabuleiro(tabuleiro, tabuleiroTamanho);

  jogar(tabuleiro, tabuleiroTamanho);

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTIONS /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int randaux()
{
  static long seed = 1;
  return (((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}

void verifInput(int *var, int min, int max)
{
  int val = *var;
  while (val < min || val > max)
  {
    printf("Valor inválido, por favor introduza um valor entre %d - %d\n", min, max);
    scanf("%d", &val);
  }
  *var = val;
}

void pularAleatorios(int saltos)
{
  for (int i = 0; i < saltos; i++)
  {
    randaux();
  }
}

void criarTabuleiro(int *tabuleiro, int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    tabuleiro[i] = randaux();
  }
}

void mostrarTabuleiro(int *tabuleiro, int tamanho)
{
  int unidade = 1;
  int dezena = 1;

  // Linha das dezenas
  if (tamanho > 9)
  {
    for (int i = 1; i <= tamanho; i++)
    {
      if (i % 10 == 0)
      {
        printf("%d", dezena);
        dezena++;
      }
      else
      {
        putchar(' ');
      }
    }
  }
  putchar('\n');

  // Linha das unidades
  for (int i = 1; i <= tamanho; i++)
  {
    if (unidade > 9) // para nao mostrar dezenas
    {
      unidade = 0;
    }

    printf("%d", unidade);
    unidade++;
  }
  putchar('\n');

  // Tabuleiro
  for (int i = 0; i < tamanho; i++)
  {
    if (tabuleiro[i] % 2 == 0)
    {
      putchar('O');
    }
    else
    {
      putchar('X');
    }
  }
}

int verifJogada(int *tabuleiro, int tamanho, int jogadaNum, int inicio, int casas)
{
  int validar;
  // O número de casas a trocar tem que sempre ser menor do que o tamanho do tabuleiro - a jogada.
  int limite = tamanho - jogadaNum;
  printf("Limite de casas: %d\n\n", limite - 1);
  if (jogadaNum < tamanho)
  {
    if (casas <= limite)
    {
      validar = verifCasas(tabuleiro, tamanho);
      if (validar == 1)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }

  // Se o número da jogada for maior ou igual ao tamanho do tabuleiro, o jogador só pode alterar 1 casa
  if (jogadaNum >= tamanho)
  {
    if (casas != 1)
    {
      return 0;
    }
    else
    {
      validar = verifCasas(tabuleiro, tamanho);
      if (validar == 1)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }
  return 0;
}

int verifCasas(int *tabuleiro, int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    if (tabuleiro[i] % 2 != 0)
    {
      return 1;
    }
  }
  return 0;
}

void alterarTabuleiro(int *tabuleiro, int tamanho, int inicio, int casas)
{
  int j = 0;
  for (int i = inicio - 1; j < casas && i < tamanho; i++, j++)
  {
    tabuleiro[i] += 1;
  }
  return;
}

void jogar(int *tabuleiro, int tamanho)
{
  int jogada = 1;
  int jogador = 1;

  while (jogada != 0)
  {
    int inicio;
    int numCasas;

    mostrarTabuleiro(tabuleiro, tamanho);
    putchar('\n');
    putchar('\n');

    // Recebendo o início
    printf("Jogada número: %d\n", jogada);
    printf("Jogador %d\n", jogador);
    printf("Início: ");
    scanf("%d", &inicio);

    verifInput(&inicio, 1, tamanho);

    printf("Casas a alterar: ");
    scanf("%d", &numCasas);
    putchar('\n');
    putchar('\n');

    int verificar = verifJogada(tabuleiro, tamanho, jogada, inicio, numCasas);

    if (verificar == 0)
    {
      printf("Jogada inválida. Jogador %d perdeu.\n", jogador);
      jogada = 0;
    }
    else
    {
      alterarTabuleiro(tabuleiro, tamanho, inicio, numCasas);
      // Trocar jogadores
      if (jogador == 1)
      {
        jogador = 2;
      }
      else
      {
        jogador = 1;
      }
      // Alterar o número da jogada
      jogada++;
    }
  }
}
