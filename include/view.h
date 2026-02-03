#ifndef VIEW_H
#define VIEW_H

#include "model.h"

// --- ÁREA DE GERENCIAMENTO DE CLIENTES ---

void menu_gerenciar_clientes(Cliente **lista);
void listar_todos_clientes(Cliente *lista);
void menu_principal(Cliente **lista_c, Produto **lista_p);
void menu_vendas(Cliente **lista_c, Produto **lista_p);

void ctrl_adicionar_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod, int qtd);
void ctrl_remover_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod);
void ctrl_finalizar_venda(Cliente *lista_c, char *cpf, Produto *lista_p);
#endif
