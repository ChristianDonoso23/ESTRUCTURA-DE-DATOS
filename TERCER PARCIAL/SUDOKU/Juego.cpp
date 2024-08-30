#include <graphics.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>  // Para _getch()

using namespace std;

const int N = 9;
int cellSize;
int boardSize;

// Función para imprimir el tablero de Sudoku
void ImprimirTablero(int* Sudoku) {
    int left = 50, top = 50;
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, 3);

    for (int i = 0; i <= N; i++) {
        int lineThickness = (i % 3 == 0) ? 3 : 1;
        setlinestyle(SOLID_LINE, 0, lineThickness);
        line(left + i * cellSize, top, left + i * cellSize, top + N * cellSize);
        line(left, top + i * cellSize, left + N * cellSize, top + i * cellSize);
    }

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (*(Sudoku + i * N + j) != 0) {
                char num[2];
                snprintf(num, sizeof(num), "%d", *(Sudoku + i * N + j));
                int x = left + j * cellSize + cellSize / 2 - 8;
                int y = top + i * cellSize + cellSize / 2 - 12;
                outtextxy(x, y, num);
            }
        }
    }
}

// Comprobar si es seguro colocar un número en una posición
bool esSeguro(int* Sudoku, int fila, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (*(Sudoku + fila * N + x) == num || *(Sudoku + x * N + col) == num)
            return false;
    }

    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (*(Sudoku + (startRow + i) * N + (startCol + j)) == num)
                return false;
        }
    }

    return true;
}

// Resolver el Sudoku
bool ResolverSudoku(int* Sudoku, int fila, int col) {
    if (fila == N - 1 && col == N) return true;
    if (col == N) {
        fila++;
        col = 0;
    }
    if (*(Sudoku + fila * N + col) != 0) return ResolverSudoku(Sudoku, fila, col + 1);

    for (int num = 1; num <= N; num++) {
        if (esSeguro(Sudoku, fila, col, num)) {
            *(Sudoku + fila * N + col) = num;
            if (ResolverSudoku(Sudoku, fila, col + 1)) return true;
            *(Sudoku + fila * N + col) = 0;
        }
    }
    return false;
}

// Generar un Sudoku completo
void GenerarSudokuCompleto(int* Sudoku) {
    int* numeros = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        *(numeros + i) = i + 1;
    }

    // Mezclar los números
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(*(numeros + i), *(numeros + j));
    }

    // Usar la lista mezclada para poblar la primera fila con números aleatorios
    for (int j = 0; j < N; j++) {
        *(Sudoku + j) = *(numeros + j);
    }

    // Resolver el Sudoku desde esta configuración inicial
    ResolverSudoku(Sudoku, 0, 0);

    free(numeros);
}

// Crear un Sudoku incompleto
void CrearSudokuIncompleto(int* Sudoku, int filledCells) {
    GenerarSudokuCompleto(Sudoku);
    srand(time(0));

    int cellsToRemove = N * N - filledCells;
    while (cellsToRemove > 0) {
        int i = rand() % N;
        int j = rand() % N;
        if (*(Sudoku + i * N + j) != 0) {
            *(Sudoku + i * N + j) = 0;
            cellsToRemove--;
        }
    }
}

// Mostrar el menú y permitir la navegación
int MostrarMenu() {
    int opcion = 1;
    const int totalOpciones = 3;

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
            else if (i == 3) cout << "3. Salir" << endl;
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
    // Crear el Sudoku usando memoria dinámica
    int* Sudoku = (int*)malloc(N * N * sizeof(int));
    for (int i = 0; i < N * N; i++) {
        *(Sudoku + i) = 0;
    }

    int windowSize = 600;
    cellSize = windowSize / N;
    boardSize = N * cellSize;
    bool sudokuGenerado = false;

    int opcion;
    do {
        opcion = MostrarMenu();

        if (opcion == 1) {
            initwindow(boardSize + 100, boardSize + 100, "Sudoku Solver");
            CrearSudokuIncompleto(Sudoku, 30);
            ImprimirTablero(Sudoku);
            sudokuGenerado = true;
            getch();
            closegraph();
        } else if (opcion == 2) {
            if (!sudokuGenerado) {
                cout << "Primero debe generar un Sudoku aleatorio (opcion 1)." << endl;
                getch();
            } else {
                initwindow(boardSize + 100, boardSize + 100, "Sudoku Solver");
                if (ResolverSudoku(Sudoku, 0, 0)) {
                    ImprimirTablero(Sudoku);
                    cout << "Sudoku completado" << endl;
                } else {
                    cout << "No se pudo completar el Sudoku." << endl;
                }
                // Reiniciar el Sudoku a 0 antes de resolverlo
                for (int i = 0; i < N * N; i++) {
                    *(Sudoku + i) = 0;
                }
                getch();
                closegraph();
            }
        } else if (opcion == 3) {
            cout << "Saliendo del programa..." << endl;
        }

    } while (opcion != 3);

    // Liberar la memoria dinámica
    free(Sudoku);

    return 0;
}