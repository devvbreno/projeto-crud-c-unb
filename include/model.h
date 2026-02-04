/* HEADER GUARD (Guarda de Cabeçalho)
   #ifndef e #define evitam que este arquivo seja lido duas vezes 
   pelo compilador, o que causaria erro de "redefinição de struct".
*/

#ifndef MODEL_H
#define MODEL_H

/* STRUCT ITEMCARRINHO
   Representa um nó da lista encadeada de compras DENTRO de um cliente.
   Não guardamos o Produto inteiro aqui, apenas o código dele e a quantidade.
   Isso economiza memória (referência em vez de cópia).
*/

typedef struct ItemCarrinho {
    int codigo_produto; // Chave estrangeira (liga ao Produto)
    int qtd_comprada; // Quantas unidades o cliente quer
    struct ItemCarrinho *prox; // Ponteiro para o próximo item do carrinho
} ItemCarrinho;

/* STRUCT CLIENTE
   Representa o nó da lista principal de clientes.
   Note que é uma estrutura complexa: ela contém dados e UMA OUTRA LISTA (carrinho).
*/

typedef struct Cliente {
    char cpf[15];       
    char nome[50];
    char email[80];    
    char data_nasc[15]; 
    char telefone[15];
    ItemCarrinho *carrinho; // Sub-lista encadeada: Cada cliente tem seu próprio "trem" de compras.
    struct Cliente *prox; // Ponteiro para o próximo cliente (Elo da corrente principal).
} Cliente;

/* STRUCT PRODUTO
   Lista encadeada simples para o estoque.
*/

typedef struct Produto{
    int codigo; // Identificador único (Primary Key)
    char nome[50]; 
    float preco; 
    int quantidade; // Estoque disponível
    struct Produto *prox; // Elo para o próximo produto
} Produto;

// --- PROTÓTIPOS ---

// Clientes
// Usa ponteiro duplo (Cliente **lista) porque a lista pode mudar de endereço (ex: 1º inserção)
void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *email, char *data_nasc, char *telefone);
// Usa ponteiro simples (Cliente *lista) porque apenas LÊ a lista, não altera o início dela.
Cliente* buscar_cliente(Cliente *lista, char *cpf);
int remover_cliente(Cliente **lista, char *cpf);
int editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_email, char *nova_data, char *novo_telefone);
void liberar_lista_clientes(Cliente **lista);

// Produtos
// Produtos - declaração de funções
// Uso de ponteiro duplo para alterar o endereço, uso de ponteiro simples para ler a informação armazenada no byte

int adicionar_produto(Produto **lista, int codigo, char *nome, float preco, int quantidade);
void listar_produtos(Produto *lista); //Listar só lê, não altera onde a lista começa.
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


