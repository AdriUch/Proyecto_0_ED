/*
			Archivo: Clase Tiquete
			Hecho por: Carmen Hidalgo Paz

			Descripción general: Una clase que contiene los atributos necesarios
			para poder crear un objeto llamado Tiquete que después se guardará
			en una cola de prioridad. Se detalla el funcionamiento de
			la asignación, las comparaciones entre objetos y la impresión.
*/


#pragma once
#include <iostream>
#include <ctime>

using std::ostream;
using std::string;
using std::time_t;
using std::time;
using std::tm;


class Tiquete {
public:
	string areaCode;
	string code;
	tm horaCreation;
	int prioridadUser;
	int prioridadServicio;
	int prioridadFinal;

	Tiquete() {}
	Tiquete(int prioridadUser, int prioridadServicio, string areaCode, string numGlobal) {
		this->areaCode = areaCode; 
		this->code = this->areaCode + numGlobal;
		// Se obtiene el tiempo actual y se convierte a una hora más entendible
		// para el lector
		time_t tiempoActual = time(0);
		tm utcTime;
		gmtime_s(&utcTime, &tiempoActual);

		const int offset_seconds = -6 * 3600;
		time_t gmt_minus_6 = tiempoActual + offset_seconds;

		tm gmtMinus6Time;
		gmtime_s(&gmtMinus6Time, &gmt_minus_6);

		this->horaCreation = gmtMinus6Time;
		this->prioridadUser = prioridadUser;
		this->prioridadServicio = prioridadServicio;
		this->prioridadFinal = prioridadUser * 10 + prioridadServicio;
	}
	void operator =(const Tiquete& other) {
		this->areaCode = other.areaCode;
		this->code = other.code;
		this->horaCreation = other.horaCreation;
		this->prioridadUser = other.prioridadUser;
		this->prioridadServicio = other.prioridadServicio;
		this->prioridadFinal = other.prioridadFinal;
	}

	string getCode() {
		return code;
	}

	void getTime(){
		cout << horaCreation.tm_hour << ":" << (horaCreation.tm_min < 10 ? "0" : "") <<
			horaCreation.tm_min << ':' << (horaCreation.tm_sec < 10 ? "0" : "") <<
			horaCreation.tm_sec << endl;
	}

	int getFinalPriority() {
		return prioridadFinal;
	}
};

ostream& operator <<(ostream& os, const Tiquete& ticketInfo) {
	os << "(" << ticketInfo.code << ", " << ticketInfo.horaCreation.tm_hour << ":"
		<< (ticketInfo.horaCreation.tm_min < 10 ? "0" : "") << ticketInfo.horaCreation.tm_min<< ':'
		<< (ticketInfo.horaCreation.tm_sec < 10 ? "0" : "") << ticketInfo.horaCreation.tm_sec
		<< ", " << ticketInfo.prioridadFinal << ")";
	return os;
}

