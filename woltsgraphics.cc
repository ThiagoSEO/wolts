#include <iostream>
#include <fstream> // Para manipulacao de arquivos
#include <limits>
#include <cstdlib> // Para usar o system()

// Funcao para ler os valores de potencia
void lerValores(double potencias[], int numValores) {
    for (int i = 0; i < numValores; i++) {
        std::cout << "Digite o valor " << i + 1 << ": ";
        std::cin >> potencias[i];
    }
}

// Funcao para encontrar o valor maximo
double encontrarMaximo(const double potencias[], int numValores) {
    double maxPotencia = std::numeric_limits<double>::min();
    for (int i = 0; i < numValores; i++) {
        if (potencias[i] > maxPotencia) {
            maxPotencia = potencias[i];
        }
    }
    return maxPotencia;
}

// Funcao para encontrar o valor miinimo
double encontrarMinimo(const double potencias[], int numValores) {
    double minPotencia = std::numeric_limits<double>::max();
    for (int i = 0; i < numValores; i++) {
        if (potencias[i] < minPotencia) {
            minPotencia = potencias[i];
        }
    }
    return minPotencia;
}

// Funcao para salvar os valores em um arquivo para plotagem
void salvarValoresEmArquivo(const double potencias[], int numValores) {
    std::ofstream arquivo("potencias.dat"); // Abre um arquivo de dados
    for (int i = 0; i < numValores; i++) {
        arquivo << i + 1 << " " << potencias[i] << "\n"; // Salva os índices e os valores
    }
    arquivo.close();
}

// Funcao para gerar o grafico usando o GNUplot
void gerarGrafico() {
    // Cria um arquivo de script para o GNUplot
    std::ofstream gnuplotScript("script.gnuplot");
    gnuplotScript << "set title 'Grafico de Tensao Eletrica em potencia Thiago Martins'\n";
    gnuplotScript << "set xlabel 'Tempo (Unidade de Tempo em Horas)'\n";
    gnuplotScript << "set ylabel 'Potencia (W)'\n";
    gnuplotScript << "plot 'potencias.dat' with linespoints title 'Potencia'\n";
    gnuplotScript << "pause -1\n"; // Mantém o grafico aberto
    gnuplotScript.close();

    // Chama o GNUplot com o script gerado
    system("gnuplot script.gnuplot");
}

int main() {
    const int numValores = 20;
    double potencias[numValores];

    // Chama a funcao para ler os valores de potencia
    lerValores(potencias, numValores);

    // Chama as funcoes para encontrar o valor maximo e minimo
    double maxPotencia = encontrarMaximo(potencias, numValores);
    double minPotencia = encontrarMinimo(potencias, numValores);

    // Exibe os valores maximo e minimo
    std::cout << "\nPotencia maxima atingida: " << maxPotencia << " W" << std::endl;
    std::cout << "Potencia minima atingida: " << minPotencia << " W" << std::endl;

    // Salva os valores em um arquivo para plotagem
    salvarValoresEmArquivo(potencias, numValores);

    // Gera o grafico com GNUplot
    gerarGrafico();

    return 0;
}
