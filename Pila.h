#ifndef Pila_h
#define Pila_h


#include <list>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#define ARCHIVOLR "/Users/CarlosRaygoza/Documents/CARLOSRAYGOZA/CUCEI/7/SEM Traductores 2/Todo/compilador/practica6_generacion/datos/compilador.lr"


using namespace std;

class Nodo;


class ElementoPila{
public:
    //string nombreT;
    //int valor;
    Nodo* nodo;
public:
    virtual void muestra(){}
    virtual int getEstado(){ return 0; }
    virtual string getTerminal(){ return ""; }
    virtual string getNoTerminal(){ return ""; }
    virtual Nodo* getNodo(){ return nodo; }

};

class Terminal: public ElementoPila{
//protected:
    string terminal;
    int tipo;
public:
    Terminal(string terminal){
        this->terminal= terminal;
    }

    string getTerminal(){
        return this->terminal;
    }

    void muestra(){
        cout<<terminal<<" ";
    }
};

class NoTerminal: public ElementoPila{
protected:
    string noTerminal;
    Nodo* nodo;
public:
    NoTerminal(string noTerminal, Nodo* nuevoNodo){
        this->noTerminal= noTerminal;
        this->nodo = nuevoNodo;
    }

    string getNoTerminal(){
        return this->noTerminal;
    }

    Nodo* getNodo(){
        return this->nodo;
    }

    void muestra(){
        cout<<noTerminal<<" ";
    }
};

class Estado: public ElementoPila{
protected:
    int estado;
public:
    Estado(int estado){
        this->estado= estado;
    }

    int getEstado(){
        return this->estado;
    }

    void muestra(){
        cout<<estado<<" ";
    }
};



class Pila{

private:
    list <ElementoPila*> lista;

public:
    void ejercicio2();

    //PRACTICA 2
    void push(ElementoPila *x);
    ElementoPila* top();
    ElementoPila* pop();
    int accionDesplazamiento;
    void muestra(int elementos);
    int elementos;
    void leer();
    void mostrarArrays();

    //Práctica 3
    int filas, columnas, totalReglas, asignacion, tamano;
    bool negativo;

    void asignTablaLR(int valor, string c);
    void asignValuesTablaLR();
    int asignSizeVectores(string valor);
    int asignValuesVectores(string valor);

    vector<vector<int>>tablaLR;
    vector<int> idReglas;
    vector<int>lonReglas;
    vector<string>nomR;
    vector<int>tablaProvisional;

    //constructor
    Pila(){
        totalReglas = 0, filas = 0, columnas = 0, asignacion = 0, tamano = 0;
        negativo = false;
        leer();
    }
};


#endif /* Pila_hpp */
