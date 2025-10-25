#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  char nome;
  int id;
}Peca;

#define MAX 5

typedef struct {
  Peca pecas[MAX];
}Pecas;

Peca* gerarPeca(){
  static Peca peca;
  // gerar pecas aleatorias entre I O T L
  char tipos[] = {'I', 'O', 'T', 'L'};
  int id = rand() % 4;
  peca.nome = tipos[id];
  peca.id = id;

  return &peca;
}

void exibirPecas(Peca* pecas){
  for(int i = 0; i < MAX; i++){
    printf("[%d %c]", pecas[i].id, pecas[i].nome);
  }
}

void menu(){
  printf("1. Gerar peca\n");
  printf("2. Mostrar peca\n");
  printf("3. Sair\n");
}

int main(){
  srand(time(NULL));
  Peca* pecas = gerarPeca();
  
  exibirPecas(pecas);
  return 0;
}