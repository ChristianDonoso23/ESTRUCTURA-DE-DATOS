#include "nreinas.h"
#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

Movimiento** movimientosPorSolucion = nullptr;
int* numMovimientosPorSolucion = nullptr;
int capacidadSoluciones = 0;
int numSoluciones = 0;
int** soluciones = nullptr;

void agregarMovimiento(int fila, int columna, const char* accion, Movimiento*& movimientos, int& capacidadMovimientos, int& numMovimientos) {
    if (numMovimientos >= capacidadMovimientos) {
        int nuevaCapacidad = capacidadMovimientos == 0 ? 10 : capacidadMovimientos * 2;
        movimientos = (Movimiento*)realloc(movimientos, nuevaCapacidad * sizeof(Movimiento));
        capacidadMovimientos = nuevaCapacidad;
    }
    Movimiento mov;
    mov.fila = fila;
    mov.columna = columna;
    strcpy(mov.accion, accion);
    movimientos[numMovimientos] = mov;
    ++numMovimientos;
}

void guardarMovimientosEnArchivo(const char* nombreArchivo, Movimiento* movimientos, int numMovimientos) {
    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    for (int i = 0; i < numMovimientos; ++i) {
        archivo << "Fila: " << movimientos[i].fila
                << ", Columna: " << movimientos[i].columna
                << ", Accion: " << movimientos[i].accion << '\n';
    }

    archivo << "Total de movimientos: " << numMovimientos << '\n';

    archivo.close();
}

void inicializarPosicionesReinas(int* posicionReinas, int n, int indice) {
    if (indice >= n) return;
    posicionReinas[indice] = -1;
    inicializarPosicionesReinas(posicionReinas, n, indice + 1);
}

bool esSeguroColocarReina(int* posicionReinas, int filaActual, int columna) {
    for (int i = 0; i < filaActual; ++i) {
        int otraColumna = posicionReinas[i];
        if (otraColumna == columna || abs(otraColumna - columna) == abs(i - filaActual)) {
            return false;
        }
    }
    return true;
}

void encontrarTodasLasSoluciones(int* posicionReinas, int filaActual, int n, Movimiento*& movimientos, int& capacidadMovimientos, int& numMovimientos) {
    if (filaActual == n) {
        if (numSoluciones >= capacidadSoluciones) {
            int nuevaCapacidad = capacidadSoluciones == 0 ? 10 : capacidadSoluciones * 2;
            soluciones = (int**)realloc(soluciones, nuevaCapacidad * sizeof(int*));
            movimientosPorSolucion = (Movimiento**)realloc(movimientosPorSolucion, nuevaCapacidad * sizeof(Movimiento*));
            numMovimientosPorSolucion = (int*)realloc(numMovimientosPorSolucion, nuevaCapacidad * sizeof(int));
            capacidadSoluciones = nuevaCapacidad;
        }
        soluciones[numSoluciones] = (int*)malloc(n * sizeof(int));
        memcpy(soluciones[numSoluciones], posicionReinas, n * sizeof(int));
        movimientosPorSolucion[numSoluciones] = (Movimiento*)malloc(numMovimientos * sizeof(Movimiento));
        memcpy(movimientosPorSolucion[numSoluciones], movimientos, numMovimientos * sizeof(Movimiento));
        numMovimientosPorSolucion[numSoluciones] = numMovimientos;
        ++numSoluciones;
        return;
    }
    for (int columna = 0; columna < n; ++columna) {
        if (esSeguroColocarReina(posicionReinas, filaActual, columna)) {
            posicionReinas[filaActual] = columna;
            agregarMovimiento(filaActual, columna, "Colocar", movimientos, capacidadMovimientos, numMovimientos);
            encontrarTodasLasSoluciones(posicionReinas, filaActual + 1, n, movimientos, capacidadMovimientos, numMovimientos);
            agregarMovimiento(filaActual, columna, "Eliminar", movimientos, capacidadMovimientos, numMovimientos);
            posicionReinas[filaActual] = -1;
        }
    }
}

int seleccionarIndiceSolucionAleatoria() {
    srand(time(nullptr));
    return rand() % numSoluciones;
}

void dibujarReina(int x, int y, int tamanoCuadro) {
    int margen = tamanoCuadro * 0.1;
    string path = "imagenes/ReinaBlanca1.jpg";
    readimagefile(path.c_str(), x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

void ejecutarNReinas(int n) {
    if (n <= 0) {
        cout << "El numero de reinas debe ser mayor que 0.\n";
        return;
    }
    int* posicionReinas = (int*)malloc(n * sizeof(int));
    if (posicionReinas == nullptr) {
        cout << "Error al asignar memoria.\n";
        return;
    }
    inicializarPosicionesReinas(posicionReinas, n, 0);

    numSoluciones = 0;
    capacidadSoluciones = 10;
    soluciones = (int**)malloc(capacidadSoluciones * sizeof(int*));
    movimientosPorSolucion = (Movimiento**)malloc(capacidadSoluciones * sizeof(Movimiento*));
    numMovimientosPorSolucion = (int*)malloc(capacidadSoluciones * sizeof(int));

    Movimiento* movimientosActuales = (Movimiento*)malloc(n * n * 2 * sizeof(Movimiento));
    int capacidadMovimientosActuales = n * n * 2;
    int numMovimientosActuales = 0;

    encontrarTodasLasSoluciones(posicionReinas, 0, n, movimientosActuales, capacidadMovimientosActuales, numMovimientosActuales);

    cout << "Numero total de soluciones encontradas: " << numSoluciones << endl;

    int indiceSolucionAleatoria = seleccionarIndiceSolucionAleatoria();
    int* solucionAleatoria = soluciones[indiceSolucionAleatoria];
    Movimiento* movimientosSolucionAleatoria = movimientosPorSolucion[indiceSolucionAleatoria];
    int numMovimientosSolucionAleatoria = numMovimientosPorSolucion[indiceSolucionAleatoria];

    for (int i = 0; i < n; ++i) {
        posicionReinas[i] = solucionAleatoria[i];
    }

    int tamanoCuadro = (n < 7) ? 70 : 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;
    closegraph();

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de N-Reinas");

    int inicioX = 20;
    int inicioY = 20;
    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();
    for (int fila = 0; fila < n; ++fila) {
        for (int columna = 0; columna < n; ++columna) {
            dibujarCuadroConPieza(tablero, fila, columna, nullptr);
        }
    }
    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);
    for (int fila = 0; fila < n; ++fila) {
        int columna = posicionReinas[fila];
        int x = tablero.inicioX + columna * tablero.tamanoCuadro;
        int y = tablero.inicioY + fila * tablero.tamanoCuadro;
        dibujarReina(x, y, tablero.tamanoCuadro);
    }
    getch();
    closegraph();

    guardarMovimientosEnArchivo("movimientos.txt", movimientosSolucionAleatoria, numMovimientosSolucionAleatoria);
    free(posicionReinas);
    free(movimientosActuales);
    for (int i = 0; i < numSoluciones; ++i) {
        free(soluciones[i]);
        free(movimientosPorSolucion[i]);
    }
    free(soluciones);
    free(movimientosPorSolucion);
    free(numMovimientosPorSolucion);
}
