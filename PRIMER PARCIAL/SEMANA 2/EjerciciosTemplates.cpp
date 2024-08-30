/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase fecha
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 13 de mayo de 2024
 * Fecha modificacion: viernes ,17 de mayo de 2024 
 ***********************************************************************/
#include<conio.h>
#include<iostream>
#include <vector>

using namespace std;

//plantilla para determinar el numero mayor de dos numeros
template <typename T>
T numeroMayor(T num1, T num2){
    T resultado;
    if(num1 > num2){
        resultado=num1;
    }else{
        resultado=num2;
    }
    return resultado;
}

//plantilla para determinar el numero menor de dos numeros
template <typename T>
T numeroMenor(T num1, T num2){
    T resultado;
    if(num1 < num2){
        resultado=num1;
    }else{
        resultado=num2;
    }
    return resultado;
}

//Plantilla para intercambiar los valores de dos variables del mismo tipo
template <typename T>
void intercambiar(T a, T b){
    T aux=a;
    a=b;
    b=aux;
}

//Plantilla para calcular la potencia de un numero
template <typename T>
T potencia(T base, int exponente){
    if(exponente==0){
        return 1;
    }else if(exponente>0){
        T resultado = 1;
        for(int i=0;i<exponente;i++){
            resultado = resultado*base;
        }
        return resultado;
    }else{
        T resultado = 1;
        for (int i = 0; i < -exponente; ++i) {
            resultado /= base;
        }
        return resultado;
    }
}

//Plantilla para sumar dos variables
template <typename T>
T sumar(T a, T b){
    return a + b;
}
//Plantilla para restar dos variables
template <typename T>
T restar(T a, T b){
    return a - b;
}
//Plantilla para multiplicar dos variables
template <typename T>
T multiplicar(T a, T b){
    return a * b;
}
//Plantilla para dividir dos variables
template <typename T>
T dividir(T a, T b){
    return a / b;
}

//Plantilla para determinar si un numero es positivo
template <typename T>
bool numPositivo(T num){
    return num > 0;
}

//Plantilla para buscar un elemento dentro de un vector de cualquier tipo
template <typename T>
int buscar(vector<T>& vector, T elemento) {
  for (int i = 0; i < vector.size(); ++i) {
    if (vector[i] == elemento) {
      return i; //
    }
  }
  return -1;
}

//Funcion principal
int main(){
    //Implementacion funcion numeroMayor
    int mayor = numeroMayor(10,20);
    cout<<mayor<<endl;

    //Implementacion funcion numeroMenor
    float menor = numeroMenor(10.4,10.5);
    cout<<menor<<endl;

    //Implementacion funcion intercambiar
    int x=25, y=20;
    intercambiar(x,y);
    cout<<x<<"     "<<y<<endl;

    //Implementacion funcion potencia
    int base=2,exp=3;
    cout<<potencia(base,exp)<<endl;

    //Implementacion funcion sumar, restar, multiplicar y dividir
    int num1=10, num2=2;
    cout<<sumar(num1,num2)<<endl;
    cout<<restar(num1,num2)<<endl;
    cout<<multiplicar(num1,num2)<<endl;
    cout<<dividir(num1,num2)<<endl;

    //Implementacion funcion numPositivo
    cout<<numPositivo(-655)<<endl;

    //Implementacion funcion buscar
    vector<int> vector_enteros = {10, 30, 30, 40, 50};
    int posicion_entero = buscar(vector_enteros, 30);
    if (posicion_entero != -1) {
        cout << "Elemento entero 30 encontrado en la posicion: " << posicion_entero << endl;
    } else {
        cout << "Elemento entero 30 no encontrado." <<endl;
    }

    getch();
}
