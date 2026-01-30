#ifndef VIEW_H
#define VIEW_H

#include "model.h"

// --- ÁREA DE GERENCIAMENTO DE CLIENTES ---

void menu_gerenciar_clientes(Cliente **lista);
void listar_todos_clientes(Cliente *lista);
void menu_principal(Cliente **lista_c, Produto **lista_p);

#endif
