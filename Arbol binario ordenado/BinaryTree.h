# ifndef __BINARY_TREE_H__
# define __BINARY_TREE_H__

# include <iostream>
# include <list>
# include <vector>
# include "NodeBinaryTree.h"

template<class T>
class BinaryTree {
	protected:
		int weight;
		NodeBinaryTree<T>* root;

	public:
		// CONSTRUCTOR Y DESTRUCTOR
		BinaryTree();
		virtual ~BinaryTree();

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
		NodeBinaryTree<T>* find(const T& data) const;
		BinaryTree<T> copyPostOrder();
		BinaryTree<T> copyPreOrder();
		BinaryTree<T> copyInOrder();
		bool compare(BinaryTree<T>& tree);
};

# include "BinaryTree.hxx"

# endif
