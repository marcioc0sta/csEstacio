#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

int encontrarTerritorioPorNome(struct Territorio* territorios, int numeroDeTerritorios, char* nome){
  for (int i = 0; i < numeroDeTerritorios; i++) {
    if (strcmp(territorios[i].nome, nome) == 0) {
      return i;
    }
  }
  return -1; // Territorio nao encontrado
}


void exibirResultadoDoAtaque(struct Territorio* atacante, struct Territorio* defensor, int dadosDoAtacante, int dadosDoDefensor){
  printf("--------------------------------\n -- Resultado do Ataque --\n--------------------------------\n");
  printf("Atacante: %s\n", atacante->nome);
  printf("Defensor: %s\n", defensor->nome);
  printf("Vencedor: %s\n", dadosDoAtacante > dadosDoDefensor ? atacante->nome : defensor->nome);
  printf("Dados %s: %d\n", atacante->nome, dadosDoAtacante);
  printf("Dados %s: %d\n", defensor->nome, dadosDoDefensor);
  printf("Tropas %s: %d\n", atacante->nome, atacante->tropas);
  printf("Tropas %s: %d\n", defensor->nome, defensor->tropas);
  printf("--------------------------------\n");
}

void atacarTerritorio(struct Territorio* territorios, int numeroDeTerritorios, int indiceAtacante, int indiceDefensor){
  struct Territorio* atacante = &territorios[indiceAtacante];
  struct Territorio* defensor = &territorios[indiceDefensor];
  
  int dadosDoAtacante = rand() % 6 + 1;
  int dadosDoDefensor = rand() % 6 + 1;

  printf("Dados %s: %d\n", atacante->nome, dadosDoAtacante);
  printf("Dados %s: %d\n", defensor->nome, dadosDoDefensor);

  if (dadosDoAtacante > dadosDoDefensor){
    defensor->tropas = defensor->tropas - 1;
    printf("%s venceu!\n", atacante->nome);
    
    if (defensor->tropas == 0) {
      printf("%s conquistou o territorio %s!\n", atacante->nome, defensor->nome);
      strcpy(defensor->cor, atacante->cor);
      defensor->tropas = 1;
      atacante->tropas = atacante->tropas - 1;
      printarTerritorios(territorios, numeroDeTerritorios);
      return;
    }
  } else {
    atacante->tropas = atacante->tropas - 1;
    printf("%s venceu!\n", defensor->nome);
    
    if (atacante->tropas == 0){
      printf("%s conquistou o territorio %s!\n", defensor->nome, atacante->nome);
      strcpy(atacante->cor, defensor->cor);
      atacante->tropas = 1;
      defensor->tropas = defensor->tropas - 1;
      printarTerritorios(territorios, numeroDeTerritorios);
      return;
    }
  }

  exibirResultadoDoAtaque(atacante, defensor, dadosDoAtacante, dadosDoDefensor);
}

int executarAtaque(struct Territorio* territorios, int numeroDeTerritorios) {
  printf("Digite o nome do territorio atacante (ou 'sair' para sair, 'parar' para parar ataques): ");
  char nomeAtacante[30];
  scanf(" %[^\n]s", nomeAtacante);
  getchar();
  
  if (strcmp(nomeAtacante, "sair") == 0) {
    printf("Saindo do jogo...\n");
    return 2; // Sair do jogo
  }
  
  if (strcmp(nomeAtacante, "parar") == 0) {
    printf("Parando ataques...\n");
    return 1; // Parar ataques
  }
  
  int indiceAtacante = encontrarTerritorioPorNome(territorios, numeroDeTerritorios, nomeAtacante);
  if (indiceAtacante == -1) {
    printf("Territorio '%s' nao encontrado!\n", nomeAtacante);
    return 0; // Continuar
  }
  
  printf("Digite o nome do territorio defensor: ");
  char nomeDefensor[30];
  scanf(" %[^\n]s", nomeDefensor);
  getchar();
  
  int indiceDefensor = encontrarTerritorioPorNome(territorios, numeroDeTerritorios, nomeDefensor);
  if (indiceDefensor == -1) {
    printf("Territorio '%s' nao encontrado!\n", nomeDefensor);
    return 0; // Continuar
  }
  
  if (indiceAtacante == indiceDefensor) {
    printf("Um territorio nao pode atacar a si mesmo!\n");
    return 0; // Continuar
  }
  
  if (strcmp(territorios[indiceAtacante].cor, territorios[indiceDefensor].cor) == 0) {
    printf("Territorios da mesma cor nao podem atacar um ao outro!\n");
    return 0; // Continuar
  }
  
  if (territorios[indiceAtacante].tropas <= 0) {
    printf("O territorio %s nao tem tropas para atacar!\n", territorios[indiceAtacante].nome);
    return 0; // Continuar
  }
  
  atacarTerritorio(territorios, numeroDeTerritorios, indiceAtacante, indiceDefensor);
  return 0; // Continuar
}

void loopDeAtaques(struct Territorio* territorios, int numeroDeTerritorios) {
  while (1) {
    int resultado = executarAtaque(territorios, numeroDeTerritorios);
    if (resultado == 1 || resultado == 2) {
      break;
    }
  }
}

void menuPrincipal(struct Territorio* territorios, int numeroDeTerritorios) {
  while (1) {
    printf("\n=== MENU ===\n");
    printf("1. Ver territorios\n");
    printf("2. Continuar ataques\n");
    printf("3. Sair do jogo\n");
    printf("Escolha uma opcao: ");
    
    int opcao;
    scanf("%d", &opcao);
    getchar();
    
    switch (opcao) {
      case 1:
        printarTerritorios(territorios, numeroDeTerritorios);
        break;
      case 2:
        printf("Retomando ataques...\n");
        loopDeAtaques(territorios, numeroDeTerritorios);
        break;
      case 3:
        printf("Saindo do jogo...\n");
        return;
      default:
        printf("Opcao invalida!\n");
        break;
    }
  }
}

int main(){
  // Inicializando o gerador de numeros aleatorios
  srand(time(NULL));
  
  // Criando o numero de territorios
  int numeroDeTerritorios = criaNumeroDeTerritorios();

  // Criando o array de territorios
  struct Territorio *territorio = malloc(numeroDeTerritorios * sizeof(struct Territorio));

  // Criando os territorios
  criarTerritorios(territorio, numeroDeTerritorios);

  // Inicia o jogo
  loopDeAtaques(territorio, numeroDeTerritorios);
  menuPrincipal(territorio, numeroDeTerritorios);
  free(territorio);
  return 0;
}
