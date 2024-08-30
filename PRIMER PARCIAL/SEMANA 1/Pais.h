/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase pais
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 6 de mayo de 2024
 * Fecha modificacion: viernes, 10 de mayo de 2024 
 ***********************************************************************/
#if !defined(__Class_Diagram_1_Pais_h)
#define __Class_Diagram_1_Pais_h

class Persona;

class Pais
{
public:
   Persona** persona;

protected:
private:
   int Id_pais;
   std::string nombre;
   std::string observacion;


};

#endif