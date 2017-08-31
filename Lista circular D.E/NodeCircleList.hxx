# include "NodeCircleList.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

template<class T>
NodeCircleList<T>::NodeCircleList(const T& data, NodeCircleList<T>* next, NodeCircleList<T>* back) {
	this->data = data;
	if(next == NULL) {
		this->next = this;
	} else {
		this->next = next;
	}
	if(back == NULL) {
		this->back = this;
	} else {
		this->back = back;
	}
}

template<class T>
NodeCircleList<T>::~NodeCircleList() {
	if(this->next != NULL) {
		delete this->next;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

template<class T>
T& NodeCircleList<T>::getData() {
	return this->data;
}

template<class T>
void NodeCircleList<T>::setData(const T& data) {
	this->data = data;
}

template<class T>
NodeCircleList<T>* NodeCircleList<T>::getNext() const {
	return this->next;
}

template<class T>
void NodeCircleList<T>::setNext(NodeCircleList<T>* next) {
	this->next = next;
}

template<class T>
NodeCircleList<T>* NodeCircleList<T>::getBack() const {
	return this->back;
}

template<class T>
void NodeCircleList<T>::setBack(NodeCircleList<T>* back) {
	this->back = back;
}