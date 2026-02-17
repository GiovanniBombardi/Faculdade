#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes globais
#define MAX_TERRITORIOS 5

// Definição da estrutura
struct Territorio {
    char nome[50];
    char cor[10];
    int tropas;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal (main)
int main() {
    struct Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

    // Laço principal do menu
    do {
        // Exibe menu
        printf("==========================\n");
        printf("JOGO DE WAR\n");
        printf("==========================\n");
        printf("1- Cadastrar novo território\n");
        printf("2- Listar todos os territórios\n");
        printf("0- Sair\n");
        printf("---------------------------\n");
        printf("Escolha uma opcao: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada();  

        // Processamento da opção
        switch (opcao) {
            case 1:
                printf("-- Cadastro de Novo Território --\n\n");

                if (totalTerritorios < MAX_TERRITORIOS) {
                    printf("Digite o nome do território: ");
                    fgets(territorios[totalTerritorios].nome, 50, stdin);

                    printf("Digite a cor do território: ");
                    fgets(territorios[totalTerritorios].cor, 10, stdin);

                    printf("Digite o número de tropas: ");
                    scanf("%d", &territorios[totalTerritorios].tropas);
                    limparBufferEntrada();

                    territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';
                    territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

                    totalTerritorios++;
                } else {
                    printf("Limite de territórios atingido!\n");
                }
                break;

            case 2:
                printf("-- Lista de Territórios --\n\n");
                
                if (totalTerritorios == 0) {
                    printf("Nenhum território cadastrado!\n");
                } else {
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("---------------------------\n");
                        printf("Território %d:\n", i + 1);
                        printf("Nome: %s\n", territorios[i].nome);
                        printf("Cor: %s\n", territorios[i].cor);
                        printf("Tropas: %d\n", territorios[i].tropas);
                        printf("---------------------------\n");
                    }
                }
                break;

                case 0:
                    printf("Saindo do jogo. Até a próxima!\n");
                    break;

                default:
                        printf("Opção inválida! Tente novamente.\n");
                        break;
            }
    } while (opcao != 0);

    free(territorios); // Libera a memória alocada para os territórios
    return 0;
}