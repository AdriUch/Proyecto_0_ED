#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <conio.h> // Para elección del menú

#include "LinkedPriorityQueue.h"
#include "MinHeap.h"
#include "HeapPriorityQueue.h"
#include "ArrayList.h"
#include "Usuario.h"
#include "Servicio.h"
#include "Tiquete.h"


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

// - - - - - MENÚS TIQUETES - - - - -
//sub menu de elegri servivicios

Servicio selectionService(List<Servicio>* serviciosDisponibles) {
    int menuSize = serviciosDisponibles->getSize();
    int currentSelection = 0;

    if (menuSize == 0) {
        throw runtime_error("No hay servicios disponibles.");
    }

    while (true) {
        system("cls");
        cout << "* * * Selección de Servicio * * *" << endl;

        // Mostrar el menú de servicios
        mostrarMenu(currentSelection, serviciosDisponibles, menuSize);

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
        else if (key == 13) { 
            // Seleccionar el servicio
            serviciosDisponibles->goToPos(currentSelection);
            Servicio servicioSeleccionado = serviciosDisponibles->getElement();
            cout << "Servicio seleccionado: " << servicioSeleccionado.getDescripcion() << endl;
            system("pause");
            return servicioSeleccionado; // Devuelve el servicio seleccionado
        }
    }
}

// Sub-menú de Tiquete. Menú de selección de Usuario y creación de Tiquete
bool selectionElements(PriorityQueue<Usuario>* userList, PriorityQueue<Tiquete>* ticketList, List<Servicio>* serviciosDisponibles) {
    List<Usuario>* arrayListUsers = new ArrayList<Usuario>(userList->getSize());
    int prioridadUser = 0;

    cout << "Seleccione el tipo de usuario que es: " << endl;

    while (!userList->isEmpty()) {
        arrayListUsers->append(userList->removeMin());
    }
    int menuSize = arrayListUsers->getSize();
    int currentSelection = 0;
    bool repeatMenu = true;
    while (repeatMenu) {
        system("cls");
        cout << "* * * Tipos de Usuarios * * *" << endl;
        mostrarMenu(currentSelection, arrayListUsers, menuSize);

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

            if (currentSelection < menuSize) {
                arrayListUsers->goToPos(currentSelection);
                prioridadUser = arrayListUsers->getElement().prioridadUser;

                // Selección de servicio
                Servicio servicioSeleccionado = selectionService(serviciosDisponibles);

                int prioridadServicio = 2; // Puedes ajustar esto según el servicio seleccionado
                string areaCode = "AC";
                string stringNumGlobal = std::to_string(numGlobal);
                numGlobal++;

                Tiquete ticket(prioridadUser, prioridadServicio, areaCode, stringNumGlobal);
                ticketList->insert(ticket, ticket.getFinalPriority());

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

    while (!arrayListUsers->isEmpty()) {
        Usuario user = arrayListUsers->remove();
        userList->insert(user, user.getPriority());
    }

    delete arrayListUsers;

    return false;
}

//Sub-menú del principal. Para pedir la creación de un tiquete.
bool menuTiquetes(PriorityQueue<Usuario>* userList, PriorityQueue<Tiquete>* ticketList) {
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
			listMenu->goToPos(currentSelection);
			if (listMenu->getElement() == "Creacion de Tiquete") {
				bool creacionTiquete = selectionElements(userList, ticketList);
				if (!creacionTiquete) {
					continue;
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

// - - - - - MENÚS ADMINISTRACIÓN - - - - -

// Sub-menú de Admin. Realiza las operaciones de los usuarios.
bool menuTipoUsuarios(PriorityQueue<Usuario>* userList) {
	const int menuSize = 3;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Agregar");
	listMenu->append("Eliminar");
	listMenu->append("Regresar");
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Menu de Usuarios * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

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
			listMenu->goToPos(currentSelection);
			if (listMenu->getElement() == "Agregar") {
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

				cout << endl << "* Accion realizada con exito *" << endl;
			}
			if (listMenu->getElement() == "Eliminar") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (currentSelection == menuSize - 1) {
				return false;
			}
			system("pause");
		}
	}
	delete listMenu;
}

//Sub-menú del principal. Se encarga de dar opciones para listas o colas de usuarios, áres y servicios
bool menuAdmin(PriorityQueue<Usuario>* userList) {
	const int menuSize = 4;
	List<string>* listMenu = new ArrayList<string>(menuSize);
	listMenu->append("Tipo de Usuario");
	listMenu->append("Areas");
	listMenu->append("Servicios disponibles");
	listMenu->append("Regresar");
	int currentSelection = 0;

	while (true) {
		system("cls");
		cout << "* * * Menu de Administracion * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

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
			listMenu->goToPos(currentSelection);
			if (listMenu->getElement() == "Tipo de Usuario") {
				bool tipoUsuariosMenu = menuTipoUsuarios(userList);
				if (!tipoUsuariosMenu) {
					continue;
				}
			}
			if (listMenu->getElement() == "Areas") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (listMenu->getElement() == "Servicios disponibles") {
				cout << "estoy aqui, wooo" << endl;
			}
			if (currentSelection == menuSize - 1) {
				return false;
			}
			system("pause");
		}
	}
	delete listMenu;
}



// - - - - - MENÚ PRINCIPAL - - - - -
void menuPrincipal(PriorityQueue<Usuario>* userList, PriorityQueue<Tiquete>* ticketList) {
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
		cout << "* * * Menu Principal * * *" << endl;
		mostrarMenu(currentSelection, listMenu, menuSize);

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
			listMenu->goToPos(currentSelection);
			if (listMenu->getElement() == "Estado de las colas") {
				cout << "estoy aqui, wooo";
			}
			if (listMenu->getElement() == "Tiquetes") {
				bool tiquetesMenu = menuTiquetes(userList, ticketList);
				if (!tiquetesMenu) {
					continue;
				}
			}
			if (listMenu->getElement() == "Atender") {
				cout << "estoy aqui, wooo";
			}
			if (listMenu->getElement() == "Administracion") {
				bool adminMenu = menuAdmin(userList);
				if (!adminMenu) {
					continue;
				}
			}
			if (listMenu->getElement() == "Estadisticas del sistema") {
				cout << "estoy aqui, wooo";
			}
			if (currentSelection == menuSize - 1) {
				break;
			}
			system("pause");
		}
	}
	delete listMenu;
}


int main() {
    PriorityQueue<Usuario>* colaUsuarios = new HeapPriorityQueue<Usuario>();
    PriorityQueue<Tiquete>* colaTiquetes = new HeapPriorityQueue<Tiquete>();


    List<Servicio>* serviciosDisponibles = new ArrayList<Servicio>(5);
    serviciosDisponibles->append(Servicio("Comprar Boleto", 1));
    serviciosDisponibles->append(Servicio("Cambiar Boleto", 2));
    serviciosDisponibles->append(Servicio("Solicitar Información", 3));
    serviciosDisponibles->append(Servicio("Realizar Reclamo", 4));

    
    menuPrincipal(colaUsuarios, colaTiquetes, serviciosDisponibles);

    delete colaUsuarios;
    delete colaTiquetes;
    delete serviciosDisponibles; // No olvides liberar la memoria
    return 0;
}


