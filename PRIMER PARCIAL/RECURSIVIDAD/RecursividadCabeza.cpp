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
// Función recursiva para invertir una cadena
void InvertirString(std::string &str, int index = 0) {
    // Caso base: si el índice alcanza la mitad de la cadena, se detiene
    if (index >= str.length() / 2) {
        return;
    }
    
    // Intercambiar los caracteres en la posición actual y la correspondiente desde el final
    swap(str[index], str[str.length() - 1 - index]);
    
    // Llamada recursiva
    InvertirString(str, index + 1);
}

int main() {
    string str;
    cout << "Introduce una cadena: ";
    cin >> str;
    
    InvertirString(str);
    
    cout << "Cadena invertida: " << str << endl;

    return 0;
}
