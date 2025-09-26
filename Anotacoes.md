"#include <fstream>"     --> serve para trabalhar com os arquivos;
"#include <vector>"      --> serve para armazenar as matrizes;
"#include <chrono>"      --> serve para medir o tempo;
"#include <thread>"      --> serve para criar e gerenciar múltiplas threads;
"#include <unistd.h>"    --> serve para usar fork();
"#include <sys/wait.h>"  --> serve para usar wait();
"#include <cstdlib>"     --> serve para funções utilitárias gerais (ex: atoi(), rand(),exit());
"#include <ctime>"       --> serve para manipular o tempo (ex: time()), usado em srand() para gerar números aleatórios diferentes;

Para apagar os aquivos gerados por ParaleloThreads.cpp: rm -f ResultadoProcesso*.txt
Para apagar os aquivos gerados por ParaleloProcessos.cpp: rm -f M1.txt M2.txt Resultado*.txt Multiplicacao*.txt
