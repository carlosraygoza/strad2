# Compilador
Compilador realizado en el seminario de Traductores de Lenguajes 2
## Contenido

A continuación se listan los símbolos que deberá reconocer el analizador léxico:

* Identificadores = letra (letra|digito)*  
* Entero = digito+  
* Real = entero.entero  
* Operador de adición: + | -    
* Operador de multiplicación: * | /  
* Operador de asignación: =  
* Operador relacional: < | > | <= | >= | != | ==  
* Operador And: &&   
* Operador Or: ||   
* Operador Not: !  
* Parentesis: (,)  
* Llave: { , }  
* Punto y coma: ;  

Además de las siguientes palabras reservadas: 
* if
* while
* return
* else
* int
* float

Lectura de archivo *.lr*  donde hace lectura de 
- Número de reglas
- ID del No terminal
- Longitud de regla
- Nombre de regla
- Magnitud de matriz
- Valores de matriz

Va creando nodos para lograr el árbol sintáctico  

![Arbol](/79.gif)  


# EJEMPLO
### Entrada  
```
int main(){
  int d;   
  b=3;   
  return 0;   
}
```

### Gramática de pila
- Inicio  
```
Pila: $ 0   
Token: int  
accion: 5  
  ```
- Final  
```
Pila: $ 0 programa 1   
Token: $  
accion: -1  
```

### Generación de código
```
.data  
d dword 0  

.code  
main:  
push 3  
pop eax  
mov d, eax  
ret  
print str$(eax)  
print chr$(10)  
exit  
end main  
```
