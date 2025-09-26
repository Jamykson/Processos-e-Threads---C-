#!/bin/bash

# Compilar
g++ Auxiliar.cpp -o Auxiliar
g++ Sequencial.cpp -o Sequencial
g++ ParaleloThreads.cpp -o ParaleloThreads -pthread
g++ ParaleloProcessos.cpp -o ParaleloProcessos

# Gerar matrizes
./Auxiliar 200 300 300 150

# Executar
./Sequencial Matriz1.txt Matriz2.txt
./ParaleloThreads Matriz1.txt Matriz2.txt 100
./ParaleloProcessos Matriz1.txt Matriz2.txt 100
