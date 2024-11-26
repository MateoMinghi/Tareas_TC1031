/*
* Mateo Minghi
* A01711231
* 
*/

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key); //función anónima
	unsigned int size;
	unsigned int count;
	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key));

    void put(Key, Value);
    Value get(const Key);
	string toString() const;
};

template <class Key, class Value>
string Quadratic <Key, Value>::toString() const {
    stringstream aux;
    for (int i = 0; i < size; i++){
    		if (keys[i] != initialValue){
    			aux << "(" << i << " ";
    			aux << keys[i] << " : " << values[i] << ") ";
    		}
    }
    return aux.str();
}

template <class Key, class Value>
Quadratic <Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	
	count = 0;
	
	size = sze;
	initialValue = init;
	
	
	keys = new Key[size];
	
	for (int i = 0; i < size; i++){
		keys[i] = initialValue;
	}

	
	values = new Value[size];
	for (int i = 0; i < size; i++){
		values[i] = 0;}

	func = f;
}

template <class Key, class Value>
long Quadratic <Key, Value>::indexOf(const Key k) const {
	
	unsigned int i, start;

	start = i = func(k) % size;
	int count_hash = 1;
	do {
		if (keys[i] == k) {
			return i;}
		i = ((count_hash * count_hash) + i) % size;
		count_hash++;
 	} 
	while (start != i);
	
	return -1;
}

template <class Key, class Value>
void Quadratic <Key, Value> :: put(Key k, Value v){
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return;
	}

	start = i = func(k) % size;
	int count_hash = 1;
	do {	
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return;}
		i = ((count_hash * count_hash) + i) % size;
		count_hash++;
	} 
	while (start != i);
}

template <class Key, class Value>
Value Quadratic <Key, Value> :: get(const Key k){
	long pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
}

#endif