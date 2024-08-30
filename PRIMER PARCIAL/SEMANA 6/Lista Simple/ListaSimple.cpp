#include "ListaSimple.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <limits>
#include <sstream>
#include <functional>
using namespace std;
ListaSimple::ListaSimple() {
    primero = NULL;
    ultimo = NULL;
};
ListaSimple::~ListaSimple() {
    Nodo *actual = primero;
    while (actual != NULL) {
        Nodo *temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }
};
Nodo* ListaSimple::getPrimero() {
    return this->primero;
}
void ListaSimple::setPrimero(Nodo *primero) {
    this->primero = primero;
};
Nodo* ListaSimple::getUltimo() {
    return this->ultimo;
};
void ListaSimple::setUltimo(Nodo *ultimo) {
    this->ultimo = ultimo;
};
void ListaSimple::ingresarDato(string dato) {
    Nodo *nuevo = new Nodo();
    nuevo->setDato(dato);
    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->setSiguiente(nuevo);
        ultimo = nuevo;
    }
    cout << "Dato " << dato << " ingresado correctamente." << endl;
};
string ListaSimple::generarCorreo(string nombre) {
    int contador = 0;
    string correo = nombre + "@espe.edu.ec";
    return correoRepetido(correo, nombre, contador);
};
string ListaSimple::correoRepetido(string correo, string inicio, int contador) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(correo) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    if (encontrado) {
        do {
            contador++;
            correo = inicio + to_string(contador) + "@espe.edu.ec";
            encontrado = false;
            archivo.open("datos.txt");
            while (getline(archivo, linea)) {
                if (linea.find(correo) != string::npos) {
                    encontrado = true;
                    break;
                }
            }
            archivo.close();
        } while (encontrado);
    }
    return correo;
};
void ListaSimple::mostrarLista() {
    Nodo* actual = primero;
    while (actual) {
        cout << "Dato: " << actual->getDato() << endl;
        actual = actual->getSiguiente();
    }
};
string ListaSimple::convertirMinusculas(string cadena) {
    for (size_t i = 0; i < cadena.length(); ++i) {
        *(cadena.data() + i) = tolower(*(cadena.data() + i));
    }
    return cadena;
}
string ListaSimple::datos(string primerNombre, string segundoNombre, string apellido) {
    string cadena;
    if (!primerNombre.empty()) {
        char inicialPrimerNombre = tolower(*(primerNombre.c_str()));
        cadena += inicialPrimerNombre;
    }
    if (!segundoNombre.empty()) {
        char inicialSegundoNombre = tolower(*(segundoNombre.c_str()));
        cadena += inicialSegundoNombre;
    }
    string apellidoMinusculas = convertirMinusculas(apellido);
    cadena += apellidoMinusculas;
    return cadena;
}
void ListaSimple::disable_echo_mode(struct termios *old_attr) {
    struct termios new_attr;
    tcgetattr(STDIN_FILENO, old_attr);
    new_attr = *old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
};
void ListaSimple::restore_echo_mode(const struct termios *old_attr) {
    tcsetattr(STDIN_FILENO, TCSANOW, old_attr);
};
char* ListaSimple::ingresarNumeros(const char *msj, int max_length) {
    char *dato = (char *)malloc((max_length + 1) * sizeof(char));
    if (dato == nullptr) {
        cerr << "Error: No se pudo asignar memoria." << endl;
        return nullptr;
    }
    char c;
    int i = 0;
    struct termios old_attr;
    printf("%s", msj);
    fflush(stdout);
    disable_echo_mode(&old_attr);
    while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n') {
        if (c >= '0' && c <= '9' && i < max_length) {
            *(dato + i++) = c;
            write(STDOUT_FILENO, &c, 1);
        } else if (c == 127) {
            if (i > 0) {
                i--;
                write(STDOUT_FILENO, "\b \b", 3);
            }
        }
    }
    *(dato + i) = '\0';
    restore_echo_mode(&old_attr);
    printf("\n"); 
    int len = strlen(dato);
    if (len > 0 && *(dato + len - 1) == '\n') {
        *(dato + len - 1) = '\0';
    }
    return dato;
}
bool ListaSimple::cedulaRepetida(string cedula) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(cedula) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    return encontrado;
};
bool ListaSimple::validarCedula(const char *cedula) {
    printf("Cedula recibida: %s\n", cedula);
    int longitud = strlen(cedula);
    if (longitud != 10) {
        printf("Error: La cédula debe tener 10 dígitos.\n");
        return false;
    }
    int* digitos = (int*)malloc(9 * sizeof(int));
    if (digitos == nullptr) {
        cerr << "Error: No se pudo asignar memoria." << endl;
        return false;
    }
    const char* ptr = cedula;
    for (int i = 0; i < 9; ++i) {
        if (*(ptr + i) >= '0' && *(ptr + i) <= '9') {
            *(digitos + i) = *(ptr + i) - '0';
        } else {
            printf("\nError: La cédula debe contener solo dígitos.\n");
            free(digitos);
            return false;
        }
    }
    int* coef = (int*)malloc(9 * sizeof(int));
    if (coef == nullptr) {
        cerr << "Error: No se pudo asignar memoria." << endl;
        free(digitos);
        return false;
    }
    for (int i = 0; i < 9; ++i) {
        if (i % 2 == 0) {
            *(coef + i) = 2;
        } else {
            *(coef + i) = 1;
        }
    }
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int prod = *(digitos + i) * *(coef + i);
        if (prod > 9) prod -= 9;
        suma += prod;
    }
    int digitoVerificador = (10 - (suma % 10)) % 10;
    free(digitos);
    free(coef);
    return (*(ptr + 9) - '0') == digitoVerificador;
}
void ListaSimple::guardarDatos(string primerNombre, string segundoNombre, string apellido, string cedula) {
    ofstream archivo("datos.txt", ios::app);
    if (archivo.is_open()) {
        string correo = generarCorreo(datos(primerNombre, segundoNombre, apellido));
        char* contrasenia = generarContrasenia(primerNombre.c_str(), segundoNombre.c_str(), apellido.c_str());
        archivo << "Cedula: " << cedula << " - " << " Nombre: " << primerNombre << " " << segundoNombre << " " << apellido << " - " << "Correo: " << correo << " - " << "contrasenia:" << contrasenia << endl;
        free(contrasenia);
        archivo.close();
        cout << "Datos guardados correctamente en el archivo datos.txt" << endl;
    } else {
        cout << "Error al abrir el archivo datos.txt" << endl;
    }
}


void ListaSimple::mostrarDatos(string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
};

string ListaSimple::ingresarLetras(const char* msj) {
    string dato;
    char c;
    cout << msj;
    cout.flush();
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (true) {
        read(STDIN_FILENO, &c, 1);
        if (c == '\n') {
            if (!dato.empty()) {
                break;
            }
        } else if (c == 127) {
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            dato += c;
            cout << c;
            cout.flush();
        }
    }
    cout << "\n";
    cout.flush();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return dato;
}
string ListaSimple::validarLetras(const char* msj, bool allowEmpty) {
    string dato;
    char c;
    cout << msj;
    cout.flush();
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n') {
        if (isalpha(c) || (allowEmpty && c == '\n')) {
            dato += c;
            cout << c;
        } else if (c == 127 && !dato.empty()) {
            dato.pop_back();
            cout << "\b \b";
        }
        cout.flush();
    }
    cout << endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return dato;
}

char* ListaSimple::generarContrasenia(const char* primerNombre, const char* segundoNombre, const char* apellido) {
    if (!primerNombre || !apellido) {
        return nullptr;
    }
    int tamanioPrimerNombre = strlen(primerNombre);
    int tamanioApellido = strlen(apellido);
    if (tamanioPrimerNombre == 0 || tamanioApellido == 0) {
        return nullptr;
    }
    const char* segundoNombreReal = segundoNombre && strlen(segundoNombre) > 0 ? segundoNombre : " ";
    int lenContrasena = 3 + tamanioApellido - 1;
    char* contrasenaBase = (char*)malloc((lenContrasena + 1) * sizeof(char));
    if (!contrasenaBase) {
        cerr << "Error: No se pudo asignar memoria para la contraseña." << endl;
        return nullptr;
    }
    *contrasenaBase = *(apellido + tamanioApellido - 1);
    *(contrasenaBase + 2) = *primerNombre;
    *(contrasenaBase + 1) = *segundoNombreReal;
    for (int i = 0; i < tamanioApellido - 1; i++) {
        *(contrasenaBase + 3 + i) = *(apellido + tamanioApellido - 2 - i);
    }
    *(contrasenaBase + lenContrasena) = '\0';

    char* contrasenaCifrada = cifrarCesar(contrasenaBase, 5);  // Utilizar la función estática cifrarCesar
    free(contrasenaBase);

    string contrasenaFinal = contrasenaCifrada;
    free(contrasenaCifrada);

    // Verificar si la contraseña base ya existe en el archivo datos.txt
    ifstream archivo("datos.txt");
    string linea;
    bool encontrada = false;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("contrasenia:" + contrasenaFinal);
        if (pos != string::npos) {
            encontrada = true;
            break;
        }
    }
    archivo.close();

    // Si la contraseña base ya existe, agregar sufijo cifrado
    if (encontrada) {
        contrasenaFinal = contrasenaRepetida(contrasenaFinal);
    }

    char* resultado = (char*)malloc((contrasenaFinal.length() + 1) * sizeof(char));
    strcpy(resultado, contrasenaFinal.c_str());

    return resultado;
}

char* ListaSimple::cifrarCesar(const char* texto, int desplazamiento) {
    int longitud = strlen(texto);
    char* textoCifrado = (char*)malloc((longitud + 1) * sizeof(char));
    if (!textoCifrado) {
        return nullptr;
    }
    const char* ptrTexto = texto;
    char* ptrCifrado = textoCifrado;
    while (*ptrTexto != '\0') {
        char c = *ptrTexto;
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            *ptrCifrado = (c - base + desplazamiento) % 26 + base;
        } else if (isdigit(c)) {
            *ptrCifrado = (c - '0' + desplazamiento) % 10 + '0';
        } else {
            *ptrCifrado = c;
        }
        ptrTexto++;
        ptrCifrado++;
    }
    *ptrCifrado = '\0';
    return textoCifrado;
}

string ListaSimple::contrasenaRepetida(string contrasena) {
    ifstream archivo("datos.txt");
    string linea;
    int maxSufijo = -1;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("contrasenia:" + contrasena);
        if (pos != string::npos) {
            size_t inicio = pos + 12 + contrasena.length();
            if (inicio < linea.length() && isdigit(linea[inicio])) {
                string sufijo = linea.substr(inicio);
                for (char &c : sufijo) {
                    if (isdigit(c)) {
                        char cifraOriginal = ((c - '0' - 5 + 10) % 10) + '0'; // Decifrar el sufijo numérico
                        c = cifraOriginal;
                    }
                }
                int sufijoInt = stoi(sufijo);
                if (sufijoInt > maxSufijo) {
                    maxSufijo = sufijoInt;
                }
            }
        }
    }
    archivo.close();
    int newSufijo = maxSufijo + 1;
    stringstream ss;
    ss << newSufijo;
    string sufijoString = ss.str();
    for (char &c : sufijoString) {
        char cifraCifrada = ((c - '0' + 5) % 10) + '0'; // Cifrar el nuevo sufijo numérico
        c = cifraCifrada;
    }
    contrasena += sufijoString;

    return contrasena;
}

/*string ListaSimple::contrasenaRepetida(string contrasena, function<char*(const char*, int)> cifrar) {
    ifstream archivo("datos.txt");
    string linea;
    int maxSufijo = -1;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("contrasenia:" + contrasena);
        if (pos != string::npos) {
            size_t inicio = pos + 12 + contrasena.length();
            if (inicio < linea.length() && isdigit(linea[inicio])) {
                string sufijo = linea.substr(inicio);
                for (char &c : sufijo) {
                    if (isdigit(c)) {
                        char cifraOriginal = ((c - '0' - 5 + 10) % 10) + '0'; // Decifrar el sufijo numérico
                        c = cifraOriginal;
                    }
                }
                int sufijoInt = stoi(sufijo);
                if (sufijoInt > maxSufijo) {
                    maxSufijo = sufijoInt;
                }
            }
        }
    }
    archivo.close();
    int newSufijo = maxSufijo + 1;
    stringstream ss;
    ss << newSufijo;
    string sufijoString = ss.str();
    for (char &c : sufijoString) {
        char cifraCifrada = ((c - '0' + 5) % 10) + '0'; // Cifrar el nuevo sufijo numérico
        c = cifraCifrada;
    }
    contrasena += sufijoString;

    return contrasena;
}*/
/*char* ListaSimple::generarContrasenia(const char* primerNombre, const char* segundoNombre, const char* apellido) {
    if (!primerNombre || !apellido) {
        return nullptr;
    }
    int tamanioPrimerNombre = strlen(primerNombre);
    int tamanioApellido = strlen(apellido);
    if (tamanioPrimerNombre == 0 || tamanioApellido == 0) {
        return nullptr;
    }
    const char* segundoNombreReal = segundoNombre && strlen(segundoNombre) > 0 ? segundoNombre : " ";
    int lenContrasena = 3 + tamanioApellido - 1;
    char* contrasenaBase = (char*)malloc((lenContrasena + 1) * sizeof(char));
    if (!contrasenaBase) {
        cerr << "Error: No se pudo asignar memoria para la contraseña." << endl;
        return nullptr;
    }
    *contrasenaBase = *(apellido + tamanioApellido - 1);
    *(contrasenaBase + 2) = *primerNombre;
    *(contrasenaBase + 1) = *segundoNombreReal;
    for (int i = 0; i < tamanioApellido - 1; i++) {
        *(contrasenaBase + 3 + i) = *(apellido + tamanioApellido - 2 - i);
    }
    *(contrasenaBase + lenContrasena) = '\0';

    auto cifrarCesar = [](const char* texto, int desplazamiento) -> char* {
        int longitud = strlen(texto);
        char* textoCifrado = (char*)malloc((longitud + 1) * sizeof(char));
        if (!textoCifrado) {
            return nullptr;
        }
        const char* ptrTexto = texto;
        char* ptrCifrado = textoCifrado;
        while (*ptrTexto != '\0') {
            char c = *ptrTexto;
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                *ptrCifrado = (c - base + desplazamiento) % 26 + base;
            } else if (isdigit(c)) {
                *ptrCifrado = (c - '0' + desplazamiento) % 10 + '0';
            } else {
                *ptrCifrado = c;
            }
            ptrTexto++;
            ptrCifrado++;
        }
        *ptrCifrado = '\0';
        return textoCifrado;
    };

    char* contrasenaCifrada = cifrarCesar(contrasenaBase, 5);  // Usar un desplazamiento fijo de 5
    free(contrasenaBase);

    string contrasenaFinal = contrasenaCifrada;
    free(contrasenaCifrada);

    // Verificar si la contraseña base ya existe en el archivo datos.txt
    ifstream archivo("datos.txt");
    string linea;
    bool encontrada = false;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("contrasenia:" + contrasenaFinal);
        if (pos != string::npos) {
            encontrada = true;
            break;
        }
    }
    archivo.close();

    // Si la contraseña base ya existe, agregar sufijo cifrado
    if (encontrada) {
        contrasenaFinal = contrasenaRepetida(contrasenaFinal, cifrarCesar);
    }

    char* resultado = (char*)malloc((contrasenaFinal.length() + 1) * sizeof(char));
    strcpy(resultado, contrasenaFinal.c_str());

    return resultado;
}*/
