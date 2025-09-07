#include <stdio.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void bubbleSort(int vetor[], int tamanho) {
  for (int i = 0; i < tamanho - 1; i++) {
      for (int j = 0; j < tamanho - 1 - i; j++) {
          if (vetor[j] > vetor[j + 1]) {
              trocar(&vetor[j], &vetor[j + 1]);
          }
      }
  }
}

void insertionSort(int vetor[], int tamanho) {
  for (int i = 1; i < tamanho; i++) {
      int chave = vetor[i];
      int j = i - 1;

      // Move os elementos maiores que a chave uma posição à frente
      while (j >= 0 && vetor[j] > chave) {
          vetor[j + 1] = vetor[j];
          j--;
      }

      vetor[j + 1] = chave;
  }
}

void selectionSort(int vetor[], int tamanho) {
  for (int i = 0; i < tamanho - 1; i++) {
      int indiceMenor = i;
      for (int j = i + 1; j < tamanho; j++) {
          if (vetor[j] < vetor[indiceMenor]) {
              indiceMenor = j;
          }
      }
      if (indiceMenor != i) {
          trocar(&vetor[i], &vetor[indiceMenor]);
      }
  }
} 

void measureSortTime(void (*sortFunction)(int[], int), int vetor[], int tamanho, const char* sortName) {
    // Create a copy of the array to preserve original
    int vetorCopy[tamanho];
    for (int i = 0; i < tamanho; i++) {
        vetorCopy[i] = vetor[i];
    }
    
    clock_t inicio = clock();
    sortFunction(vetorCopy, tamanho);
    clock_t fim = clock();
    
    double tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    printf("%s: %.3f ms\n", sortName, tempo_ms);
}

int main() {
  int vetor[] = {5, 3, 8, 4, 2, 10, 1, 9, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
  int tamanho = sizeof(vetor) / sizeof(vetor[0]);
  
  printf("Vetor original: ");
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n\n");
  
  printf("Tempos de execucao:\n");
  measureSortTime(bubbleSort, vetor, tamanho, "Bubble Sort");
  measureSortTime(insertionSort, vetor, tamanho, "Insertion Sort");
  measureSortTime(selectionSort, vetor, tamanho, "Selection Sort");
  printf("\nVetor ordenado (bubble sort): ");
  bubbleSort(vetor, tamanho);
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n");

  printf("\nVetor ordenado (insertion sort): ");
  insertionSort(vetor, tamanho);
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n");

  printf("\nVetor ordenado (selection sort): ");
  selectionSort(vetor, tamanho);
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n");
}