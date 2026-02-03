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

// --- ESPAÇO DE GERENCIAMENTO DE PRODUTOS: Abraão Pereira Dias 202045384 --

void listar_todos_produtos(Produto *lista) {
    if (lista == NULL) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }
    printf("\n--- LISTA DE PRODUTOS ---\n");
    Produto *atual = lista;
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->codigo, atual->nome);
        printf("Preco: R$ %.2f | Qtd: %d\n", atual->preco, atual->quantidade);
        printf("----------------------------------------------------\n");
        atual = atual->prox; // Agora acessa o proximo corretamente
    }
}

void menu_cadastrar_produto(Produto **lista) {
    int codigo, quantidade;
    float preco;
    char nome[50];

    printf("\n--- NOVO PRODUTO ---\n");
    
    printf("Codigo (ID): ");
    scanf("%d", &codigo);
    getchar(); // Limpa buffer do enter

    // Validação visual antes de tentar inserir
    if (buscar_produto(*lista, codigo) != NULL) {
        printf("Erro: Codigo ja cadastrado!\n");
        return;
    }

    printf("Nome: ");
    ler_texto(nome, 50); // Reutiliza a função auxiliar do Samuel

    printf("Preco: ");
    scanf("%f", &preco);

    printf("Quantidade: ");
    scanf("%d", &quantidade);
    getchar(); // Limpa buffer

    // Chama sua função do model.c
    if (adicionar_produto(lista, codigo, nome, preco, quantidade)) {
        printf(">> Produto cadastrado com sucesso!\n");
    } else {
        printf("Erro: Falha ao cadastrar (Memoria cheia ou ID duplicado).\n");
    }
}

void menu_editar_produto_view(Produto *lista) {
    int codigo, nova_qtd;
    float novo_preco;
    char novo_nome[50];

    printf("\n--- EDITAR PRODUTO ---\n");
    printf("Informe o Codigo do produto: ");
    scanf("%d", &codigo);
    getchar();

    if (buscar_produto(lista, codigo) == NULL) {
        printf("Erro: Produto nao encontrado.\n");
        return;
    }

    printf("Novos Dados (Digite para substituir):\n");
    
    printf("Novo Nome: ");
    ler_texto(novo_nome, 50);

    printf("Novo Preco (digite -1 para manter): ");
    scanf("%f", &novo_preco);

    printf("Nova Quantidade (digite -1 para manter): ");
    scanf("%d", &nova_qtd);
    getchar();

    if (editar_produto(lista, codigo, novo_nome, novo_preco, nova_qtd)) {
        printf(">> Dados do produto atualizados!\n");
    } else {
        printf("Erro ao atualizar.\n");
    }
}

void menu_remover_produto_view(Produto **lista) {
    int codigo;
    printf("\n--- REMOVER PRODUTO ---\n");
    printf("Informe o Codigo: ");
    scanf("%d", &codigo);
    getchar();

    if (remover_produto(lista, codigo)) {
        printf(">> Produto removido com sucesso!\n");
    } else {
        printf("Erro: Produto nao encontrado.\n");
    }
}

// Menu Principal do módulo de Produtos
void menu_gerenciar_produtos(Produto **lista) {
    int opcao;
    do {
        printf("\n=== GESTAO DE PRODUTOS ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Editar Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch(opcao) {
            case 1: menu_cadastrar_produto(lista); break;
            case 2: listar_todos_produtos(*lista); break;
            case 3: menu_editar_produto_view(*lista); break;
            case 4: menu_remover_produto_view(lista); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// --- MENU PRINCIPAL DO SISTEMA ---
void menu_principal(Cliente **lista_c, Produto **lista_p) {
    int opcao;
    do {
        printf("\n==================================\n");
        printf("      SISTEMA DE VENDAS       \n");
        printf("==================================\n");
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Produtos\n"); // <--- SUA PARTE AQUI
        printf("3. Realizar Venda (Beta)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch(opcao) {
            case 1:
                menu_gerenciar_clientes(lista_c);
                break;
            case 2:
                // Passa a lista de produtos para o seu menu
                menu_gerenciar_produtos(lista_p);
                break;
            case 3:
                printf("Modulo de Vendas em desenvolvimento...\n");
                // Futuramente chamara: processar_compra(...);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}


