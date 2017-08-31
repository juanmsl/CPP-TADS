# ifndef __AVL_TREE_H__
# define __AVL_TREE_H__

# include <iostream>
# include <sstream>
# include <fstream>
# include <list>
# include <vector>
# include "NodeAVLTree.h"

template<class T>
class AVLTree {
	protected:
		int weight;
		NodeAVLTree<T>* root;
	
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		AVLTree();
		virtual ~AVLTree();
		
		// METODOS ENCAPSULADORES
		const int& getWeight() const;
		std::vector<T> getPostOrder();
		std::vector<T> getPreOrder();
		std::vector<T> getInOrder();

		// METODOS MODIFICADORES
		bool insert(const T& data);
		bool remove(const T& data);

		// METODOS DE ACCESO
		bool isEmpty() const;
		bool isNotEmpty() const;
		void printPreOrder(std::ostream& out) const;
		void printPostOrder(std::ostream& out) const;
		void printInOrder(std::ostream& out) const;
		void printLevels(std::ostream& out);
		std::list<T> getPathOf(const T& first);
		NodeAVLTree<T>* find(const T& data) const;
		AVLTree<T> copyPostOrder();
		AVLTree<T> copyPreOrder();
		AVLTree<T> copyInOrder();
		bool compare(AVLTree<T>& tree, std::ostream& out);
		void printAsPNG(const std::string& fileName);
		void printHeightsAsPNG(const std::string& fileName);
};

# include "AVLTree.hxx"

# endif
