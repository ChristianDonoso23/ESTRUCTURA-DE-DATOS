/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios recursividad 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 3 de junio de 2024
 * Fecha modificacion: viernes , 7 de junio de 2024 
 ***********************************************************************/
#include <iostream>
using namespace std;

void functionA(int n);
void functionB(int n);

void functionA(int n) {
    if (n > 0) {
        cout << "Function A: " << n << endl;
        functionB(n - 1);
    }
}

void functionB(int n) {
    if (n > 0) {
        cout << "Function B: " << n << endl;
        functionA(n / 2);
    }
}

int main() {
    int num;
    cout << "Introduce un número: ";
    cin >> num;
    
    functionA(num);

    return 0;
}
