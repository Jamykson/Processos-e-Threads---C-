#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Função que gera uma matriz aleatória e salva em arquivo;
void gerarMatrizAleatoria_(int linha_, int coluna_, const string& nomeDoArquivo_) {
    ofstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeDoArquivo_ << endl; // neste caso tratamos erro de abertura;
        exit(1);
    }

    arquivo_ << linha_ << " " << coluna_ << endl; // primeira linha contém as dimensões da matriz; isso faz com que a leitura futura saiba o tamanho;

    // Geração aleatória de números entre 0 e 9;
    for (int i_ = 0; i_ < linha_; i_++) {
        for (int j_ = 0; j_ < coluna_; j_++) {
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

    int linha1_ = atoi(argv_[1]); // convertemos argumentos string para int;
    int coluna1_ = atoi(argv_[2]);
    int linha2_ = atoi(argv_[3]);
    int coluna2_ = atoi(argv_[4]);

    if (coluna1_ != linha2_) {
        cerr << "Erro: A multiplicacao apenas e possivel se m1 for igual a n2;" << endl;
        return 1; // isso faz com que só possamos multiplicar matrizes compatíveis;
    }

    gerarMatrizAleatoria_(linha1_, coluna1_, "M1.txt"); 
    gerarMatrizAleatoria_(linha2_, coluna2_, "M2.txt"); 

    return 0;
}
