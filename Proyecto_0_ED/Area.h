/*
            Archivo: Clase Área
            Hecho por:

            Descripción general:
*/

#pragma once
#include <string>
#include <iostream>
#include <memory> // Para punteros inteligentes
//#include "LinkedQueue.h"
#include "Tiquete.h"
//#include "Ventanilla.h"

using std::ostream;
using std::string;
using std::unique_ptr;
using std::make_unique;
class Area {
private:
    string tituloArea;
    string codigo;
    int cantidadVentanillas;
    //unique_ptr<LinkedQueue<Tiquete>> listaTiquetes;  // Atributo de tipo puntero inteligente
   // unique_ptr<LinkedQueue<Ventanilla>> listaVentanillas;  // Atributo de tipo puntero inteligente


public:
    // Constructor por defecto
    Area(){}

    // Constructor con lista de inicialización
    Area(const string& titulo, const string& codigo, int cantidadVentanillas /*const LinkedQueue<Tiquete>& listaTiquetes*/)
        : tituloArea(titulo), codigo(codigo), 
        cantidadVentanillas(cantidadVentanillas) /*listaTiquetes(make_unique<LinkedQueue<Tiquete>>(listaTiquetes), listaVentanillas(make_unique<LinkedQueue<Ventanilla>>(listaVentanillas))*/ {}

    // Operador de asignación
    Area& operator=(const Area& other) {
        if (this != &other) { // Evitar la autoasignación
            tituloArea = other.tituloArea;
            codigo = other.codigo;
            cantidadVentanillas = other.cantidadVentanillas;
            //listaTiquetes = make_unique<LinkedQueue<Tiquete>>(*other.listaTiquetes);
           // listaVentanilla = make_unique<LinkedQueue<Ventanilla>>(*other.listaVentanillas);
        }
        return *this; // Devuelve la referencia al objeto actual
    }

    // Método para agregar o modificar un área
    void agregarArea(const string& titulo, const string& codigo, int cantidadVentanillas /*const LinkedQueue<Tiquete>& nuevaListaTiquetes, const LinkedQueue<Ventanilla>& nuevaListaVentanillas*/) {
        this->tituloArea = titulo;
        this->codigo = codigo;
        this->cantidadVentanillas = cantidadVentanillas;
        //this->listaTiquetes = make_unique<LinkedQueue<Tiquete>>(nuevaListaTiquetes);
        //this->listaVentanillas= make_unique<LinkedQueue<Ventanilla>>(nuevaListaVentanillas);
    }

    // Método para modificar la cantidad de ventanillas
    void modificarVentanillas(int nuevaCantidad) {
        this->cantidadVentanillas = nuevaCantidad; // Cambia la cantidad de ventanillas
    }

    // Método para eliminar un área (a través de un arreglo de áreas)
    static void eliminarArea(Area* areas, int& totalAreas, int posicionArea) {
        if (posicionArea < 0 || posicionArea >= totalAreas) {
            throw std::out_of_range("Posición fuera de rango."); // Manejo de errores
        }

        // Mueve las áreas hacia adelante para llenar el vacío
        for (int i = posicionArea; i < totalAreas - 1; ++i) {
            areas[i] = areas[i + 1];
        }
        totalAreas--; // Disminuye el contador de áreas activas
    }

    // Getters
    string getTituloArea() const { return tituloArea; }
    string getCodigo() const { return codigo; }
    int getCantidadVentanillas() const { return cantidadVentanillas; }
    /*LinkedQueue<Tiquete>& getListaTiquetes() const { return *listaTiquetes; }*/
    //    LinkedQueue<Ventanilla>& getListaVentanillas() const { return *listaVentanillas; }
};
