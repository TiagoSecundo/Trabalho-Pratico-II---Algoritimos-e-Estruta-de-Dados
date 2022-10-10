#include <iostream>
#include <windows.h>
#include <stack>
#include <fstream>
#include "tp2.hpp"

using namespace std;

void menu() // escreve o menu principal no programa
{

    cout << " ___________________________________" << endl;
    cout << "|                                   |" << endl;
    cout << "|                                   |" << endl;
    cout << "|        Delivery Sorveteria        |" << endl;
    cout << "|                                   |" << endl;
    cout << "|___________________________________|" << endl
         << endl
         << endl
         << endl;
    cout << "1. Inclusao de um novo pedido. " << endl;
    cout << "2. Listar pedidos. " << endl;
    cout << "3. Ver cardapio. " << endl;
    cout << "4. Consultar pedidos. " << endl;
    cout << "5. Imprimir lista de entrega." << endl;
    cout << "6. Enviar entrega. " << endl;
    cout << "7. Imprimir lista apos entrega. " << endl;
    cout << "8. Sair " << endl;
}

void IncludePedido(Pedido id, stack<Pedido> *RecebePedido, int *cont)
{

    int recebeID;
    float preco[] = {0.0, 10.50, 13.75, 18.0, 12.00, 16.50, 19.00, 12.00, 15.00, 17.50}; // armazendando vpreços do produto
    id.codigo = *cont;

    while (recebeID != 0 && id.tamanho_produto < 10) // veririfica o id do produto
    {

        Cardapio();
        cin >> recebeID;
        if (recebeID != 0) // compara a opçao desejada e se for diferente de 0 soma a quantidade dos produtos que o usuario deseja
        {

            id.valor_pedido += preco[recebeID];
            id.produtos[id.tamanho_produto] = recebeID;
            id.tamanho_produto++;
        }
    }
    cout << "Insira distancia da entrega: (em quilometros)" << endl;
    cin >> id.distancia;

    if (id.distancia == 0 && id.tamanho_produto == 0) // compara se a distancia é zero ou se o id do produto é zero
    {
        return;
    }
    else
    {
        *cont += 1;
        RecebePedido->push(id);
    }
}

void Cardapio() // escreve as opcoes que o usuario tem pra escolher
{

    cout << " ___________________________________" << endl;
    cout << "|                                   |" << endl;
    cout << "|                                   |" << endl;
    cout << "|             Cardapio              |" << endl;
    cout << "|                                   |" << endl;
    cout << "|___________________________________|" << endl
         << endl
         << endl
         << "Insira opcao desejada: "
         << endl;
    cout << "1. Acai (300ml)................... R$10,50" << endl;
    cout << "2. Acai (600ml)................... R$13,75" << endl;
    cout << "3. Acai (900ml)................... R$18,00" << endl;
    cout << "------------------------------------------" << endl;
    cout << "4. Milk Shake (300ml)............. R$12,00" << endl;
    cout << "5. Milk Shake (600ml)............. R$16,50" << endl;
    cout << "6. Milk Shake (900ml)............. R$19,00" << endl;
    cout << "------------------------------------------" << endl;
    cout << "7. Sorvete (300ml)................ R$12,00" << endl;
    cout << "8. Sorvete (600ml)................ R$15,00" << endl;
    cout << "9. Sorvete (900ml)................ R$17,50" << endl;
    cout << "0. Para finalizar pedido " << endl;
    cout << "------------------------------------------" << endl
         << endl;
}

void ListarPedidos(stack<Pedido> RecebePedido, string nomeproduto[])
{
    stack<Pedido> aux;

    while (!RecebePedido.empty())
    {
        aux.push(RecebePedido.top());
        RecebePedido.pop();
    }
    RecebePedido.swap(aux);

    while (!RecebePedido.empty())
    {
        cout << "Codigo de entrega do pedido: " << RecebePedido.top().codigo << endl;
        cout << "Valor total do pedido: R$" << RecebePedido.top().valor_pedido << endl;
        for (int i = 0; i < RecebePedido.top().tamanho_produto; i++)
        {
            cout << RecebePedido.top().produtos[i] << " " << nomeproduto[RecebePedido.top().produtos[i]] << endl;
        }
        cout << endl;
        RecebePedido.pop();
    }
    system("pause");
    system("cls");
}

void Consultar_Pedido(stack<Pedido> RecebePedido, string nomeproduto[]) // usada para pesquisar o produto atraves do id
{

    int id;
    cout << " ___________________________________" << endl;
    cout << "|                                   |" << endl;
    cout << "|                                   |" << endl;
    cout << "|         Consultar Pedido          |" << endl;
    cout << "|                                   |" << endl;
    cout << "|___________________________________|" << endl
         << endl
         << endl;
    cout << "Insira Id do pedido: " << endl;
    cin >> id;
    while (!RecebePedido.empty()) // percorre a pilha
    {

        if (id == RecebePedido.top().codigo) // compara o id do produto e soma o valor final da compra
        {
            cout << "ID: " << RecebePedido.top().codigo << endl
                 << "R$: " << RecebePedido.top().valor_pedido << endl;
            for (int i = 0; i < RecebePedido.top().tamanho_produto; i++)
            {
                cout << RecebePedido.top().produtos[i] << " " << nomeproduto[RecebePedido.top().produtos[i]] << endl;
            }
        }
        cout << endl;
        RecebePedido.pop();
    }
}

void Imprime_Entrega(stack<Pedido> *EntregaPedidos, stack<Pedido> *RecebePedido) // organiza e imprime a ordem de acordo com a menor distancia
{
    stack<Pedido> aux;
    int id, tamanho;
    float maior_distancia = 0.0;
    tamanho = RecebePedido->size();
    for (int i = 0; i < tamanho; i++) // percorre o tamanho da pilha
    {
        maior_distancia = 0;
        while (!RecebePedido->empty())
        {
            aux.push(RecebePedido->top());
            RecebePedido->pop();
            if (aux.top().distancia > maior_distancia)
            {
                maior_distancia = aux.top().distancia;
                id = aux.top().codigo;
            }
        }

        while (!aux.empty()) // percorre e passa os elementos para outra pilha, ja visando ordem de entrega
        {
            if (aux.top().codigo == id)
            {
                EntregaPedidos->push(aux.top());
            }
            else
            {
                RecebePedido->push(aux.top());
            }
            aux.pop();
        }
    }

    cout << "Os pedidos estao prontos para entrega. " << endl;
}

void lancar_entrega(stack<Pedido> *EntregaPedidos) // emite as intregas
{

    if (EntregaPedidos->empty()) // mensagem de erro para acusar caso a pilha esteja vazia
    {
        cout << "ERRO AO RETIRAR O PEDIDO..." << endl;
    }
    else // emite entrega
    {
        EntregaPedidos->pop();
        cout << "Pedido retirado com sucesso. " << endl;
    }
}

void lerArquivo(stack<Pedido> *EntregaPedido, int *id)
{
    FILE *file = fopen("lanchonete.bin", "r");
    Pedido pedido;
    if (file != NULL)
    {
        while (fread(&pedido, sizeof(Pedido), 1, file))
        {
            if (pedido.codigo > *id)
            {
                *id = pedido.codigo;
            }
            EntregaPedido->push(pedido);
        }
    }
}

void salvarArquivo(stack <Pedido> EntregaPedido)
{
    FILE *file = fopen("lanchonete.bin", "w");
    Pedido pedido;
    while ( !EntregaPedido.empty())
    {
        pedido = EntregaPedido.top();
        EntregaPedido.pop();
        fwrite(&pedido, sizeof(Pedido), 1, file);
    }
}