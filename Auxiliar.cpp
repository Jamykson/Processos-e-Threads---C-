#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Função que gera uma matriz aleatória e salva em arquivo;
void gerarMatrizAleatoria_(int n_, int m_, const string& nomeDoArquivo_) {
    ofstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl;
        exit(1);
    }

    arquivo_ << n_ << " " << m_ << endl; // primeira linha contém as dimensões da matriz;

    // Geração aleatória de numeros entre 0 e 9;
    for (int i_ = 0; i_ < n_; i_++) {
        for (int j_ = 0; j_ < m_; j_++) {
            int valor_ = rand() % 10; 
            arquivo_ << valor_ << " ";
        }
        arquivo_ << endl;
    }

    arquivo_.close(); 
    cout << "A matriz foi salva em " << nomeDoArquivo_ << "." << endl; 
}

int main(int argc_, char* argv_[]) {
    if (argc_ != 5) {
        cerr << "Uso: " << argv_[0] << " n1 m1 n2 m2" << endl;//imprime mensagem de erro.
        return 1;// Se o usuário não passar exatamente 4 números, o programa mostra a forma correta de uso e encerra
    }

    srand(time(0)); // Adiciona uma semente para gerar números realmente aleatórios;

    int n1_ = atoi(argv_[1]); //Convertendo String para Int
    int m1_ = atoi(argv_[2]);
    int n2_ = atoi(argv_[3]);
    int m2_ = atoi(argv_[4]);

    if (m1_ != n2_) {
        cerr << "Erro: A multiplicacao apenas e possivel se m1 for igual a n2;" << endl;
        return 1;
    }

    gerarMatrizAleatoria_(n1_, m1_, "M1.txt"); 
    gerarMatrizAleatoria_(n2_, m2_, "M2.txt"); 

    return 0;
}
