#include <iostream>
#include <vector>
using namespace std;

int main(){
    //Funcion lambda para multiplicar dos numeros
    auto multiplicar = [](int x, int y){return x * y;};
    int resultado = multiplicar(9,8);
    cout<<resultado<<endl;
    //Funcion lambda para verificar si un numero es par
    auto numeroPar = [](int numero){return numero%2==0;};
    bool par = numeroPar(10);
    cout<<par<<endl;
    //Funcion lambda para calcular la potencia de un numero;
    auto potencia = [](int base, int exponente){
        int resultado = 1;
        for (int i=0; i<exponente;i++){
            resultado=resultado*base;
        }
        return resultado;
    };
    cout<<potencia(2,5)<<endl;
    //Funcion lambda para determinar el numero mayor de un vector
    vector<int> numeros = {8,9,10,25,30,9,12};
    auto mayor = [](vector<int>& arreglo){
        int valor_maximo = arreglo[0];
        for(int& numero : arreglo){
            if(numero > valor_maximo){
                valor_maximo = numero;
            }
        }
        return valor_maximo;
    };
    int numeroMayor = mayor(numeros);
    cout<<numeroMayor<<endl;
    //Funcion lambda para calcular el promedio de un arreglo
    int arreglo[]={1,2,3,4,5};
    int tamanioArreglo=0;
    for(int i:arreglo){
        tamanioArreglo++;
    }
    auto promedio=[](int arreglo[], int tamanioArreglo) -> float{
        float suma=0.0;
        for (int i=0;i<tamanioArreglo;i++){
            suma+=arreglo[i];
        }
        return suma/tamanioArreglo;
    };
    cout<<promedio(arreglo,tamanioArreglo);

    return 0;
}
