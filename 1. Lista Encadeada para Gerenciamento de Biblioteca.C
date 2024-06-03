#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do livro
typedef struct Livro {
    char autor[100];
    char titulo[100];
    char editora[100];
    int ano;
    struct Livro* prox;
} Livro;

// Funções de manipulação da lista
Livro* inserirLivroOrdenado(Livro* head, Livro* novoLivro) {
    Livro* novo = (Livro*) malloc(sizeof(Livro));
    strcpy(novo->autor, novoLivro->autor);
    strcpy(novo->titulo, novoLivro->titulo);
    strcpy(novo->editora, novoLivro->editora);
    novo->ano = novoLivro->ano;
    novo->prox = NULL;

    if (head == NULL || strcmp(novo->titulo, head->titulo) < 0) {
        novo->prox = head;
        return novo;
    }

    Livro* atual = head;
    while (atual->prox != NULL && strcmp(atual->prox->titulo, novo->titulo) < 0) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    return head;
}

Livro* removerLivro(Livro* head, char* titulo) {
    if (head == NULL) return NULL;

    if (strcmp(head->titulo, titulo) == 0) {
        Livro* temp = head;
        head = head->prox;
        free(temp);
        return head;
    }

    Livro* atual = head;
    while (atual->prox != NULL && strcmp(atual->prox->titulo, titulo) != 0) {
        atual = atual->prox;
    }

    if (atual->prox != NULL) {
        Livro* temp = atual->prox;
        atual->prox = atual->prox->prox;
        free(temp);
    }
    return head;
}

void alterarLivro(Livro* head, char* titulo) {
    Livro* atual = head;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        printf("Digite o novo autor: ");
        scanf("%s", atual->autor);
        printf("Digite o novo título: ");
        scanf("%s", atual->titulo);
        printf("Digite a nova editora: ");
        scanf("%s", atual->editora);
        printf("Digite o novo ano: ");
        scanf("%d", &atual->ano);
    } else {
        printf("Livro não encontrado.\n");
    }
}

Livro* buscarLivroPorNome(Livro* head, char* titulo) {
    Livro* atual = head;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->prox;
    }
    return atual;
}

Livro* buscarLivroPorAutor(Livro* head, char* autor) {
    Livro* result = NULL;
    Livro* atual = head;
    while (atual != NULL) {
        if (strcmp(atual->autor, autor) == 0) {
            Livro* novo = (Livro*) malloc(sizeof(Livro));
            strcpy(novo->autor, atual->autor);
            strcpy(novo->titulo, atual->titulo);
            strcpy(novo->editora, atual->editora);
            novo->ano = atual->ano;
            novo->prox = result;
            result = novo;
        }
        atual = atual->prox;
    }
    return result;
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir Livro\n");
    printf("2. Remover Livro\n");
    printf("3. Alterar Livro\n");
    printf("4. Buscar Livro por Nome\n");
    printf("5. Buscar Livro por Autor\n");
    printf("6. Exibir Todos os Livros\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void imprimirLivros(Livro* head) {
    Livro* atual = head;
    while (atual != NULL) {
        printf("Autor: %s, Titulo: %s, Editora: %s, Ano: %d\n", atual->autor, atual->titulo, atual->editora, atual->ano);
        atual = atual->prox;
    }
}

int main() {
    Livro* biblioteca = NULL;
    int opcao;
    char titulo[100], autor[100];
    Livro novoLivro;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Inserção
                printf("Digite o autor: ");
                scanf("%s", novoLivro.autor);
                printf("Digite o título: ");
                scanf("%s", novoLivro.titulo);
                printf("Digite a editora: ");
                scanf("%s", novoLivro.editora);
                printf("Digite o ano: ");
                scanf("%d", &novoLivro.ano);
                biblioteca = inserirLivroOrdenado(biblioteca, &novoLivro);
                break;
            case 2:
                // Remoção
                printf("Digite o título do livro a ser removido: ");
                scanf("%s", titulo);
                biblioteca = removerLivro(biblioteca, titulo);
                break;
            case 3:
                // Alteração
                printf("Digite o título do livro a ser alterado: ");
                scanf("%s", titulo);
                alterarLivro(biblioteca, titulo);
                break;
            case 4:
                // Busca por nome
                printf("Digite o título do livro a ser buscado: ");
                scanf("%s", titulo);
                Livro* livroEncontrado = buscarLivroPorNome(biblioteca, titulo);
                if (livroEncontrado != NULL) {
                    printf("Livro encontrado: %s por %s\n", livroEncontrado->titulo, livroEncontrado->autor);
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;
            case 5:
                // Busca por autor
                printf("Digite o autor do livro a ser buscado: ");
                scanf("%s", autor);
                Livro* livrosEncontrados = buscarLivroPorAutor(biblioteca, autor);
                if (livrosEncontrados != NULL) {
                    imprimirLivros(livrosEncontrados);
                } else {
                    printf("Livros não encontrados.\n");
                }
                break;
            case 6:
                // Exibir todos os livros
                imprimirLivros(biblioteca);
                break;
        }
    } while (opcao != 0);

    return 0;
}
