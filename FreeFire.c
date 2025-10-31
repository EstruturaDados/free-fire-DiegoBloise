// ============================================================================
//             PROJETO: SISTEMA DE INVENTÁRIO FREE FIRE (NÍVEL AVENTUREIRO)
// ============================================================================
//
// OBJETIVOS:
// - Gerenciar dinamicamente a mochila do jogador (até 10 itens).
// - Inserção, remoção e listagem de componentes.
// - Ordenação por critérios (nome, tipo, prioridade) usando Insertion Sort.
// - Busca binária por nome com verificação de ordenação.
// - Foco em design, clareza, modularização e documentação.
//
// AUTOR: Diego Bloise
// DATA: Outubro de 2025
// LINGUAGEM: C (padrão C99)
// COMPILAÇÃO (exemplo):
//     gcc ilha.c -o ilha
//
// EXECUÇÃO:
//     ./ilha
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
//                          CONSTANTES E ESTRUTURAS
// ============================================================================

#define MAX_ITENS 10

/** @enum CriterioOrdenacao
 *  @brief Define os critérios possíveis de ordenação.
 */
typedef enum {
    ORDENAR_POR_NOME = 1,
    ORDENAR_POR_TIPO,
    ORDENAR_POR_PRIORIDADE
} CriterioOrdenacao;

/** @struct Item
 *  @brief Representa um item coletado durante o plano de fuga.
 */
typedef struct {
    int id;
    char nome[50];
    int quantidade;
    char tipo[50];
    int prioridade;
} Item;

// Vetor principal da mochila
Item mochila[MAX_ITENS];
int totalItens = 0;

// Controle de estado
int comparacoes = 0;
bool ordenadaPorNome = false;

// ============================================================================
//                          PROTÓTIPOS DE FUNÇÕES
// ============================================================================

// Utilitárias
void limparTela();
void pausar();
void limparBufferEntrada();

// Núcleo do jogo
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);
void buscaBinariaPorNome();

// ============================================================================
//                           FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    int opcao;

    do {
        limparTela();
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        limparTela();
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

        pausar();
    } while (opcao != 0);

    return 0;
}

// ============================================================================
//                            FUNÇÕES UTILITÁRIAS
// ============================================================================

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    limparBufferEntrada();
}

// ============================================================================
//                           FUNÇÕES DE INTERFACE
// ============================================================================

void exibirMenu() {
    printf("==============================================\n");
    printf("           MOCHILA DE SOBREVIVÊNCIA           \n");
    printf("==============================================\n\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Buscar item por nome (busca binária)\n");
    printf("0 - Sair\n");
    printf("----------------------------------------------\n");
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "SIM" : "NÃO");
    printf("----------------------------------------------\n");
    printf("Escolha uma opção: ");
}

// ============================================================================
//                           FUNÇÕES PRINCIPAIS
// ============================================================================

/**
 * @brief Adiciona um novo item à mochila.
 */
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("A mochila está cheia!\n");
        return;
    }

    Item novo;
    novo.id = totalItens + 1;

    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite o tipo do item: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);
    limparBufferEntrada();

    if (novo.prioridade < 1) novo.prioridade = 1;
    if (novo.prioridade > 5) novo.prioridade = 5;

    mochila[totalItens++] = novo;
    ordenadaPorNome = false;

    printf("\nItem inserido com sucesso!\n");
}

/**
 * @brief Remove um item da mochila pelo nome.
 */
void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeRemover[50];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = encontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;
    printf("Item removido com sucesso!\n");
}

/**
 * @brief Lista todos os itens armazenados na mochila.
 */
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n==================== ITENS NA MOCHILA ====================\n");
    printf("%-3s | %-20s | %-12s | %-8s | %-10s\n", "ID", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-3d | %-20s | %-12s | %-8d | %-10d\n",
               mochila[i].id, mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("----------------------------------------------------------\n");
}

/**
 * @brief Exibe o menu de ordenação e chama o Insertion Sort.
 */
void menuDeOrdenacao() {
    int opcao;
    printf("Escolha o critério de ordenação:\n");
    printf("1 - Nome (A-Z)\n");
    printf("2 - Tipo (A-Z)\n");
    printf("3 - Prioridade (Maior → Menor)\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    limparBufferEntrada();

    if (opcao < 1 || opcao > 3) {
        printf("Critério inválido!\n");
        return;
    }

    comparacoes = 0;
    insertionSort(opcao);
    printf("\nItens ordenados com sucesso!\n");
    printf("Comparações realizadas: %d\n", comparacoes);

    if (opcao == ORDENAR_POR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;
}

/**
 * @brief Ordena a mochila pelo critério selecionado usando Insertion Sort.
 */
void insertionSort(CriterioOrdenacao criterio) {
    for (int i = 1; i < totalItens; i++) {
        Item atual = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            bool cond = false;

            if (criterio == ORDENAR_POR_NOME)
                cond = strcmp(mochila[j].nome, atual.nome) > 0;
            else if (criterio == ORDENAR_POR_TIPO)
                cond = strcmp(mochila[j].tipo, atual.tipo) > 0;
            else if (criterio == ORDENAR_POR_PRIORIDADE)
                cond = mochila[j].prioridade < atual.prioridade;

            if (!cond)
                break;

            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = atual;
    }
}

/**
 * @brief Realiza uma busca binária pelo nome do item.
 */
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila precisa estar ordenada por nome para busca binária!\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int ini = 0, fim = totalItens - 1;
    int achou = -1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;

        int cmp = strcmp(nomeBusca, mochila[meio].nome);
        if (cmp == 0) {
            achou = meio;
            break;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }

    printf("\nComparações realizadas: %d\n", comparacoes);

    if (achou == -1)
        printf("Item '%s' não encontrado!\n", nomeBusca);
    else {
        printf("\nItem encontrado!\n");
        printf("%-3s | %-20s | %-12s | %-8s | %-10s\n", "ID", "Nome", "Tipo", "Qtd", "Prioridade");
        printf("----------------------------------------------------------\n");
        printf("%-3d | %-20s | %-12s | %-8d | %-10d\n",
               mochila[achou].id, mochila[achou].nome, mochila[achou].tipo,
               mochila[achou].quantidade, mochila[achou].prioridade);
    }
}
