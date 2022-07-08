#ifndef GUARD_MODELO_HPP
#define GUARD_MODELO_HPP

#include <vector>
#include <string>
#include <set>
#include <utility>

class LaberintoPerfecto{
public:
    LaberintoPerfecto(int filas, int columnas);

    int obtener_filas() const;
    int obtener_columnas() const;
    int obtener_total_habitaciones() const;
    int obtener_total_paredes() const;

    std::pair<int, int> habitaciones_unidas_por_pared(int indice_pared) const;
    int obtener_conjunto_habitacion(int indice_habitacion) const;
    void unir_conjuntos_de_habitaciones(int conjunto_a, int conjunto_b);

    std::string str() const;

private:
    const int m_filas, m_columnas;

    std::vector<bool> m_estado_paredes;
    std::vector< std::set<int> > m_conjuntos_habitaciones;
};

inline std::ostream& operator<<(std::ostream& os, const LaberintoPerfecto& laberinto){
    os << laberinto.str();
    return os;
}

#endif /* GUARD_MODELO_HPP */
