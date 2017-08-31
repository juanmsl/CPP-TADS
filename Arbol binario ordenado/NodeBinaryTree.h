# ifndef __NODE_BINARY_TREE_H__
# define __NODE_BINARY_TREE_H__

# include <iostream>
# include <queue>
# include <list>
# include <vector>

template<class T>
class NodeBinaryTree {
	protected:
		T data;
		int height;
		NodeBinaryTree<T>* left;
		NodeBinaryTree<T>* right;
		
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeBinaryTree(const T& data);
		virtual ~NodeBinaryTree();
		
		// METODOS ENCAPSULADORES
		T& getData();
		void setData(const T& data);
		NodeBinaryTree<T>* getLeft();
		void setLeft(NodeBinaryTree<T>* left);
		NodeBinaryTree<T>* getRight();
		void setRight(NodeBinaryTree<T>* right);
		void getPostOrder(std::vector<T>& vector);
		void getPreOrder(std::vector<T>& vector);
		void getInOrder(std::vector<T>& vector);

		// METODOS MODIFICADORES
		bool insert(const T& data);
		bool remove(const T& data);
		void updateHeight();
		void findLeftHigher(NodeBinaryTree<T>* node, NodeBinaryTree<T>* dadIM, NodeBinaryTree<T>* IM);

		// METODOS DE ACCESO
		void printPreOrder(std::ostream& out) const;
		void printPostOrder(std::ostream& out) const;
		void printInOrder(std::ostream& out) const;
		std::list<T> getPathOf(const T& first);
		NodeBinaryTree<T>* find(const T& data) const;
};

# include "NodeBinaryTree.hxx"

# endif
