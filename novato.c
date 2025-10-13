#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // Limite máximo da mochila

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MOCHILA DE LOOT ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf(" Saindo do inventário...\n");
                break;
            default:
                printf("  Opção inválida, tente novamente!\n");
        }

    } while(opcao != 0);

    return 0;
}

// Função para adicionar um item
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n Mochila cheia! Capacidade máxima (%d itens) atingida.\n", MAX_ITENS);
        printf("Remova um item antes de adicionar outro.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite o tipo do item (arma, munição, cura...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("\n Item \"%s\" adicionado com sucesso!\n", novo.nome);
    listarItens(mochila, *total);
}

// Função para remover um item com confirmação (S/N)
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n  A mochila está vazia, nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        char confirmacao;
        printf("\n  Tem certeza que deseja remover o item \"%s\"? (S/N): ", nomeRemover);
        scanf(" %c", &confirmacao);
        getchar(); // limpa o buffer

        if (confirmacao == 'S' || confirmacao == 's') {
            for (int j = encontrado; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("  Item \"%s\" removido com sucesso!\n", nomeRemover);
        } else {
            printf(" Remoção cancelada. Item \"%s\" permanece na mochila.\n", nomeRemover);
        }

    } else {
        printf(" Item \"%s\" não encontrado na mochila.\n", nomeRemover);
    }

    listarItens(mochila, *total);
}

// Função para listar os itens
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\n Mochila vazia!\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA (%d/%d) ===\n", total, MAX_ITENS);
    for (int i = 0; i < total; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("---------------------------\n");
    }
}

// Função para buscar um item
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n Item encontrado:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf(" Item \"%s\" não está na mochila.\n", nomeBusca);
    }
}