#pragma once
#include <iostream>

using std::ostream;
using std::string;

class Usuario {
public:
	int prioridadUser;
	string tipoUser;

	Usuario() {}
	Usuario(int prioridadUser, string tipoUser) {
		this->prioridadUser = prioridadUser;
		this->tipoUser = tipoUser;
	}
	void operator =(const Usuario& other) {
		this->tipoUser = other.tipoUser;
		this->prioridadUser = other.prioridadUser;
	}
	
	int getPriority() {
		return prioridadUser;
	}
};

ostream& operator <<(ostream& os, const Usuario& userInfo) {
	os << "(" << userInfo.tipoUser << ")";
	return os;
}