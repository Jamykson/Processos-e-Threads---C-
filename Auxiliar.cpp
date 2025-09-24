#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Função que gera uma matriz aleatória e salva em arquivo;
void gerarMatrizAleatoria_(int n_, int m_, const string& nomeDoArquivo_) {
    ofstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl; // neste caso tratamos erro de abertura;
        exit(1);
    }

    arquivo_ << n_ << " " << m_ << endl; // primeira linha contém as dimensões da matriz; isso faz com que a leitura futura saiba o tamanho;

    // Geração aleatória de números entre 0 e 9;
    for (int i_ = 0; i_ < n_; i_++) {
        for (int j_ = 0; j_ < m_; j_++) {
            int valor_ = rand() % 10; 
            arquivo_ << valor_ << "\t"; // neste caso usamos tabulação para facilitar visualização no arquivo;
        }
        arquivo_ << endl;
    }

    arquivo_.close(); 
    cout << "A matriz foi salva em " << nomeDoArquivo_ << "." << endl; 
}

int main(int argc_, char* argv_[]) {
    if (argc_ != 5) {
        cerr << "Uso: " << argv_[0] << " n1 m1 n2 m2" << endl; // imprime mensagem de erro;
        return 1; // neste caso encerramos se o usuário não passar exatamente 4 números;
    }

    srand(time(0)); // neste caso adicionamos uma semente para gerar números diferentes em cada execução;

    int n1_ = atoi(argv_[1]); // convertemos argumentos string para int;
    int m1_ = atoi(argv_[2]);
    int n2_ = atoi(argv_[3]);
    int m2_ = atoi(argv_[4]);

    if (m1_ != n2_) {
        cerr << "Erro: A multiplicacao apenas e possivel se m1 for igual a n2;" << endl;
        return 1; // isso faz com que só possamos multiplicar matrizes compatíveis;
    }

    gerarMatrizAleatoria_(n1_, m1_, "M1.txt"); 
    gerarMatrizAleatoria_(n2_, m2_, "M2.txt"); 

    return 0;
}
