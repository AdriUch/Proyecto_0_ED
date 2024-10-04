/*
			Trabajo: Proyecto 0 - Sistema de administración de colas
			Hecho por: Carmen Hidalgo Paz, Britany y Adrián
			Fecha de Entrega: 8 de octubre del 2024
			Clase: Estructuras de Datos

			Descripción General: En este archivo se manejan todos las menús
			del programa. Cada opción puede generar un sub-menú nuevo con
			más opciones por escoger, muestra alguna información o modifica
			de alguna manera las listas y colas creadas al inicio del programa.

*/



#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <conio.h> // Para elección del menú

#include "MinHeap.h"
#include "HeapPriorityQueue.h"
#include "ArrayList.h"
#include "Usuario.h"
#include "Servicio.h"
#include "Tiquete.h"
#include "Area.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::to_string;

int numGlobal = 100;

// - - - - -  - - - - - MENÚS - - - - - - - - - -

// Función para mostrar un menú
template <typename E>
void mostrarMenu(int currentSelection, List<E>* opciones, int size) {
	for (int i = 0; i < size; i++) {
		opciones->goToPos(i);
		if (i == currentSelection) {
			cout << " > " << opciones->getElement() << endl;
		}
		else {
			cout << "   " << opciones->getElement() << endl;
		}
	}
}


// - - - - - MENÚS ADMINISTRACIÓN - - - - -

// Sub-menú de Admin. Realiza las operaciones de los usuarios.
bool menuTipoUsuarios(PriorityQueue<Usuario>* userList) {
	// Opciones del menú
	const int menuSize = 3;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Eliminar");
	listMenu->append("Regresar");
	int currentSelection = 0;
	
	// Manejo de teclas presionadas en el menú
	while (true) {
		system("cls");
		// Se muestran las opciones del menú
		cout << "* * * Menu de Usuarios * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Flecha arriba
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80: // Flecha abajo
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			if (listMenu->getElement() == "Agregar") {
				// Se pide al usuario un número y un string
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
				// Se crea el objeto Usuario y se agrega a la lista
				Usuario user(userPriority, userName);
				userList->insert(user, user.getPriority());

				cout << endl << "* Accion realizada con exito *" << endl;
			}
			if (listMenu->getElement() == "Eliminar") {
				cout << "estoy aqui, wooo" << endl;
			}
			// Opción de regresar
			if (currentSelection == menuSize - 1) {
				delete listMenu;
				return false;
			}
			system("pause");
		}
	}
}

/*Area selectionArea() {

}*/

bool menuServicios(List<Servicio>* serviceList) {
	// Opciones del menú
	const int menuSize = 4;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Eliminar");
	listMenu->append("Reordenar");
	listMenu->append("Regresar");
	int currentSelection = 0;

	// Manejo de teclas presionadas en el menú
	while (true) {
		system("cls");
		// Se muestran las opciones del menú
		cout << "* * * Menu de Servicios * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Flecha arriba
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80: // Flecha abajo
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			if (listMenu->getElement() == "Agregar") {
				// Se pide al usuario un número y un string
				string serviceName;
				int servicePriority;
				cout << "Ingrese el nombre del servicio que desea agregar: ";
				getline(cin, serviceName);

				while (true) {
					cout << endl << "Ingrese la prioridad del servicio: ";
					cin >> servicePriority;

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
				
				// Selección de área
				//Area areaSeleccionada = selectionArea(areaList);
				
				// Se crea el objeto Servicio y se agrega a la lista
				// sustituir el "AC" por areaSeleccionada.getCodigo()
				Servicio service(serviceName, servicePriority, "AC");
				serviceList->append(service);

				cout << endl << "* Accion realizada con exito *" << endl;
			}
			if (listMenu->getElement() == "Eliminar") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (listMenu->getElement() == "Reordenar") {
				cout << "estoy aqui, wooo" << endl;
			}
			// Opción de regresar
			if (currentSelection == menuSize - 1) {
				delete listMenu;
				return false;
			}
			system("pause");
		}
	}
}

// MENÚ ADMINISTRACIÓN. Sub-menú del principal. Se encarga
// de dar opciones para listas o colas de usuarios, áreas y servicios
bool menuAdmin(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList) {
	// Opciones del menú
	const int menuSize = 5;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Tipo de Usuario");
	listMenu->append("Areas");
	listMenu->append("Servicios disponibles");
	listMenu->append("Limpiar Colas y Estadisticas");
	listMenu->append("Regresar");
	int currentSelection = 0;
	
	// Manejo de las teclas del menú
	while (true) {
		system("cls");
		cout << "* * * Menu de Administracion * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Flecha arriba
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80: // Flecha abajo
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			// Agregar/Eliminar usuario
			if (listMenu->getElement() == "Tipo de Usuario") {
				bool tipoUsuariosMenu = menuTipoUsuarios(userList);
				if (!tipoUsuariosMenu) {
					continue;
				}
			}
			// Agregar/ Eliminar áreas y modificar cantidad de ventanillas
			if (listMenu->getElement() == "Areas") {
				cout << "estoy aqui, wooo" << endl;
			}
			// Agregar/Eliminar/Reordenar servicio
			if (listMenu->getElement() == "Servicios disponibles") {
				bool serviciosMenu = menuServicios(serviceList);
				if (!serviciosMenu) {
					continue;
				}
			}
			if (listMenu->getElement() == "Limpiar Colas y Estadisticas") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (currentSelection == menuSize - 1) {
				delete listMenu;
				return false;
			}
			system("pause");
		}
	}
}


// - - - - - MENÚS TIQUETES - - - - -

//Sub-menú de elegir servivicios
Servicio selectionService(List<Servicio>* serviceList) {
	int menuSize = serviceList->getSize();
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Seleccion de Servicio * * *" << endl;

		// Mostrar el menú de servicios
		mostrarMenu(currentSelection, serviceList, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Flecha arriba
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80: // Flecha abajo
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) { // Enter
			// Seleccionar el servicio
			serviceList->goToPos(currentSelection);

			// Se modifica el contador de tiquetes del servicio
			Servicio service = serviceList->remove();
			service.setTicketCounter();
			serviceList->insert(service);

			Servicio servicioSeleccionado = serviceList->getElement();
			return servicioSeleccionado; // Devuelve el servicio seleccionado
		}
	}
}

// Sub-menú de Tiquete. Menú de selección de Usuario y creación de Tiquete
bool selectionElements(PriorityQueue<Usuario>* userList, PriorityQueue<Tiquete>* ticketList,
						List<Servicio>* serviceList) {
	try {
		List<Usuario>* arrayListUsers = new ArrayList<Usuario>(userList->getSize());
		int prioridadUser = 0;

		// Si las listas de usuario y servicios están vacías
		if (userList->getSize() == 0) {
			throw runtime_error("* No hay tipos de Usuarios disponibles *");
		}
		if (serviceList->getSize() == 0) {
			throw runtime_error("* No hay servicios disponibles *");
		}

		while (!userList->isEmpty()) {
			arrayListUsers->append(userList->removeMin());
		}
		int menuSize = arrayListUsers->getSize();
		int currentSelection = 0;
		bool repeatMenu = true;
		while (repeatMenu) {
			system("cls");
			cout << "* * * Seleccion de Tipos de Usuarios * * *" << endl;
			mostrarMenu(currentSelection, arrayListUsers, menuSize);

			int key = _getch();
			if (key == 224) {
				key = _getch();
				switch (key) {
				case 72: // Flecha arriba
					if (currentSelection > 0) {
						currentSelection--;
					}
					break;
				case 80: // Flecha abajo
					if (currentSelection < menuSize - 1) {
						currentSelection++;
					}
					break;
				}
			}
			else if (key == 13) { // Enter
				system("cls");

				if (currentSelection < menuSize) {
					// Selección del usuario

					arrayListUsers->goToPos(currentSelection);
					// Se modifica el atributo de cuenta de tiquetes
					// del Usuario elegido
					Usuario user = arrayListUsers->remove();
					user.setTicketCounter();
					arrayListUsers->insert(user);
					prioridadUser = arrayListUsers->getElement().prioridadUser;

					// Selección de servicio
					Servicio servicioSeleccionado = selectionService(serviceList);

					string stringNumGlobal = std::to_string(numGlobal);
					numGlobal++;

					// Creación de tiquete
					Tiquete ticket(prioridadUser, servicioSeleccionado.getPrioridadServicio(), 
								servicioSeleccionado.getAreaCode(), stringNumGlobal);
					ticketList->insert(ticket, ticket.getFinalPriority());

					cout << endl << "* Accion realizada con exito *" << endl << endl;
					cout << "Informacion del tiquete creado: " << endl;
					cout << "Codigo: " << ticket.getCode() << endl;
					cout << "Hora de creacion:";
					ticket.getTime();
					cout << "Prioridad: " << ticket.getFinalPriority() << endl;
					system("pause");
				}
				repeatMenu = false;
			}

		}

		arrayListUsers->goToStart();
		while (!arrayListUsers->isEmpty()) {
			Usuario user = arrayListUsers->remove();
			userList->insert(user, user.getPriority());
		}

		delete arrayListUsers;

		return false;

	}
	catch (const runtime_error& errorDetectado) {
		std::cerr << "Error: " << errorDetectado.what() << endl;
		system("pause");
		return false;
	}
}

// MENÚ TIQUETES. Sub-menú del principal. Para pedir la creación de un tiquete.
bool menuTiquetes(PriorityQueue<Usuario>* userList, PriorityQueue<Tiquete>* ticketList,
					List<Servicio>* serviceList) {
	const int menuSize = 2;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Creacion de Tiquete");
	listMenu->append("Regresar");
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Menu de Tiquetes * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Flecha arriba
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80: // Flecha abajo
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			// Crear un tiquete
			if (listMenu->getElement() == "Creacion de Tiquete") {
				bool creacionTiquete = selectionElements(userList, ticketList, serviceList);
				if (!creacionTiquete) {
					continue;
				}
			}
			if (currentSelection == menuSize - 1) {
				delete listMenu;
				return false;
			}
			system("pause");
		}
	}
}


// - - - - - MENÚ PRINCIPAL - - - - -

// Contiene sub-menús: Estado de Colas, Tiquetes, Atender,
// Administración y Estadísticas del sistema
void menuPrincipal(PriorityQueue<Usuario>* userList, PriorityQueue<Tiquete>* ticketList,
					List<Servicio>* serviceList) {
	const int menuSize = 6;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Estado de las colas");
	listMenu->append("Tiquetes");
	listMenu->append("Atender");
	listMenu->append("Administracion");
	listMenu->append("Estadisticas del sistema");
	listMenu->append("Salir");
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Menú Principal * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Flecha arriba
				if (currentSelection > 0) {
					currentSelection--;
				}
				break;
			case 80: // Flecha abajo
				if (currentSelection < menuSize - 1) {
					currentSelection++;
				}
				break;
			}
		}
		else if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			// Impresión de áreas y ventanillas
			if (listMenu->getElement() == "Estado de las colas") {
				cout << "estoy aqui, wooo";
			}
			// Opciones de manejo de tiquetes
			if (listMenu->getElement() == "Tiquetes") {
				bool tiquetesMenu = menuTiquetes(userList, ticketList, serviceList);
				if (!tiquetesMenu) {
					continue;
				}
			}
			// Se atiende el siguiente tiquete
			if (listMenu->getElement() == "Atender") {
				cout << "estoy aqui, wooo";
			}
			// Opciones para usuarios, áreas y servicios
			if (listMenu->getElement() == "Administracion") {
				bool adminMenu = menuAdmin(userList, serviceList);
				if (!adminMenu) {
					continue;
				}
			}
			// Consulta de ciertas estadísticas
			if (listMenu->getElement() == "Estadisticas del sistema") {
				cout << "estoy aqui, wooo";
			}
			if (currentSelection == menuSize - 1) {
				delete listMenu;
				break;
			}
			system("pause");
		}
	}
}
/*try {
} catch (const runtime_error& errorDetectado) {
	std::cerr << "Error: " << errorDetectado.what() << endl;
}*/

int main() {
	// Se crean todas las listas y colas que se van a utilizar
	PriorityQueue<Usuario>* colaUsuarios = new HeapPriorityQueue<Usuario>();
    PriorityQueue<Tiquete>* colaTiquetes = new HeapPriorityQueue<Tiquete>();
    List<Servicio>* listaServicios = new ArrayList<Servicio>();

	menuPrincipal(colaUsuarios, colaTiquetes, listaServicios);

	colaUsuarios->print();
	colaTiquetes->print();
	listaServicios->print();
	
	// No olvides liberar la memoria
	delete colaUsuarios;
    delete colaTiquetes;
    delete listaServicios;
    return 0;
}


