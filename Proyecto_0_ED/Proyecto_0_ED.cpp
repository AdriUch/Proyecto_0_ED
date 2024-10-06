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

// - - - - - MENÚS ADMINISTRACIÓN - - - - -

// Función para seleccionar un área desde la lista de áreas disponibles
Area selectionArea(ArrayList<Area>& areas) {
	if (areas.getSize() == 0) {
		cout << "No hay áreas disponibles para seleccionar." << endl;
		throw std::runtime_error("No hay áreas disponibles.");
	}

	int currentSelection = 0;
	int menuSize = areas.getSize();

	while (true) {
		system("cls");
		cout << "* * * Seleccione el área que desea * * *" << endl;

		// Mostrar el menú con la lista de áreas usando `mostrarMenu`
		mostrarMenu(currentSelection, &areas, menuSize);

		int key = _getch();
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
			return areas.getTheElement(currentSelection);
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
                Servicio service(serviceName, servicePriority, "AC");
                serviceList->append(service);

                cout << endl << "* Accion realizada con exito *" << endl;
            }
			//Britany agrego eliminar y reordenar
            if (listMenu->getElement() == "Eliminar") {
                int eliminarIndex;
                cout << "Ingrese el número de servicio que desea eliminar: ";
                cin >> eliminarIndex;

                if (eliminarIndex < 0 || eliminarIndex >= serviceList->getSize()) {
                    cout << "Índice fuera de rango." << endl;
                } else {
                    // Eliminar el servicio directamente
                    serviceList->goToPos(eliminarIndex);
                    serviceList->remove();
                    cout << "Servicio eliminado con éxito." << endl;
                }
            }
            if (listMenu->getElement() == "Reordenar") {
                cout << "* * * Reordenar Servicios * * *" << endl;

                // Lógica de reordenamiento de servicios
                int n = serviceList->getSize();
                bool swapped;

                do {
                    swapped = false;
                    for (int i = 0; i < n - 1; i++) {
                        serviceList->goToPos(i);
                        Servicio current = serviceList->getElement();
                        serviceList->goToPos(i + 1);
                        Servicio next = serviceList->getElement();

                        // Comparar por prioridad
                        if (current.getPrioridadServicio() > next.getPrioridadServicio()) {
                            // Intercambiar servicios
                            serviceList->goToPos(i);
                            serviceList->remove();
                            serviceList->insert(next);
                            serviceList->goToPos(i + 1);
                            serviceList->remove();
                            serviceList->insert(current);
                            swapped = true;
                        }
                    }
                    n--;
                } while (swapped);

                cout << "Servicios reordenados con éxito." << endl;
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



// Sub-menú de Admin. Realiza las operaciones de las áreas
bool menuAreas(ArrayList<Area>& areas) {
	int totalArea = areas.getSize();
	const int menuSize = 4;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Modificar cantidad de ventanillas");
	listMenu->append("Eliminar");
	listMenu->append("Regresar");
	int currentSelection = 0;

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
				cout << "Ingrese la cantidad de ventanillas: ";
				cin >> cantidadVentanillas;

				// Crear una nueva área usando el constructor adecuado
				Area nuevaArea(titulo, codigo, cantidadVentanillas, 5, 5);
				areas.append(nuevaArea);

				cout << "* Area agregada con exito *" << endl;
			}
			//Modifica algún área ya existente
			else if (listMenu->getElement() == "Modificar cantidad de ventanillas") {
				int areaIndex;
				cout << "Ingrese el indice del area a modificar: ";
				cin >> areaIndex;

				//Cambia la cantidad de ventanillas
				if (areaIndex >= 0 && areaIndex < areas.getSize()) {
					int nuevaCantidad;
					cout << "Cantidad actual: " << areas.getElement().getCantidadVentanillas() << endl;
					cout << "Ingrese la nueva cantidad: ";
					cin >> nuevaCantidad;
					areas.getElement().modificarVentanillas(nuevaCantidad);
					cout << "* Cantidad de ventanillas modificada con exito *" << endl;
				}
				else {
					cout << "Indice no valido." << endl;
				}
			}
			//Eliminar el área seleccionada
			else if (listMenu->getElement() == "Eliminar") {
				int areaIndex;
				cout << "Ingrese el indice del area a eliminar: ";
				cin >> areaIndex;

				if (areaIndex >= 0 && areaIndex < areas.getSize()) {
					string confirm;
					cout << "Seguro que desea eliminar esta area? (s/n): ";
					cin >> confirm;
					if (confirm == "s" || confirm == "S") {
						Area::eliminarArea(areas.getArray(), totalArea, areaIndex);
						cout << "* Area eliminada con exito *" << endl;
					}
				}
				else {
					cout << "Indice no valido." << endl;
				}
			}
			if (currentSelection == menuSize - 1) {
				return false;
			}
			system("pause");
		}
	}
	delete listMenu;
}

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
bool menuAdmin(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList, ArrayList<Area>& areas) {
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
		currentSelection = keysMenu(key, currentSelection, menuSize);

		if (key == 13) { // Enter
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
				bool areasMenu = menuAreas(areas);
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
// - - - - - FIN MENÚS ADMINISTRACIÓN - - - - -

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
		currentSelection = keysMenu(key, currentSelection, menuSize);
		
		if (key == 13) { // Enter
			// Seleccionar el servicio
			serviceList->goToPos(currentSelection);

			// Se modifica el contador de tiquetes del servicio
			Servicio service = serviceList->remove();
			service.incrementarContadorTiquetes();
			serviceList->insert(service);

			Servicio servicioSeleccionado = serviceList->getElement();
			return servicioSeleccionado; // Devuelve el servicio seleccionado
		}
	}
}

// Sub-menú de Tiquete. Menú de selección de Usuario y creación de Tiquete
bool selectionElements(PriorityQueue<Usuario>* userList, List<Servicio>* serviceList,
						ArrayList<Area>& areas) {
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
					Servicio servicioSeleccionado = selectionService(serviceList);

					string stringNumGlobal = std::to_string(numGlobal);
					numGlobal++;

					// Creación de tiquete
					Tiquete ticket(prioridadUser, servicioSeleccionado.getPrioridadServicio(), 
								servicioSeleccionado.getAreaCode(), stringNumGlobal);
					
					Area selectedArea;
					for (int i = 0; i < areas.getSize(); i++) {
						Area currentArea = areas.getElement();
						if (servicioSeleccionado.getAreaCode() == currentArea.getCodigo()) {
							selectedArea = currentArea;
						}
					}
					selectedArea.getColaTiquetes().insert(ticket, ticket.getFinalPriority());

					selectedArea.getColaTiquetes().print();

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
	listMenu->append("Administracion");
	listMenu->append("Estadisticas del sistema");
	listMenu->append("Salir");
	int currentSelection = 0;

	while (true) {
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
				cout << "estoy aqui, wooo";
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
			if (listMenu->getElement() == "Administracion") {
				bool adminMenu = menuAdmin(userList, serviceList, areas);
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
	std::locale::global(std::locale("es_ES.UTF-8"));  // Configurar la localización a español
	setlocale(LC_ALL, "");
	// Se crean todas las listas y colas que se van a utilizar
	PriorityQueue<Usuario>* colaUsuarios = new HeapPriorityQueue<Usuario>();
    List<Servicio>* listaServicios = new ArrayList<Servicio>();
	ArrayList<Area> areaArrayList;
	ArrayList<Area>& listaAreas = areaArrayList;

	menuPrincipal(colaUsuarios, listaServicios, listaAreas);

	colaUsuarios->print();
	listaServicios->print();
	
	// No olvides liberar la memoria
	delete colaUsuarios;
    delete listaServicios;
    return 0;
}
