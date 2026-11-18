#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
// Inclusao dos modulos (os arquivos .h devem declarar as funcoes que serao chamadas aqui)
// #include "instalacoes.h"
// #include "chamados.h"
// #include "equipes.h"
// #include "historico.h"

void menu_abertura() {
    int opcao;
    do {
        printf("\n=== FASE DE ABERTURA (Atendimento ao Cliente) ===\n");
        printf("1. Receber ligacao (Abrir novo chamado)\n");
        printf("2. Consultar se chamado ja existe (Por UC)\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_atendimento() {
    int opcao;
    do {
        printf("\n=== FASE DE ATENDIMENTO (Despacho de Equipes) ===\n");
        printf("1. Despachar equipe para o chamado mais urgente\n");
        printf("2. Acompanhar equipes em atendimento\n");
        printf("3. Encerrar atendimento de uma equipe\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_cadastros_historico() {
    int opcao;
    do {
        printf("\n=== GESTAO E HISTORICO ===\n");
        printf("1. Cadastrar nova Instalacao\n");
        printf("2. Cadastrar nova Equipe\n");
        printf("3. Navegar pelo Historico de Chamados\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:;
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    int opcao;

    // Aqui voce inicializara as estruturas de dados no futuro
    // ex: inicializar_hash_instalacoes();
    // ex: inicializar_filas_chamados();

    do {
        printf("\n==================================================\n");
        printf("   SISTEMA DE DESPACHO - REDE ELETRICA (CEEE)\n");
        printf("==================================================\n");
        printf("1. Fase de Abertura (Operador de Atendimento)\n");
        printf("2. Fase de Atendimento (Coordenador de Despacho)\n");
        printf("3. Gestao de Cadastros e Historico\n");
        printf("0. Encerrar Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menu_abertura();
                break;
            case 2:
                menu_atendimento();
                break;
            case 3:
                menu_cadastros_historico();
                break;
            case 0:
                printf("\nEncerrando o sistema. Salvando dados...\n");
                // Aqui voce chamara as funcoes para liberar a memoria alocada (free)
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}