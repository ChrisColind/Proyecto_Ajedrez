#include <iostream>
#include "gestorpartida.h"

using namespace std;

GestorPartida::GestorPartida(){
    tablero=new Tablero();
    turno='R';
}

GestorPartida::~GestorPartida(){
    delete tablero;
}

void GestorPartida::cambiarTurno(){
    turno=(turno=='R') ? 'A' : 'R';
}

bool GestorPartida::verificarGanador(char color){
    for(int fila=0 ; fila<8 ; fila++){
        for(int columna=0 ; columna<8 ; columna++){

            if(tablero->hayPiezaEn(fila,columna)){
                if(tablero->colorEnCasilla(fila,columna)==color && tablero->simboloEnCasilla(fila,columna)=='K'){
                    return false;
                }
            }
        }
    }

    return true;
}

void GestorPartida::menu(){
    int opcion;

    do{
        cout<<"\n===*** JUEGO DE AJEDREZ ***==="<<endl;
        cout<<"1. Nueva partida"<<endl;
        cout<<"2. Cargar partida"<<endl;
        cout<<"3. Ver ranking"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Seleccione una opcion: "<<endl;

        while(!(cin>>opcion) || (opcion<1 || opcion>4)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"[ERROR] Ingrese un dato correcto (1 - 4)"<<endl;
        }

        switch(opcion){
        case 1:
            iniciarPartida();
            break;

        case 2:
            cout<<"nada"<<endl;
            break;

        case 3:
            cout<<"nada"<<endl;
            break;

        case 4:
            cout<<"[Cerrando el juego...]"<<endl;
            break;
        }

    }while(opcion!=4);
}

void GestorPartida::iniciarPartida(){
    string entrada;
    int filaOrigen,columnaOrigen,filaDestino,columnaDestino;

    turno='R';

    while(true){
        tablero->imprimir();

        cout<<"Turno: "<<(turno=='R' ? "Rojos" : "Azules")<<endl;
        cout<<"Casilla origen (o 'salir'): ";
        cin>>entrada;

        if(entrada=="salir"){
            break;
        }

        if(!tablero->convertirCoordenada(entrada,filaOrigen,columnaOrigen)){
            cout<<"[ERROR] Coordenada invalida"<<endl;
            continue;
        }

        if(!tablero->hayPiezaEn(filaOrigen,columnaOrigen)){
            cout<<"[ERROR] No hay pieza en esa casilla"<<endl;
            continue;
        }

        if(tablero->colorEnCasilla(filaOrigen,columnaOrigen)!=turno){
            cout<<"[ERROR] Esa pieza no es tuya"<<endl;
            continue;
        }

        cout<<"Casilla destino: ";
        cin>>entrada;

        if(!tablero->convertirCoordenada(entrada,filaDestino,columnaDestino)){
            cout<<"[ERROR] Coordenada invalida"<<endl;
            continue;
        }

        if(tablero->hayPiezaEn(filaDestino,columnaDestino) && tablero->colorEnCasilla(filaDestino,columnaDestino)==turno){
            cout<<"[ERROR] No puedes capturar tu propia pieza"<<endl;
            continue;
        }

        if(!tablero->movimientoValido(filaOrigen,columnaOrigen,filaDestino,columnaDestino)){
            cout<<"[ERROR] Movimiento invalido"<<endl;
            continue;
        }

        tablero->moverPieza(filaOrigen,columnaOrigen,filaDestino,columnaDestino);
        char jugadorPerdedor=(turno=='R') ? 'A' : 'R';

        if(verificarGanador(jugadorPerdedor)){
            tablero->imprimir();
            cout<<"Ganan los "<<(turno=='R' ? "Rojos" : "Azules")<<"!"<<endl;
            break;
        }

        cambiarTurno();
    }
}