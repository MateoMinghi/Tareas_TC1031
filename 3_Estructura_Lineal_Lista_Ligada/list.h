/*
 * Mateo Minghi
 * TC1031
 * Prof. Benjamin 
 * 
*/

#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <string>

using namespace std;

template <class T> class List;

template <class T>
class Link {
private:
    Link(T);
	Link(T, Link<T>*);
	
	T value;
	Link<T>* next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}


template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();
    void clear();
    
    void insertion(T);
    int search(T);
    void update(int, T);
    void deleteAt(int);
    string toString() const;

private:
    Link<T> *head;
	int size;
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
void List<T>::clear() {
	Link<T> *current, *temp;

	current = head;
	while (current != nullptr) {
		temp = current->next;
		delete current;
		current = temp;
	}
	head = 0;
	size = 0;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
void List<T>::insertion(T val) {
    Link<T> *newNode, *temp;

    newNode = new Link<T>(val);
    if (newNode == 0) {
        return;
    }

    if (head == nullptr) {
        newNode->next = head;
        head = newNode;
        size++;
        return;
    }

    temp = head;
    while (temp->next != 0) {
        temp = temp->next;
    }

    newNode->next = 0;
    temp->next = newNode;
    size++;
}

template <class T>
int List<T>::search(T val) {
    Link<T>* temp;
    int index;

    temp = head;
    index = 0;
   
    while (temp != nullptr) {
        if (temp->value == val) {
            return index;
        }
        
        index++;
        temp = temp->next;
    }

    return -1;
}

template <class T>
void List<T>::update(int index, T val) {
    Link<T>* temp;
    int counter;

    if (index < 0 || index >= size) {
        return;
    }

    temp = head;
    counter = 0;
    while (counter != index) {
        temp = temp->next;
        counter++;
    }

    temp->value = val;
}

template <class T>
void List<T>::deleteAt(int index) {
    Link<T> *current, *temp;
    int pos;

    if (index < 0 || index >= size) {
        return;
    }

    if (index == 0) {
        current = head;
        head = head->next;
        delete current;
        size--;
        return;
    }

    current = head;
    pos = 0;
    while (pos != index) {
        temp = current;
        current = current->next;
        pos++;
    }

    temp->next = current->next;
    delete current;
    size--;
}

template <class T>
string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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

#endif