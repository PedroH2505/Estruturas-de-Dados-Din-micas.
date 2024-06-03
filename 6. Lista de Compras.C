#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char nome[100];
    int quantidade;
    struct Item* prox;
} Item;

typedef struct {
    Item* cabeca;
} ListaCompras;

void inicializarLista(ListaCompras* lista) {
    lista->cabeca = NULL;
}

void inserirItem(ListaCompras* lista, char* nome, int quantidade) {
    Item* novo = (Item*) malloc(sizeof(Item));
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->prox = lista->cabeca;
    lista->cabeca = novo;
}

void removerItem(ListaCompras* lista, char* nome) {
    Item* atual = lista->cabeca;
    Item* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto não encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        lista->cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
}

Item* consultarItem(ListaCompras* lista, char* nome) {
    Item* atual = lista->cabeca;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void exibirLista(ListaCompras* lista) {
    Item* atual = lista->cabeca;
    while (atual != NULL) {
        printf("Produto: %s - Quantidade: %d\n", atual->nome, atual->quantidade);
        atual = atual->prox;
    }
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir Produto\n");
    printf("2. Remover Produto\n");
    printf("3. Consultar Produto\n");
    printf("4. Exibir Lista\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    ListaCompras lista;
    inicializarLista(&lista);
    int opcao, quantidade;
    char nome[100];

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]s", nome);
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                inserirItem(&lista, nome, quantidade);
                break;
            case 2:
                printf("Digite o nome do produto a ser removido: ");
                scanf(" %[^\n]s", nome);
                removerItem(&lista, nome);
                break;
            case 3:
                printf("Digite o nome do produto a ser consultado: ");
                scanf(" %[^\n]s", nome);
                Item* item = consultarItem(&lista, nome);
                if (item != NULL) {
                    printf("Produto encontrado: %s - Quantidade: %d\n", item->nome, item->quantidade);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            case 4:
                exibirLista(&lista);
                break;
        }
    } while (opcao != 0);

    return 0;
}
