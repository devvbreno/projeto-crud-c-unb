#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/view.h"
#include "../include/model.h"

// ESPAÇO DE GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---
// --- FUNÇÕES AUXILIARES (PRIVADAS AO ARQUIVO) ---

// Limpa buffer e remove o \n do final
void ler_texto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// Valida se o ano é bissexto
int eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Valida formato e existência da data
int validar_data(char *data) {
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') return 0;
    
    int dia = atoi(data);
    int mes = atoi(data + 3);
    int ano = atoi(data + 6);

    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;

    int dias_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && eh_bissexto(ano)) dias_mes[2] = 29;

    if (dia < 1 || dia > dias_mes[mes]) return 0;

    return 1;
}

// --- MENUS DO MEMBRO 1 ---

void listar_todos_clientes(Cliente *lista) {
    if (lista == NULL) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }
    printf("\n--- LISTA DE CLIENTES ---\n");
    Cliente *atual = lista;
    while (atual != NULL) {
        printf("CPF: %s | Nome: %s\n", atual->cpf, atual->nome);
        printf("E-mail: %s | Nasc: %s | Tel: %s\n", atual->email, atual->data_nasc, atual->telefone);
        printf("----------------------------------------------------\n");
        atual = atual->prox;
    }
}

void menu_cadastrar_cliente(Cliente **lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];

    printf("\n--- NOVO CLIENTE ---\n");
    printf("CPF: ");
    ler_texto(cpf, 15);

    if (buscar_cliente(*lista, cpf) != NULL) {
        printf("Erro: CPF ja cadastrado!\n");
        return;
    }

    printf("Nome: ");
    ler_texto(nome, 50);

    printf("E-mail: ");
    ler_texto(email, 80);

    do {
        printf("Data de Nascimento (DD/MM/AAAA): ");
        ler_texto(data, 15);
        if (!validar_data(data)) {
            printf("Erro: Data invalida! Verifique dias, meses e ano bissexto.\n");
        }
    } while (!validar_data(data));

    printf("Telefone: ");
    ler_texto(tel, 15);

    adicionar_cliente(lista, cpf, nome, email, data, tel);
    printf(">> Cliente cadastrado com sucesso!\n");
}

void menu_editar_cliente_view(Cliente *lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];
    
    printf("\n--- EDITAR CLIENTE ---\n");
    printf("Informe o CPF do cliente: ");
    ler_texto(cpf, 15);

    if (buscar_cliente(lista, cpf) == NULL) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    printf("Novos Dados (Digite para substituir):\n");
    printf("Novo Nome: "); ler_texto(nome, 50);
    printf("Novo E-mail: "); ler_texto(email, 80);
    
    do {
        printf("Nova Data (DD/MM/AAAA): ");
        ler_texto(data, 15);
    } while (!validar_data(data));

    printf("Novo Telefone: "); ler_texto(tel, 15);

    editar_cliente(lista, cpf, nome, email, data, tel);
    printf(">> Dados atualizados!\n");
}

void menu_remover_cliente_view(Cliente **lista) {
    char cpf[15];
    printf("\n--- REMOVER CLIENTE ---\n");
    printf("Informe o CPF: ");
    ler_texto(cpf, 15);

    if (remover_cliente(lista, cpf)) {
        printf(">> Cliente removido com sucesso!\n");
    } else {
        printf("Erro: Cliente nao encontrado.\n");
    }
}

// Menu Principal deste módulo
void menu_gerenciar_clientes(Cliente **lista) {
    int opcao;
    do {
        printf("\n=== GESTAO DE CLIENTES ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch(opcao) {
            case 1: menu_cadastrar_cliente(lista); break;
            case 2: listar_todos_clientes(*lista); break;
            case 3: menu_editar_cliente_view(*lista); break;
            case 4: menu_remover_cliente_view(lista); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
