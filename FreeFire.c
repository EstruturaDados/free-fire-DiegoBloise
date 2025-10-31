#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    int id;
    char nome[50];
    int quantidade;
    char tipo[50];
    int prioridade;
} Item;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[MAX_ITENS];
int totalItens = 0;

// Limpar tela:
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela();

// Exibir Menu:
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu();

// Inserir Item:
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem();

// Remover Item:
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem();

// Listar Itens:
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens();

// Menu De Ordenacao:
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao();

// Insertion Sort:
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort();

// Busca Binaria Por Nome:
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome();

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
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
                //menuDeOrdenacao();
                break;
            case 5:
                //buscaBinariaPorNome();
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}

void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void exibirMenu() {
    printf("===== MOCHILA DO PLANO DE FUGA =====\n");
    printf("------------------------------------\n");
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome (busca binaria)\n");
    printf("0. Sair\n");
    printf("------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("A mochila esta cheia!\n");
        return;
    }

    Item novo;
    novo.id = totalItens + 1;

    getchar(); // limpar buffer
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
    if (novo.prioridade < 1) novo.prioridade = 1;
    if (novo.prioridade > 5) novo.prioridade = 5;

    mochila[totalItens++] = novo;

    printf("Item inserido com sucesso!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    getchar();
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
        printf("Item nao encontrado!\n");
        return;
    }

    for (int i = encontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;
    printf("Item removido com sucesso!\n");
}

void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n===== ITENS NA MOCHILA =====\n");
    printf("%-3s | %-15s | %-10s | %-5s | %-10s\n", "ID", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-3d | %-15s | %-10s | %-5d | %-10d\n",
               mochila[i].id, mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-------------------------------------------------------\n");
}