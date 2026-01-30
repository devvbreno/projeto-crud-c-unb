#ifndef MODEL_H
#define MODEL_H

// --- ESPAÇO GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---

// Definição do Cliente (Nó da Lista Encadeada)
typedef struct Cliente {
    char cpf[15];       // Chave primária
    char nome[50];
    char telefone[15];
    struct Cliente *prox; // Ponteiro para o próximo cliente (Lista Encadeada)
} Cliente;

// Protótipos das funções (O que o código faz)
// Note que passamos ponteiro de ponteiro (**lista) para poder alterar o início da lista se necessário
void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *telefone);
void listar_clientes(Cliente *lista); // Aqui só lê, não precisa de **
Cliente* buscar_cliente(Cliente *lista, char *cpf);
void remover_cliente(Cliente **lista, char *cpf);
void editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_telefone);

// --- FIM DO ESPAÇO GERENCIAMENTO DE CLIENTES ---

// ESPAÇO RESERVADO PARA GERENCIAMENTO DE PRODUTOS: ABRAÃO PEREIRA DIAS - 202045384 ---

// ESPAÇO RESERVADO PARA GERENCIAMENTO DE COMPRA (CARRINHO): BRENO ELIAS DE CARVALHO CORREIA - 242028815 ---

#endif
