# include "BinaryTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

template<class T>
BinaryTree<T>::BinaryTree() {
	this->root = NULL;
}

template<class T>
BinaryTree<T>::~BinaryTree() {
	if(this->isNotEmpty()) {
		delete this->root;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

template<class T>
const int& BinaryTree<T>::getWeight() const {
	return this->weight;
}

template<class T>
std::vector<T> BinaryTree<T>::getPostOrder() {
	std::vector<T> vector;
	if(this->isNotEmpty()) {
		this->root->getPostOrder(vector);
	}
	return vector;
}

template<class T>
std::vector<T> BinaryTree<T>::getPreOrder() {
	std::vector<T> vector;
	if(this->isNotEmpty()) {
		this->root->getPreOrder(vector);
	}
	return vector;
}

template<class T>
std::vector<T> BinaryTree<T>::getInOrder() {
	std::vector<T> vector;
	if(this->isNotEmpty()) {
		this->root->getInOrder(vector);
	}
	return vector;
}

/*************************************************************

					METODOS MODIFICADORES

*************************************************************/

template<class T>
bool BinaryTree<T>::insert(const T& data) {
	if(this->isEmpty()) {
		this->root = new NodeBinaryTree<T>(data);
		this->weight++;
		return true;
	}else{
		if(this->root->insert(data)) {
			this->weight++;
			return true;
		} else {
			return false;
		}
	}
}

template<class T>
bool BinaryTree<T>::remove(const T& data) {
	if(this->isNotEmpty()) {
		if(this->root->getData() == data) {
			NodeBinaryTree<T>* node = this->root;

			if(node->getLeft() == NULL) { // NO TIENE IZQUIERDO PERO TIENE DERECHO, O, SI ES HOJA (1)(2)
				this->root = node->getRight();
				node->setLeft(NULL);
				node->setRight(NULL);
				delete node;
				this->weight--;
				return true;
			} else { // SI TIENE IZQUIERDO (3)(4)(5)(6)
				if(node->getLeft()->getRight() == NULL ) { // SI EL IZQUIERDO ES EL IZQUIERDO MAYOR (3)(5)
					node->setData(node->getLeft()->getData());
					NodeBinaryTree<T>* aux = node->getLeft();
					node->setLeft(aux->getLeft());
					aux->setLeft(NULL);
					aux->setRight(NULL);
					delete aux;
					this->weight--;
					return true;
				} else { // SI EL IZQUIERDO NO ES EL IZQUIERDO MAYOR (4)(6)
					NodeBinaryTree<T>* dadIM = node->getLeft();
					NodeBinaryTree<T>* IM = dadIM->getRight();
					this->root->findLeftHigher(node, dadIM, IM);
					this->weight--;
					return true;
				}
			}
		} else {
			if(this->root->remove(data)) {
				this->weight--;
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/

template<class T>
bool BinaryTree<T>::isEmpty()  const {
	return this->root == NULL;
}

template<class T>
bool BinaryTree<T>::isNotEmpty()  const {
	return this->root != NULL;
}

template<class T>
void BinaryTree<T>::printPreOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printPreOrder(out);
	}
}

template<class T>
void BinaryTree<T>::printPostOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printPostOrder(out);
	}
}

template<class T>
void BinaryTree<T>::printInOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printInOrder(out);
	}
}

template<class T>
void BinaryTree<T>::printLevels(std::ostream& out) {
	if(this->isNotEmpty()) {
		std::queue<NodeBinaryTree<T>*> queue;
		std::queue<int> levels;
		levels.push(0);
		queue.push(this->root);
		int ant = 0;
		out<<"Nivel 0: ";
		while(!queue.empty()) {
			NodeBinaryTree<T>* sub = queue.front();
			int level = levels.front();
			levels.pop();
			queue.pop();
			if(level > ant) {
				out<<"\nNivel "<<level<<": ";
				ant = level;
			}
			out<<"["<<sub->getData()<<"] ";
			if(sub->getLeft() != NULL) {
				queue.push(sub->getLeft());
				levels.push(level+1);
			}
			if(sub->getRight() != NULL) {
				queue.push(sub->getRight());
				levels.push(level+1);
			}
		}
	} else {
		out<<"Arbol esta vacio";
	}
}

template<class T>
std::list<T> BinaryTree<T>::getPathOf(const T& first) {
	std::list<T> list;
	if(this->isNotEmpty()) {
		list = this->root->getPathOf(first);
	}
	return list;
}

template<class T>
NodeBinaryTree<T>* BinaryTree<T>::find(const T& data) const {
	if(this->isNotEmpty()) {
		return this->root->find(data);
	}else {
		return NULL;
	}
}

template<class T>
BinaryTree<T> BinaryTree<T>::copyPostOrder() {
	BinaryTree<T> tree;
	std::vector<T> path = this->getPostOrder();
	for(int i=0; i < path.size(); i++) {
		tree.insert(path[i]);
	}
	return tree;
}

template<class T>
BinaryTree<T> BinaryTree<T>::copyPreOrder() {
	BinaryTree<T> tree;
	std::vector<T> path = this->getPreOrder();
	for(int i=0; i < path.size(); i++) {
		tree.insert(path[i]);
	}
	return tree;
}

template<class T>
BinaryTree<T> BinaryTree<T>::copyInOrder() {
	BinaryTree<T> tree;
	std::vector<T> path = this->getInOrder();
	for(int i=0; i < path.size(); i++) {
		tree.insert(path[i]);
	}
	return tree;
}

template<class T>
bool BinaryTree<T>::compare(BinaryTree<T>& tree) {
	if(tree.getWeight() == this->weight) {
		bool post = this->getPostOrder() == tree.getPostOrder();
		bool pre = this->getPreOrder() == tree.getPreOrder();
		bool in = this->getInOrder() == tree.getInOrder();
		std::cout<<"PostOrder: ";(post)? std::cout<<"Son iguales\n": std::cout<<"No son iguales\n";
		std::cout<<"PreOrder: ";(pre)? std::cout<<"Son iguales\n": std::cout<<"No son iguales\n";
		std::cout<<"InOrder: ";(in)? std::cout<<"Son iguales\n": std::cout<<"No son iguales\n";
		return post && pre && in;
	}
	return false;
}
