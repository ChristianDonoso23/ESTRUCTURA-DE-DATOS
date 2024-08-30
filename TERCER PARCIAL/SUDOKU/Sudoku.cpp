#include "Sudoku.h"
#include <conio.h> // Para _getch()

Sudoku::Sudoku() {
    board = (int*)malloc(N * N * sizeof(int));
    for (int i = 0; i < N * N; i++) {
        *(board + i) = 0; // Inicializar el Sudoku con ceros
    }
    cellSize = 0;
    boardSize = 0;
}

Sudoku::~Sudoku() {
    free(board); // Liberar la memoria del tablero
}

void Sudoku::setCellSize(int size) {
    cellSize = size;
}

void Sudoku::setBoardSize(int size) {
    boardSize = size;
}

// Función para imprimir el tablero de Sudoku
void Sudoku::ImprimirTablero() {
    int left = 50, top = 50;

    // Establecer fondo blanco
    setbkcolor(WHITE);
    cleardevice(); // Limpiar la pantalla con el color de fondo

    setcolor(BLACK); // Color de las líneas
    setlinestyle(SOLID_LINE, 0, 3); // Estilo de línea sólido

    // Dibujar las líneas del tablero
    for (int i = 0; i <= N; i++) {
        int lineThickness = (i % 3 == 0) ? 4 : 1; // Bordes externos más gruesos
        setlinestyle(SOLID_LINE, 0, lineThickness);
        line(left + i * cellSize, top, left + i * cellSize, top + N * cellSize);
        line(left, top + i * cellSize, left + N * cellSize, top + i * cellSize);
    }

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(BLACK); // Color del texto negro

    // Usar lógica de punteros para imprimir el tablero
    ImprimirTableroRecursivo(0, 0, left, top);
}

void Sudoku::ImprimirTableroRecursivo(int i, int j, int left, int top) {
    if (i >= N) return; // Caso base: si hemos llegado al final del tablero

    int* cell = board + (i * N + j); // Acceder a la celda usando punteros
    if (*cell != 0) {
        char num[2];
        snprintf(num, sizeof(num), "%d", *cell);
        int x = left + j * cellSize + cellSize / 2 - 8;
        int y = top + i * cellSize + cellSize / 2 - 12;
        outtextxy(x, y, num);
    }

    if (j + 1 < N) {
        ImprimirTableroRecursivo(i, j + 1, left, top); // Continuar en la misma fila
    } else {
        ImprimirTableroRecursivo(i + 1, 0, left, top); // Pasar a la siguiente fila
    }
}

// Comprobar si es seguro colocar un número en una posición
bool Sudoku::esSeguro(int fila, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (*(board + fila * N + x) == num || *(board + x * N + col) == num)
            return false;
    }

    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (*(board + (startRow + i) * N + (startCol + j)) == num)
                return false;
        }
    }

    return true;
}

// Resolver el Sudoku
bool Sudoku::ResolverSudoku(int fila, int col) {
    if (fila == N - 1 && col == N) return true;
    if (col == N) {
        fila++;
        col = 0;
    }
    if (*(board + fila * N + col) != 0) return ResolverSudoku(fila, col + 1);

    for (int num = 1; num <= N; num++) {
        if (esSeguro(fila, col, num)) {
            *(board + fila * N + col) = num;
            if (ResolverSudoku(fila, col + 1)) return true;
            *(board + fila * N + col) = 0;
        }
    }
    return false;
}

// Generar un Sudoku completo
void Sudoku::GenerarSudokuCompleto() {
    int* numeros = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        *(numeros + i) = i + 1; // Usar lógica de punteros
    }

    // Mezclar los números
    MezclarNumeros(numeros, N);

    // Usar la lista mezclada para poblar la primera fila con números aleatorios
    LlenarPrimeraFila(0, numeros);

    // Resolver el Sudoku desde esta configuración inicial
    ResolverSudoku(0, 0);

    free(numeros);
}

void Sudoku::MezclarNumeros(int* numeros, int size) {
    if (size <= 1) return; // Caso base para la recursión

    // Mezclar usando el algoritmo de Fisher-Yates
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(*(numeros + i), *(numeros + j)); // Usar lógica de punteros
    }
}

void Sudoku::LlenarPrimeraFila(int j, int* numeros) {
    if (j >= N) return; // Caso base: hemos llenado la fila

    *(board + j) = *(numeros + j); // Acceso mediante punteros
    LlenarPrimeraFila(j + 1, numeros); // Llenar la siguiente celda
}

// Crear un Sudoku incompleto
void Sudoku::CrearSudokuIncompleto(int filledCells) {
    GenerarSudokuCompleto();
    srand(time(0));

    int cellsToRemove = N * N - filledCells;
    EliminarCeldas(cellsToRemove);
}

void Sudoku::EliminarCeldas(int cellsToRemove) {
    if (cellsToRemove <= 0) return; // Caso base: no quedan celdas por eliminar

    int i = rand() % N;
    int j = rand() % N;
    if (*(board + i * N + j) != 0) {
        *(board + i * N + j) = 0; // Acceso mediante punteros
        EliminarCeldas(cellsToRemove - 1); // Eliminar una celda y continuar
    } else {
        EliminarCeldas(cellsToRemove); // Intentar eliminar otra celda
    }
}
void Sudoku::ResetBoard() {
    for (int i = 0; i < N * N; i++) {
        *(board + i) = 0; // Reiniciar cada celda del tablero a 0
    }
}

