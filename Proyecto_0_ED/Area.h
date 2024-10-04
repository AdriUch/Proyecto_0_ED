/*
            Archivo: Clase Área
            Hecho por: Adrián Ugalde

            Descripción general:Clase que contiene los atributos necesarios
			para crear un objeto llamado Area para después guardarlo
			en una lista. Se detalla el funcionamiento de
			la asignación, las comparaciones entre objetos y la impresión.

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

    // Constructor con parámetros
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

    // Operador de asignación. Evita problemas con los "=" de ciertas funciones
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

    // Método para agregar o modificar un área
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

    // Método para modificar la cantidad de ventanillas
    void modificarVentanillas(int nuevaCantidad) {
        this->cantidadVentanillas = nuevaCantidad;
    }

    // Método estático para eliminar un área de un arreglo de áreas
    static void eliminarArea(Area* areas, int& totalAreas, int posicionArea) {
        if (posicionArea < 0 || posicionArea >= totalAreas) {
            throw std::out_of_range("Posición fuera de rango.");
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

    // Método para mostrar la información del área
    void mostrarInfoArea() const {
        std::cout << "Area: " << tituloArea << " | Codigo: " << codigo << " | Ventanillas: " << cantidadVentanillas << std::endl;
    }
};


