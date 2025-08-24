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

struct Missoes {
  char nome [30];
  char descricao [100];
  int tropas;
  int territorios;
};

// Function prototypes
void loopDeAtaques(struct Territorio* territorios, int numeroDeTerritorios, struct Missoes missaoAtual);
int menuPrincipal(struct Territorio* territorios, int numeroDeTerritorios, struct Missoes missaoAtual);
void exibirMissao(struct Missoes missao);
int verificarMissaoCompleta(struct Missoes missao, struct Territorio* territorios, int numeroDeTerritorios, char* corJogador);
void parabenizarJogador(struct Missoes missao);

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

void atacarTerritorio(struct Territorio* territorios, int numeroDeTerritorios, int indiceAtacante, int indiceDefensor, struct Missoes missaoAtual){
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
  
  // Verifica se a missao foi completada
  if (verificarMissaoCompleta(missaoAtual, territorios, numeroDeTerritorios, atacante->cor)) {
    parabenizarJogador(missaoAtual);
  }
}

int executarAtaque(struct Territorio* territorios, int numeroDeTerritorios, struct Missoes missaoAtual) {
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
  
  atacarTerritorio(territorios, numeroDeTerritorios, indiceAtacante, indiceDefensor, missaoAtual);
  return 0; // Continuar
}

struct Missoes* criarMissoes() {
  struct Missoes* missoes = malloc(5 * sizeof(struct Missoes));
  
  // Missao 1: Conquistar 1 territorio
  strcpy(missoes[0].nome, "Conquistar 1 territorio");
  strcpy(missoes[0].descricao, "Conquiste pelo menos 1 territorio inimigo");
  missoes[0].tropas = 0;
  missoes[0].territorios = 1;
  
  // Missao 2: Conquistar 2 territorios
  strcpy(missoes[1].nome, "Conquistar 2 territorios");
  strcpy(missoes[1].descricao, "Conquiste pelo menos 2 territorios inimigos");
  missoes[1].tropas = 0;
  missoes[1].territorios = 2;
  
  // Missao 3: Derrotar America
  strcpy(missoes[2].nome, "Derrotar America");
  strcpy(missoes[2].descricao, "Conquiste o territorio America");
  missoes[2].tropas = 0;
  missoes[2].territorios = 0;
  
  // Missao 4: Derrotar Asia
  strcpy(missoes[3].nome, "Derrotar Asia");
  strcpy(missoes[3].descricao, "Conquiste o territorio Asia");
  missoes[3].tropas = 0;
  missoes[3].territorios = 0;
  
  // Missao 5: Derrotar Oceania
  strcpy(missoes[4].nome, "Derrotar Oceania");
  strcpy(missoes[4].descricao, "Conquiste o territorio Oceania");
  missoes[4].tropas = 0;
  missoes[4].territorios = 0;
  
  return missoes;
}

struct Missoes sortearMissao(struct Missoes* missoes) {
  int indice = rand() % 5;
  return missoes[indice];
}

void exibirMissao(struct Missoes missao) {
  printf("--------------------------------\n");
  printf("MISSAO ATUAL:\n");
  printf("Nome: %s\n", missao.nome);
  printf("Descricao: %s\n", missao.descricao);
  printf("--------------------------------\n");
}

int verificarMissaoCompleta(struct Missoes missao, struct Territorio* territorios, int numeroDeTerritorios, char* corJogador) {
  int territoriosConquistados = 0;
  
  // Conta quantos territorios o jogador possui
  for (int i = 0; i < numeroDeTerritorios; i++) {
    if (strcmp(territorios[i].cor, corJogador) == 0) {
      territoriosConquistados++;
    }
  }
  
  // Verifica se a missao foi completada
  if (strstr(missao.nome, "Conquistar") != NULL) {
    if (strstr(missao.nome, "1 territorio") != NULL) {
      return territoriosConquistados >= 1;
    } else if (strstr(missao.nome, "2 territorios") != NULL) {
      return territoriosConquistados >= 2;
    }
  } else if (strstr(missao.nome, "Derrotar") != NULL) {
    // Verifica se o territorio especifico foi conquistado
    char* territorioAlvo = NULL;
    if (strstr(missao.nome, "America") != NULL) {
      territorioAlvo = "America";
    } else if (strstr(missao.nome, "Asia") != NULL) {
      territorioAlvo = "Asia";
    } else if (strstr(missao.nome, "Oceania") != NULL) {
      territorioAlvo = "Oceania";
    }
    
    if (territorioAlvo != NULL) {
      for (int i = 0; i < numeroDeTerritorios; i++) {
        if (strcmp(territorios[i].nome, territorioAlvo) == 0 && 
            strcmp(territorios[i].cor, corJogador) == 0) {
          return 1;
        }
      }
    }
  }
  
  return 0;
}

void parabenizarJogador(struct Missoes missao) {
  printf("--------------------------------\n");
  printf("PARABENS! VOCE COMPLETOU A MISSAO!\n");
  printf("Missao: %s\n", missao.nome);
  printf("Descricao: %s\n", missao.descricao);
  printf("--------------------------------\n");
}

int menuPrincipal(struct Territorio* territorios, int numeroDeTerritorios, struct Missoes missaoAtual) {
  while (1) {
    printf("\n=== MENU ===\n");
    printf("1. Ver territorios\n");
    printf("2. Continuar ataques\n");
    printf("3. Ver missao atual\n");
    printf("4. Sair do jogo\n");
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
        loopDeAtaques(territorios, numeroDeTerritorios, missaoAtual);
        break;
      case 3:
        exibirMissao(missaoAtual);
        break;
      case 4:
        printf("Saindo do jogo...\n");
        return 1; // Indica que deve sair do jogo
      default:
        printf("Opcao invalida!\n");
        break;
    }
  }
  return 0;
}

void loopDeAtaques(struct Territorio* territorios, int numeroDeTerritorios, struct Missoes missaoAtual) {
  while (1) {
    int resultado = executarAtaque(territorios, numeroDeTerritorios, missaoAtual);
    if (resultado == 1 || resultado == 2) {
      break;
    }
    
    // Mostra o menu apos cada ataque
    menuPrincipal(territorios, numeroDeTerritorios, missaoAtual);
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

  // Criando e sorteando a missao
  struct Missoes* missoes = criarMissoes();
  struct Missoes missaoAtual = sortearMissao(missoes);
  
  printf("Missao sorteada!\n");
  exibirMissao(missaoAtual);
  
  // Inicia o jogo
  loopDeAtaques(territorio, numeroDeTerritorios, missaoAtual);
  if (menuPrincipal(territorio, numeroDeTerritorios, missaoAtual) == 1) {
    free(territorio);
    free(missoes);
    return 0;
  }
  free(territorio);
  free(missoes);
  return 0;
}
