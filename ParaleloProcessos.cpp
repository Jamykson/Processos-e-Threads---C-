#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>   // para fork()
#include <sys/wait.h> // para wait()
#include <chrono>

using namespace std;
using namespace std::chrono;

// Função para ler matriz de arquivo
vector<vector<int>> lerMatriz_(const string& nomeDoArquivo_, int &n_, int &m_) {
    ifstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl;
        exit(1);
    }

    arquivo_ >> n_ >> m_; // isso faz com que saibamos quantas linhas e colunas a matriz possui;
    vector<vector<int>> matriz_(n_, vector<int>(m_));

    for (int i_ = 0; i_ < n_; i_++) {
        for (int j_ = 0; j_ < m_; j_++) {
            arquivo_ >> matriz_[i_][j_]; // neste caso lemos cada valor;
        }
    }

    arquivo_.close();
    return matriz_;
}

// Função que cada processo vai executar para calcular sua parte
void calcularParteProcesso_(const vector<vector<int>>& M1_, const vector<vector<int>>& M2_, 
                            int n1_, int m1_, int m2_, int inicio_, int fim_, int idProcesso_) {

    auto inicioTempo_ = high_resolution_clock::now(); // neste caso marcamos o início;

    vector<vector<int>> resultado_(n1_, vector<int>(m2_, 0)); // neste caso criamos matriz local para este processo

    for (int idx_ = inicio_; idx_ < fim_; idx_++) {
        int i_ = idx_ / m2_;
        int j_ = idx_ % m2_;
        int soma_ = 0;
        for (int k_ = 0; k_ < m1_; k_++) {
            soma_ += M1_[i_][k_] * M2_[k_][j_]; // isso faz com que calculemos o produto escalar
        }
        resultado_[i_][j_] = soma_;
    }

    auto fimTempo_ = high_resolution_clock::now();
    duration<double, milli> duracao_ = fimTempo_ - inicioTempo_;

    // Salvar resultados parciais
    string nomeArquivo_ = "ResultadoProcesso" + to_string(idProcesso_) + ".txt";
    ofstream arquivo_(nomeArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao criar o arquivo " << nomeArquivo_ << endl;
        exit(1);
    }

    arquivo_ << n1_ << " " << m2_ << endl;
    for (int idx_ = inicio_; idx_ < fim_; idx_++) {
        int i_ = idx_ / m2_;
        int j_ = idx_ % m2_;
        arquivo_ << "Resultado[" << i_ << "][" << j_ << "] = " << resultado_[i_][j_] << endl;
    }
    arquivo_ << "Tempo do processo " << idProcesso_ << ": " << duracao_.count() << " ms" << endl;

    arquivo_.close();
}

int main(int argc_, char* argv_[]) {
    if (argc_ != 4) {
        cerr << "Uso: " << argv_[0] << " M1.txt M2.txt P" << endl;
        return 1;
    }

    int n1_, m1_, n2_, m2_;
    vector<vector<int>> M1_ = lerMatriz_(argv_[1], n1_, m1_);
    vector<vector<int>> M2_ = lerMatriz_(argv_[2], n2_, m2_);

    if (m1_ != n2_) {
        cerr << "Erro: numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl;
        return 1;
    }

    int P_ = stoi(argv_[3]);
    int totalElementos_ = n1_ * m2_;
    int numProcessos_ = (totalElementos_ + P_ - 1) / P_; // isso faz com que cada processo tenha no máximo P elementos

    cout << "Criando " << numProcessos_ << " processos..." << endl;

    auto inicio_ = high_resolution_clock::now();

    for (int p_ = 0; p_ < numProcessos_; p_++) {
        int inicio = p_ * P_;
        int fim = min(inicio + P_, totalElementos_);

        pid_t pid_ = fork(); // neste caso criamos um novo processo

        if (pid_ < 0) {
            cerr << "Erro ao criar processo " << p_ << endl;
            exit(1);
        } else if (pid_ == 0) {
            // processo filho
            calcularParteProcesso_(M1_, M2_, n1_, m1_, m2_, inicio, fim, p_);
            exit(0); // neste caso o filho termina depois de salvar seus resultados
        }
        // processo pai continua criando próximos processos
    }

    // processo pai espera todos os filhos terminarem
    for (int p_ = 0; p_ < numProcessos_; p_++) {
        wait(NULL); // isso faz com que o pai espere cada filho terminar
    }

    auto fim_ = high_resolution_clock::now();
    duration<double, milli> duracao_ = fim_ - inicio_;
    cout << "Multiplicacao paralela com processos concluida." << endl;
    cout << "Tempo total: " << duracao_.count() << " ms (" << duracao_.count()/1000 << " s)" << endl;

    return 0;
}
