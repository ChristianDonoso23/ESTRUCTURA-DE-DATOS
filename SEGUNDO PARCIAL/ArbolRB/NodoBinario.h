#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
private:
    string cedula;
    string nombre;
    string apellido;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;

public:
    // Constructor
    Nodo(string cedula, string nombre, string apellido);

    // Getters
    string getCedula() const;
    string getNombre() const;
    string getApellido() const;
    Nodo* getIzquierdo() const;
    Nodo* getDerecho() const;
    Nodo* getPadre() const;

    // Setters
    void setCedula(const string& cedula);
    void setNombre(const string& nombre);
    void setApellido(const string& apellido);
    void setIzquierdo(Nodo* izquierdo);
    void setDerecho(Nodo* derecho);
    void setPadre(Nodo* padre);
};

#endif // NODO_H
