#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


typedef enum {
    INST_RESIDENCIAL = 1,
    INST_COMERCIAL,
    INST_INDUSTRIAL,
    INST_SERVICO_ESSENCIAL
} TipoInstalacao;

typedef enum {
    INST_COM_ENERGIA = 1,
    INST_SEM_ENERGIA
} StatusInstalacao;

typedef enum {
    EQP_LINHA_VIVA = 1,
    EQP_REDE
} TipoEquipe;

typedef enum {
    EQP_DISPONIVEL = 1,
    EQP_EM_ATENDIMENTO
} StatusEquipe;

typedef enum {
    CHM_FIO_CAIDO = 1,
    CHM_POSTE_DANIFICADO,
    CHM_TRANSFORMADOR_DEFEITO,
    CHM_FALTA_ENERGIA
} TipoChamado;

typedef enum {
    URGENCIA_RISCO_VIDA = 1,
    URGENCIA_SERVICO_ESSENCIAL = 2,
    URGENCIA_DEMAIS_CASOS = 3
} UrgenciaChamado;

typedef enum {
    STATUS_CHM_ABERTO = 1,
    STATUS_CHM_EM_ATENDIMENTO,
    STATUS_CHM_CONCLUIDO,
    STATUS_CHM_CANCELADO
} StatusChamado;

// DECLARAÇÃO PRÉVIA (FORWARD DECLARATION)
typedef struct chamado Chamado;

// ESTRUTURAS DE DADOS (ENTIDADES)

typedef struct {
    int uc;
    char nome_titular[100];
    TipoInstalacao tipo;
    StatusInstalacao status;
} Instalacao;

typedef struct equipe {
    char nome[50];
    TipoEquipe tipo;
    StatusEquipe status;
    Chamado *chamado_em_atendimento; 
} Equipe;

struct chamado {
    int uc_instalacao;           // Apenas o número da UC
    TipoChamado tipo;
    UrgenciaChamado urgencia;
    char nome_equipe[50];        // Apenas o nome da equipe responsável
    StatusChamado status;
};

#endif // ESTRUTURAS_H
