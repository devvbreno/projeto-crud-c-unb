#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/model.h" // Importa o seu contrato

// --- IMPLEMENTAÇÃO DO GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---

// Função para adicionar cliente no final da lista
void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *telefone) {
    // 1. Alocar memória para o novo cliente
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (novo == NULL) {
        return; // Falha na alocação (sem memória)
    }

    // 2. Preencher os dados
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->prox = NULL; // Ele será o último, então aponta para o nada

    // 3. Inserir na lista
    if (*lista == NULL) {
        // Se a lista está vazia, o novo é o primeiro
        *lista = novo;
    } else {
        // Se não, percorre até o fim e adiciona
        Cliente *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Função para buscar um cliente pelo CPF (Retorna o ponteiro ou NULL)
Cliente* buscar_cliente(Cliente *lista, char *cpf) {
    Cliente *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            return atual; // Encontrou! Retorna o endereço dele
        }
        atual = atual->prox;
    }
    return NULL; // Chegou ao fim e não achou
}

// Remove um cliente pelo CPF
void remover_cliente(Cliente **lista, char *cpf) {
    // Se a lista estiver vazia, não faz nada
    if (*lista == NULL) {
        return;
    }

    Cliente *atual = *lista;
    Cliente *anterior = NULL;

    // Procura o cliente na lista
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se chegou no fim e não achou (atual é NULL)
    if (atual == NULL) {
        return; 
    }

    // Lógica de remoção ("Costura" dos ponteiros)
    if (anterior == NULL) {
        // CASO 1: O cliente a remover é o PRIMEIRO da lista
        // O início da lista passa a ser o segundo elemento
        *lista = atual->prox;
    } else {
        // CASO 2: O cliente está no MEIO ou no FIM
        // O anterior pula o atual e aponta para o próximo
        anterior->prox = atual->prox;
    }

    // IMPORTANTE: Liberar a memória do nó removido
    free(atual);
}

// Edita nome e telefone de um cliente existente
// Retorna 1 se editou, 0 se não encontrou (para controle de erro na View)
int editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_telefone) {
    // Reutilizamos a função de busca que você já fez!
    Cliente *alvo = buscar_cliente(lista, cpf);
    
    if (alvo != NULL) {
        strcpy(alvo->nome, novo_nome);
        strcpy(alvo->telefone, novo_telefone);
        return 1; // Sucesso
    }
    return 0; // Não achou
}

