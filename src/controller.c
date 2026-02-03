#include "../include/model.h"
#include <stdio.h>

// camada intermediaria para adicionar itens
void ctrl_adicionar_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod, int qtd) {
    Cliente *c = buscar_cliente(lista_c, cpf);
    Produto *p = buscar_produto(lista_p, cod_prod);

    if (c == NULL || p == NULL) {
        printf("\n[ERRO] Cliente ou Produto não encontrado.\n");
        return;
    }

    // estoque
    if (p->quantidade < qtd) {
        printf("\n[ERRO] Estoque insuficiente! (Disponível: %d)\n", p->quantidade);
        return;
    }

    adicionar_ao_carrinho(c, p, qtd);
    printf("\n[SUCESSO] %d unidade(s) de '%s' adicionada(s) ao carrinho de %s.\n", qtd, p->nome, c->nome);
}

// camada intermediaria para remover item
void ctrl_remover_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod) {
    Cliente *c = buscar_cliente(lista_c, cpf);
    
    if (c == NULL) {
        printf("\n[ERRO] Cliente não encontrado.\n");
        return;
    }

    if (remover_do_carrinho(c, cod_prod, lista_p)) {
        printf("\n[SUCESSO] Item removido e estoque devolvido.\n");
    } else {
        printf("\n[ERRO] Este produto não está no carrinho deste cliente.\n");
    }
}

// camada Intermediária para Finalizar Compra
void ctrl_finalizar_venda(Cliente *lista_c, char *cpf, Produto *lista_p) {
    Cliente *c = buscar_cliente(lista_c, cpf);

    if (c == NULL || c->carrinho == NULL) {
        printf("\n[ERRO] Operação cancelada: Carrinho vazio ou cliente inexistente.\n");
        return;
    }

    calcular_total_carrinho(c, lista_p);
    
    finalizar_compra(c);
    printf("\n[VENDA FINALIZADA] Carrinho de %s foi processado e limpo.\n", c->nome);
}