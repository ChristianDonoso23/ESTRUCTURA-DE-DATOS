#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include <string>
    bool esCaracterValido(char c);
    bool esOperador(char c);
    int obtenerPrioridad(char C);
    bool esOperador2 (const std::string& token);
    std::string infijoASufijo(const std::string& infijo);
    std::string infijoAPrefijo(const std::string& infijo);
    std::string sufijoAInfijo(const std::string& sufijo);
    std::string prefijoASufijo(const std::string& prefijo);
    std::string sufijoAPrefijo(const std::string& sufijo);
    std::string prefijoAInfijo(const std::string& prefijo);
    bool esFuncion(const std::string& token);
    int obtenerPrioridadFuncion(const std::string& token);
    bool esExpresionValida(const std::string& expresion);
    double evaluarSufijo(const std::string& sufijo);
    bool validarExpresion(const std::string& expresion, const std::string& tipo);
    bool esPrefijoValido(const std::string& prefijo);
    bool esSufijoValido(const std::string& sufijo);
    bool esInfijoValido(const std::string& infijo);
    bool balanceParentesis(const std::string& expresion);
    std::string cambiarOperadores(const std::string& expresion);
    std::string sufijoAInfijoSinParentesis(const std::string& sufijo);
    std::string prefijoAInfijoSinParentesis(const std::string& prefijo);
#endif
