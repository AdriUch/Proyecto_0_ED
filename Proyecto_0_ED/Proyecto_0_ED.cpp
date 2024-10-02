#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <conio.h> // Para elección del menú

#include "LinkedPriorityQueue.h"
#include "MinHeap.h"
#include "HeapPriorityQueue.h"
#include "Usuario.h"
#include "Tiquete.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::to_string;

// - - - - -  - - - - - MENÚS - - - - - - - - - -


// Función para mostrar un menú
void mostrarMenu(int currentSelection, const string opciones[], int size) {
	system("cls");

	for (int i = 0; i < size; ++i) {
		if (i == currentSelection) {
			cout << " > " << opciones[i] << endl;
		}
		else {
			cout << "   " << opciones[i] << endl;
		}
	}
}

// - - - - - MENÚS TIQUETES - - - - -

//Sub-menú del principal. Genera un tiquete
bool menuTiquetes() {
	const int menuSize = 2;
	string opciones[menuSize] = { "Tipo de Usuario", "Regresar" };
	int currentSelection = 0;

	while (true) {
		mostrarMenu(currentSelection, opciones, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80:
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) {
			system("cls");
			
			if (opciones[currentSelection] == "Tipo de Usuario") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (currentSelection == menuSize - 1) {
				return false;
			}
			system("pause");
		}
	}
}

// - - - - - MENÚS ADMINISTRACIÓN - - - - -

// Sub-menú de Admin. Realiza las operaciones de los usuarios.
bool menuTipoUsuarios(PriorityQueue<Usuario>* userList) {
	const int menuSize = 3;
	string opciones[menuSize] = { "Agregar", "Eliminar", "Regresar" };
	int currentSelection = 0;

	while (true) {
		mostrarMenu(currentSelection, opciones, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80:
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) {
			system("cls");

			if (opciones[currentSelection] == "Agregar") {
				string userName;
				int userPriority;
				cout << "Ingrese el nombre de usuario que desea agregar: ";
				getline(cin, userName);

				while (true) {
					cout << endl << "Ingrese la prioridad del tipo de usuario: ";
					cin >> userPriority;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cout << "* Por favor, ingrese un numero valido *" << endl;
					}
					else {
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					}
				}

				Usuario user(userPriority, userName);
				userList->insert(user, user.getPriority());

				userList->print();

				cout << endl << "* Accion realizada con exito *" << endl;
			}
			if (opciones[currentSelection] == "Eliminar") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (currentSelection == menuSize - 1) {
				return false;
			}
			system("pause");
		}
	}
}

//Sub-menú del principal. Se encarga de dar opciones para listas o colas de usuarios, áres y servicios
bool menuAdmin(PriorityQueue<Usuario>* userList) {
	const int menuSize = 4;
	string opciones[menuSize] = { "Tipo de Usuario", "Areas", "Servicios disponibles", "Regresar"};
	int currentSelection = 0;

	while (true) {
		mostrarMenu(currentSelection, opciones, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80:
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) {
			system("cls");

			if (opciones[currentSelection] == "Tipo de Usuario") {
				bool tipoUsuariosMenu = menuTipoUsuarios(userList);
				if (!tipoUsuariosMenu) {
					continue;
				}
			}
			if (opciones[currentSelection] == "Areas") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (opciones[currentSelection] == "Servicios disponibles") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (currentSelection == menuSize - 1) {
				return false;
			}
			system("pause");
		}
	}
}



// - - - - - MENÚ PRINCIPAL - - - - -
void menuPrincipal(PriorityQueue<Usuario>* userList) {
	const int menuSize = 6;
	string opciones[menuSize] = { "Estado de las colas", "Tiquetes", "Atender", "Administracion", "Estadisticas del sistema", "Exit"};
	int currentSelection = 0;

	while (true) {
		mostrarMenu(currentSelection, opciones, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80:
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) {
			system("cls");

			if (opciones[currentSelection] == "Estado de las colas") {
				cout << "estoy aqui, wooo";
			}
			if (opciones[currentSelection] == "Tiquetes") {
				bool tiquetesMenu = menuTiquetes();
				if (!tiquetesMenu) {
					continue;
				}
			}
			if (opciones[currentSelection] == "Atender") {
				cout << "estoy aqui, wooo";
			}
			if (opciones[currentSelection] == "Administracion") {
				bool adminMenu = menuAdmin(userList);
				if (!adminMenu) {
					continue;
				}
			}
			if (opciones[currentSelection] == "Estadisticas del sistema") {
				cout << "estoy aqui, wooo";
			}
			if (currentSelection == menuSize - 1) {
				break;
			}
			system("pause");
		}
	}
}

int main() {
	PriorityQueue<Usuario>* colaUsuarios = new HeapPriorityQueue<Usuario>();
	menuPrincipal(colaUsuarios);

	delete colaUsuarios;
	return 0;
}
