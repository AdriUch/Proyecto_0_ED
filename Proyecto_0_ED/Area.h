/*
            Archivo: Clase �rea
            Hecho por:

            Descripci�n general:
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

    // Constructor con lista de inicializaci�n
    Area(const string& titulo, const string& codigo, int cantidadVentanillas /*const LinkedQueue<Tiquete>& listaTiquetes*/)
        : tituloArea(titulo), codigo(codigo), 
        cantidadVentanillas(cantidadVentanillas) /*listaTiquetes(make_unique<LinkedQueue<Tiquete>>(listaTiquetes), listaVentanillas(make_unique<LinkedQueue<Ventanilla>>(listaVentanillas))*/ {}

    // Operador de asignaci�n
    Area& operator=(const Area& other) {
        if (this != &other) { // Evitar la autoasignaci�n
            tituloArea = other.tituloArea;
            codigo = other.codigo;
            cantidadVentanillas = other.cantidadVentanillas;
            //listaTiquetes = make_unique<LinkedQueue<Tiquete>>(*other.listaTiquetes);
           // listaVentanilla = make_unique<LinkedQueue<Ventanilla>>(*other.listaVentanillas);
        }
        return *this; // Devuelve la referencia al objeto actual
    }

    // M�todo para agregar o modificar un �rea
    void agregarArea(const string& titulo, const string& codigo, int cantidadVentanillas /*const LinkedQueue<Tiquete>& nuevaListaTiquetes, const LinkedQueue<Ventanilla>& nuevaListaVentanillas*/) {
        this->tituloArea = titulo;
        this->codigo = codigo;
        this->cantidadVentanillas = cantidadVentanillas;
        //this->listaTiquetes = make_unique<LinkedQueue<Tiquete>>(nuevaListaTiquetes);
        //this->listaVentanillas= make_unique<LinkedQueue<Ventanilla>>(nuevaListaVentanillas);
    }

    // M�todo para modificar la cantidad de ventanillas
    void modificarVentanillas(int nuevaCantidad) {
        this->cantidadVentanillas = nuevaCantidad; // Cambia la cantidad de ventanillas
    }

    // M�todo para eliminar un �rea (a trav�s de un arreglo de �reas)
    static void eliminarArea(Area* areas, int& totalAreas, int posicionArea) {
        if (posicionArea < 0 || posicionArea >= totalAreas) {
            throw std::out_of_range("Posici�n fuera de rango."); // Manejo de errores
        }

        // Mueve las �reas hacia adelante para llenar el vac�o
        for (int i = posicionArea; i < totalAreas - 1; ++i) {
            areas[i] = areas[i + 1];
        }
        totalAreas--; // Disminuye el contador de �reas activas
    }

    // Getters
    string getTituloArea() const { return tituloArea; }
    string getCodigo() const { return codigo; }
    int getCantidadVentanillas() const { return cantidadVentanillas; }
    /*LinkedQueue<Tiquete>& getListaTiquetes() const { return *listaTiquetes; }*/
    //    LinkedQueue<Ventanilla>& getListaVentanillas() const { return *listaVentanillas; }
};
