#include <iostream>
#include "Frac.h"
using namespace std;
int main(){
    Frac F1,F2,result;
    system("cls");
    cout<<"Ingrese la primera fraccion: "<<endl;
    F1.in();

    cout<<"Ingrese la segunda fraccion: "<<endl;
    F2.in();
    result = F1*F2;
    result.out();

    return 0;

}
