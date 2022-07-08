#include <iostream>
#include <limits>

#include <laberinto/modelo.hpp>

int obtener_numero(const std::string& pregunta, int minimo, int maximo){
    std::cout << pregunta;

    int numero = 0;
    std::cin >> numero;

    while(!std::cin || numero < minimo || numero > maximo){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Error - Ingrese un número entre " << minimo << " y " << maximo << "\n";
        std::cout << pregunta;
        std::cin >> numero;
    }

    return numero;
}

int main(int, char**) {
    std::cout << "Bienvenido al generador de laberintos perfectos\n";

    // 1. Solicitar dimensiones del laberinto
    int filas = obtener_numero("Ingrese la cantidad de filas: ", 2, 50);
    int columnas = obtener_numero("Ingrese la cantidad de columnas: ", 2, 50);

    std::cout << "Deseas generar un laberinto con " << filas << " filas y "
            << columnas << " columnas.\n";

    // 2. Crear laberinto
    //   2.1 Algoritmo
    //   2.2 Obtener estado de pared
    //   2.3 Unir dos areas
    LaberintoPerfecto laberinto(filas, columnas);


    // 3. Mostrar laberinto
    std::cout << laberinto << '\n';
}
