#include "Lexico.h"
#define while_ 0
#define return_ 1
#define else_ 2
#define if_ 3
#define int_ 4
#define void_ 5
#define float_ 6

Lexico::Lexico(string fuente){
    ind = 0;
    this->fuente = fuente;
}

Lexico::Lexico(){
    ind = 0;
}

string Lexico::tipoAcad(int tipo){
    //Asignacion de descripcion de tipo
    string cad = "";
    switch (tipo){
        case TipoSimbolo::ENTERO:           cad = "Entero"; break;
        case TipoSimbolo::IDENTIFICADOR:    cad = "Identificador"; break;
        case TipoSimbolo::OPADIC:           cad = "Adicion o sustraccion"; break;
        case TipoSimbolo::OPMULT:           cad = "Multiplicacion o division"; break;
        case TipoSimbolo::REAL:             cad = "Real"; break;
        case TipoSimbolo::CADENA:           cad = "Cadena"; break;
        case TipoSimbolo::TIPO:             cad = "Tipo"; break;
        case TipoSimbolo::OPRELAC:          cad = "Relacional"; break;
        case TipoSimbolo::OPOR:             cad = "OR"; break;
        case TipoSimbolo::OPAND:            cad = "AND"; break;
        case TipoSimbolo::OPNOT:            cad = "NOT"; break;
        case TipoSimbolo::OPIGUALDAD:       cad = "Igualdad"; break;
        case TipoSimbolo::PUNTO_COMA:       cad = "Punto y coma"; break;
        case TipoSimbolo::COMA:             cad = "Coma"; break;
        case TipoSimbolo::PARENT_IZQ:       cad = "Abre parentesis"; break;
        case TipoSimbolo::PARENT_DER:       cad = "Cierra parentesis"; break;
        case TipoSimbolo::LLAVE_IZQ:        cad = "Abre llave"; break;
        case TipoSimbolo::LLAVE_DER:        cad = "Cierra llave"; break;
        case TipoSimbolo::ASIGNACION:       cad = "Igual"; break;
        case TipoSimbolo::IF:               cad = "Reservada: If"; break;
        case TipoSimbolo::WHILE:            cad = "Reservada: While"; break;
        case TipoSimbolo::RETURN:           cad = "Reservada: Return"; break;
        case TipoSimbolo::ELSE:             cad = "Reservada: Else"; break;
        case TipoSimbolo::PESOS:            cad = "Pesos"; break;
            //missing IDENTIFICADORES
        default:                            cad = "\t* ERROR *"; break;
    }
    return cad;
}

void Lexico::entrada(string fuente){
    ind = 0;
    this->fuente = fuente;
}

int Lexico::sigSimbolo(){
    estado=0;
    continua= true;
    simbolo= "";
    
    //Inicio del Automata
    while (continua){
        c= sigCaracter();
        
        switch (estado){
            case 0:
                if ( esLetra(c) ) sigEstado(21);
                else if ( c == '\"') sigEstado(22);
                else if ( esDigito(c) ) sigEstado(1);
                else if ( c == '+' || c =='-') aceptacion(6);
                else if ( c == '*' || c == '/') aceptacion(7);
                else if ( c == '<' || c == '>') sigEstado(4);
                else if ( c == '|') sigEstado(8);
                else if ( c == '&') sigEstado(10);
                else if ( c == '!') sigEstado(12);
                else if ( c == '=') sigEstado(14);
                else if ( c == ';') aceptacion(15);
                else if ( c == ',') aceptacion(16);
                else if ( c == '(') aceptacion(17);
                else if ( c == ')') aceptacion(18);
                else if ( c == '{') aceptacion(19);
                else if ( c == '}') aceptacion(20);
                else if ( c == '$' ) aceptacion(23);
                else{
                    if ( c != ' ' and c != '\t' and c != '\n'){
                        return -1; // si no es espacios entonces ha de ser un simbolo invalido
                    }
                }
                break;
                
            case 1:
                if ( esDigito(c)) sigEstado(1);
                else if ( c == '.') sigEstado(2);
                else{
                    retroceso();
                }
                break;
                
            case 2:
                if( esDigito(c)) sigEstado(3);
                
                break;
                
            case 3:
                if( esDigito(c)) sigEstado(3);
                else{
                    retroceso();
                }
                break;
                
            case 4:
                if( c == '=') sigEstado(5);
                else{
                    retroceso();
                }
                break;
                
            case 5:
                retroceso();
                break;
                
            case 8:
                if (c == '|') sigEstado(9);
                break;
                
            case 9:
                retroceso();
                break;
                
            case 10:
                if (c == '&') sigEstado(11);
                break;
                
            case 11:
                retroceso();
                break;
                
            case 12:
                if( c ==  '=') sigEstado(13);
                else{
                    retroceso();
                }
                break;
                
            case 13:
                retroceso();
                break;
                
            case 14:
                if (c == '=') sigEstado(13);
                else{
                    retroceso();
                }
                break;
                
            case 21:
                if ( esLetra(c) || esDigito(c) ) sigEstado(21);
                else{
                    retroceso();
                }
                break;
                
            case 22:
                if ( esLetra(c) || esDigito(c) || esEspacio(c) ) sigEstado(23);
                break;
                
            case 23:
                if ( esLetra(c) || esDigito(c) || esEspacio(c) ) sigEstado(23);
                else{
                    if( c == '\"') sigEstado(24);
                }
                break;
                
            case 24:
                retroceso();
                break;
                
            default:
                break;
        }
        
    }
    //Fin del Automata
    
    switch (estado){
        case 1:
            tipo= TipoSimbolo::ENTERO;
            break;
        case 3:
            tipo= TipoSimbolo::REAL;
            break;
        case 4:
            tipo= TipoSimbolo::OPRELAC;
            break;
        case 5:
            tipo= TipoSimbolo::OPRELAC;
            break;
        case 6:
            tipo= TipoSimbolo::OPADIC;
            break; 
        case 7:
            tipo = TipoSimbolo::OPMULT;
            break;
        case 9:
            tipo = TipoSimbolo::OPOR;
            break;
        case 11:
            tipo = TipoSimbolo::OPAND;
            break;
        case 12:
            tipo = TipoSimbolo::OPNOT;
            break;
        case 13:
            tipo = TipoSimbolo::OPIGUALDAD;
            break;
        case 14:
            tipo = TipoSimbolo::ASIGNACION;
            break;
        case 15:
            tipo = TipoSimbolo::PUNTO_COMA;
            break;
        case 16:
            tipo = TipoSimbolo::COMA;
            break;
        case 17:
            tipo = TipoSimbolo::PARENT_IZQ;
            break;
        case 18:
            tipo = TipoSimbolo::PARENT_DER;
            break;
        case 19:
            tipo = TipoSimbolo::LLAVE_IZQ;
            break;
        case 20:
            tipo = TipoSimbolo::LLAVE_DER;
            break;
        case 21:
            if( simbolo == "int" || simbolo == "float" || simbolo == "void" || simbolo == "string") tipo = TipoSimbolo::TIPO;
            else
                if( simbolo == "if") tipo = TipoSimbolo::IF;
                else
                    if (simbolo == "while") tipo = TipoSimbolo::WHILE;
                    else
                        if (simbolo == "return") tipo = TipoSimbolo::RETURN;
                        else
                            if (simbolo == "else") tipo = TipoSimbolo::ELSE;
                            else{
                                tipo = TipoSimbolo::IDENTIFICADOR;
                            }
            break;
        case 23: 
            tipo = TipoSimbolo::PESOS;
            break;
        case 24:
            tipo = TipoSimbolo::CADENA;
            break;
        default:
            tipo= TipoSimbolo::ERROR;
            break;
    }
    return tipo;
}

int Lexico::esAlfabetico(){
    bool isIdentificador = false;
    coincide = false;
    string reservadas[7] = {"while", "return", "else", "if", "int", "void", "float"};
    
    if(c=='w'){ //while
        string palabra = reservadas[while_];
        explorarReservadas(palabra, TipoSimbolo::WHILE, 21);
    }else if(c=='r'){ //return
        string palabra = reservadas[return_];
        explorarReservadas(palabra, TipoSimbolo::RETURN, 22);
    }else if(c=='e'){ //else
        string palabra = reservadas[else_];
        explorarReservadas(palabra, TipoSimbolo::ELSE, 23);
        tipo = TipoSimbolo::ELSE;
    }else if(c=='i'){ //if
        string palabra = reservadas[if_];
        explorarReservadas(palabra, TipoSimbolo::IF, 25);
        tipo = TipoSimbolo::IF;
        /*
        aceptacion(28);
        c = sigCaracter();
        //aceptacion(28);
        cout<<"jiji: "<<simbolo<<endl;
        
        if(c == 'f'){
            atrasCaracter();
            //atrasCaracter();
            cout<<"jiji1: "<<simbolo<<endl;
            c = simbolo[0];
            string palabra = reservadas[if_];
            explorarReservadas(palabra, TipoSimbolo::IF, 28);

            //es if
//            cout<<"simbolo: "<<simbolo<<endl;
            coincide = true;
            tipo = TipoSimbolo::IF;
            //aceptacion(28);
        }else{
            //puede ser int o identificador
            cout<<"fin"<<endl;
            tipo = TipoSimbolo::TIPO;
           // string palabra = reservadas[int_];
          //  explorarReservadas(palabra, TipoSimbolo::IDENTIFICADOR, 20);
        }
        //int
         */
    }else if(c=='v'){ //void
        string palabra = reservadas[void_];
        explorarReservadas(palabra, TipoSimbolo::TIPO, 26);
        tipo = TipoSimbolo::TIPO;
    }else if(c=='f'){ //float
        string palabra = reservadas[float_];
        explorarReservadas(palabra, TipoSimbolo::TIPO, 26);
        tipo = TipoSimbolo::TIPO;
    }
    //Si no coincide con alguna palabra reservada, puede ser identificador
    if (!coincide) {
        do{
//            c = sigCaracter();
            c_numero = c - '0';
            if (isalpha(c) || (c_numero >= 0 && c_numero <= 9)) {
                //sigue siendo identificador
                aceptacion(20);
                if(simbolo == "int"){
                    isIdentificador = true;
                    tipo = TipoSimbolo::TIPO;
//                    break;
                }
                c = sigCaracter();
            }else{
                //esto ya no es identificador
                isIdentificador = true;
                atrasCaracter(); //regresar
                tipo = TipoSimbolo::IDENTIFICADOR;
                //return 0;
            }
            //tipo = TipoSimbolo::IDENTIFICADOR;
            //
        }while(!isIdentificador);
    }
    return 0; //TipoSimbolo::WHILE;
}

bool Lexico::explorarReservadas(string palabra, int tipoEnviado, int edoAceptacion){
    int i = 0;
    bool isCadena = false; //rompe cadena
    
    do{
        i++;
        if (c == palabra[i-1]) {
            aceptacion(edoAceptacion);
            if(i <= palabra.length()-1){
                //funcion que evita leer el siguiente al acabarse el identificador
                c = sigCaracter();
            }
        }else if(i==palabra.length()+1 && simbolo.compare(palabra)==0){
            //se ha recorrido toda la cadena y coincide
            tipo = tipoEnviado;
            isCadena = true;
            coincide = true;
            //return 0;
        }else{
            //no es palabra reservada dentro del arreglo
            isCadena = true;
        }
    }while(!isCadena);
    //si es diferente de palabra reservada, cerrar y mandar al do while de coincide
    return coincide;
}

char Lexico::sigCaracter(){
    if (terminado()) return '$';
    return fuente[ind++];
}

char Lexico::atrasCaracter(){
    if (terminado()) return '$';
    return fuente[ind--];
}

void Lexico::sigEstado(int estado){
    this->estado = estado;
    simbolo += c;
}

void Lexico::aceptacion(int estado){
    sigEstado(estado);
    continua = false;
}

void Lexico::continuaEstado(int estado){
    sigEstado(estado);
    continua = true;
}

bool Lexico::terminado(){//fin de cadena
    return ind >= fuente.length();
}

bool Lexico::esLetra(char c){
    return isalpha(c) || c == '_';
}

bool Lexico::esDigito(char c){
    return isdigit(c);
}

bool Lexico::esEspacio(char c){
    return c == ' ' || c == '\t';
}

void Lexico::retroceso(){
    if (c != '$') ind--;
    continua = false;
}
