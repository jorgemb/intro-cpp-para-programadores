#include <laberinto/modelo.hpp>

#include <numeric>
#include <random>
#include <sstream>
#include <chrono>

LaberintoPerfecto::LaberintoPerfecto(int filas, int columnas): m_filas(filas), m_columnas(columnas),
m_estado_paredes(obtener_total_paredes(), true){
    // Crear conjuntos de habitaciones
    for(int i=0; i < obtener_total_habitaciones(); ++i){
        m_conjuntos_habitaciones.push_back(std::set<int>({i}));
    }

    // Crear lista con ID de paredes
    std::vector<int> paredes(obtener_total_paredes(), 0);
    std::iota(paredes.begin(), paredes.end(), 0);

    // auto semilla_inicial = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device aleatoriedad;
    auto semilla_inicial = aleatoriedad();
    std::default_random_engine generador(semilla_inicial);
    std::shuffle(paredes.begin(), paredes.end(), generador);

    // Iterar por las paredes
    for(auto iterador = paredes.begin(); iterador != paredes.end(); ++iterador){
        int indice_pared = *iterador;

        auto [hab_a, hab_b] = habitaciones_unidas_por_pared(indice_pared);
        int indice_conjunto_hab_a = obtener_conjunto_habitacion(hab_a);
        int indice_conjunto_hab_b = obtener_conjunto_habitacion(hab_b);

        if(indice_conjunto_hab_a != indice_conjunto_hab_b){
            // Tumbar pared
            m_estado_paredes[indice_pared] = false;
            unir_conjuntos_de_habitaciones(indice_conjunto_hab_a, indice_conjunto_hab_b);
        }
    }
    
}

int LaberintoPerfecto::obtener_columnas() const{
    return m_columnas;
}

int LaberintoPerfecto::obtener_filas() const{
    return m_filas;
}

int LaberintoPerfecto::obtener_total_habitaciones() const{
    return m_filas * m_columnas;
}

int LaberintoPerfecto::obtener_total_paredes() const{
    int verticales = m_filas * (m_columnas - 1);
    int horizontales = m_columnas * (m_filas - 1);
    return verticales + horizontales;
}

std::pair<int, int> LaberintoPerfecto::habitaciones_unidas_por_pared(int indice_pared) const{
    // Deterimnar si la pared es vertical u horizontal
    int paredes_por_fila = 2 * obtener_columnas() - 1;

    int fila_actual = indice_pared / paredes_por_fila;
    int pared_en_fila = indice_pared % paredes_por_fila;

    bool es_vertical = pared_en_fila < obtener_columnas() - 1;

    // Encontrar la habitacion a la izquierda (o arriba)
    int habitacion_a = -1;
    if(es_vertical){
        habitacion_a = fila_actual * obtener_columnas() + pared_en_fila;
    } else {
        habitacion_a = fila_actual * obtener_columnas() + (pared_en_fila - (obtener_columnas()-1));
    }

    // Encontrar la habitacion a la derecha (o abajo)
    int habitacion_b = -1;
    if(es_vertical){
        habitacion_b = habitacion_a + 1;
    } else {
        habitacion_b = habitacion_a + obtener_columnas();
    }

    return std::make_pair(habitacion_a, habitacion_b);
}

int LaberintoPerfecto::obtener_conjunto_habitacion(int indice_habitacion) const{
    for(auto iter = m_conjuntos_habitaciones.cbegin(); iter != m_conjuntos_habitaciones.cend(); ++iter){
        if(iter->find(indice_habitacion) != iter->cend()){
            return std::distance(m_conjuntos_habitaciones.begin(), iter);
        }
    }

    // ERROR
    return -1;
}


void LaberintoPerfecto::unir_conjuntos_de_habitaciones(int conjunto_a, int conjunto_b){
    // Alias de los conjuntos
    auto& ref_conjunto_a = m_conjuntos_habitaciones[conjunto_a];
    auto& ref_conjunto_b = m_conjuntos_habitaciones[conjunto_b];

    ref_conjunto_a.insert(ref_conjunto_b.begin(), ref_conjunto_b.end());
    ref_conjunto_b.clear();
}


std::string LaberintoPerfecto::str() const{
    //  _ _ _ 
    // |_|_|_|
    // |_|_|_|
    // |_|_|_|

    std::stringstream impresion;
    const char pared_v = '|', pared_h = '_', vacio = ' ';

    // Pared superior
    for(int columna = 0; columna < obtener_columnas(); ++columna){
        impresion << vacio << pared_h;
    }
    impresion << vacio << '\n';

    // Filas
    for(int fila = 0; fila < obtener_filas(); ++fila){
        // Primer pared
        impresion << pared_v;

        int paredes_por_fila = 2 * obtener_columnas() - 1;
        for(int columna = 0; columna < obtener_columnas(); ++columna){
            int id_pared_vertical = fila * paredes_por_fila + columna;
            int id_pared_horizontal = id_pared_vertical + (obtener_columnas() - 1);

            // Horizontal
            if(fila != obtener_filas() - 1){
                impresion << (m_estado_paredes[id_pared_horizontal] ? pared_h : vacio );
            } else {
                impresion << pared_h;
            }

            // Vertical
            if(columna != obtener_columnas() - 1){
                impresion << (m_estado_paredes[id_pared_vertical] ? pared_v : vacio );
            } else {
                impresion << pared_v;
            }

        }
        impresion << '\n';
    }

    return impresion.str();
}

