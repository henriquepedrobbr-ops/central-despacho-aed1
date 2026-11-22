#ifndef INSTALACOES_H
#define INSTALACOES_H

#include "estruturas.h"

typedef struct no_avl {
    Instalacao *dados;       // Ponteiro para a entidade alocada uma única vez
    struct no_avl *esq;
    struct no_avl *dir;
    int altura;
} NoAVL;

// Operações obrigatórias do Módulo 1
NoAVL* inserir_instalacao(NoAVL *raiz, Instalacao *nova_inst, int *sucesso);
Instalacao* buscar_instalacao(NoAVL *raiz, int uc);
int atualizar_instalacao(NoAVL *raiz, int uc, const char *novo_titular, TipoInstalacao novo_tipo);
NoAVL* remover_instalacao(NoAVL *raiz, int uc, int *sucesso);

// Consultas sugeridas do Módulo 1
void listar_instalacoes_sem_energia(NoAVL *raiz);
int contar_instalacoes_sem_energia(NoAVL *raiz);
void listar_instalacoes_por_tipo(NoAVL *raiz, TipoInstalacao tipo);

// Liberação de memória (evita vazamentos no Valgrind)
void liberar_arvore_instalacoes(NoAVL *raiz);

#endif 