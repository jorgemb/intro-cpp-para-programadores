#include <sudoku/sudoku.hpp>

Sudoku::Sudoku(const std::string& valores){
    int actual = 0;
    for(char c: valores){
        int fila = actual / m_columnas;
        int columna = actual % m_columnas;

        if(c != '0'){
            int valor_fijar = static_cast<int>(c - '0');
            fijar_opcion(fila, columna, valor_fijar);
        }

        ++actual;
    }
}

bool Sudoku::fijar_opcion(int fila, int columna, int opcion){
    bool exito = true;

    // Fijar opcion en la casilla actual
    bool resultado = m_casillas[fila][columna].fijar_opcion(opcion);
    exito = exito && resultado;

    // Eliminar opcion en toda la fila
    for(int c=0; c < m_columnas; ++c){
        if( c!= columna ){
            resultado = m_casillas[fila][c].eliminar_opcion(opcion);
            exito = exito && resultado;
        }
    }

    // Eliminar opcion en toda la columna
    for(int f=0; f < m_filas; ++f){
        if( f != fila){
            resultado = m_casillas[f][columna].eliminar_opcion(opcion);
            exito = exito && resultado;
        }
    }

    // Eliminar opcion en el cuadro
    int cuadro_fila_inicio = (fila / 3) * 3;
    int cuadro_columna_inicio = (columna / 3) * 3;

    for(int f=cuadro_fila_inicio; f < cuadro_fila_inicio+3; ++f){
        for(int c=cuadro_columna_inicio; c < cuadro_columna_inicio+3; ++c){
            if( f != fila && c != columna){
                resultado = m_casillas[f][c].eliminar_opcion(opcion);
                exito = exito && resultado;
            }
        }
    }

    return exito;
}

bool Sudoku::disponible_opcion(int fila, int columna, int opcion) const{
    return m_casillas[fila][columna].existe_opcion(opcion);
}

bool Sudoku::valido() const{
    for(const auto& fila: m_casillas){
        for(const auto& casilla: fila){
            if(!casilla.valida()){
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::resuelto() const{
    for(const auto& fila: m_casillas){
        for(const auto& casilla: fila){
            if(casilla.cantidad_opciones() != 1){
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku){
    for(const auto& fila: sudoku.m_casillas){
        for(const auto& casilla: fila){
            os << casilla;
        }
        os << '\n';
    }

    return os;
}



Sudoku::ListaSudokus Sudoku::sucesores() const{
    ListaSudokus sucesores;

    // Iterar por casillas
    for(int f=0; f < m_filas; ++f){
        for(int c=0; c < m_columnas; ++c){

            if(m_casillas[f][c].cantidad_opciones() > 1){
                // Crear copias con cada opcion
                for(int opcion: m_casillas[f][c].obtener_opciones()){
                    Sudoku nuevo(*this);
                    nuevo.fijar_opcion(f, c, opcion);

                    if(nuevo.valido()){
                        sucesores.push_back(std::move(nuevo));
                    }
                }

                return sucesores;
            }

        }
    }

    return sucesores;
}