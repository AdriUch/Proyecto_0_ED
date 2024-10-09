/*
            Archivo: Clase Ventanilla
            Hecho por:Britany Romero

            Descripción general:Es un punto ( clase ) donde se atienden los clientes.
            Cada ventanilla tiene un código único y puede atender
            a clientes mediante un sistema de tiquetes.
            Además, registra la hora en que se brinda la atención.

            Modificación hecha por: Carmen Hidalgo Paz

            Descripción: Se detalla el funcionamiento de las comparaciones
            entre objetos.
*/


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
    Tiquete tiqueteActual;
    time_t segundos;
    tm horaAtencion;
    time_t horaEsperaTiquete;
    time_t tiempoTotalEspera;
    int contadorTiquetes;

public:
    Ventanilla() : codigoVentanilla(""), tiqueteActual() {
        // Inicializar horaAtencion a cero
        std::memset(&horaAtencion, 0, sizeof(horaAtencion));
        segundos = 0;
        horaEsperaTiquete = 0;
        contadorTiquetes = 0;
        tiempoTotalEspera = 0;
    }

    Ventanilla(const string& areaCode, int numeroVentanilla)
        : codigoVentanilla(areaCode + std::to_string(numeroVentanilla)),
        tiqueteActual() {
        std::memset(&horaAtencion, 0, sizeof(horaAtencion));
        segundos = 0;
        horaEsperaTiquete = 0;
        contadorTiquetes = 0;
        tiempoTotalEspera = 0;
    }

    bool operator ==(const Ventanilla& other) {
        return this->codigoVentanilla == other.codigoVentanilla
            && this->tiqueteActual == other.tiqueteActual
            && this->segundos == other.segundos
            && this->horaEsperaTiquete == other.horaEsperaTiquete
            && this->contadorTiquetes == other.contadorTiquetes
            && this->tiempoTotalEspera == other.tiempoTotalEspera;
    }

    string getCode() { return codigoVentanilla; }
    Tiquete getTicket() { return tiqueteActual; }
    int getContadorTiquetes() const { return contadorTiquetes; }
    time_t getTiempoTotalEspera() { return tiempoTotalEspera; }
    time_t getTimeVentanilla() { return segundos; }

    void incrementarContadorTiquetes() { contadorTiquetes++; }
    void incrementarTiempoTotalEspera() {
        tiempoTotalEspera = tiempoTotalEspera + horaEsperaTiquete;
    }
    void setContadorTiquetes(int count) { contadorTiquetes = count; }
    void setTiempoTiquete(int count) { horaEsperaTiquete = count; }
    void setTiempoTotalEspera(int count) { tiempoTotalEspera = count; }

    // atender un tiquete
    void atenderTiquete(PriorityQueue<Tiquete>& colaPrioridad) {
        if (colaPrioridad.isEmpty()) {
            throw runtime_error("No hay tiquetes en la cola de prioridad.");
        }

        // Tiquete con mayor prioridad
        Tiquete tiqueteAtendido = colaPrioridad.removeMin();
        this->tiqueteActual = tiqueteAtendido;


        time_t tiempoActual = time(0);
        tm utcTime;
        gmtime_s(&utcTime, &tiempoActual);


        const int offset_seconds = -6 * 3600; // GMT-6
        time_t gmt_minus_6 = tiempoActual + offset_seconds;


        tm gmtMinus6Time;
        gmtime_s(&gmtMinus6Time, &gmt_minus_6);

        this->segundos = tiempoActual;
        this->horaAtencion = gmtMinus6Time; // Guardar hora de atención ajustada

        // Tiquete atendido
        std::cout << "Tiquete atendido en la ventanilla: " << this->codigoVentanilla << endl;
        std::cout << "Hora de atención: " << horaAtencion.tm_hour << ":"
            << (horaAtencion.tm_min < 10 ? "0" : "") << horaAtencion.tm_min << ":"
            << (horaAtencion.tm_sec < 10 ? "0" : "") << horaAtencion.tm_sec << "\n";
    }

    void borrarTiquete() {
        this->tiqueteActual = Tiquete();
    }

    void calcularEspera(time_t horaTiquete) {
        horaEsperaTiquete = segundos - horaTiquete;
    }

    // Imprimir la ventanilla
    friend ostream& operator<<(ostream& os, const Ventanilla& ventanillaInfo) {
        os << "Ventanilla: " << ventanillaInfo.codigoVentanilla
            << " | Tiquete Actual: " << endl << ventanillaInfo.tiqueteActual;
        return os;
    }
};
