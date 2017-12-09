#ifndef tabla_h
#define tabla_h

#include <iostream>
#include "simbolo.h"

using namespace std;

vector<Simbolo*> vectorSimbolos;
class TablaSimbolos{
    
protected:
public:
    TablaSimbolos();
    void insert(Simbolo*);
    void muestra();
    bool buscarTablaSim(string);
    bool buscarTablaSim(string,string);
    Simbolo* buscarSimbolo(string,string);
    //hacer un buscarSimbolo que busque por id y por ambito
    char dameTipo(string,string);
    string dameVar(int);
    int getTablaSize();
};

TablaSimbolos::TablaSimbolos(){
}

void TablaSimbolos::insert(Simbolo *s){
    vectorSimbolos.push_back(s);
}

void TablaSimbolos::muestra(){
    cout << endl;
    //cout << "tamanio del vector: "  << vectorSimbolos.size() << endl;
    cout << "-------------- VARIABLES Y AMBITOS --------------" << endl;
    for (int i = 0; i < vectorSimbolos.size(); i++){
        vectorSimbolos[i]->muestra();
    }
    cout << "-------------------------------------------------" << endl;
    cout << endl;
}

bool TablaSimbolos::buscarTablaSim(string id){
    for (int i = 0; i < vectorSimbolos.size(); i++){
        //cout << "buscarTablaSim:::::" << vectorSimbolos[i]->getSimbolo() << " vs " << id << endl;
        if(vectorSimbolos[i]->getSimbolo() == id){
            return true;
        }
    }
    return false;
}

bool TablaSimbolos::buscarTablaSim(string id, string ambito){
    
    for (int i = 0; i < vectorSimbolos.size(); i++){
        //cout << "buscarTablaSim:::::" << vectorSimbolos[i]->getSimbolo() << " vs " << id << endl;
        /*if(vectorSimbolos[i]->getSimbolo() == "res"){
         }*/
        if(vectorSimbolos[i]->getSimbolo() == id and vectorSimbolos[i]->getAmbito() == ambito){
            //cout << "Encontre: "<< vectorSimbolos[i]->getSimbolo() << " en la tabla de simbolos con ambito --> " << vectorSimbolos[i]->getAmbito() << "\n"<< endl;
            return true;
        }
    }
    return false;
}

Simbolo* TablaSimbolos::buscarSimbolo(string id,string ambito){
    
    for (int i = 0; i < vectorSimbolos.size(); i++){
        if(vectorSimbolos[i]->getSimbolo() == id){
            return vectorSimbolos[i];
        }
    }
    return NULL;
}

char TablaSimbolos::dameTipo(string id, string ambito){
    
    for (int i = 0; i < vectorSimbolos.size(); i++){
        //cout << "dameTipo [" << i << "] :" << vectorSimbolos[i]->getSimbolo() << "  vs 	" << id << endl;
        if(vectorSimbolos[i]->getSimbolo() == id and vectorSimbolos[i]->getAmbito() == ambito){
            //cout << "el tipo de dameTipo : " << id << " = " << vectorSimbolos[i]->getTipo() << endl;
            return vectorSimbolos[i]->getTipo();
        }
    }
    return '@';
}

int TablaSimbolos::getTablaSize(){
    return vectorSimbolos.size();
}

string TablaSimbolos::dameVar(int indice){
    return vectorSimbolos[indice]->getSimbolo();
}


class TablaErrores{
protected:
    vector<string> vectorErrores;
public:
    TablaErrores();
    void insert(int,string);
    void muestra();
    
};

TablaErrores::TablaErrores(){}

void TablaErrores::insert(int error, string id){
    string errorStr="";
    switch(error){
        case 1:
            cout << "\tERROR 1: \""<< id << "\""" Esta variable ya esta repetida" << endl;
            errorStr = " - " + id + "\""" Esta variable ya esta definida";
            break;
        case 2:
//            cout << "\tERROR 2: \"" << id << "\""" Esta variable no se ha declarado anteriormente " << endl;
            errorStr = " - " + id + "\""" Esta variable no se ha declarado anteriormente ";
            break;
        case 3:
//            cout << "\tERROR 3: La expresion NO fue del mismo tipo " << endl;
            errorStr = " - La expresion NO fue del mismo tipo ";
            break;
        case 4:
//            cout << "\tERROR 4: La expresion NO fue del mismo tipo de dato que: " << id << endl;
            errorStr = " - La expresion NO fue del mismo tipo de dato que: " + id ;
            break;
        case 5:
//            cout << "\tERROR 5: \""<< id << "\""" Esta funcion no se ha declarado anteriormente" << endl;
            errorStr = " - " + id + " Esta funcion no se ha declarado anteriormente";
            break;
        case 6:
//            cout << "\tERROR 6: \""<< id << "\""" El Valor Regresa NO es del mismo tipo que la funcion" << endl;
            errorStr = " - " + id + "  El Valor Regresa NO es del mismo tipo que la funcion";
            break;
        case 7:
//            cout << "\tERROR 7: \""<< id << "\""" No hay suficientes argumentos para la definicion de la funcion" << endl;
            errorStr = " - " + id + " No hay suficientes argumentos para la definicion de la funcion";
            break;
        case 8:
//            cout << "\tERROR 8: \""<< id << "\""" La llamada a funcion no concuerda en argumentos con la declaracion de la Funcion " << endl;
            errorStr = " - " + id + " La llamada a funcion no concuerda en argumentos con la declaracion de la Funcion ";
            break;
            
    }
    vectorErrores.push_back(errorStr);
}


void TablaErrores::muestra(){
//    cout << endl;
//    cout << "tamanio del vector: "  << vectorSimbolos.size() << endl;
//    cout <<"-----------------------------------------------------------"<<endl;
//    cout <<"-----------------------------------------------------------"<<endl;

    for (int i = 0; i < vectorErrores.size(); i++){
        cout << vectorErrores[i] << endl;
    }
//    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout<<endl;
}


#endif /* tabla_h */
