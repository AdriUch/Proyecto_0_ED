/*
    Archivo: Clase Servicio
    Hecho por: Britany Romero 
    Descripción general: Es basicamente un servicio que se ofrece a los clientes. 
    Cada servicio tiene una descripción, un nivel de prioridad, un código de área y un contador que rastrea cuántos tiquetes se han atendido. 
    Esta clase nos deja gestionar y comparar diferentes servicios.

    Modificación hecha por: Carmen Hidalgo Paz
    Descripción: Se detalla el funcionamiento de las comparaciones
    entre objetos. Se agregó el atributo contadorTiquetes y se actualizaron
    los métodos para que se tomara en cuenta.
*/

#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

class Servicio {
private:
    string descripcion;           // Descripción del servicio
    int prioridadServicio;       // Prioridad del servicio
    string areaCode;             // Código del área a la que pertenece
    int contadorTiquetes;        // Contador de tiquetes atendidos

public:
    // Constructor 
    Servicio() : descripcion(""), prioridadServicio(0), areaCode(""), contadorTiquetes(0) {}


    Servicio(const string& descripcion, int prioridadServicio, const string& areaCode)
        : descripcion(descripcion), prioridadServicio(prioridadServicio), areaCode(areaCode), contadorTiquetes(0) {}

 
    bool operator ==(const Servicio& other) const {
        return this->descripcion == other.descripcion && 
               this->prioridadServicio == other.prioridadServicio &&
               this->areaCode == other.areaCode && 
               this->contadorTiquetes == other.contadorTiquetes;
    }

   
    bool operator <(const Servicio& other) const {
        return this->prioridadServicio < other.prioridadServicio; // Comparación por prioridad
    }

    // Getters
    string getDescripcion() const { return descripcion; }
    int getPrioridadServicio() const { return prioridadServicio; }
    string getAreaCode() const { return areaCode; }
    int getContadorTiquetes() const { return contadorTiquetes; }

    // Setters
    void setDescripcion(const string& desc) { descripcion = desc; }
    void setPrioridadServicio(int prioridad) { prioridadServicio = prioridad; }
    void setAreaCode(const string& area) { areaCode = area; }
    void incrementarContadorTiquetes() { contadorTiquetes++; }
    void setContadorTiquetes(int count) { contadorTiquetes = count; }

    
    friend ostream& operator <<(ostream& os, const Servicio& servicioInfo) {
        os << "Descripción: " << servicioInfo.descripcion 
           << ", Prioridad: " << servicioInfo.prioridadServicio 
           << ", Área: " << servicioInfo.areaCode 
           << ", Contador de Tiquetes: " << servicioInfo.contadorTiquetes;
        return os;
    }
};
