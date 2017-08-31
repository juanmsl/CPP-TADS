# include <iostream>
# include <list>
# include <string>
# include "CircleList.h"

int main() {
	
	CircleList<int> list; // FIRST: NULL - LAST: NULL - CURRENT: NULL
	list.insert(1); // FIRST: 1 - LAST: 1 - CURRENT: 1
	list.insert(2); // FIRST: 1 - LAST: 2 - CURRENT: 2
	list.insert(3); // FIRST: 1 - LAST: 3 - CURRENT: 3
	list.insert(4); // FIRST: 1 - LAST: 4 - CURRENT: 4
	list.insert(5); // FIRST: 1 - LAST: 5 - CURRENT: 5
	list.insert(6); // FIRST: 1 - LAST: 6 - CURRENT: 6

	// AQUI EL CURRENT DEBERIA SER EL NUMERO 6, YA QUE AL USAR EL METODO INSERT()
	// EL INSERTA EL DATO DONDE SE ENCUENTRE EL CURRENT Y ESE NUEVO DATO SERA EN NUEVO CURRENT
	std::cout<<"First: "<<list.first()<<" - Last: "<<list.last()<<" - Actual: "<<list.current()<<"\n\n";

	std::cout<<"Recorrido de fin a inicio con iteradores:\n";

	CircleList<int>::iterator it = list.getFirst();

	for(int i = list.size(); i > 0; it++, i--) {
		CircleList<int>::iterator aux = it;
		std::cout<<"["<<*it<<"] ";
		it--;
		list.remove(aux);

	}
	

	return 0;
}

