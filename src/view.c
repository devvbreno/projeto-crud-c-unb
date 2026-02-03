#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "../include/view.h"
#include "../include/model.h"

// --- CORES E FORMATAÇÃO ---
#define COR_RESET   "\033[0m"
#define COR_TITULO  "\033[1;36m" // Ciano Claro
#define COR_MENU    "\033[1;37m" // Branco Brilhante
#define COR_ERRO    "\033[1;31m" // Vermelho
#define COR_SUCESSO "\033[1;32m" // Verde

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
    if (strchr(email, '@') == NULL) return 0;
    if (strlen(email) < 5) return 0;
    return 1;
}

int validar_telefone(char *tel) {
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

    if (dia < 1 || dia > dias_mes[mes]) return 0;

    return 1;
}

// --- GESTÃO DE CLIENTES ---

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
        printf(" Nasc:  %s\n", atual->data_nasc);
        printf("----------------------------------\n");
        atual = atual->prox;
    }
}

void menu_cadastrar_cliente(Cliente **lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];

    printf("\n%s--- NOVO CLIENTE (0 para Sair) ---%s\n", COR_TITULO, COR_RESET);

    while (1) {
        printf("CPF (11 digitos): ");
        ler_texto(cpf, 15);
        if (strcmp(cpf, "0") == 0) return;

        if (strlen(cpf) != 11 || !eh_numerico(cpf)) {
            printf("%s[!] Erro: O CPF deve conter 11 números.%s\n", COR_ERRO, COR_RESET);
            continue;
        }
        if (buscar_cliente(*lista, cpf) != NULL) {
            printf("%s[!] Erro: CPF já cadastrado!%s\n", COR_ERRO, COR_RESET);
            return;
        }
        break;
    }

    printf("Nome: "); ler_texto(nome, 50);

    do {
        printf("Email: "); ler_texto(email, 80);
        if (!validar_email(email)) printf("%s[!] Email inválido (falta @).%s\n", COR_ERRO, COR_RESET);
    } while (!validar_email(email));

    do {
        printf("Nascimento (DD/MM/AAAA): "); ler_texto(data, 15);
        if (!validar_data(data)) printf("%s[!] Data inválida.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_data(data));

    do {
        printf("Telefone (10 ou 11 digitos): "); ler_texto(tel, 15);
        if (!validar_telefone(tel)) printf("%s[!] Telefone inválido.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_telefone(tel));

    adicionar_cliente(lista, cpf, nome, email, data, tel);
    printf("\n%s[v] Cliente cadastrado!%s\n", COR_SUCESSO, COR_RESET);
}

void menu_editar_cliente_view(Cliente *lista) {
    char cpf[15], nome[50], email[80], data[15], tel[15];
    
    printf("\n%s--- EDITAR CLIENTE ---%s\n", COR_TITULO, COR_RESET);
    printf("Informe o CPF: ");
    ler_texto(cpf, 15);

    if (buscar_cliente(lista, cpf) == NULL) {
        printf("%s[!] Cliente não encontrado.%s\n", COR_ERRO, COR_RESET);
        return;
    }

    printf("\n>> Novos Dados:\n");
    printf("Novo Nome: "); ler_texto(nome, 50);
    
    do {
        printf("Novo Email: "); ler_texto(email, 80);
        if (!validar_email(email)) printf("%s[!] Email inválido.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_email(email));
    
    do {
        printf("Nova Data (DD/MM/AAAA): "); ler_texto(data, 15);
        if (!validar_data(data)) printf("%s[!] Data inválida.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_data(data));

    do {
        printf("Novo Telefone: "); ler_texto(tel, 15);
        if (!validar_telefone(tel)) printf("%s[!] Telefone inválido.%s\n", COR_ERRO, COR_RESET);
    } while (!validar_telefone(tel));

    editar_cliente(lista, cpf, nome, email, data, tel);
    printf("\n%s[v] Dados atualizados!%s\n", COR_SUCESSO, COR_RESET);
}

void menu_remover_cliente_view(Cliente **lista) {
    char cpf[15];
    printf("\n%s--- REMOVER CLIENTE ---%s\n", COR_TITULO, COR_RESET);
    printf("Informe o CPF: ");
    ler_texto(cpf, 15);

    if (remover_cliente(lista, cpf)) {
        printf("\n%s[v] Cliente removido!%s\n", COR_SUCESSO, COR_RESET);
    } else {
        printf("%s[!] Cliente não encontrado.%s\n", COR_ERRO, COR_RESET);
    }
}

void menu_gerenciar_clientes(Cliente **lista) {
    int opcao;
    do {
        limpar_tela();
        printf("\n%s=== GESTAO DE CLIENTES ===%s\n", COR_TITULO, COR_RESET);
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: menu_cadastrar_cliente(lista); esperar_enter(); break;
            case 2: listar_todos_clientes(*lista); esperar_enter(); break;
            case 3: menu_editar_cliente_view(*lista); esperar_enter(); break;
            case 4: menu_remover_cliente_view(lista); esperar_enter(); break;
            case 0: break;
            default: printf("Opção invalida!\n"); esperar_enter();
        }
    } while (opcao != 0);
}

// --- GESTÃO DE PRODUTOS ---

void listar_todos_produtos(Produto *lista) {
    printf("\n%s=== LISTA DE PRODUTOS ===%s\n", COR_TITULO, COR_RESET);
    if (lista == NULL) {
        printf(">> Nenhum produto cadastrado.\n");
        return;
    }
    Produto *atual = lista;
    while (atual != NULL) {
        printf(" ID: %d | Nome: %s\n", atual->codigo, atual->nome);
        printf(" Preco: R$ %.2f | Estoque: %d\n", atual->preco, atual->quantidade);
        printf("----------------------------------\n");
        atual = atual->prox; 
    }
}

void menu_cadastrar_produto(Produto **lista) {
    int codigo, quantidade;
    float preco;
    char nome[50];
    char buffer_cod[20]; 

    printf("\n%s--- NOVO PRODUTO ---%s\n", COR_TITULO, COR_RESET);
    
    while (1) {
        printf("Código (ID): ");
        ler_texto(buffer_cod, 20); 

        if (strcmp(buffer_cod, "0") == 0) return;
        codigo = atoi(buffer_cod);

        if (codigo <= 0) {
            printf("%s[!] Código inválido.%s\n", COR_ERRO, COR_RESET);
            continue;
        }
        if (buscar_produto(*lista, codigo) != NULL) {
            printf("%s[!] Código já cadastrado!%s\n", COR_ERRO, COR_RESET);
            return;
        }
        break;
    }

    printf("Nome: "); ler_texto(nome, 50);
    printf("Preço: "); scanf("%f", &preco);
    printf("Quantidade: "); scanf("%d", &quantidade);
    getchar(); // Consumir enter

    if (adicionar_produto(lista, codigo, nome, preco, quantidade)) {
        printf("\n%s[v] Produto cadastrado!%s\n", COR_SUCESSO, COR_RESET);
    } else {
        printf("\n%s[x] Erro ao cadastrar.%s\n", COR_ERRO, COR_RESET);
    }
}

void menu_editar_produto_view(Produto *lista) {
    int codigo, nova_qtd;
    float novo_preco;
    char novo_nome[50];

    printf("\n%s--- EDITAR PRODUTO ---%s\n", COR_TITULO, COR_RESET);
    printf("Informe o ID do produto: ");
    scanf("%d", &codigo);
    getchar();

    if (buscar_produto(lista, codigo) == NULL) {
        printf("%s[!] Produto não encontrado.%s\n", COR_ERRO, COR_RESET);
        return;
    }

    printf("\n>> Novos Dados (use -1 para manter preco/qtd):\n");
    printf("Novo Nome: "); ler_texto(novo_nome, 50);
    printf("Novo Preço: "); scanf("%f", &novo_preco);
    printf("Nova Quantidade: "); scanf("%d", &nova_qtd);
    getchar();

    if (editar_produto(lista, codigo, novo_nome, novo_preco, nova_qtd)) {
        printf("\n%s[v] Produto atualizado!%s\n", COR_SUCESSO, COR_RESET);
    } else {
        printf("\n%s[x] Erro ao atualizar.%s\n", COR_ERRO, COR_RESET);
    }
}

void menu_remover_produto_view(Produto **lista) {
    int codigo;
    printf("\n%s--- REMOVER PRODUTO ---%s\n", COR_TITULO, COR_RESET);
    printf("Informe o ID: ");
    scanf("%d", &codigo);
    getchar();

    if (remover_produto(lista, codigo)) {
        printf("\n%s[v] Produto removido!%s\n", COR_SUCESSO, COR_RESET);
    } else {
        printf("%s[!] Produto não encontrado.%s\n", COR_ERRO, COR_RESET);
    }
}

void menu_gerenciar_produtos(Produto **lista) {
    int opcao;
    do {
        limpar_tela();
        printf("\n%s=== GESTÃO DE PRODUTOS ===%s\n", COR_TITULO, COR_RESET);
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Editar Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: menu_cadastrar_produto(lista); esperar_enter(); break;
            case 2: listar_todos_produtos(*lista); esperar_enter(); break;
            case 3: menu_editar_produto_view(*lista); esperar_enter(); break;
            case 4: menu_remover_produto_view(lista); esperar_enter(); break;
            case 0: break;
            default: printf("Opcao invalida!\n"); esperar_enter();
        }
    } while (opcao != 0);
}

// --- MODO VENDAS (CARRINHO) ---

void menu_vendas(Cliente **lista_c, Produto **lista_p) {
    char cpf[15];
    int opcao, cod_prod, qtd;

    printf("\n%s--- MODO COMPRA ---%s\n", COR_TITULO, COR_RESET);
    printf("Informe o CPF do Cliente: ");
    ler_texto(cpf, 15);

    Cliente *c = buscar_cliente(*lista_c, cpf);
    if (c == NULL) {
        printf("%s[ERRO] Cliente nao encontrado!%s\n", COR_ERRO, COR_RESET);
        esperar_enter();
        return;
    }

    do {
        printf("\n%s=== CARRINHO DE %s ===%s\n", COR_TITULO, c->nome, COR_RESET);
        printf("1. Adicionar Produto\n");
        printf("2. Ver Carrinho e Total\n");
        printf("3. Retirar Produto\n");
        printf("4. Finalizar Compra\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("Codigo do Produto: "); scanf("%d", &cod_prod);
                printf("Quantidade: "); scanf("%d", &qtd);
                getchar(); // Consumir enter
                ctrl_adicionar_item(*lista_c, *lista_p, cpf, cod_prod, qtd);
                esperar_enter();
                break;
            case 2:
                calcular_total_carrinho(c, *lista_p);
                esperar_enter();
                break;
            case 3:
                printf("Codigo do Produto a remover: "); scanf("%d", &cod_prod);
                getchar();
                ctrl_remover_item(*lista_c, *lista_p, cpf, cod_prod);
                esperar_enter();
                break;
            case 4:
                ctrl_finalizar_venda(*lista_c, cpf, *lista_p);
                opcao = 0; 
                esperar_enter();
                break;
        }
    } while (opcao != 0);
}

// --- MENU PRINCIPAL ---

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
        printf("0. Salvar e Sair\n");
        printf("----------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: menu_gerenciar_clientes(lista_c); break;
            case 2: menu_gerenciar_produtos(lista_p); break;
            case 3: menu_vendas(lista_c, lista_p); break;
            case 0: 
                salvar_dados(*lista_c, *lista_p); 
                printf("\nEncerrando...\n"); 
                break;
            default: printf("\nOpcao invalida!\n"); esperar_enter();
        }
    } while (opcao != 0);
}

