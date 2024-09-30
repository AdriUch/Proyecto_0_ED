#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "LinkedPriorityQueue.h"
#include "MinHeap.h"
#include "HeapPriorityQueue.h"
#include "Usuario.h"
#include "Tiquete.h"

using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::to_string;

int main() {
	PriorityQueue<Usuario>* colaUsuarios = new HeapPriorityQueue<Usuario>();
	PriorityQueue<Tiquete>* colaTiquetes = new HeapPriorityQueue<Tiquete>();
	
	Usuario user(0, "hello");
	Usuario user2(2, "todo");
	Usuario user3(1, "bien");
	Usuario user4(4, "por");
	Usuario user5(0, "aqui");
	Usuario user6(3, "?");

	colaUsuarios->insert(user, user.getPriority());
	colaUsuarios->insert(user2, user2.getPriority());
	colaUsuarios->insert(user3, user3.getPriority());
	colaUsuarios->insert(user4, user4.getPriority());
	colaUsuarios->insert(user5, user5.getPriority());
	colaUsuarios->insert(user6, user6.getPriority());
	colaUsuarios->print();


	Tiquete ticket(user.getPriority(), 1, "A", to_string(100));
	Tiquete ticket2(user2.getPriority(), 2, "B", to_string(101));
	Tiquete ticket3(user3.getPriority(), 1,  "C", to_string(102));
	Tiquete ticket4(user4.getPriority(), 3, "A", to_string(103));
	Tiquete ticket5(user5.getPriority(), 1,  "C", to_string(104));
	Tiquete ticket6(user6.getPriority(), 4, "C", to_string(105));

	colaTiquetes->insert(ticket, ticket.getFinalPriority());
	colaTiquetes->insert(ticket2, ticket2.getFinalPriority());
	colaTiquetes->insert(ticket3, ticket3.getFinalPriority());
	colaTiquetes->insert(ticket4, ticket4.getFinalPriority());
	colaTiquetes->insert(ticket5, ticket5.getFinalPriority());
	colaTiquetes->insert(ticket6, ticket6.getFinalPriority());
	colaTiquetes->print();

	delete colaUsuarios;
	delete colaTiquetes;

	return 0;
}
