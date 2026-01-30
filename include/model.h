#ifndef MODEL_H
#define MODEL_H

// --- ESPAÇO GERENCIAMENTO DE CLIENTES: SAMUEL CAMPOS ROCHA - 211031824 ---

// Definição do Cliente (Nó da Lista Encadeada)
typedef struct Cliente {
    char cpf[15];       // Chave primária
    char nome[50];
    char telefone[15];
    ItemCarrinho *carrinho; // o ponteiro para a sublista de compras
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

typedef struct ItemCarrinho {
    int codigo_produto;
    int qtd_comprada;
    struct ItemCarrinho *prox;
} ItemCarrinho;

void adicionar_ao_carrinho(Cliente *cliente, Produto *produto, int qtd);
void calcular_total_carrinho(Cliente *cliente, Produto *lista_produtos);

#endif


