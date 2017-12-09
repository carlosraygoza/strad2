#include "Pila.h"
#include "Lexico.h"
#include "arbol.h"
#include <sstream>


// --------> PRACTICA 2

void Pila::push(ElementoPila *x){
    lista.push_front(x);
}

ElementoPila*  Pila::pop(){
    ElementoPila* x= *lista.begin();
    lista.erase ( lista.begin() );
    return x;
}

ElementoPila* Pila::top(){
    return *lista.begin();
}

void Pila::muestra(int elementos){
    list <ElementoPila*>::reverse_iterator  it;
    ElementoPila *x;
    cout << " - Pila: \t ";
    
    for (it= lista.rbegin(); it != lista.rend(); it++){
        x = *it;
        x->muestra();
    }
    cout << endl;
}

void Pila::ejercicio2(){
    // inicialización de la pila, y el analizador léxico
    Pila pila;
    int fila, columna = 0, accion, oldAccion = 0, regla = 0;
    string simbolo;
    Lexico lexico;
//    lexico.entrada("int a; float c;"
//                   "int main( ){"
//                   "int a, b; "
//                   "b=3; a=c; "
//                   "c = a+b;"
//                   "}");
    lexico.entrada("int main(){ int d;  b=3; return 0; }");
    pila.push(new Terminal("$"));
    pila.push(new Estado(0));
    lexico.sigSimbolo();
    
    fila= pila.top()->getEstado();
    columna= lexico.tipo;
    accion = tablaLR[fila][columna]; //encontrar la primera acción a realizar
    cout<<" ------------------------------ GRAMATICA ------------------------------"<<endl<<endl;
    cout<<" --> INICIO "<<endl;
    
    
    while (true) {
        //        cout<<" fila: "<<fila<<" - columna: "<<columna<<endl;
        //mostramos el contenido de la pila, la entrada actual y la acción que se va a realizar.
        pila.muestra(elementos);
        cout << " - Token: " << lexico.simbolo<<endl; // << "tipo: "<<lexico.tipo<<" = "<<lexico.tipoAcad(lexico.tipo)<<")"<<endl;
        cout << " - accion: " << accion << endl;
        cout<<endl;
        
        if(accion == -1){
                  cout<<"----------------------- ACEPTACIÓN ------------------------"<<endl;
            cout<<endl<<"------------------- Generación de código -------------------"<<endl;
            cout<<endl<<" Ha sido realizada con éxito !"<<endl<<endl<<endl;
            break;
        }else if(accion > 0){
            cout<<" --> DESPLAZAMIENTO "<<endl;
            pila.push(new Terminal(lexico.simbolo)); //símbolo actual
            pila.push(new Estado(accion)); //número de salida
            elementos += 2; //suma de elementos en pila
            lexico.sigSimbolo();
            
            fila= pila.top()->getEstado();
            columna= lexico.tipo;
            accion = tablaLR[fila][columna];
        }else if(accion < 0){
            //determinar regla
            regla = (accion*-1)-1;
            
            Nodo* nuevoNodo = nullptr;
            switch(regla){
                    
                case 2: case 7: case 10: case 12: case 15: case 19: case 26: case 29: case 31: case 33:
                    nuevoNodo = new nullNodo();
                    break;
                case 1:
                    cout<<" ------------------------------ ARBOL ------------------------------";
                    nuevoNodo = new Programa_R1(pila);
                    cout<<endl;
                    nuevoNodo->muestra(1);
                    nuevoNodo->generarCodigo();
                    
                    break;
                case 3:
                    nuevoNodo = new Definiciones_R3(pila);
                    break;
                case 4:
                    nuevoNodo = new Definicion_R4(pila);
                    break;
                case 5:
                    nuevoNodo = new Definicion_R5(pila);
                    break;
                case 6:
                    nuevoNodo = new DefVar_R6(pila);
                    break;
                case 8:
                    nuevoNodo = new ListaVar_R8(pila);
                    break;
                case 9:
                    nuevoNodo = new DefFunc_R9(pila);
                    break;
                case 11:
                    nuevoNodo = new Parametros_R11(pila);
                    break;
                case 13:
                    nuevoNodo = new ListaParam_R13(pila);
                    break;
                case 14:
                    nuevoNodo = new BloqFunc_R14(pila);
                    break;
                case 16:
                    nuevoNodo = new DefLocales_R16(pila);
                    break;
                case 17:
                    nuevoNodo = new DefLocal_R17(pila);
                    break;
                case 18:
                    nuevoNodo = new DefLocal_R18(pila);
                    break;
                case 20:
                    nuevoNodo = new Sentencias_R20(pila);
                    break;
                case 21:
                    nuevoNodo = new Sentencia_R21(pila);
                    break;
                case 22:
                    nuevoNodo = new Sentencia_R22(pila);
                    break;
                case 23:
                    nuevoNodo = new Sentencia_R23(pila);
                    break;
                case 24:
                    nuevoNodo = new Sentencia_R24(pila);
                    break;
                case 25:
                    nuevoNodo = new Sentencia_R25(pila);
                    break;
                case 27:
                    nuevoNodo = new Otro_R27(pila);
                    break;
                case 28:
                    nuevoNodo = new Bloque_R28(pila);
                    break;
                case 30:
                    nuevoNodo = new ValorRegresa_R30(pila);
                    break;
                case 32:
                    nuevoNodo = new Argumentos_R32(pila);
                    break;
                case 34:
                    nuevoNodo = new ListaArgumentos_R34(pila);
                    break;
                case 35:
                    nuevoNodo = new Termino_R35(pila);
                    break;
                case 36:
                    nuevoNodo = new Termino_R36(pila);
                    break;
                case 37:
                    nuevoNodo = new Termino_R37(pila);
                    break;
                case 38:
                    nuevoNodo = new Termino_R38(pila);
                    break;
                case 39:
                    nuevoNodo = new Termino_R39(pila);
                    break;
                case 40:
                    nuevoNodo = new LlamadaFunc_R40(pila);
                    break;
                case 41:
                    nuevoNodo = new SentenciaBloque_R41(pila);
                    break;
                case 42:
                    nuevoNodo = new SentenciaBloque_R42(pila);
                    break;
                case 43:
                    nuevoNodo = new Expresion_R43(pila);
                    break;
                case 44:
                    nuevoNodo = new Expresion_R44(pila);
                    break;
                case 45:
                    nuevoNodo = new Expresion_R45(pila);
                    break;
                case 46:
                    nuevoNodo = new Expresion_R46(pila);
                    break;
                case 47:
                    nuevoNodo = new Expresion_R47(pila);
                    break;
                case 48:
                    nuevoNodo = new Expresion_R48(pila);
                    break;
                case 49:
                    nuevoNodo = new Expresion_R49(pila);
                    break;
                case 50:
                    nuevoNodo = new Expresion_R50(pila);
                    break;
                case 51:
                    nuevoNodo = new Expresion_R51(pila);
                    break;
                case 52:
                    nuevoNodo = new Expresion_R52(pila);
                    break;
                    
            }
            cout<<" --> REDUCCIÓN";
            fila= pila.top()->getEstado();
            columna = idReglas[abs(accion)-2];
            oldAccion = accion;
            accion = tablaLR[fila][columna];
            
            simbolo = nomR[abs(oldAccion)-2];
            pila.push(new NoTerminal(simbolo, nuevoNodo));
            pila.push(new Estado(accion));
            cout<<endl;
            
            fila = pila.top()->getEstado();
            columna = lexico.tipo;
            accion = tablaLR[fila][columna];
            continue;
        
        }else{
            cout<<" * ERROR *"<<endl;
            break;
        }
    }
}

//Práctica 3
void Pila::leer(){
    int valor = 0;
    char cc = ' ';
    string cadena = "";
    
    ifstream archivo(ARCHIVOLR);
    string variable(char);
    //leer todo
    if(!archivo.good()){
        cout<<"error"<<endl;
    }else{
        while (archivo.get(cc)){
            stringstream ss;
            string s;
            ss << cc;
            ss >> s;
            cadena = cadena + s;
            if(cc == '\t' || cc =='\n' || cc == ' '){
                cadena = cadena + " ";
            }
        }
        
        //leer por pasos
        Lexico lexico(cadena);
        
        for (int i = 0; i<= cadena.length(); i++) {
            lexico.sigSimbolo();
            //si no es espacio, tab, renglón entonces asignar
            if(lexico.simbolo != " " && lexico.simbolo !="\n" && lexico.simbolo!="\t"){
                if (valor == 0) {
                    //asignación de tamaño de vectores
                    asignSizeVectores(lexico.simbolo);
                }else if(valor <= totalReglas){
                    //asignar valores de reglas
                    asignValuesVectores(lexico.simbolo);
                }else{
                    //creación de dimensiones de TablaLR y provisional
                    asignTablaLR(valor, lexico.simbolo);
                }
                valor++;
            }
        }
        //asignar valores de provisional a tablaLR
        asignValuesTablaLR();
    }
    archivo.close();
}

void Pila::mostrarArrays(){
    cout<<endl<<"lectura de arrays"<<endl;
    for(int i=0; i<tamano; i++){
        cout<<lonReglas[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<tamano; i++){
        cout<<idReglas[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<tamano; i++){
        cout<<nomR[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<100; i++){
        cout<<tablaProvisional[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<filas ; i++){
        for(int j=0; j<columnas; j++){
            cout<<""<<tablaLR[i][j]<<" "<<endl;
            cout<<i<<","<<j<<endl;
            cout<<" "<<endl;
        }
    }
}


int Pila::asignSizeVectores(string valor){
    //asignación de tamaño de vectores
    //casteo de string a int
    tamano = atoi(valor.c_str());
    
    //    cout<<"tamaño: "<<tamano<<endl;
    vector<int>idReglas((tamano));
    vector<int>lonReglas((tamano));
    vector<string>nomR((tamano));
    //nuevo valor para leer
    totalReglas = tamano * 3;
    return totalReglas;
}

int Pila::asignValuesVectores(string valor){
    //casteo de string a int
    int numero = atoi(valor.c_str());
    //asignar valores de reglas
    if (asignacion == 0) {
        //asigna a ID
        idReglas.push_back(numero);
        asignacion++;
    }else if(asignacion == 1){
        //asigna a longitud
        lonReglas.push_back(numero);
        asignacion++;
    }else if(asignacion == 2){
        //asigna a nombre
        nomR.push_back(valor);
        //reinicio de valor de asignacion debido a que solo hay 3 valores por renglon para cada regla
        asignacion = 0;
    }
    return asignacion;
}

void Pila::asignTablaLR(int valor, string c){
    int numero;
    numero = atoi(c.c_str());
    int total = 0;
    //asignar tamaño de matriz
    if (valor <= totalReglas+1) {
        filas = numero;
    }else if(valor <= totalReglas+2){
        columnas = numero;
        //asignacion de fila y columnas a tablaLR
        tablaLR.resize(filas,vector<int>(columnas));
        total = filas * columnas;
        vector<int>tablaProvisional(total);
    }else{
        //asignar valores de tablaLR leidos a provisional
        if (c == "-") {
            negativo = true;
        }else if(negativo){
            //agregar numero negativo
            tablaProvisional.push_back(-(numero));
            negativo = false;
        }else{
            //agregar numero positivo
            tablaProvisional.push_back((numero));
            negativo = false;
        }
    }
}

void Pila::asignValuesTablaLR(){
    int provi = 0;
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            tablaLR[i][j] = tablaProvisional[provi];
            provi++;
        }
    }
}

