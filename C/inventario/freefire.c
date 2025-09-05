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
void menuCadastrar(struct item *inventario, int *items);
void menuListar(struct item *inventario, int items);
void menuBuscar(struct item *inventario, int items);
void menuRemover(struct item *inventario, int *items);

int main() {
  int items = 0;
  int opcao;

  do {
    printf("\n=== MENU DO INVENTÁRIO ===\n");
    printf("1. Cadastrar item\n");
    printf("2. Listar itens\n");
    printf("3. Buscar item\n");
    printf("4. Remover item\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
      printf("Entrada inválida! Digite um número.\n");
      // Clear the input buffer
      while (getchar() != '\n');
      continue;
    }

    switch (opcao) {
      case 1:
        menuCadastrar(inventario, &items);
        break;
      
      case 2:
        menuListar(inventario, items);
        break;
      
      case 3:
        menuBuscar(inventario, items);
        break;
      
      case 4:
        menuRemover(inventario, &items);
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
  // Clear any leftover newline from previous scanf
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  fgets(item->nome, sizeof(item->nome), stdin);
  // Remove newline character
  item->nome[strcspn(item->nome, "\n")] = 0;
  
  printf("Digite o tipo do item: ");
  fgets(item->tipo, sizeof(item->tipo), stdin);
  // Remove newline character
  item->tipo[strcspn(item->tipo, "\n")] = 0;
  
  printf("Digite a quantidade do item: ");
  scanf("%d", &item->quantidade);
  // Clear the newline left by scanf
  getchar();
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
    if (inventario[i].quantidade > 0 && strcmp(inventario[i].nome, nome) == 0) {
      printf("\n=== RESULTADO DA BUSCA ===\n");
      printf("%-30s %-20s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
      printf("--------------------------------------------------------\n");
      printf("%-30s %-20s %-10d\n", inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
      printf("--------------------------------------------------------\n\n");
      return;
    }
  }
  printf("Item não encontrado\n");
}

void menuCadastrar(struct item *inventario, int *items) {
  if (*items < QTY_MAX_ITEMS) {
    int itemIndex = 0;
    // Find the next empty slot
    while (itemIndex < QTY_MAX_ITEMS && inventario[itemIndex].quantidade > 0) {
      itemIndex++;
    }
    
    if (itemIndex < QTY_MAX_ITEMS) {
      cadastrarItem(&inventario[itemIndex], *items);
      *items += inventario[itemIndex].quantidade;
      printf("Item cadastrado com sucesso!\n");
    } else {
      printf("Limite de itens atingido!\n");
    }
  } else {
    printf("Limite de itens atingido!\n");
  }
}

void menuListar(struct item *inventario, int items) {
  listarItens(inventario, items);
}

void menuBuscar(struct item *inventario, int items) {
  char nomeBusca[30];
  printf("Digite o nome do item a buscar: ");
  // Clear any leftover newline from previous scanf
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  fgets(nomeBusca, sizeof(nomeBusca), stdin);
  // Remove newline character
  nomeBusca[strcspn(nomeBusca, "\n")] = 0;
  buscarItem(inventario, nomeBusca);
}

void menuRemover(struct item *inventario, int *items) {
  if (*items > 0) {
    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    // Clear any leftover newline from previous scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    // Remove newline character
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;
    
    int itemIndex = -1;
    for (int i = 0; i < QTY_MAX_ITEMS; i++) {
      if (inventario[i].quantidade > 0 && strcmp(inventario[i].nome, nomeRemover) == 0) {
        itemIndex = i;
        break;
      }
    }
    
    if (itemIndex != -1) {
      printf("Item encontrado: %s (quantidade atual: %d)\n", inventario[itemIndex].nome, inventario[itemIndex].quantidade);
      printf("Digite a quantidade a remover (0 para remover todos): ");
      int quantidadeRemover;
      scanf("%d", &quantidadeRemover);
      
      if (quantidadeRemover <= 0 || quantidadeRemover >= inventario[itemIndex].quantidade) {
        // Remove all items
        *items -= inventario[itemIndex].quantidade;
        inventario[itemIndex].quantidade = 0;
        printf("Item %s removido completamente do inventário\n", nomeRemover);
      } else {
        // Remove partial quantity
        inventario[itemIndex].quantidade -= quantidadeRemover;
        *items -= quantidadeRemover;
        printf("Removidos %d unidades de %s (restam %d)\n", quantidadeRemover, nomeRemover, inventario[itemIndex].quantidade);
      }
    } else {
      printf("Item não encontrado!\n");
    }
  } else {
    printf("Nenhum item para remover!\n");
  }
}

