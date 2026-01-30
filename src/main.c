#include <stdio.h>
#include <stdlib.h>
#include "../include/model.h"
#include "../include/view.h"

int main() {
    // inicializa as listas
    Cliente *listar_clientes = NULL;
    Produto *listar_produtos = NULL;

    // o loop do menu deve ser chamado aqui
    menu_principal(&listar_clientes, &listar_produtos);

    liberar_sistema(&listar_clientes, &listar_produtos);

    printf ("\n Sistema encerrado com seguranca. \n");
    return 0; 
}