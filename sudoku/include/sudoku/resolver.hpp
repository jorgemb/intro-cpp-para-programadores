#ifndef GUARD_RESOLVER_HPP
#define GUARD_RESOLVER_HPP

#include <sudoku/sudoku.hpp>

#include <utility>
#include <deque>

class Resolver{
public:
    static std::pair<Sudoku, int> resolver_sudoku(const Sudoku& sudoku){
        std::deque<Sudoku> lista_sudokus;
        int copias = 0;

        // Verificar sudoku resuelto
        if(sudoku.resuelto() || !sudoku.valido()){
            return std::make_pair(sudoku, copias);
        }

        // Obtener listado de sucesores
        auto sucesores = sudoku.sucesores();
        copias += sucesores.size();

        lista_sudokus.insert(lista_sudokus.end(), sucesores.begin(), sucesores.end());

        // Verificar sucesores
        while(!lista_sudokus.empty()){
            Sudoku actual = lista_sudokus.back();
            lista_sudokus.pop_back();

            // ¿Resuelto?
            if(actual.resuelto()){
                return std::make_pair(actual, copias);
            }

            // Obtener sucesores
            auto sucesores = actual.sucesores();
            copias += sucesores.size();

            lista_sudokus.insert(lista_sudokus.end(), sucesores.begin(), sucesores.end());
        }

        return std::make_pair(sudoku, copias);
    }
};

#endif /* GUARD_RESOLVER_HPP */
