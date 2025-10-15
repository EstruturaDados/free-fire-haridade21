#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================
// ESTRUTURAS BÁSICAS
//============================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//============================
// VARIÁVEIS GLOBAIS
//============================

#define MAX_ITENS 10
Item mochilaVetor[MAX_ITENS];
int qtdItensVetor = 0;

No* mochilaLista = NULL;

int comparacoesSeq = 0;
int comparacoesBin = 0;

//============================
// FUNÇÕES DO VETOR
//============================

void inserirItemVetor() {
    if (qtdItensVetor >= MAX_ITENS) {
        printf("\n[Mochila Vetor] Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("\n[Mochila Vetor] Nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[qtdItensVetor++] = novo;
    printf("[Mochila Vetor] Item adicionado!\n");
}

void removerItemVetor() {
    if (qtdItensVetor == 0) {
        printf("\n[Mochila Vetor] Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("\n[Mochila Vetor] Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < qtdItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < qtdItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            qtdItensVetor--;
            printf("[Mochila Vetor] Item removido!\n");
            return;
        }
    }
    printf("[Mochila Vetor] Item não encontrado!\n");
}

void listarVetor() {
    if (qtdItensVetor == 0) {
        printf("\n[Mochila Vetor] Mochila vazia!\n");
        return;
    }
    printf("\nItens no Vetor:\n");
    for (int i = 0; i < qtdItensVetor; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void buscarSequencialVetor() {
    if (qtdItensVetor == 0) {
        printf("\n[Mochila Vetor] Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\n[Mochila Vetor] Nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    comparacoesSeq = 0;
    for (int i = 0; i < qtdItensVetor; i++) {
        comparacoesSeq++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado! Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesSeq);
            return;
        }
    }
    printf("Item não encontrado! Comparações: %d\n", comparacoesSeq);
}

void ordenarVetor() {
    if (qtdItensVetor < 2) {
        printf("\n[Mochila Vetor] Poucos itens para ordenar.\n");
        return;
    }

    Item temp;
    for (int i = 0; i < qtdItensVetor - 1; i++) {
        for (int j = 0; j < qtdItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("[Mochila Vetor] Itens ordenados!\n");
}

void buscarBinariaVetor() {
    if (qtdItensVetor == 0) {
        printf("\n[Mochila Vetor] Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\n[Mochila Vetor] Nome do item para busca binária: ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = qtdItensVetor - 1;
    comparacoesBin = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBin++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) {
            printf("Item encontrado! Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações binárias: %d\n", comparacoesBin);
            return;
        } else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    printf("Item não encontrado! Comparações binárias: %d\n", comparacoesBin);
}

//============================
// FUNÇÕES DA LISTA ENCADEADA
//============================

void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de memória!\n");
        return;
    }

    printf("\n[Mochila Lista] Nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;
    printf("[Mochila Lista] Item adicionado!\n");
}

void removerItemLista() {
    if (!mochilaLista) {
        printf("\n[Mochila Lista] Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\n[Mochila Lista] Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No *atual = mochilaLista, *anterior = NULL;
    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("[Mochila Lista] Item não encontrado!\n");
        return;
    }

    if (anterior)
        anterior->proximo = atual->proximo;
    else
        mochilaLista = atual->proximo;

    free(atual);
    printf("[Mochila Lista] Item removido!\n");
}

void listarLista() {
    if (!mochilaLista) {
        printf("\n[Mochila Lista] Mochila vazia!\n");
        return;
    }

    No* aux = mochilaLista;
    printf("\nItens na Lista Encadeada:\n");
    while (aux) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void buscarSequencialLista() {
    if (!mochilaLista) {
        printf("\n[Mochila Lista] Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\n[Mochila Lista] Nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    comparacoesSeq = 0;
    No* aux = mochilaLista;
    while (aux) {
        comparacoesSeq++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("Item encontrado! Tipo: %s | Quantidade: %d\n",
                   aux->dados.tipo, aux->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSeq);
            return;
        }
        aux = aux->proximo;
    }
    printf("Item não encontrado! Comparações: %d\n", comparacoesSeq);
}

//============================
// MENU GERAL
//============================

void menuVetor() {
    int op;
    do {
        printf("\n--- Mochila com Vetor ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("5 - Ordenar itens\n");
        printf("6 - Busca binária\n");
        printf("0 - Próxima estrutura\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }
    } while (op != 0);
}

void menuLista() {
    int op;
    do {
        printf("\n--- Mochila com Lista Encadeada ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarLista(); break;
            case 4: buscarSequencialLista(); break;
        }
    } while (op != 0);
}

int main() {
    printf("==== SISTEMA DE MOCHILA ====\n");
    printf("\nPrimeiro, será usada a mochila com VETOR.\n");
    menuVetor();

    printf("\nAgora, será usada a mochila com LISTA ENCADEADA.\n");
    menuLista();

    printf("\nComparação concluída.\n");
    printf("Vetores permitem ordenação e busca binária (mais rápida), mas têm tamanho fixo.\n");
    printf("Listas encadeadas são dinâmicas, porém as buscas são mais lentas.\n");
    printf("Fim do programa.\n");
    return 0;
}
