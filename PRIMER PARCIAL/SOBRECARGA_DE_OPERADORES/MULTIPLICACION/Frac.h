#include <iostream>
class Frac{
private:
    int a;
    int b;
public:
    Frac():a(0),b(0){}
    void in();
    Frac operator*(const Frac &obj);
    void out();

};
