#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um componente da torre de fuga
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

#define MAX_COMPONENTES 20

// Variáveis globais para contagem de comparações
int comparacoes_bubble = 0;
int comparacoes_insertion = 0;
int comparacoes_selection = 0;
int comparacoes_busca = 0;

// Protótipos das funções
void cadastrarComponentes(Componente componentes[], int *numComponentes);
void bubbleSortPorNome(Componente componentes[], int n);
void insertionSortPorTipo(Componente componentes[], int n);
void selectionSortPorPrioridade(Componente componentes[], int n);
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]);
void mostrarComponentes(Componente componentes[], int n);
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n, char nomeAlgoritmo[]);
void menuPrincipal(Componente componentes[], int *numComponentes);
void menuOrdenacao(Componente componentes[], int numComponentes);
void limparBuffer();

int main() {
    Componente componentes[MAX_COMPONENTES];
    int numComponentes = 0;
    
    printf("=== SISTEMA DE PRIORIZAÇÃO E MONTAGEM DA TORRE DE FUGA ===\n");
    printf("Bem-vindo ao sistema de montagem da torre de fuga!\n");
    printf("Você pode cadastrar até %d componentes e escolher diferentes estratégias de ordenação.\n\n", MAX_COMPONENTES);
    
    menuPrincipal(componentes, &numComponentes);
    
    return 0;
}

/**
 * Função para limpar o buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Função para cadastrar componentes da torre
 */
void cadastrarComponentes(Componente componentes[], int *numComponentes) {
    if (*numComponentes >= MAX_COMPONENTES) {
        printf("Limite máximo de %d componentes atingido!\n", MAX_COMPONENTES);
        return;
    }
    
    printf("\n=== CADASTRO DE COMPONENTES ===\n");
    printf("Componente %d de %d:\n", *numComponentes + 1, MAX_COMPONENTES);
    
    // Nome do componente
    printf("Digite o nome do componente: ");
    limparBuffer();
    fgets(componentes[*numComponentes].nome, sizeof(componentes[*numComponentes].nome), stdin);
    componentes[*numComponentes].nome[strcspn(componentes[*numComponentes].nome, "\n")] = 0;
    
    // Tipo do componente
    printf("Digite o tipo do componente (controle, suporte, propulsão, etc.): ");
    fgets(componentes[*numComponentes].tipo, sizeof(componentes[*numComponentes].tipo), stdin);
    componentes[*numComponentes].tipo[strcspn(componentes[*numComponentes].tipo, "\n")] = 0;
    
    // Prioridade do componente
    printf("Digite a prioridade (1-10, onde 10 é mais prioritário): ");
    scanf("%d", &componentes[*numComponentes].prioridade);
    
    // Validação da prioridade
    while (componentes[*numComponentes].prioridade < 1 || componentes[*numComponentes].prioridade > 10) {
        printf("Prioridade inválida! Digite um valor entre 1 e 10: ");
        scanf("%d", &componentes[*numComponentes].prioridade);
    }
    
    (*numComponentes)++;
    printf("Componente cadastrado com sucesso!\n");
}

/**
 * Bubble Sort para ordenação por nome (string)
 */
void bubbleSortPorNome(Componente componentes[], int n) {
    comparacoes_bubble = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes_bubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os elementos
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}

/**
 * Insertion Sort para ordenação por tipo (string)
 */
void insertionSortPorTipo(Componente componentes[], int n) {
    comparacoes_insertion = 0;
    
    for (int i = 1; i < n; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        comparacoes_insertion++;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            comparacoes_insertion++;
            componentes[j + 1] = componentes[j];
            j--;
        }
        componentes[j + 1] = chave;
    }
}

/**
 * Selection Sort para ordenação por prioridade (int)
 */
void selectionSortPorPrioridade(Componente componentes[], int n) {
    comparacoes_selection = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        
        for (int j = i + 1; j < n; j++) {
            comparacoes_selection++;
            if (componentes[j].prioridade > componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
        }
    }
}

/**
 * Busca binária por nome (requer array ordenado por nome)
 */
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    comparacoes_busca = 0;
    int esquerda = 0, direita = n - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        comparacoes_busca++;
        int resultado = strcmp(componentes[meio].nome, nome);
        
        if (resultado == 0) {
            return meio; // Componente encontrado
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1; // Componente não encontrado
}

/**
 * Função para mostrar todos os componentes
 */
void mostrarComponentes(Componente componentes[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    
    printf("\n=== COMPONENTES DA TORRE DE FUGA ===\n");
    printf("%-30s %-20s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-30s %-20s %-10d\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("--------------------------------------------------------\n");
    printf("Total de componentes: %d\n\n", n);
}

/**
 * Função genérica para medir tempo de execução
 */
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n, char nomeAlgoritmo[]) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    // Criar uma cópia do array para não modificar o original
    Componente copia[MAX_COMPONENTES];
    for (int i = 0; i < n; i++) {
        copia[i] = componentes[i];
    }
    
    printf("\n=== EXECUTANDO %s ===\n", nomeAlgoritmo);
    
    inicio = clock();
    algoritmo(copia, n);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo de execução: %.6f segundos\n", tempo_gasto);
    
    // Mostrar número de comparações baseado no algoritmo
    if (strstr(nomeAlgoritmo, "Bubble") != NULL) {
        printf("Número de comparações: %d\n", comparacoes_bubble);
    } else if (strstr(nomeAlgoritmo, "Insertion") != NULL) {
        printf("Número de comparações: %d\n", comparacoes_insertion);
    } else if (strstr(nomeAlgoritmo, "Selection") != NULL) {
        printf("Número de comparações: %d\n", comparacoes_selection);
    }
    
    printf("Componentes ordenados:\n");
    mostrarComponentes(copia, n);
}

/**
 * Menu principal do sistema
 */
void menuPrincipal(Componente componentes[], int *numComponentes) {
    int opcao;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar componentes\n");
        printf("4. Buscar componente-chave\n");
        printf("5. Montagem final da torre\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            limparBuffer();
            continue;
        }
        
        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, numComponentes);
                break;
            case 2:
                mostrarComponentes(componentes, *numComponentes);
                break;
            case 3:
                if (*numComponentes > 0) {
                    menuOrdenacao(componentes, *numComponentes);
                } else {
                    printf("Nenhum componente cadastrado para ordenar!\n");
                }
                break;
            case 4:
                if (*numComponentes > 0) {
                    char nomeBusca[30];
                    printf("Digite o nome do componente-chave para buscar: ");
                    limparBuffer();
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                    
                    int posicao = buscaBinariaPorNome(componentes, *numComponentes, nomeBusca);
                    
                    if (posicao != -1) {
                        printf("\n=== COMPONENTE-CHAVE ENCONTRADO! ===\n");
                        printf("Nome: %s\n", componentes[posicao].nome);
                        printf("Tipo: %s\n", componentes[posicao].tipo);
                        printf("Prioridade: %d\n", componentes[posicao].prioridade);
                        printf("Posição no array: %d\n", posicao);
                        printf("Comparações realizadas: %d\n", comparacoes_busca);
                        printf("A torre pode ser ativada!\n");
                    } else {
                        printf("Componente-chave '%s' não encontrado!\n", nomeBusca);
                        printf("Comparações realizadas: %d\n", comparacoes_busca);
                        printf("Verifique se o array está ordenado por nome.\n");
                    }
                } else {
                    printf("Nenhum componente cadastrado para buscar!\n");
                }
                break;
            case 5:
                if (*numComponentes > 0) {
                    printf("\n=== MONTAGEM FINAL DA TORRE DE FUGA ===\n");
                    printf("Todos os componentes foram organizados e a torre está pronta!\n");
                    mostrarComponentes(componentes, *numComponentes);
                    printf("A torre de fuga foi montada com sucesso!\n");
                } else {
                    printf("Nenhum componente cadastrado para montagem!\n");
                }
                break;
            case 6:
                printf("Saindo do sistema de montagem da torre...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);
}

/**
 * Menu de ordenação
 */
void menuOrdenacao(Componente componentes[], int numComponentes) {
    int opcao;
    
    do {
        printf("\n=== MENU DE ORDENAÇÃO ===\n");
        printf("1. Bubble Sort (por nome)\n");
        printf("2. Insertion Sort (por tipo)\n");
        printf("3. Selection Sort (por prioridade)\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            limparBuffer();
            continue;
        }
        
        switch (opcao) {
            case 1:
                medirTempo(bubbleSortPorNome, componentes, numComponentes, "BUBBLE SORT");
                break;
            case 2:
                medirTempo(insertionSortPorTipo, componentes, numComponentes, "INSERTION SORT");
                break;
            case 3:
                medirTempo(selectionSortPorPrioridade, componentes, numComponentes, "SELECTION SORT");
                break;
            case 4:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);
}
