#include <iostream>
#include <fstream>
#include <vector>
#include <thread> 
#include <chrono>

using namespace std;
using namespace std::chrono;

//essa função lê matriz da arquivo
vector<vector<int>> lendoMatriz_(const string& nomeDoArquivo_, int &linha_, int &coluna_) {

    ifstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {

        cerr << "Houve um erro ao abrir o arquivo " << nomeDoArquivo_ << "." << endl;
        exit(1);
    }
    arquivo_ >> linha_ >> coluna_;  //isso faz com que saibamos quantas linhas e colunas a matriz possui;
    vector<vector<int>> matriz_(linha_, vector<int>(coluna_));
    for (int i_ = 0; i_ < linha_; i_++) {

        for (int j_ = 0; j_ < coluna_; j_++) {

            arquivo_ >> matriz_[i_][j_];    //neste caso preenchemos a matriz com os valores do arquivo;
        }
    }
    arquivo_.close();
    return matriz_;
}

//essa é a função que cada processo vai executar para calcular sua parte;
void calcularParteProcesso_(const vector<vector<int>>& M1_, const vector<vector<int>>& M2_, int linha1_, int coluna1_, int coluna2_, int inicio_, int fim_, int idProcesso_) {

    auto inicioTempo_ = high_resolution_clock::now();   //neste caso marcamos o início;
    vector<vector<int>> resultado_(linha1_, vector<int>(coluna2_, 0));  //neste caso criamos matriz local para este processo;
    for (int idx_ = inicio_; idx_ < fim_; idx_++) {

        int i_ = idx_ / coluna2_;   //converter os índices lineares em índices de linha e coluna;
        int j_ = idx_ % coluna2_;
        int soma_ = 0;
        for (int k_ = 0; k_ < coluna1_; k_++) {

            soma_ += M1_[i_][k_] * M2_[k_][j_]; //calculo do produto escalar;
        }
        resultado_[i_][j_] = soma_;
    }

    auto fimTempo_ = high_resolution_clock::now();  //marca o fim do tempo;
    duration<double, milli> duracao_ = fimTempo_ - inicioTempo_;    //calcula o tempo gasto;
    string nomeArquivo_ = "ResultadoProcesso" + to_string(idProcesso_) + ".txt"; //isso salva os resultados parciais;
    ofstream arquivo_(nomeArquivo_);
    if (!arquivo_.is_open()) {

        cerr << "Houve um erro ao criar o arquivo " << nomeArquivo_ << "." << endl;
        exit(1);
    }
    arquivo_ << linha1_ << " " << coluna2_ << endl; //para que saibamos quantas linhas e colunas a matriz possui;
    for (int idx_ = inicio_; idx_ < fim_; idx_++) {

        int i_ = idx_ / coluna2_;
        int j_ = idx_ % coluna2_;
        arquivo_ << "Resultado[" << i_ << "][" << j_ << "] = " << resultado_[i_][j_] << endl;   //registra no arquivo cada valor calculado;
    }
    arquivo_ << "Tempo do processo " << idProcesso_ << ": " << duracao_.count() << " ms" << endl;
    arquivo_.close();
}

int main(int argc_, char* argv_[]) {

    if (argc_ != 4) {

        cerr << "Uso: " << argv_[0] << " M1.txt M2.txt P" << endl;
        return 1;
    }
    int linha1_, coluna1_, linha2_, coluna2_;
    vector<vector<int>> M1_ = lendoMatriz_(argv_[1], linha1_, coluna1_);  //isso faz a leitura das duas matrizes;
    vector<vector<int>> M2_ = lendoMatriz_(argv_[2], linha2_, coluna2_);

    if (coluna1_ != linha2_) {

        cerr << "Houve um erro: o numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl;
        return 1;
    }

    int P_ = stoi(argv_[3]);    //P (número de elementos por processo);
    int totalElementos_ = linha1_ * coluna2_;  
    int numProcessos_ = (totalElementos_ + P_ - 1) / P_;    //para que cada processo tenha no máximo P elementos;

    cout << "Criando " << numProcessos_ << " processos..." << endl;

    auto inicio_ = high_resolution_clock::now();    //isso marca o início do tempo total;

    vector<thread> threads; // Vetor para armazenar as threads criadas

    for (int p_ = 0; p_ < numProcessos_; p_++) {

        int inicio = p_ * P_;
        int fim = min(inicio + P_, totalElementos_);
        threads.emplace_back(calcularParteProcesso_, ref(M1_), ref(M2_), linha1_, coluna1_, coluna2_, inicio, fim, p_);
    }

    for (auto& th : threads) {
        
        th.join(); 
    }

    auto fim_ = high_resolution_clock::now();
    duration<double, milli> duracao_ = fim_ - inicio_;
    cout << "Multiplicacao paralela com processos concluida." << endl;
    cout << "Tempo total: " << duracao_.count() << " ms (" << duracao_.count()/1000 << " s)" << endl;

    return 0;
}