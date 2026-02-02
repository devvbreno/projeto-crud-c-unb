#include <stdio.h>
#include <stdlib.h>
#include "../include/model.h"
#include "../include/view.h"

int main() {
    // inicializa as listas
    Cliente *lista_c = NULL;
    Produto *lista_p = NULL;

    // o loop do menu deve ser chamado aqui
    menu_principal(&lista_c, &lista_p);
    liberar_sistema(&lista_c, &lista_p);

    printf ("\n Sistema encerrado com seguranca. \n");
    return 0; 
}