#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
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

    casillas=new Pieza*[64];

    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            casillas[(fila)*8+(columna)]=nullptr;
        }
    }
}

void Tablero::inicializarPosicionInicial(){

    for(int columna=0 ; columna<8 ; columna++){

        if(columna==0 || columna==7){
            casillas[(0)*8+(columna)]=new Torre('A',0,columna);
            casillas[(7)*8+(columna)]=new Torre('R',7,columna);
        }else if(columna==1 || columna==6){
            casillas[(0)*8+(columna)]=new Caballo('A',0,columna);
            casillas[(7)*8+(columna)]=new Caballo('R',7,columna);
        }else if(columna==2 || columna==5){
            casillas[(0)*8+(columna)]=new Alfil('A',0,columna);
            casillas[(7)*8+(columna)]=new Alfil('R',7,columna);
        }else if(columna==3){
            casillas[(0)*8+(columna)]=new Reina('A',0,columna);
            casillas[(7)*8+(columna)]=new Reina('R',7,columna);
        }else{
            casillas[(0)*8+(columna)]=new Rey('A',0,columna);
            casillas[(7)*8+(columna)]=new Rey('R',7,columna);
        }

        casillas[(1)*8+(columna)]=new Peon('A',1,columna);
        casillas[(6)*8+(columna)]=new Peon('R',6,columna);
    }
}

void Tablero::liberarMemoria(){
    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            if(casillas[(fila)*8+(columna)]!=nullptr){
                delete casillas[(fila)*8+(columna)];

                casillas[(fila)*8+(columna)]=nullptr;
            }
        }
    }

    delete[] casillas;
}

bool Tablero::movimientoValido(int filaOrigen, int columnaOrigen,int filaDestino, int columnaDestino){
    Movimiento movimiento(filaOrigen,columnaOrigen,filaDestino,columnaDestino);
    bool hayPiezaDestino=hayPiezaEn(movimiento.getFilaDestino(),movimiento.getColumnaDestino());
    bool hayObstaculo=hayObstaculoEnTrayectoria(filaOrigen,columnaOrigen,movimiento.getFilaDestino(),movimiento.getColumnaDestino());

    return casillas[(filaOrigen)*8+(columnaOrigen)]->esMovimientoValido(movimiento.getFilaDestino(),movimiento.getColumnaDestino(),hayPiezaDestino,hayObstaculo);
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
    return casillas[(fila)*8+(columna)]!=nullptr;
}

char Tablero::colorEnCasilla(int fila, int columna){
    return casillas[(fila)*8+(columna)]->getColor();
}

char Tablero::simboloEnCasilla(int fila, int columna){
    return casillas[(fila)*8+(columna)]->getSimbolo();
}

bool Tablero::estaEnJaque(char color){ //lo logico de revisar si un rey esta en peligro o no
    int filaRey=-1;
    int columnaRey=-1;

    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            if(hayPiezaEn(fila,columna)){
                if(colorEnCasilla(fila,columna)==color && simboloEnCasilla(fila,columna)=='K'){
                    filaRey=fila;
                    columnaRey=columna;
                }
            }
        }
    }

    char colorContrario=(color=='R') ? 'A' : 'R';

    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            if(hayPiezaEn(fila,columna) && colorEnCasilla(fila,columna)==colorContrario){
                bool hayObstaculo=hayObstaculoEnTrayectoria(fila,columna,filaRey,columnaRey);

                if(casillas[(fila)*8+(columna)]->esMovimientoValido(filaRey,columnaRey,true,hayObstaculo)){
                    return true;
                }
            }
        }
    }

    return false;
}

bool Tablero::dejaEnJaquePropio(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino){
    char colorPieza=casillas[(filaOrigen)*8+(columnaOrigen)]->getColor();

    Pieza* piezaOrigen=casillas[(filaOrigen)*8+(columnaOrigen)];
    Pieza* piezaDestino=casillas[(filaDestino)*8+(columnaDestino)];

    casillas[(filaDestino)*8+(columnaDestino)]=piezaOrigen;
    casillas[(filaOrigen)*8+(columnaOrigen)]=nullptr;

    bool quedaEnJaque=estaEnJaque(colorPieza);

    casillas[(filaOrigen)*8+(columnaOrigen)]=piezaOrigen;
    casillas[(filaDestino)*8+(columnaDestino)]=piezaDestino;

    return quedaEnJaque;
}

void Tablero::moverPieza(int filaOrigen, int columnaOrigen,int filaDestino, int columnaDestino){

    if(casillas[(filaDestino)*8+(columnaDestino)]!=nullptr){
        delete casillas[(filaDestino)*8+(columnaDestino)];
    }

    casillas[(filaDestino)*8+(columnaDestino)]=casillas[(filaOrigen)*8+(columnaOrigen)];
    casillas[(filaOrigen)*8+(columnaOrigen)]=nullptr;
    casillas[(filaDestino)*8+(columnaDestino)]->setPosicion(filaDestino, columnaDestino);
}

bool Tablero::esPromocion(int fila, int columna){
    if(!hayPiezaEn(fila,columna) || simboloEnCasilla(fila,columna)!='P'){
        return false;
    }

    char color=colorEnCasilla(fila,columna);
    int filaFinal=(color=='R') ? 0 : 7;

    return fila==filaFinal;
}

void Tablero::promocionarPeon(int fila, int columna){
    char color=casillas[(fila)*8+(columna)]->getColor();

    delete casillas[(fila)*8+(columna)];

    casillas[(fila)*8+(columna)]=new Reina(color,fila,columna);
}

bool Tablero::enroqueValido(char color, bool esCorto){//revisa que ninguna de las piezas se haya movido en toda la partida, que tengamos espacio, y que no este en jaque el rey, y que no lo deje en jaque, si todo sale correcto, da true
    int fila=(color=='R') ? 7 : 0;
    int columnaRey=4;
    int columnaTorre=(esCorto) ? 7 : 0;

    if(!hayPiezaEn(fila,columnaRey) || simboloEnCasilla(fila,columnaRey)!='K'){
        return false;
    }

    if(!hayPiezaEn(fila,columnaTorre) || simboloEnCasilla(fila,columnaTorre)!='T'){
        return false;
    }

    if(casillas[(fila)*8+(columnaRey)]->getSeHaMovido() || casillas[(fila)*8+(columnaTorre)]->getSeHaMovido()){
        return false;
    }

    int pasoColumna=(esCorto) ? 1 : -1;
    int columnaActual=columnaRey+pasoColumna;

    while(columnaActual!=columnaTorre){
        if(hayPiezaEn(fila,columnaActual)){
            return false;
        }

        columnaActual=columnaActual+pasoColumna;
    }

    if(estaEnJaque(color)){
        return false;
    }

    int columnaIntermedia=columnaRey+pasoColumna;

    if(dejaEnJaquePropio(fila,columnaRey,fila,columnaIntermedia)){
        return false;
    }

    int columnaFinal=columnaRey+(2*pasoColumna);

    if(dejaEnJaquePropio(fila,columnaRey,fila,columnaFinal)){
        return false;
    }

    return true;
}

void Tablero::hacerEnroque(char color, bool esCorto){
    int fila=(color=='R') ? 7 : 0;
    int columnaRey=4;
    int columnaTorre=(esCorto) ? 7 : 0;
    int pasoColumna=(esCorto) ? 1 : -1;

    int columnaFinalRey=columnaRey+(2*pasoColumna);
    int columnaFinalTorre=columnaRey+pasoColumna;

    moverPieza(fila,columnaRey,fila,columnaFinalRey);
    moverPieza(fila,columnaTorre,fila,columnaFinalTorre);
}


void Tablero::imprimir() const{
#ifdef _WIN32
    HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    cout<<"\n    A   B   C   D   E   F   G   H\n";
    cout<<"  +---+---+---+---+---+---+---+---+\n";

    for(int fila=0 ; fila<8 ; fila++){
        int numeroMostrado=8-fila;
        cout<<numeroMostrado<<" |";
        for(int columna=0 ; columna<8 ; columna++){
            Pieza* pieza=casillas[(fila)*8+(columna)];

            if(pieza==nullptr){
                cout<<" . |";
            }else{

                if(pieza->getColor()=='R'){
#ifdef _WIN32
                    SetConsoleTextAttribute(consola, 12);
#else
                    cout<<"\033[31m";
#endif
                }else{
#ifdef _WIN32
                    SetConsoleTextAttribute(consola, 9);
#else
                    cout<<"\033[34m";
#endif
                }

                cout<<" "<<pieza->getSimbolo()<<" ";
#ifdef _WIN32
                SetConsoleTextAttribute(consola, 7);
#else
                cout<<"\033[0m";
#endif
                cout<<"|";
            }
        }

        cout<<" "<<numeroMostrado<<"\n";
        cout<<"  +---+---+---+---+---+---+---+---+\n";
    }

    cout<<"    A   B   C   D   E   F   G   H\n\n";
}

void Tablero::guardarEnArchivo(ofstream &archivo){
    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){

            if(hayPiezaEn(fila,columna)){
                archivo<<colorEnCasilla(fila,columna)<<" "<<simboloEnCasilla(fila,columna)<<" "<<casillas[(fila)*8+(columna)]->getSeHaMovido()<<endl;
            }else{
                archivo<<"-"<<" "<<"-"<<" "<<"0"<<endl;
            }
        }
    }
}

void Tablero::cargarDesdeArchivo(ifstream &archivo){
    liberarMemoria();
    vaciarCasillas();

    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){
            char color,simbolo;
            bool seHaMovido;

            archivo>>color>>simbolo>>seHaMovido;

            if(simbolo=='-'){
                continue;
            }

            Pieza* piezaNueva=nullptr;

            if(simbolo=='P'){
                piezaNueva=new Peon(color,fila,columna);
            }else if(simbolo=='T'){
                piezaNueva=new Torre(color,fila,columna);
            }else if(simbolo=='C'){
                piezaNueva=new Caballo(color,fila,columna);
            }else if(simbolo=='A'){
                piezaNueva=new Alfil(color,fila,columna);
            }else if(simbolo=='R'){
                piezaNueva=new Reina(color,fila,columna);
            }else if(simbolo=='K'){
                piezaNueva=new Rey(color,fila,columna);
            }

            piezaNueva->setSeHaMovido(seHaMovido);
            casillas[(fila)*8+(columna)]=piezaNueva;
        }
    }
}