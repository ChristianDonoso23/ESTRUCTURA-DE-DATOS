#include "CuboMagico.h"
#include <cstdio>    // Para sprintf
#include <conio.h>   // Para textwidth y textheight
#include <cstdlib>   // Para malloc y free

CuadradoMagico::CuadradoMagico(int tamano, bool esImpar, int x_offset, int y_offset)
    : n(tamano), esImpar(esImpar), x_offset(x_offset), y_offset(y_offset) {}

void CuadradoMagico::dibujarCuadrado(int x, int y, int tamano, int numero) {
    rectangle(x, y, x + tamano, y + tamano);  // Dibuja el cuadrado

    char buffer[5];
    sprintf(buffer, "%d", numero);  // Convierte el número a texto
    int text_width = textwidth(buffer);  // Ancho del texto
    int text_height = textheight(buffer);  // Altura del texto
    int text_x = x + (tamano - text_width) / 2;  // Posición x para centrar el texto
    int text_y = y + (tamano - text_height) / 2;  // Posición y para centrar el texto

    outtextxy(text_x, text_y, buffer);  // Muestra el número en la celda, centrado
}

bool CuadradoMagico::esCuadradoMagico(int** cuadrado) {
    int suma_fila = 0, suma_columna = 0;
    int suma_diagonal1 = 0, suma_diagonal2 = 0;

    for (int i = 0; i < n; ++i) {
        suma_fila = suma_columna = 0;
        for (int j = 0; j < n; ++j) {
            suma_fila += *(*(cuadrado + i) + j);  // Acceso mediante punteros
            suma_columna += *(*(cuadrado + j) + i);
        }
        if (suma_fila != 30 || suma_columna != 30) {
            return false;
        }
    }

    for (int i = 0; i < n; ++i) {
        suma_diagonal1 += *(*(cuadrado + i) + i);
        suma_diagonal2 += *(*(cuadrado + i) + (n - i - 1));
    }

    return (suma_diagonal1 == 30 && suma_diagonal2 == 30);
}

bool CuadradoMagico::backtracking(int** cuadrado, bool* usados, int pos) {
    if (pos == n * n) {
        return esCuadradoMagico(cuadrado);
    }

    int fila = pos / n;
    int col = pos % n;

    for (int num = 2; num <= n * n * 2; num += 2) {
        if (!*(usados + (num / 2 - 1))) {
            *(usados + (num / 2 - 1)) = true;
            *(*(cuadrado + fila) + col) = num;
            if (backtracking(cuadrado, usados, pos + 1)) {
                return true;
            }
            *(usados + (num / 2 - 1)) = false;
            *(*(cuadrado + fila) + col) = 0;
        }
    }

    return false;
}

void CuadradoMagico::llenarCuadradoMagicoPar() {
    int tamano_celda = 100;  // Tamaño de cada celda del cuadrado mágico

    // Crear cuadrado dinámico
    int** cuadrado = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        *(cuadrado + i) = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            *(*(cuadrado + i) + j) = 0;  // Inicializar en 0
        }
    }

    // Crear arreglo dinámico para marcar los números usados
    bool* usados = (bool*)malloc(n * n * sizeof(bool));
    for (int i = 0; i < n * n; ++i) {
        *(usados + i) = false;
    }

    // Resolver el cuadrado mágico con backtracking
    if (backtracking(cuadrado, usados, 0)) {
        // Dibuja el cuadrado mágico
        setbkcolor(WHITE);  // Establece el color de fondo blanco
        cleardevice();  // Limpia la ventana con el color de fondo establecido

        setcolor(BLACK);  // Color negro para el trazo de los cuadrados y el texto
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Estilo de texto (fuente por defecto, horizontal, tamaño 2)

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x = j * tamano_celda + x_offset;  // Calcula la posición x
                int y = i * tamano_celda + y_offset;  // Calcula la posición y
                dibujarCuadrado(x, y, tamano_celda, *(*(cuadrado + i) + j));  // Dibuja el número en la celda
            }
        }
    } else {
        cout << "No se encontró una solución." << endl;
    }

    // Liberar la memoria dinámica
    for (int i = 0; i < n; ++i) {
        free(*(cuadrado + i));
    }
    free(cuadrado);
    free(usados);
}

void CuadradoMagico::llenarCuadradoMagicoImpar() {
    int i = 0, j = n / 2;  // Empieza en la fila 0, columna central
    int numero_actual = 1;  // Primer número para cuadrado mágico impar
    int tamano_celda = 100;  // Tamaño de cada celda del cuadrado mágico

    setbkcolor(WHITE);  // Establece el color de fondo blanco
    cleardevice();  // Limpia la ventana con el color de fondo establecido

    setcolor(BLACK);  // Color negro para el trazo de los cuadrados y el texto
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Estilo de texto (fuente por defecto, horizontal, tamaño 2)

    // Crear cuadrado dinámico
    int** cuadrado = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        *(cuadrado + i) = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            *(*(cuadrado + i) + j) = 0;  // Inicializar en 0
        }
    }

    for (int count = 1; count <= n * n; count++) {
        int x = j * tamano_celda + x_offset;  // Desplaza el cuadrado en el eje x
        int y = i * tamano_celda + y_offset;  // Desplaza el cuadrado en el eje y

        *(*(cuadrado + i) + j) = numero_actual;
        dibujarCuadrado(x, y, tamano_celda, numero_actual);  // Dibuja el número en la celda

        int nueva_i = (i - 1 + n) % n;
        int nueva_j = (j + 1) % n;

        if (*(*(cuadrado + nueva_i) + nueva_j) != 0) {
            i = (i + 1) % n;
        } else {
            i = nueva_i;
            j = nueva_j;
        }

        numero_actual += 2;  // Incrementa en 2 para usar solo números impares
    }

    // Liberar la memoria dinámica
    for (int i = 0; i < n; ++i) {
        free(*(cuadrado + i));
    }
    free(cuadrado);
}

void CuadradoMagico::dibujar() {
    if (esImpar) {
        llenarCuadradoMagicoImpar();
    } else {
        llenarCuadradoMagicoPar();
    }
}

void CuadradoMagico::llenarCuadradoMagicoTradicional(int numero_inicial, int incremento) {
    int tamano_celda = 100;  // Tamaño de cada celda del cuadrado mágico

    // Crear cuadrado dinámico
    int** cuadrado = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        *(cuadrado + i) = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            *(*(cuadrado + i) + j) = 0;  // Inicializar en 0
        }
    }

    int fila = 0;   // Comienza en la fila superior
    int columna = 1; // Comienza en la columna central
    int numero_actual = numero_inicial;  // Primer número para el cuadrado mágico

    while (numero_actual <= numero_inicial + (n * n - 1) * incremento) {
        *(*(cuadrado + fila) + columna) = numero_actual;  // Coloca el número en la celda
        numero_actual += incremento;  // Incrementa el número

        // Calcula la nueva posición
        int nueva_fila = (fila - 1 + n) % n;  // Mueve a la celda diagonal superior
        int nueva_columna = (columna + 1) % n;

        if (*(*(cuadrado + nueva_fila) + nueva_columna) != 0) {  // Si la celda ya está ocupada
            nueva_fila = (fila + 1) % n;  // Mueve a la celda directamente debajo
            nueva_columna = columna;
        }

        fila = nueva_fila;
        columna = nueva_columna;
    }

    // Dibuja el cuadrado mágico
    setbkcolor(WHITE);  // Establece el color de fondo blanco
    cleardevice();  // Limpia la ventana con el color de fondo establecido

    setcolor(BLACK);  // Color negro para el trazo de los cuadrados y el texto
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Estilo de texto (fuente por defecto, horizontal, tamaño 2)

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = j * tamano_celda + x_offset;  // Calcula la posición x
            int y = i * tamano_celda + y_offset;  // Calcula la posición y
            dibujarCuadrado(x, y, tamano_celda, *(*(cuadrado + i) + j));  // Dibuja el número en la celda
        }
    }

    // Liberar la memoria dinámica
    for (int i = 0; i < n; ++i) {
        free(*(cuadrado + i));
    }
    free(cuadrado);
}
