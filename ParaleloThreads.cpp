#include <iostream>  // Arquivo para a multiplicação com threads;
#include <fstream>   // para salvar resultados parciais em arquivos;
#include <vector>    // para armazenar as matrizes em memória;
#include <thread>    // para criar e gerenciar múltiplas threads;
#include <chrono>    // para medir o tempo de execução de cada thread;

using namespace std;
using namespace std::chrono;

// Função para ler uma matriz a partir de um arquivo;
vector<vector<int>> lerMatriz_(const string& nomeDoArquivo_, int &n_, int &m_) {
    ifstream arquivo_(nomeDoArquivo_); // neste caso abrimos o arquivo em modo de leitura;
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl; // neste caso tratamos erro de abertura;
        exit(1);
    }

    arquivo_ >> n_ >> m_; // isso faz com que saibamos quantas linhas e colunas a matriz possui;
    vector<vector<int>> matriz_(n_, vector<int>(m_)); // neste caso criamos a matriz em memória já com o tamanho certo;

    for (int i_ = 0; i_ < n_; i_++) {
        for (int j_ = 0; j_ < m_; j_++) {
            arquivo_ >> matriz_[i_][j_]; // isso faz com que cada valor seja lido e armazenado na posição correta;
        }
    }

    arquivo_.close(); // neste caso fechamos o arquivo após a leitura;
    return matriz_; // isso faz com que a matriz completa seja retornada para o programa;
}

// Função que cada thread executa para calcular parte da matriz resultado;
void calcularParte_(const vector<vector<int>>& M1_, const vector<vector<int>>& M2_, 
                    vector<vector<int>>& resultado_, 
                    int n1_, int m1_, int m2_, 
                    int inicio_, int fim_, int idThread_) {
    auto inicioTempo_ = high_resolution_clock::now(); // neste caso marcamos o início do tempo de execução da thread;

    for (int idx_ = inicio_; idx_ < fim_; idx_++) {
        int i_ = idx_ / m2_; // isso faz com que saibamos em qual linha da matriz resultado estamos;
        int j_ = idx_ % m2_; // isso faz com que saibamos em qual coluna da matriz resultado estamos;

        int soma_ = 0;
        for (int k_ = 0; k_ < m1_; k_++) {
            soma_ += M1_[i_][k_] * M2_[k_][j_]; // neste caso calculamos o produto escalar da linha de M1 com a coluna de M2;
        }
        resultado_[i_][j_] = soma_; // isso faz com que armazenemos o valor calculado na posição correta da matriz resultado;
    }

    auto fimTempo_ = high_resolution_clock::now(); // neste caso marcamos o fim do tempo da thread;
    duration<double, milli> duracao_ = fimTempo_ - inicioTempo_; // isso faz com que saibamos o tempo total que a thread levou;

    // Salvar os resultados parciais desta thread;
    string nomeArquivo_ = "MultiplicacaoThread" + to_string(idThread_) + ".txt"; // neste caso o nome depende do id da thread;
    ofstream arquivo_(nomeArquivo_); 
    if (!arquivo_.is_open()) {
        cerr << "Erro ao criar o arquivo " << nomeArquivo_ << endl; // neste caso tratamos erro de escrita;
        exit(1);
    }

    arquivo_ << n1_ << " " << m2_ << endl; // isso faz com que registremos as dimensões da matriz resultado;
    for (int idx_ = inicio_; idx_ < fim_; idx_++) {
        int i_ = idx_ / m2_; // recuperamos a linha correspondente ao índice;
        int j_ = idx_ % m2_; // recuperamos a coluna correspondente ao índice;
        arquivo_ << "Resultado[" << i_ << "][" << j_ << "] = " << resultado_[i_][j_] << endl; // salvamos o valor calculado;
    }
    arquivo_ << "Tempo da thread " << idThread_ << ": " << duracao_.count() << " ms" << endl; // mostramos o tempo de execução da thread;

    arquivo_.close(); // neste caso fechamos o arquivo após salvar os resultados;
}

// Função principal (main);
int main(int argc_, char* argv_[]) {
    if (argc_ != 4) {
        cerr << "Uso: " << argv_[0] << " M1.txt M2.txt P" << endl; // neste caso mostramos a forma correta de uso do programa;
        return 1; // isso faz com que o programa termine se os argumentos não forem suficientes;
    }

    int n1_, m1_, n2_, m2_;
    vector<vector<int>> M1_ = lerMatriz_(argv_[1], n1_, m1_); // neste caso lemos a primeira matriz do arquivo;
    vector<vector<int>> M2_ = lerMatriz_(argv_[2], n2_, m2_); // neste caso lemos a segunda matriz do arquivo;

    if (m1_ != n2_) {
        cerr << "Erro: numero de colunas de M1 deve ser igual ao numero de linhas de M2;" << endl; // regra da multiplicação de matrizes;
        return 1;
    }

    int P_ = stoi(argv_[3]); // neste caso convertemos o parâmetro P (número de elementos por thread);
    int totalElementos_ = n1_ * m2_; // isso faz com que saibamos quantos elementos terá a matriz resultado;
    int numThreads_ = (totalElementos_ + P_ - 1) / P_; // neste caso calculamos quantas threads são necessárias (arredondando para cima);

    vector<vector<int>> resultado_(n1_, vector<int>(m2_, 0)); // cria a matriz resultado já preenchida com zeros;
    vector<thread> threads_; // neste caso criamos um vetor para armazenar todas as threads;

    cout << "Criando " << numThreads_ << " threads..." << endl; // mensagem informativa para o usuário;

    for (int t_ = 0; t_ < numThreads_; t_++) {
        int inicio_ = t_ * P_; // neste caso definimos a posição inicial de cálculo da thread;
        int fim_ = min(inicio_ + P_, totalElementos_); // isso faz com que definamos a posição final sem passar do limite;

        // aqui criamos uma nova thread que executa a função calcularParte_;
        threads_.emplace_back(calcularParte_, cref(M1_), cref(M2_), ref(resultado_), 
                              n1_, m1_, m2_, inicio_, fim_, t_);
    }

    for (auto &thr_ : threads_) {
        thr_.join(); // neste caso esperamos cada thread terminar antes de prosseguir;
    }

    cout << "Multiplicacao paralela com threads concluida. Resultados parciais salvos em arquivos separados." << endl; // mensagem final para o usuário;

    return 0; // fim do programa;
}
