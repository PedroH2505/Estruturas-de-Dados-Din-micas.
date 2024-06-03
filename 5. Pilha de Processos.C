#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Processo {
    int id;
    char descricao[100];
    struct Processo* prox;
} Processo;

typedef struct {
    Processo* topo;
} PilhaProcessos;

void inicializarPilha(PilhaProcessos* pilha) {
    pilha->topo = NULL;
}

void push(PilhaProcessos* pilha, int id, char* descricao) {
    Processo* novo = (Processo*) malloc(sizeof(Processo));
    novo->id = id;
    strcpy(novo->descricao, descricao);
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

Processo* pop(PilhaProcessos* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha está vazia.\n");
        return NULL;
    }
    Processo* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    return temp;
}

int estaVazia(PilhaProcessos* pilha) {
    return pilha->topo == NULL;
}

void exibirPilha(PilhaProcessos* pilha) {
    Processo* atual = pilha->topo;
    while (atual != NULL) {
        printf("Processo #%d - %s\n", atual->id, atual->descricao);
        atual = atual->prox;
    }
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir Processo\n");
    printf("2. Remover Processo\n");
    printf("3. Exibir Pilha de Processos\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    PilhaProcessos pilha;
    inicializarPilha(&pilha);
    int opcao, id;
    char descricao[100];

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o ID do processo: ");
                scanf("%d", &id);
                printf("Digite a descrição do processo: ");
                scanf(" %[^\n]s", descricao);
                push(&pilha, id, descricao);
                break;
            case 2:
                if (!estaVazia(&pilha)) {
                    Processo* processo = pop(&pilha);
                    printf("Removido o processo #%d - %s\n", processo->id, processo->descricao);
                    free(processo);
                } else {
                    printf("A pilha está vazia.\n");
                }
                break;
            case 3:
                exibirPilha(&pilha);
                break;
        }
    } while (opcao != 0);

    while (!estaVazia(&pilha)) {
        Processo* processo = pop(&pilha);
        free(processo);
    }

    return 0;
}
