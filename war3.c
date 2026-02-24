#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_MISSOES 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct {
    char nome[50];
    char cor[10];
    char *missao;
} Jogador;

void limparBufferEntrada(void);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void exibirMissao(const char *missao);
void atacar(Territorio *atacante, Territorio *defensor);
void exibirMapa(Territorio *mapa, int tamanho);
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int nJogadores);

int main(void) {
    srand((unsigned int)time(NULL));

    char *missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 10 tropas no total",
        "Manter apenas territorios azuis",
        "Ter pelo menos 2 territorios com mais de 5 tropas"
    };

    int totalTerritorios = MAX_TERRITORIOS;
    Territorio *territorios = calloc(totalTerritorios, sizeof(Territorio));
    if (!territorios) {
        perror("malloc");
        return 1;
    }

    printf("==========================\n");
    printf("JOGO DE WAR - VERSAO COM MISSÕES\n");
    printf("==========================\n");
    printf("-- Cadastre os %d territorios --\n\n", totalTerritorios);

    for (int i = 0; i < totalTerritorios; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(territorios[i].nome, sizeof territorios[i].nome, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do território %d: ", i + 1);
        fgets(territorios[i].cor, sizeof territorios[i].cor, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite o número de tropas no território %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();
        printf("\nTerritório %d cadastrado com sucesso!\n", i + 1);
        printf("---------------------------\n");
    }

    // exibe mapa inicial
    exibirMapa(territorios, totalTerritorios);

    // cria os jogadores e atribui missões
    Jogador jogadores[2];
    strcpy(jogadores[0].nome, "Jogador 1");
    strcpy(jogadores[0].cor, "vermelha");
    jogadores[0].missao = malloc(100);
    atribuirMissao(jogadores[0].missao, missoes, MAX_MISSOES);
    printf("%s, sua missão é:\n", jogadores[0].nome);
    exibirMissao(jogadores[0].missao);

    strcpy(jogadores[1].nome, "Jogador 2");
    strcpy(jogadores[1].cor, "azul");
    jogadores[1].missao = malloc(100);
    atribuirMissao(jogadores[1].missao, missoes, MAX_MISSOES);
    printf("%s, sua missão é:\n", jogadores[1].nome);
    exibirMissao(jogadores[1].missao);

    int vencedor = -1;
    while (1) {
        printf("\n-- Fase de Ataque --\n");
        exibirMapa(territorios, totalTerritorios);

        int atacante, defensor;
        printf("Digite o número do território atacante (1-%d) ou 0 para sair: ", totalTerritorios);
        if (scanf("%d", &atacante) != 1) {
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();
        if (atacante == 0) break;
        if (atacante < 1 || atacante > totalTerritorios) {
            printf("Território inválido\n");
            continue;
        }
        printf("Digite o número do território defensor: ");
        if (scanf("%d", &defensor) != 1) {
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();
        if (defensor < 1 || defensor > totalTerritorios) {
            printf("Território inválido\n");
            continue;
        }
        if (atacante == defensor) {
            printf("Não é possível atacar o mesmo território\n");
            continue;
        }
        // valida se cor igual -> não permite ataque entre mesmos donos
        if (strcmp(territorios[atacante-1].cor, territorios[defensor-1].cor) == 0) {
            printf("Só é permitido atacar território inimigo\n");
            continue;
        }

        atacar(&territorios[atacante-1], &territorios[defensor-1]);

        // checa missões silenciosamente
        for (int j = 0; j < 2; j++) {
            if (verificarMissao(jogadores[j].missao, territorios, totalTerritorios)) {
                vencedor = j;
                break;
            }
        }
        if (vencedor != -1) {
            printf("\n*** %s cumpriu sua missão! ***\n", jogadores[vencedor].nome);
            break;
        }
    }

    liberarMemoria(territorios, jogadores, 2);
    if (vencedor == -1)
        printf("Jogo encerrado sem cumprimento de missões.\n");
    return 0;
}

// limpa caracteres pendentes do stdin até o fim da linha
// usada sempre que lemos inteiros com scanf e queremos garantir que
// a próxima leitura de string/fgets comece em linha limpa
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// escolhe aleatoriamente uma missão entre o vetor 'missoes' e copia
// para 'destino' usando strcpy. 'destino' deve apontar para memória
// previamente alocada pelo chamador.
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// verifica se uma missão foi cumprida de acordo com o estado atual
// do mapa de territórios. A comparação faz buscas simples na string
// da missão para decidir qual regra aplicar; cada regra caminha pelo
// vetor de territórios. Retorna 1 se atingida, 0 caso contrário.
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    if (strstr(missao, "3 territorios seguidos")) {
        int cont = 1;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i-1].cor) == 0) {
                cont++;
                if (cont >= 3) return 1;
            } else {
                cont = 1;
            }
        }
        return 0;
    }
    if (strstr(missao, "cor vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    if (strstr(missao, "10 tropas")) {
        int total = 0;
        for (int i = 0; i < tamanho; i++)
            total += mapa[i].tropas;
        return total >= 10;
    }
    if (strstr(missao, "apenas territorios azuis")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") != 0) return 0;
        }
        return 1;
    }
    if (strstr(missao, "2 territorios") && strstr(missao, "5 tropas")) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 5) cont++;
        }
        return cont >= 2;
    }
    return 0;
}

// imprime a missão na tela. recebe a string por valor, não altera.
void exibirMissao(const char *missao) {
    printf(" - %s\n", missao);
}

// simula um ataque entre dois territórios usando rolagens de dados 1‑6.
// Se o atacante vence, metade (no mínimo 1) de suas tropas vão para o defensor
// e o defensor passa a ter a cor do atacante. Caso contrário, o atacante perde
// uma tropa.
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;
    printf("%s ataca %s (dados: %d x %d)\n", atacante->nome, defensor->nome, dadoA, dadoD);
    if (dadoA > dadoD) {
        // atacante vence
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;
        defensor->tropas += tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
        printf("Atacante venceu: %d tropas transferidas\n", tropasTransferidas);
    } else {
        // defensor vence
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("Defensor venceu: atacante perde 1 tropa\n");
    }
}

// imprime o estado atual de todos os territórios (índice, nome, cor e tropas)
void exibirMapa(Territorio *mapa, int tamanho) {
    printf("\nMapa atual:\n");
    for (int i = 0; i < tamanho; i++) {
        printf(" %d) %s [%s] tropas: %d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// libera toda a memória dinâmica alocada na execução: vetor de territórios
// e as strings de missão de cada jogador
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int nJogadores) {
    free(mapa);
    for (int i = 0; i < nJogadores; i++) {
        free(jogadores[i].missao);
    }
}
