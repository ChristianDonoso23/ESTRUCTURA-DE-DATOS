/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios recursividad 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 3 de junio de 2024
 * Fecha modificacion: viernes , 7 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <string>
using namespace std;
// Función para intercambiar dos caracteres
void swap(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}

// Función recursiva para generar permutaciones
void permute(std::string str, int l, int r) {
    if (l == r) {
        std::cout << str << std::endl;
    } else {
        for (int i = l; i <= r; i++) {
            swap(str[l], str[i]);
            permute(str, l + 1, r);
            swap(str[l], str[i]); // backtrack
        }
    }
}

int main() {
    string str;
    cout << "Introduce una cadena: ";
    cin >> str;
    
    permute(str, 0, str.length() - 1);

    return 0;
}
