#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes globais
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// definição da estrutura
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para emprestado
};

struct Emprestimo {
    int indiceLivro; // índice do livro emprestado
    char nomeUsuario[TAM_STRING];
};

// Prototipo das funções
// Declarar as funçoes aqui permite que a 'main' as chame antes de suas definições, mantendo o código organizado e fácil de ler.
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca, struct Emprestimo *emprestimos, int *totalEmprestimos, int totalLivros);
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);

// função principal (main)
// Agora a função main é mais limpa. Ela aloca memoria, controla o menu,
// e delega as tarefas para as funções especializadas.
int main() {
    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));
    
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;


    do {
        // exibe o menu
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        // processamento da opção
        switch (opcao) {
            case 1: // cadastro de livros
                // Passamos o endereço de totalLivros (&) para que a função possa atualizar o valor na main.
                cadastrarLivro(biblioteca, &totalLivros);
                break;

            case 2: // listagem de livros 
                // passamos apenas o valor de totalLivros, pois a função só precisa ler.
                listarLivros(biblioteca, totalLivros);
                break;

            case 3: // realizar emprestimo
                realizarEmprestimo(biblioteca, emprestimos, &totalEmprestimos, totalLivros);
                break;
            
            case 4: // listar emprestimos
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;

            case 0: 
                printf("\nSaindo do Sistema...\n");
                break;

                default:
                    printf("Opcao invalida! Tente novamente.\n");
                    break;
        }

    }while (opcao != 0);

    // Chama a função para liberar a memória alocada.
    liberarMemoria(biblioteca, emprestimos);
    return 0;
}

// Implementação das funções
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n=== Sistema de Biblioteca ===\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Realizar Emprestimo\n");
    printf("4. Listar Emprestimos\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

/**
 * @brief Função para cadastrar um livro na biblioteca.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Ponteiro para o contador de livros cadastrados.
 */

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    printf("\n=== Cadastro de Livro ===\n");

    if (*totalLivros >= MAX_LIVROS) {
        int indice = *totalLivros; // Usa o valor apontado pelo ponteiro para o indice

        printf("Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);

        printf("Digite o autor do livro: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);

        printf("Digite a editora do livro: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);

        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = '\0';
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0';
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = '\0';

        printf("Digite a edicao: ");
        scanf("%d", &biblioteca[indice].edicao);
        limparBufferEntrada();

        biblioteca[indice].disponivel = 1; // marca o livro como disponível
        (*totalLivros)++; // incrementa o contador de livros
        printf("Livro cadastrado com sucesso!\n");
    } else {
        printf("Limite de livros atingido! Nao e possivel cadastrar mais.\n");
    }
    printf("pressione Enter para continuar...");
    getchar();
}

/**
 * @brief Função para listar os livros cadastrados na biblioteca.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Número total de livros cadastrados.
 */

void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    printf("\n=== Lista de Livros ===\n");

    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado!\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("-------------------------------\n");
            printf("Livro %d:\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
        }
        printf("-------------------------------\n");
    }
    printf("pressione Enter para continuar...");
    getchar();
}

/**
 * @brief Função para realizar um empréstimo de livro.
 * @param biblioteca Ponteiro para o array de livros. (modificavel, para alterar o status.)
 * @param totalLivros Número total de livros cadastrados.
 * @param emprestimos Ponteiro para o array de empréstimos.
 * @param totalEmprestimos Ponteiro para o contador de empréstimos realizados. 
 */

void realizarEmprestimo(struct Livro *biblioteca, struct Emprestimo *emprestimos, int *totalEmprestimos, int totalLivros) {
    printf("\n=== Realizar Emprestimo ===\n");

    if (totalLivros >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido! Nao e possivel realizar mais.\n");
        } else {
            printf("Livros disponiveis para emprestimo:\n");
            int disponiveis = 0;
            for (int i = 0; i < totalLivros; i++) {
                if (biblioteca[i].disponivel) {
                    printf("%d. %s\n", i + 1, biblioteca[i].nome);
                    disponiveis++;
                }
            }

            if (disponiveis == 0) {
                printf("Nenhum livro disponivel para emprestimo!\n");
            } else {
                printf("Digite o numero do livro que deseja emprestar: ");
                int numLivro;
                scanf("%d", &numLivro);
                limparBufferEntrada();

                int indice = numLivro - 1; // Ajusta para índice do array
                if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                    printf("Digite o nome do usuario: ");
                    fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                    emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = '\0';

                    emprestimos[*totalEmprestimos].indiceLivro = indice;
                    biblioteca[indice].disponivel = 0; // Modifica o array original.

                    (*totalEmprestimos)++; // Modifica o contador original.
                    printf("Emprestimo realizado com sucesso!\n");
                } else {
                    printf("Opcao invalida ou livro nao disponivel! Tente novamente.\n");
                }
            }
        }
    printf("pressione Enter para continuar...");
    getchar();
}

/**
 * @brief Função para listar os empréstimos realizados.
 * @param biblioteca Ponteiro para o array de livros (para mostrar os nomes dos livros).
 * @param emprestimos Ponteiro para o array de empréstimos.
 * @param totalEmprestimos Número total de empréstimos realizados.
 */

void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("\n=== Lista de Emprestimos ===\n");

    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado!\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            int indiceLivro = emprestimos[i].indiceLivro;
            printf("-------------------------------\n");
            printf("Emprestimo %d:\n", i + 1);
            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
            printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
        }
        printf("-------------------------------\n");
    }
    printf("pressione Enter para continuar...");
    getchar();
}

/**
 * @brief Função para liberar a memória alocada para a biblioteca e os empréstimos.
 */

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);
    printf("Memoria liberada com sucesso!\n");
}
