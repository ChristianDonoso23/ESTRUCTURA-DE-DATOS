#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
#include "Nodo.cpp"
#include <functional>

class ListaSimple {
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaSimple();
    ~ListaSimple();
    Nodo* getPrimero();
    void setPrimero(Nodo* );
    Nodo* getUltimo();
    void setUltimo(Nodo* );
    
    void ingresarDato(string);
    string generarCorreo(string);
    string datos(string, string, string);
    void disable_echo_mode(struct termios* );
    void restore_echo_mode(const struct termios* );

    bool validarCedula(const char* );
    char* ingresarNumeros(const char*, int);    
    void guardarDatos(string, string, string, string);
    string correoRepetido(string, string, int);
    string convertirMinusculas(string);
    void mostrarDatos(string&);
    bool cedulaRepetida(string);
    void mostrarLista();
    string validarLetras(const char*, bool);
    char* generarContrasenia( const char*, const char*, const char*);
    string ingresarLetras(const char*);
    string contrasenaRepetida(string );
    char *cifrarCesar(const char* , int );
};
#endif  // LISTASIMPLE_H
