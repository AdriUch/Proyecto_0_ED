/*
            Archivo: Clase �rea
            Hecho por: Adri�n Ugalde

            Descripci�n general:Clase que contiene los atributos necesarios
			para crear un objeto llamado Area para despu�s guardarlo
			en una lista. Se detalla el funcionamiento de
			la asignaci�n, las comparaciones entre objetos y la impresi�n.

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
        for (int i = posicionArea; i < totalAreas - 1; ++i) {
            areas[i] = areas[i + 1];
        }
        totalAreas--;
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
};


