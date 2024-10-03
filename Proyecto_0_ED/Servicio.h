#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

class Servicio {
public:
    string descripcion;
    int prioridadServicio;
    string areaCode;

    Servicio() {}
    Servicio(string descripcion, int prioridadServicio, string areaCode) {
        this->descripcion = descripcion;
        this->prioridadServicio = prioridadServicio;
        this->areaCode = areaCode;
    }

    void operator =(const Servicio& other) {
        this->descripcion = other.descripcion;
        this->prioridadServicio = other.prioridadServicio;
        this->areaCode = other.areaCode;
    }
};

ostream& operator <<(ostream& os, const Servicio& servicioInfo) {
    os << "Servicio: " << servicioInfo.descripcion 
       << " | Prioridad: " << servicioInfo.prioridadServicio 
       << " | Área: " << servicioInfo.areaCode;
    return os;
}
