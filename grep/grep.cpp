#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

void coincidencias_archivo(const string& nombre_archivo, const regex& re_patron, 
	bool mostrar_linea, bool mostrar_nombre){
		
	// Abrir el archivo
	ifstream archivo(nombre_archivo);
	if(!archivo.is_open()){
		cerr << "No fue posible abrir el archivo: " << nombre_archivo
		<< endl;
		
		return;
	}
	
	// Buscar el patron y mostrar lineas
	string linea;
	size_t numero_linea = 1;
	while(getline(archivo, linea)){
		if(regex_search(linea, re_patron)){
			// Mostrar nombre del archivo
			if(mostrar_nombre){
				cout << nombre_archivo << ": ";
			}
			
			// Mostrar numero de linea
			if(mostrar_linea){
				cout << numero_linea << ": ";
			}
			cout << linea << endl;
		}
		
		++numero_linea;
	}
}

int main(int argc, char* argv[]){
	// Verificar argumentos en linea de comandos
	if(argc < 3){
		cout << "Uso: " << argv[0] 
		<< "[-n] <patron> <nombre_archivo> [<nombre_archivo>...]" << endl;
		return 0;
	}
	
	// Recibir parametros de la linea de comandos
	bool leido_patron = false, mostrar_linea = false;
	string patron;
	vector<string> lista_archivos;
	
	for(int i=1; i != argc; ++i){
		string argumento = argv[i];
		
		if(argumento == "-n"){
			mostrar_linea = true;
		}else if(!leido_patron){
			patron = argumento;
			leido_patron = true;
		} else {
			lista_archivos.push_back(argumento);
		}
	}
	
	// Buscar el patron en cada archivo
	bool mostrar_nombre = lista_archivos.size() > 1;
	regex re_patron(patron, regex_constants::icase);
	
	for(int i=0; i < lista_archivos.size(); ++i){
		coincidencias_archivo(lista_archivos[i], re_patron, 
		mostrar_linea, mostrar_nombre);
	}
	
	
	
	
	
	
	return 0;
}