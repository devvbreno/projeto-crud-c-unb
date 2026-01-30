#include "../include/model.h"
#include <stdio.h>
#include <stdlib.h>

void processar_compra(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod, int qtd) {
    Cliente *c = buscar_cliente(lista_c, cpf);
    Produto *p = buscar_produto(lista_p, cod_prod);

    if (c == NULL || p == NULL) {
        printf("Erro: Cliente ou Produto nao encontrado!\n");
        return;
    }

    // verifica o estoque
    if (p->quantidade < qtd) {
        printf("Erro: Estoque insuficiente!\n");
        return;
    }

    // alocação dinâmica do item no carrinho
    ItemCarrinho *novo = (ItemCarrinho*) malloc(sizeof(ItemCarrinho));
    if (novo == NULL) return;

    novo->codigo_produto = p->codigo;
    novo->qtd_comprada = qtd;

    novo->prox = c->carrinho;
    c->carrinho = novo;

    p->quantidade -= qtd;
    printf("Sucesso: Item adicionado ao carrinho de %s!\n", c->nome);
}