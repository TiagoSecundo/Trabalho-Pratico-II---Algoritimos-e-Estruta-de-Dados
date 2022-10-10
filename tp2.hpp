#ifndef PILHA_H
#define PILHA_H
#include <fstream>
#include <stack>

#define MAXTAM 10
#define MAX_ENTREGA 7

using namespace std;

typedef struct // struct cadastrando variaveis usadas durante o programa
{
    int codigo;
    int produtos[MAXTAM];
    float valor_pedido = 0;
    float distancia = 0;
    int tamanho_produto = 0;
} Pedido;

// cabeçario das funçoes
void menu();
void Cardapio();
void IncludePedido(Pedido id, stack<Pedido> *RecebePedido, int *cont);
void ListarPedidos(stack<Pedido> RecebePedido, string nomeproduto[]);
void Consultar_Pedido(stack<Pedido> RecebePedido, string nomeproduto[]);
void Imprime_Entrega(stack<Pedido> *EntregaPedidos, stack<Pedido> *RecebePedido);
void lancar_entrega(stack<Pedido> EntregaPedidos);
void lerArquivo(stack<Pedido> *EntregaPedido, int *id);
#endif