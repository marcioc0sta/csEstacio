#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Territorio
{
  char nome [30];
  char cor [10];
  int tropas;
};

void criarTerritorios(struct Territorio territorios[], int numeroDeTerritorios){
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
  } while (i < numeroDeTerritorios);
}

void printarTerritorios(struct Territorio territorios[], int numeroDeTerritorios){
  for (int i = 0; i < numeroDeTerritorios; i++)
  {
    printf("--------------------------------\n -- Territorio %d --\n--------------------------------\n", i + 1);
    printf("Nome: %s\n", territorios[i].nome);
    printf("Cor: %s\n", territorios[i].cor);
    printf("Tropas: %d\n", territorios[i].tropas);
  }
  printf("--------------------------------\n");
}

int criaNumeroDeTerritorios(){
  int numeroDeTerritorios;
  printf("Digite o numero de territorios: ");
  scanf("%d", &numeroDeTerritorios);
  getchar();
  return numeroDeTerritorios;
}

int main(){
  // Criando o numero de territorios
  int numeroDeTerritorios = criaNumeroDeTerritorios();

  // Criando o array de territorios
  struct Territorio *territorio = malloc(numeroDeTerritorios * sizeof(struct Territorio));

  // Criando os territorios
  criarTerritorios(territorio, numeroDeTerritorios);
  printarTerritorios(territorio, numeroDeTerritorios);

  free(territorio);
  return 0;
}
