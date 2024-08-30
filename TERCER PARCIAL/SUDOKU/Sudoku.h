#ifndef SUDOKU_H
#define SUDOKU_H

#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Sudoku {
private:
    int cellSize; // Tamaño de cada celda
    int boardSize; // Tamaño del tablero

    // Funciones privadas para operaciones recursivas
    void ImprimirTableroRecursivo(int i, int j, int left, int top);
    void MezclarNumeros(int* numeros, int size);
    void LlenarPrimeraFila(int j, int* numeros);
    void EliminarCeldas(int cellsToRemove);

public:
    int* board; // Puntero para el tablero
    static const int N = 9; // Tamaño del tablero

    Sudoku();
    ~Sudoku();
    void ImprimirTablero();
    bool esSeguro(int fila, int col, int num);
    bool ResolverSudoku(int fila, int col);
    void GenerarSudokuCompleto();
    void CrearSudokuIncompleto(int filledCells);
    void setCellSize(int size);
    void setBoardSize(int size);
    void ResetBoard();
};

#endif // SUDOKU_H
