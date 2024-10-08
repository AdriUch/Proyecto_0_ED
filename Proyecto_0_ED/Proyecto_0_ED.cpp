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
#include <locale>

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

// - - - - -  - - - - - MANEJO MENÚS - - - - - - - - - -

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
// Manejo de flechas presionadas en el menú
int keysMenu(int key, int currentSelection, int menuSize) {
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

	return currentSelection;
}
// - - - - -  - - - - - FIN MANEJO MENÚS - - - - - - - - - -

bool removeTickets(ArrayList<Area>& areas) {
	areas.goToStart();
	while (!areas.atEnd()) {
		Area currentArea = areas.getElement();
		currentArea.getColaTiquetes().clear();
		areas.setElement(currentArea);
		areas.next();
	}
	return false;
}

// - - - - - MENÚS ADMINISTRACIÓN - - - - -

// - - MENÚ ADMIN: SERVICIOS - -

int seleccionServicio(List<Servicio>* serviceList) {
	int menuSize = serviceList->getSize();
	int currentSelection = 0;
	bool continueCycle = true;
	while (continueCycle) {
		system("cls");
		cout << "* * * Seleccion de Servicios * * *" << endl;

		// Mostrar el menú con la lista de áreas usando `mostrarMenu`
		mostrarMenu(currentSelection, serviceList, menuSize);

		int key = _getch();
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			continueCycle = false;
		}
	}
	return currentSelection;
}

bool borrarServicio(List<Servicio>* serviceList, int currentSelection) {
	serviceList->goToPos(currentSelection);
	serviceList->remove();
	return false;
}

// Función para seleccionar un área desde la lista de áreas disponibles
Area selectionArea(ArrayList<Area>& areas) {
	int currentSelection = 0;
	int menuSize = areas.getSize();

	while (true) {
		system("cls");
		cout << "* * * Seleccion de Area * * *" << endl;

		// Mostrar el menú con la lista de áreas usando `mostrarMenu`
		mostrarMenu(currentSelection, &areas, menuSize);

		int key = _getch();
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			return areas.getTheElement(currentSelection);
		}
	}
}

//Sub-menú de elegir servicios
Servicio selectionService(List<Servicio>* serviceList, bool incCounter) {
	int menuSize = serviceList->getSize();
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Seleccion de Servicio * * *" << endl;

		// Mostrar el menú de servicios
		mostrarMenu(currentSelection, serviceList, menuSize);

		int key = _getch();
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			// Seleccionar el servicio
			serviceList->goToPos(currentSelection);

			if (incCounter) {
				// Se modifica el contador de tiquetes del servicio
				Servicio service = serviceList->remove();
				service.incrementarContadorTiquetes();
				serviceList->insert(service);
			}

			Servicio servicioSeleccionado = serviceList->getElement();
			return servicioSeleccionado; // Devuelve el servicio seleccionado
		}
	}
}

bool menuServicios(List<Servicio>* serviceList, ArrayList<Area>& areas) {
	// Opciones del menú
	const int menuSize = 4;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Eliminar");
	listMenu->append("Reordenar");
	listMenu->append("Regresar");
	int currentSelection = 0;
	try {
		// Manejo de teclas presionadas en el menú
		while (true) {
			system("cls");
			// Se muestran las opciones del menú
			cout << "* * * Menu de Servicios * * *" << endl;
			mostrarMenu(currentSelection, listMenu, menuSize);

			int key = _getch();
			currentSelection = keysMenu(key, currentSelection, menuSize);

			if (key == 13) { // Enter
				system("cls");
				listMenu->goToPos(currentSelection);
				if (listMenu->getElement() == "Agregar") {
					
					// Si no hay áreas creadas, tirar error
					if (areas.getSize() == 0) {
						throw std::runtime_error("No hay áreas disponibles para seleccionar.");
					}
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
					Area areaSeleccionada = selectionArea(areas);

					// Se crea el objeto Servicio y se agrega a la lista
					// sustituir el "AC" por areaSeleccionada.getCodigo()
					Servicio service(serviceName, servicePriority, areaSeleccionada.getCodigo());
					serviceList->append(service);

					cout << endl << "* Accion realizada con exito *" << endl;
				}
				if (listMenu->getElement() == "Eliminar") {
					// Si las cola de usuarios está vacía
					if (serviceList->getSize() == 0) {
						throw runtime_error("* No hay Servicios disponibles *");
						continue;
					}
					cout << "* * * Seleccion de Borrado de Servicios * * *" << endl;
					int index = seleccionServicio(serviceList);
					string confirm;
					while (true) {
						cout << endl << "¿Desea borrar este servicio?" << endl
							 << "Tome en cuenta que también se borrarán todos los tiquetes." << endl
							 << "Escriba S/s si desea continuar y N/n si no: ";
						cin >> confirm;

						if (confirm == "s" || confirm == "S") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							// Se borra el servicio
							borrarServicio(serviceList, index);
							// Se borran los tiquetes
							removeTickets(areas);
							cout << endl << "* Accion realizada con exito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Accion abandonada *" << endl;
							system("pause");
							break;
						}
						else {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un valor válido *" << endl;
						}
					}
					continue;
				}
				if (listMenu->getElement() == "Reordenar") {
					cout << "* * * Reordenar Servicios * * *" << endl
						 << "Escoja el servicio que desea cambiar a otra posicion:" << endl;

					Servicio selectedService = selectionService(serviceList, false);
					int indexService = serviceList->indexOf(selectedService, 0);

					int newIndex;
					while (true) {
						cout << endl << "El servicio seleccionado se encuentra actualmente en la posicion "
							<< indexService << endl;
						cout << "Ingrese la posicion a la que desea reubicar el servicio."
							<< "Puede elegir una posicion desde 0 hasta "
							<< serviceList->getSize() - 1 << " inclusive: ";
						cin >> newIndex;

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
					serviceList->goToPos(indexService);
					serviceList->remove();
					if (newIndex == serviceList->getSize()) {
						serviceList->append(selectedService);
					}
					else {
						serviceList->goToPos(newIndex);
						serviceList->insert(selectedService);
					}
					cout << "Servicio reordenado con éxito." << endl;
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
	catch (const runtime_error& errorDetectado) {
		std::cerr << "Error: " << errorDetectado.what() << endl;
		system("pause");
		delete listMenu;
		return false;
	}
}

// - - MENÚ ADMIN: ÁREAS - -

void serviceElimination(ArrayList<Area>& areas, int currentAreaIndex,
						List<Servicio>* serviceList) {
	serviceList->goToStart();
	areas.goToPos(currentAreaIndex);
	Area selectedArea = areas.getElement();
	while (!serviceList->atEnd()) {
		Servicio currentService = serviceList->getElement();
		if (currentService.getAreaCode() == selectedArea.getCodigo()) {
			serviceList->remove();
		}
		else {
			serviceList->next();
		}
	}
}

int areaSelection(ArrayList<Area>& areas) {
	int menuSize = areas.getSize();
	int currentSelection = 0;
	bool continueCycle = true;
	while (continueCycle) {
		system("cls");
		cout << "* * * Seleccion de Areas * * *" << endl;

		// Mostrar el menú con la lista de áreas usando `mostrarMenu`
		mostrarMenu(currentSelection, &areas, menuSize);

		int key = _getch();
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			continueCycle = false;
		}
	}
	return currentSelection;
}

bool areaElimination(ArrayList<Area>& areas, int currentSelection) {
	areas.goToPos(currentSelection);
	areas.remove();
	return false;
}

// Sub-menú de Admin. Realiza las operaciones de las áreas
bool menuAreas(ArrayList<Area>& areas, List<Servicio>* serviceList) {
	
	int totalArea = areas.getSize();
	const int menuSize = 4;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Modificar cantidad de ventanillas");
	listMenu->append("Eliminar");
	listMenu->append("Regresar");
	int currentSelection = 0;
	try {

		while (true) {
			system("cls");
			cout << "* * * Menu de Areas * * *" << endl;
			mostrarMenu(currentSelection, listMenu, menuSize);

			//Manejo de las teclas de selección
			int key = _getch();
			currentSelection = keysMenu(key, currentSelection, menuSize);

			if (key == 13) {  // Enter key
				system("cls");
				listMenu->goToPos(currentSelection);
				if (listMenu->getElement() == "Agregar") {
					string titulo, codigo;
					int cantidadVentanillas;

					cout << "Ingrese el titulo del area: ";
					getline(cin, titulo);
					cout << "Ingrese el codigo del area: ";
					getline(cin, codigo);
					while (true) {
						cout << "Ingrese la cantidad de ventanillas: ";
						cin >> cantidadVentanillas;

						if (cin.fail() || cantidadVentanillas <= 0) {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un numero valido *" << endl;
						}
						else {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							break;
						}
					}
					// Crear una nueva área usando el constructor adecuado
					Area nuevaArea(titulo, codigo, cantidadVentanillas);
					// Crear las ventanillas
					for (int i = 0; i < cantidadVentanillas; i++) {
						Ventanilla newVentanilla(codigo, i+1);
						nuevaArea.getListaVentanillas().append(newVentanilla);
					}
					areas.append(nuevaArea);

					cout << "* Area agregada con exito *" << endl;
				}
				//Modifica algún área ya existente
				else if (listMenu->getElement() == "Modificar cantidad de ventanillas") {
					string confirm;
					while (true) {
						cout << "¿Desea modificar la cantidad de ventanillas?" << endl
							<< "Tome en cuenta que también se borrarán todas las actuales y se perderá"
							<< endl << "Estos son los servicios que se van a borrar: " << endl;
						cout << endl << "toda su información. Escriba S/s si desea continuar y N/n si no: ";
						cin >> confirm;

						if (confirm == "s" || confirm == "S") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							// Se selecciona área
							int areaIndex = areaSelection(areas);
							areas.goToPos(areaIndex);
							Area selectedArea = areas.getElement();
							//Cambia la cantidad de ventanillas
							int nuevaCantidad;
							cout << endl << "Cantidad actual: "
								<< selectedArea.getCantidadVentanillas() << endl;
							while (true) {
								cout << "Ingrese la nueva cantidad: ";
								cin >> nuevaCantidad;

								if (cin.fail() || nuevaCantidad <= 0) {
									cin.clear();
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									cout << "* Por favor, ingrese un numero valido *" << endl;
								}
								else {
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									break;
								}
							}
							selectedArea.modificarVentanillas(nuevaCantidad);
							while (!selectedArea.getListaVentanillas().atEnd()) {
								selectedArea.getListaVentanillas().remove();
							}
							for (int i = 0; i < nuevaCantidad; i++) {
								Ventanilla newVentanilla(selectedArea.getCodigo(), i + 1);
								selectedArea.getListaVentanillas().append(newVentanilla);
							}
							areas.setElement(selectedArea);
							cout << endl << "* Accion realizada con exito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Accion abandonada *" << endl;
							system("pause");
							break;
						}
						else {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un valor válido *" << endl;
						}
					}
					continue;
				}
				//Eliminar el área seleccionada
				else if (listMenu->getElement() == "Eliminar") {
					// Si las cola de usuarios está vacía
					if (areas.getSize() == 0) {
						throw runtime_error("* No hay Areas disponibles *");
						continue;
					}
					int selectedIndex = areaSelection(areas);
					string confirm;
					while (true) {
						cout << "¿Desea borrar esta area?" << endl
							<< "Tome en cuenta que también se borrarán todos los servicios y tiquetes asociados a esta"
							<< endl << "Estos son los servicios que se van a borrar: " << endl;
						// Mostar lista de servicios
						serviceList->goToStart();
						areas.goToPos(selectedIndex);
						Area selectedArea = areas.getElement();
						while (!serviceList->atEnd()) {
							Servicio currentService = serviceList->getElement();
							if (currentService.getAreaCode() == selectedArea.getCodigo()) {
								cout << currentService.getDescripcion() << endl;
							}
							serviceList->next();
						}
						cout << endl << "Escriba S/s si desea continuar y N/n si no: ";
						cin >> confirm;

						if (confirm == "s" || confirm == "S") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							// Se borra el área
							areaElimination(areas, selectedIndex);
							// Se borran los servicios
							if (serviceList->getSize() != 0) {
								serviceElimination(areas, selectedIndex, serviceList);
							}
							cout << endl << "* Accion realizada con exito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Accion abandonada *" << endl;
							system("pause");
							break;
						}
						else {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un valor válido *" << endl;
						}
					}
					continue;
				}
				if (currentSelection == menuSize - 1) {
					delete listMenu;
					return false;
				}
				system("pause");
			}
		}
	}
	catch (const runtime_error& errorDetectado) {
		std::cerr << "Error: " << errorDetectado.what() << endl;
		system("pause");
		delete listMenu;
		return false;
	}
}

// - - MENÚ ADMIN: USUARIOS - -

bool userElimination(PriorityQueue<Usuario>* userList) {
	int menuSize = userList->getSize();
	int currentSelection = 0;
	List<Usuario>* arrayListUsers = new ArrayList<Usuario>(userList->getSize());
	int prioridadUser = 0;

		while (!userList->isEmpty()) {
			arrayListUsers->append(userList->removeMin());
		}
		bool continueCycle = true;
		while (continueCycle) {
			system("cls");
			cout << "* * * Seleccion de Borrado de Usuario * * *" << endl;

			// Mostrar el menú de usuarios
			mostrarMenu(currentSelection, arrayListUsers, menuSize);

			int key = _getch();
			currentSelection = keysMenu(key, currentSelection, menuSize);

			if (key == 13) { // Enter
				
				// Seleccionar el usuario
				arrayListUsers->goToPos(currentSelection);

				// Se borra el usuario
				arrayListUsers->remove();
				continueCycle = false;
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

// Sub-menú de Admin. Realiza las operaciones de los usuarios.
bool menuTipoUsuarios(PriorityQueue<Usuario>* userList, ArrayList<Area>& areas) {
	// Opciones del menú
	const int menuSize = 3;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Eliminar");
	listMenu->append("Regresar");
	int currentSelection = 0;
	try {
		// Manejo de teclas presionadas en el menú
		while (true) {
			system("cls");
			// Se muestran las opciones del menú
			cout << "* * * Menu de Usuarios * * *" << endl;
			mostrarMenu(currentSelection, listMenu, menuSize);

			int key = _getch();
			currentSelection = keysMenu(key, currentSelection, menuSize);

			if (key == 13) { // Enter
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
					// Si las cola de usuarios está vacía
					if (userList->getSize() == 0) {
						throw runtime_error("* No hay tipos de Usuarios disponibles *");
						continue;
					}
					string confirm;
					
					while (true) {
						cout << "¿Desea borrar un tipo de usuario?" << endl
							<< "Tome en cuenta que también se borrarán todos los tiquetes creados"
							<< endl << "Escriba S/s si desea continuar y N/n si no: ";
						cin >> confirm;

						if (confirm == "s" || confirm == "S") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							// Se borra el usuario
							userElimination(userList);
							// Se borran los tiquetes
							removeTickets(areas);
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Accion abandonada *" << endl;
							system("pause");
							break;
						}
						else {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un valor válido *" << endl;
						}
					}
					cout << endl << "* Accion realizada con exito *" << endl;
					system("pause");
					continue;
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
	catch (const runtime_error& errorDetectado) {
		std::cerr << "Error: " << errorDetectado.what() << endl;
		system("pause");
		delete listMenu;
		return false;
	}
}

// MENÚ ADMINISTRACIÓN. Sub-menú del principal. Se encarga
// de dar opciones para listas o colas de usuarios, áreas y servicios
bool menuAdmin(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
				ArrayList<Area>& areas) {
	// Opciones del menú
	const int menuSize = 5;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Tipo de Usuario");
	listMenu->append("Areas");
	listMenu->append("Servicios disponibles");
	listMenu->append("Limpiar Colas y Estadisticas");
	listMenu->append("Regresar");
	int currentSelection = 0;
	
	try {
		// Manejo de las teclas del menú
		while (true) {
			system("cls");
			cout << "* * * Menu de Administracion * * *" << endl;
			mostrarMenu(currentSelection, listMenu, menuSize);

			int key = _getch();
			currentSelection = keysMenu(key, currentSelection, menuSize);

			if (key == 13) { // Enter
				system("cls");
				listMenu->goToPos(currentSelection);
				// Agregar/Eliminar usuario
				if (listMenu->getElement() == "Tipo de Usuario") {
					bool tipoUsuariosMenu = menuTipoUsuarios(userList, areas);
					if (!tipoUsuariosMenu) {
						continue;
					}
				}
				// Agregar/ Eliminar áreas y modificar cantidad de ventanillas
				if (listMenu->getElement() == "Areas") {
					bool areasMenu = menuAreas(areas, serviceList);
					if (!areasMenu) {
						continue;
					}
				}
				// Agregar/Eliminar/Reordenar servicio
				if (listMenu->getElement() == "Servicios disponibles") {
					bool serviciosMenu = menuServicios(serviceList, areas);
					if (!serviciosMenu) {
						continue;
					}
				}
				if (listMenu->getElement() == "Limpiar Colas y Estadisticas") {
					string confirm;
					while (true) {
						cout << "¿Desea limpiar las colas y estadisticas?" << endl
							<< "Tome en cuenta que también se borrarán todos los tiquetes creados y los atendidos"
							<< endl << "Escriba S/s si desea continuar y N/n si no: ";
						cin >> confirm;

						if (areas.isEmpty()) {
							throw runtime_error("No hay Areas disponibles");
						}
						if (confirm == "s" || confirm == "S") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							// Se borran las colas de tiquetes
							removeTickets(areas);
							// Se eliminan los tiquetes atendidos en las ventanillas
							areas.goToStart();
							while (!areas.atEnd()) {
								Area currentArea = areas.getElement();
								if (!currentArea.getListaVentanillas().isEmpty()) {
									while (!currentArea.getListaVentanillas().atEnd()) {
										Ventanilla currentVentanilla = currentArea.getListaVentanillas().getElement();
										currentVentanilla.borrarTiquete();
										currentArea.getListaVentanillas().setElement(currentVentanilla);
										currentArea.getListaVentanillas().next();
									}
								}
								areas.setElement(currentArea);
								areas.next();
							}
							cout << endl << "* Accion realizada con exito *" << endl;
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Accion abandonada *" << endl;
							system("pause");
							break;
						}
						else {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un valor válido *" << endl;
						}
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
	catch (const runtime_error& errorDetectado) {
		std::cerr << "Error: " << errorDetectado.what() << endl;
		system("pause");
		delete listMenu;
		return false;
	}
}
// - - - - - FIN MENÚS ADMINISTRACIÓN - - - - -

// - - - - - MENÚS TIQUETES - - - - -

// Sub-menú de Tiquete. Menú de selección de Usuario y creación de Tiquete
bool selectionElements(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
						ArrayList<Area>& areas) {
	try {
		// Si las listas de usuario y servicios están vacías
		if (userList->getSize() == 0) {
			throw runtime_error("* No hay tipos de Usuarios disponibles *");
		}
		if (serviceList->getSize() == 0) {
			throw runtime_error("* No hay servicios disponibles *");
		}

		List<Usuario>* arrayListUsers = new ArrayList<Usuario>(userList->getSize());
		int prioridadUser = 0;

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
			currentSelection = keysMenu(key, currentSelection, menuSize);
			
			if (key == 13) { // Enter
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
					Servicio servicioSeleccionado = selectionService(serviceList, true);

					string stringNumGlobal = std::to_string(numGlobal);
					numGlobal++;

					// Creación de tiquete
					Tiquete ticket(prioridadUser, servicioSeleccionado.getPrioridadServicio(), 
								servicioSeleccionado.getAreaCode(), stringNumGlobal);
					
					areas.goToStart();
					while (!areas.atEnd()) {
						Area currentArea = areas.getElement();
						if (servicioSeleccionado.getAreaCode() == currentArea.getCodigo()) {
							currentArea.getColaTiquetes().insert(ticket, ticket.getFinalPriority());
							currentArea.incrementarContadorTiquetes();
							areas.setElement(currentArea);
						}
						areas.next();
					}

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
bool menuTiquetes(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
					ArrayList<Area>& areas) {
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
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			// Crear un tiquete
			if (listMenu->getElement() == "Creacion de Tiquete") {
				bool creacionTiquete = selectionElements(userList, serviceList, areas);
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
// - - - - - FIN MENÚS TIQUETES - - - - -

// - - - - - MENÚ PRINCIPAL - - - - -

// Contiene sub-menús: Estado de Colas, Tiquetes, Atender,
// Administración y Estadísticas del sistema
void menuPrincipal(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
					ArrayList<Area>& areas) {
	const int menuSize = 6;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Estado de las colas");
	listMenu->append("Tiquetes");
	listMenu->append("Atender");
	listMenu->append("Administración");
	listMenu->append("Estadísticas del sistema");
	listMenu->append("Salir");
	int currentSelection = 0;

	while (true) {
		try {
			system("cls");
			cout << "* * * Menú Principal * * *" << endl;
			mostrarMenu(currentSelection, listMenu, menuSize);

			int key = _getch();
			currentSelection = keysMenu(key, currentSelection, menuSize);

			if (key == 13) { // Enter
				system("cls");
				listMenu->goToPos(currentSelection);
				// Impresión de áreas y ventanillas
				if (listMenu->getElement() == "Estado de las colas") {
					if (areas.isEmpty()) {
						throw runtime_error("* No hay Areas disponibles *");
					}
					system("cls");
					areas.goToStart();
					for (int i = 0; i < areas.getSize(); i++) {
						Area currentA = areas.getElement();
						// Se imprimen datos del área actual
						cout << "Area: " << currentA.getTituloArea() << "  |  "
							<< "Codigo: " << currentA.getCodigo() << endl;
						// Se imprime su cola de tiquetes
						cout << endl << "	* Cola de Tiquetes *" << endl;
						cout << endl << "	- - Inicio de cola - -" << endl << endl;
						// Se crea una lista de tiquetes para que se impriman en orden
						List<Tiquete>* listTickets = 
							new ArrayList<Tiquete>(currentA.getColaTiquetes().getSize());
						while (!currentA.getColaTiquetes().isEmpty()) {
							listTickets->append(currentA.getColaTiquetes().removeMin());
						}
						for (int i = 0; i < listTickets->getSize(); i++) {
							Tiquete currentT = listTickets->getElement();
							cout << "	" << currentT.getCode() << endl;
							listTickets->next();
						}
						cout << endl << "	- - Final de cola - -" << endl;
						listTickets->goToStart();
						// La lista se vuelve a pasar a la cola
						while (!listTickets->isEmpty()) {
							Tiquete ticket = listTickets->remove();
							currentA.getColaTiquetes().insert(ticket, ticket.getFinalPriority());
						}

						delete listTickets;

						// Se imprimen sus ventanillas
						cout << endl << "		* Ventanillas *" << endl << endl;
						currentA.getListaVentanillas().goToStart();
						for (int i = 0; i < currentA.getListaVentanillas().getSize(); i++) {
							Ventanilla currentV = currentA.getListaVentanillas().getElement();
							// Se imprimen datos de la ventanilla actual
							cout << "		Ventanilla: " << currentV.getCode() << endl;
							cout << "			Último Tiquete Atendido: " 
								<< currentV.getTicket().getCode() << endl;
							currentA.getListaVentanillas().next();
						}
						areas.next();

					}
					cout << endl;
				}
				// Opciones de manejo de tiquetes
				if (listMenu->getElement() == "Tiquetes") {
					bool tiquetesMenu = menuTiquetes(userList, serviceList, areas);
					if (!tiquetesMenu) {
						continue;
					}
				}
				// Se atiende el siguiente tiquete
				if (listMenu->getElement() == "Atender") {
					cout << "estoy aqui, wooo";
				}
				// Opciones para usuarios, áreas y servicios
				if (listMenu->getElement() == "Administración") {
					bool adminMenu = menuAdmin(userList, serviceList, areas);
					if (!adminMenu) {
						continue;
					}
				}
				// Consulta de ciertas estadísticas
				if (listMenu->getElement() == "Estadísticas del sistema") {
					cout << "* Estadisticas del Sistema *" << endl << endl;
					cout << "- - Información de Áreas - -" << endl << endl;
					if (areas.getSize() != 0) {
						areas.goToStart();
						for (int i = 0; i < areas.getSize(); i++) {
							int tiempoEsperaTotal = 0;
							Area currentA = areas.getElement();
							// Se imprimen datos del área actual
							cout << "Area: " << currentA.getTituloArea() << endl << endl;

							currentA.getListaVentanillas().goToStart();
							for (int i = 0; i < currentA.getListaVentanillas().getSize(); i++) {
								Ventanilla currentV = currentA.getListaVentanillas().getElement();
								tiempoEsperaTotal = tiempoEsperaTotal + currentV.getTiempoTotalEspera();
								cout << "	Ventanilla " << currentV.getCode() << ": " << endl;
								cout << "		Tiquetes atendidos: " << currentV.getContadorTiquetes() << endl;
								currentA.getListaVentanillas().next();
							}
							if (currentA.getContadorTiquetes() == 0) {
								cout << endl << "	Tiempo promedio de espera: 0 segundos" << endl;
							}
							else {
								double promedio = static_cast<double>(tiempoEsperaTotal) / currentA.getContadorTiquetes();
								cout << endl << "	Tiempo promedio de espera: " << promedio << " segundos" << endl;
							}
							cout << endl << "	Tiquetes dispensados: " << currentA.getContadorTiquetes() << endl << endl;
							areas.next();
						}
					}
					else {
						cout << "* No hay Áreas Disponibles *" << endl;
					}
					cout << endl << "- - Información de Servicios - -" << endl << endl;
					if (serviceList->getSize() != 0) {
						serviceList->goToStart();
						for (int i = 0; i < serviceList->getSize(); i++) {
							Servicio currentS = serviceList->getElement();
							cout << "Servicio: " << currentS.getDescripcion() << endl;
							cout << endl << "	Tiquetes solicitados: " << currentS.getContadorTiquetes() << endl << endl;
							serviceList->next();
						}
					}
					else {
						cout << "* No hay Servicios Disponibles *" << endl;
					}
					cout << endl << "- - Información de Usuarios - -" << endl << endl;
					if (userList->getSize() != 0) {
						List<Usuario>* listUsers =
							new ArrayList<Usuario>(userList->getSize());
						// Se crea una lista de usuarios para que se impriman en orden
						while (!userList->isEmpty()) {
							listUsers->append(userList->removeMin());
						}
						listUsers->goToStart();
						for (int i = 0; i < listUsers->getSize(); i++) {
							Usuario currentU = listUsers->getElement();
							cout << "Usuario: " << currentU.getName() << endl;
							cout << endl << "	Tiquetes emitidos: " << currentU.getTicketCounter() << endl;
							listUsers->next();
						}

						// La lista se vuelve a pasar a la cola
						listUsers->goToStart();
						while (!listUsers->isEmpty()) {
							Usuario user = listUsers->remove();
							userList->insert(user, user.getPriority());
						}
						cout << endl;
						delete listUsers;
					}
					else {
						cout << "* No hay Usuarios Disponibles *" << endl << endl;
					}
				}
				if (currentSelection == menuSize - 1) {
					delete listMenu;
					break;
				}
				system("pause");
			}
		}
		catch (const runtime_error& errorDetectado) {
			std::cerr << "Error: " << errorDetectado.what() << endl;
			system("pause");
		}
	}
}

int main() {
	std::locale::global(std::locale("es_ES.UTF-8"));  // Configurar la localización a español
	setlocale(LC_ALL, "");
	// Se crean todas las listas y colas que se van a utilizar
	PriorityQueue<Usuario>* colaUsuarios = new HeapPriorityQueue<Usuario>();
    List<Servicio>* listaServicios = new ArrayList<Servicio>();
	ArrayList<Area> areaArrayList;
	ArrayList<Area>& listaAreas = areaArrayList;

	menuPrincipal(colaUsuarios, listaServicios, listaAreas);
	
	// No olvides liberar la memoria
	delete colaUsuarios;
    delete listaServicios;
    return 0;
}
