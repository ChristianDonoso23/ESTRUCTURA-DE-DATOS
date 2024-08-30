#ifndef JUEGOHANOI_H
#define JUEGOHANOI_H

#include "Torre.cpp"
#include <fstream>  // Para manejar archivos

class JuegoHanoi {
public:
    // Constructor que acepta el número de discos, el número de torres y la torre de origen
    JuegoHanoi(int numDiscos, int numTorres, int torreOrigen);
    void moverDiscos(int numDiscos, int torreOrigen, int torreDestino, int torreAuxiliar);
    void dibujar();
    ~JuegoHanoi();

private:
    int numDiscos;
    int numTorres;
    Torre** torres;
    std::ofstream archivoMovimientos;  // Objeto para manejar el archivo de movimientos
};

#endif // JUEGOHANOI_H
