#include <iostream>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <cmath>

struct Fecha {
    int dia;
    int mes;
    int anio;
};

// Función para determinar si un año es bisiesto
bool esBisiesto(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Función para calcular el Domingo de Pascua (algoritmo de Gauss)
Fecha calcularPascua(int anio) {
    int a = anio % 19;
    int b = anio / 100;
    int c = anio % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int mes = (h + l - 7 * m + 114) / 31;
    int dia = ((h + l - 7 * m + 114) % 31) + 1;

    return {dia, mes, anio};
}

// Función para determinar si una fecha es feriado en Ecuador
bool esFeriado(int dia, int mes, int anio) {
    // Feriados fijos
    if ((dia == 1 && mes == 1) ||  // Año Nuevo
        (dia == 1 && mes == 5) ||  // Día del Trabajo
        (dia == 24 && mes == 5) || // Batalla de Pichincha
        (dia == 10 && mes == 8) || // Primer Grito de Independencia
        (dia == 9 && mes == 10) || // Independencia de Guayaquil
        (dia == 2 && mes == 11) || // Día de los Difuntos
        (dia == 3 && mes == 11) || // Independencia de Cuenca
        (dia == 24 && mes == 12) || // Nochebuena
        (dia == 25 && mes == 12)    // Navidad
    ) {
        return true;
    }

    // Cálculo del Domingo de Pascua
    Fecha pascua = calcularPascua(anio);

    // Viernes Santo (2 días antes del Domingo de Pascua)
    tm viernesSanto = {};
    viernesSanto.tm_mday = pascua.dia - 2;
    viernesSanto.tm_mon = pascua.mes - 1; // Los meses en tm_struct son 0-11
    viernesSanto.tm_year = anio - 1900;
    mktime(&viernesSanto);

    if (dia == viernesSanto.tm_mday && mes == viernesSanto.tm_mon + 1) {
        return true;
    }

    // Lunes y Martes de Carnaval (48 y 47 días antes del Domingo de Pascua)
    tm lunesCarnaval = viernesSanto;
    lunesCarnaval.tm_mday -= 39;  // 48 días antes del Domingo de Pascua
    mktime(&lunesCarnaval);

    tm martesCarnaval = lunesCarnaval;
    martesCarnaval.tm_mday += 1;  // 47 días antes del Domingo de Pascua
    mktime(&martesCarnaval);

    if ((dia == lunesCarnaval.tm_mday && mes == lunesCarnaval.tm_mon + 1) ||
        (dia == martesCarnaval.tm_mday && mes == martesCarnaval.tm_mon + 1)) {
        return true;
    }

    return false;
}

// Función para obtener el máximo de días en un mes específico
int obtenerMaximoDias(int mes, int anio) {
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    } else if (mes == 2) {
        return esBisiesto(anio) ? 29 : 28;
    }
    return 31;
}

// Función para ajustar la fecha al próximo día laboral si cae en fin de semana o feriado
Fecha ajustarFechaLaboral(int dia, int mes, int anio) {
    int maxDias = obtenerMaximoDias(mes, anio);
    if (dia > maxDias) {
        dia = maxDias;  // Ajustar al último día del mes si la fecha no existe
    }

    tm fecha = {};
    fecha.tm_mday = dia;
    fecha.tm_mon = mes - 1; // Los meses en tm_struct son 0-11
    fecha.tm_year = anio - 1900;
    mktime(&fecha);

    // Ajusta la fecha si cae en sábado (6), domingo (0), o feriado
    while (fecha.tm_wday == 0 || fecha.tm_wday == 6 || esFeriado(fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900)) {
        fecha.tm_mday++;
        mktime(&fecha);
    }

    return {fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900};
}

// Función para obtener la fecha actual del sistema
Fecha obtenerFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return {now->tm_mday, now->tm_mon + 1, now->tm_year + 1900};  // tm_mon es 0-11, por eso se suma 1
}

// Función para ingresar solo números desde la consola
int obtenerNumero(const std::string& mensaje) {
    std::string entrada;
    char tecla;
    
    std::cout << mensaje;
    while (true) {
        tecla = _getch();

        if (tecla == 13 && !entrada.empty()) { // Enter key y solo si no está vacío
            std::cout << std::endl;
            return std::stoi(entrada); // Retorna el número convertido de la cadena
        }
        
        if (isdigit(tecla)) { // Solo acepta dígitos
            entrada += tecla;
            std::cout << tecla; // Muestra el número en la pantalla
        } else if (tecla == 8 && !entrada.empty()) { // Backspace key
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el último caracter mostrado en la consola
        }
    }
}

int main() {
    char continuar;
    do {
        double valorPrestamo;
        int meses;
        valorPrestamo = obtenerNumero("Ingrese el valor del prestamo: ");

        meses = obtenerNumero("Ingrese el número de meses para pagar el prestamo: ");
        
        int diaInicio, mesInicio, anioInicio;
        Fecha fechaActual = obtenerFechaActual();

        // Validación del año
        do {
            anioInicio = obtenerNumero("Ingrese el año de inicio del prestamo: ");
            if (anioInicio < fechaActual.anio) {
                std::cout << "Año incorrecto. Ingrese un valor mayor o igual al año actual (" << fechaActual.anio << ")." << std::endl;
            }
        } while (anioInicio < fechaActual.anio);

        // Validación del mes
        do {
            mesInicio = obtenerNumero("Ingrese el mes de inicio del prestamo: ");
            if (anioInicio == fechaActual.anio && mesInicio < fechaActual.mes) {
                std::cout << "Mes incorrecto. Ingrese un valor mayor o igual al mes actual (" << fechaActual.mes << ")." << std::endl;
            } else if (mesInicio < 1 || mesInicio > 12) {
                std::cout << "Mes incorrecto. Ingrese un valor entre 1 y 12." << std::endl;
            }
        } while ((anioInicio == fechaActual.anio && mesInicio < fechaActual.mes) || mesInicio < 1 || mesInicio > 12);

        // Validación del día
        int maxDias = obtenerMaximoDias(mesInicio, anioInicio);
        do {
            diaInicio = obtenerNumero("Ingrese el día de inicio del prestamo: ");
            if (anioInicio == fechaActual.anio && mesInicio == fechaActual.mes && diaInicio < fechaActual.dia) {
                std::cout << "Día incorrecto. Ingrese un valor mayor o igual al día actual (" << fechaActual.dia << ")." << std::endl;
            } else if (diaInicio < 1 || diaInicio > maxDias) {
                std::cout << "Día incorrecto. Ingrese un valor entre 1 y " << maxDias << " para el mes ingresado." << std::endl;
            }
        } while ((anioInicio == fechaActual.anio && mesInicio == fechaActual.mes && diaInicio < fechaActual.dia) || diaInicio < 1 || diaInicio > maxDias);

        Fecha fechaInicio = {diaInicio, mesInicio, anioInicio};

        Fecha fechaPago = fechaInicio;

        for (int i = 1; i <= meses; ++i) {
            // Avanzar un mes
            fechaPago.mes++;
            if (fechaPago.mes > 12) {
                fechaPago.mes = 1;
                fechaPago.anio++;
            }

            // Ajustar al próximo día laboral si es necesario
            fechaPago = ajustarFechaLaboral(fechaPago.dia, fechaPago.mes, fechaPago.anio);

            std::cout << "Fecha de pago " << i << ": " << std::setw(2) << fechaPago.dia << "/"
                      << std::setw(2) << fechaPago.mes << "/" << fechaPago.anio << std::endl;
        }

        std::cout << "\n¿Desea realizar otro cálculo? (s/n): ";
        continuar = _getch();
        std::cout << std::endl;

    } while (continuar == 's' || continuar == 'S');

    std::cout << "\nPrograma terminado. Presiona cualquier tecla para salir...";
    _getch();  // Espera hasta que se presione una tecla

    return 0;
}
