/*
			Archivo: Clase MinHeap
			Hecha en clase

			Descripci�n general: Una clase que contiene los atributos necesarios
			para poder crear un objeto llamado MinHeap que tiene forma de un �rbol
			y organiza elementos de forma que siempre va a salir el que tiene
			menor prioridad.

			Modificaci�n hecha por: Carmen Hidalgo Paz

			Descripci�n: Se agreg� el m�todo privado expand() para expandir el
			arreglo cuando se desea insertar un elemento y el arreglo est� lleno.
*/


#pragma once
#define DEFAULT_MAX 1024

#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class MinHeap {
private:
	E* elements;
	int max;
	int size;

	void siftUp(int pos) {
		while (pos != 0 && elements[pos] < elements[parent(pos)]) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	void siftDown(int pos) {
		while (!isLeaf(pos) && elements[pos] > elements[minChild(pos)]) {
			int mChild = minChild(pos);
			swap(pos, mChild);
			pos = mChild;
		}
	}
	int parent(int pos) {
		return (pos - 1) / 2;
	}
	int leftChild(int pos) {
		return 2 * pos + 1;
	}
	int rightChild(int pos) {
		return 2 * pos + 2;
	}
	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}
	void swap(int pos1, int pos2) {
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}
	int minChild(int pos) {
		if (rightChild(pos) >= size || 
			elements[leftChild(pos)] < elements[rightChild(pos)])
			return leftChild(pos);
		return rightChild(pos);
	}

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
	MinHeap(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		size = 0;
		this->max = max;
	}
	// Copy constructor for MinHeap
	MinHeap(const MinHeap<E>& other) {
		max = other.max;
		size = other.size;
		elements = new E[max];  // Allocate new memory for the elements

		// Copy each element from the other heap into this one
		for (int i = 0; i < size; i++) {
			elements[i] = other.elements[i];
		}
	}
	~MinHeap() {
		delete[] elements;
	}
	void insert(E element) {
		if (size == max) {
			expand();
		}

		elements[size] = element;
		size++;
		siftUp(size - 1);
	}
	E getElementAt(int index) const {
		if (index < 0 || index >= size) {
			throw runtime_error("Index out of bounds.");
		}
		return elements[index];
	}
	E first() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return elements[0];
	}	
	E removeFirst() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return remove(0);
	}	
	E remove(int pos) {
		if (pos < 0 || pos >= size)
			throw runtime_error("Index out of bounds.");
		swap(pos, size - 1);
		size--;
		siftDown(pos);
		return elements[size];
	}
	void clear() {
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << "	" << elements[i] << endl;
		}
	}
};

