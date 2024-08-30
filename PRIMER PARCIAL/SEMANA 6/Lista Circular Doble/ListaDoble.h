#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Nodo.cpp"

using namespace std;

class ListaDoble {
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaDoble();
    ~ListaDoble();
    Nodo* getPrimero();
    void setPrimero(Nodo* );
    Nodo* getUltimo();
    void setUltimo(Nodo* );
    
    void ingresarDato(string);
    string generarCorreo(string);
    string datos(string, string, string);
    void disable_echo_mode(struct termios* );
    void restore_echo_mode(const struct termios* );

    bool validarCedula(const char* cedula);
    char* ingresarNumeros(const char* msj, int max_length);    
    void guardarDatos(string, string, string, string);
    string correoRepetido(string, string, int);
    string convertirMinusculas(string);
    void mostrarDatos(string&);
    bool cedulaRepetida(string);
    void mostrarLista();

    
};