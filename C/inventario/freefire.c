#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct item {
  char nome[30];
  char tipo[20];
  int quantidade;
};

#define QTY_MAX_ITEMS 10

struct item inventario[QTY_MAX_ITEMS];

void cadastrarItem(struct item *item, int items);
void removerItem(struct item *item, int items);
void listarItens(struct item *inventario, int items);
void buscarItem(struct item *inventario, char *nome);

int main() {
  int items = 0;
  int opcao;
  char nomeBusca[30];

  do {
    printf("\n=== MENU DO INVENTÁRIO ===\n");
    printf("1. Cadastrar item\n");
    printf("2. Listar itens\n");
    printf("3. Buscar item\n");
    printf("4. Remover item\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        if (items < QTY_MAX_ITEMS) {
          int itemIndex = 0;
          // Find the next empty slot
          while (itemIndex < QTY_MAX_ITEMS && inventario[itemIndex].quantidade > 0) {
            itemIndex++;
          }
          
          if (itemIndex < QTY_MAX_ITEMS) {
            cadastrarItem(&inventario[itemIndex], items);
            items += inventario[itemIndex].quantidade;
            printf("Item cadastrado com sucesso!\n");
          } else {
            printf("Limite de itens atingido!\n");
          }
        } else {
          printf("Limite de itens atingido!\n");
        }
        break;
      
      case 2:
        listarItens(inventario, items);
        break;
      
      case 3:
        printf("Digite o nome do item a buscar: ");
        scanf("%s", nomeBusca);
        buscarItem(inventario, nomeBusca);
        break;
      
      case 4:
        if (items > 0) {
          char nomeRemover[30];
          printf("Digite o nome do item a ser removido: ");
          scanf("%s", nomeRemover);
          
          int itemIndex = -1;
          for (int i = 0; i < QTY_MAX_ITEMS; i++) {
            if (inventario[i].quantidade > 0 && strcmp(inventario[i].nome, nomeRemover) == 0) {
              itemIndex = i;
              break;
            }
          }
          
          if (itemIndex != -1) {
            items -= inventario[itemIndex].quantidade;
            inventario[itemIndex].quantidade = 0; // Mark as empty
            printf("Item %s removido do inventário\n", nomeRemover);
          } else {
            printf("Item não encontrado!\n");
          }
        } else {
          printf("Nenhum item para remover!\n");
        }
        break;
      
      case 5:
        printf("Saindo do inventário...\n");
        break;
      
      default:
        printf("Opção inválida! Tente novamente.\n");
    }
  } while (opcao != 5);

  return 0;
}

void cadastrarItem(struct item *item, int items) {
  if (items >= QTY_MAX_ITEMS) {
    printf("Limite de itens atingido\n");
    return;
  }

  printf("Digite o nome do item: ");
  scanf("%s", item->nome);
  printf("Digite o tipo do item: ");
  scanf("%s", item->tipo);
  printf("Digite a quantidade do item: ");
  scanf("%d", &item->quantidade);
}

void removerItem(struct item *item, int items) {
  if (items == 0) {
    printf("Nenhum item cadastrado\n");
    return;
  }

  printf("Digite o nome do item a ser removido: ");
  scanf("%s", item->nome);

  for (int i = 0; i < items; i++) {
    if (strcmp(inventario[i].nome, item->nome) == 0) {
      inventario[i] = inventario[items - 1];
      items--;
      break;
    }
  }

  printf("Item %s removido do inventário\n", item->nome);
}

void listarItens(struct item *inventario, int items) {
  if (items == 0) {
    printf("Nenhum item cadastrado\n");
    return;
  }

  printf("\n=== INVENTÁRIO ===\n");
  printf("%-30s %-20s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
  printf("--------------------------------------------------------\n");
  
  int tiposItens = 0;
  for (int i = 0; i < QTY_MAX_ITEMS; i++) {
    if (inventario[i].quantidade > 0) {
      printf("%-30s %-20s %-10d\n", inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
      tiposItens++;
    }
  }
  printf("--------------------------------------------------------\n");
  printf("Total de tipos de itens: %d\n", tiposItens);
  printf("Total de quantidade: %d\n\n", items);
}

void buscarItem(struct item *inventario, char *nome) {
  for (int i = 0; i < QTY_MAX_ITEMS; i++) {
    if (strcmp(inventario[i].nome, nome) == 0) {
      printf("Item encontrado: %s - %s - %d\n", inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
      return;
    }
  }
  printf("Item não encontrado\n");
}

