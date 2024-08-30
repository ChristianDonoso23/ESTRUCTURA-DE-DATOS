/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#pragma once
#include <string>

using namespace std; 

class Persona
{
public:
	void setNombre(string nuevoNombre);
	void setEdad(int nuevaEdad);
	void setPeso(double nuevoPeso);
	string getNombre(void);
	int getEdad(void);
	double getPeso(void);
	
    Persona(string nombreA, int edadA, double pesoA);
    bool operator >(Persona const& persona);

private:
	
    string nombre;
    int edad;
    double peso;
};