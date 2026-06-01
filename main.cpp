#include <iostream>
#include <fstream>

using namespace std;

struct Artigo {
    char titulo[100];
    char autor[50];
    int  anoPB;
    int  DOI;
    int  citacoes;
    Artigo* next;
};

// Novo artigo
void insertArtigo(Artigo*& head) {
    Artigo* novo = new Artigo();

    cout << "Inserir Novo Artigo\n";

    cout << "Titulo: ";
    cin.ignore();
    cin.getline(novo->titulo, 100);

    cout << "Autor principal: ";
    cin.getline(novo->autor, 50);

    cout << "Ano de publicacao: ";
    cin >> novo->anoPB;

    cout << "DOI (numero inteiro): ";
    cin >> novo->DOI;

    cout << "Numero de citacoes: ";
    cin >> novo->citacoes;

    // insere na frente da lista
    novo->next = head;
    head = novo;

    cout << "Artigo inserido com sucesso!\n";
}


Artigo* buscarPorDOI(Artigo* head, int doi) {
    //caso base
    if (head == nullptr)
        return nullptr;

    if (head->DOI == doi)
        return head;

    return buscarPorDOI(head->next, doi);
}



void menuBuscar(Artigo* head) {
    int doi;
    cout << "Buscar Artigo por DOI\n";
    cout << "Digite o DOI: ";
    cin >> doi;

    Artigo* encontrado = buscarPorDOI(head, doi);

    if (encontrado == nullptr) {
        cout << "Artigo nao encontrado.\n";
    } else {
        cout << "Artigo Encontrado\n";
        cout << "Titulo   : " << encontrado->titulo   << "\n";
        cout << "Autor    : " << encontrado->autor    << "\n";
        cout << "Ano      : " << encontrado->anoPB    << "\n";
        cout << "DOI      : " << encontrado->DOI      << "\n";
        cout << "Citacoes : " << encontrado->citacoes << "\n";
    }
}


// atualizar citaçoes

void atualizarCitacoes(int& citacoes, int incremento) {
    citacoes += incremento;
}


void menuAtualizarCitacoes(Artigo* head) {
    int doi, incremento;
    cout << "Atualizar Citacoes\n";
    cout << "Digite o DOI do artigo: ";
    cin >> doi;

    Artigo* art = buscarPorDOI(head, doi);

    if (art == nullptr) {
        cout << "Artigo nao encontrado.\n";
        return;
    }

    cout << "Citacoes atuais: " << art->citacoes << "\n";
    cout << "Quantas citacoes deseja adicionar? ";
    cin >> incremento;

    atualizarCitacoes(art->citacoes, incremento);  

    cout << "Citacoes atualizadas para: " << art->citacoes << "\n";
}

//gerar relatorio por ano
void gerarRelatorio(Artigo* head) {
    int anoInicio, anoFim;
    cout << "Gerar Relatorio por Ano";
    cout << "Ano inicial: ";
    cin >> anoInicio;
    cout << "Ano final  : ";
    cin >> anoFim;

    ofstream arquivo("relatorio.txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de relatorio!\n";
        return;
    }

    arquivo << "Relatorio de Artigos (" << anoInicio << " - " << anoFim << ")\n\n";

    Artigo* atual = head;
    int count = 0;

    while (atual != nullptr) {
        if (atual->anoPB >= anoInicio && atual->anoPB <= anoFim) {
            arquivo << "Titulo   : " << atual->titulo   << "\n";
            arquivo << "Autor    : " << atual->autor    << "\n";
            arquivo << "Ano      : " << atual->anoPB    << "\n";
            arquivo << "DOI      : " << atual->DOI      << "\n";
            arquivo << "Citacoes : " << atual->citacoes << "\n";
            arquivo << "-----------------------------------\n";
            count++;
        }
        atual = atual->next;
    }

    arquivo << "\nTotal de artigos no periodo: " << count << "\n";
    arquivo.close();

    cout << "Relatorio gerado em 'relatorio.txt' com " << count << " artigos.\n";
}


// exibir Recursivo
int totalCitacoesRecursivo(Artigo* head) {
    // caso base
    if (head == nullptr)
        return 0;

    return head->citacoes + totalCitacoesRecursivo(head->next);
}



void exibirEstatisticas(Artigo* head) {
    cout << "Estatisticas de Citacoes\n";

    if (head == nullptr) {
        cout << "Acervo vazio.\n";
        return;
    }

    int total = totalCitacoesRecursivo(head);

    int count = 0;
    int maxCit = -1;
    char maisCtado[100];
    maisCtado[0] = '\0';

    Artigo* atual = head;
    while (atual != nullptr) {
        count++;
        if (atual->citacoes > maxCit) {
            maxCit = atual->citacoes;
            for (int i = 0; i < 100; i++) maisCtado[i] = atual->titulo[i];
        }
        atual = atual->next;
    }

    cout << "Total de artigos  : " << count         << "\n";
    cout << "Total de citacoes : " << total         << "\n";
    cout << "Media de citacoes : " << (double)total / count << "\n";
    cout << "Artigo mais citado: " << maisCtado     << " (" << maxCit << " citacoes)\n";
}

//salvar e carregar binario
void salvarBinario(Artigo* head) {
    ofstream arquivo("acervo.dat", ios::binary);

    if (!arquivo.is_open()) {
        cout << "Erro ao salvar o acervo!\n";
        return;
    }

    Artigo* atual = head;
    while (atual != nullptr) {
        arquivo.write(reinterpret_cast<char*>(atual), sizeof(Artigo) - sizeof(Artigo*));
        atual = atual->next;
    }

    arquivo.close();
    cout << "Acervo salvo\n";
}



void carregarBinario(Artigo*& head) {
    ifstream arquivo("acervo.dat", ios::binary);

    if (!arquivo.is_open()) {
        return;
    }

    int tamDados = sizeof(Artigo) - sizeof(Artigo*);
    char buffer[sizeof(Artigo)];

    while (arquivo.read(buffer, tamDados)) {
        Artigo* novo = new Artigo();

        for (int i = 0; i < 100; i++) novo->titulo[i] = buffer[i];
        for (int i = 0; i < 50;  i++) novo->autor[i]  = buffer[100 + i];

        int* campos = reinterpret_cast<int*>(buffer + 150);
        novo->anoPB    = campos[0];
        novo->DOI      = campos[1];
        novo->citacoes = campos[2];

        novo->next = head;
        head = novo;
    }
    //a

    arquivo.close();
    cout << "Acervo carregado com sucesso!\n";
}

// Liberar memoria
void liberarMemoria(Artigo*& head) {
    while (head != nullptr) {
        Artigo* temp = head;
        head = head->next;
        delete temp;
    }
}


int main() {
    Artigo* head = nullptr;

    carregarBinario(head);

    int opcao;

    while(opcao != 6){
        cout << "1. Inserir Novo Artigo\n";
        cout << "2. Buscar Artigo por DOI\n";
        cout << "3. Atualizar Citacoes\n";
        cout << "4. Gerar Relatorio por Ano\n";
        cout << "5. Exibir Estatisticas de Citacoes\n";
        cout << "6. Sair\n";
        cout << ">>> ";
        cin >> opcao;
        
        if (opcao == 1 ){
            insertArtigo(head);
        }else if(opcao == 2){
            menuBuscar(head);  
        }else if(opcao == 3){
            menuAtualizarCitacoes(head);   
        }else if(opcao == 4){
            gerarRelatorio(head);  
        }else if(opcao == 5){
           exibirEstatisticas(head);   
        }else if(opcao == 6){
            salvarBinario(head);
            liberarMemoria(head);
            cout << "Memoria liberada.\n";
        }else{
           cout << "Opcao invalida!\n";
        }


    }
   

    return 0;
}