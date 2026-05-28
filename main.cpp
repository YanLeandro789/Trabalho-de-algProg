#include <iostream>
#include <fstream>
//YAN VIADO
using namespace std;

//add Artigo (Alocação Dinâmica)
//Buscar Artigo (Recursivo)
//Atualizar Citaçoes (Passagem por referência).
//Gerar Relatório por Ano (Arquivo em testo)
//Exibir Estatisticas de Citaçoes (Recursivo)
//Sair (Salvar em binario ".dat" e liberar memoria)

struct Artigo{
    char titulo[50]; //titulo
    char autor[30]; //autor principal
    int anoPB; //ano Publicado
    int DOI; //DOI (identificador digital)

    //nó
    Artigo* next;

    
};

void insertArtigoFront(Artigo*& head, char tit, char atr, int Ano, int doi ){
    Artigo* NvArt = new Artigo(tit,atr,Ano,doi);
    head->next = NvArt;
    delete NvArt;
}

int main(){


    int escolha; // variavel para celeção que vai usar
    while (escolha != 6) 
    {
        cout << "1. Adicionar Artigo" << endl;
        cout << "2. Buscar Artigo" << endl;
        cout << "3. Atualizar Citações" << endl;
        cout << "4. Gerar Relatório por Ano" << endl;
        cout << "5. Exibir Estatísticas de Citações" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> escolha;
        if (escolha == 1) {
            // Adicionar Artigo
    }
        else if (escolha == 2) {
            // Buscar Artigo
        }
        else if (escolha == 3) {
            // Atualizar Citações
        }
        else if (escolha == 4) {
            // Gerar Relatório por Ano
        }
        else if (escolha == 5) {
            // Exibir Estatísticas de Citações
        }
        else if (escolha == 6) {
            // Sair (Salvar em binário ".dat" e liberar memória)
        }
        else {
            cout << "Opção inválida. Tente novamente." << endl;
        }

    return 0;
}