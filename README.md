# Trabalho Prático 1 – Sistemas Operacionais  
## Universidade Federal do Rio Grande do Norte  
### Instituto Metrópole Digital  

### 📌 Tema: Processos e Threads  

Este trabalho tem como objetivo implementar e analisar a **multiplicação de matrizes** utilizando diferentes abordagens:  
- **Sequencial**  
- **Paralela com Threads**  
- **Paralela com Processos**  

A proposta é comparar o desempenho entre soluções sequenciais e paralelas, verificando ganhos e limitações na execução.

---

## 🚀 Etapa 1 – Projeto Base  

Implementar os seguintes programas:  

1. **Auxiliar**  
   - Recebe como argumento `(n1, m1, n2, m2)`.  
   - Gera duas matrizes aleatórias (`M1` e `M2`) e as salva em arquivos.  

2. **Sequencial**  
   - Recebe dois arquivos de matrizes como entrada.  
   - Realiza a multiplicação de forma **convencional (sequencial)**.  
   - Salva o resultado em arquivo, junto com o tempo de execução.  

3. **Paralelo com Threads**  
   - Recebe dois arquivos de matrizes e um valor **P** (número de elementos da matriz resultado por thread).  
   - Cria múltiplas **threads** para calcular os elementos.  
   - Salva resultados parciais em arquivos separados.  

4. **Paralelo com Processos**  
   - Recebe dois arquivos de matrizes e um valor **P** (número de elementos da matriz resultado por processo).  
   - Cria múltiplos **processos** para calcular os elementos.  
   - Salva resultados parciais em arquivos separados.  

> **Observação importante:**  
> - Todas as classes e variáveis devem terminar com `_`.  
> - O código deve ser **bem comentado**, com cada comentário terminado em `;`.  
> - Deve-se utilizar frequentemente as expressões **“neste caso”** e **“Isso faz com que”** nos comentários.  

---

## 📊 Etapa 2 – Comparação Sequencial vs Paralelo  

### Experimento E1  
- Executar os programas com diferentes tamanhos de matrizes (100x100, 200x200, 400x400, …).  
- Continuar até que a execução **sequencial** dure no mínimo 2 minutos.  
- Nos paralelos, usar `P = ⌈(n1 * m2) / 8⌉`.  
- Executar cada teste 10 vezes e calcular a média.  
- Plotar gráfico do **tempo médio x tamanho da matriz**.  

### Experimento E2  
- Usar as mesmas matrizes do **E1**.  
- Variar o valor de **P** (reduzindo até ¼ de `P` inicial e aumentando até `(n1 * m2) / 2`).  
- Executar 10 vezes para cada valor de P e calcular a média.  
- Plotar gráfico do **tempo médio x P**.  

---

## 💬 Etapa 3 – Discussões  

Responder às seguintes questões com base nos gráficos obtidos:  
1. O que explica os resultados do experimento **E1**?  
2. O que explica os resultados do experimento **E2**?  
3. Qual o **valor ideal de P** para a multiplicação das matrizes M1 e M2?  

---

## 📹 Entregáveis  

- Relatório com explicações e gráficos.  
- Códigos completos e compiláveis.  
- Vídeo (até 2 minutos) explicando:  
  - Implementação.  
  - Resultados e análise.  
  - **Observação:** rosto dos alunos deve aparecer e o tempo deve ser dividido igualmente.  

---

## ⚠️ Observações Importantes  

- Trabalho pode ser feito **individualmente ou em dupla**.  
- Entregas via **SIGAA** dentro do prazo estipulado.  
- A **não entrega** de qualquer item (código, relatório ou vídeo) implica em **nota 0**.  
- Todos os códigos passarão por **sistema anti-plágio**.  
- Casos de plágio resultam em nota **0,00** para o grupo e podem levar à **reprovação**.  

---

🔗 [Gustafson’s Law – Wikipédia](https://en.wikipedia.org/wiki/Gustafson%27s_law)  

---
