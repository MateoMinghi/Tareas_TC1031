/*
 *   Mateo Minghi 
 *   A01711231
 *   TC1031
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones{
public:
    Funciones(){};

    long sumaIterativa(int n){
        long suma = 0;
        for (int i = 0; i<=n; i++){
            suma+=i;
        }
        return suma;
    }

    long sumaRecursiva(int n){
        if (n == 0){
            return 0;
        }
        else if (n == 1){
            return 1;
        }
        else{
            return sumaRecursiva(n-1) + n;
        }
    } 

    long sumaDirecta(int n){
        long result;
        return (n*(n+1))/2;
    }

    
};




#endif