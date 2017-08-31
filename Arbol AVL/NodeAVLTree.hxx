# include "NodeAVLTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

template<class T>
NodeAVLTree<T>::NodeAVLTree(const T& data) {
	this->left = NULL;
	this->right = NULL;
	this->data = data;
	this->height = 1;
}

template<class T>
NodeAVLTree<T>::~NodeAVLTree() {
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
T& NodeAVLTree<T>::getData() {
	return this->data;
}

template<class T>
void NodeAVLTree<T>::setData(const T& data) {
	this->data = data;
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::getLeft() {
	return this->left;
}

template<class T>
void NodeAVLTree<T>::setLeft(NodeAVLTree<T>* left) {
	this->left = left;
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::getRight() {
	return this->right;
}

template<class T>
void NodeAVLTree<T>::setRight(NodeAVLTree<T>* right) {
	this->right = right;
}

template<class T>
void NodeAVLTree<T>::getPostOrder(std::vector<T>& vector) {
	if(this->left != NULL){
		this->left->getPostOrder(vector);
	}
	if(this->right != NULL){
		this->right->getPostOrder(vector);
	}
	vector.push_back(this->data);
}

template<class T>
void NodeAVLTree<T>::getPreOrder(std::vector<T>& vector) {
	vector.push_back(this->data);
	if(this->left != NULL){
		this->left->getPreOrder(vector);
	}
	if(this->right != NULL){
		this->right->getPreOrder(vector);
	}
}

template<class T>
void NodeAVLTree<T>::getInOrder(std::vector<T>& vector) {
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
bool NodeAVLTree<T>::insert(const T& data) {
	if(this->data > data) { // ME VOY POR LA IZQUIERDA
		if(this->left == NULL) {
			this->left = new NodeAVLTree<T>(data);
			updateHeight();
			return true;
		} else {
			if(this->left->insert(data)) {
				this->left = this->left->identifyRotation();
				updateHeight();
				return true;
			} else {
				return false;
			}
		}
	} else if(this->data < data) { // ME VOY POR LA DERECHA
		if(this->right == NULL) {
			this->right = new NodeAVLTree<T>(data);
			updateHeight();
			return true;
		} else {
			if(this->right->insert(data)) {
				this->right = this->right->identifyRotation();
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
bool NodeAVLTree<T>::remove(const T& data) {
	NodeAVLTree<T>* nodeToDelete;
	bool nodeToDeleteIsRightChild;
	if(this->data < data) {
		if(this->right == NULL) {
			return false;
		} else {
			if(this->right->getData() == data) {
				nodeToDelete = this->right;
				nodeToDeleteIsRightChild = true;
			} else {
				if(this->right->remove(data)) {
					this->right = this->right->identifyRotation();
					this->updateHeight();
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
				nodeToDelete = this->left;
				nodeToDeleteIsRightChild = false;
			} else {
				if(this->left->remove(data)) {
					this->left = this->left->identifyRotation();
					this->updateHeight();
					return true;
				} else {
					return false;
				}
			}
		}
	}

	if(nodeToDelete->left == NULL) { // NO TIENE IZQUIERDO PERO TIENE DERECHO, O, SI ES HOJA
		if(nodeToDeleteIsRightChild) this->right = nodeToDelete->right;
		else this->left = nodeToDelete->right;

		nodeToDelete->left = NULL;
		nodeToDelete->right = NULL;
		delete nodeToDelete;
		this->updateHeight();
		return true;
	} else { // SI TIENE IZQUIERDO

		if(nodeToDelete->left->right == NULL ) { // SI EL IZQUIERDO ES EL IZQUIERDO MAYOR
			nodeToDelete->setData(nodeToDelete->left->data);
			NodeAVLTree<T>* aux = nodeToDelete->left;
			nodeToDelete->left = aux->left;
			aux->left = NULL;
			aux->right = NULL;
			delete aux;			
			nodeToDelete->updateHeight();
		} else { // SI EL IZQUIERDO NO ES EL IZQUIERDO MAYOR
			NodeAVLTree<T>* dadIM = nodeToDelete->left;
			NodeAVLTree<T>* IM = dadIM->right;
			findLeftHigher(nodeToDelete, dadIM, IM);
			nodeToDelete->left = nodeToDelete->left->identifyRotation();
			nodeToDelete->updateHeight();
		}

		if(nodeToDeleteIsRightChild) this->right = this->right->identifyRotation();
		else this->left = this->left->identifyRotation();
		this->updateHeight();
		return true;
	}
}

template<class T>
void NodeAVLTree<T>::updateHeight() {
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
void NodeAVLTree<T>::findLeftHigher(NodeAVLTree<T>* node, NodeAVLTree<T>* dadIM, NodeAVLTree<T>* IM) {
	if(IM->right != NULL) {
		findLeftHigher(node, IM, dadIM->right);
	} else {
		node->setData(IM->data);
		dadIM->right = IM->left;
		IM->left = NULL;
		IM->right = NULL;
		delete IM;
	}
	if(dadIM->right != NULL){
		dadIM->right = dadIM->right->identifyRotation();
	}
	dadIM->updateHeight();
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::identifyRotation() {
	int factor = equilibriumFactor();
	if(factor <= (-2) || factor >= 2) {
		if(factor <= (-2)) {
			if(this->right->equilibriumFactor() <= 0) { // ROTACION IZQUIERDA
				return rotationLeft(this);
			} else if(this->right->equilibriumFactor() == 1) { // ROTACION IZQUIERDA-DERECHA
				return rotationLeftRight(this);
			}
		} else if(factor >= 2) {
			if(this->left->equilibriumFactor() >= 0) { // ROTACION DERECHA
				return rotationRight(this);
			} else if(this->left->equilibriumFactor() == (-1)) { // ROTACION DERECHA-IZQUIERDA
				return rotationRightLeft(this);
			}
		}
	}

	return this;
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::rotationLeft(NodeAVLTree<T>* x) {
	NodeAVLTree<T>* y = x->right;
	NodeAVLTree<T>* b = y->left;
	// -------------------------
	y->left = x;
	x->right = b;
	// -------------------------
	x->updateHeight();
	y->updateHeight();
	return y;
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::rotationRight(NodeAVLTree<T>* x) {
	NodeAVLTree<T>* y = x->left;
	NodeAVLTree<T>* b = y->right;
	// -------------------------
	y->right = x;
	x->left = b;
	// -------------------------
	x->updateHeight();
	y->updateHeight();
	return y;
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::rotationLeftRight(NodeAVLTree<T>* x) {
	NodeAVLTree<T>* y = x->right;
	NodeAVLTree<T>* z = y->left;
	NodeAVLTree<T>* c = z->left;
	NodeAVLTree<T>* d = z->right;
	// -------------------------
	z->left = x;
	z->right = y;
	x->right = c;
	y->left = d;
	// -------------------------
	x->updateHeight();
	y->updateHeight();
	z->updateHeight();
	return z;
}

template<class T>
NodeAVLTree<T>* NodeAVLTree<T>::rotationRightLeft(NodeAVLTree<T>* x) {
	NodeAVLTree<T>* y = x->left;
	NodeAVLTree<T>* z = y->right;
	NodeAVLTree<T>* c = z->left;
	NodeAVLTree<T>* d = z->right;
	// -------------------------
	z->left = y;
	z->right = x;
	y->right = c;
	x->left = d;
	// -------------------------
	x->updateHeight();
	y->updateHeight();
	z->updateHeight();
	return z;
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/

template<class T>
int NodeAVLTree<T>::equilibriumFactor() {
	int l = (this->left == NULL)? 0 : this->left->height;
	int r = (this->right == NULL)? 0 : this->right->height;
	int factor = l - r;
	return factor;
}

template<class T>
void NodeAVLTree<T>::printPreOrder(std::ostream& out) const {
	out<<"["<<this->data<<"] ";
	if(this->left != NULL){
		this->left->printPreOrder(out);
	}
	if(this->right != NULL){
		this->right->printPreOrder(out);
	}
}

template<class T>
void NodeAVLTree<T>::printPostOrder(std::ostream& out) const {
	if(this->left != NULL){
		this->left->printPostOrder(out);
	}
	if(this->right != NULL){
		this->right->printPostOrder(out);
	}
	out<<"["<<this->data<<"] ";
}

template<class T>
void NodeAVLTree<T>::printInOrder(std::ostream& out) const {
	if(this->left != NULL){
		this->left->printInOrder(out);
	}
	out<<"["<<this->data<<"] ";
	if(this->right != NULL){
		this->right->printInOrder(out);
	}
}

template<class T>
std::list<T> NodeAVLTree<T>::getPathOf(const T& first) {
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
NodeAVLTree<T>* NodeAVLTree<T>::find(const T& data) const {
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

template<class T>
const std::string NodeAVLTree<T>::printAsPNG() {
	std::stringstream str;

	if(this->left != NULL)	{
		str	<< "\"" << this->data <<"\"->\""<< this->left->data << "\""<< "[shape=box,label=L]" <<"\n"
		<< this->left->printAsPNG();
	}

	if(this->right != NULL) {
		str	<< "\"" << this->data <<"\"->\""<< this->right->data << "\""<< "[shape=box,label=R]" <<"\n"
		<< this->right->printAsPNG();
	}

	return str.str();
}

template<class T>
const std::string NodeAVLTree<T>::printHeightsAsPNG() {
	std::stringstream str;

	if(this->left != NULL)	{
		str	<< "\"" << this->data <<"\" [label=\""<<this->height<<"\"]" <<"\n";
		str	<< "\"" << this->left->data <<"\" [label=\""<<this->left->height<<"\"]" <<"\n";
		str	<< "\"" << this->data <<"\"->\""<< this->left->data << "\""<< "[shape=box,label=L]" <<"\n"
		<< this->left->printHeightsAsPNG();
	}

	if(this->right != NULL) {
		str	<< "\"" << this->data <<"\" [label=\""<<this->height<<"\"]" <<"\n";
		str	<< "\"" << this->right->data <<"\" [label=\""<<this->right->height<<"\"]" <<"\n";
		str	<< "\"" << this->data <<"\"->\""<< this->right->data << "\""<< "[shape=box,label=R]" <<"\n"
		<< this->right->printHeightsAsPNG();
	}

	return str.str();
}