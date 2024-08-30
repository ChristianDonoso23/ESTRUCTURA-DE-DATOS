/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios recursividad 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 3 de junio de 2024
 * Fecha modificacion: viernes , 7 de junio de 2024 
 ***********************************************************************/
#include <iostream>
using namespace std;
// Función factorial recursiva
int factorial(int n) {
    // Caso base
    if (n == 0) {
        return 1;
    }
    // Llamada recursiva
    return n * factorial(n - 1);
}

int main() {
    int num;
    cout << "Introduce un número: ";
    cin >> num;
    
    int result = factorial(num);
    cout << "El factorial de " << num << " es " << result << endl;

    return 0;
}
