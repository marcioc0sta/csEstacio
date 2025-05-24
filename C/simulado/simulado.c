#include <stdio.h>

int main() {
  char letra;

  printf("Digite uma letra: ");

  scanf("%c", &letra);

  letra = letra + ('A' - 'a');

  printf("Letra digitada: %c\n", letra);
  return 0;
}