#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
protected:
	E* elements;
	int max;
	int size;
	int pos;

	void expand() {
		E* temp;
		temp = new E[max * 2];

		for (int i = 0; i < size; i++) {
			temp[i] = elements[i];
		}

		delete[] elements;
		elements = temp;
		max = max * 2;
	}

public:
	// Constructor
	ArrayList(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		size = 0;
		pos = 0;
	}
	// Destructor
	~ArrayList() {
		delete[] elements;
	}
	// Inserta un elemento nuevo en la posici�n actual
	void insert(E element) {
		if (size == max) {
			expand();
		}

		for (int i = size; i > pos; i--) {
			elements[i] = elements[i - 1];
		}

		elements[pos] = element;
		size++;
	}
	// Agrega un elemento nuevo en la �ltima posici�n de la lista
	void append(E element) {
		if (size == max) {
			expand();
		}

		elements[size] = element;
		size++;
	}
	// Elimina el elemento encontrado en la posici�n actual
	E remove() {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (pos == size) {
			throw runtime_error("No current element.");
		}

		E result = elements[pos];
		for (int i = pos + 1; i < size; i++) {
			elements[i - 1] = elements[i];
		}

		size--;

		return result;
	}
	// Retorna el valor del elemento encontrado en la posici�n actual
	E getElement() {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (pos == size) {
			throw runtime_error("No current element.");
		}

		return elements[pos];
	}
	// Elimina todos los elementos de la lista y la deja vac�a
	void clear() {
		size = pos = 0;
	}
	// Mueve la posici�n actual al inicio de la lista
	void goToStart() {
		pos = 0;
	}
	// Mueve la posici�n actual al final de la lista
	void goToEnd() {
		pos = size;
	}
	// Mueve la posici�n actual a la posici�n indicada por par�metro
	void goToPos(int pos) {
		if (pos < 0 || pos > size) {
			throw runtime_error("Index out of bounds.");
		}
		this->pos = pos;
	}
	// Mueve la posici�n actual al siguiente elemento, si lo hay
	void next() {
		if (pos < size) {
			pos++;
		}
	}
	// Mueve la posici�n actual al elemento anterior, si lo hay
	void previous() {
		if (pos > 0) {
			pos--;
		}
	}
	// Retorna verdadero si la posici�n actual de la lista se encuentra al inicio
	bool atStart() {
		return pos == 0;
	}
	// Retorna verdadero si la posici�n actual de la lista se encuentra al final
	bool atEnd() {
		return pos == size;
	}
	// Retorna un entero con la posici�n actual dentro de la lista
	int getPos() {
		return pos;
	}
	// Retorna el tama�o de la lista
	int getSize() {
		return size;
	}
	// Dice si la lista est� vac�a
	bool isEmpty() {
		return size == 0;
	}
	// Dice la posici�n de un elemento en una lista, empezando la b�squeda desde
	// una posici�n dada por par�metro
	int indexOf(E element, int start) {
		if (start < 0 || start > size) {
			throw runtime_error("Invalid start position.");
		}
		for (int i = start; i < size; i++) {
			if (elements[i] == element) {
				return i;
			}
		}

		return -1;

	}
	// Retorna verdadero si una lista contiene un elemento dado por par�metro
	bool contains(E element) {
		bool exists = false;

		for (int i = 0; i < size; i++) {
			if (elements[i] == element) {
				exists = true;
			}
		}

		return exists;
	}
	// Imprime la lista
	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++) {
			if (i == pos) {
				cout << "*";
			}
			cout << elements[i] << " ";
		}
		if (pos == size) {
			cout << "*";
		}
		cout << "]" << endl;
		cout << " " << endl;
	}
};

