#include <iostream>  
#include <fstream>   
#include <vector>    
#include <thread>    
#include <chrono>    

using namespace std;
using namespace std::chrono;

//Essa função para lê uma matriz a partir de um arquivo;
vector<vector<int>> lendoMatriz_(const string& nomeDoArquivo_, int &linha_, int &coluna_) {

    ifstream arquivo_(nomeDoArquivo_); 
    if (!arquivo_.is_open()) {

        cerr << "Houve um erro ao abrir o arquivo " << nomeDoArquivo_ << "." << endl; 
        exit(1);
    }

    arquivo_ >> linha_ >> coluna_; //isso faz com que as dimensões sejam salvas no arquivo;
    vector<vector<int>> matriz_(linha_, vector<int>(coluna_)); //neste caso é criada a matriz em memória já com o tamanho certo;

    for (int i_ = 0; i_ < linha_; i_++) {

        for (int j_ = 0; j_ < coluna_; j_++) {

            arquivo_ >> matriz_[i_][j_];
        }
    }

    arquivo_.close(); 
    return matriz_; 
}

//Essa função calcula a parte da multiplicação atribuída a cada thread;
void calcularParte_(const vector<vector<int>>& M1_, const vector<vector<int>>& M2_, vector<vector<int>>& resultado_, int linha1_, int coluna1_, int coluna2_, int inicio_, int fim_, int idThread_) {
    
    auto inicioTempo_ = high_resolution_clock::now(); //marca o início do tempo de execução da thread;

    for (int idx_ = inicio_; idx_ < fim_; idx_++) {

        int i_ = idx_ / coluna2_; // isso faz com que saibamos em qual linha e coluna da matriz resultado está;
        int j_ = idx_ % coluna2_; 

        int soma_ = 0;
        for (int k_ = 0; k_ < coluna1_; k_++) {

            soma_ += M1_[i_][k_] * M2_[k_][j_]; //calculo do produto escalar da linha de M1 com a coluna de M2;
        }
        resultado_[i_][j_] = soma_; //isso faz com que se armazene o valor calculado na posição correta da matriz resultado;
    }

    auto fimTempo_ = high_resolution_clock::now(); //marca o fim do tempo da thread;
    duration<double, milli> duracao_ = fimTempo_ - inicioTempo_; //tempo total que a thread levou;

    string nomeArquivo_ = "MultiplicacaoThread" + to_string(idThread_) + ".txt";
    ofstream arquivo_(nomeArquivo_); 
    if (!arquivo_.is_open()) {

        cerr << "Houve um erro ao criar o arquivo " << nomeArquivo_ << "." << endl; 
        exit(1);
    }

    arquivo_ << linha1_ << " " << coluna2_ << endl; //isso faz com que as dimensões sejam salvas no arquivo;
    for (int idx_ = inicio_; idx_ < fim_; idx_++) {

        int i_ = idx_ / coluna2_; 
        int j_ = idx_ % coluna2_; 
        arquivo_ << "Resultado[" << i_ << "][" << j_ << "] = " << resultado_[i_][j_] << endl; //isto salva o valor calculado;
    }
    arquivo_ << "Tempo da thread " << idThread_ << ": " << duracao_.count() << " ms" << endl; //isto mostra o tempo de execução da thread;

    arquivo_.close(); 
}

int main(int argc_, char* argv_[]) {

    if (argc_ != 4) {

        cerr << "Uso: " << argv_[0] << " arquivo1.txt arquivo2.txt I(inteiro)" << endl; //forma correta de uso do programa;
        return 1; 
    }

    int linha1_, coluna1_, linha2_, coluna2_;
    vector<vector<int>> M1_ = lendoMatriz_(argv_[1], linha1_, coluna1_); //se lê a primeira e a segunda matriz do arquivo;
    vector<vector<int>> M2_ = lendoMatriz_(argv_[2], linha2_, coluna2_);

    if (coluna1_ != linha2_) {

        cerr << "Houve um erro: o numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl; 
        return 1;
    }

    int P_ = stoi(argv_[3]); //P (número de elementos por thread);
    int totalElementos_ = linha1_ * coluna2_; 
    int numThreads_ = (totalElementos_ + P_ - 1) / P_; 

    vector<vector<int>> resultado_(linha1_, vector<int>(coluna2_, 0)); //matriz resultado já preenchida com zeros;
    vector<thread> threads_; //vetor para armazenar todas as threads;

    cout << "Criando " << numThreads_ << " threads..." << endl; 

    auto inicioTotal_ = high_resolution_clock::now();

    for (int t_ = 0; t_ < numThreads_; t_++) {

        int inicio_ = t_ * P_; //define a posição inicial de cálculo da thread;
        int fim_ = min(inicio_ + P_, totalElementos_); //define a posição final sem passar do limite;

        threads_.emplace_back(calcularParte_, cref(M1_), cref(M2_), ref(resultado_), linha1_, coluna1_, coluna2_, inicio_, fim_, t_);
        //cria uma nova thread que executa a função calcularParte_;
    }

    for (auto &thr_ : threads_) {

        thr_.join(); //espera cada thread terminar antes de prosseguir;
    }

    auto fimTotal_ = high_resolution_clock::now();
    duration<double, milli> duracao_ = fimTotal_ - inicioTotal_;

    cout << "Multiplicacao paralela com threads concluida." << endl; 
    cout << "Tempo total: " << duracao_.count() << " ms (" << duracao_.count()/1000 << " s)" << endl;

    return 0; 
}
