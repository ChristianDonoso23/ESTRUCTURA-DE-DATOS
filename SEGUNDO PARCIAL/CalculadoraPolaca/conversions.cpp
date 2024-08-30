#include "conversions.h"
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <unordered_set>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool esCaracterValido(char c) {
    return (isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || isspace(c) || isalpha(c) || c == '.');
}

bool esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool esOperador2(const std::string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

bool esOperadorUnario(char c) {
    return (c == '-');
}

int obtenerPrioridad(char C) {
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

int obtenerPrioridadFuncion(const std::string& token) {
    if (esFuncion(token))
        return 4;
    return 0;
}

bool esExpresionValida(const std::string& expresion) {
    for (char c : expresion) {
        if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '^' && c != '(' && c != ')' && !isspace(c) && !isalpha(c) && c != '.') {
            return false;
        }
    }
    return true;
}

std::string infijoASufijo(const std::string& infijo) {
    std::stack<std::string> stk;
    std::string sufijo;
    std::istringstream iss(infijo);
    std::string token;
    bool lastWasOperator = true;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            sufijo += token + ' ';
            lastWasOperator = false;
        } else if (esFuncion(token)) {
            stk.push(token);
        } else if (token == "(") {
            stk.push(token);
            lastWasOperator = true;
        } else if (token == ")") {
            while (!stk.empty() && stk.top() != "(") {
                sufijo += stk.top() + ' ';
                stk.pop();
            }
            if (!stk.empty() && stk.top() == "(") {
                stk.pop();
            }
            if (!stk.empty() && esFuncion(stk.top())) {
                sufijo += stk.top() + ' ';
                stk.pop();
            }
            lastWasOperator = false;
        } else {
            while (!stk.empty()) {
                const char* top = stk.top().c_str();
                if (obtenerPrioridad(token[0]) > obtenerPrioridad(top[0])) break;
                sufijo += stk.top() + ' ';
                stk.pop();
            }
            stk.push(token);
            lastWasOperator = true;
        }
    }

    while (!stk.empty()) {
        sufijo += stk.top() + ' ';
        stk.pop();
    }

    return sufijo;
}

std::string infijoAPrefijo(const std::string& infijo) {
    std::string rev_infix = infijo;
    std::reverse(rev_infix.begin(), rev_infix.end());
    for (char& c : rev_infix) {
        if (c == '(')
            c = ')';
        else if (c == ')')
            c = '(';
    }
    std::string rev_postfix = infijoASufijo(rev_infix);
    std::reverse(rev_postfix.begin(), rev_postfix.end());
    return rev_postfix;
}

std::string sufijoAInfijo(const std::string& sufijo) {
    std::stack<std::string> stk;
    std::istringstream iss(sufijo);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(token);
        } else if (esFuncion(token)) {
            std::string op1 = stk.top(); stk.pop();
            std::string exp = token + "(" + op1 + ")";
            stk.push(exp);
        } else {
            std::string op1 = stk.top(); stk.pop();
            std::string op2 = stk.top(); stk.pop();
            std::string exp = "(" + op2 + " " + token + " " + op1 + ")";
            stk.push(exp);
        }
    }

    return stk.top();
}

std::string sufijoAInfijoSinParentesis(const std::string& sufijo) {
    std::stack<std::string> stk;
    std::istringstream iss(sufijo);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(token);
        } else if (esFuncion(token)) {
            std::string op1 = stk.top(); stk.pop();
            std::string exp = token + "(" + op1 + ")";
            stk.push(exp);
        } else if (esOperador(token[0])) {
            std::string op1 = stk.top(); stk.pop();
            std::string op2 = stk.top(); stk.pop();
            std::string exp = op2 + " " + token + " " + op1;
            stk.push(exp);
        }
    }

    return stk.top();
}

std::string prefijoASufijo(const std::string& prefijo) {
    std::stack<std::string> stk;
    std::istringstream iss(prefijo);
    std::string token;
    std::stack<std::string> tokens;

    while (iss >> token) {
        tokens.push(token);
    }

    while (!tokens.empty()) {
        token = tokens.top();
        tokens.pop();

        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(token);
        } else if (esFuncion(token)) {
            std::string op1 = stk.top(); stk.pop();
            std::string temp = op1 + " " + token;
            stk.push(temp);
        } else {
            std::string op1 = stk.top(); stk.pop();
            std::string op2 = stk.top(); stk.pop();
            std::string temp = op1 + " " + op2 + " " + token;
            stk.push(temp);
        }
    }

    return stk.top();
}

std::string prefijoAInfijo(const std::string& prefijo) {
    std::stack<std::string> stk;
    std::istringstream iss(prefijo);
    std::string token;
    std::stack<std::string> tokens;

    while (iss >> token) {
        tokens.push(token);
    }

    while (!tokens.empty()) {
        token = tokens.top();
        tokens.pop();

        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(token);
        } else if (esFuncion(token)) {
            std::string op1 = stk.top(); stk.pop();
            std::string exp = token + "(" + op1 + ")";
            stk.push(exp);
        } else {
            std::string op1 = stk.top(); stk.pop();
            std::string op2 = stk.top(); stk.pop();
            std::string exp = "(" + op1 + " " + token + " " + op2 + ")";
            stk.push(exp);
        }
    }

    return stk.top();
}

std::string prefijoAInfijoSinParentesis(const std::string& prefijo) {
    std::stack<std::string> stk;
    std::istringstream iss(prefijo);
    std::string token;
    std::stack<std::string> tokens;

    while (iss >> token) {
        tokens.push(token);
    }

    while (!tokens.empty()) {
        token = tokens.top();
        tokens.pop();

        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(token);
        } else if (esOperador(token[0])) {
            std::string op1 = stk.top(); stk.pop();
            std::string op2 = stk.top(); stk.pop();
            std::string exp = op2 + " " + token + " " + op1;
            stk.push(exp);
        } else {
            return "";
        }
    }

    return stk.top();
}

std::string sufijoAPrefijo(const std::string& sufijo) {
    std::stack<std::string> stk;
    std::istringstream iss(sufijo);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(token);
        } else if (esFuncion(token)) {
            std::string op1 = stk.top(); stk.pop();
            std::string temp = token + " " + op1;
            stk.push(temp);
        } else {
            std::string op1 = stk.top(); stk.pop();
            std::string op2 = stk.top(); stk.pop();
            std::string temp = token + " " + op2 + " " + op1;
            stk.push(temp);
        }
    }

    return stk.top();
}

bool esFuncion(const std::string& token) {
    return (token == "sqrt" || token == "sin" || token == "cos" || token == "tan");
}

double evaluarSufijo(const std::string& sufijo) {
    std::stack<double> stk;
    std::istringstream iss(sufijo);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(std::stod(token));
        } else if (esFuncion(token)) {
            double op1 = stk.top(); stk.pop();
            if (token == "sqrt") stk.push(sqrt(op1));
            else if (token == "sin") stk.push(sin(op1));
            else if (token == "cos") stk.push(cos(op1));
            else if (token == "tan") stk.push(tan(op1));
        } else {
            if (stk.size() < 2) {
                throw std::runtime_error("Error: No hay suficientes operandos para la operación.");
            }
            double op1 = stk.top(); stk.pop();
            double op2 = stk.top(); stk.pop();
            if (token == "+") stk.push(op2 + op1);
            else if (token == "-") stk.push(op2 - op1);
            else if (token == "*") stk.push(op2 * op1);
            else if (token == "/") stk.push(op2 / op1);
            else if (token == "^") stk.push(pow(op2, op1));
        }
    }

    if (stk.size() != 1) {
        throw std::runtime_error("Error: Pila final no tiene un único valor.");
    }

    return stk.top();
}

double evaluarPrefijo(const std::string& prefijo) {
    std::stack<double> stk;
    std::istringstream iss(prefijo);
    std::string token;
    std::stack<std::string> tokens;

    while (iss >> token) {
        tokens.push(token);
    }

    while (!tokens.empty()) {
        token = tokens.top();
        tokens.pop();

        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stk.push(std::stod(token));
        } else if (esFuncion(token)) {
            double op1 = stk.top(); stk.pop();
            if (token == "sqrt") stk.push(sqrt(op1));
            else if (token == "sin") stk.push(sin(op1));
            else if (token == "cos") stk.push(cos(op1));
            else if (token == "tan") stk.push(tan(op1));
        } else {
            double op1 = stk.top(); stk.pop();
            double op2 = stk.top(); stk.pop();
            if (token == "+") stk.push(op1 + op2);
            else if (token == "-") stk.push(op1 - op2);
            else if (token == "*") stk.push(op1 * op2);
            else if (token == "/") stk.push(op1 / op2);
            else if (token == "^") stk.push(pow(op1, op2));
        }
    }

    if (stk.size() != 1) {
        throw std::runtime_error("Error: Pila final no tiene un único valor.");
    }

    return stk.top();
}

bool balanceParentesis(const std::string& expresion) {
    std::stack<char> stk;
    for (char c : expresion) {
        if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            if (stk.empty() || stk.top() != '(') {
                return false;
            }
            stk.pop();
        }
    }
    return stk.empty();
}

bool esInfijoValido(const std::string& infijo) {
    std::istringstream iss(infijo);
    std::string token;
    bool lastWasOperator = true;

    while (iss >> token) {
        if (std::isdigit(token[0]) || std::isalpha(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            lastWasOperator = false;
        } else if (esOperador(token[0])) {
            if (lastWasOperator && token[0] != '-') return false;
            lastWasOperator = true;
        } else if (token == "(" || token == ")") {
            // No changes needed for parentheses
        } else {
            return false;
        }
    }
    return !lastWasOperator;
}

bool esSufijoValido(const std::string& sufijo) {
    std::istringstream iss(sufijo);
    std::string token;
    int operandos = 0;

    while (iss >> token) {
        if (std::isdigit(token[0]) || std::isalpha(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            operandos++;
        } else if (esOperador(token[0]) || esFuncion(token)) {
            if (operandos < 2) return false;
            operandos--;
        } else {
            return false;
        }
    }
    return operandos == 1;
}

bool esPrefijoValido(const std::string& prefijo) {
    std::istringstream iss(prefijo);
    std::string token;
    int operandos = 0;
    std::stack<std::string> tokens;

    while (iss >> token) {
        tokens.push(token);
    }

    while (!tokens.empty()) {
        token = tokens.top();
        tokens.pop();
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            operandos++;
        } else if (esOperador(token[0]) || esFuncion(token)) {
            if (operandos < 2) return false;
            operandos--;
        } else {
            return false;
        }
    }
    return operandos == 1;
}

bool validarExpresion(const std::string& expresion, const std::string& tipo) {
    if (!esExpresionValida(expresion)) return false;
    if (tipo == "infijo") {
        return esInfijoValido(expresion);
    } else if (tipo == "sufijo") {
        return esSufijoValido(expresion);
    } else if (tipo == "prefijo") {
        return esPrefijoValido(expresion);
    } else {
        throw std::invalid_argument("Tipo de notación no soportado");
    }
}

std::string cambiarOperadores(const std::string& expresion) {
    std::string nuevaExpresion;
    bool ultimoFueOperador = true;
    const char* p = expresion.c_str();
    const char* end = p + expresion.size();

    while (p != end) {
        char c = *p;

        if (c == ' ') {
            nuevaExpresion += c;
            ++p;
            continue;
        }

        if (std::isdigit(c) || (c == '-' && (p == expresion.c_str() || esOperador(*(p - 1)) || *(p - 1) == '('))) {
            nuevaExpresion += c;
            ultimoFueOperador = false;
        } else if (esOperador(c)) {
            if (ultimoFueOperador && c == '-') {
                nuevaExpresion += '-';
            } else {
                switch (c) {
                    case '+': nuevaExpresion += '*'; break;
                    case '-': nuevaExpresion += '/'; break;
                    case '*': nuevaExpresion += '+'; break;
                    case '/': nuevaExpresion += '-'; break;
                }
            }
            ultimoFueOperador = true;
        } else {
            nuevaExpresion += c;
            ultimoFueOperador = false;
        }
        ++p;
    }
    return nuevaExpresion;
}
