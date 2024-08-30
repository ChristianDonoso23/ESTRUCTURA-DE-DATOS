#include <iostream>
class Racional{
private:
    int numerador;
    int denominador;
public:
    Racional():numerador(0),denominador(1){}
    void in();
    Racional operator/(const Racional &obj);
    void out();
};
