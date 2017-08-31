# ifndef __SINTAX_BINARY_TREE_H__
# define __SINTAX_BINARY_TREE_H__

# include <iostream>
# include <vector>
# include <string>
# include <queue>
# include <sstream>
# include "NodeSintaxBinaryTree.h"

class SintaxBinaryTree {
	protected:
		NodeSintaxBinaryTree* root;
	
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		SintaxBinaryTree();
		virtual ~SintaxBinaryTree();
		
		// METODOS ENCAPSULADORES
		std::vector<std::string> getPostOrder();
		std::vector<std::string> getPreOrder();
		std::vector<std::string> getInOrder();

		// METODOS MODIFICADORES
		bool build(const std::string& data);
		double evaluate();
		double reduce();
		void clear();

		// METODOS DE ACCESO
		bool isEmpty() const;
		bool isNotEmpty() const;
		void printPreOrder(std::ostream& out) const;
		void printPostOrder(std::ostream& out) const;
		void printInOrder(std::ostream& out) const;
		void printLevels(std::ostream& out);
};

# include "SintaxBinaryTree.hxx"

# endif
