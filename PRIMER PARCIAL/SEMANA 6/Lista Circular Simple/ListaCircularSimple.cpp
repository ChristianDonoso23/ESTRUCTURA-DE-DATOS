#include "ListaCircularSimple.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <termios.h>

using namespace std;

ListaCircularSimple::ListaCircularSimple() {
    primero = NULL;
    ultimo = NULL;
}

ListaCircularSimple::~ListaCircularSimple() {
    if (primero != NULL) {
        Nodo *actual = primero;
        do {
            Nodo *temp = actual;
            actual = actual->getSiguiente();
            delete temp;
        } while (actual != primero);
    }
}

Nodo* ListaCircularSimple::getPrimero() {
    return this->primero;
}

void ListaCircularSimple::setPrimero(Nodo *primero) {
    this->primero = primero;
}

Nodo* ListaCircularSimple::getUltimo() {
    return this->ultimo;
}

void ListaCircularSimple::setUltimo(Nodo *ultimo) {
    this->ultimo = ultimo;
}

void ListaCircularSimple::ingresarDato(string dato) {
    Nodo *nuevo = new Nodo();
    nuevo->setDato(dato);
    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->setSiguiente(nuevo);  // Apunta a sí mismo
    } else {
        nuevo->setSiguiente(primero);
        ultimo->setSiguiente(nuevo);
        ultimo = nuevo;
    }
    cout << "Dato " << dato << " ingresado correctamente." << endl;
}

string ListaCircularSimple::generarCorreo(string nombre) {
    int contador = 0;
    string correo = nombre + "@espe.edu.ec";
    return correoRepetido(correo, nombre, contador);
}

string ListaCircularSimple::correoRepetido(string correo, string inicio, int contador) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(correo) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if (encontrado) {
        do {
            contador++;
            correo = inicio + to_string(contador) + "@espe.edu.ec";
            encontrado = false;
            archivo.open("datos.txt");
            while (getline(archivo, linea)) {
                if (linea.find(correo) != string::npos) {
                    encontrado = true;
                    break;
                }
            }
            archivo.close();
        } while (encontrado);
    }

    return correo;
}

void ListaCircularSimple::mostrarLista() {
    if (primero == NULL) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo* actual = primero;
    do {
        cout << "Dato: " << actual->getDato() << endl;
        actual = actual->getSiguiente();
    } while (actual != primero);
}

string ListaCircularSimple::convertirMinusculas(string cadena) {
    for (int i = 0; i < cadena.length(); i++) {
        cadena[i] = tolower(cadena[i]);
    }
    return cadena;
}

string ListaCircularSimple::datos(string primerNombre, string segundoNombre, string apellido) {
    string cadena;
    cadena += tolower(primerNombre[0]);
    cadena += tolower(segundoNombre[0]);
    cadena += convertirMinusculas(apellido);
    return cadena;
}

void ListaCircularSimple::disable_echo_mode(struct termios *old_attr) {
    struct termios new_attr;
    tcgetattr(STDIN_FILENO, old_attr);
    new_attr = *old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}

void ListaCircularSimple::restore_echo_mode(const struct termios *old_attr) {
    tcsetattr(STDIN_FILENO, TCSANOW, old_attr);
};

char* ListaCircularSimple::ingresarNumeros(const char *msj, int max_length) {
    char *dato = (char *)malloc((max_length + 1) * sizeof(char));
    char c;
    int i = 0;
    struct termios old_attr;
    printf("%s: ", msj);
    fflush(stdout);
    disable_echo_mode(&old_attr);
    while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n') {
        if (c >= '0' && c <= '9' && i < max_length) {
            dato[i++] = c;
            write(STDOUT_FILENO, &c, 1);
        } else if (c == 127) {
            if (i > 0) {
                i--;
                write(STDOUT_FILENO, "\b \b", 3);
            }
        }
    }
    dato[i] = '\0';
    restore_echo_mode(&old_attr);
    printf("\n"); 
    int len = strlen(dato);
    if (len > 0 && dato[len - 1] == '\n') {
        dato[len - 1] = '\0';
    }
    return dato;
}

bool ListaCircularSimple::cedulaRepetida(string cedula) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(cedula) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    return encontrado;
}

bool ListaCircularSimple::validarCedula(const char *cedula) {
    printf("Cedula recibida: %s\n", cedula);
    int longitud = strlen(cedula);
    if (longitud != 10) {
        printf("Error: La cédula debe tener 10 dígitos.\n");
        return false;
    }
    int digitos[9];
    for (int i = 0; i < 9; i++) {
        if (cedula[i] >= '0' && cedula[i] <= '9') {
            digitos[i] = cedula[i] - '0';
        } else {
            printf("\nError: La cédula debe contener solo dígitos.\n");
            return false;
        }
    }
    // Calcular el dígito verificador
    int coef[] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int prod = digitos[i] * coef[i];
        if (prod > 9) prod -= 9;
        suma += prod;
    }

    int digitoVerificador = (10 - (suma % 10)) % 10;

    // Comparar el dígito verificador calculado con el último dígito de la cédula
    return (cedula[9] - '0') == digitoVerificador;
}

void ListaCircularSimple::guardarDatos(string primerNombre, string segundoNombre, string apellido, string cedula) {
    ofstream archivo("datos.txt", ios::app);
    if (archivo.is_open()) {
        string correo = generarCorreo(datos(primerNombre, segundoNombre, apellido));
        archivo << "Cedula: " << cedula << " - " << " Nombre: " << primerNombre << " " << segundoNombre << " " << apellido << " - " << "Correo: " << correo << endl;
        archivo.close();
        cout << "Datos guardados correctamente en el archivo datos.txt" << endl;
    } else {
        cout << "Error al abrir el archivo datos.txt" << endl;
    }
}

void ListaCircularSimple::mostrarDatos(string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
}
