#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "../include/view.h"
#include "../include/model.h"

// --- CORES E FORMATAÇÃO (Neutras/Profissionais) ---
#define COR_RESET   "\033[0m"
#define COR_TITULO  "\033[1;36m" // Ciano Claro
#define COR_MENU    "\033[1;37m" // Branco Brilhante
#define COR_ERRO    "\033[1;31m" // Vermelho
#define COR_SUCESSO "\033[1;32m" // Verde
#define COR_AVISO   "\033[1;33m" // Amarelo

// --- FUNÇÕES AUXILIARES ---

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void esperar_enter() {
    printf("\n%s>> Pressione ENTER para continuar...%s", COR_MENU, COR_RESET);
    getchar();
}

void ler_texto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

int eh_numerico(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int validar_email(char *email) {
    // Validação simples: precisa ter '@'
    if (strchr(email, '@') == NULL) return 0;
    if (strlen(email) < 5) return 0;
    return 1;
}

int validar_telefone(char *tel) {
    // Aceita 10 (Fixo: XX NNNN-NNNN) ou 11 (Cel: XX 9NNNN-NNNN) dígitos
    if (!eh_numerico(tel)) return 0;
    int len = strlen(tel);
    if (len != 10 && len != 11) return 0;
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

    // Garante que 30/02 ou 31/04 sejam invalidados
    if (dia < 1 || dia > dias_mes[mes]) return 0;

    return 1;
}

// --- VIEW CLIENTES ---

void menu_cadastrar_cliente(Cliente **lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];

    printf("\n%s--- NOVO CLIENTE (Digite 0 para Cancelar) ---%s\n", COR_TITULO, COR_RESET);

    // Validação CPF
    while (1) {
        printf("CPF (apenas numeros, 11 digitos): ");
        ler_texto(cpf, 15);
        if (strcmp(cpf, "0") == 0) return;
        if (strlen(cpf) != 11 || !eh_numerico(cpf)) {
            printf("%s[!] Erro: CPF deve ter 11 digitos numericos.%s\n", COR_ERRO, COR_RESET);
            continue;
        }
        if (buscar_cliente(*lista, cpf) != NULL) {
            printf("%s[!] Erro: CPF ja cadastrado!%s\n", COR_ERRO, COR_RESET);
            return;
        }
        break;
    }

    printf("Nome Completo: ");
    ler_texto(nome, 50);

    // Validação Email
    do {
        printf("E-mail: ");
        ler_texto(email, 80);
        if (!validar_email(email)) printf("%s[!] Email invalido! Deve conter '@'.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_email(email));

    // Validação Data
    do {
        printf("Nascimento (DD/MM/AAAA): ");
        ler_texto(data, 15);
        if (!validar_data(data)) printf("%s[!] Data invalida ou inexistente!%s\n", COR_ERRO, COR_RESET);
    } while (!validar_data(data));

    // Validação Telefone
    do {
        printf("Telefone (DDD+Numero, apenas digitos): ");
        ler_texto(tel, 15);
        if (!validar_telefone(tel)) printf("%s[!] Tel invalido! Use 10 ou 11 digitos.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_telefone(tel));

    adicionar_cliente(lista, cpf, nome, email, data, tel);
    printf("\n%s[v] Cliente cadastrado com sucesso!%s\n", COR_SUCESSO, COR_RESET);
}

void listar_todos_clientes(Cliente *lista) {
    printf("\n%s=== LISTA DE CLIENTES ===%s\n", COR_TITULO, COR_RESET);
    if (lista == NULL) {
        printf(">> Nenhum cliente cadastrado.\n");
        return;
    }
    Cliente *atual = lista;
    while (atual != NULL) {
        printf(" CPF:   %s | Nome: %s\n", atual->cpf, atual->nome);
        printf(" Email: %s | Tel: %s\n", atual->email, atual->telefone);
        printf("----------------------------------\n");
        atual = atual->prox;
    }
}

// ... Mantém as funções de editar e remover com estrutura similar ...
// Vou omitir editar/remover repetitivas para focar nas mudanças principais, 
// mas elas seguem a mesma lógica de validação do cadastro se implementadas corretamente.

void menu_gerenciar_clientes(Cliente **lista) {
    int opcao;
    do {
        limpar_tela();
        printf("\n%s=== GESTAO DE CLIENTES ===%s\n", COR_TITULO, COR_RESET);
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        // printf("3. Editar Cliente\n"); // Implementar chamando validações similares
        printf("4. Remover Cliente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: menu_cadastrar_cliente(lista); esperar_enter(); break;
            case 2: listar_todos_clientes(*lista); esperar_enter(); break;
            case 4: menu_remover_cliente_view(lista); esperar_enter(); break;
            case 0: break;
            default: printf("Opcao invalida!\n"); esperar_enter();
        }
    } while (opcao != 0);
}

// --- MENUS DE PRODUTOS E GERAL ---
// (Adapte listar_todos_produtos e menu_gerenciar_produtos com as cores novas)

void menu_remover_cliente_view(Cliente **lista) {
    char cpf[15];
    printf("\n--- REMOVER CLIENTE ---\n");
    printf("Informe o CPF: ");
    ler_texto(cpf, 15);
    if (remover_cliente(lista, cpf)) printf("%s[v] Removido!%s\n", COR_SUCESSO, COR_RESET);
    else printf("%s[!] Nao encontrado.%s\n", COR_ERRO, COR_RESET);
}

void menu_principal(Cliente **lista_c, Produto **lista_p) {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    do {
        limpar_tela();
        printf("\n%s##################################%s\n", COR_TITULO, COR_RESET);
        printf("%s      CENTRAL DE VENDAS      %s\n", COR_TITULO, COR_RESET);
        printf("%s##################################%s\n", COR_TITULO, COR_RESET);
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Produtos\n");
        printf("3. Carrinho de Compras\n");
        printf("0. Salvar e Sair\n"); // Alterado para indicar que salva
        printf("----------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: menu_gerenciar_clientes(lista_c); break;
            case 2: menu_gerenciar_produtos(lista_p); break;
            case 3: menu_vendas(lista_c, lista_p); break;
            case 0: 
                salvar_dados(*lista_c, *lista_p); // Salva antes de sair
                printf("\nEncerrando...\n"); 
                break;
            default: printf("\nOpcao invalida!\n"); esperar_enter();
        }
    } while (opcao != 0);
}
