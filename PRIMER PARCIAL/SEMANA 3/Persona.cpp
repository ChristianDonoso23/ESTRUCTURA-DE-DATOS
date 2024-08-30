/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include "Persona.h"

Persona::Persona(string nombreA, int edadA, double pesoA){
	this->nombre=nombreA;
	this->edad=edadA;
	this->peso=pesoA;
}

string Persona::getNombre(void)
{
   return nombre;
}

void Persona::setNombre(string nuevoNombre)
{
   nombre = nuevoNombre;
}

int Persona::getEdad(void)
{
   return edad;
}

void Persona::setEdad(int nuevaEdad)
{
   edad = nuevaEdad;
}

double Persona::getPeso(void)
{
	return peso;
}

void Persona::setPeso(double nuevoPeso)
{
	peso=nuevoPeso;
}

bool Persona::operator >(Persona const& persona)
{
    return edad > persona.edad;
}
