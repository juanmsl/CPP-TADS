# include <iostream>
# include <stdlib.h>
# include <vector>
# include "SintaxBinaryTree.h"

int main(int argv, char *args[]){
	
	SintaxBinaryTree tree;

	try {
		tree.build("- * / 5 - 7 + 1 1 3 - + 2 + 1 * 4 3 * 2 8");
		tree.printInOrder(std::cout);
		std::cout<<" = "<<tree.evaluate()<<"\n";
	} catch (std::exception& err) {
		std::cerr<<err.what();
	}

	return 0;
}

