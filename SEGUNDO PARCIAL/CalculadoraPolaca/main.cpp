#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "conversions.cpp"

enum OpcionMenu {
    INFIX_TO_POSTFIX_AND_PREFIX,
    POSTFIX_TO_INFIX,
    PREFIX_TO_POSTFIX,
    POSTFIX_TO_PREFIX,
    PREFIX_TO_INFIX,
    CAMBIAR_OPERADORES,
    EXIT,
    MENU_OPTIONS_COUNT
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    std::string opcionesMenu[MENU_OPTIONS_COUNT] = {
        "Convertir infijo a sufijo y prefijo",
        "Convertir sufijo a infijo",
        "Convertir prefijo a sufijo",
        "Convertir sufijo a prefijo",
        "Convertir prefijo a infijo",
        "Cambiar operadores de una expresion",
        "Salir"
    };

    std::cout << "Seleccione una opcion:\n";
    for (int i = 0; i < MENU_OPTIONS_COUNT; ++i) {
        if (i == opcionSeleccionada) {
            std::cout << "-> " << opcionesMenu[i] << "\n";
        } else {
            std::cout << "   " << opcionesMenu[i] << "\n";
        }
    }
}

int main() {
    std::string expresion;
    int opcionSeleccionada = 0;
    int tecla;

    do {
        mostrarMenu(opcionSeleccionada);

        tecla = _getch();
        switch (tecla) {
        case 72: // Flecha arriba
            if (opcionSeleccionada > 0) {
                --opcionSeleccionada;
            }
            break;
        case 80: // Flecha abajo
            if (opcionSeleccionada < MENU_OPTIONS_COUNT - 1) {
                ++opcionSeleccionada;
            }
            break;
        case 13: // Enter
            system("cls");
            try {
                switch (opcionSeleccionada) {
                case INFIX_TO_POSTFIX_AND_PREFIX: {
                    std::cout << "Ingrese la expresion infija: ";
                    std::getline(std::cin, expresion);

                    if (validarExpresion(expresion, "infijo")) {
                        std::string sufijo = infijoASufijo(expresion);
                        std::string prefijo = infijoAPrefijo(expresion);
                        double resultado = evaluarSufijo(sufijo);

                        std::cout << "Expresion infija: " << expresion << "\n";
                        std::cout << "Conversion a sufijo: " << sufijo << "\n";
                        std::cout << "Conversion a prefijo: " << prefijo << "\n";
                        std::cout << "Resultado: " << resultado << "\n";
                    } else {
                        std::cout << "Entrada invalida. Por favor, ingrese solo numeros y operadores validos.\n";
                    }
                    break;
                }
                case POSTFIX_TO_INFIX: {
                    std::cout << "Ingrese la expresion sufija: ";
                    std::getline(std::cin, expresion);

                    if (validarExpresion(expresion, "sufijo")) {
                        std::string infijo = sufijoAInfijo(expresion);
                        double resultado = evaluarSufijo(expresion);

                        std::cout << "Conversion a infijo: " << infijo << "\n";
                        std::cout << "Resultado: " << resultado << "\n";
                    } else {
                        std::cout << "Entrada invalida. Por favor, ingrese una expresion sufija valida.\n";
                    }
                    break;
                }
                case PREFIX_TO_POSTFIX: {
                    std::cout << "Ingrese la expresion prefija: ";
                    std::getline(std::cin, expresion);

                    if (validarExpresion(expresion, "prefijo")) {
                        std::string sufijo = prefijoASufijo(expresion);
                        double resultado = evaluarSufijo(sufijo);

                        std::cout << "Conversion a sufijo: " << sufijo << "\n";
                        std::cout << "Resultado: " << resultado << "\n";
                    } else {
                        std::cout << "Entrada invalida. Por favor, ingrese una expresion prefija valida.\n";
                    }
                    break;
                }
                case POSTFIX_TO_PREFIX: {
                    std::cout << "Ingrese la expresion sufija: ";
                    std::getline(std::cin, expresion);

                    if (validarExpresion(expresion, "sufijo")) {
                        std::string prefijo = sufijoAPrefijo(expresion);
                        double resultado = evaluarSufijo(expresion);

                        std::cout << "Conversion a prefijo: " << prefijo << "\n";
                        std::cout << "Resultado: " << resultado << "\n";
                    } else {
                        std::cout << "Entrada invalida. Por favor, ingrese una expresion sufija valida.\n";
                    }
                    break;
                }
                case PREFIX_TO_INFIX: {
                    std::cout << "Ingrese la expresion prefija: ";
                    std::getline(std::cin, expresion);

                    if (validarExpresion(expresion, "prefijo")) {
                        std::string infijo = prefijoAInfijo(expresion);
                        std::string sufijo = prefijoASufijo(expresion);
                        double resultado = evaluarSufijo(sufijo);

                        std::cout << "Conversion a infijo: " << infijo << "\n";
                        std::cout << "Resultado: " << resultado << "\n";
                    } else {
                        std::cout << "Entrada invalida. Por favor, ingrese una expresion prefija valida.\n";
                    }
                    break;
                }
                case CAMBIAR_OPERADORES: {
                    std::cout << "Ingrese la expresion: ";
                    std::getline(std::cin, expresion);
                    if (esPrefijoValido(expresion)) {
                        std::string infija = prefijoAInfijoSinParentesis(expresion);
                        std::string convertido = cambiarOperadores(infija);
                        std::string sufijo = infijoASufijo(convertido);
                        double resultadoConvertido = evaluarSufijo(sufijo);
                        std::cout << "Operadores cambiados: " << sufijo << "\n";
                        std::cout << "Resultado convertido: " << resultadoConvertido << "\n";
                    } else if (esSufijoValido(expresion)) {
                        std::string infija = sufijoAInfijoSinParentesis(expresion);
                        std::string convertido = cambiarOperadores(infija);
                        std::string sufijo = infijoASufijo(convertido);
                        double resultadoConvertido = evaluarSufijo(sufijo);
                        std::cout << "Operadores cambiados: " << sufijo << "\n";
                        std::cout << "Resultado convertido: " << resultadoConvertido << "\n";
                    } else if (esInfijoValido(expresion)) {
                        std::string convertido = cambiarOperadores(expresion);
                        std::string sufijo = infijoASufijo(convertido);
                        double resultadoConvertido = evaluarSufijo(sufijo);
                        std::cout << "Operadores cambiados: " << sufijo << "\n";
                        std::cout << "Resultado convertido: " << resultadoConvertido << "\n";
                    } else {
                        std::cout << "Entrada invalida. Por favor, ingrese solo numeros y operadores validos.\n";
                    }
                    break;
                }
                case EXIT:
                    std::cout << "Saliendo...\n";
                    break;
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            std::cout << "Presione cualquier tecla para continuar...";
            _getch();
            break;
        }
    } while (opcionSeleccionada != EXIT || tecla != 13);

    return 0;
}
