# ifndef __NODE_AVL_TREE_H__
# define __NODE_AVL_TREE_H__

# include <iostream>
# include <sstream>
# include <queue>
# include <list>
# include <vector>

template<class T>
class NodeAVLTree {
	protected:
		T data;
		public: int height;
		NodeAVLTree<T>* left;
		NodeAVLTree<T>* right;
		
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeAVLTree(const T& data);
		virtual ~NodeAVLTree();
		
		// METODOS ENCAPSULADORES
		T& getData();
		void setData(const T& data);
		NodeAVLTree<T>* getLeft();
		void setLeft(NodeAVLTree<T>* left);
		NodeAVLTree<T>* getRight();
		void setRight(NodeAVLTree<T>* right);
		void getPostOrder(std::vector<T>& vector);
		void getPreOrder(std::vector<T>& vector);
		void getInOrder(std::vector<T>& vector);

		// METODOS MODIFICADORES
		bool insert(const T& data);
		bool remove(const T& data);
		void updateHeight();
		void findLeftHigher(NodeAVLTree<T>* node, NodeAVLTree<T>* dadIM, NodeAVLTree<T>* IM);
		NodeAVLTree<T>* identifyRotation();
		NodeAVLTree<T>* rotationLeft(NodeAVLTree<T>* x);
		NodeAVLTree<T>* rotationRight(NodeAVLTree<T>* x);
		NodeAVLTree<T>* rotationLeftRight(NodeAVLTree<T>* x);
		NodeAVLTree<T>* rotationRightLeft(NodeAVLTree<T>* x);

		// METODOS DE ACCESO
		int equilibriumFactor();
		void printPreOrder(std::ostream& out) const;
		void printPostOrder(std::ostream& out) const;
		void printInOrder(std::ostream& out) const;
		std::list<T> getPathOf(const T& first);
		NodeAVLTree<T>* find(const T& data) const;
		const std::string printAsPNG();
		const std::string printHeightsAsPNG();
};

# include "NodeAVLTree.hxx"

# endif
