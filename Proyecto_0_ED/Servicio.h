/*
            Archivo: Clase Servicio
            Hecho por:

            Descripción general:

            Modificación hecha por: Carmen Hidalgo Paz

            Descripción: Se detalla el funcionamiento de las comparaciones
            entre objetos Se agregó el atributo contadorTiquetes y se actualizaron
            los métodos para que se tomara en cuenta.
*/


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

    Servicio(const string& descripcion, int prioridadServicio, const string& areaCode)
        : descripcion(descripcion), prioridadServicio(prioridadServicio),
        areaCode(areaCode){ contadorTiquetes = 0; }
    
    bool operator ==(const Servicio& other) {
        return this->descripcion == other.descripcion && this->prioridadServicio == other.prioridadServicio
               && this->areaCode == other.areaCode && this->contadorTiquetes == other.contadorTiquetes;
    }


    string getDescripcion() const { return descripcion; }
    int getPrioridadServicio() const { return prioridadServicio; }
    string getAreaCode() const { return areaCode; }
    int getContadorTiquetes() const { return contadorTiquetes; }


    void setDescripcion(const string& desc) { descripcion = desc; }
    void setPrioridadServicio(int prioridad) { prioridadServicio = prioridad; }
    void setAreaCode(const string& area) { areaCode = area; }
    void setTicketCounter() { contadorTiquetes = contadorTiquetes + 1; }

  
    friend ostream& operator <<(ostream& os, const Servicio& servicioInfo) {
        os << servicioInfo.descripcion;
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

            // Comparar por prioridad o cualquier otro criterio
            if (current.getPriority() > next.getPriority()) {
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

