#include <stdio.h>
#include "../include/view.h"

// ESPAÇO DE GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---
// Função auxiliar apenas para ler string (limpa o buffer)
void ler_texto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    // Remove o \n do final se existir
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

void menu_cadastrar_cliente(Cliente **lista) {
    char cpf[15], nome[50], telefone[15];

    printf("\n--- Novo Cliente ---\n");
    
    printf("Digite o CPF: ");
    ler_texto(cpf, 15);
    
    // Validacao simples: verificar se já existe
    if (buscar_cliente(*lista, cpf) != NULL) {
        printf("Erro: CPF ja cadastrado!\n");
        return;
    }

    printf("Digite o Nome: ");
    ler_texto(nome, 50);

    printf("Digite o Telefone: ");
    ler_texto(telefone, 15);

    // CHAMA A MODEL PARA FAZER O TRABALHO SUJO
    adicionar_cliente(lista, cpf, nome, telefone);
    printf("Cliente cadastrado com sucesso!\n");
}

void menu_listar_clientes(Cliente *lista) {
    printf("\n--- Lista de Clientes ---\n");
    Cliente *atual = lista;
    while (atual != NULL) {
        // Aqui o printf é permitido!
        printf("CPF: %s | Nome: %s | Tel: %s\n", atual->cpf, atual->nome, atual->telefone);
        atual = atual->prox;
    }
}
