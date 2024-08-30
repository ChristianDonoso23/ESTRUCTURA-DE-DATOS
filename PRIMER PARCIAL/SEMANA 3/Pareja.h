/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
using namespace std;
class Pareja {

private:
    int a, b;

public:
    Pareja() : a(0), b(0) {}
    Pareja(const int a,const int b) {
	this->a = a;
	this->b = b;
    }

    Pareja(const Pareja&);

    Pareja& operator + (const Pareja &p); 	 	
    Pareja& operator - (const Pareja &p);
    Pareja& operator * (const Pareja &p);
    Pareja& operator / (const Pareja &p);
    Pareja& operator = (const Pareja &p);
    Pareja& operator ++();
    bool  operator ==(const Pareja &p) const;

    friend ostream& operator << (ostream &o,const Pareja &p);
    friend istream& operator >> (istream &o, Pareja &p);

    /**
     * @brief %
     * @param p 
     * @return Pareja
    */
    Pareja& operator % (const Pareja &p);

    /**
     * @brief <
     * @param p 
     * @return bool
    */
    bool operator < (const Pareja &p);

    /**
     * @brief >
     * @param p 
     * @return bool
    */
    bool operator > (const Pareja &p);

    /**
     * @brief <=
     * @param p 
     * @return bool
    */
    bool operator <= (const Pareja &p);

    /**
     * @brief >=
     * @param p 
     * @return bool
    */
    bool operator >= (const Pareja &p);

    /**
     * @brief +=
     * @param p 
     * @return Pareja
    */
    Pareja& operator += (const Pareja& p);

    /**
     * @brief -=
     * @param p 
     * @return Pareja
    */
    Pareja& operator -= (const Pareja& p);

    /**
     * @brief *=
     * @param p 
     * @return Pareja
    */
    Pareja& operator *= (const Pareja& p);

    /**
     * @brief /=
     * @param p 
     * @return Pareja
    */
    Pareja& operator /= (const Pareja& p);

    /**
     * @brief %=
     * @param p 
     * @return Pareja
    */
    Pareja& operator %= (const Pareja& p);
};