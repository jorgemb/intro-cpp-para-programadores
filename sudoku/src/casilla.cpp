#include <sudoku/casilla.hpp>

#include <algorithm>

Casilla::Casilla(): m_opciones{1, 2, 3, 4, 5, 6, 7, 8, 9} {}

bool Casilla::existe_opcion(int opcion) const{
    return std::find(m_opciones.begin(), m_opciones.end(), opcion) != m_opciones.end();
}

bool Casilla::eliminar_opcion(int opcion){
    auto iterador_opcion = std::find(m_opciones.begin(), m_opciones.end(), opcion);
    if(iterador_opcion == m_opciones.end()){
        return false;
    }

    m_opciones.erase(iterador_opcion);
    return true;
}

bool Casilla::fijar_opcion(int opcion){
    auto iterador_opcion = std::find(m_opciones.begin(), m_opciones.end(), opcion);
    if(iterador_opcion == m_opciones.end()){
        return false;
    }

    m_opciones = ListaOpciones{opcion};
    return true;
}

bool Casilla::valida() const{
    return !m_opciones.empty();
}


std::ostream& operator<<(std::ostream& os, const Casilla& casilla){
    if(casilla.cantidad_opciones() > 1){
        os << '0';
    } else if(casilla.cantidad_opciones() == 1){
        os << casilla.obtener_opciones()[0];
    } else {
        os << '-';
    }

    return os;
}