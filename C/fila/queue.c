#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char nome[30];
  int idade;
} Pessoa;

#define MAX 5

typedef struct {
  Pessoa pessoas[MAX];
  int inicio;
  int fim;
  int tamanho;
} Fila;

void inicializarFila(Fila *fila) {
  fila->inicio = 0;
  fila->fim = 0;
  fila->tamanho = 0;
}

int filaVazia(Fila *fila) {
  return fila->tamanho == 0;
}

int filaCheia(Fila *fila) {
  return fila->tamanho == MAX;
}

void inserir(Fila *fila, Pessoa pessoa) {
  if (filaCheia(fila)) {
    printf("Fila cheia\n");
  }
  fila->pessoas[fila->fim] = pessoa;
  fila->fim = (fila->fim + 1) % MAX;
  fila->tamanho++;
}

void remover(Fila *f, Pessoa *p) {
  if (filaVazia(f)) {
      printf("Fila vazia. Não é possível remover.\n");
      return;
  }

  *p = f->pessoas[f->inicio];             
  f->inicio = (f->inicio + 1) % MAX;     
  f->tamanho--;                        
}

void mostrarFila(Fila *f) {
  printf("Fila: ");
  for (int i = 0, idx = f->inicio; i < f->tamanho; i++, idx = (idx + 1) % MAX) {
      printf("[%s, %d] ", f->pessoas[idx].nome, f->pessoas[idx].idade);
  }
  printf("\n");
}

int main() {
  Fila f;
  inicializarFila(&f);  // Inicializa a fila

  // Insere algumas pessoas na fila
  Pessoa p1 = {"João", 25};
  Pessoa p2 = {"Maria", 30};
  inserir(&f, p1);
  inserir(&f, p2);

  mostrarFila(&f);  // Mostra a fila antes da remoção

  // Remove uma pessoa da fila
  Pessoa removida;
  remover(&f, &removida);  // Aqui usamos a função de remoção

  printf("Pessoa removida: %s, %d\n", removida.nome, removida.idade);

  mostrarFila(&f);  // Mostra a fila após a remoção

  return 0;
}