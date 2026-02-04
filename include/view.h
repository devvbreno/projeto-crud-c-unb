/* [COMPILAÇÃO]
   "São os 'Header Guards' (Guardas de Cabeçalho). Eles impedem que este arquivo seja incluído
   duas vezes no mesmo código, o que causaria erro de redefinição de funções durante a compilação."
*/

#ifndef VIEW_H
#define VIEW_H

/* [DEPENDÊNCIA]
   "Os protótipos das funções abaixo usam os tipos 'Cliente' e 'Produto' (nos parâmetros).
   Como essas structs estão definidas no model.h, eu preciso importá-lo para o compilador reconhecer esses tipos."
*/

#include "model.h"

// --- ÁREA DE GERENCIAMENTO DE CLIENTES ---

/* [PONTEIROS] Por que 'Cliente **lista' (duplo)?
   "Como esse menu chama as funções de Cadastrar e Remover (que alteram o início da lista),
   eu preciso passar o endereço do ponteiro principal para que as alterações persistam quando voltar para a main."
*/
void menu_gerenciar_clientes(Cliente **lista);

/* [PONTEIROS] E por que 'Cliente *lista' (simples)?
   "A listagem é uma operação apenas de LEITURA. Não preciso alterar onde a lista começa,
   apenas percorrer ela. Passar ponteiro simples é mais seguro e evita alterações acidentais."
*/
void listar_todos_clientes(Cliente *lista);
void menu_principal(Cliente **lista_c, Produto **lista_p);
void menu_vendas(Cliente **lista_c, Produto **lista_p);
void menu_gerenciar_produtos(Produto **lista);
void menu_vendas(Cliente **lista_c, Produto **lista_p);

/* [ARQUITETURA MVC]
   Essas funções começam com 'ctrl_'. Elas não estão implementadas no view.c, mas sim no controller.c.
   "Como a View (interface) é quem CHAMA o Controller, ela precisa conhecer esses protótipos para compilar.
   Colocá-los aqui permite que o arquivo 'view.c' enxergue as funções do 'controller.c'."
*/

void ctrl_adicionar_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod, int qtd);
void ctrl_remover_item(Cliente *lista_c, Produto *lista_p, char *cpf, int cod_prod);
void ctrl_finalizar_venda(Cliente *lista_c, char *cpf, Produto *lista_p);
#endif


