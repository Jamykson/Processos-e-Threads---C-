#include <iostream> //Para a multiplicação sequencial.
#include <fstream> 
#include <vector>
#include <chrono> // para medir o tempo

using namespace std;
using namespace std::chrono;

using namespace std;

// Função para ler uma matriz a partir de arquivo;
vector<vector<int>> lerMatriz_(const string& nomeDoArquivo_, int &n_, int &m_) {
    // ... (nenhuma mudança nesta função)
    ifstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl;
        exit(1);
    }
    arquivo_ >> n_ >> m_;
    vector<vector<int>> matriz_(n_, vector<int>(m_));
    for (int i_ = 0; i_ < n_; i_++) {
        for (int j_ = 0; j_ < m_; j_++) {
            arquivo_ >> matriz_[i_][j_];
        }
    }
    arquivo_.close();
    return matriz_;
}

// Função para multiplicar duas matrizes 
vector<vector<int>> multiplicarMatrizes_(const vector<vector<int>>& PrimeiraMatriz_, const vector<vector<int>>& SegundaMatriz_, int n1_, int m1_, int m2_) {
    // ... (nenhuma mudança nesta função)
    vector<vector<int>> resultado_(n1_, vector<int>(m2_, 0));
    for (int i_ = 0; i_ < n1_; i_++) {
        for (int j_ = 0; j_ < m2_; j_++) {
            for (int k_ = 0; k_ < m1_; k_++) {
                resultado_[i_][j_] += PrimeiraMatriz_[i_][k_] * SegundaMatriz_[k_][j_];
            }
        }
    }
    return resultado_; 
}

// Salvar a matriz resultado em arquivo;
void salvarEmArquivo_(const string& tituloDoArquivo_, const vector<vector<int>>& matriz_, int n_, int m_, double tempo_) {
    // ... (nenhuma mudança nesta função)
    ofstream arquivo_(tituloDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Houve um erro ao criar o arquivo " << tituloDoArquivo_ <<"."<< endl;
        exit(1);
    }
    arquivo_ << n_ << " " << m_ << endl;
    for (int i_ = 0; i_ < n_; i_++) {
        for (int j_ = 0; j_ < m_; j_++) {
            arquivo_ << matriz_[i_][j_] << " ";
        }
        arquivo_ << endl;
    }
    arquivo_ << "Tempo: " << tempo_  << " ms" << endl;
    arquivo_.close();
}

int main(int argc_, char* argv_[]) {
    if (argc_ != 3) {
        cerr << "Uso: " << argv_[0] << " M1.txt M2.txt" << endl;
        return 1;
    }

    int n1_, m1_, n2_, m2_;
    vector<vector<int>> M1_ = lerMatriz_(argv_[1], n1_, m1_);
    vector<vector<int>> M2_ = lerMatriz_(argv_[2], n2_, m2_);

    if (m1_ != n2_) {
        cerr << "Erro: numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl;
        return 1;
    }

    auto inicio_ = high_resolution_clock::now();

    vector<vector<int>> resultado_ = multiplicarMatrizes_(M1_, M2_, n1_, m1_, m2_);

    auto fim_ = high_resolution_clock::now();
    duration<double, milli> duracao_ = fim_ - inicio_;

    // ===== CORREÇÃO 1 DE 2: O nome da função aqui foi corrigido. =====
    salvarEmArquivo_("ResultadoSequencial.txt", resultado_, n1_, m2_, duracao_.count());

    cout << "Multiplicacao sequencial concluida. Resultado salvo em ResultadoSequencial.txt" << endl;

    return 0;
}

