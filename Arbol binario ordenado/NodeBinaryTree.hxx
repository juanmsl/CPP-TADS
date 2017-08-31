# include "NodeBinaryTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

template<class T>
NodeBinaryTree<T>::NodeBinaryTree(const T& data) {
	this->left = NULL;
	this->right = NULL;
	this->data = data;
	this->height = 1;
}

template<class T>
NodeBinaryTree<T>::~NodeBinaryTree() {
	if(this->left != NULL){
		delete this->left;
	}
	if(this->right != NULL){
		delete this->right;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

template<class T>
void NodeBinaryTree<T>::setData(const T& data) {
	this->data = data;
}

template<class T>
T& NodeBinaryTree<T>::getData() {
	return this->data;
}

template<class T>
NodeBinaryTree<T>* NodeBinaryTree<T>::getLeft() {
	return this->left;
}

template<class T>
void NodeBinaryTree<T>::setLeft(NodeBinaryTree<T>* left) {
	this->left = left;
}

template<class T>
NodeBinaryTree<T>* NodeBinaryTree<T>::getRight() {
	return this->right;
}

template<class T>
void NodeBinaryTree<T>::setRight(NodeBinaryTree<T>* right) {
	this->right = right;
}

template<class T>
void NodeBinaryTree<T>::getPostOrder(std::vector<T>& vector) {
	if(this->left != NULL){
		this->left->getPostOrder(vector);
	}
	if(this->right != NULL){
		this->right->getPostOrder(vector);
	}
	vector.push_back(this->data);
}

template<class T>
void NodeBinaryTree<T>::getPreOrder(std::vector<T>& vector) {
	vector.push_back(this->data);
	if(this->left != NULL){
		this->left->getPreOrder(vector);
	}
	if(this->right != NULL){
		this->right->getPreOrder(vector);
	}
}

template<class T>
void NodeBinaryTree<T>::getInOrder(std::vector<T>& vector) {
	if(this->left != NULL){
		this->left->getInOrder(vector);
	}
	vector.push_back(this->data);
	if(this->right != NULL){
		this->right->getInOrder(vector);
	}
}

/*************************************************************

					METODOS MODIFICADORES

*************************************************************/

template<class T>
bool NodeBinaryTree<T>::insert(const T& data) {
	if(this->data > data) { // ME VOY POR LA IZQUIERDA
		if(this->left == NULL) {
			this->left = new NodeBinaryTree<T>(data);
			updateHeight();
			return true;
		} else {
			if(this->left->insert(data)) {
				updateHeight();
				return true;
			} else {
				return false;
			}
		}
	} else if(this->data < data) { // ME VOY POR LA DERECHA
		if(this->right == NULL) {
			this->right = new NodeBinaryTree<T>(data);
			updateHeight();
			return true;
		} else {
			if(this->right->insert(data)) {
				updateHeight();
				return true;
			} else {
				return false;
			}
		}
	} else { // SI EL DATO YA ESTA AGREGADO
		return false;
	}
}

template<class T>
bool NodeBinaryTree<T>::remove(const T& data) {
	NodeBinaryTree<T>* node;
	bool r;
	if(this->data < data) {
		if(this->right == NULL) {
			return false;
		} else {
			if(this->right->getData() == data) {
				node = this->right;
				r = true;
			} else {
				if(this->right->remove(data)) {
					updateHeight();
					return true;
				} else {
					return false;
				}
			}
		}
	} else if (this->data > data) {
		if(this->left == NULL) {
			return false;
		} else {
			if(this->left->getData() == data) {
				node = this->left;
				r = false;
			} else {
				if(this->left->remove(data)) {
					updateHeight();
					return true;
				} else {
					return false;
				}
			}
		}
	}

	if(node->left == NULL) { // NO TIENE IZQUIERDO PERO TIENE DERECHO, O, SI ES HOJA (1)(2)
		if(r) {
			this->right = node->right;
		} else {
			this->left = node->right;
		}
		node->left = NULL;
		node->right = NULL;
		delete node;
		updateHeight();
		return true;
	} else { // SI TIENE IZQUIERDO (3)(4)(5)(6)
		if(node->left->right == NULL ) { // SI EL IZQUIERDO ES EL IZQUIERDO MAYOR (3)(5)
			node->setData(node->left->data);
			NodeBinaryTree<T>* aux = node->left;
			node->left = aux->left;
			aux->left = NULL;
			aux->right = NULL;
			delete aux;
			node->updateHeight();
			updateHeight();
			return true;
		} else { // SI EL IZQUIERDO NO ES EL IZQUIERDO MAYOR (4)(6)
			NodeBinaryTree<T>* dadIM = node->left;
			NodeBinaryTree<T>* IM = dadIM->right;
			findLeftHigher(node, dadIM, IM);
			node->updateHeight();
			updateHeight();
			return true;
		}
	}
}

template<class T>
void NodeBinaryTree<T>::updateHeight() {
	if(this->left != NULL && this->right != NULL) { // AMBOS HIJOS

		if(this->left->height > this->right->height) {
			this->height = (1 + this->left->height);
		} else {
			this->height = (1 + this->right->height);
		}

	} else if(this->left == NULL && this->right != NULL) { // HIJO DERECHO

		this->height = (1 + this->right->height);

	} else if(this->left != NULL && this->right == NULL) { // HIJO IZQUIERDO

		this->height = (1 + this->left->height);

	} else if(this->left == NULL && this->right == NULL) { // SIN HIJOS
		this->height = 1;
	}
}

template<class T>
void NodeBinaryTree<T>::findLeftHigher(NodeBinaryTree<T>* node, NodeBinaryTree<T>* dadIM, NodeBinaryTree<T>* IM) {
	if(IM->right != NULL) {
		findLeftHigher(node, IM, dadIM->right);
	} else {
		node->setData(IM->data);
		dadIM->right = IM->left;
		IM->left = NULL;
		IM->right = NULL;
		delete IM;
	}
	dadIM->updateHeight();
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/

template<class T>
void NodeBinaryTree<T>::printPreOrder(std::ostream& out) const {
	out<<"["<<this->data<<"] ";
	if(this->left != NULL){
		this->left->printPreOrder(out);
	}
	if(this->right != NULL){
		this->right->printPreOrder(out);
	}
}

template<class T>
void NodeBinaryTree<T>::printPostOrder(std::ostream& out) const {
	if(this->left != NULL){
		this->left->printPostOrder(out);
	}
	if(this->right != NULL){
		this->right->printPostOrder(out);
	}
	out<<"["<<this->data<<"] ";
}

template<class T>
void NodeBinaryTree<T>::printInOrder(std::ostream& out) const {
	if(this->left != NULL){
		this->left->printInOrder(out);
	}
	out<<"["<<this->data<<"] ";
	if(this->right != NULL){
		this->right->printInOrder(out);
	}
}

template<class T>
std::list<T> NodeBinaryTree<T>::getPathOf(const T& first) {
	std::list<T> path;
	if(this->data < first){
		if(this->right != NULL) {
			path = this->right->getPathOf(first);
			if(path.size() > 0) {
				path.push_front(this->data);
				return path;
			}
		}
	} else if(this->data > first) {
		if(this->left != NULL) {
			path = this->left->getPathOf(first);
			if(path.size() > 0) {
				path.push_front(this->data);
				return path;
			}
		}
	} else {
		path.push_front(this->data);
		return path;
	}
	return path;
}

template<class T>
NodeBinaryTree<T>* NodeBinaryTree<T>::find(const T& data) const {
	if(this->data < data){
		if(this->right != NULL) {
			return this->right->find(data);
		} else {
			return NULL;
		}
	} else if(this->data > data) {
		if(this->left != NULL) {
			return this->left->find(data);
		} else {
			return NULL;
		}
	} else {
		return this;
	}
}