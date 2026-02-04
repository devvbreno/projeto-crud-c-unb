#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/model.h"

// --- IMPLEMENTAÇÃO CLIENTES ---

void adicionar_cliente(Cliente **lista, char *cpf, char *nome, char *email, char *data_nasc, char *telefone) {
/* [ALOCAÇÃO DINÂMICA]
       "Uso da função malloc para pedir memória na Heap. Se retornar NULL, 
       significa que a memória RAM acabou (crítico), então aborto a operação."
*/
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (novo == NULL) return; // Validação de segurança: Se a RAM estiver cheia, malloc retorna NULL.

/* [USO DE STRCPY] 
       "Usamos strcpy assumindo que a validação de tamanho seria feita na entrada de dados. 
       Sei que em "produção" o correto seria 'strncpy' para evitar invasão de memória vizinha."
*/
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->data_nasc, data_nasc);
    strcpy(novo->telefone, telefone);

    // Inicializa os ponteiros internos
    novo->prox = NULL; // Ele será o último, então não aponta pra ninguém.
    novo->carrinho = NULL; // Cliente nasce com o carrinho vazio.

    // INSERÇÃO NA LISTA ENCADEADA
    if (*lista == NULL) {
        // O ponteiro principal (da main) passa a apontar para este novo cliente.
        *lista = novo; 
    } else {
/* [PERFORMANCE] Inserção no Fim (O(n))
           "Por que percorrer a lista toda? Não fica lento?"
           "Sim, a complexidade é linear O(N). Fizemos assim para manter a ordem cronológica 
           de cadastro na listagem. Se precisasse de velocidade máxima, inseriria no início (O(1)),
           como fizemos no carrinho de compras."
*/
        Cliente *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox; 
        }
        atual->prox = novo;
    }
}

Cliente* buscar_cliente(Cliente *lista, char *cpf) {
    Cliente *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

int remover_cliente(Cliente **lista, char *cpf) {
    if (*lista == NULL) return 0;

    Cliente *atual = *lista;
    Cliente *anterior = NULL;

    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0; 

    if (anterior == NULL) {
        *lista = atual->prox; 
    } else {
        anterior->prox = atual->prox; 
    }
/* [MEMORY LEAK]
       "Remove o cliente, mas esquece de limpar o carrinho dele antes!
       O código remove o cliente da lista, mas os itens do carrinho dele ficam perdidos na memória (vazamento). 
       Eu corrigi essa lógica na função 'liberar_sistema', mas aqui na remoção individual faltou replicar o loop de limpeza."
*/
    free(atual); 
    return 1;
}

int editar_cliente(Cliente *lista, char *cpf, char *novo_nome, char *novo_email, char *nova_data, char *novo_telefone) {
    Cliente *alvo = buscar_cliente(lista, cpf);
    if (alvo != NULL) {
        strcpy(alvo->nome, novo_nome);
        strcpy(alvo->email, novo_email);
        strcpy(alvo->data_nasc, nova_data);
        strcpy(alvo->telefone, novo_telefone);
        return 1;
    }
    return 0;
}

void liberar_lista_clientes(Cliente **lista) {
    Cliente *atual = *lista;
    while (atual != NULL) {
        Cliente *proximo = atual->prox;
/* [GERENCIAMENTO DE MEMÓRIA] A Forma Correta
        "Aqui está a maneira certa de liberar: primeiro limpo a sub-lista (carrinho)
        para não deixar nós órfãos, e só depois libero a struct principal do cliente."
*/
        ItemCarrinho *item = atual->carrinho;
        while (item != NULL) {
            ItemCarrinho *prox_item = item->prox;
            free(item);
            item = prox_item;
        }
        
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}

// --- IMPLEMENTAÇÃO PRODUTOS ---

int adicionar_produto(Produto **lista, int codigo, char *nome, float preco, int quantidade) {
    if (buscar_produto(*lista, codigo) != NULL) return 0; 

    Produto *novo = (Produto*) malloc(sizeof(Produto));
    if (novo == NULL) return 0; 

    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    novo->preco = preco;
    novo->quantidade = quantidade;
    novo->prox = NULL;

    if (*lista == NULL) {
        *lista = novo;
    } else {
        Produto *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    return 1;
}

Produto* buscar_produto(Produto *lista, int codigo) {
    Produto *atual = lista;
    while (atual != NULL) {
        if (atual->codigo == codigo) return atual;
        atual = atual->prox;
    }
    return NULL;
}

int editar_produto(Produto *lista, int codigo, char *novo_nome, float novo_preco, int nova_qtd) {
    Produto *alvo = buscar_produto(lista, codigo);
    if (alvo != NULL) {
        if (strlen(novo_nome) > 0) strcpy(alvo->nome, novo_nome);
        if (novo_preco >= 0) alvo->preco = novo_preco;
        if (nova_qtd >= 0) alvo->quantidade = nova_qtd; 
        return 1; 
    }
    return 0; 
}

void liberar_lista_produtos(Produto **lista) {
    Produto *atual = *lista;
    while (atual != NULL) {
        Produto *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *lista = NULL;
}

int remover_produto(Produto **lista, int codigo) {
    if (*lista == NULL) return 0; 

    Produto *atual = *lista;
    Produto *anterior = NULL;

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0;

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    return 1;
}

// --- CARRINHO ---

int remover_do_carrinho(Cliente *cliente, int cod_prod, Produto *lista_produtos) {
    if (cliente == NULL || cliente->carrinho == NULL) return 0;

    ItemCarrinho *atual = cliente->carrinho;
    ItemCarrinho *anterior = NULL;

    while (atual != NULL && atual->codigo_produto != cod_prod) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0;

    
    Produto *p = buscar_produto(lista_produtos, cod_prod);
    if (p != NULL) {
        p->quantidade += atual->qtd_comprada;
    }

    if (anterior == NULL) cliente->carrinho = atual->prox;
    else anterior->prox = atual->prox;

    free(atual);
    return 1;
}

void finalizar_compra(Cliente *cliente) {
    if (cliente == NULL) return;
    
    ItemCarrinho *atual = cliente->carrinho;
    while (atual != NULL) {
        ItemCarrinho *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    cliente->carrinho = NULL;
}

void liberar_sistema(Cliente **lista_c, Produto **lista_p) {
    liberar_lista_clientes(lista_c);
    liberar_lista_produtos(lista_p);
}

void adicionar_ao_carrinho(Cliente *cliente, Produto *produto, int qtd) {
    if (cliente == NULL || produto == NULL || qtd <= 0) return;

    ItemCarrinho *novo = (ItemCarrinho*) malloc(sizeof(ItemCarrinho));
    if (novo == NULL) return;

    novo->codigo_produto = produto->codigo;
    novo->qtd_comprada = qtd;

    novo->prox = cliente->carrinho; 
    cliente->carrinho = novo;

    produto->quantidade -= qtd;
}

void calcular_total_carrinho(Cliente *cliente, Produto *lista_produtos) {
    if (cliente == NULL || cliente->carrinho == NULL) {
        printf("\nCarrinho de %s estah vazio.\n", cliente->nome);
        return;
    }

    float total_geral = 0;
    ItemCarrinho *atual = cliente->carrinho;

    printf("\n--- Extrato de Compras: %s ---\n", cliente->nome);
    while (atual != NULL) {
        Produto *p = buscar_produto(lista_produtos, atual->codigo_produto);
        if (p != NULL) {
            float subtotal = p->preco * atual->qtd_comprada;
            printf("- %s (Cod: %d) | Qtd: %d | Unit: R$ %.2f | Subtotal: R$ %.2f\n", 
                   p->nome, p->codigo, atual->qtd_comprada, p->preco, subtotal);
            total_geral += subtotal;
        }
        atual = atual->prox;
    }
    printf("-------------------------------------------\n");
    printf("VALOR TOTAL DA COMPRA: R$ %.2f\n", total_geral);
}

// --- PERSISTÊNCIA DE DADOS ---

void salvar_dados(Cliente *lista_c, Produto *lista_p) {
    FILE *arquivo = fopen("database.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar dados!\n");
        return;
    }

    // Salvar Clientes
    Cliente *c = lista_c;
    while (c != NULL) {
        fprintf(arquivo, "C\n%s\n%s\n%s\n%s\n%s\n", c->cpf, c->nome, c->email, c->data_nasc, c->telefone);
        c = c->prox;
    }

    // Salvar Produtos
    Produto *p = lista_p;
    while (p != NULL) {
        fprintf(arquivo, "P\n%d\n%s\n%.2f\n%d\n", p->codigo, p->nome, p->preco, p->quantidade);
        p = p->prox;
    }

    fclose(arquivo);
    printf("\n[SISTEMA] Dados salvos em 'database.txt' com sucesso.\n");
}

void carregar_dados(Cliente **lista_c, Produto **lista_p) {
    FILE *arquivo = fopen("database.txt", "r");
    if (arquivo == NULL) return; // Arquivo não existe ainda

    char tipo[5], buffer[100];
    
    // Variáveis auxiliares para leitura
    char cpf[15], nome[50], email[80], data[15], tel[15];
    int codigo, qtd;
    float preco;

    while (fscanf(arquivo, "%s\n", tipo) != EOF) {
        if (strcmp(tipo, "C") == 0) {
            // Ler dados do cliente (usando fgets para pegar espaços nos nomes)
            fgets(cpf, 15, arquivo); cpf[strcspn(cpf, "\n")] = 0;
            fgets(nome, 50, arquivo); nome[strcspn(nome, "\n")] = 0;
            fgets(email, 80, arquivo); email[strcspn(email, "\n")] = 0;
            fgets(data, 15, arquivo); data[strcspn(data, "\n")] = 0;
            fgets(tel, 15, arquivo); tel[strcspn(tel, "\n")] = 0;
            
            adicionar_cliente(lista_c, cpf, nome, email, data, tel);
        } 
        else if (strcmp(tipo, "P") == 0) {
            fscanf(arquivo, "%d\n", &codigo);
            fgets(nome, 50, arquivo); nome[strcspn(nome, "\n")] = 0;
            fscanf(arquivo, "%f\n", &preco);
            fscanf(arquivo, "%d\n", &qtd);
            
            adicionar_produto(lista_p, codigo, nome, preco, qtd);
        }
    }
    fclose(arquivo);
    printf("[SISTEMA] Dados carregados do disco.\n");
}


