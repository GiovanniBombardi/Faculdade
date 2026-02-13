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

//nova estrutura para empréstimos
struct Emprestimo {
    int indiceLivro; // índice do livro emprestado
    char nomeUsuario[TAM_STRING];
};

// função para limpar o buffer de entrada 
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// função principal (main)
int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    // laço principal do menu
    do {
        // exibe menu
        printf("==========================\n");
        printf("BIBLIOTECA PARTE 1\n");
        printf("==========================\n");
        printf("1- Cadastrar novo livro\n");
        printf("2- Listar todos os livros\n");
        printf("3- Realizar emprestimo\n");
        printf("4- Listar emprestimos\n");
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

                    // define o livro como disponível
                    biblioteca[totalLivros].disponivel = 1;

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

                        // exibe status de disponibilidade
                        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");

                    }
                    printf("---------------------------\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3: // realizar emprestimo
                printf("-- Realizar Emprestimo --\n\n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprestimos atingidos!\n");
                } else {
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
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

                    int indice = numLivro - 1;

                    // validação da escolha do usuario
                    if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                        printf("Digite o nome do usuario que esta pegando o livro: ");
                        fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                        emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';
                        
                        // registra o emprestimo
                        emprestimos[totalEmprestimos].indiceLivro = indice;

                        // atualiza o status do livro para indisponivel
                        biblioteca[indice].disponivel = 0;

                        totalEmprestimos++;
                        printf("\nEmprestimo realizado com sucesso!\n");
                    } else {
                        printf("\nNumero de livro invalido ou livro indisponivel! Tente novamente.\n");
                    }
                }
            }

            printf("\nPressione Enter para continuar...");
            getchar();
            break;
            
            case 4: // listar emprestimos
                printf("-- Lista de Emprestimos --\n\n");

                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo registrado ainda.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("---------------------------\n");
                        printf("EMPRESTIMO %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
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

    // libera memoria alocada
    free(biblioteca);
    free(emprestimos);

    printf("Memoria liberada. Ate mais!\n");

    return 0;
}
