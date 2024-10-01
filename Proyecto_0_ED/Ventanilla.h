#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

class Ventanilla {
public:
    string codigoVentanilla;
    string tiqueteActual; // Código del tiquete que se está atendiendo actualmente

    Ventanilla() {}
    Ventanilla(string areaCode, int numeroVentanilla) {
        this->codigoVentanilla = areaCode + std::to_string(numeroVentanilla);
        this->tiqueteActual = "N/A"; // No hay tiquete al iniciar
    }

    void atenderTiquete(string tiqueteCode) {
        this->tiqueteActual = tiqueteCode;
    }

    void operator =(const Ventanilla& other) {
        this->codigoVentanilla = other.codigoVentanilla;
        this->tiqueteActual = other.tiqueteActual;
    }
};

ostream& operator <<(ostream& os, const Ventanilla& ventanillaInfo) {
    os << "Ventanilla: " << ventanillaInfo.codigoVentanilla 
       << " | Tiquete Actual: " << ventanillaInfo.tiqueteActual;
    return os;
}
