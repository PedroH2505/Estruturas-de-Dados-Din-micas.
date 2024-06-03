#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    float dado;
    struct Nodo* prox;
} Nodo;

typedef struct Pilha {
    Nodo* topo;
} Pilha;

void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

void push(Pilha* pilha, float valor) {
    Nodo* novoNodo = (Nodo*) malloc(sizeof(Nodo));
    novoNodo->dado = valor;
    novoNodo->prox = pilha->topo;
    pilha->topo = novoNodo;
}

float pop(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha está vazia.\n");
        return -1; // Valor de erro
    }
    Nodo* temp = pilha->topo;
    float valor = temp->dado;
    pilha->topo = temp->prox;
    free(temp);
    return valor;
}

int estaVazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

void exibirPilha(Pilha* pilha) {
    Nodo* atual = pilha->topo;
    printf("Pilha: ");
    while (atual != NULL) {
        printf("%.2f ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir (push)\n");
    printf("2. Retirar (pop)\n");
    printf("3. Exibir Pilha\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Pilha pilha;
    inicializarPilha(&pilha);
    int opcao;
    float valor;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um número real para empilhar: ");
                scanf("%f", &valor);
                push(&pilha, valor);
                break;
            case 2:
                if (!estaVazia(&pilha)) {
                    valor = pop(&pilha);
                    printf("Valor desempilhado: %.2f\n", valor);
                } else {
                    printf("A pilha está vazia.\n");
                }
                break;
            case 3:
                exibirPilha(&pilha);
                break;
        }
    } while (opcao != 0);

    return 0;
}

