#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes globais
#define MAX_LIVROS 50
#define TAM_STRING 100

// definição da estrutura
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// função para limpar o buffer de entrada 
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// função principal (main)
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    // laço principal do menu
    do {
        // exibe menu
        printf("==========================\n");
        printf("BIBLIOTECA PARTE 1\n");
        printf("==========================\n");
        printf("1- Cadastrar novo livro\n");
        printf("2- Listar todos os livros\n");
        printf("0- Sair\n");
        printf("---------------------------\n");
        printf("Escolha uma opcao: ");

        // le a opção do usuario
        scanf("%d", &opcao);
        limparBufferEntrada();

        // processamento da opção
        switch (opcao) {
            case 1:
                printf("-- Cadastro de Novo Livro --\n\n");

                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    totalLivros++;

                    printf("\nLivro cadastro com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Nao e possivel cadastrar mais livros.\n");
                }

                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

            case 2: // listagem de livros 
                printf("-- Lista de Livros Cadastrados --\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("---------------------------\n");
                        printf("LIVRO %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);

                    }
                    printf("---------------------------\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0: 
                printf("\nSaindo do Sistema...\n");
                break;

                default:
                    printf("\nOpcao invalida! Tente novamente.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
        }

    }while (opcao != 0);

    return 0;
}
