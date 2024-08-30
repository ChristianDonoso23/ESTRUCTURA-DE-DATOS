#include "ListaDoble.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <termios.h>

using namespace std;

ListaDoble::ListaDoble() {
    primero = NULL;
    ultimo = NULL;
};

ListaDoble::~ListaDoble() {
    Nodo *actual = primero;
    while (actual != NULL) {
        Nodo *temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }
};

Nodo* ListaDoble::getPrimero() {
    return this->primero;
}

void ListaDoble::setPrimero(Nodo *primero) {
    this->primero = primero;
};

Nodo* ListaDoble::getUltimo() {
    return this->ultimo;
};

void ListaDoble::setUltimo(Nodo *ultimo) {
    this->ultimo = ultimo;
};

void ListaDoble::ingresarDato(string dato) {
    Nodo *nuevo = new Nodo();
    nuevo->setDato(dato);
    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        ultimo = nuevo;
    }
    cout << "Dato " << dato << " ingresado correctamente." << endl;
};

string ListaDoble::generarCorreo(string nombre) {
    int contador = 0;
    string correo = nombre + "@espe.edu.ec";
    return correoRepetido(correo, nombre, contador);
};

string ListaDoble::correoRepetido(string correo, string inicio, int contador){
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
};

void ListaDoble::mostrarLista() {
    Nodo* actual = primero;
    while (actual) {
        cout << "Dato: " << actual->getDato() << endl;
        actual = actual->getSiguiente();
    }
};

string ListaDoble::convertirMinusculas(string cadena){
    for (int i = 0; i < cadena.length(); i++) {
        cadena[i] = tolower(cadena[i]);
    }
    return cadena;
};

string ListaDoble::datos(string primerNombre, string segundoNombre, string apellido) {
    string cadena;
    cadena += tolower(primerNombre[0]);
    cadena += tolower(segundoNombre[0]);
    cadena += convertirMinusculas(apellido);
    return cadena;
};

void ListaDoble::disable_echo_mode(struct termios *old_attr) {
    struct termios new_attr;
    tcgetattr(STDIN_FILENO, old_attr);
    new_attr = *old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
};

void ListaDoble::restore_echo_mode(const struct termios *old_attr) {
    tcsetattr(STDIN_FILENO, TCSANOW, old_attr);
};

char *ListaDoble::ingresarNumeros(const char *msj, int max_length) {
    char *dato = (char *)malloc((max_length + 1) * sizeof(char));
    char c;
    int i = 0;
    struct termios old_attr;
    printf("%s", msj);
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
};

bool ListaDoble::cedulaRepetida(string cedula){
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
};

bool ListaDoble::validarCedula(const char *cedula){
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
};

void ListaDoble::guardarDatos(string primerNombre, string segundoNombre,string apellido, string cedula){
    ofstream archivo("datos.txt", ios::app);
    if (archivo.is_open()) {
        string correo = generarCorreo(datos(primerNombre,segundoNombre,apellido));
        archivo << "Cedula: " << cedula << " - " << " Nombre: " << primerNombre << " " << segundoNombre << " " << apellido << " - " << "Correo: " << correo << endl;
        archivo.close();
        cout << "Datos guardados correctamente en el archivo datos.txt" << endl;
    } else {
        cout << "Error al abrir el archivo datos.txt" << endl;
    }
};

void ListaDoble::mostrarDatos(string& nombreArchivo) {
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
};

string ListaDoble::validarLetras(const char* msj) {
    string dato;
    char c;
    cout << msj; // Utilizar cout en lugar de printf
    cout.flush(); // Agregar flush para asegurarse de que el buffer se vacíe
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (true) {
        read(STDIN_FILENO, &c, 1);
        if (c == '\n') {
            if (!dato.empty()) {
                break;
            }
        } else if (c == 127) { // backspace
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            dato += c;
            cout << c;
            cout.flush();
        }
        // Si se ingresa un número o un caracter no válido, no se hace nada
    }
    cout << "\n";
    cout.flush();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return dato;
}