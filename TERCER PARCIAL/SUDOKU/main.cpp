#include <graphics.h>
#include <iostream>
#include <conio.h> // Para _getch()
#include "Sudoku.cpp" // Incluir la clase Sudoku

using namespace std;

int MostrarMenu() {
    int opcion = 1;
    const int totalOpciones = 3; // Reducir el total de opciones a 3

    while (true) {
        system("cls"); // Limpiar la consola
        cout << "Seleccione una opcion:" << endl;

        // Mostrar opciones de menú
        for (int i = 1; i <= totalOpciones; i++) {
            if (i == opcion) {
                cout << "> "; // Indicador de la opción seleccionada
            } else {
                cout << "  ";
            }

            if (i == 1) cout << "1. Ver Sudoku con numeros generados aleatoriamente" << endl;
            else if (i == 2) cout << "2. Completar Sudoku" << endl;
            else if (i == 3) cout << "3. Salir" << endl; // Opción para salir
        }

        // Capturar la entrada de teclas
        int key = _getch();
        if (key == 224) { // Tecla especial
            key = _getch(); // Captura la siguiente tecla
            if (key == 72) { // Flecha arriba
                opcion--;
                if (opcion < 1) opcion = totalOpciones; // Envolver hacia abajo
            } else if (key == 80) { // Flecha abajo
                opcion++;
                if (opcion > totalOpciones) opcion = 1; // Envolver hacia arriba
            }
        } else if (key == 13) { // Enter
            return opcion; // Retornar la opción seleccionada
        }
    }
}

int main() {
    Sudoku sudoku; // Crear una instancia de Sudoku
    int windowSize = 600;
    int filledCells = 30; // Número de celdas llenas en el Sudoku
    sudoku.setCellSize(windowSize / Sudoku::N);
    sudoku.setBoardSize(windowSize);
    bool sudokuGenerado = false;

    int opcion;
    do {
        opcion = MostrarMenu();

        if (opcion == 1) {
            sudoku.ResetBoard(); // Reiniciar el tablero antes de crear un nuevo Sudoku
            initwindow(windowSize + 100, windowSize + 100, "Sudoku Solver");
            sudoku.CrearSudokuIncompleto(filledCells);
            sudoku.ImprimirTablero();
            sudokuGenerado = true;
            getch();
            closegraph(); // Cerrar la ventana gráfica
        } else if (opcion == 2) {
            if (!sudokuGenerado) {
                cout << "Primero debe generar un Sudoku aleatorio (opcion 1)." << endl;
                getch();
            } else {
                initwindow(windowSize + 100, windowSize + 100, "Sudoku Solver");
                if (sudoku.ResolverSudoku(0, 0)) {
                    sudoku.ImprimirTablero();
                    cout << "Sudoku completado" << endl;
                } else {
                    cout << "No se pudo completar el Sudoku." << endl;
                }
                // Reiniciar el Sudoku a 0 antes de resolverlo
                for (int i = 0; i < sudoku.N * sudoku.N; i++) {
                    *(sudoku.board + i) = 0; // Reseteo del tablero
                }
                getch();
                closegraph();
            }
        } else if (opcion == 3) {
            cout << "Saliendo del programa..." << endl; // Mensaje al salir
        }

    } while (opcion != 3);

    return 0;
}
