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

void menu_remover_cliente(Cliente **lista) {
    char cpf[15];
    printf("\n--- Remover Cliente ---\n");
    printf("Digite o CPF do cliente a remover: ");
    ler_texto(cpf, 15);

    // Verifica se existe antes de tentar remover (opcional, mas amigável)
    if (buscar_cliente(*lista, cpf) == NULL) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    remover_cliente(lista, cpf);
    printf("Cliente removido com sucesso!\n");
}

void menu_editar_cliente(Cliente *lista) {
    char cpf[15], novo_nome[50], novo_telefone[15];
    
    printf("\n--- Editar Cliente ---\n");
    printf("Digite o CPF do cliente que deseja alterar: ");
    ler_texto(cpf, 15);

    // Busca para ver se existe e mostra os dados atuais
    Cliente *atual = buscar_cliente(lista, cpf);
    if (atual == NULL) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    printf("Editando cliente: %s\n", atual->nome);
    
    printf("Novo Nome: ");
    ler_texto(novo_nome, 50);
    
    printf("Novo Telefone: ");
    ler_texto(novo_telefone, 15);

    // Chama a model
    editar_cliente(lista, cpf, novo_nome, novo_telefone);
    printf("Dados atualizados com sucesso!\n");
}

// ESPAÇO PARA GERENCIAMENTO DE PRODUTOS: ABRAÃO PEREIRA DIAS - 202045384 ---

void menu_cadastrar_produto(Produto **lista) {
    int codigo;
    char nome[50];
    float preco;

    printf("\n--- Novo Produto ---\n");

    printf("Digite o Codigo (numero): ");
    scanf("%d", &codigo);
    getchar(); // Limpa o buffer do \n deixado pelo scanf

    // Validação de unicidade
    if (buscar_produto(*lista, codigo) != NULL) {
        printf("Erro: Codigo ja existe!\n");
        return;
    }

    printf("Digite o Nome do Produto: ");
    ler_texto(nome, 50); // Função auxiliar criada pelo Membro 1

    printf("Digite o Preco: ");
    scanf("%f", &preco);
    getchar(); // Limpa buffer novamente

    adicionar_produto(lista, codigo, nome, preco);
    printf("Produto cadastrado com sucesso!\n");
}

void menu_listar_produtos(Produto *lista) {
    printf("\n--- Estoque de Produtos ---\n");
    Produto *atual = lista;
    while (atual != NULL) {
        // %.2f formata o float para 2 casas decimais (dinheiro)
        printf("Cod: %d | Nome: %s | R$ %.2f\n", atual->codigo, atual->nome, atual->preco);
        atual = atual->prox;
    }
}

