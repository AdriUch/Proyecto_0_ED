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
using std::runtime_error;

class Ventanilla {
private:
    string codigoVentanilla;     
    string tiqueteActual;         
    tm horaAtencion;              

public:
    Ventanilla() : codigoVentanilla(""), tiqueteActual("N/A") {
        // Inicializar horaAtencion a cero
        std::memset(&horaAtencion, 0, sizeof(horaAtencion));
    }

    Ventanilla(const string& areaCode, int numeroVentanilla) 
        : codigoVentanilla(areaCode + std::to_string(numeroVentanilla)), 
          tiqueteActual("N/A") {
        std::memset(&horaAtencion, 0, sizeof(horaAtencion));
    }

    // atiender un tiquete
    void atenderTiquete(PriorityQueue<Tiquete>& colaPrioridad) {
        if (colaPrioridad.isEmpty()) {
            throw runtime_error("No hay tiquetes en la cola de prioridad.");
        }

        // Tiquete con mayor prioridad
        Tiquete tiqueteAtendido = colaPrioridad.removeMin();
        this->tiqueteActual = tiqueteAtendido.getCode();

   
        time_t tiempoActual = time(0);
        tm utcTime;
        gmtime_s(&utcTime, &tiempoActual);


        const int offset_seconds = -6 * 3600; // GMT-6
        time_t gmt_minus_6 = tiempoActual + offset_seconds;


        tm gmtMinus6Time;
        gmtime_s(&gmtMinus6Time, &gmt_minus_6);

        this->horaAtencion = gmtMinus6Time; // Guardar hora de atención ajustada

        // Tiquete atendido
        std::cout << "Tiquete atendido en la " << this->codigoVentanilla << ":\n";
        std::cout << tiqueteAtendido << std::endl;
        std::cout << "Hora de atención: " << horaAtencion.tm_hour << ":" 
                  << (horaAtencion.tm_min < 10 ? "0" : "") << horaAtencion.tm_min << ":" 
                  << (horaAtencion.tm_sec < 10 ? "0" : "") << horaAtencion.tm_sec << "\n";
    }

    // Imprimir la ventanilla
    friend ostream& operator<<(ostream& os, const Ventanilla& ventanillaInfo) {
        os << "Ventanilla: " << ventanillaInfo.codigoVentanilla 
           << " | Tiquete Actual: " << ventanillaInfo.tiqueteActual;
        return os;
    }
};
;
