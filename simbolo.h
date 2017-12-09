#ifndef simbolo_h
#define simbolo_h

class Simbolo{
protected:
    char tipo;
    string simbolo;
    string ambito;
    char param;
    char vectorParam[20];
    bool funcion;
public:
    Simbolo(char, string, string,bool);
    Simbolo(char, string, string,char*,bool);
    void muestra();
    char getTipo();
    string getSimbolo();
    string getAmbito();
    int getNumParam();
    char getVectorParam(int);
    bool getFuncion();
    
};


Simbolo::Simbolo(char ti, string sim, string amb, bool funcion){
    this->tipo=ti;
    this->simbolo=sim;
    this->ambito=amb;
    this->funcion=funcion;
}

Simbolo::Simbolo(char ti, string sim, string amb, char* vectorParam, bool funcion){
    this->tipo=ti;
    this->simbolo=sim;
    this->ambito=amb;
    for (int i = 0; i < sizeof(vectorParam); i++){
        this->vectorParam[i]=vectorParam[i];
    }
    
    this->funcion = funcion;
}


void Simbolo::muestra(){
    
    
    cout <<"tipo: ";
    switch (tipo) {
        case 'i':
            cout<<"entero";
            break;
        case 'f':
            cout<<"flotante";
            break;
        case 'v':
            cout<<"void";
            break;
        default:
            cout<<" ";
            break;
    }

    cout<< "\t simbolo " << simbolo << "\t ambito " << ambito << endl;
//    cout << "-------------------------------------------------" << endl;
    
    
}

char Simbolo::getTipo(){
    return tipo;
}

string Simbolo::getSimbolo(){
    return simbolo;
}

string Simbolo::getAmbito(){
    return ambito;
}

int Simbolo::getNumParam(){
    int i;
    for (i = 0; i < sizeof(vectorParam) ; i++){
        if (vectorParam[i]==0){
            //cout << "retornando i: " << i << endl;
            return i;
        }
        //cout << "Parametro["<< i << "]= " << vectorParam[i] << endl;
    }
    return i;
}

bool Simbolo::getFuncion(){
    return funcion;
}

char Simbolo::getVectorParam(int i){
    return vectorParam[i];
}


#endif /* simbolo_h */
