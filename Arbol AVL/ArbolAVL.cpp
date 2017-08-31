# include <iostream>
# include <stdlib.h>
# include <vector>
# include "AVLTree.h"

int main(){
	
	AVLTree<int>

	char ins;
	int number;

	while(std::cin>>ins>>number){
		if(ins == 'A') tree.insert(number);
		else if(ins == 'E') tree.remove(number);
		else if(ins == 'Q') break;
		std::cout<<"\n";
		tree.printLevels(std::cout);
		std::cout<<"\n\n";
		tree.printAsPNG("D.png");
		tree.printHeightsAsPNG("DH.png");
	}



	return 0;
}

