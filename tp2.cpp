#include <iostream>
#include <stack>
#include <fstream>
#include "funcoes.cpp"
#include "tp2.hpp"

using namespace std;

int main()
{
    stack<Pedido> pedido, entregapedido; // pilhas usadas no programa
    Pedido id;
    string produtos[] = {" ", "Acai (300ml) ", "Acai (600ml)", "Acai (900ml)",
                         "Milk Shake (300ml)", "Milk Shake (600ml)",
                         "Milk Shake (900ml)", "Sorvete (300ml)", "Sorvete (600ml)", "Sorvete (900ml)"}; // usado para comparar produtos
    int op, cont = 0;

    lerArquivo(&pedido, &cont);

    cont++;

    do // percorrer as 8 opcoes do usuario
    {
        menu();
        cout << "Insira opcao desejada: " << endl;
        cin >> op;

        switch (op) // usado para armazenar as funçoes em casos especificos
        {
        case 1:
            IncludePedido(id, &pedido, &cont);
            break;

        case 2:
            ListarPedidos(pedido, produtos);
            break;

        case 3:
            Cardapio();

            break;

        case 4:
            Consultar_Pedido(pedido, produtos);
            break;

        case 5:
            Imprime_Entrega(&entregapedido, &pedido);
            ListarPedidos(entregapedido, produtos);
            break;

        case 6:
            lancar_entrega(&entregapedido);
            break;

        case 7:
            ListarPedidos(entregapedido, produtos);
            break;

        case 8:
            break;
        }
        system("pause");
        system("cls");
    } while (op != 8);
    salvarArquivo(pedido);
    return 0;
}