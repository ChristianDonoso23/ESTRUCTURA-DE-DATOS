
/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios recursividad 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 3 de junio de 2024
 * Fecha modificacion: viernes , 7 de junio de 2024 
 ***********************************************************************/
#include <iostream>
using namespace std;
// Función auxiliar para la recursividad por cola
int SumaRecursiva(int n, int accumulator) {
    if (n == 0) {
        return accumulator;
    }
    // Llamada recursiva por cola: se realiza al final del subprograma
    return SumaRecursiva(n - 1, accumulator + n);
}

// Función de interfaz para la recursividad por cola
int sum(int n) {
    return SumaRecursiva(n, 0);
}

int main() {
    int n;
    cout << "Introduce un número: ";
    cin >> n;

    int result = sum(n);
    cout << "La suma de los primeros " << n << " números naturales es: " << result << endl;

    return 0;
}
