/*
			Archivo: Clase HeapPriorityQueue
			Hecha en clase

			Descripci�n general: Hereda de la clase PriorityQueue. Se implementan
			los m�todos para el manejo de los elementos, que en este caso son los
			objetos KVPair, dentro de la cola de prioridad.

			Modificaci�n hecha por: Carmen Hidalgo Paz

			Descripci�n: Se le agreg� un constructor de copia.
*/


#pragma once

#include <stdexcept>
#include "PriorityQueue.h"
#include "MinHeap.h"
#include "KVPair.h" 

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
	MinHeap<KVPair<int, E>>* pairs;
	int max;

public:
	HeapPriorityQueue(int max = DEFAULT_MAX) {
		pairs = new MinHeap<KVPair<int, E>>(max);
		this->max = max;
	}
	// Copy constructor for HeapPriorityQueue
	HeapPriorityQueue(const HeapPriorityQueue<E>& other) {
		max = other.max;
		// Allocate a new MinHeap with the same capacity
		pairs = new MinHeap<KVPair<int, E>>(*other.pairs);
	}
	void insert(E element, int priority) {
		KVPair<int, E> p(priority, element);
		pairs->insert(p);
	}
	E min() {
		KVPair<int, E> p = pairs->first();
		return p.value;
	}
	int minPriority() {
		KVPair<int, E> p = pairs->first();
		return p.key;
	}
	E removeMin() {
		KVPair<int, E> p = pairs->removeFirst();
		return p.value;
	}
	void clear() {
		pairs->clear();
	}
	int getSize() {
		return pairs->getSize();
	}
	bool isEmpty() {
		return pairs->isEmpty();
	}
	void print() {
		pairs->print();
	}
};

