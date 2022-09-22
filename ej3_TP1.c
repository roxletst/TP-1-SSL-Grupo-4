#include <stdio.h>
#include <stdlib.h> // NECESARIO PARA USO DE MALLOC

struct nodo
{
    int resultado;
    char operador;
    struct nodo* izq;
    struct nodo* der;
};

void calcularNodo( struct nodo* nodoPtr)
{
    if(nodoPtr->izq != 0 && nodoPtr->der != 0)
    {
        if(nodoPtr->izq->operador == 'n' && nodoPtr->der->operador == 'n' )
        {
            //calcular resultado
            switch(nodoPtr->operador)
            {
                case '+':
                    nodoPtr->resultado = nodoPtr -> izq -> resultado + nodoPtr -> der -> resultado;
                    break;
                case '-':
                    nodoPtr->resultado = nodoPtr -> izq -> resultado - nodoPtr -> der -> resultado;
                    break;
                case '*':
                    nodoPtr->resultado = nodoPtr -> izq -> resultado * nodoPtr -> der -> resultado;
                    break;
                case '/':
                    if (nodoPtr -> der -> resultado =! 0){
                    nodoPtr->resultado = nodoPtr -> izq -> resultado / nodoPtr -> der -> resultado;
                    }
                    else {
                        printf ("Division por cero");
                    }
                    break;    
                default:
                    printf("Entrada incorrecta: %d \n", 5);
                    return;
            }

            //CAMBIA EL TIPO DE NODO A 'N'
            nodoPtr->operador == 'n';

            //NODOS AUXILIARES Y LIBERACION DE MEMORIA
            struct nodo* tempizq = nodoPtr->izq;
            struct nodo* tempder = nodoPtr->der;
            nodoPtr->izq = tempizq->izq;
            nodoPtr->der = tempder->der;
            free(tempizq);
            free(tempder);
        }
        else
        {
            printf("Entrada incorrecta: %d \n", 4);
            return;
        }
    }
    else{
        printf("Entrada incorrecta: %d \n", 3);
        return;
    }
}

void pushNodoALista( struct nodo**cabeza, struct nodo**cola, char op, int resultado)
{
    struct nodo* nodoPtr = malloc(sizeof(*nodoPtr));
    nodoPtr->operador = op;
    resultado = resultado;
    if(!cabeza)
    {
        *cabeza = nodoPtr;
        *cola = nodoPtr;
        nodoPtr->izq = 0;
        nodoPtr->der = 0;
    }
    else{
        nodoPtr->izq = *cola;
        (*cola)->der = nodoPtr;
        *cola = nodoPtr;
    }
}

enum InputState{
    START = 0,
    NUMBER,
    operador
    };

int main(void) {

int ch;
struct nodo* cabeza = 0;
struct nodo* cola = 0;

//MAQUINA DE ESTADO PARA LA LOGICA

int num = 0;
enum InputState mState = START;

int i = 1;
while ((ch = getchar()) != EOF)
{
    switch(mState)
    {
        case START:
            if (ch >= '0' && ch <= '9'){
                mState = NUMBER;
                num = 0;
                //ESTADO INICIAL PARA NUMERO
            }
            else if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
                mState = operador;
                //ESTADO INICIAL PARA OPERADOR
            }
            else{
                //SI NO RECONOCE NADA
                printf("Caracter no reconocido: %d \n", 1);
                return 0;
            }
        break;
        case NUMBER:
            if (ch >= '0' && ch <= '9'){
                num = num * 10 + ch - '0';
            }
            else if(ch == '+' || ch == '-' || ch == '*'|| ch == '/'){
                mState = operador;
                //PUSH A LISTA DE NUMEROS
                pushNodoALista(&cabeza,&cola,'n',num);//'n' es un numero
            }
            else{
                printf("Entrada incorrecta: %d \n", 2);
                return 0;
            }
        break;
        case operador:
            if (ch >= '0' && ch <= '9'){
                mState = NUMBER;
                num = ch - '0';
            }
            else if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
                pushNodoALista(&cabeza,&cola,ch,0);//PUSH A LA LISTA DE OPERADORES
            }
            else{
                printf("Entrada incorrecta: %d \n", 3);
                return 0;
            }
        break;
    }
}

//CONDICION FINAL AL LLEGAR AL ULTIMO NUMERO PARA HACER PUSH

if(mState == NUMBER)
{
    pushNodoALista(&cabeza,&cola,'n',num);//'n' de numero
}
// OPERACIONES DE PRORIDAD ALTA

struct nodo* nodoAux = cabeza;
while(nodoAux !=cola) // asumo que la ultima entrada es un numero
{
    if(nodoAux->operador == '*' || nodoAux->operador == '/')
    {
        calcularNodo(nodoAux);
    }
}

//OPERACIONES DE BAJA PRIORIDAD

nodoAux = cabeza;
while(nodoAux !=cola)
{
    if(nodoAux->operador == '+' || nodoAux->operador == '-' )
    {
        calcularNodo(nodoAux);
    }
}

//IMPRIME EL RESULTADO

if(cabeza == cola && cabeza->operador == 'n')
{
    printf("resultado : %d\n", cabeza->resultado);
}
else
{
    printf("Error: %d \n", 7);
    return 0;
}


return 0;
}

