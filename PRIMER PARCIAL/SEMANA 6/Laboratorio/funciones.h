#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
#include "ListaDoble.h"

using namespace std;

void procesarNombres(ListaDoble& lista, ofstream& archivo);
void cargarCorreosExistentes(ListaDoble& lista, string& archivoNombre);

#endif // FUNCIONES_H
