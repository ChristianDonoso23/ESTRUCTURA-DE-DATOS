/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase persona
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: martes, 14 de mayo de 2024
 * Fecha modificacion: martes, 14 de mayo de 2024 
 ***********************************************************************/
#if !defined(__Class_Diagram_1_Persona_h)
#define __Class_Diagram_1_Persona_h

#include <Pais.h>
#include <Fecha.h>

class Persona
{
public:
protected:
private:
   std::string numeroCedula;
   std::string apellidos;
   std::string nombres;
   Pais pais;
   Fecha fecha;
   enum sexo;
   Fecha fechaV;
   enum estadoCivil;
   std::string dactilar;
   enum tipoSangre;
   bool donante;


};

#endif