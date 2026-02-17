#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes globais
#define MAX_TERRITORIOS 5

// Definição da estrutura
struct Territorio {
    char nome[50];
    char cor[10];
    int tropas;
};

struct especialista { // exibir o mapa do jogo
    char nome[50];
    char estrategia[100];
};

struct ataque { // realizar ataques entre territórios
    char territorioAtacante[50];
    char territorioDefesa[50];
    int tropasEnviadas;
};

struct dados { // rolar dados para resolver batalhas
    int valorDado;
};

struct Territorio *territorios; // Ponteiro para armazenar os territórios
struct especialista *especialistas; // Ponteiro para armazenar os especialistas
struct ataque *ataques; // Ponteiro para armazenar os ataques
struct dados *dados; // Ponteiro para armazenar os dados

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal (main)
int main() {
    territorios = (struct Territorio *) malloc(MAX_TERRITORIOS * sizeof(struct Territorio));
    especialistas = (struct especialista *) malloc(MAX_TERRITORIOS * sizeof(struct especialista));
    ataques = (struct ataque *) malloc(MAX_TERRITORIOS * sizeof(struct ataque));
    dados = (struct dados *) malloc(MAX_TERRITORIOS * sizeof(struct dados));

    if (territorios == NULL || especialistas == NULL || ataques == NULL || dados == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    int totalTerritorios = 0;

    srand((unsigned int) time(NULL));

    // Cadastro dos territórios
    printf("==========================\n");
    printf("JOGO DE WAR\n");
    printf("==========================\n");
    printf("-- Cadastre os %d territorios --\n\n", MAX_TERRITORIOS);

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(territorios[i].nome, 50, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do território %d: ", i + 1);
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite o número de tropas no território %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);
        printf("\nTerritório %d cadastrado com sucesso!\n", i + 1);
        printf("---------------------------\n");
        limparBufferEntrada();
    }

    totalTerritorios = MAX_TERRITORIOS;

    // Exibição dos territórios cadastrados
    printf("-- Lista de Territórios --\n\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("============================\n");
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("============================\n");
    }

    // Fase de ataque
    printf("-- Fase de Ataque --\n\n");
    while (1) {
        printf("Digite o número do território atacante de 1 a %d ou 0 para sair: ", totalTerritorios);
        int ataque;
        if (scanf("%d", &ataque) != 1) {
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();

        if (ataque == 0) {
            break;
        }
        if (ataque < 1 || ataque > totalTerritorios) {
            printf("Número de território inválido! Tente novamente.\n");
            continue;
        }

        printf("Digite o número do território de defesa: ");
        int defesa;
        if (scanf("%d", &defesa) != 1) {
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();

        if (defesa < 1 || defesa > totalTerritorios) {
            printf("Número de território inválido! Tente novamente.\n");
            continue;
        }
        
        int tropasEnviar = 1;

        // Armazenar o ataque (usa índice 0 por simplicidade)
        strcpy(ataques[0].territorioAtacante, territorios[ataque - 1].nome);
        strcpy(ataques[0].territorioDefesa, territorios[defesa - 1].nome);
        ataques[0].tropasEnviadas = tropasEnviar;
        printf("\nAtaque registrado: %s atacando %s com %d tropas.\n", ataques[0].territorioAtacante, ataques[0].territorioDefesa, ataques[0].tropasEnviadas);

        // Fase de rolagem de dados: 1 dado para cada lado
        int dadoAtacante = rand() % 6 + 1;
        int dadoDefensor = rand() % 6 + 1;
        printf("Dado do atacante: %d\n", dadoAtacante);
        printf("Dado do defensor: %d\n", dadoDefensor);

        // Processamento do resultado do ataque
        if (dadoAtacante > dadoDefensor) {
            // Atacante vence: defensor perde tropas
            territorios[defesa - 1].tropas -= ataques[0].tropasEnviadas;
            if (territorios[defesa - 1].tropas <= 0) {
                // Território conquistado: move tropas enviadas para o novo território
                territorios[defesa - 1].tropas = ataques[0].tropasEnviadas;
                territorios[ataque - 1].tropas -= ataques[0].tropasEnviadas;
                if (territorios[ataque - 1].tropas < 0) territorios[ataque - 1].tropas = 0;
                // Atualiza controle/cor para o atacante
                strcpy(territorios[defesa - 1].cor, territorios[ataque - 1].cor);
                printf("\nO atacante venceu o combate e conquistou %s!\n", territorios[defesa - 1].nome);
            } else {
                printf("\nO atacante venceu o combate! O defensor perdeu %d tropas.\n", ataques[0].tropasEnviadas);
            }
            printf("Status: %s (tropas: %d), %s (tropas: %d)\n",
                   territorios[ataque - 1].nome, territorios[ataque - 1].tropas,
                   territorios[defesa - 1].nome, territorios[defesa - 1].tropas);
        } else {
            // Defensor vence: tropas enviadas são perdidas
            territorios[ataque - 1].tropas -= ataques[0].tropasEnviadas;
            if (territorios[ataque - 1].tropas < 0) territorios[ataque - 1].tropas = 0;
            printf("\nO defensor venceu o combate! Tropas enviadas foram perdidas.\n");
            printf("Status: %s (tropas: %d), %s (tropas: %d)\n",
                   territorios[ataque - 1].nome, territorios[ataque - 1].tropas,
                   territorios[defesa - 1].nome, territorios[defesa - 1].tropas);
        }

    // libera memoria alocada
    free(territorios);
    free(especialistas);
    free(ataques);
    free(dados);

    printf("Memoria liberada. Ate mais!\n");

    return 0;
    }





