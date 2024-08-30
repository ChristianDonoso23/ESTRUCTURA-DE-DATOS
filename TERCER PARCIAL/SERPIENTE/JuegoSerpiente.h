#ifndef JUEGO_SERPIENTE_H
#define JUEGO_SERPIENTE_H

#include "ListaSimple.cpp"
#include "ListaObstaculos.h"

enum eDireccion { PARADO = 0, IZQUIERDA, DERECHA, ARRIBA, ABAJO };
enum ModoJuego { FACIL, MEDIO, DIFICIL };

class JuegoSerpiente {
public:
    JuegoSerpiente(ModoJuego modo = FACIL);
    void Ejecutar();

private:
    void Configurar();
    void Dibujar();
    void CapturarEntrada();
    void Logica();
    void Limpiar();
    bool esPosicionOcupadaPorObstaculo(int x, int y) const;
    
    bool juegoTerminado;
    eDireccion direccion;
    ListaSimple serpiente;
    ListaObstaculos obstaculos;
    Posicion comida;
    ModoJuego modoJuego;
    const int ANCHO = 20;
    const int ALTO = 17;
};

#endif // JUEGO_SERPIENTE_H
