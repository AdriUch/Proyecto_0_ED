/*
            Archivo: Clase Área
            Hecho por: Adrián Ugalde

            Descripción general:Clase que contiene los atributos necesarios
			para crear un objeto llamado Area para después guardarlo
			en una lista. Se detalla el funcionamiento de
			la asignación, las comparaciones entre objetos y la impresión.

            Modificación hecha por: Carmen Hidalgo Paz

            Descripción: Se detalla el funcionamiento de las comparaciones
            entre objetos y de la impresión de los datos.

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
    PriorityQueue<Tiquete>* colaTiquetes;      // Lista de tiquetes
    ArrayList<Ventanilla>* listaVentanillas;  // Lista de ventanillas

public:
    // Constructor base
    Area()
        : tituloArea(""), codigo(""), cantidadVentanillas(0),
        colaTiquetes(new HeapPriorityQueue<Tiquete>()),
        listaVentanillas(new ArrayList<Ventanilla>()) {}

    // Constructor con par�metros 
    Area(const string& titulo, const string& codigo, int cantidadVentanillas)
        : tituloArea(titulo), codigo(codigo), cantidadVentanillas(cantidadVentanillas) {
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
        : tituloArea(other.tituloArea), codigo(other.codigo), cantidadVentanillas(other.cantidadVentanillas) {
        // Copiar nuevas listas 
        colaTiquetes = new HeapPriorityQueue<Tiquete>();
        while (!other.colaTiquetes->isEmpty()) {
            colaTiquetes->insert(other.colaTiquetes->min(), other.colaTiquetes->minPriority());
            other.colaTiquetes->removeMin();
        }
        listaVentanillas = new ArrayList<Ventanilla>(*other.listaVentanillas);  // Deep copy of listaVentanillas 
    }

    bool operator ==(const Area& other) {
        return this->tituloArea == other.tituloArea && this->codigo == other.codigo
            && this->cantidadVentanillas == other.cantidadVentanillas
            && this->colaTiquetes == other.colaTiquetes
            && this->listaVentanillas == other.listaVentanillas;
    }

    // Operador de asignación. Evita problemas con los "=" de ciertas funciones
    Area& operator=(const Area& other) {
        if (this != &other) {
            tituloArea = other.tituloArea;
            codigo = other.codigo;
            cantidadVentanillas = other.cantidadVentanillas;

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

    // Método para agregar o modificar un área
    void agregarArea(const string& titulo, const string& codigo, int cantidadVentanillas, int maxTiquetes, int maxVentanillas) {
        this->tituloArea = titulo;
        this->codigo = codigo;
        this->cantidadVentanillas = cantidadVentanillas;

        // Eliminar listas actuales y crear nuevas
        delete colaTiquetes;
        colaTiquetes = new HeapPriorityQueue<Tiquete>();

        delete listaVentanillas;
        listaVentanillas = new ArrayList<Ventanilla>(maxVentanillas);
    }

    // Método para modificar la cantidad de ventanillas
    void modificarVentanillas(int nuevaCantidad) {
        this->cantidadVentanillas = nuevaCantidad;
    }

    // Método estático para eliminar un área de un arreglo de áreas
    static void eliminarArea(Area* areas, int& totalAreas, int posicionArea) {
        if (posicionArea < 0 || posicionArea >= totalAreas) {
            throw std::out_of_range("Posición fuera de rango.");
        }

        // Obtener el área a eliminar
        Area& areaEliminar = areas[posicionArea];
        cout << "Área seleccionada para eliminar: " << areaEliminar.getTituloArea() << " (Código: " << areaEliminar.getCodigo() << ")\n";

        // 1. Mostrar los tiquetes asociados a esta área
        std::cout << "Tiquetes relacionados al área que se eliminarán:\n";
        for (int i = 0; i < areaEliminar.getColaTiquetes().getSize(); ++i) {
            cout << " - Tiquete ID: " << areaEliminar.getColaTiquetes().min() << "\n";
        }

        // 2. Confirmación del usuario antes de eliminar
        std::cout << "¿Deseas eliminar el área y sus elementos relacionados? (S/N): ";
        char confirmacion;
        std::cin >> confirmacion;
        if (confirmacion != 'S' && confirmacion != 's') {
            cout << "Operación cancelada.\n";
            return;
        }

        // 3. Eliminar los tiquetes asociados a esta área
        cout << "Eliminando tiquetes relacionados al área...\n";
        while (areaEliminar.getColaTiquetes().getSize() > 0) {
            areaEliminar.getColaTiquetes().removeMin();  // Remueve cada tiquete desde la posición 0
        }

        // 4. Eliminar las ventanillas relacionadas a esta área
        cout << "Eliminando ventanillas relacionadas al área...\n";
        while (areaEliminar.getListaVentanillas().getSize() > 0) {
            areaEliminar.getListaVentanillas().remove();  // Remueve cada ventanilla desde la posición 0
        }

        // 5. Eliminar el área de la lista de áreas
        for (int i = posicionArea; i < totalAreas - 1; ++i) {
            areas[i] = areas[i + 1];  // Desplaza las áreas para eliminar la seleccionada
        }
        totalAreas--;

        cout << "Área eliminada con éxito.\n";
    }

    // Getters
    string getTituloArea() const { return tituloArea; }
    string getCodigo() const { return codigo; }
    int getCantidadVentanillas() const { return cantidadVentanillas; }

    // Obtiene las referencias a las listas de tiquetes y ventanillas
    PriorityQueue<Tiquete>& getColaTiquetes() const { return *colaTiquetes; }
    ArrayList<Ventanilla>& getListaVentanillas() const { return *listaVentanillas; }

    // Método para mostrar la información del área
    void mostrarInfoArea() const {
        std::cout << "Area: " << tituloArea << " | Codigo: " << codigo << " | Ventanillas: " << cantidadVentanillas << std::endl;
    }

    friend ostream& operator <<(ostream& os, const Area& areaInfo) {
        os << "Area: " << areaInfo.tituloArea << " | Codigo: "
            << areaInfo.codigo << " | Ventanillas: "
            << areaInfo.cantidadVentanillas << std::endl;
        return os;
    }
};
