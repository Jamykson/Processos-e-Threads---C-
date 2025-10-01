#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//essa função faz com que seja gerada uma matriz aleatória, e salva em arquivo;
void gerandoMatrizAleatoria_(int linha_, int coluna_, const string& nomeDoArquivo_) {
    
    ofstream arquivo_(nomeDoArquivo_);
    if (!arquivo_.is_open()) {
        
        cerr << "Houve um erro ao abrir o arquivo " << nomeDoArquivo_ <<"."<< endl;   //no casso de erro de abertura;
        exit(1);
    }

    arquivo_ << linha_ << " " << coluna_ << endl;   //isso faz com que as dimensões sejam lidas e armazenadas em linha_ e coluna_; 
    
    for (int i_ = 0; i_ < linha_; i_++) {  
        for (int j_ = 0; j_ < coluna_; j_++) {

            int valor_ = rand() % 10; 
            arquivo_ << valor_ << "\t"; //insere o valor aleatório no arquivo com um tab(/t) para separar;;
        }
        arquivo_ << endl;
    }

    arquivo_.close(); 
    cout << "A matriz foi salva em " << nomeDoArquivo_ << "." << endl; 
}

int main(int argc_, char* argv_[]) {

    if (argc_ != 5) {

        cerr << "Uso Correto: " << argv_[0] << " l1 c1 l2 c2" << endl;  //nesse caso mostra a forma correta de usar o programa;
        return 1; 
    }

    srand(time(0)); 

    int linha1_ = atoi(argv_[1]); //converte os argumentos string para int;
    int coluna1_ = atoi(argv_[2]);
    int linha2_ = atoi(argv_[3]);
    int coluna2_ = atoi(argv_[4]);

    if (coluna1_ != linha2_) {

        cerr << "Erro: A multiplicacao apenas é possivel se m1 for igual a n2;" << endl;
        return 1; 
    }

    gerandoMatrizAleatoria_(linha1_, coluna1_, "Matriz1.txt"); 
    gerandoMatrizAleatoria_(linha2_, coluna2_, "Matriz2.txt"); 

    return 0;
}