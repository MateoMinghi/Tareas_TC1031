/* 
 * Mateo Minghi
 * A01711231
*/

#ifndef _SORTS_H
#define _SORTS_H_

#include <iostream>


template <class T>
class Sorts {
private:
    void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);

public:
    int busqSecuencial(const std::vector<T>&, int);
    int busqBinaria(std::vector<T>&, int);

    void ordenaBurbuja(std::vector<T>&);    
    void ordenaSeleccion(std::vector<T>&); 
 
    void ordenaMerge(std::vector<T>&);    
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
    T temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &prueba) {
	for (int i = 0; i<prueba.size()-1; i++){
		int minimo = i;
		for (int j = i+1; j < prueba.size(); j++){
			if (prueba[j] < prueba[minimo]){
				minimo = j; 
			}
			
		}
		if (minimo != i){
				swap(prueba, i, minimo);
			}
	}
}


template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &prueba) {
	for (int i = prueba.size() - 1; i > 0; i--){
		for (int j = 0; j < i; j++){
			if (prueba[j] > prueba[j+1]){
				swap(prueba, j, j+1);
			}
		}
	}
}


template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high){
	for (int i = low; i <= high; i++) {
			A[i] = B[i];
		}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int left, int mid, int right){
	int i, j, k;

	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid &&j <= right) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= right; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high){
	if ( (high - low) < 1 ) {
		return;
	}
	int mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &prueba) {
	std::vector<T> tmp(prueba.size());
	mergeSplit(prueba, tmp, 0, prueba.size() - 1);
	
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &prueba, int val){
	for (int i = 0; i < prueba.size(); i++){
		if (prueba[i] == val){
			return i;
		}
	} 
	return -1; 
}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &prueba, int val){
    ordenaBurbuja(prueba);
	int middle;
	int l = 0;
	int r = prueba.size() - 1;

	while (l < r) {
		middle = (r + l) / 2;
		if (val == prueba[middle]) {
			return middle;
		} else if (val < prueba[middle]) {
			r = middle - 1;
		} else if (val > prueba[middle]) {
			l = middle + 1;
		}
	}
	return -1;
}
#endif