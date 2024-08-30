#include "ArbolExpresion.h"
#include <stack>
#include <sstream>
#include <cmath>
#include <graphics.h>

ArbolExpresion::ArbolExpresion() : raiz(nullptr) {}

Nodo* ArbolExpresion::crearNodo(std::string valor) {
    return new Nodo(valor);
}

bool ArbolExpresion::esNumero(std::string str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

bool ArbolExpresion::esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool ArbolExpresion::esFuncion(std::string token) {
    return token == "sin" || token == "cos" || token == "tan" || token == "sqrt" || token == "exp";
}

bool ArbolExpresion::validarInfija(std::string expresion) {
    int balance = 0;
    bool prevEsOperador = true;
    std::istringstream stream(expresion);
    std::string token;

    while (stream >> token) {
        if (token == "(") {
            balance++;
            prevEsOperador = true;
        } else if (token == ")") {
            balance--;
            if (balance < 0) return false;
            prevEsOperador = false;
        } else if (esNumero(token)) {
            prevEsOperador = false;
        } else if (esFuncion(token)) {
            prevEsOperador = true;
        } else if (esOperador(token[0])) {
            if (prevEsOperador) return false;
            prevEsOperador = true;
        } else {
            return false;
        }
    }
    return balance == 0 && !prevEsOperador;
}

Nodo* ArbolExpresion::construirArbol(std::string expresion) {
    std::stack<Nodo*> operandos;
    std::stack<std::string> operadores;
    std::istringstream stream(expresion);
    std::string token;

    while (stream >> token) {
        if (esNumero(token)) {
            Nodo* nodo = crearNodo(token);
            operandos.push(nodo);
        } else if (token == "(") {
            operadores.push(token);
        } else if (token == ")") {
            while (!operadores.empty() && operadores.top() != "(") {
                std::string op = operadores.top();
                operadores.pop();
                Nodo* nodo = crearNodo(op);

                if (esFuncion(op)) {
                    nodo->izquierda = operandos.top();
                    operandos.pop();
                } else {
                    nodo->derecha = operandos.top();
                    operandos.pop();
                    nodo->izquierda = operandos.top();
                    operandos.pop();
                }

                operandos.push(nodo);
            }
            operadores.pop();
        } else if (esOperador(token[0]) || esFuncion(token)) {
            while (!operadores.empty() && precedencia(operadores.top()) >= precedencia(token)) {
                std::string op = operadores.top();
                operadores.pop();
                Nodo* nodo = crearNodo(op);

                if (esFuncion(op)) {
                    nodo->izquierda = operandos.top();
                    operandos.pop();
                } else {
                    nodo->derecha = operandos.top();
                    operandos.pop();
                    nodo->izquierda = operandos.top();
                    operandos.pop();
                }

                operandos.push(nodo);
            }
            operadores.push(token);
        }
    }

    while (!operadores.empty()) {
        std::string op = operadores.top();
        operadores.pop();
        Nodo* nodo = crearNodo(op);

        if (esFuncion(op)) {
            nodo->izquierda = operandos.top();
            operandos.pop();
        } else {
            nodo->derecha = operandos.top();
            operandos.pop();
            nodo->izquierda = operandos.top();
            operandos.pop();
        }

        operandos.push(nodo);
    }

    raiz = operandos.top();
    operandos.pop();
    return raiz;
}

int ArbolExpresion::precedencia(std::string operador) {
    if (operador == "+" || operador == "-") return 1;
    if (operador == "*" || operador == "/") return 2;
    if (operador == "^" || operador == "exp") return 3;
    if (esFuncion(operador)) return 4;
    return 0;
}

std::string ArbolExpresion::obtenerInfija(Nodo* nodo) {
    if (nodo == nullptr) return "";
    if (esFuncion(nodo->dato)) {
        return nodo->dato + "(" + obtenerInfija(nodo->izquierda) + ")";
    }
    return "(" + obtenerInfija(nodo->izquierda) + nodo->dato + obtenerInfija(nodo->derecha) + ")";
}

std::string ArbolExpresion::obtenerSufija(Nodo* nodo) {
    if (nodo == nullptr) return "";
    return obtenerSufija(nodo->izquierda) + obtenerSufija(nodo->derecha) + nodo->dato + " ";
}

std::string ArbolExpresion::obtenerPrefija(Nodo* nodo) {
    if (nodo == nullptr) return "";
    return nodo->dato + " " + obtenerPrefija(nodo->izquierda) + obtenerPrefija(nodo->derecha);
}

double ArbolExpresion::evaluarSufija(std::string sufija) {
    std::stack<double> pila;
    std::istringstream stream(sufija);
    std::string token;

    while (stream >> token) {
        if (esNumero(token)) {
            pila.push(std::stod(token));
        } else if (esOperador(token[0])) {
            double operando2 = pila.top(); pila.pop();
            double operando1 = pila.top(); pila.pop();

            switch (token[0]) {
                case '+': pila.push(operando1 + operando2); break;
                case '-': pila.push(operando1 - operando2); break;
                case '*': pila.push(operando1 * operando2); break;
                case '/': pila.push(operando1 / operando2); break;
                case '^': pila.push(pow(operando1, operando2)); break;
            }
        } else if (esFuncion(token)) {
            double operando = pila.top(); pila.pop();

            if (token == "sin") {
                pila.push(sin(operando * M_PI / 180.0));
            } else if (token == "cos") {
                pila.push(cos(operando * M_PI / 180.0));
            } else if (token == "tan") {
                pila.push(tan(operando * M_PI / 180.0));
            } else if (token == "sqrt") {
                pila.push(sqrt(operando));
            } else if (token == "exp") {
                pila.push(exp(operando));
            }
        }
    }

    return pila.top();
}

void ArbolExpresion::mostrarArbol(Nodo* nodo, int x, int y, int nivel) {
    if (nodo == nullptr) return;

    int deltaX = 50 / (nivel + 1);  // Adjust deltaX dynamically based on the level
    int deltaY = 50;
    int radio = 20;
    setcolor(WHITE);

    if (nodo->izquierda != nullptr) {
        dibujarLinea(x, y, x - deltaX, y + deltaY, radio);
        mostrarArbol(nodo->izquierda, x - deltaX, y + deltaY, nivel + 1);
    }
    if (nodo->derecha != nullptr) {
        dibujarLinea(x, y, x + deltaX, y + deltaY, radio);
        mostrarArbol(nodo->derecha, x + deltaX, y + deltaY, nivel + 1);
    }

    // Draw the current node
    circle(x, y, radio);
    outtextxy(x - 5, y - 5, const_cast<char*>(nodo->dato.c_str()));
}

void ArbolExpresion::dibujarLinea(int x1, int y1, int x2, int y2, int radio) {
    double angulo = atan2(y2 - y1, x2 - x1);
    int x1_new = x1 + radio * cos(angulo);
    int y1_new = y1 + radio * sin(angulo);
    int x2_new = x2 - radio * cos(angulo);
    int y2_new = y2 - radio * sin(angulo);
    line(x1_new, y1_new, x2_new, y2_new);
}
