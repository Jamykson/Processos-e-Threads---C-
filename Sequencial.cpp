#include <iostream> 
#include <fstream>  
#include <vector>   
#include <chrono>   

using namespace std;
using namespace std::chrono;

// essa função lê uma matriz a partir de arquivo;
vector<vector<int>> lerMatriz_(const string& nomeDoArquivo_, int &linha_, int &coluna_) {

    ifstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {

        cerr << "Houve um erro ao abrir o arquivo " << nomeDoArquivo_ << "."<< endl; 
        exit(1);
    }

    arquivo_ >> linha_ >> coluna_;  //isso faz com que as dimensões sejam lidas e armazenadas em linha_ e coluna_; 
    vector<vector<int>> matriz_(linha_, vector<int>(coluna_));
    for (int i_ = 0; i_ < linha_; i_++) {

        for (int j_ = 0; j_ < coluna_; j_++) {

            arquivo_ >> matriz_[i_][j_]; //isso faz com que cada valor seja lido e armazenado na posição correta da matriz;
        }
    }
    arquivo_.close();
    return matriz_;
}

//essa função multiplica duas matrizes;
vector<vector<int>> multiplicarMatrizes_(const vector<vector<int>>& PrimeiraMatriz_, const vector<vector<int>>& SegundaMatriz_, int linha1_, int coluna1_, int coluna2_) {
  
    vector<vector<int>> resultado_(linha1_, vector<int>(coluna2_, 0)); 
    for (int i_ = 0; i_ < linha1_; i_++) {

        for (int j_ = 0; j_ < coluna2_; j_++) {

            for (int k_ = 0; k_ < coluna1_; k_++) {

                resultado_[i_][j_] += PrimeiraMatriz_[i_][k_] * SegundaMatriz_[k_][j_]; //isso faz com que cada valor seja calculado e armazenado na posição correta da matriz resultado;
            }
        }
    }
    return resultado_; 
}

//essa função salva a matriz resultado em arquivo;
void salvarEmArquivo_(const string& tituloDoArquivo_, const vector<vector<int>>& matriz_, int linha_, int coluna_, double tempo_) {

    ofstream arquivo_(tituloDoArquivo_);
    if (!arquivo_.is_open()) {

        cerr << "Houve um erro ao criar o arquivo " << tituloDoArquivo_ <<"."<< endl;
        exit(1);
    }

    arquivo_ << linha_ << " " << coluna_ << endl; //isso faz com que as dimensões sejam salvas no arquivo;
    for (int i_ = 0; i_ < linha_; i_++) {

        for (int j_ = 0; j_ < coluna_; j_++) {

            arquivo_ << matriz_[i_][j_] << " "; //isso faz com que cada valor seja salvo na posição correta da matriz no arquivo;
        }
        arquivo_ << endl;
    }
    arquivo_ << "Tempo: " << tempo_  << " ms (" << tempo_ / 1000 << " s)" << endl; // neste caso mostramos em ms e s;
    arquivo_.close();
}

int main(int argc_, char* argv_[]) {
    if (argc_ != 3) {

        cerr << "Uso correto: " << argv_[0] << " arquivo1.txt arquivo2.txt" << endl;
        return 1;
    }

    int linha1_, coluna1_, linha2_, coluna2_;
    vector<vector<int>> M1_ = lerMatriz_(argv_[1], linha1_, coluna1_); // neste caso lemos as duas matrizes do arquivo;
    vector<vector<int>> M2_ = lerMatriz_(argv_[2], linha2_, coluna2_);

    if (coluna1_ != linha2_) {

        cerr << "Houve um erro: o numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl;
        return 1;
    }

    auto inicio_ = high_resolution_clock::now(); // neste caso marca o início;

    vector<vector<int>> resultado_ = multiplicarMatrizes_(M1_, M2_, linha1_, coluna1_, coluna2_);

    auto fim_ = high_resolution_clock::now(); // neste caso marca o fim;
    duration<double, milli> duracao_ = fim_ - inicio_;

    salvarEmArquivo_("MultiplicacaoSequencial.txt", resultado_, linha1_, coluna2_, duracao_.count());

    cout << "Multiplicacao sequencial concluida. Resultado salvo em MultiplicacaoSequencial.txt" << endl;
    cout << "Tempo total: " << duracao_.count() << " ms (" << duracao_.count()/1000 << " s)" << endl;

    return 0;
}
