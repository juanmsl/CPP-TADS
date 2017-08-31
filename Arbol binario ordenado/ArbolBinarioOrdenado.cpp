# include <iostream>
# include <stdlib.h>
# include <vector>
# include "BinaryTree.h"

int main(int argv, char *args[]){
	
	if(argv <= 1) {
		perror("Debe mandar argumentos enteros");
		return -1;
	}
	
	std::vector<int> numeros;
	for(int i=1; i<argv; i++) {
		numeros.push_back(atoi(args[i]));
	}
	
	BinaryTree<int> tree;
	
	for(int i=0; i<numeros.size(); i++) {
		tree.insert(numeros[i]);
	}

	std::cout<<"\nRecorrido in order:\n";
	tree.printInOrder(std::cout);
	
	std::cout<<"\nRecorrido pre order:\n";
	tree.printPreOrder(std::cout);

	std::cout<<"\nRecorrido post order:\n";
	tree.printPostOrder(std::cout);

	return 0;
}

