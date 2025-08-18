#include <stdio.h>
#include <string.h>
struct Territorio
{
  char nome [30];
  char cor [10];
  int tropas;
};

void criarTerritorios(struct Territorio territorios[]){
  int i = 0;
  do 
  {
    printf("--------------------------------\n -- Criando Territorios %d --\n--------------------------------\n", i + 1);
    printf("Digite o nome do territorio: ");
    scanf(" %[^\n]s", territorios[i].nome);
    getchar();

    printf("Digite a cor do territorio: ");
    scanf(" %[^\n]s", territorios[i].cor);
    getchar();

    printf("Digite o numero de tropas do territorio: ");
    scanf("%d", &territorios[i].tropas);
    getchar();

    printf("--------------------------------\n");
    i++;
  } while (i < 5);
}

void printarTerritorios(struct Territorio territorios[]){
  for (int i = 0; i < 5; i++)
  {
    printf("--------------------------------\n -- Territorio %d --\n--------------------------------\n", i + 1);
    printf("Nome: %s\n", territorios[i].nome);
    printf("Cor: %s\n", territorios[i].cor);
    printf("Tropas: %d\n", territorios[i].tropas);
  }
  printf("--------------------------------\n");
}

int main(){
  struct Territorio territorios[5];

  criarTerritorios(territorios);
  printarTerritorios(territorios);

  return 0;
}
