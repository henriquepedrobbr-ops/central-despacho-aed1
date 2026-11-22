#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instalacoes.h"

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int altura_no(NoAVL *no) {
    return (no == NULL) ? 0 : no->altura;
}

static int fator_balanceamento(NoAVL *no) {
    return (no == NULL) ? 0 : altura_no(no->esq) - altura_no(no->dir);
}

static NoAVL* criar_no_avl(Instalacao *inst) {
    NoAVL *novo = (NoAVL*) malloc(sizeof(NoAVL));
    if (novo != NULL) {
        novo->dados = inst;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 1;
    }
    return novo;
}

static NoAVL* rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura_no(y->esq), altura_no(y->dir)) + 1;
    x->altura = max(altura_no(x->esq), altura_no(x->dir)) + 1;

    return x;
}

static NoAVL* rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura_no(x->esq), altura_no(x->dir)) + 1;
    y->altura = max(altura_no(y->esq), altura_no(y->dir)) + 1;

    return y;
}

static NoAVL* menor_valor_no(NoAVL *no) {
    NoAVL *atual = no;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

NoAVL* inserir_instalacao(NoAVL *raiz, Instalacao *nova_inst, int *sucesso) {
    if (raiz == NULL) {
        *sucesso = 1;
        return criar_no_avl(nova_inst);
    }

    if (nova_inst->uc < raiz->dados->uc) {
        raiz->esq = inserir_instalacao(raiz->esq, nova_inst, sucesso);
    } else if (nova_inst->uc > raiz->dados->uc) {
        raiz->dir = inserir_instalacao(raiz->dir, nova_inst, sucesso);
    } else {
        *sucesso = 0; // Bloqueia UC duplicada
        return raiz;
    }

    raiz->altura = 1 + max(altura_no(raiz->esq), altura_no(raiz->dir));
    int fb = fator_balanceamento(raiz);

    if (fb > 1 && nova_inst->uc < raiz->esq->dados->uc)
        return rotacao_direita(raiz);

    if (fb < -1 && nova_inst->uc > raiz->dir->dados->uc)
        return rotacao_esquerda(raiz);

    if (fb > 1 && nova_inst->uc > raiz->esq->dados->uc) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && nova_inst->uc < raiz->dir->dados->uc) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

Instalacao* buscar_instalacao(NoAVL *raiz, int uc) {
    if (raiz == NULL) return NULL;

    if (uc == raiz->dados->uc) {
        return raiz->dados;
    } else if (uc < raiz->dados->uc) {
        return buscar_instalacao(raiz->esq, uc);
    } else {
        return buscar_instalacao(raiz->dir, uc);
    }
}

int atualizar_instalacao(NoAVL *raiz, int uc, const char *novo_titular, TipoInstalacao novo_tipo) {
    Instalacao *inst = buscar_instalacao(raiz, uc);
    if (inst == NULL) return 0;

    strncpy(inst->nome_titular, novo_titular, sizeof(inst->nome_titular) - 1);
    inst->nome_titular[sizeof(inst->nome_titular) - 1] = '\0';
    inst->tipo = novo_tipo;
    return 1;
}

NoAVL* remover_instalacao(NoAVL *raiz, int uc, int *sucesso) {
    if (raiz == NULL) {
        *sucesso = 0;
        return raiz;
    }

    if (uc < raiz->dados->uc) {
        raiz->esq = remover_instalacao(raiz->esq, uc, sucesso);
    } else if (uc > raiz->dados->uc) {
        raiz->dir = remover_instalacao(raiz->dir, uc, sucesso);
    } else {
        *sucesso = 1;

        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            NoAVL *temp = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz->dados);
            free(raiz);
            return temp;
        } else {
            NoAVL *temp = menor_valor_no(raiz->dir);

            // Troca apenas os ponteiros (nunca copia a struct inteira)
            Instalacao *aux = raiz->dados;
            raiz->dados = temp->dados;
            temp->dados = aux;

            raiz->dir = remover_instalacao(raiz->dir, temp->dados->uc, sucesso);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(altura_no(raiz->esq), altura_no(raiz->dir));
    int fb = fator_balanceamento(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) >= 0)
        return rotacao_direita(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) < 0) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->dir) <= 0)
        return rotacao_esquerda(raiz);

    if (fb < -1 && fator_balanceamento(raiz->dir) > 0) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

void listar_instalacoes_sem_energia(NoAVL *raiz) {
    if (raiz == NULL) return;

    listar_instalacoes_sem_energia(raiz->esq);
    if (raiz->dados->status == INST_SEM_ENERGIA) {
        printf("UC: %d | Titular: %s | Tipo: %d\n",
               raiz->dados->uc, raiz->dados->nome_titular, raiz->dados->tipo);
    }
    listar_instalacoes_sem_energia(raiz->dir);
}

int contar_instalacoes_sem_energia(NoAVL *raiz) {
    if (raiz == NULL) return 0;

    int atual = (raiz->dados->status == INST_SEM_ENERGIA) ? 1 : 0;
    return atual + contar_instalacoes_sem_energia(raiz->esq) + contar_instalacoes_sem_energia(raiz->dir);
}

void listar_instalacoes_por_tipo(NoAVL *raiz, TipoInstalacao tipo) {
    if (raiz == NULL) return;

    listar_instalacoes_por_tipo(raiz->esq, tipo);
    if (raiz->dados->tipo == tipo) {
        printf("UC: %d | Titular: %s | Status: %s\n",
               raiz->dados->uc,
               raiz->dados->nome_titular,
               raiz->dados->status == INST_COM_ENERGIA ? "Com energia" : "Sem energia");
    }
    listar_instalacoes_por_tipo(raiz->dir, tipo);
}

void liberar_arvore_instalacoes(NoAVL *raiz) {
    if (raiz == NULL) return;

    liberar_arvore_instalacoes(raiz->esq);
    liberar_arvore_instalacoes(raiz->dir);

    free(raiz->dados);
    free(raiz);
}