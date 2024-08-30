#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

enum Color { ROJO, NEGRO };

class Nodo {
private:
    string cedula;
    string nombre;
    string apellido;
    Color color;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;

public:
    Nodo(string cedula, string nombre, string apellido, Color color = ROJO);

    // Getters
    string getCedula() const;
    string getNombre() const;
    string getApellido() const;
    Color getColor() const;
    Nodo* getIzquierdo() const;
    Nodo* getDerecho() const;
    Nodo* getPadre() const;

    // Setters
    void setCedula(const string& cedula);
    void setNombre(const string& nombre);
    void setApellido(const string& apellido);
    void setColor(Color color);
    void setIzquierdo(Nodo* izquierdo);
    void setDerecho(Nodo* derecho);
    void setPadre(Nodo* padre);
};

#endif // NODO_H
