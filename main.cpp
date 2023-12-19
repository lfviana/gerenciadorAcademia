#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Pessoa {
public:
    string nome;
    float altura;
    float peso;
    int idade;

    Pessoa(const string& n, float alt, float p, int id) : nome(n), altura(alt), peso(p), idade(id) {}

    virtual ~Pessoa() {}
};

class AlunoAcademia : public Pessoa {
public:
    string matricula;
    float imc;
    string treino;
    static int contadorAlunos; 

    AlunoAcademia(const string& n, float alt, float p, int id) : Pessoa(n, alt, p, id) {
        matricula = to_string(202300 + contadorAlunos);
        imc = calcularIMC(altura, peso);
        contadorAlunos++;
    }

    ~AlunoAcademia() {}

    float calcularIMC(float altura, float peso) const {
        if (altura <= 0.0 || peso <= 0.0) {
            return 0.0;
        }
        return peso / (altura * altura);
    }
};

int AlunoAcademia::contadorAlunos = 0;  // Inicialização do membro estático

void exibirRelatorio(const vector<AlunoAcademia>& alunos) {
    cout << "\nDADOS DOS ALUNOS\n" << endl;
    for (const auto& aluno : alunos) {
        cout << "Matrícula: " << aluno.matricula << endl;
        cout << "Nome: " << aluno.nome << endl;
        cout << "Idade: " << aluno.idade << endl;
        cout << "Altura: " << aluno.altura << endl;
        cout << "Peso: " << aluno.peso << endl;
        cout << "IMC: " << aluno.imc << endl;
        cout << "Treino: " << aluno.treino << "\n\n";
    }
}

void definirTreino(AlunoAcademia& aluno) {
    cout << "Informe o treino para " << aluno.nome << endl;
    cin.ignore(); // Limpar o buffer do teclado
    getline(cin, aluno.treino);
}

void adicionarAluno(vector<AlunoAcademia>& alunos) {
    string nome;
    float altura, peso;
    int idade;

    cout << "\nNome do novo aluno: ";
    cin.ignore();
    getline(cin, nome);

    cout << "Idade do novo aluno: ";
    cin >> idade;

    cout << "Altura do novo aluno: ";
    cin >> altura;

    cout << "Peso do novo aluno: ";
    cin >> peso;

    AlunoAcademia aluno(nome, altura, peso, idade);
    definirTreino(aluno);
    alunos.push_back(aluno);

    cout << "\nNovo aluno adicionado com sucesso!\n" << endl;
}

void checarDadosAluno(const vector<AlunoAcademia>& alunos) {
    string matricula;
    cout << "\n\nDigite a matrícula do aluno que deseja verificar: ";
    cin >> matricula;

    auto it = find_if(alunos.begin(), alunos.end(), [matricula](const AlunoAcademia& aluno) {
        return aluno.matricula == matricula;
    });

    if (it != alunos.end()) {
        cout << "\n\nDados do aluno encontrado:" << endl;
        cout << "Matrícula: " << it->matricula << endl;
        cout << "Nome: " << it->nome << endl;
        cout << "Idade: " << it->idade << endl;
        cout << "Altura: " << it->altura << "metros" << endl;
    cout << "Peso: " << it->peso << "kg" << endl;
        cout << "IMC: " << it->imc << endl;
        cout << "Treino: " << it->treino << "\n" << endl;
    } else {
        cout << "Aluno não encontrado." << endl;
    }
}

void alterarTreino(vector<AlunoAcademia>& alunos) {
    string matricula;
    cout << "\n\nDigite a matrícula do aluno para alterar o treino: ";
    cin >> matricula;

    auto it = find_if(alunos.begin(), alunos.end(), [matricula](const AlunoAcademia& aluno) {
        return aluno.matricula == matricula;
    });

    if (it != alunos.end()) {
        cout << "\n\nInforme o novo treino para " << it->nome << " (separe os exercícios por ';'): ";
        cin.ignore(); // Limpar o buffer do teclado
        getline(cin, it->treino);
        cout << "\nTreino alterado com sucesso." << endl;
    } else {
        cout << "Aluno não encontrado." << endl;
    }
}

void salvarDados(const vector<AlunoAcademia>& alunos, const string& nomeArquivo) {
    ofstream arquivo_saida(nomeArquivo);

    if (arquivo_saida.is_open()) {
        arquivo_saida << "Matricula, Nome, Idade, Altura, Peso, IMC, Treino" << endl;
        for (const auto& aluno : alunos) {
            arquivo_saida << aluno.matricula << ", " << aluno.nome << ", " << aluno.idade <<
                ", " << aluno.altura << ", " << aluno.peso << ", " << aluno.imc << ", " << aluno.treino << endl;
        }

        cout << "\n\nDados salvos no arquivo com sucesso." << endl;
        arquivo_saida.close();
    } else {
        cout << "Não foi possível abrir o arquivo para salvar os dados." << endl;
    }
}

void salvarDadosAlunoIndividual(const vector<AlunoAcademia>& alunos) {
    string matricula;
    cout << "\n\nDigite a matrícula do aluno que deseja verificar: ";
    cin >> matricula;

    auto it = find_if(alunos.begin(), alunos.end(), [matricula](const AlunoAcademia& aluno) {
        return aluno.matricula == matricula;
    });

    if (it != alunos.end()) {
        string nomeArquivo = "aluno_" + matricula + ".txt";
        salvarDados({*it}, nomeArquivo);
        cout << "\nDados do aluno salvos no arquivo \"" << nomeArquivo << "\" com sucesso." << endl;
    } else {
        cout << "Aluno não encontrado." << endl;
    }
}

void carregarDadosArquivo(vector<AlunoAcademia>& alunos) {
    string nomeArquivo = "dados_alunos.txt";
    ifstream arquivo_entrada(nomeArquivo);

    if (arquivo_entrada.is_open()) {
        string linha;
        getline(arquivo_entrada, linha);

        while (getline(arquivo_entrada, linha)) {
            stringstream ss(linha);
            string matricula, nome, idade, altura, peso, imc, treino;

            getline(ss, matricula, ',');
            getline(ss, nome, ',');
            getline(ss, idade, ',');
            getline(ss, altura, ',');
            getline(ss, peso, ',');
            getline(ss, imc, ',');
            getline(ss, treino, ',');

            int idadeInt = stoi(idade);
            float alturaFloat = stof(altura);
            float pesoFloat = stof(peso);
            float imcFloat = stof(imc);

            AlunoAcademia aluno(nome, alturaFloat, pesoFloat, idadeInt);
            aluno.matricula = matricula;
            aluno.imc = imcFloat;
            aluno.treino = treino;

            alunos.push_back(aluno);
        }

        arquivo_entrada.close();
    } else {
        return;
    }
}

int main() {
    vector<AlunoAcademia> alunos;

    string nomeArquivo = "dados_alunos.txt";
    carregarDadosArquivo(alunos);

    int escolha;
    do {
        cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "|        MENU       |" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\n1. Adicionar novo aluno" << endl;
        cout << "2. Checar dados de um aluno" << endl;
        cout << "3. Trocar treino de um aluno" << endl;
        cout << "\n|    GERENCIADOR   |\n" << endl;
        cout << "4. Gerar relatório" << endl;
        cout << "5. Exibir total de alunos" << endl;
        cout << "6. Salvar dados em arquivo" << endl;
        cout << "7. Salvar dados de um aluno" << endl;
        cout << "8. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                adicionarAluno(alunos);
                break;
            case 2:
                checarDadosAluno(alunos);
                break;
            case 3:
                alterarTreino(alunos);
                break;
            case 4:
                exibirRelatorio(alunos);
                break;
            case 5:
                cout << "\nTotal de alunos: " << AlunoAcademia::contadorAlunos << "\n" << endl;
                break;
            case 6:
                salvarDados(alunos, nomeArquivo);
                break;
            case 7:
                salvarDadosAlunoIndividual(alunos);
                break;
            case 8:
                cout << "Saindo do programa.\n";
                break;
            default:
                cout << "Opção inválida. Tente novamente.\n";
        }

    } while (escolha != 8);

    return 0;
}
