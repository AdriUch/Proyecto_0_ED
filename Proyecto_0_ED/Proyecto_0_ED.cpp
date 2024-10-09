/*
			Trabajo: Proyecto 0 - Sistema de administración de colas
			Hecho por: Carmen Hidalgo Paz, Britany Romero Hernández y Adrián Ugalde Chaves
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
		cout << "* * * Selección de Servicios * * *" << endl;

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
		cout << "* * * Selección de Área * * *" << endl;

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
		cout << "* * * Selección de Servicio * * *" << endl;

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
// Agregado por Britany y las funciones reordenar y eliminar modificadas por Carmem
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
			cout << "* * * Menú de Servicios * * *" << endl;
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
							cout << "* Por favor, ingrese un número válido *" << endl;
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

					cout << endl << "* Acción realizada con éxito *" << endl;
				}
				if (listMenu->getElement() == "Eliminar") {
					// Si las cola de usuarios está vacía
					if (serviceList->getSize() == 0) {
						throw runtime_error("* No hay Servicios disponibles *");
						continue;
					}
					cout << "* * * Selección de Borrado de Servicios * * *" << endl;
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
							cout << endl << "* Acción realizada con éxito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Acción abandonada *" << endl;
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
						<< "Escoja el servicio que desea cambiar a otra posición:" << endl;

					Servicio selectedService = selectionService(serviceList, false);
					int indexService = serviceList->indexOf(selectedService, 0);

					int newIndex;
					while (true) {
						cout << endl << "El servicio seleccionado se encuentra actualmente en la posición "
							<< indexService << endl;
						cout << "Ingrese la posición a la que desea reubicar el servicio."
							<< endl << "Puede elegir una posición desde 0 hasta "
							<< serviceList->getSize() - 1 << " inclusive: ";
						cin >> newIndex;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un número válido *" << endl;
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
					cout << endl << "Servicio reordenado con éxito." << endl;
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
// - - FIN DE MENÚ ADMIN: SERVICIOS - -


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
		cout << "* * * Selección de Áreas * * *" << endl;

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
			cout << "* * * Menú de Áreas * * *" << endl;
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

					cout << "Ingrese el título del área: ";
					getline(cin, titulo);
					cout << "Ingrese el código del área: ";
					getline(cin, codigo);
					while (true) {
						cout << "Ingrese la cantidad de ventanillas: ";
						cin >> cantidadVentanillas;

						if (cin.fail() || cantidadVentanillas <= 0) {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << "* Por favor, ingrese un número válido *" << endl;
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
						Ventanilla newVentanilla(codigo, i + 1);
						nuevaArea.getListaVentanillas().append(newVentanilla);
					}
					areas.append(nuevaArea);

					cout << endl << "* Área agregada con éxito *" << endl;
				}
				//Modifica algún área ya existente
				else if (listMenu->getElement() == "Modificar cantidad de ventanillas") {
					string confirm;
					while (true) {
						cout << "¿Desea modificar la cantidad de ventanillas?" << endl
							<< "Tome en cuenta que también se borrarán todas las actuales y se perderá"
							<< endl << "toda su información. Escriba S/s si desea continuar y N/n si no: ";
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
									cout << "* Por favor, ingrese un número válido *" << endl;
								}
								else {
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									break;
								}
							}
							selectedArea.modificarVentanillas(nuevaCantidad);
							selectedArea.getListaVentanillas().goToStart();
							while (!selectedArea.getListaVentanillas().atEnd()) {
								selectedArea.getListaVentanillas().remove();
							}
							for (int i = 0; i < nuevaCantidad; i++) {
								Ventanilla newVentanilla(selectedArea.getCodigo(), i + 1);
								selectedArea.getListaVentanillas().append(newVentanilla);
							}
							areas.setElement(selectedArea);
							cout << endl << "* Acción realizada con éxito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Acción abandonada *" << endl;
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
						throw runtime_error("* No hay Áreas disponibles *");
						continue;
					}
					int selectedIndex = areaSelection(areas);
					string confirm;
					while (true) {
						cout << "¿Desea borrar esta área?" << endl
							<< "Tome en cuenta que también se borrarán todos los servicios y tiquetes asociados a ésta"
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
							cout << endl << "* Acción realizada con éxito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Acción abandonada *" << endl;
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

// - - FIN DE MENÚ ADMIN: ÁREAS - -



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
		cout << "* * * Selección de Borrado de Usuario * * *" << endl;

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
			cout << "* * * Menú de Usuarios * * *" << endl;
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
							cout << "* Por favor, ingrese un número válido *" << endl;
						}
						else {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							break;
						}
					}
					// Se crea el objeto Usuario y se agrega a la lista
					Usuario user(userPriority, userName);
					userList->insert(user, user.getPriority());

					cout << endl << "* Acción realizada con éxito *" << endl;
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
							cout << endl << "* Acción realizada con éxito *" << endl;
							system("pause");
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Acción abandonada *" << endl;
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

// - - FIN DE MENÚ ADMIN: USUARIOS - -



// MENÚ ADMINISTRACIÓN. Sub-menú del principal. Se encarga
// de dar opciones para listas o colas de usuarios, áreas y servicios
bool menuAdmin(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
	ArrayList<Area>& areas) {
	// Opciones del menú
	const int menuSize = 5;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Tipo de Usuario");
	listMenu->append("Áreas");
	listMenu->append("Servicios disponibles");
	listMenu->append("Limpiar Colas y Estadísticas");
	listMenu->append("Regresar");
	int currentSelection = 0;

	try {
		// Manejo de las teclas del menú
		while (true) {
			system("cls");
			cout << "* * * Menú de Administración * * *" << endl;
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
				if (listMenu->getElement() == "Áreas") {
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
				if (listMenu->getElement() == "Limpiar Colas y Estadísticas") {
					string confirm;
					while (true) {
						if (areas.isEmpty()) {
							throw runtime_error("No hay Áreas disponibles");
						}
						cout << "¿Desea limpiar las colas y estadísticas?" << endl
							<< "Tome en cuenta que se borrarán todos los tiquetes creados y los atendidos."
							<< endl << "Además, se van eliminar todos los datos guardados en las estadísticas."
							<< endl << "Escriba S/s si desea continuar y N/n si no: ";
						cin >> confirm;
						if (confirm == "s" || confirm == "S") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							// Se borran las colas de tiquetes
							removeTickets(areas);
							// Se eliminan los tiquetes atendidos en las ventanillas
							areas.goToStart();
							while (!areas.atEnd()) {
								Area currentArea = areas.getElement();
								if (!currentArea.getListaVentanillas().isEmpty()) {
									currentArea.getListaVentanillas().goToStart();
									while (!currentArea.getListaVentanillas().atEnd()) {
										Ventanilla currentVentanilla = currentArea.getListaVentanillas().getElement();
										currentVentanilla.borrarTiquete();
										currentVentanilla.setContadorTiquetes(0);
										currentVentanilla.setTiempoTotalEspera(0);
										currentVentanilla.setTiempoTiquete(0);
										currentArea.getListaVentanillas().setElement(currentVentanilla);
										currentArea.getListaVentanillas().next();
									}
								}
								currentArea.setContadorTiquetes(0);
								areas.setElement(currentArea);
								areas.next();
							}
							serviceList->goToStart();
							while (!serviceList->atEnd()) {
								Servicio currentS = serviceList->getElement();
								currentS.setContadorTiquetes(0);
								serviceList->setElement(currentS);
								serviceList->next();
							}
							if (userList->getSize() != 0) {
								List<Usuario>* listUsers =
									new ArrayList<Usuario>(userList->getSize());
								// Se crea una lista de usuarios para que se pueda acceder a todos
								while (!userList->isEmpty()) {
									listUsers->append(userList->removeMin());
								}
								listUsers->goToStart();
								for (int i = 0; i < listUsers->getSize(); i++) {
									Usuario currentU = listUsers->getElement();
									currentU.resetTicketCounter(0);
									listUsers->setElement(currentU);
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

							cout << endl << "* Acción realizada con éxito *" << endl;
							break;
						}
						if (confirm == "n" || confirm == "N") {
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cout << endl << "* Acción abandonada *" << endl;
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
			cout << "* * * Selección de Tipos de Usuarios * * *" << endl;
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

					cout << endl << "* Acción realizada con éxito *" << endl << endl;
					cout << "Información del tiquete creado: " << endl;
					cout << "Código: " << ticket.getCode() << endl;
					cout << "Hora de creación:";
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
	listMenu->append("Creación de Tiquete");
	listMenu->append("Regresar");
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Menú de Tiquetes * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

		int key = _getch();
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			system("cls");
			listMenu->goToPos(currentSelection);
			// Crear un tiquete
			if (listMenu->getElement() == "Creación de Tiquete") {
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


// - - - - -  MENÚ ATENDER - - - - -

// MENÚ ATENDER. Sub-menú del principal. Para pedir que se atienda un tiquete.
bool atenderTiquete(ArrayList<Area>& areas) {
	// Verificar que haya áreas disponibles
	if (areas.isEmpty()) {
		std::cout << "No hay áreas disponibles para atender tiquetes." << std::endl;
		system("pause");
		return false;
	}

	// Selección del área
	int areaIndex = areaSelection(areas);  // Reutilizar la función de selección de área
	areas.goToPos(areaIndex);
	Area selectedArea = areas.getElement();

	// Mostrar las ventanillas disponibles y permitir seleccionar una
	selectedArea.getListaVentanillas().goToStart();
	std::cout << "* * * Ventanillas disponibles en el área " << selectedArea.getTituloArea() << " * * *" << std::endl;
	for (int i = 0; i < selectedArea.getListaVentanillas().getSize(); i++) {
		Ventanilla vent = selectedArea.getListaVentanillas().getElement();
		std::cout << i + 1 << ". Ventanilla " << vent.getCode() << std::endl;
		selectedArea.getListaVentanillas().next();
	}

	int ventanillaIndex;
	while (true) {
		std::cout << endl << "Seleccione el número de ventanilla a usar: ";
		std::cin >> ventanillaIndex;

		if (std::cin.fail() || ventanillaIndex < 1 || ventanillaIndex > selectedArea.getListaVentanillas().getSize()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << endl << "* Por favor, ingrese un número de ventanilla válido *" << std::endl;
		}
		else {
			break;
		}
	}

	// Acceder a la ventanilla seleccionada
	selectedArea.getListaVentanillas().goToPos(ventanillaIndex - 1);
	Ventanilla selectedVentanilla = selectedArea.getListaVentanillas().getElement();

	// Verificar si hay tiquetes en la cola del área seleccionada
	if (selectedArea.getColaTiquetes().isEmpty()) {
		std::cout << "* No hay usuarios en espera en la cola del área seleccionada *" << std::endl;
	}
	else {
		// Asignar el siguiente tiquete de la cola a la ventanilla
		try {
			selectedVentanilla.atenderTiquete(selectedArea.getColaTiquetes());  // Utiliza la función de `Ventanilla`
			selectedVentanilla.calcularEspera(selectedVentanilla.getTicket().getSeconds());
			selectedVentanilla.incrementarTiempoTotalEspera();
			selectedVentanilla.incrementarContadorTiquetes();
		}
		catch (const std::runtime_error& e) {
			cout << "Error: " << e.what() << endl;
		}

		// Actualizar la ventanilla en el área
		selectedArea.getListaVentanillas().setElement(selectedVentanilla);

		cout << endl << "* Tiquete atendido exitosamente en la ventanilla seleccionada *" << endl;
	}

	// Actualizar el área seleccionada en la lista de áreas
	areas.setElement(selectedArea);
	system("pause");
	return false;
}

// - - - - - FIN MENÚ ATENDER - - - - -

// - - - - - MENÚ PRINCIPAL - - - - -

void configurarConsola() {
	// Configurar la consola para aceptar caracteres UTF-8
	setlocale(LC_ALL, "es_ES.UTF-8");  // Configurar la localización a español (UTF-8)
	system("chcp 65001 > nul");        // Cambiar el código de página a UTF-8 en Windows
	std::locale::global(std::locale("es_ES.UTF-8"));  // Configurar la localización global
}

// Contiene sub-menús: Estado de Colas, Tiquetes, Atender,
// Administración y Estadísticas del sistema
void menuPrincipal(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
	ArrayList<Area>& areas) {
	configurarConsola();
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
						throw runtime_error("* No hay Áreas disponibles *");
					}
					system("cls");
					areas.goToStart();
					for (int i = 0; i < areas.getSize(); i++) {
						Area currentA = areas.getElement();
						// Se imprimen datos del área actual
						cout << endl << "Area: " << currentA.getTituloArea() << "  |  "
							<< "Codigo: " << currentA.getCodigo() << endl;
						// Se imprime su cola de tiquetes
						cout << endl << "	* Cola de Tiquetes *" << endl;
						cout << endl << "	- - Inicio de cola - -" << endl << endl;
						if (currentA.getColaTiquetes().getSize() != 0) {
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
						}
						else {
							cout << "	* No hay usuarios en espera *" << endl;
							cout << endl << "	- - Final de cola - -" << endl;
						}

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
					bool attending = atenderTiquete(areas);
					if (!attending) {
						continue;
					}
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
					cout << "* Estadísticas del Sistema *" << endl << endl;
					cout << "- - Información de Áreas - -" << endl << endl;
					if (areas.getSize() != 0) {
						areas.goToStart();
						for (int i = 0; i < areas.getSize(); i++) {
							int tiempoEsperaTotal = 0;
							int tiquetesAtendidos = 0;
							Area currentA = areas.getElement();
							// Se imprimen datos del área actual
							cout << "Área: " << currentA.getTituloArea() << endl << endl;

							currentA.getListaVentanillas().goToStart();
							for (int i = 0; i < currentA.getListaVentanillas().getSize(); i++) {
								Ventanilla currentV = currentA.getListaVentanillas().getElement();
								tiempoEsperaTotal = tiempoEsperaTotal + currentV.getTiempoTotalEspera();
								tiquetesAtendidos = tiquetesAtendidos + currentV.getContadorTiquetes();
								cout << "	-Ventanilla " << currentV.getCode() << ": " << endl;
								cout << "		Tiquetes atendidos: " << currentV.getContadorTiquetes() << endl << endl;
								currentA.getListaVentanillas().next();
							}
							if (tiquetesAtendidos == 0) {
								cout << endl << "	-Tiempo promedio de espera: 0 segundos" << endl;
							}
							else {
								double promedio = static_cast<double>(tiempoEsperaTotal) / tiquetesAtendidos;
								cout << endl << "	-Tiempo promedio de espera: " << promedio << " segundos" << endl;
							}
							cout << endl << "	-Tiquetes dispensados: " << currentA.getContadorTiquetes() << endl << endl;
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
