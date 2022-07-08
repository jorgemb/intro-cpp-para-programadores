#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <sudoku/casilla.hpp>

TEMPLATE_TEST_CASE("Pruebas de Casilla", "[casilla]", Casilla, CasillaBit){
    const int maximo_opciones = 9;
    TestType casilla;

    SECTION("Opciones de una casilla inicial"){
        REQUIRE(casilla.cantidad_opciones() == maximo_opciones);

        int valor_esperado = 1;
        for(int valor: casilla.obtener_opciones()){
            REQUIRE(valor == valor_esperado);
            valor_esperado++;
        }

        for(int i=1; i <= maximo_opciones; ++i){
            REQUIRE(casilla.existe_opcion(i));
        }
    }


    for(int i=1; i <= maximo_opciones; ++i){
        DYNAMIC_SECTION("Eliminar opcion " << i){
            REQUIRE(casilla.existe_opcion(i));
            REQUIRE(casilla.eliminar_opcion(i));
            REQUIRE_FALSE(casilla.eliminar_opcion(i));

            for(int j=1; j <= maximo_opciones; ++j){
                if(i != j){
                    REQUIRE(casilla.existe_opcion(j));
                }
            }
        }
    }

    for(int i=1; i<= maximo_opciones; ++i){
        DYNAMIC_SECTION("Fijar opcion " << i){
            REQUIRE(casilla.fijar_opcion(i));
            REQUIRE(casilla.cantidad_opciones() == 1);

            for(int j=1; j <= maximo_opciones; ++j){
                if(i != j){
                    REQUIRE_FALSE(casilla.existe_opcion(j));
                } else {
                    REQUIRE(casilla.existe_opcion(j));
                }
            }
        }
    }

    SECTION("Casilla invalida"){
        REQUIRE(casilla.valida());
        for(int i=1; i <= maximo_opciones; ++i){
            casilla.eliminar_opcion(i);
        }

        REQUIRE_FALSE(casilla.valida());
    }
}