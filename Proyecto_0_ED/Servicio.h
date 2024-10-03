#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

class Servicio {
private:
    string descripcion;
    int prioridadServicio;
    string areaCode;

public:

    Servicio() : descripcion(""), prioridadServicio(0), areaCode("") {}

    Servicio(const string& descripcion, int prioridadServicio, const string& areaCode)
        : descripcion(descripcion), prioridadServicio(prioridadServicio), areaCode(areaCode) {}


    string getDescripcion() const { return descripcion; }
    int getPrioridadServicio() const { return prioridadServicio; }
    string getAreaCode() const { return areaCode; }


    void setDescripcion(const string& desc) { descripcion = desc; }
    void setPrioridadServicio(int prioridad) { prioridadServicio = prioridad; }
    void setAreaCode(const string& area) { areaCode = area; }

  
    friend ostream& operator<<(ostream& os, const Servicio& servicioInfo) {
        os << "Servicio: " << servicioInfo.descripcion 
           << " | Prioridad: " << servicioInfo.prioridadServicio 
           << " | Área: " << servicioInfo.areaCode;
        return os;
    }
};

