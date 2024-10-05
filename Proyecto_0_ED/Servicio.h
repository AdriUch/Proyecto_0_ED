/*
            Archivo: Clase Servicio
            Hecho por:

            Descripción general:

            Modificación hecha por: Carmen Hidalgo Paz

            Descripción: Se detalla el funcionamiento de las comparaciones
            entre objetos Se agregó el atributo contadorTiquetes y se actualizaron
            los métodos para que se tomara en cuenta.
*/

//Britany trabajo aqui a muy altas horas de la noche
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
    int contadorTiquetes;

public:
   
    Servicio() : descripcion(""), prioridadServicio(0), areaCode(""), contadorTiquetes(0) {}

    // Constructor con parámetros
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
void reordenarServicios(List<Servicio>* serviceList) {
    int n = serviceList->getSize();
    bool swapped;

    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            serviceList->goToPos(i);
            Servicio current = serviceList->getElement();
            serviceList->goToPos(i + 1);
            Servicio next = serviceList->getElement();

            // Comparar por prioridad
            if (current.getPrioridadServicio() > next.getPrioridadServicio()) {
                // Intercambiar servicios
                serviceList->goToPos(i);
                serviceList->remove();
                serviceList->insert(next);
                serviceList->goToPos(i + 1);
                serviceList->remove();
                serviceList->insert(current);
                swapped = true;
            }
        }
        n--;
    } while (swapped);
}
