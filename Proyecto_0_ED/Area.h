/*
            Archivo: Clase Área
            Hecho por: Adrián Ugalde

            Descripción general: Clase que contiene los atributos necesarios
            para crear un objeto llamado Área para después guardarlo
            en una lista. Se detalla el funcionamiento de
            la asignación, las comparaciones entre objetos y la impresión.

            Modificación hecha por: Carmen Hidalgo Paz

            Descripción: Se agrega un atributo contador de tiquetes y métodos
            que retornan y modifican este atributo

*/

#pragma once
#include <string>
#include <iostream>
#include "PriorityQueue.h"
#include "ArrayList.h"
#include "Tiquete.h"
#include "Ventanilla.h"

using std::ostream;
using std::string;

class Area {
private:
    string tituloArea;
    string codigo;
    int cantidadVentanillas;
    HeapPriorityQueue<Tiquete>* colaTiquetes;      // cola de tiquetes
    ArrayList<Ventanilla>* listaVentanillas;  // Lista de ventanillas
    int contadorTiquetes;

public:
    // Constructor base
    Area()
        : tituloArea(""), codigo(""), cantidadVentanillas(0),
        colaTiquetes(new HeapPriorityQueue<Tiquete>()),
        listaVentanillas(new ArrayList<Ventanilla>()),
        contadorTiquetes(0) {}

    // Constructor con par�metros 
    Area(const string& titulo, const string& codigo, int cantidadVentanillas)
        : tituloArea(titulo), codigo(codigo), cantidadVentanillas(cantidadVentanillas), contadorTiquetes(0) {
        colaTiquetes = new HeapPriorityQueue<Tiquete>();              // Usar HeapPriorityQueue para cola de tiquetes 
        listaVentanillas = new ArrayList<Ventanilla>(cantidadVentanillas);  // Usar ArrayList para lista de ventanillas 
    }

    // Destructor 
    ~Area() {
        delete colaTiquetes;
        delete listaVentanillas;
    }

    //  Constructor de copia
    Area(const Area& other)
        : tituloArea(other.tituloArea), codigo(other.codigo),
        cantidadVentanillas(other.cantidadVentanillas), contadorTiquetes(other.contadorTiquetes) {
        // Copiar nuevas listas 
        colaTiquetes = new HeapPriorityQueue<Tiquete>(*other.colaTiquetes);
        listaVentanillas = new ArrayList<Ventanilla>(*other.listaVentanillas);
    }

    bool operator ==(const Area& other) {
        return this->tituloArea == other.tituloArea && this->codigo == other.codigo
            && this->cantidadVentanillas == other.cantidadVentanillas
            && this->colaTiquetes == other.colaTiquetes
            && this->listaVentanillas == other.listaVentanillas
            && this->contadorTiquetes == other.contadorTiquetes;
    }

    // Operador de asignación. Evita problemas con los "=" de ciertas funciones
    Area& operator=(const Area& other) {
        if (this != &other) {
            tituloArea = other.tituloArea;
            codigo = other.codigo;
            cantidadVentanillas = other.cantidadVentanillas;
            contadorTiquetes = other.contadorTiquetes;

            // Limpiar colas y listas 
            if (colaTiquetes != nullptr) {
                delete colaTiquetes;
            }
            if (listaVentanillas != nullptr) {
                delete listaVentanillas;
            }

            // Copiar nuevas listas 
            colaTiquetes = new HeapPriorityQueue<Tiquete>();
            while (!other.colaTiquetes->isEmpty()) {
                colaTiquetes->insert(other.colaTiquetes->min(), other.colaTiquetes->minPriority());
                other.colaTiquetes->removeMin();
            }
            listaVentanillas = new ArrayList<Ventanilla>(*other.listaVentanillas);
        }
        return *this;
    }
    // Método para modificar la cantidad de ventanillas
    void modificarVentanillas(int nuevaCantidad) {
        this->cantidadVentanillas = nuevaCantidad;
    }

    // Getters
    string getTituloArea() const { return tituloArea; }
    string getCodigo() const { return codigo; }
    int getCantidadVentanillas() const { return cantidadVentanillas; }
    int getContadorTiquetes() const { return contadorTiquetes; }

    void incrementarContadorTiquetes() { contadorTiquetes++; }
    void setContadorTiquetes(int count) { contadorTiquetes = count; }

    // Obtiene las referencias a las listas de tiquetes y ventanillas
    PriorityQueue<Tiquete>& getColaTiquetes() const { return *colaTiquetes; }
    ArrayList<Ventanilla>& getListaVentanillas() const { return *listaVentanillas; }

    // Método para mostrar la información del área
    void mostrarInfoArea() const {
        std::cout << "Area: " << tituloArea << " | Codigo: " << codigo << " | Ventanillas: " << cantidadVentanillas << std::endl;
    }

    friend ostream& operator <<(ostream& os, const Area& areaInfo) {
        os << areaInfo.tituloArea;
        return os;
    }
};
