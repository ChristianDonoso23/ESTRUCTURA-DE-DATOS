#include <iostream>
#include <fstream>
#include "ListaDoble.cpp"
#include "funciones.cpp"

using namespace std;

int main() {
    ListaDoble lista;
    string archivoNombre = "correos.txt";
    
    // Cargar correos existentes en la lista
    cargarCorreosExistentes(lista, archivoNombre);

    std::ofstream archivo(archivoNombre, std::ios::app); // Abrir archivo en modo append

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    procesarNombres(lista, archivo); // Llamar a la función para procesar nombres

    archivo.close(); // Cerrar el archivo

    return 0;
}
