#include <iostream>

using namespace std;

// Función para multiplicar dos matrices
int** multiplicar_matrices(int** matriz1, int** matriz2, int n) {

    int** matrizR = nullptr;

	matrizR = (int**)malloc(n * sizeof(int*));
    
	for (int j = 0; j < n; j++) {
		*(matrizR + j) = (int*)malloc(3 * sizeof(int*));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(*(matrizR + i) + j) = 1;
		}
	}

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += *(*(matriz1 + i) + k)  *  *(*(matriz2 + k) + j);
            }
            *(*(matrizR+ i) + j) = sum;
        }
    }

    return matrizR;
}

// Función recursiva para calcular la potencia de una matriz.
int** potencia_matriz(int** matriz1, int n, int potencia) {
    // Cualquier matriz elevado a 1 es la misma matriz.
    if (potencia == 1) {
        return matriz1;
    }
    // Si la potencia es par
    if (potencia % 2 == 0) {
        int** potencia_par = potencia_matriz(matriz1, n, potencia / 2);
        int** resultado = multiplicar_matrices(potencia_par, potencia_par, n);
        return resultado;
    } else {
        // Si la potencia es impar
        int** potencia_impar = potencia_matriz(matriz1, n, potencia - 1);
        int** resultado = multiplicar_matrices(matriz1, potencia_impar, n);
        return resultado;
    }
}

int main() {
    // Tamaño de la matriz
    int n = 4; 
	int** mat1 = nullptr;
	mat1 = (int**)malloc(n * sizeof(int*));
	for (int j = 0; j < n; j++) {
		*(mat1 + j) = (int*)malloc(3 * sizeof(int*));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(*(mat1 + i) + j) = 1;
		}
	}
    // Aqui calculamos la potencia. 
    int potencia = 3;
    int** resultado = potencia_matriz(mat1, n, potencia);

    // Imprimir el resultado
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << *(*(resultado + i) + j) << " ";
        }
        cout << endl;
    }
    return 0;
}
