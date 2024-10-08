/*
			Archivo: Clase Usuario
			Hecho por: Carmen Hidalgo Paz

			Descripción general: Una clase que contiene los atributos necesarios
			para poder crear un objeto llamado Usuario que después se guardará
			en una cola de prioridad. Se detalla el funcionamiento de
			la asignación, las comparaciones entre objetos y la impresión.
*/


#pragma once
#include <iostream>

using std::ostream;
using std::string;

class Usuario {
public:
	int prioridadUser;
	string tipoUser;
	int contadorTiquetes;

	Usuario() {}
	Usuario(int prioridadUser, string tipoUser) {
		this->prioridadUser = prioridadUser;
		this->tipoUser = tipoUser;
		contadorTiquetes = 0;
	}
	void operator =(const Usuario& other) {
		this->tipoUser = other.tipoUser;
		this->prioridadUser = other.prioridadUser;
		this->contadorTiquetes = other.contadorTiquetes;
	}
	bool operator ==(const Usuario& other) {
		return this->tipoUser == other.tipoUser &&
				this->prioridadUser == other.prioridadUser &&
				this->contadorTiquetes == other.contadorTiquetes;
	}
	bool operator !=(const Usuario& other) {
		return this->tipoUser != other.tipoUser &&
				this->prioridadUser != other.prioridadUser &&
				this->contadorTiquetes != other.contadorTiquetes;
	}
	bool operator <(const Usuario& other) {
		return this->tipoUser < other.tipoUser &&
				this->prioridadUser < other.prioridadUser &&
				this->contadorTiquetes < other.contadorTiquetes;
	}
	bool operator <=(const Usuario& other) {
		return this->tipoUser <= other.tipoUser &&
				this->prioridadUser <= other.prioridadUser &&
				this->contadorTiquetes <= other.contadorTiquetes;
	}
	bool operator >(const Usuario& other) {
		return this->tipoUser > other.tipoUser &&
				this->prioridadUser > other.prioridadUser &&
				this->contadorTiquetes > other.contadorTiquetes;
	}
	bool operator >=(const Usuario& other) {
		return this->tipoUser >= other.tipoUser &&
				this->prioridadUser >= other.prioridadUser &&
				this->contadorTiquetes >= other.contadorTiquetes;
	}

	string getName() {
		return tipoUser;
	}
	int getPriority() {
		return prioridadUser;
	}
	int getTicketCounter() {
		return contadorTiquetes;
	}
	void setTicketCounter() {
		contadorTiquetes = contadorTiquetes + 1;
	}
	void resetTicketCounter(int count) {
		contadorTiquetes = 0;
	}
};

ostream& operator <<(ostream& os, const Usuario& userInfo) {
	os << userInfo.tipoUser;
	return os;
}