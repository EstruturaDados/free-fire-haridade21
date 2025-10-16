#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 10
#define NOME_SIZE 30
#define TIPO_SIZE 20

typedef struct {
    char nome[NOME_SIZE];
    char tipo[TIPO_SIZE];
    int prioridade;
} Componente;

// --- Prototipos ---
void bubbleSortNome(Componente[], int, long *);
void insertionSortTipo(Componente[], int, long *);
void selectionSortPrioridade(Componente[], int, long *);
int buscaBinariaPorNome(Componente[], int, const char[], long *);
void mostrarComponentes(Componente[], int);
double medirTempo(void (*algoritmo)(Componente[], int, long *), Componente[], int, long *);
void trim_newline(char *);

// --- Funções de Utilidade ---
void trim_newline(char *s) {
    size_t L = strlen(s);
    if (L > 0 && s[L-1] == '\n') s[L-1] = '\0';
}

int lerInteiro() {
    char buf[64];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    return atoi(buf);
}

void copiaVetor(Componente dest[], Componente src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// --- Algoritmos de Ordenação ---
void bubbleSortNome(Componente arr[], int n, long *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

void insertionSortTipo(Componente arr[], int n, long *comparisons) {
    *comparisons = 0;
    for (int i = 1; i < n; i++) {
        Componente key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparisons)++;
            if (strcmp(arr[j].tipo, key.tipo) > 0)
                arr[j+1] = arr[j--];
            else break;
        }
        arr[j+1] = key;
    }
}

void selectionSortPrioridade(Componente arr[], int n, long *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            (*comparisons)++;
            if (arr[j].prioridade < arr[min_idx].prioridade)
                min_idx = j;
        }
        if (min_idx != i) {
            Componente tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

double medirTempo(void (*algoritmo)(Componente[], int, long *), Componente arr[], int n, long *comparisons) {
    Componente temp[MAX_COMPONENTES];
    copiaVetor(temp, arr, n);

    clock_t start = clock();
    algoritmo(temp, n, comparisons);
    clock_t end = clock();

    copiaVetor(arr, temp, n);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// --- Busca Binária ---
int buscaBinariaPorNome(Componente arr[], int n, const char target[], long *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        (*comparisons)++;
        int cmp = strcmp(arr[mid].nome, target);
        if (cmp == 0) return mid;
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// --- Exibir Inventário ---
void mostrarComponentes(Componente arr[], int n) {
    if (n == 0) {
        printf("\nInventário vazio.\n");
        return;
    }
    printf("\n--------------------------------------------------------------\n");
    printf(" #  | Nome                         | Tipo           | Prioridade\n");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%2d  | %-28s | %-14s | %d\n", i+1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("--------------------------------------------------------------\n");
}

// --- Programa Principal ---
int main() {
    Componente mochila[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    int ordenadoPorNome = 0;

    while (1) {
        printf("\n=================================================================\n");
        printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("=================================================================\n");
        printf("Itens na Mochila: %d/%d\n", qtd, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("-----------------------------------------------------------------\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("-----------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        opcao = lerInteiro();

        if (opcao == 0) {
            printf("\n Torre de Fuga ativada! Missão concluída.\n");
            break;
        }

        switch (opcao) {
            case 1: {
                if (qtd >= MAX_COMPONENTES) {
                    printf(" Mochila cheia! Descarte algo antes de adicionar.\n");
                    break;
                }
                printf("\nDigite o nome do componente: ");
                fgets(mochila[qtd].nome, sizeof(mochila[qtd].nome), stdin);
                trim_newline(mochila[qtd].nome);

                printf("Digite o tipo do componente: ");
                fgets(mochila[qtd].tipo, sizeof(mochila[qtd].tipo), stdin);
                trim_newline(mochila[qtd].tipo);

                printf("Digite a prioridade (1 a 10): ");
                mochila[qtd].prioridade = lerInteiro();

                qtd++;
                ordenadoPorNome = 0;
                printf(" Componente adicionado com sucesso!\n");
                break;
            }

            case 2: {
                if (qtd == 0) {
                    printf("Mochila vazia.\n");
                    break;
                }
                mostrarComponentes(mochila, qtd);
                printf("Digite o número do componente para descartar: ");
                int idx = lerInteiro();
                if (idx < 1 || idx > qtd) {
                    printf("Índice inválido.\n");
                    break;
                }
                for (int i = idx - 1; i < qtd - 1; i++)
                    mochila[i] = mochila[i + 1];
                qtd--;
                ordenadoPorNome = 0;
                printf("  Componente descartado.\n");
                break;
            }

            case 3: {
                mostrarComponentes(mochila, qtd);
                break;
            }

            case 4: {
                if (qtd == 0) {
                    printf("Nada para ordenar.\n");
                    break;
                }
                printf("\nEscolha o tipo de ordenação:\n");
                printf("1 - Por Nome (Bubble Sort)\n");
                printf("2 - Por Tipo (Insertion Sort)\n");
                printf("3 - Por Prioridade (Selection Sort)\n");
                printf("Opção: ");
                int tipo = lerInteiro();

                long comps = 0;
                double tempo = 0;

                switch (tipo) {
                    case 1:
                        tempo = medirTempo(bubbleSortNome, mochila, qtd, &comps);
                        ordenadoPorNome = 1;
                        printf("\nOrdenado por NOME (Bubble Sort)\n");
                        break;
                    case 2:
                        tempo = medirTempo(insertionSortTipo, mochila, qtd, &comps);
                        ordenadoPorNome = 0;
                        printf("\nOrdenado por TIPO (Insertion Sort)\n");
                        break;
                    case 3:
                        tempo = medirTempo(selectionSortPrioridade, mochila, qtd, &comps);
                        ordenadoPorNome = 0;
                        printf("\nOrdenado por PRIORIDADE (Selection Sort)\n");
                        break;
                    default:
                        printf("Opção inválida.\n");
                        continue;
                }
                printf("Comparações: %ld | Tempo: %.6f segundos\n", comps, tempo);
                mostrarComponentes(mochila, qtd);
                break;
            }

            case 5: {
                if (!ordenadoPorNome) {
                    printf(" A busca binária só funciona após ordenar por nome.\n");
                    break;
                }
                printf("Digite o nome do componente-chave: ");
                char chave[NOME_SIZE];
                fgets(chave, sizeof(chave), stdin);
                trim_newline(chave);

                long comps = 0;
                int idx = buscaBinariaPorNome(mochila, qtd, chave, &comps);

                if (idx >= 0) {
                    printf("\n Componente-Chave encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                           mochila[idx].nome, mochila[idx].tipo, mochila[idx].prioridade);
                    printf("Comparações na busca: %ld\n", comps);
                    printf("Torre de Fuga pode ser ativada!\n");
                } else {
                    printf(" Componente não encontrado. Comparações: %ld\n", comps);
                }
                break;
            }

            default:
                printf("Opção inválida.\n");
                break;
        }
    }
    return 0;
}
