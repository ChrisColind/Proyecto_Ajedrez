#include <iostream>
#include <windows.h>
#include <cctype>

#include "tablero.h"
#include "peon.h"
#include "rey.h"
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

    char simbolosMayores[8]={'T', 'C', 'A', 'R', 'K', 'A', 'C', 'T'};

    for(int columna=0 ; columna<8 ; columna++){
        if(columna==4){
            casillas[0][columna]=new Rey('A',0,columna);
            casillas[7][columna]=new Rey('R',7,columna);
        }else{
            casillas[0][columna]=new Pieza('A',simbolosMayores[columna],0,columna);
            casillas[7][columna]=new Pieza('R',simbolosMayores[columna],7,columna);
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
    int direccion;

    if(casillas[filaOrigen][columnaOrigen]->getColor()=='R'){
        direccion=-1;
    }else{
        direccion=1;
    }

    int filaIntermedia=filaOrigen+direccion;
    bool hayPiezaIntermedia=false;

    if(filaIntermedia>=0 && filaIntermedia<8){
        hayPiezaIntermedia=hayPiezaEn(filaIntermedia,columnaOrigen);
    }

    return casillas[filaOrigen][columnaOrigen]->esMovimientoValido(movimiento.getFilaDestino(),movimiento.getColumnaDestino(),hayPiezaDestino,hayPiezaIntermedia);
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