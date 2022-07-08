#ifndef GUARD_CASILLA_HPP
#define GUARD_CASILLA_HPP

#include <vector>
#include <ostream>

#include <bitset>

class Casilla{
public:
    Casilla();

    using ListaOpciones = std::vector<int>;
    ListaOpciones::size_type cantidad_opciones() const{
        return m_opciones.size();
    }
    ListaOpciones obtener_opciones() const{
        return m_opciones;
    }

    bool eliminar_opcion(int opcion);
    bool fijar_opcion(int opcion); 
    bool existe_opcion(int opcion) const;

    bool valida() const;
private:
    ListaOpciones m_opciones;
};

std::ostream& operator<<(std::ostream& os, const Casilla& casilla);


class CasillaBit{
public:
    CasillaBit(): m_opciones(0b111111111) {}

    using ListaOpciones = std::vector<int>;
    ListaOpciones::size_type cantidad_opciones() const{
        return m_opciones.count();
    }

    ListaOpciones obtener_opciones() const{
        ListaOpciones opciones;
        for(int i=0; i < m_opciones.size(); ++i){
            if(m_opciones.test(i)){
                opciones.push_back(i+1);
            }
        }

        return opciones;
    }

    bool eliminar_opcion(int opcion){
        int posicion = opcion-1;

        if(!m_opciones.test(posicion)){
            return false;
        }

        m_opciones.reset(posicion);
        return true;
    }

    bool fijar_opcion(int opcion) {
        int posicion = opcion-1;

        if(!m_opciones.test(posicion)){
            return false;
        }

        m_opciones.reset();
        m_opciones.set(posicion);
        return true;
    }

    bool existe_opcion(int opcion) const{
        int posicion = opcion-1;
        return m_opciones.test(posicion);
    }

    bool valida() const{
        return m_opciones.any();
    }
private:
    std::bitset<9> m_opciones;
};


inline std::ostream& operator<<(std::ostream& os, const CasillaBit& casilla){
    auto cantidad_opciones = casilla.cantidad_opciones();

    if(cantidad_opciones == 0){
        os << '-';
    } else if(cantidad_opciones == 1){
        os << casilla.obtener_opciones().front();
    } else {
        os << '0';
    }

    return os;
}

#endif /* GUARD_CASILLA_HPP */
