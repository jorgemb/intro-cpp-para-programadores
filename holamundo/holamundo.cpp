// Mi primer programa en C++

/* Este es un comentario
largo que abarca varias
lineas */

#include <iostream>
#include <string>

int main(){
	std::cout << "¡Hola!, ¿cómo te llamas?" << std::endl;
	
	std::string nombre;
	std::cin >> nombre;
	
	std::cout << "¡Bienvenido " << nombre << "!" << std::endl;
	
	return 0;
}
