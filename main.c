#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "instalacoes.h"

const char* nome_tipo_instalacao(TipoInstalacao tipo) {
    switch (tipo) {
        case INST_RESIDENCIAL: return "Residencial";
        case INST_COMERCIAL: return "Comercial";
        case INST_INDUSTRIAL: return "Industrial";
        case INST_SERVICO_ESSENCIAL: return "Servico Essencial";
        default: return "Desconhecido";
    }
}

void menu_instalacoes(NoAVL **raiz) {
    int opcao;
    do {
        printf("\n--- GERENCIAR INSTALACOES (MODULO 1) ---\n");
        printf("1. Cadastrar instalacao\n");
        printf("2. Buscar instalacao por UC\n");
        printf("3. Atualizar instalacao\n");
        printf("4. Remover instalacao\n");
        printf("5. Listar instalacoes sem energia (Total: %d)\n", contar_instalacoes_sem_energia(*raiz));
        printf("6. Listar instalacoes por tipo\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (opcao == 1) {
            Instalacao *nova = (Instalacao*) malloc(sizeof(Instalacao));
            if (nova == NULL) {
                printf("Erro de alocacao de memoria!\n");
                continue;
            }

            int tipo_int;
            printf("Numero da UC: ");
            scanf("%d", &nova->uc);
            printf("Nome do titular: ");
            scanf(" %99[^\n]", nova->nome_titular);
            printf("Tipo (1-Residencial, 2-Comercial, 3-Industrial, 4-Servico Essencial): ");
            scanf("%d", &tipo_int);

            nova->tipo = (TipoInstalacao) tipo_int;
            nova->status = INST_COM_ENERGIA; // Toda instalacao comeca com energia

            int sucesso = 0;
            *raiz = inserir_instalacao(*raiz, nova, &sucesso);
            if (sucesso) {
                printf("Instalacao UC %d cadastrada com sucesso!\n", nova->uc);
            } else {
                printf("Erro: Ja existe uma instalacao com a UC %d!\n", nova->uc);
                free(nova); // Evita vazamento de memoria se a insercao falhar
            }

        } else if (opcao == 2) {
            int uc;
            printf("Digite a UC para busca: ");
            scanf("%d", &uc);
            Instalacao *inst = buscar_instalacao(*raiz, uc);
            if (inst != NULL) {
                printf("\n[Encontrada] UC: %d | Titular: %s | Tipo: %s | Status: %s\n",
                       inst->uc, inst->nome_titular, nome_tipo_instalacao(inst->tipo),
                       inst->status == INST_COM_ENERGIA ? "Com energia" : "Sem energia");
            } else {
                printf("Instalacao UC %d nao encontrada.\n", uc);
            }

        } else if (opcao == 3) {
            int uc, tipo_int;
            char novo_titular[100];
            printf("Digite a UC para atualizar: ");
            scanf("%d", &uc);
            printf("Novo nome do titular: ");
            scanf(" %99[^\n]", novo_titular);
            printf("Novo tipo (1-Residencial, 2-Comercial, 3-Industrial, 4-Servico Essencial): ");
            scanf("%d", &tipo_int);

            if (atualizar_instalacao(*raiz, uc, novo_titular, (TipoInstalacao) tipo_int)) {
                printf("Instalacao atualizada com sucesso!\n");
            } else {
                printf("Instalacao UC %d nao encontrada.\n", uc);
            }

        } else if (opcao == 4) {
            int uc, sucesso = 0;
            printf("Digite a UC para remover: ");
            scanf("%d", &uc);
            *raiz = remover_instalacao(*raiz, uc, &sucesso);
            if (sucesso) {
                printf("Instalacao UC %d removida com sucesso!\n", uc);
            } else {
                printf("Instalacao UC %d nao encontrada.\n", uc);
            }

        } else if (opcao == 5) {
            printf("\n--- INSTALACOES SEM ENERGIA ---\n");
            listar_instalacoes_sem_energia(*raiz);

        } else if (opcao == 6) {
            int tipo_int;
            printf("Tipo (1-Residencial, 2-Comercial, 3-Industrial, 4-Servico Essencial): ");
            scanf("%d", &tipo_int);
            printf("\n--- INSTALACOES DO TIPO %s ---\n", nome_tipo_instalacao((TipoInstalacao) tipo_int));
            listar_instalacoes_por_tipo(*raiz, (TipoInstalacao) tipo_int);
        }
    } while (opcao != 0);
}

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
                printf("\n[Proximo passo: Implementar Modulo 2 - abrir_chamado()]\n");
                break;
            case 2:
                printf("\n[Proximo passo: Implementar Modulo 2 - buscar_chamado_por_uc()]\n");
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
                printf("\n[Proximo passo: Implementar Modulo 3 - despachar_chamado()]\n");
                break;
            case 2:
                printf("\n[Proximo passo: Implementar Modulo 3 - listar_equipes_em_atendimento()]\n");
                break;
            case 3:
                printf("\n[Proximo passo: Implementar Modulo 4 - encerrar_atendimento()]\n");
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_cadastros_historico(NoAVL **arvore_instalacoes) {
    int opcao;
    do {
        printf("\n=== GESTAO E HISTORICO ===\n");
        printf("1. Gerenciar Instalacoes (Cadastrar / Buscar / Editar / Remover)\n");
        printf("2. Cadastrar nova Equipe\n");
        printf("3. Navegar pelo Historico de Chamados\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menu_instalacoes(arvore_instalacoes);
                break;
            case 2:
                printf("\n[Proximo passo: Implementar Modulo 3 - cadastrar_equipe()]\n");
                break;
            case 3:
                printf("\n[Proximo passo: Implementar Modulo 4 - exibir_historico()]\n");
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
    NoAVL *arvore_instalacoes = NULL;

    do {
        printf("\n==================================================\n");
        printf("   SISTEMA DE DESPACHO - REDE ELETRICA (CEEE)\n");
        printf("==================================================\n");
        printf("1. Fase de Abertura (Operador de Atendimento)\n");
        printf("2. Fase de Atendimento (Coordenador de Despacho)\n");
        printf("3. Gestao de Cadastros e Historico\n");
        printf("0. Encerrar Sistema\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                menu_abertura();
                break;
            case 2:
                menu_atendimento();
                break;
            case 3:
                menu_cadastros_historico(&arvore_instalacoes);
                break;
            case 0:
                printf("\nEncerrando o sistema e liberando memoria...\n");
                liberar_arvore_instalacoes(arvore_instalacoes);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}