#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

unsigned int factorial(unsigned int n){
    if(n==0 || n==1){
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

TEST_CASE("Prueba de factorial", "[factorial]"){
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(5) == 120);
    REQUIRE(factorial(10) == 3628800);
}