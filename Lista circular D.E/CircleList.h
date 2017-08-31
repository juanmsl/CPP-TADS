# ifndef __CIRCLE_LIST_H__
# define __CIRCLE_LIST_H__

# include <iostream>
# include "NodeCircleList.h"

template<class T>
class CircleList {
	protected:
		NodeCircleList<T>* m_first;
		NodeCircleList<T>* m_last;
		NodeCircleList<T>* m_current;
		int m_size;

	public:
		class iterator {
			public:
				NodeCircleList<T>* m_it;

				// CONSTRUCTOR Y DESTRUCTOR
				iterator(NodeCircleList<T>* pointer);
				iterator();
				~iterator();

				// SOBRECARGA DE OPERADORES
				NodeCircleList<T>* operator ++ ();
				NodeCircleList<T>* operator ++ (int);
				NodeCircleList<T>* operator -- ();
				NodeCircleList<T>* operator -- (int);
				T& operator* ();
                T* operator->();
                bool operator == (const iterator& itt);
                bool operator != (const iterator& itt);
		};

		// CONSTRUCTOR Y DESTRUCTOR
		CircleList();
		~CircleList();

		// METODOS ENCAPSULADORES
		const int& size() const;
		T& first() const;
		T& last() const;
		T& current() const;

		iterator getFirst() const;
		iterator getLast() const;
		iterator getCurrent() const;

		// METODOS MODIFICADORES
		bool insert(const T& data);
		bool insertAtFirst(const T& data);
		bool insertAtLast(const T& data);

		bool remove();
		bool remove(iterator& it);
		bool removeFirst();
		bool removeLast();

		void setCurrentAtFirst();
		void setCurrentAtLast();

		// METODOS DE ACCESO
		bool isEmpty() const;
		bool isNotEmpty() const;

		// SOBRECARGA DE OPERADORES
		CircleList<T>& operator ++();
		CircleList<T>& operator --();
};

# include "CircleList.hxx"

# endif