#ifndef MODEL_H
#define MODEL_H

// Por que usar typedef aqui?
// R: Para não precisar escrever "struct Cliente" toda vez, apenas "Cliente".
typedef struct ItemCarrinho {
    int codigo_produto;
    int qtd_comprada;
    struct ItemCarrinho *prox;
} ItemCarrinho;

// --- ESTRUTURAS ---

typedef struct Cliente {
    char cpf[15];       
    char nome[50];
    char email[80];    
    char data_nasc[15]; 
    char telefone[15];
    ItemCarrinho *carrinho; 
    struct Cliente *prox; // O que é isso? R: O ponteiro que liga este nó ao próximo da lista.
} Cliente;

typedef struct Produto{
    int codigo; 
    char nome[50]; 
    float preco; 
    int quantidade; 
    struct Produto *prox; 
} Produto;

// --- PROTÓTIPOS ---

// Clientes
void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *email, char *data_nasc, char *telefone);
Cliente* buscar_cliente(Cliente *lista, char *cpf);
int remover_cliente(Cliente **lista, char *cpf);
int editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_email, char *nova_data, char *novo_telefone);
void liberar_lista_clientes(Cliente **lista);

// Produtos
int adicionar_produto(Produto **lista, int codigo, char *nome, float preco, int quantidade);
void listar_produtos(Produto *lista); // [PROFESSOR] P: Por que aqui é *lista e no adicionar é **lista? R: Listar só lê, não altera onde a lista começa.
Produto* buscar_produto(Produto *lista, int codigo);
int remover_produto(Produto **lista, int codigo);
int editar_produto(Produto *lista, int codigo, char *novo_nome, float novo_preco, int nova_qtd);
void liberar_lista_produtos(Produto **lista);

// Carrinho / Vendas
int remover_do_carrinho(Cliente *cliente, int cod_prod, Produto *listar_produtos);
void finalizar_compra(Cliente *cliente);
void liberar_sistema(Cliente **lista_c, Produto **lista_p);
void adicionar_ao_carrinho(Cliente *cliente, Produto *produto, int qtd);
void calcular_total_carrinho(Cliente *cliente, Produto *lista_produtos);

// --- PERSISTÊNCIA (BANCO DE DADOS TXT) ---
void salvar_dados(Cliente *lista_c, Produto *lista_p);
void carregar_dados(Cliente **lista_c, Produto **lista_p);

#endif
