# ifndef __NODE_CIRCLE_LIST_H__
# define __NODE_CIRCLE_LIST_H__

template<class T>
class NodeCircleList {
	protected:
		T data;
		NodeCircleList<T>* next;
		NodeCircleList<T>* back;

	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeCircleList(const T& data, NodeCircleList<T>* next, NodeCircleList<T>* back);
		~NodeCircleList();

		// METODOS ENCAPSULADORES
		T& getData();
		NodeCircleList<T>* getNext() const;
		NodeCircleList<T>* getBack() const;
		void setData(const T& data);
		void setNext(NodeCircleList<T>* next);
		void setBack(NodeCircleList<T>* back);
};

# include "NodeCircleList.hxx"

# endif