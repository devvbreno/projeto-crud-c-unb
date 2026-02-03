#include <stdio.h>
#include <stdlib.h>
#include "../include/model.h"
#include "../include/view.h"

int main() {
    // 1. Inicializa ponteiros como NULL (Lista Vazia)
    Cliente *lista_c = NULL;
    Produto *lista_p = NULL;

    // 2. Carrega dados do arquivo "database.txt" se existir
    carregar_dados(&lista_c, &lista_p);

    // 3. Executa o Menu
    menu_principal(&lista_c, &lista_p);

    // 4. Limpa a memória RAM antes de fechar (Boa prática)
    // Nota: Os dados já foram salvos dentro do menu_principal ao digitar 0
    liberar_sistema(&lista_c, &lista_p);

    return 0; 
}
