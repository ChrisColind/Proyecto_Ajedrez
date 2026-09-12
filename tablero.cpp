#include <iostream>
#include <windows.h>
#include <cctype>

#include "tablero.h"
#include "peon.h"
#include "rey.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"
#include "reina.h"
#include "movimiento.h"

using namespace std;

Tablero::Tablero(){
    vaciarCasillas();
    inicializarPosicionInicial();
}

Tablero::~Tablero(){
    liberarMemoria();
}

void Tablero::vaciarCasillas(){

    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            casillas[fila][columna]=nullptr;
        }
    }
}

void Tablero::inicializarPosicionInicial(){

    for(int columna=0 ; columna<8 ; columna++){

        if(columna==0 || columna==7){
            casillas[0][columna]=new Torre('A',0,columna);
            casillas[7][columna]=new Torre('R',7,columna);
        }else if(columna==1 || columna==6){
            casillas[0][columna]=new Caballo('A',0,columna);
            casillas[7][columna]=new Caballo('R',7,columna);
        }else if(columna==2 || columna==5){
            casillas[0][columna]=new Alfil('A',0,columna);
            casillas[7][columna]=new Alfil('R',7,columna);
        }else if(columna==3){
            casillas[0][columna]=new Reina('A',0,columna);
            casillas[7][columna]=new Reina('R',7,columna);
        }else{
            casillas[0][columna]=new Rey('A',0,columna);
            casillas[7][columna]=new Rey('R',7,columna);
        }

        casillas[1][columna]=new Peon('A',1,columna);
        casillas[6][columna]=new Peon('R',6,columna);
    }
}

void Tablero::liberarMemoria(){
    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            if(casillas[fila][columna]!=nullptr){
                delete casillas[fila][columna];

                casillas[fila][columna]=nullptr;
            }
        }
    }
}

bool Tablero::movimientoValido(int filaOrigen, int columnaOrigen,int filaDestino, int columnaDestino){
    Movimiento movimiento(filaOrigen,columnaOrigen,filaDestino,columnaDestino);
    bool hayPiezaDestino=hayPiezaEn(movimiento.getFilaDestino(),movimiento.getColumnaDestino());
    bool hayObstaculo=hayObstaculoEnTrayectoria(filaOrigen,columnaOrigen,movimiento.getFilaDestino(),movimiento.getColumnaDestino());

    return casillas[filaOrigen][columnaOrigen]->esMovimientoValido(movimiento.getFilaDestino(),movimiento.getColumnaDestino(),hayPiezaDestino,hayObstaculo);
}

bool Tablero::hayObstaculoEnTrayectoria(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino){
    int diferenciaFila=filaDestino-filaOrigen;
    int diferenciaColumna=columnaDestino-columnaOrigen;

    int pasoFila=0;
    if(diferenciaFila>0){
        pasoFila=1;
    }
    if(diferenciaFila<0){
        pasoFila=-1;
    }

    int pasoColumna=0;
    if(diferenciaColumna>0){
        pasoColumna=1;
    }
    if(diferenciaColumna<0){
        pasoColumna=-1;
    }

    int filaAbsoluta=(diferenciaFila<0) ? -diferenciaFila : diferenciaFila;
    int columnaAbsoluta=(diferenciaColumna<0) ? -diferenciaColumna : diferenciaColumna;

    bool esLineaRecta=(diferenciaFila==0 || diferenciaColumna==0);
    bool esDiagonal=(filaAbsoluta==columnaAbsoluta);

    //movimientos que no son en linea recta ni en diagonal (ej. el caballo)
    //no tienen "trayectoria" que revisar, por eso no hay obstaculo
    if(!esLineaRecta && !esDiagonal){
        return false;
    }

    int filaActual=filaOrigen+pasoFila;
    int columnaActual=columnaOrigen+pasoColumna;

    while(filaActual!=filaDestino || columnaActual!=columnaDestino){
        if(hayPiezaEn(filaActual,columnaActual)){
            return true;
        }

        filaActual=filaActual+pasoFila;
        columnaActual=columnaActual+pasoColumna;
    }

    return false;
}

bool Tablero::convertirCoordenada(string texto, int &fila, int &columna){
    if(texto.length()!=2){
        return false;
    }

    char letra=toupper(texto[0]);
    char numero=texto[1];

    if(letra<'A' || letra>'H'){
        return false;
    }

    if(numero<'1' || numero>'8'){
        return false;
    }

    columna=letra-'A';
    fila=8-(numero-'0');
    return true;
}

bool Tablero::hayPiezaEn(int fila, int columna){
    return casillas[fila][columna]!=nullptr;
}

char Tablero::colorEnCasilla(int fila, int columna){
    return casillas[fila][columna]->getColor();
}

char Tablero::simboloEnCasilla(int fila, int columna){
    return casillas[fila][columna]->getSimbolo();
}

void Tablero::moverPieza(int filaOrigen, int columnaOrigen,int filaDestino, int columnaDestino){

    if(casillas[filaDestino][columnaDestino]!=nullptr){
        delete casillas[filaDestino][columnaDestino];
    }

    casillas[filaDestino][columnaDestino]=casillas[filaOrigen][columnaOrigen];
    casillas[filaOrigen][columnaOrigen]=nullptr;
    casillas[filaDestino][columnaDestino]->setPosicion(filaDestino, columnaDestino);
}

void Tablero::imprimir() const{
    HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"\n    A   B   C   D   E   F   G   H\n";
    cout<<"  +---+---+---+---+---+---+---+---+\n";

    for(int fila=0 ; fila<8 ; fila++){
        int numeroMostrado=8-fila;
        cout<<numeroMostrado<<" |";
        for(int columna=0 ; columna<8 ; columna++){
            Pieza* pieza=casillas[fila][columna];

            if(pieza==nullptr){
                cout<<" . |";
            }else{

                if(pieza->getColor()=='R'){
                    SetConsoleTextAttribute(consola, 12);
                }else{
                    SetConsoleTextAttribute(consola, 9);
                }

                cout<<" "<<pieza->getSimbolo()<<" ";
                SetConsoleTextAttribute(consola, 7);
                cout<<"|";
            }
        }

        cout<<" "<<numeroMostrado<<"\n";
        cout<<"  +---+---+---+---+---+---+---+---+\n";
    }

    cout<<"    A   B   C   D   E   F   G   H\n\n";
}