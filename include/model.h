#ifndef MODEL_H
#define MODEL_H

// a struct ItemCarrinho precisa estar acima das outras
typedef struct ItemCarrinho {
    int codigo_produto;
    int qtd_comprada;
    struct ItemCarrinho *prox;
} ItemCarrinho;

// --- ESPAÇO GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---

// Estrutura do Cliente (Nó da Lista)
typedef struct Cliente {
    char cpf[15];       // Chave primária
    char nome[50];
    char email[80];    
    char data_nasc[15]; // (DD/MM/AAAA)
    ItemCarrinho *carrinho; // essa linha precisa estar aqui
    char telefone[15];
    struct Cliente *prox; // Ponteiro para lista encadeada
} Cliente;

// --- Protótipos das Funções (Lógica Pura) ---

// Adiciona um novo cliente ao final da lista
void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *email, char *data_nasc, char *telefone);

// Busca um cliente pelo CPF (Retorna o ponteiro ou NULL)
Cliente* buscar_cliente(Cliente *lista, char *cpf);

// Remove um cliente da lista e libera a memória
int remover_cliente(Cliente **lista, char *cpf);

// Edita os dados de um cliente existente
int editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_email, char *nova_data, char *novo_telefone);

// Libera toda a lista da memória (para fechar o programa)
void liberar_lista_clientes(Cliente **lista);

// ESPAÇO PARA GERENCIAMENTO DE PRODUTOS: ABRAÃO PEREIRA DIAS - 202045384 ---

typedef struct Produto{
    int codigo; // Código de Identificação do produto
    char nome[50]; // Nome do Produto
    float preco; // Valor do produto
    int quantidade; // Quantidade do Produto em estoque
    struct Produto *prox; // Ponteiro para o próximo produto
} Produto;

// Funções 
// Observação: 'lista' é ponteiro para ponteiro (Produto**) quando precisa alterar o início (adicionar/remover)

// Adiciona um novo produto à lista
// Retorna 1 se sucesso, 0 se erro (memória ou código duplicado)
int adicionar_produto(Produto **lista, int codigo, char *nome, float preco, int quantidade);
// Lista todos os produtos (apenas leitura, então ponteiro simples)
void listar_produtos(Produto *lista);
// Busca um produto pelo código
Produto* buscar_produto(Produto *lista, int codigo);
// Remove um produto da lista
void remover_produto(Produto **lista, int codigo);
// Edita os dados de um produto existente
int editar_produto(Produto *lista, int codigo, char *novo_nome, float novo_preco, int nova_qtd);
// Libera toda a memória da lista ao fechar o programa
void liberar_lista_produtos(Produto **lista);

// ESPAÇO RESERVADO PARA GERENCIAMENTO DE COMPRA (CARRINHO): BRENO ELIAS DE CARVALHO CORREIA - 242028815 ---

// typedef struct ItemCarrinho {
//     int codigo_produto;
//     int qtd_comprada;
//     struct ItemCarrinho *prox;
// } ItemCarrinho;
// Função de integração que você criou na main

void liberar_sistema(Cliente **lista_c, Produto **lista_p);
void adicionar_ao_carrinho(Cliente *cliente, Produto *produto, int qtd);
void calcular_total_carrinho(Cliente *cliente, Produto *lista_produtos);

#endif