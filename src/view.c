#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h> // Para acentos
#include "../include/view.h"
#include "../include/model.h"

// --- FUNÇÕES AUXILIARES DE TELA ---

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void esperar_enter() {
    printf("\n>> Pressione ENTER para continuar...");
    getchar(); // Espera o usuário ler a mensagem
}

// --- OUTRAS FUNÇÕES AUXILIARES ---

void ler_texto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// Verifica se string contém apenas números
int eh_numerico(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

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

// --- MENUS DE CLIENTES (SAMUEL CAMPOS ROCHA) ---

void listar_todos_clientes(Cliente *lista) {
    printf("\n==================================\n");
    printf("        LISTA DE CLIENTES         \n");
    printf("==================================\n");
    
    if (lista == NULL) {
        printf(">> Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente *atual = lista;
    while (atual != NULL) {
        printf(" CPF:   %s\n", atual->cpf);
        printf(" Nome:  %s\n", atual->nome);
        printf(" Email: %s\n", atual->email);
        printf(" Nasc.: %s  |  Tel: %s\n", atual->data_nasc, atual->telefone);
        printf("----------------------------------\n");
        atual = atual->prox;
    }
}

void menu_cadastrar_cliente(Cliente **lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];

    printf("\n--- NOVO CLIENTE (Digite 0 para Cancelar) ---\n");

    // Loop de validação do CPF
    while (1) {
        printf("CPF (apenas números, 11 dígitos): ");
        ler_texto(cpf, 15);

        // Opção de Cancelar
        if (strcmp(cpf, "0") == 0) {
            printf(">> Operação cancelada.\n");
            return; 
        }

        // Validação de Formato
        if (strlen(cpf) != 11 || !eh_numerico(cpf)) {
            printf("   [!] Erro: O CPF deve conter exatamente 11 dígitos numéricos.\n");
            continue;
        }

        // Validação de Duplicidade
        if (buscar_cliente(*lista, cpf) != NULL) {
            printf("   [!] Erro: CPF já cadastrado!\n");
            return;
        }
        
        break; // Sai do loop se estiver ok
    }

    printf("Nome Completo: ");
    ler_texto(nome, 50);

    printf("E-mail: ");
    ler_texto(email, 80);

    do {
        printf("Data de Nascimento (DD/MM/AAAA): ");
        ler_texto(data, 15);
        if (!validar_data(data)) {
            printf("   [!] Data inválida!\n");
        }
    } while (!validar_data(data));

    printf("Telefone: ");
    ler_texto(tel, 15);

    adicionar_cliente(lista, cpf, nome, email, data, tel);
    printf("\n[v] Cliente cadastrado com sucesso!\n");
}

void menu_editar_cliente_view(Cliente *lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];
    
    printf("\n--- EDITAR CLIENTE ---\n");
    printf("Informe o CPF do cliente: ");
    ler_texto(cpf, 15);

    if (buscar_cliente(lista, cpf) == NULL) {
        printf("   [!] Erro: Cliente não encontrado.\n");
        return;
    }

    printf("\n>> Novos Dados:\n");
    printf("Novo Nome: "); ler_texto(nome, 50);
    printf("Novo E-mail: "); ler_texto(email, 80);
    
    do {
        printf("Nova Data (DD/MM/AAAA): ");
        ler_texto(data, 15);
    } while (!validar_data(data));

    printf("Novo Telefone: "); ler_texto(tel, 15);

    editar_cliente(lista, cpf, nome, email, data, tel);
    printf("\n[v] Dados atualizados!\n");
}

void menu_remover_cliente_view(Cliente **lista) {
    char cpf[15];
    printf("\n--- REMOVER CLIENTE ---\n");
    printf("Informe o CPF: ");
    ler_texto(cpf, 15);

    if (remover_cliente(lista, cpf)) {
        printf("\n[v] Cliente removido com sucesso!\n");
    } else {
        printf("   [!] Erro: Cliente não encontrado.\n");
    }
}

// MENU DE GESTÃO DE CLIENTES
void menu_gerenciar_clientes(Cliente **lista) {
    int opcao;
    do {
        limpar_tela(); // <--- Limpa antes de desenhar o menu

        printf("\n=== GESTÃO DE CLIENTES ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: 
                menu_cadastrar_cliente(lista); 
                esperar_enter(); // <--- Pausa para ver o resultado
                break;
            case 2: 
                listar_todos_clientes(*lista); 
                esperar_enter();
                break;
            case 3: 
                menu_editar_cliente_view(*lista); 
                esperar_enter();
                break;
            case 4: 
                menu_remover_cliente_view(lista); 
                esperar_enter();
                break;
            case 0: break;
            default: 
                printf("Opção inválida!\n");
                esperar_enter();
        }
    } while (opcao != 0);
}

// --- MENUS DE PRODUTOS (ABRAÃO PEREIRA DIAS) ---

void listar_todos_produtos(Produto *lista) {
    printf("\n==================================\n");
    printf("        LISTA DE PRODUTOS         \n");
    printf("==================================\n");

    if (lista == NULL) {
        printf(">> Nenhum produto cadastrado.\n");
        return;
    }
    Produto *atual = lista;
    while (atual != NULL) {
        printf(" ID:    %d\n", atual->codigo);
        printf(" Nome:  %s\n", atual->nome);
        printf(" Preço: R$ %.2f | Qtd: %d\n", atual->preco, atual->quantidade);
        printf("----------------------------------\n");
        atual = atual->prox; 
    }
}

void menu_cadastrar_produto(Produto **lista) {
    int codigo, quantidade;
    float preco;
    char nome[50];
    char buffer_cod[20]; 

    printf("\n--- NOVO PRODUTO (Digite 0 para Cancelar) ---\n");
    
    while (1) {
        printf("Código (ID): ");
        ler_texto(buffer_cod, 20); // Lê como texto primeiro

        if (strcmp(buffer_cod, "0") == 0) {
            printf(">> Operação cancelada.\n");
            return;
        }

        codigo = atoi(buffer_cod);

        if (codigo <= 0) {
            printf("   [!] Erro: Código inválido.\n");
            continue;
        }

        if (buscar_produto(*lista, codigo) != NULL) {
            printf("   [!] Erro: Código já cadastrado!\n");
            return;
        }

        break;
    }

    printf("Nome: ");
    ler_texto(nome, 50);

    printf("Preço: ");
    scanf("%f", &preco);

    printf("Quantidade: ");
    scanf("%d", &quantidade);
    getchar();

    if (adicionar_produto(lista, codigo, nome, preco, quantidade)) {
        printf("\n[v] Produto cadastrado com sucesso!\n");
    } else {
        printf("\n[x] Erro: Falha ao cadastrar.\n");
    }
}

void menu_editar_produto_view(Produto *lista) {
    int codigo, nova_qtd;
    float novo_preco;
    char novo_nome[50];

    printf("\n--- EDITAR PRODUTO ---\n");
    printf("Informe o Código do produto: ");
    scanf("%d", &codigo);
    getchar();

    if (buscar_produto(lista, codigo) == NULL) {
        printf("   [!] Erro: Produto não encontrado.\n");
        return;
    }

    printf("\n>> Novos Dados:\n");
    printf("Novo Nome: "); ler_texto(novo_nome, 50);
    printf("Novo Preço (digite -1 para manter): "); scanf("%f", &novo_preco);
    printf("Nova Quantidade (digite -1 para manter): "); scanf("%d", &nova_qtd);
    getchar();

    if (editar_produto(lista, codigo, novo_nome, novo_preco, nova_qtd)) {
        printf("\n[v] Dados atualizados!\n");
    } else {
        printf("\n[x] Erro ao atualizar.\n");
    }
}

void menu_remover_produto_view(Produto **lista) {
    int codigo;
    printf("\n--- REMOVER PRODUTO ---\n");
    printf("Informe o Código: ");
    scanf("%d", &codigo);
    getchar();

    if (remover_produto(lista, codigo)) {
        printf("\n[v] Produto removido com sucesso!\n");
    } else {
        printf("   [!] Erro: Produto não encontrado.\n");
    }
}

// MENU DE GESTÃO DE PRODUTOS
void menu_gerenciar_produtos(Produto **lista) {
    int opcao;
    do {
        limpar_tela(); // <--- Limpa a tela

        printf("\n=== GESTÃO DE PRODUTOS ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Editar Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: 
                menu_cadastrar_produto(lista); 
                esperar_enter(); // <--- Pausa
                break;
            case 2: 
                listar_todos_produtos(*lista); 
                esperar_enter();
                break;
            case 3: 
                menu_editar_produto_view(*lista); 
                esperar_enter();
                break;
            case 4: 
                menu_remover_produto_view(lista); 
                esperar_enter();
                break;
            case 0: break;
            default: 
                printf("Opção inválida!\n");
                esperar_enter();
        }
    } while (opcao != 0);
}

// --- MENU PRINCIPAL DO SISTEMA ---
void menu_principal(Cliente **lista_c, Produto **lista_p) {
    setlocale(LC_ALL, "Portuguese"); // Ativa acentos

    int opcao;
    do {
        limpar_tela(); // <--- Limpa a tela no menu principal também

        printf("\n##################################\n");
        printf("      SISTEMA DE VENDAS       \n");
        printf("##################################\n");
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Produtos\n");
        printf("3. Realizar Venda (Beta)\n");
        printf("0. Sair\n");
        printf("----------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                menu_gerenciar_clientes(lista_c);
                break;
            case 2:
                menu_gerenciar_produtos(lista_p);
                break;
            case 3:
                printf("\n>> Módulo de Vendas em desenvolvimento...\n");
                esperar_enter();
                break;
            case 0:
                printf("\nEncerrando sistema... Até logo!\n");
                break;
            default:
                printf("\n[!] Opção inválida!\n");
                esperar_enter();
        }
    } while (opcao != 0);
}
