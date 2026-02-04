#include "../include/model.h"
#include <stdio.h>

/* [ARQUITETURA MVC] O Papel do Controller
   O Controller atua como o 'gerente' da loja.
   A View (vendedor) recebe o pedido do cliente, mas quem verifica se tem no estoque
   e autoriza a saída do produto é o Controller, antes de mexer no Model (estoque)."
*/

// camada intermediaria para adicionar itens
void ctrl_adicionar_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod, int qtd) {
/* [LÓGICA]
       "Busco o cliente e produto novamente para garantir que os dados existem no momento exato da ação.
       Poderia passar os ponteiros direto da View? Sim, mas buscar pelo ID garante que estou lidando com dados atualizados."
*/
    Cliente *c = buscar_cliente(lista_c, cpf);
    Produto *p = buscar_produto(lista_p, cod_prod);

    if (c == NULL || p == NULL) {
        printf("\n[ERRO] Cliente ou Produto não encontrado.\n");
        return;
    }

// [REGRA DE NEGÓCIO] Estoque
/* [DESTAQUE] A principal razão do Controller existir!
       Aqui você impede uma venda impossível (vender mais do que tem).
       Essa lógica não pertence à View (que só mostra dados) nem à Model (que só guarda dados).
*/
    if (p->quantidade < qtd) {
        printf("\n[ERRO] Estoque insuficiente! (Disponível: %d)\n", p->quantidade);
        return;
    }

    adicionar_ao_carrinho(c, p, qtd);
    printf("\n[SUCESSO] %d unidade(s) de '%s' adicionada(s) ao carrinho de %s.\n", qtd, p->nome, c->nome);
}

// Camada intermediária para remover item
void ctrl_remover_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod) {
    Cliente *c = buscar_cliente(lista_c, cpf);
    
    if (c == NULL) {
        printf("\n[ERRO] Cliente não encontrado.\n");
        return;
    }
/* [INTEGRAÇÃO]
       O Controller chama a função 'remover_do_carrinho' da Model, que retorna 1 (sucesso) ou 0 (falha).
       Com base nisso, o Controller decide qual mensagem mostrar.
*/

    if (remover_do_carrinho(c, cod_prod, lista_p)) {
        printf("\n[SUCESSO] Item removido e estoque devolvido.\n");
    } else {
        printf("\n[ERRO] Este produto não está no carrinho deste cliente.\n");
    }
}

// Camada Intermediária para Finalizar Compra
void ctrl_finalizar_venda(Cliente *lista_c, char *cpf, Produto *lista_p) {
    Cliente *c = buscar_cliente(lista_c, cpf);
/* [VALIDAÇÃO]
       Evita processar vendas vazias. Isso economiza processamento.
*/
    if (c == NULL || c->carrinho == NULL) {
        printf("\n[ERRO] Operação cancelada: Carrinho vazio ou cliente inexistente.\n");
        return;
    }

    // Mostra o total uma última vez antes de limpar
    calcular_total_carrinho(c, lista_p);
    // Efetiva a limpeza do carrinho (Model)
    finalizar_compra(c);
    printf("\n[VENDA FINALIZADA] Carrinho de %s foi processado e limpo.\n", c->nome);
}
