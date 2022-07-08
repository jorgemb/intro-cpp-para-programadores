#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include <sudoku/sudoku.hpp>
#include <sudoku/resolver.hpp>

int main(int, char**) {
    // Abrir archivo
    auto archivo = std::ifstream("datos/facil.txt");
    if(!archivo.is_open()){
        std::cerr << "No fue posible abrir el archivo de sudokus\n";
        return -1;
    }

    int n = 1;
    std::string linea;
    while(std::getline(archivo, linea)){
        Sudoku sudoku(linea);

        auto tiempo_inicio = std::chrono::system_clock::now();
        auto [retorno, copias] = Resolver::resolver_sudoku(sudoku);
        auto duracion = std::chrono::system_clock::now() - tiempo_inicio;

        using milisegundos = std::chrono::duration<double, std::milli>;
        auto duracion_ms = std::chrono::duration_cast<milisegundos>(duracion);

        std::cout << n << " - ";
        if(retorno.resuelto()){
            // ¡Sudoku resuelto!
            std::cout << "Sudoku resuelto en " << copias << " copias";
        } else {
            // No fue posible resolverlo
            std::cout << "No fue posible resolver el sudoku despues de " << copias << " copias";
        }

        std::cout << " en " << duracion_ms.count() << " ms\n";
        ++n;
    }
}
