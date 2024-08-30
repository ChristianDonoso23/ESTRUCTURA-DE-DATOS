
/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios recursividad 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 3 de junio de 2024
 * Fecha modificacion: viernes , 7 de junio de 2024 
 ***********************************************************************/
#include <iostream>
using namespace std;
// Función recursiva para calcular el n-ésimo número de Fibonacci
int fibonacci(int n) {
    // Caso base
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    // Llamada recursiva
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int num;
    cout << "Introduce un número: ";
    cin >> num;
    
    int result = fibonacci(num);
    cout << "El " << num << "-ésimo número de Fibonacci es " << result << endl;

    return 0;
}
