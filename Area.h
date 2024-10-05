/*
            Archivo: Clase �rea
            Hecho por: Adri�n Ugalde

            Descripci�n general:Clase que contiene los atributos necesarios
			para crear un objeto llamado Area para despu�s guardarlo
			en una lista. Se detalla el funcionamiento de
			la asignaci�n, las comparaciones entre objetos y la impresi�n.

            Modificaci�n hecha por: Carmen Hidalgo Paz

            Descripci�n: Se detalla el funcionamiento de las comparaciones
            entre objetos y de la impresi�n de los datos.

*/

#pragma once
#include <string>
#include <iostream>
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
    ArrayList<Tiquete>* listaTiquetes;      // Lista de tiquetes
    ArrayList<Ventanilla>* listaVentanillas;  // Lista de ventanillas

public:
    // Constructor base
    Area()
        : tituloArea(""), codigo(""), cantidadVentanillas(0),
        listaTiquetes(new ArrayList<Tiquete>()),
        listaVentanillas(new ArrayList<Ventanilla>()) {}

    // Constructor con par�metros
    Area(const string& titulo, const string& codigo, int cantidadVentanillas, int maxTiquetes, int maxVentanillas)
        : tituloArea(titulo), codigo(codigo), cantidadVentanillas(cantidadVentanillas) {
        listaTiquetes = new ArrayList<Tiquete>(maxTiquetes);          // Usar ArrayList para lista de tiquetes
        listaVentanillas = new ArrayList<Ventanilla>(maxVentanillas);  // Usar ArrayList para lista de ventanillas
    }

    // Destructor
    ~Area() {
        delete listaTiquetes;
        delete listaVentanillas;
    }

    bool operator ==(const Area& other) {
        return this->tituloArea == other.tituloArea && this->codigo == other.codigo
            && this->cantidadVentanillas == other.cantidadVentanillas
            && this->listaTiquetes == other.listaTiquetes
            && this->listaVentanillas == other.listaVentanillas;
    }
    
    // Operador de asignaci�n. Evita problemas con los "=" de ciertas funciones
    Area& operator=(const Area& other) {
        if (this != &other) {
            tituloArea = other.tituloArea;
            codigo = other.codigo;
            cantidadVentanillas = other.cantidadVentanillas;

            // Limpiar listas actuales
            delete listaTiquetes;
            delete listaVentanillas;

            // Copiar nuevas listas
            listaTiquetes = new ArrayList<Tiquete>(*other.listaTiquetes);
            listaVentanillas = new ArrayList<Ventanilla>(*other.listaVentanillas);
        }
        return *this;
    }

    // M�todo para agregar o modificar un �rea
    void agregarArea(const string& titulo, const string& codigo, int cantidadVentanillas, int maxTiquetes, int maxVentanillas) {
        this->tituloArea = titulo;
        this->codigo = codigo;
        this->cantidadVentanillas = cantidadVentanillas;

        // Eliminar listas actuales y crear nuevas
        delete listaTiquetes;
        listaTiquetes = new ArrayList<Tiquete>(maxTiquetes);

        delete listaVentanillas;
        listaVentanillas = new ArrayList<Ventanilla>(maxVentanillas);
    }

    // M�todo para modificar la cantidad de ventanillas
    void modificarVentanillas(int nuevaCantidad) {
        this->cantidadVentanillas = nuevaCantidad;
    }

    // M�todo est�tico para eliminar un �rea de un arreglo de �reas
    static void eliminarArea(Area* areas, int& totalAreas, int posicionArea) {
        if (posicionArea < 0 || posicionArea >= totalAreas) {
            throw std::out_of_range("Posici�n fuera de rango.");
        }

        // Obtener el �rea a eliminar
        Area& areaEliminar = areas[posicionArea];
        cout << "�rea seleccionada para eliminar: " << areaEliminar.getTituloArea() << " (C�digo: " << areaEliminar.getCodigo() << ")\n";

        // 1. Mostrar los tiquetes asociados a esta �rea
        std::cout << "Tiquetes relacionados al �rea que se eliminar�n:\n";
        for (int i = 0; i < areaEliminar.getListaTiquetes().getSize(); ++i) {
            cout << " - Tiquete ID: " << areaEliminar.getListaTiquetes().getElement() << "\n";
        }

        // 2. Confirmaci�n del usuario antes de eliminar
        std::cout << "�Deseas eliminar el �rea y sus elementos relacionados? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if (confirmacion != 'S' && confirmacion != 's') {
            cout << "Operaci�n cancelada.\n";
            return;
        }

        // 3. Eliminar los tiquetes asociados a esta �rea
        cout << "Eliminando tiquetes relacionados al �rea...\n";
        while (areaEliminar.getListaTiquetes().getSize() > 0) {
            areaEliminar.getListaTiquetes().remove();  // Remueve cada tiquete desde la posici�n 0
        }

        // 4. Eliminar las ventanillas relacionadas a esta �rea
        cout << "Eliminando ventanillas relacionadas al �rea...\n";
        while (areaEliminar.getListaVentanillas().getSize() > 0) {
            areaEliminar.getListaVentanillas().remove();  // Remueve cada ventanilla desde la posici�n 0
        }

        // 5. Eliminar el �rea de la lista de �reas
        for (int i = posicionArea; i < totalAreas - 1; ++i) {
            areas[i] = areas[i + 1];  // Desplaza las �reas para eliminar la seleccionada
        }
        totalAreas--;

        cout << "�rea eliminada con �xito.\n";
    }

    // Getters
    string getTituloArea() const { return tituloArea; }
    string getCodigo() const { return codigo; }
    int getCantidadVentanillas() const { return cantidadVentanillas; }

    // Obtiene las referencias a las listas de tiquetes y ventanillas
    ArrayList<Tiquete>& getListaTiquetes() const { return *listaTiquetes; }
    ArrayList<Ventanilla>& getListaVentanillas() const { return *listaVentanillas; }

    // M�todo para mostrar la informaci�n del �rea
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
