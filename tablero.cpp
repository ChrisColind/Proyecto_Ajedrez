#include <iostream>
#include "tablero.h"

using namespace std;

Tablero::Tablero(){
    vaciarCasillas();
    inicializarPosicionInicial();
}

Tablero::~Tablero(){
    liberarMemoria();
}

void Tablero::vaciarCasillas(){
    for(int fila=0 ; fila<8  ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            casillas[fila][columna] = nullptr;
        }
    }
}

void Tablero::inicializarPosicionInicial(){
    char simbolosMayores[8]={'T', 'C', 'A', 'R', 'K', 'A', 'C', 'T'};

    for(int columna=0 ; columna<8; columna++){
        casillas[0][columna] = new Pieza('N', simbolosMayores[columna], 0, columna);
        casillas[1][columna] = new Pieza('N', 'P', 1, columna);
        casillas[6][columna] = new Pieza('B', 'p', 6, columna);
        casillas[7][columna] = new Pieza('B', simbolosMayores[columna], 7, columna);
    }
}

void Tablero::liberarMemoria(){
    for(int fila=0 ; fila<8 ; fila++){
        for(int columna = 0; columna < 8; columna++){
            if(casillas[fila][columna] != nullptr){
                delete casillas[fila][columna];
                casillas[fila][columna] = nullptr;
            }
        }
    }
}

void Tablero::imprimir() const{
    cout<<"\n    A   B   C   D   E   F   G   H\n";
    cout<<"  +---+---+---+---+---+---+---+---+\n";

    for(int fila=0 ; fila<8 ; fila++){
        int numeroMostrado = 8-fila;

        cout << numeroMostrado << " |";
        for(int columna = 0; columna < 8; columna++){
            Pieza* pieza = casillas[fila][columna];
            char caracter = (pieza == nullptr) ? '.' : pieza->getSimbolo();
            cout<<" " << caracter << " |";
        }
        cout<<" " << numeroMostrado << "\n";
        cout<<"  +---+---+---+---+---+---+---+---+\n";
    }

    cout<<"    A   B   C   D   E   F   G   H\n\n";
}