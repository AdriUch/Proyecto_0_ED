#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Tiquete.h"
#include "PriorityQueue.h"

using std::ostream;
using std::string;
using std::time_t;
using std::time;
using std::tm;

class Ventanilla {
public:
    string codigoVentanilla;     
    string tiqueteActual;         
    tm horaAtencion;              

    Ventanilla() : tiqueteActual("N/A") {}
    
    Ventanilla(string areaCode, int numeroVentanilla) {
        this->codigoVentanilla = areaCode + std::to_string(numeroVentanilla);
        this->tiqueteActual = "N/A"; 
    }

    // Método para que la ventanilla atienda un tiquete
    void atenderTiquete(PriorityQueue<Tiquete>& colaPrioridad) {
        if (colaPrioridad.isEmpty()) {
            std::cout << "No hay tiquetes en la cola de prioridad.\n";
            return;
        }

        //  tiquete con mayor prioridad
        Tiquete tiqueteAtendido = colaPrioridad.removeMin();
        this->tiqueteActual = tiqueteAtendido.getCode();

        // hora de atención
        time_t tiempoActual = time(0);
        tm utcTime;
        gmtime_s(&utcTime, &tiempoActual);

        const int offset_seconds = -6 * 3600; //  zona horaria GMT-6
        time_t gmt_minus_6 = tiempoActual + offset_seconds;

        tm gmtMinus6Time;
        gmtime_s(&gmtMinus6Time, &gmt_minus_6);

        this->horaAtencion = gmtMinus6Time;

        // tiquete atendido
        std::cout << "Tiquete atendido en la " << this->codigoVentanilla << ":\n";
        std::cout << tiqueteAtendido << std::endl;
        std::cout << "Hora de atención: " << horaAtencion.tm_hour << ":"
                  << (horaAtencion.tm_min < 10 ? "0" : "") << horaAtencion.tm_min << ":"
                  << (horaAtencion.tm_sec < 10 ? "0" : "") << horaAtencion.tm_sec << "\n";
    }

    
    void operator =(const Ventanilla& other) {
        this->codigoVentanilla = other.codigoVentanilla;
        this->tiqueteActual = other.tiqueteActual;
        this->horaAtencion = other.horaAtencion;
    }

    //imprimir la ventanilla
    friend ostream& operator <<(ostream& os, const Ventanilla& ventanillaInfo) {
        os << "Ventanilla: " << ventanillaInfo.codigoVentanilla 
           << " | Tiquete Actual: " << ventanillaInfo.tiqueteActual;
        return os;
    }
};

