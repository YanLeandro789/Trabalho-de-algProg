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

//  copia string

void copiarStr(char* dest, const char* orig, int tamanho) {
    int i = 0;
    for (i = 0; i < tamanho - 1 && orig[i] != '\0'; i++)
        dest[i] = orig[i];
    dest[i] = '\0';
}


void insertArtigo(Artigo*& head) {
    Artigo* novo = new Artigo();

    cout << "\n--- Inserir Novo Artigo ---\n";

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
    // caso base: lista vazia ou chegou ao fim
    if (head == nullptr)
        return nullptr;

    // encontrou
    if (head->DOI == doi)
        return head;

    // chamada recursiva pro próximo nó
    return buscarPorDOI(head->next, doi);
}

void menuBuscar(Artigo* head) {
    int doi;
    cout << "\n--- Buscar Artigo por DOI ---\n";
    cout << "Digite o DOI: ";
    cin >> doi;

    Artigo* encontrado = buscarPorDOI(head, doi);

    if (encontrado == nullptr) {
        cout << "Artigo nao encontrado.\n";
    } else {
        cout << "\n=== Artigo Encontrado ===\n";
        cout << "Titulo   : " << encontrado->titulo   << "\n";
        cout << "Autor    : " << encontrado->autor    << "\n";
        cout << "Ano      : " << encontrado->anoPB    << "\n";
        cout << "DOI      : " << encontrado->DOI      << "\n";
        cout << "Citacoes : " << encontrado->citacoes << "\n";
    }
}


// atualizar (Passagem por Referência)

void atualizarCitacoes(int& citacoes, int incremento) {
    citacoes += incremento;
}

void menuAtualizarCitacoes(Artigo* head) {
    int doi, incremento;
    cout << "\n--- Atualizar Citacoes ---\n";
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

    atualizarCitacoes(art->citacoes, incremento);  // passagem por referência

    cout << "Citacoes atualizadas para: " << art->citacoes << "\n";
}

// 4. GERAR RELATÓRIO POR ANO (Arquivo de Texto)


void gerarRelatorio(Artigo* head) {
    int anoInicio, anoFim;
    cout << "\n--- Gerar Relatorio por Ano ---\n";
    cout << "Ano inicial: ";
    cin >> anoInicio;
    cout << "Ano final  : ";
    cin >> anoFim;

    ofstream arquivo("relatorio.txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de relatorio!\n";
        return;
    }

    arquivo << "=== Relatorio de Artigos (" << anoInicio << " - " << anoFim << ") ===\n\n";

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

    cout << "Relatorio gerado em 'relatorio.txt' com " << count << " artigo(s).\n";
}


// exibir (Recursivo)

int totalCitacoesRecursivo(Artigo* head) {
    // caso base
    if (head == nullptr)
        return 0;

    // soma as citações do nó atual + recursão no restante
    return head->citacoes + totalCitacoesRecursivo(head->next);
}

void exibirEstatisticas(Artigo* head) {
    cout << "\n--- Estatisticas de Citacoes ---\n";

    if (head == nullptr) {
        cout << "Acervo vazio.\n";
        return;
    }

    int total = totalCitacoesRecursivo(head);

    // conta artigos e acha o mais citado
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

// =============================================================
// 6. SALVAR / CARREGAR BINÁRIO
// =============================================================

void salvarBinario(Artigo* head) {
    ofstream arquivo("acervo.dat", ios::binary);

    if (!arquivo.is_open()) {
        cout << "Erro ao salvar o acervo!\n";
        return;
    }

    Artigo* atual = head;
    while (atual != nullptr) {
        // salva apenas os dados, sem o ponteiro next
        arquivo.write(reinterpret_cast<char*>(atual), sizeof(Artigo) - sizeof(Artigo*));
        atual = atual->next;
    }

    arquivo.close();
    cout << "Acervo salvo em 'acervo.dat'.\n";
}

void carregarBinario(Artigo*& head) {
    ifstream arquivo("acervo.dat", ios::binary);

    if (!arquivo.is_open()) {
        // arquivo ainda não existe, tudo bem
        return;
    }

    // buffer temporário com o tamanho dos dados (sem o ponteiro)
    int tamDados = sizeof(Artigo) - sizeof(Artigo*);
    char buffer[sizeof(Artigo)];

    while (arquivo.read(buffer, tamDados)) {
        Artigo* novo = new Artigo();

        // copia os campos lidos para o novo nó
        for (int i = 0; i < 100; i++) novo->titulo[i] = buffer[i];
        for (int i = 0; i < 50;  i++) novo->autor[i]  = buffer[100 + i];

        int* campos = reinterpret_cast<int*>(buffer + 150);
        novo->anoPB    = campos[0];
        novo->DOI      = campos[1];
        novo->citacoes = campos[2];

        novo->next = head;
        head = novo;
    }

    arquivo.close();
    cout << "Acervo carregado com sucesso!\n";
}

// =============================================================
// LIBERAR MEMÓRIA
// =============================================================

void liberarMemoria(Artigo*& head) {
    while (head != nullptr) {
        Artigo* temp = head;
        head = head->next;
        delete temp;
    }
}

// =============================================================
// MENU PRINCIPAL
// =============================================================

int main() {
    Artigo* head = nullptr;

    // carrega acervo salvo anteriormente
    carregarBinario(head);

    int opcao;

    do {
        cout << "\n=============================\n";
        cout << "  SGAC - Acervo Cientifico   \n";
        cout << "=============================\n";
        cout << "1. Inserir Novo Artigo\n";
        cout << "2. Buscar Artigo por DOI\n";
        cout << "3. Atualizar Citacoes\n";
        cout << "4. Gerar Relatorio por Ano\n";
        cout << "5. Exibir Estatisticas de Citacoes\n";
        cout << "6. Sair\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: insertArtigo(head);            break;
            case 2: menuBuscar(head);              break;
            case 3: menuAtualizarCitacoes(head);   break;
            case 4: gerarRelatorio(head);          break;
            case 5: exibirEstatisticas(head);      break;
            case 6:
                salvarBinario(head);
                liberarMemoria(head);
                cout << "Memoria liberada. Encerrando...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 6);

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
