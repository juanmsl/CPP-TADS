# include "AVLTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

template<class T>
AVLTree<T>::AVLTree() {
	this->root = NULL;
	this->weight = 0;
}

template<class T>
AVLTree<T>::~AVLTree() {
	if(this->isNotEmpty()) {
		delete this->root;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

template<class T>
const int& AVLTree<T>::getWeight() const {
	return this->weight;
}

template<class T>
std::vector<T> AVLTree<T>::getPostOrder() {
	std::vector<T> vector;
	if(this->isNotEmpty()) {
		this->root->getPostOrder(vector);
	}
	return vector;
}

template<class T>
std::vector<T> AVLTree<T>::getPreOrder() {
	std::vector<T> vector;
	if(this->isNotEmpty()) {
		this->root->getPreOrder(vector);
	}
	return vector;
}

template<class T>
std::vector<T> AVLTree<T>::getInOrder() {
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
bool AVLTree<T>::insert(const T& data) {
	if(this->isEmpty()) {
		this->root = new NodeAVLTree<T>(data);
		this->weight++;
		return true;
	}else{
		if(this->root->insert(data)) {
			this->weight++;
			this->root = this->root->identifyRotation();
			return true;
		} else {
			return false;
		}
	}
}

template<class T>
bool AVLTree<T>::remove(const T& data) {
	if(this->isNotEmpty()) {
		if(this->root->getData() == data) {
			NodeAVLTree<T>* node = this->root;

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
					NodeAVLTree<T>* aux = node->getLeft();
					node->setLeft(aux->getLeft());
					aux->setLeft(NULL);
					aux->setRight(NULL);
					delete aux;
					this->weight--;
					this->root->updateHeight();
					this->root = this->root->identifyRotation();
					return true;
				} else { // SI EL IZQUIERDO NO ES EL IZQUIERDO MAYOR (4)(6)
					NodeAVLTree<T>* dadIM = node->getLeft();
					NodeAVLTree<T>* IM = dadIM->getRight();
					this->root->findLeftHigher(node, dadIM, IM);
					node->setLeft(node->getLeft()->identifyRotation());
					node->getLeft()->updateHeight();
					this->root = this->root->identifyRotation();
					this->root->updateHeight();
					this->weight--;
					return true;
				}
			}
		} else {
			if(this->root->remove(data)) {
				this->root = this->root->identifyRotation();
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
bool AVLTree<T>::isEmpty()  const {
	return this->root == NULL;
}

template<class T>
bool AVLTree<T>::isNotEmpty()  const {
	return this->root != NULL;
}

template<class T>
void AVLTree<T>::printPreOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printPreOrder(out);
	}
}

template<class T>
void AVLTree<T>::printPostOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printPostOrder(out);
	}
}

template<class T>
void AVLTree<T>::printInOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printInOrder(out);
	}
}

template<class T>
void AVLTree<T>::printLevels(std::ostream& out) {
	if(this->isNotEmpty()) {
		std::queue<NodeAVLTree<T>*> queue;
		std::queue<int> levels;
		levels.push(0);
		queue.push(this->root);
		int ant = 0;
		out<<"Nivel 0: ";
		while(!queue.empty()) {
			NodeAVLTree<T>* sub = queue.front();
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
std::list<T> AVLTree<T>::getPathOf(const T& first) {
	std::list<T> list;
	if(this->isNotEmpty()) {
		list = this->root->getPathOf(first);
	}
	return list;
}

template<class T>
NodeAVLTree<T>* AVLTree<T>::find(const T& data) const {
	if(this->isNotEmpty()) {
		return this->root->find(data);
	}else {
		return NULL;
	}
}

template<class T>
AVLTree<T> AVLTree<T>::copyPostOrder() {
	AVLTree<T> tree;
	std::vector<T> path = this->getPostOrder();
	for(int i=0; i < path.size(); i++) {
		tree.insert(path[i]);
	}
	return tree;
}

template<class T>
AVLTree<T> AVLTree<T>::copyPreOrder() {
	AVLTree<T> tree;
	std::vector<T> path = this->getPreOrder();
	for(int i=0; i < path.size(); i++) {
		tree.insert(path[i]);
	}
	return tree;
}

template<class T>
AVLTree<T> AVLTree<T>::copyInOrder() {
	AVLTree<T> tree;
	std::vector<T> path = this->getInOrder();
	for(int i=0; i < path.size(); i++) {
		tree.insert(path[i]);
	}
	return tree;
}

template<class T>
bool AVLTree<T>::compare(AVLTree<T>& tree, std::ostream& out) {
	if(tree.getWeight() == this->weight) {
		out << "El peso de ambos arboles es de: ["<<tree.getWeight()<<":"<<this->weight<<"]\n\n";
		bool post = this->getPostOrder() == tree.getPostOrder();
		bool pre = this->getPreOrder() == tree.getPreOrder();
		bool in = this->getInOrder() == tree.getInOrder();
		std::cout<<"PostOrder: ";(post)? std::cout<<"Son iguales\n": std::cout<<"No son iguales\n";
		std::cout<<"PreOrder: ";(pre)? std::cout<<"Son iguales\n": std::cout<<"No son iguales\n";
		std::cout<<"InOrder: ";(in)? std::cout<<"Son iguales\n": std::cout<<"No son iguales\n";
		return post && pre && in;
	} else {
		if(out != NULL) {
			out << "Los pesos de los arboles son diferentes\n";
			out << "Peso del arbol A: " << this->weight <<"\n";
			out << "Peso del arbol B: " << tree.getWeight() <<"\n";
		}
		return false;
	}
}

template<class T>
void AVLTree<T>::printAsPNG(const std::string& fileName) {
	std::stringstream str;
	str << "digraph g{\n";
	if(this->root != NULL) {
		if(this->root->getLeft() == NULL && this->root->getRight() == NULL) {
			str << "\t\"" << this->root->getData() << "\"";
		}
		else str << this->root->printAsPNG();
	}
	str << "}";

	std::ofstream s(std::string(fileName + ".dot").c_str());
	s<<str.str();
	std::stringstream sal;
	s.close();
	sal << "dot " << fileName + ".dot -Tpng > ";
	sal << fileName;
	std::system(sal.str().c_str());
	std::remove(std::string(fileName + ".dot").c_str());
	system(fileName.c_str());
}

template<class T>
void AVLTree<T>::printHeightsAsPNG(const std::string& fileName) {
	std::stringstream str;
	str << "digraph g{\n";
	if(this->root != NULL) {
		if(this->root->getLeft() == NULL && this->root->getRight() == NULL) {
			str	<< "\"" << this->root->getData() <<"\" [label=\""<<this->root->height<<"\"]" <<"\n";
			str << "\t\"" << this->root->getData() << "\"";
		}
		else str << this->root->printHeightsAsPNG();
	}
	str << "}";

	std::ofstream s(std::string(fileName + ".dot").c_str());
	s<<str.str();
	std::stringstream sal;
	s.close();
	sal << "dot " << fileName + ".dot -Tpng > ";
	sal << fileName;
	std::system(sal.str().c_str());
	std::remove(std::string(fileName + ".dot").c_str());
	system(fileName.c_str());
}