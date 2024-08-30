#ifndef CUBO_MAGICO_H
#define CUBO_MAGICO_H

#include <graphics.h>  // Asumiendo que usas la biblioteca graphics.h para gráficos
#include <iostream>
#include <conio.h>  // Para _getch()
using namespace std;

class CuadradoMagico {
private:
    int n;  // Tamaño del cuadrado mágico
    bool esImpar;  // Indica si el cuadrado es impar (true) o par (false)
    int x_offset;  // Desplazamiento en el eje x para el dibujo
    int y_offset;  // Desplazamiento en el eje y para el dibujo

public:
    void dibujarCuadrado(int x, int y, int tamano, int numero);
    void llenarCuadradoMagicoImpar();
    void llenarCuadradoMagicoPar();
    void llenarCuadradoMagicoTradicional(int numero_inicial, int incremento);
    bool backtracking(int** cuadrado, bool* usados, int pos);
    bool esCuadradoMagico(int** cuadrado);
    CuadradoMagico(int tamano, bool esImpar, int x_offset, int y_offset);
    void dibujar();
};

#endif // CUBO_MAGICO_H
