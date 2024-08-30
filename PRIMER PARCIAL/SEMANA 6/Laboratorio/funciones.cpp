#include <iostream>
#include <fstream>
#include <cctype>
#include "funciones.h"

using namespace std;

void cargarCorreosExistentes(ListaDoble& lista, string& archivoNombre) {
    ifstream archivo(archivoNombre);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para leer correos existentes." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("Correo: ");
        if (pos != std::string::npos) {
            string correo = linea.substr(pos + 8); // 8 es la longitud de "Correo: "
            lista.insertar(correo);
        }
    }

    archivo.close();
}

void procesarNombres(ListaDoble& lista, ofstream& archivo) {
    string primerNombre, segundoNombre, apellido;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        cout << "Ingrese el primer nombre: ";
        cin >> primerNombre;
        cout << "Ingrese el segundo nombre: ";
        cin >> segundoNombre;
        cout << "Ingrese el apellido: ";
        cin >> apellido;

        // Extraer el primer caracter de ambos nombres y ponerlos en minúsculas
        char primerCaracterPrimerNombre = tolower(primerNombre[0]);
        char primerCaracterSegundoNombre = tolower(segundoNombre[0]);

        // Juntar los caracteres con el apellido
        string correo = std::string(1, primerCaracterPrimerNombre) + string(1, primerCaracterSegundoNombre) + apellido;

        // Convertir el apellido a minúsculas
        for (char& c : correo) {
            c = std::tolower(c);
        }

        // Dominio del correo
        string dominio = "@espe.edu.ec";

        // Verificar si el correo ya existe en la lista y aumentar el número si es necesario
        int numero = 1;
        string correoFinal = correo + dominio;
        while (lista.buscar(correoFinal)) {
            correoFinal = correo + to_string(numero) + dominio;
            numero++;
        }

        lista.insertar(correoFinal);
        archivo << "Nombre: " << primerNombre << " " << segundoNombre << " " << apellido << " - Correo: " << correoFinal << endl; // Escribir el nombre y correo en el archivo

        std::cout << "¿Desea ingresar otro nombre? (s/n): ";
        std::cin >> continuar;
    }
}
