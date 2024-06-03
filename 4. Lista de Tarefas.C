#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    char descricao[100];
    struct Tarefa* prox;
} Tarefa;

typedef struct {
    Tarefa* cabeca;
} ListaTarefas;

void inicializarLista(ListaTarefas* lista) {
    lista->cabeca = NULL;
}

void adicionarTarefa(ListaTarefas* lista, char* descricao) {
    Tarefa* novaTarefa = (Tarefa*) malloc(sizeof(Tarefa));
    strcpy(novaTarefa->descricao, descricao);
    novaTarefa->prox = lista->cabeca;
    lista->cabeca = novaTarefa;
}

void removerTarefa(ListaTarefas* lista) {
    if (lista->cabeca == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    Tarefa* temp = lista->cabeca;
    lista->cabeca = lista->cabeca->prox;
    free(temp);
}

void exibirTarefas(ListaTarefas* lista) {
    Tarefa* atual = lista->cabeca;
    while (atual != NULL) {
        printf("Tarefa: %s\n", atual->descricao);
        atual = atual->prox;
    }
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Adicionar Tarefa\n");
    printf("2. Remover Tarefa\n");
    printf("3. Exibir Tarefas\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    ListaTarefas lista;
    inicializarLista(&lista);
    int opcao;
    char descricao[100];

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a descrição da tarefa: ");
                scanf(" %[^\n]s", descricao);
                adicionarTarefa(&lista, descricao);
                break;
            case 2:
                removerTarefa(&lista);
                break;
            case 3:
                exibirTarefas(&lista);
                break;
        }
    } while (opcao != 0);

    return 0;
}
