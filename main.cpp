#include <iostream>
#include <fstream>

using namespace std;

struct Artigo { // criamos a struct Artigo para armazenar os dados de cada artigo e o ponteiro para o próximo
    char titulo[100]; // titulo do artigo
    char autor[50];   // autor principal do artigo
    int  anoPB;       // ano de publicação do artigo
    int  DOI;         // número DOI do artigo
    int  citacoes;    // número de citacoes do artigo
    Artigo* next;     // ponteiro para o próximo artigo na lista
};

// Novo artigo
void insertArtigo(Artigo*& head) { //funcao para inserir um novo artigo no início da lista 
    Artigo* novo = new Artigo(); //criamos um novo artigo alocando dinamicamente

    cout << "Inserir Novo Artigo\n"; //exibimos o menu para inserir um novo artigo

    cout << "Titulo: "; // solicitamos o título do artigo
    cin.ignore(); //limpamos o buffer do teclado para evitar problemas com getline após cin
    cin.getline(novo->titulo, 100); //lê o título do artigo usando getline para permitir espaços

    cout << "Autor principal: "; // solicitamos o autor principal do artigo
    cin.getline(novo->autor, 50); //lê o nome do autor usando getline para permitir espaços

    cout << "Ano de publicacao: "; // solicitamos o ano de publicação do artigo
    cin >> novo->anoPB; //lê o ano de publicação do artigo

    cout << "DOI (numero inteiro): "; // solicitamos o número DOI do artigo
    cin >> novo->DOI; //lê o número DOI do artigo

    cout << "Numero de citacoes: "; // solicitamos o número de citações do artigo
    cin >> novo->citacoes; //lê o número de citações do artigo

    // insere na frente da lista
    novo->next = head; // o próximo do novo artigo aponta para o atual head da lista
    head = novo; // o head da lista agora é o novo artigo

    cout << "Artigo inserido com sucesso!\n"; // confirmamos que o artigo foi inserido com sucesso
}



// procura por recursiva
Artigo* buscarPorDOI(Artigo* head, int doi) { // função recursiva para buscar um artigo pelo número DOI
    //caso base
    if (head == nullptr) // verificamos se chegamos ao final da lista sem encontrar o artigo
        return nullptr; // se for o caso, retornamos nullptr para indicar que o artigo não foi encontrado

    if (head->DOI == doi)// verificamos se o DOI do artigo atual é igual ao DOI que estamos buscando
        return head;// se for o caso, retornamos um ponteiro para o artigo encontrado

    return buscarPorDOI(head->next, doi); // se o DOI do artigo atual não for igual ao DOI que estamos buscando, chamamos a função recursivamente para o próximo artigo na lista
}



void menuBuscar(Artigo* head) { // função para exibir o menu de busca de artigo por DOI
    int doi; // variável para armazenar o número DOI que o usuário deseja buscar
    cout << "Buscar Artigo por DOI\n"; // exibimos o menu para buscar um artigo por DOI
    cout << "Digite o DOI: "; // solicitamos ao usuário que digite o número DOI do artigo que deseja buscar
    cin >> doi; //lê o número DOI digitado pelo usuário

    Artigo* encontrado = buscarPorDOI(head, doi); // chamamos a função de busca recursiva para encontrar o artigo com o número DOI digitado pelo usuário e armazenamos o resultado em um ponteiro chamado "encontrado"

    if (encontrado == nullptr) { // verificamos se o ponteiro "encontrado" é nullptr, o que indica que o artigo não foi encontrado na lista
        cout << "Artigo nao encontrado.\n"; // imrimimos uma mensagem informando que o artigo não foi encontrado
    } else {
        cout << "Artigo Encontrado\n"; // imprimemos uma mensagem informando que o artigo foi encontrado
        cout << "Titulo   : " << encontrado->titulo   << "\n"; // imprimimos o título do artigo encontrado
        cout << "Autor    : " << encontrado->autor    << "\n"; // imprimimos o autor principal do artigo encontrado
        cout << "Ano      : " << encontrado->anoPB    << "\n"; // imprimimos o ano de publicação do artigo encontrado
        cout << "DOI      : " << encontrado->DOI      << "\n"; // imprimimos o número DOI do artigo encontrado
        cout << "Citacoes : " << encontrado->citacoes << "\n"; // imprimimos o número de citações do artigo encontradoz\Z
    }
}


// atualizar citaçoes

void atualizarCitacoes(int& citacoes, int incremento) { // função para atualizar o número de citações de um artigo, recebe uma referência para o número de citações e o valor do incremento
    citacoes += incremento; // atualizamos o número de citações somando o valor do incremento ao número atual de citações
}


void menuAtualizarCitacoes(Artigo* head) { // função para exibir o menu de atualização de citações de um artigo
    int doi, incremento; // variáveis para armazenar o número DOI do artigo que o usuário deseja atualizar e o valor do incremento que o usuário deseja adicionar ao número de citações do artigo
    cout << "Atualizar Citacoes\n"; // exibimos o menu para atualizar as citações de um artigo
    cout << "Digite o DOI do artigo: "; // solicitamos ao usuário que digite o número DOI do artigo que deseja atualizar as citações
    cin >> doi; //lê o número DOI digitado pelo usuário

    Artigo* art = buscarPorDOI(head, doi); // chamamos a função de busca recursiva para encontrar o artigo com o número DOI digitado pelo usuário e armazenamos o resultado em um ponteiro chamado "art"

    if (art == nullptr) { // verificamos se o ponteiro "art" é nullptr, o que indica que o artigo não foi encontrado na lista
        cout << "Artigo nao encontrado.\n"; // se for o caso, imprimimos uma mensagem informando que o artigo não foi encontrado e retornamos para o menu principal
        return; // se o artigo for encontrado, continuamos com a atualização das citações
    }

    cout << "Citacoes atuais: " << art->citacoes << "\n";// imprimimos o número atual de citações do artigo encontrado
    cout << "Quantas citacoes deseja adicionar? "; // solicitamos ao usuário que digite o valor do incremento que deseja adicionar ao número de citações do artigo
    cin >> incremento; //lê o valor do incremento digitado pelo usuário

    atualizarCitacoes(art->citacoes, incremento);  // chamamos a função para atualizar o número de citações do artigo, passando a referência para o número de citações do artigo encontrado e o valor do incremento digitado pelo usuário

    cout << "Citacoes atualizadas para: " << art->citacoes << "\n"; // imprimimos o número atualizado de citações do artigo encontrado para confirmar que a atualização foi realizada com sucesso
}

//gerar relatorio por ano
void gerarRelatorio(Artigo* head) { // função para gerar um relatório de artigos publicados em um determinado período de anos
    int anoInicio, anoFim; // variáveis para armazenar o ano inicial e o ano final do período que o usuário deseja gerar o relatório
    cout << "Gerar Relatorio por Ano"; // exibimos o menu para gerar um relatório de artigos por ano
    cout << "Ano inicial: "; // solicitamos ao usuário que digite o ano inicial do período para o qual deseja gerar o relatório
    cin >> anoInicio; //lê o ano inicial digitado pelo usuário
    cout << "Ano final  : ";// solicitamos ao usuário que digite o ano final do período para o qual deseja gerar o relatório
    cin >> anoFim; //lê o ano final digitado pelo usuário

    ofstream arquivo("relatorio.txt"); // criamos um objeto ofstream para abrir o arquivo "relatorio.txt" para escrita

    if (!arquivo.is_open()) { // verificamos se o arquivo foi aberto com sucesso
        cout << "Erro ao abrir o arquivo de relatorio!\n"; // se não for o caso, imprimimos uma mensagem de erro e retornamos para o menu principal
        return;// se o arquivo foi aberto com sucesso, continuamos com a geração do relatório
    }

    arquivo << "Relatorio de Artigos (" << anoInicio << " - " << anoFim << ")\n\n"; // escrevemos o título do relatório no arquivo, indicando o período de anos para o qual o relatório foi gerado

    Artigo* atual = head; // criamos um ponteiro "atual" para percorrer a lista de artigos, começando pelo head da lista
    int count = 0; // variável para contar o número de artigos que se encaixam no período de anos especificado pelo usuário

    while (atual != nullptr) { // percorremos a lista de artigos enquanto o ponteiro "atual" não for nullptr, o que indica que chegamos ao final da lista
        if (atual->anoPB >= anoInicio && atual->anoPB <= anoFim) { // verificamos se o ano de publicação do artigo atual está dentro do período de anos especificado pelo usuário
            arquivo << "Titulo   : " << atual->titulo   << "\n"; // se for o caso, escrevemos os dados do artigo no arquivo de relatório
            arquivo << "Autor    : " << atual->autor    << "\n"; // escrevemos o autor principal do artigo no arquivo de relatório
            arquivo << "Ano      : " << atual->anoPB    << "\n"; // escrevemos o ano de publicação do artigo no arquivo de relatório
            arquivo << "DOI      : " << atual->DOI      << "\n"; // escrevemos o número DOI do artigo no arquivo de relatório
            arquivo << "Citacoes : " << atual->citacoes << "\n"; // escrevemos o número de citações do artigo no arquivo de relatório
            arquivo << "-----------------------------------\n";// escrevemos uma linha de separação entre os artigos no arquivo de relatório
            count++; // incrementamos o contador de artigos que se encaixam no período de anos especificado pelo usuário
        }
        atual = atual->next; // movemos o ponteiro "atual" para o próximo artigo na lista para continuar a verificação dos artigos seguintes
    }

    arquivo << "\nTotal de artigos no periodo: " << count << "\n"; // escrevemos o total de artigos que se encaixam no período de anos especificado pelo usuário no final do arquivo de relatório
    arquivo.close(); // fechamos o arquivo de relatório para garantir que os dados sejam salvos corretamente

    cout << "Relatorio gerado em 'relatorio.txt' com " << count << " artigos.\n"; // imprimimos uma mensagem informando que o relatório foi gerado com sucesso e indicando o número de artigos que foram incluídos no relatório
}


// exibir Recursivo
int totalCitacoesRecursivo(Artigo* head) {//fucao recursiva para calcular o total de citações de todos os artigos na lista, recebe um ponteiro para o head da lista de artigos
    // caso base
    if (head == nullptr)// verificamos se chegamos ao final da lista, o que indica que não há mais artigos para contar as citações
        return 0;// se for o caso, retornamos 0 para indicar que não há mais citações a contar

    return head->citacoes + totalCitacoesRecursivo(head->next);// se o artigo atual não for nullptr, somamos o número de citações do artigo atual com o resultado da chamada recursiva para o próximo artigo na lista, o que nos permite contar as citações de todos os artigos na lista de forma recursiva
}



void exibirEstatisticas(Artigo* head) { //funcao para exibir as estatísticas de citações dos artigos na lista, recebe um ponteiro para o head da lista de artigos
    cout << "Estatisticas de Citacoes\n"; // imprime o menu para exibir as estatísticas de citações dos artigos na lista

    if (head == nullptr) { // verificamos se o head da lista é nullptr, o que indica que a lista de artigos está vazia
        cout << "Acervo vazio.\n"; // se for o caso, imprimimos uma mensagem informando que o acervo está vazio e retornamos para o menu principal
        return; // se a lista de artigos não estiver vazia, continuamos com o cálculo e exibição das estatísticas de citações
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

// struct auxiliar sem o ponteiro next — evita problema de padding
// ao salvar/carregar. O compilador pode inserir bytes de alinhamento
// entre char[] e int, então nunca assumimos offset fixo manualmente.
struct ArtigoData {
    char titulo[100];
    char autor[50];
    int  anoPB;
    int  DOI;
    int  citacoes;
};

//salvar e carregar binario
void salvarBinario(Artigo* head) {
    ofstream arquivo("acervo.dat", ios::binary);

    if (!arquivo.is_open()) {
        cout << "Erro ao salvar o acervo!\n";
        return;
    }

    Artigo* atual = head;
    while (atual != nullptr) {
        // copia os dados para o struct auxiliar e salva ele inteiro
        ArtigoData dados;
        for (int i = 0; i < 100; i++) dados.titulo[i] = atual->titulo[i];
        for (int i = 0; i < 50;  i++) dados.autor[i]  = atual->autor[i];
        dados.anoPB    = atual->anoPB;
        dados.DOI      = atual->DOI;
        dados.citacoes = atual->citacoes;

        arquivo.write(reinterpret_cast<char*>(&dados), sizeof(ArtigoData));
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

    ArtigoData dados;

    // lê um ArtigoData por vez — sem offset manual, sem risco de padding
    while (arquivo.read(reinterpret_cast<char*>(&dados), sizeof(ArtigoData))) {
        Artigo* novo = new Artigo();

        for (int i = 0; i < 100; i++) novo->titulo[i] = dados.titulo[i];
        for (int i = 0; i < 50;  i++) novo->autor[i]  = dados.autor[i];
        novo->anoPB    = dados.anoPB;
        novo->DOI      = dados.DOI;
        novo->citacoes = dados.citacoes;

        novo->next = head;
        head = novo;
    }

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