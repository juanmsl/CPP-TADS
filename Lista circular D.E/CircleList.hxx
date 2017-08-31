# include "CircleList.h"

/*************************************************************

					CLASE ITERATOR

*************************************************************/

	/*************************************************************
						CONSTRUCTOR Y DESTRUCTOR
	*************************************************************/
	template<class T>
	CircleList<T>::iterator::iterator(NodeCircleList<T>* pointer) {
		this->m_it = pointer;
	}

	template<class T>
	CircleList<T>::iterator::iterator(){}

	template<class T>
	CircleList<T>::iterator::~iterator(){}

	/*************************************************************
						SOBRECARGA DE OPERADORES
	*************************************************************/
	template<class T>
	NodeCircleList<T>* CircleList<T>::iterator::operator ++ () {
		m_it = m_it->getNext();
		return m_it;
	}

	template<class T>
	NodeCircleList<T>* CircleList<T>::iterator::operator ++ (int) {
		NodeCircleList<T>* i = m_it;
		m_it = m_it->getNext();
		return i;
	}

	template<class T>
	NodeCircleList<T>* CircleList<T>::iterator::operator -- () {
		m_it = m_it->getBack();
		return m_it;
	}

	template<class T>
	NodeCircleList<T>* CircleList<T>::iterator::operator -- (int) {
		NodeCircleList<T>* i = m_it;
		m_it = m_it->getBack();
		return i;
	}

	template<class T>
	T& CircleList<T>::iterator::operator* () {
		return m_it->getData();
	}

	template<class T>
	T* CircleList<T>::iterator::operator->() {
		return &(m_it->getData());
	}

	template<class T>
	bool CircleList<T>::iterator::operator == (const iterator& itt) {
		return m_it == itt.m_it;
	}

	template<class T>
	bool CircleList<T>::iterator::operator != (const iterator& itt) {
		return m_it != itt.m_it;
	}

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

template<class T>
CircleList<T>::CircleList() {
	this->m_first = NULL;
	this->m_last = NULL;
	this->m_current = NULL;
	this->m_size = 0;
}

template<class T>
CircleList<T>::~CircleList() {
	if(this->isNotEmpty()) {
		this->m_last->setNext(NULL);
		delete this->m_first;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

template<class T>
const int& CircleList<T>::size() const {
	return this->m_size;
}

template<class T>
T& CircleList<T>::first() const {
	return this->m_first->getData();
}

template<class T>
T& CircleList<T>::last() const {
	return this->m_last->getData();
}

template<class T>
T& CircleList<T>::current() const {
	return this->m_current->getData();
}

template<class T>
typename CircleList<T>::iterator CircleList<T>::getFirst() const {
	return iterator(this->m_first);
}

template<class T>
typename CircleList<T>::iterator CircleList<T>::getLast() const {
	return iterator(this->m_last);
}

template<class T>
typename CircleList<T>::iterator CircleList<T>::getCurrent() const {
	return iterator(this->m_current);
}

/*************************************************************

					METODOS MODIFICADORES

*************************************************************/

template<class T>
bool CircleList<T>::insert(const T& data) {
	if(this->m_current == NULL) { // LISTA VACIA
		this->m_current = new NodeCircleList<T>(data, NULL, NULL);
		this->m_first = this->m_current;
		this->m_last = this->m_current;
		this->m_size++;
		return true;
	} else  {
		NodeCircleList<T> *newNode = new NodeCircleList<T>(data, this->m_current->getNext(), this->m_current);
		newNode->getBack()->setNext(newNode);
		newNode->getNext()->setBack(newNode);
		if(this->m_last == this->m_current) {
			this->m_last = newNode;
		}
		this->m_current = newNode;
		this->m_size++;
		return true;
	}
}

template<class T>
bool CircleList<T>::insertAtFirst(const T& data) {
	if(this->m_first == NULL) {
		this->m_first = new NodeCircleList<T>(data, NULL, NULL);
		this->m_current = this->m_first;
		this->m_last = this->m_current;
		this->m_size++;
		return true;
	} else {
		NodeCircleList<T> *newNode = new NodeCircleList<T>(data, this->m_first, this->m_last);
		newNode->getBack()->setNext(newNode);
		newNode->getNext()->setBack(newNode);
		this->m_first = newNode;
		this->m_size++;
		return true;
	}
}

template<class T>
bool CircleList<T>::insertAtLast(const T& data) {
	if(this->m_first == NULL) {
		this->m_last = new NodeCircleList<T>(data, NULL, NULL);
		this->m_current = this->m_last;
		this->m_first = this->m_current;
		this->m_size++;
		return true;
	} else {
		NodeCircleList<T> *newNode = new NodeCircleList<T>(data, this->m_first, this->m_last);
		newNode->getBack()->setNext(newNode);
		newNode->getNext()->setBack(newNode);
		this->m_last = newNode;
		this->m_size++;
		return true;
	}
}

template<class T>
bool CircleList<T>::remove() {
	if(this->m_current != NULL) {
		if(this->m_size == 1) {
			this->m_first = NULL;
			this->m_last = NULL;
			this->m_current->setNext(NULL);
			delete this->m_current;
			this->m_current = NULL;
			this->m_size--;
			return true;
		} else {
			NodeCircleList<T>* aux = this->m_current;
			if(this->m_first == this->m_current) this->m_first = this->m_current->getNext();
			if(this->m_last == this->m_current) this->m_last = this->m_current->getBack();
			this->m_current = this->m_current->getNext();
			aux->getBack()->setNext(aux->getNext());
			aux->getNext()->setBack(aux->getBack());
			aux->setNext(NULL);
			aux->setBack(NULL);
			delete aux;
			this->m_size--;
			return true;
		}
	}
}

template<class T>
bool CircleList<T>::remove(iterator& it) {
	NodeCircleList<T>* node = it.m_it;
	if(node != NULL) {
		if(this->m_size == 1) {
			this->m_first = NULL;
			this->m_last = NULL;
			this->m_current = NULL;
			node->setNext(NULL);
			delete node;
			node = NULL;
			this->m_size--;
			return true;
		} if(node == this->m_first){
			return removeFirst();
		} if(node == this->m_last){
			return removeLast();
		} if(node == this->m_current){
			return remove();
		} else {
			node->getBack()->setNext(node->getNext());
			node->getNext()->setBack(node->getBack());
			node->setNext(NULL);
			node->setBack(NULL);	
			delete node;
			this->m_size--;
			return true;
		}
	}
}

template<class T>
bool CircleList<T>::removeFirst() {
	if(this->m_first != NULL) {
		if(this->m_size == 1) {
			this->m_current = NULL;
			this->m_last = NULL;
			this->m_first->setNext(NULL);
			delete this->m_first;
			this->m_first = NULL;
			this->m_size--;
			return true;
		} else {
			NodeCircleList<T>* aux = this->m_first;
			if(this->m_current == this->m_first) this->m_current = this->m_first->getNext();
			this->m_first = this->m_first->getNext();
			aux->getBack()->setNext(aux->getNext());
			aux->getNext()->setBack(aux->getBack());
			aux->setNext(NULL);
			aux->setBack(NULL);
			delete aux;
			this->m_size--;
			return true;
		}
	}
}

template<class T>
bool CircleList<T>::removeLast() {
	if(this->m_last != NULL) {
		if(this->m_size == 1) {
			this->m_current = NULL;
			this->m_first = NULL;
			this->m_last->setNext(NULL);
			delete this->m_last;
			this->m_last = NULL;
			this->m_size--;
			return true;
		} else {
			NodeCircleList<T>* aux = this->m_last;
			if(this->m_current == this->m_last) this->m_current = this->m_last->getNext();
			this->m_last = this->m_last->getBack();
			aux->getBack()->setNext(aux->getNext());
			aux->getNext()->setBack(aux->getBack());
			aux->setNext(NULL);
			aux->setBack(NULL);
			delete aux;
			this->m_size--;
			return true;
		}
	}
}

template<class T>
void CircleList<T>::setCurrentAtFirst() {
	this->m_current = this->m_first;
}

template<class T>
void CircleList<T>::setCurrentAtLast() {
	this->m_current = this->m_last;
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/

template<class T>
bool CircleList<T>::isEmpty() const {
	return this->m_size == 0;
}

template<class T>
bool CircleList<T>::isNotEmpty() const {
	return this->m_size != 0;
}

/*************************************************************

					SOBRECARGA DE OPERADORES

*************************************************************/

template<class T>
CircleList<T>& CircleList<T>::operator ++() {
	this->m_current = this->m_current->getNext();
	return *this;
}

template<class T>
CircleList<T>& CircleList<T>::operator --() {
	this->m_current = this->m_current->getBack();
	return *this;
}