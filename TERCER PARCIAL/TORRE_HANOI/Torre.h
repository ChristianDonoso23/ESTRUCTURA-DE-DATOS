#ifndef TORRE_H
#define TORRE_H

#include "Disco.cpp"	

class Torre {
public:
    Torre(int altura, std::size_t capacidad_max, int posicion_x);  // Constructor actualizado
    void agregarDisco(Disco* disco);
    Disco* removerDisco();
    std::size_t getNumDiscos() const;
    void dibujar() const;  // Declaración del método dibujar
    ~Torre();
private:
    int altura_torre;
    std::size_t capacidad;
    std::size_t num_discos;
    int posicion_x;  // Variable para la posición en el eje x
    Disco** discos;
};

#endif // TORRE_H
