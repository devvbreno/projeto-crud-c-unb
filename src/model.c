#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/model.h" // Importa o seu contrato

// --- IMPLEMENTAÇÃO DO GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---

void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *email, char *data_nasc, char *telefone) {
    // 1. Alocação Dinâmica (Obrigatório)
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (novo == NULL) return; // Falha de memória

    // 2. Cópia segura dos dados
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->data_nasc, data_nasc);
    strcpy(novo->telefone, telefone);
    novo->prox = NULL;

    // 3. Inserção na lista
    if (*lista == NULL) {
        *lista = novo; // Lista estava vazia
    } else {
        Cliente *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox; // Caminha até o fim
        }
        atual->prox = novo;
    }
}

Cliente* buscar_cliente(Cliente *lista, char *cpf) {
    Cliente *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            return atual; // Encontrou
        }
        atual = atual->prox;
    }
    return NULL; // Não achou
}

int remover_cliente(Cliente **lista, char *cpf) {
    if (*lista == NULL) return 0;

    Cliente *atual = *lista;
    Cliente *anterior = NULL;

    // Procura o elemento
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0; // Não encontrou

    // Ajusta os ponteiros ("costura" a lista)
    if (anterior == NULL) {
        *lista = atual->prox; // Removeu o primeiro (cabeça)
    } else {
        anterior->prox = atual->prox; // Removeu do meio/fim
    }

    free(atual); // Libera memória (Obrigatório)
    return 1; // Sucesso
}

int editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_email, char *nova_data, char *novo_telefone) {
    Cliente *alvo = buscar_cliente(lista, cpf);
    if (alvo != NULL) {
        strcpy(alvo->nome, novo_nome);
        strcpy(alvo->email, novo_email);
        strcpy(alvo->data_nasc, nova_data);
        strcpy(alvo->telefone, novo_telefone);
        return 1; // Sucesso
    }
    return 0; // Erro
}

void liberar_lista_clientes(Cliente **lista) {
    Cliente *atual = *lista;
    Cliente *prox_node;
    while (atual != NULL) {
        prox_node = atual->prox;
        free(atual);
        atual = prox_node;
    }
    *lista = NULL;
}

// ESPAÇO PARA GERENCIAMENTO DE PRODUTOS: ABRAÃO PEREIRA DIAS - 202045384 ---

// --- IMPLEMENTAÇÃO DO MEMBRO 2 ---

void adicionar_produto(Produto **lista, int codigo, char *nome, float preco) {
    // 1. Alocação Dinâmica (Obrigatório)
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    if (novo == NULL) return;

    // 2. Preenchimento
    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    novo->preco = preco;
    novo->prox = NULL;

    // 3. Inserção no final da lista
    if (*lista == NULL) {
        *lista = novo;
    } else {
        Produto *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Busca por código numérico
Produto* buscar_produto(Produto *lista, int codigo) {
    Produto *atual = lista;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// Edita dados de um produto existente
int editar_produto(Produto *lista, int codigo, char *novo_nome, float novo_preco) {
    Produto *alvo = buscar_produto(lista, codigo);
    if (alvo != NULL) {
        strcpy(alvo->nome, novo_nome);
        alvo->preco = novo_preco; // Atualiza o float
        return 1; // Sucesso
    }
    return 0; // Não encontrado
}

// A função remover_produto segue a mesma lógica de ponteiros do gerenciamento de clientes,
// apenas trocando a comparação de strings (strcmp) pela comparação de inteiros (==).


// Gerenciamento do sistema - Modo Compra (Breno Elias)


void liberar_sistema(Cliente **lista_c, Produto **lista_p) {
    liberar_lista_clientes(lista_c); // chama a parte do Samuel
    liberar_lista_produtos(lista_p); // chama a parte do Abraão
}
