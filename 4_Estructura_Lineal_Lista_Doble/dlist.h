/*
 * Mateo Minghi
 * A01711231
 * Prof. Benjamin
*/

#ifndef _DLIST_H_
#define _DLIST_H_

#include <iostream>
#include <string>

using namespace std;

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	//bool empty() const;
	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	bool empty() const;
	void insertion(T);
	T removeFirst() ;
	
	
	int length() const;
	T search(int) const;
	void clear();
	
	void update(int, T);


	T deleteAt(int);
	
	string toStringForward() const;
	string toStringBackward() const;

private:
	DLink<T> *head;
	DLink<T> *tail;
	int size;

	friend class DListIterator<T>;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}


template <class T>
DList<T>::~DList() {
	clear();
}


template <class T>
int DList<T>::length() const {
	return size;
}


template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::insertion(T val){
	DLink<T> *newLink;

	newLink = new DLink<T>(val);
	

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
T DList<T>::removeFirst(){
	T val;
	DLink<T> *p;

	/*if (empty()) {
		throw NoSuchElement();
	}*/

	p = head;
	val = p->value;

	if (head == tail) {
		head = 0;
		tail = 0;
	} else {
		head = p->next;
		p->next->previous = 0;
	}
	delete p;
	size--;

	return val;
}

template <class T>
T DList<T>::search(int val) const {
    
    DLink<T>* p = head;
    int index = 0;

    while (p != nullptr) {
        if (p->value == val) {
			return index;
		}
		p = p->next;
		index++;
    }

    return -1;
}


template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}


template <class T>
DList<T>::DList(const DList<T> &source){
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		/*if (head == 0) {
			throw OutOfMemory();
		}*/
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			/*if (q->next == 0) {
				throw OutOfMemory();
			}*/
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}


template <class T>
T DList<T>::deleteAt(int index) {
	int pos;
	T val;
	DLink<T> *p;

	/*if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}*/

	if (index == 0) {
		return removeFirst();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	val = p->value;
	p->previous->next = p->next;
	if (p->next != 0) {
		p->next->previous = p->previous;
	}
	size--;

	delete p;

	return val;
}





template <class T>
void DList<T>::update(int indice, T val){
	int pos;
	DLink<T> *p;

	
	if (indice == 0) {
		head->value = val;
	} else {
		p = head;
		pos = 0;
		while (pos != indice) {
			p = p->next;
			pos++;
		}
		p->value = val;
	}	
}


template <class T>
	std::string DList<T>::toStringForward() const {
		std::stringstream aux;
		DLink<T> *p;

		p = head;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->next != 0) {
				aux << ", ";
			}
			p = p->next;
		}
		aux << "]";
		return aux.str();
	}

	template <class T>
	std::string DList<T>::toStringBackward() const {
		std::stringstream aux;
		DLink<T> *p;

		p = tail;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->previous != 0) {
				aux << ", ";
			}
			p = p->previous;
		}
		aux << "]";
		return aux.str();
	}




#endif