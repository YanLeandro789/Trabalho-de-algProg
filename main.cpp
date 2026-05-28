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


    return 0;
}