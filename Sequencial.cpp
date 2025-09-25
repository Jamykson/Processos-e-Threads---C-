#include <iostream>
#include <fstream>  // para trabalhar com arquivos;
#include <vector>   // para armazenar matrizes;
#include <chrono>   // para medir o tempo;

using namespace std;
using namespace std::chrono;

// Função para ler uma matriz a partir de arquivo;
vector<vector<int>> lerMatriz_(const string& nomeDoArquivo_, int &linha_, int &coluna_) {
    ifstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl; // neste caso tratamos erro de abertura;
        exit(1);
    }

    arquivo_ >> linha_ >> coluna_; // isso faz com que saibamos quantas linhas e colunas ler;
    vector<vector<int>> matriz_(linha_, vector<int>(coluna_));
    for (int i_ = 0; i_ < linha_; i_++) {
        for (int j_ = 0; j_ < coluna_; j_++) {
            arquivo_ >> matriz_[i_][j_];
        }
    }
    arquivo_.close();
    return matriz_;
}

// Função para multiplicar duas matrizes;
vector<vector<int>> multiplicarMatrizes_(const vector<vector<int>>& PrimeiraMatriz_, const vector<vector<int>>& SegundaMatriz_, int linha1_, int coluna1_, int coluna2_) {
    vector<vector<int>> resultado_(linha1_, vector<int>(coluna2_, 0)); 
    for (int i_ = 0; i_ < linha1_; i_++) {
        for (int j_ = 0; j_ < coluna2_; j_++) {
            for (int k_ = 0; k_ < coluna1_; k_++) {
                resultado_[i_][j_] += PrimeiraMatriz_[i_][k_] * SegundaMatriz_[k_][j_];
            }
        }
    }
    return resultado_; 
}

// Função para salvar a matriz resultado em arquivo;
void salvarEmArquivo_(const string& tituloDoArquivo_, const vector<vector<int>>& matriz_, int linha_, int coluna_, double tempo_) {
    ofstream arquivo_(tituloDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Houve um erro ao criar o arquivo " << tituloDoArquivo_ <<"."<< endl;
        exit(1);
    }

    arquivo_ << linha_ << " " << coluna_ << endl;
    for (int i_ = 0; i_ < linha_; i_++) {
        for (int j_ = 0; j_ < coluna_; j_++) {
            arquivo_ << matriz_[i_][j_] << " ";
        }
        arquivo_ << endl;
    }
    arquivo_ << "Tempo: " << tempo_  << " ms (" << tempo_ / 1000 << " s)" << endl; // neste caso mostramos em ms e s;
    arquivo_.close();
}

int main(int argc_, char* argv_[]) {
    if (argc_ != 3) {
        cerr << "Uso: " << argv_[0] << " M1.txt M2.txt" << endl;
        return 1;
    }

    int linha1_, coluna1_, linha2_, coluna2_;
    vector<vector<int>> M1_ = lerMatriz_(argv_[1], linha1_, coluna1_);
    vector<vector<int>> M2_ = lerMatriz_(argv_[2], linha2_, coluna2_);

    if (coluna1_ != linha2_) {
        cerr << "Erro: numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl;
        return 1;
    }

    auto inicio_ = high_resolution_clock::now(); // neste caso marcamos o início;

    vector<vector<int>> resultado_ = multiplicarMatrizes_(M1_, M2_, linha1_, coluna1_, coluna2_);

    auto fim_ = high_resolution_clock::now(); // neste caso marcamos o fim;
    duration<double, milli> duracao_ = fim_ - inicio_;

    salvarEmArquivo_("MultiplicacaoSequencial.txt", resultado_, linha1_, coluna2_, duracao_.count());

    cout << "Multiplicacao sequencial concluida. Resultado salvo em MultiplicacaoSequencial.txt" << endl;
    cout << "Tempo gasto: " << duracao_.count() << " ms (" << duracao_.count()/1000 << " s)" << endl;

    return 0;
}
