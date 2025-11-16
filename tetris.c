#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

/* Estrutura básica da peça */
typedef struct {
    char nome;
    int id;
} Peca;

/* Estruturas de dados */
Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];
int inicio = 0, fim = 0, qtdFila = 0;
int topo = -1;
int proximoID = 0;

/* Gera uma peça com tipo aleatório e ID único */
Peca gerarPeca() {
    char tipos[4] = { 'I', 'O', 'T', 'L' };
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proximoID++;
    return p;
}

/* Funções auxiliares */
int filaCheia()  { return qtdFila == TAM_FILA; }
int filaVazia()  { return qtdFila == 0; }
int pilhaCheia() { return topo == TAM_PILHA - 1; }
int pilhaVazia() { return topo == -1; }

/* Operações da fila */
void enqueue(Peca p) {
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
    qtdFila++;
}

Peca dequeue() {
    Peca vazio = { '-', -1 };
    if (filaVazia()) return vazio;

    Peca p = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    qtdFila--;
    return p;
}

/* Operações da pilha */
void push(Peca p) {
    pilha[++topo] = p;
}

Peca pop() {
    Peca vazio = { '-', -1 };
    if (pilhaVazia()) return vazio;
    return pilha[topo--];
}

/* Exibe fila e pilha lado a lado */
void exibirEstado() {
    printf("\n----- ESTADO ATUAL -----\n");

    printf("Fila: ");
    if (filaVazia()) {
        printf("(vazia)");
    } else {
        int i = inicio;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }

    printf("\nPilha (Topo -> Base): ");
    if (pilhaVazia()) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n-------------------------\n");
}

/* Troca simples entre fila e pilha */
void trocaSimples() {
    if (filaVazia() || pilhaVazia()) {
        printf("Nao foi possivel trocar: fila ou pilha vazia.\n");
        return;
    }

    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;

    printf("Troca simples realizada.\n");
}

/* Troca múltipla 3x3 */
void trocaMultipla() {
    if (qtdFila < 3 || topo < 2) {
        printf("Nao e possivel realizar troca 3x3.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idx = (inicio + i) % TAM_FILA;
        Peca temp = fila[idx];
        fila[idx] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("Troca multipla realizada.\n");
}

/* Programa principal */
int main() {
    srand(time(NULL));

    /* Inicializa fila com 5 peças */
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;

    do {
        exibirEstado();

        printf("\nMenu de Opcoes:\n");
        printf("1 - Jogar peca da fila\n");
        printf("2 - Inserir nova peca na fila\n");
        printf("3 - Reservar peca (fila -> pilha)\n");
        printf("4 - Usar peca reservada (pilha)\n");
        printf("5 - Trocar frente da fila com topo da pilha\n");
        printf("6 - Troca multipla (3 da fila <-> 3 da pilha)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca p = dequeue();
                if (p.id == -1) {
                    printf("A fila esta vazia.\n");
                } else {
                    printf("Peca jogada: [%c %d]\n", p.nome, p.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 2:
                if (filaCheia()) {
                    printf("A fila esta cheia, nao e possivel inserir.\n");
                } else {
                    Peca p = gerarPeca();
                    enqueue(p);
                    printf("Peca inserida: [%c %d]\n", p.nome, p.id);
                }
                break;

            case 3:
                if (filaVazia()) {
                    printf("Nao ha peca para reservar.\n");
                } else if (pilhaCheia()) {
                    printf("A pilha esta cheia.\n");
                } else {
                    Peca p = dequeue();
                    push(p);
                    enqueue(gerarPeca());
                    printf("Peca reservada: [%c %d]\n", p.nome, p.id);
                }
                break;

            case 4: {
                Peca p = pop();
                if (p.id == -1) {
                    printf("A pilha esta vazia.\n");
                } else {
                    printf("Peca usada: [%c %d]\n", p.nome, p.id);
                }
                break;
            }

            case 5:
                trocaSimples();
                break;

            case 6:
                trocaMultipla();
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
