#ifndef GUARD_SUDOKU_HPP
#define GUARD_SUDOKU_HPP

#include <sudoku/casilla.hpp>
#include <string>
#include <array>
#include <ostream>

class Sudoku{
public:
    Sudoku() {}
    explicit Sudoku(const std::string& valores);

    bool fijar_opcion(int fila, int columna, int opcion);
    bool disponible_opcion(int fila, int columna, int opcion) const;

    bool valido() const;
    bool resuelto() const;

    using ListaSudokus = std::vector<Sudoku>;
    ListaSudokus sucesores() const;
private:
    inline static const int m_filas = 9, m_columnas = 9;

    using FilaCasilla = std::array<CasillaBit, m_columnas>;
    using MatrizCasilla = std::array<FilaCasilla, m_filas>;

    MatrizCasilla m_casillas;

    friend std::ostream& operator<<(std::ostream&, const Sudoku&);
};

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);

#endif /* GUARD_SUDOKU_HPP */
