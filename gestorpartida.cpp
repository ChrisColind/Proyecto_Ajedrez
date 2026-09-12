#include <iostream>
#include "gestorpartida.h"

using namespace std;

GestorPartida::GestorPartida(){
    tablero=new Tablero();
    jugadorRojo=nullptr;
    jugadorAzul=nullptr;
    turno='R';
}

GestorPartida::~GestorPartida(){
    delete tablero;

    if(jugadorRojo!=nullptr){
        delete jugadorRojo;
    }

    if(jugadorAzul!=nullptr){
        delete jugadorAzul;
    }
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
        cout<<"4. Como jugar"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Seleccione una opcion: "<<endl;

        while(!(cin>>opcion) || (opcion<1 || opcion>5)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"[ERROR] Ingrese un dato correcto (1 - 5)"<<endl;
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
            mostrarAyuda();
            break;

        case 5:
            cout<<"[Cerrando el juego...]"<<endl;
            break;
        }

    }while(opcion!=5);
}

void GestorPartida::iniciarPartida(){
    string entrada;
    string nombreRojo,nombreAzul;
    int filaOrigen,columnaOrigen,filaDestino,columnaDestino;

    cout<<"Nombre del jugador Rojo: ";
    cin>>nombreRojo;
    cout<<"Nombre del jugador Azul: ";
    cin>>nombreAzul;

    if(jugadorRojo!=nullptr){
        delete jugadorRojo;
    }

    if(jugadorAzul!=nullptr){
        delete jugadorAzul;
    }

    jugadorRojo=new Jugador(nombreRojo);
    jugadorAzul=new Jugador(nombreAzul);

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

            Jugador* ganador=(turno=='R') ? jugadorRojo : jugadorAzul;
            Jugador* perdedor=(turno=='R') ? jugadorAzul : jugadorRojo;

            ganador->registrarVictoria();
            perdedor->registrarDerrota();

            cout<<"Ganan los "<<(turno=='R' ? "Rojos" : "Azules")<<"! ("<<ganador->getNombre()<<")"<<endl;
            cout<<ganador->getNombre()<<" - Partidas ganadas: "<<ganador->getPartidasGanadas()<<" | Puntaje: "<<ganador->getPuntaje()<<endl;
            break;
        }

        cambiarTurno();
    }
}

void GestorPartida::mostrarAyuda(){
    cout<<endl;
    cout<<"===***INTRUCCIONES PARA JUGAR***==="<<endl;
    cout<<"Cada casilla se nombra con una letra de columna (A-H) y un numero de fila (1-8), ej: ORIGEN: E2, DESTINO: E3."<<endl;
    cout<<"En tu turno debes escribir la casilla de origen y luego la casilla de destino."<<endl;
    cout<<"\n====MOVIMIENTOS DE PIEZA===="<<endl;
    cout<<"Peon (P): avanza 1 casilla al frente (2 SI ES TU PRIMER MOVIMIENTO) y captura en diagonal."<<endl;
    cout<<"Torre (T): se mueve en linea recta, la cantidad de casillas que quiera (FILA O COLUMNA)."<<endl;
    cout<<"Caballo (C): se mueve en forma de L (2 y 1) y es la unica pieza que salta sobre otras."<<endl;
    cout<<"Alfil (A): se mueve en diagonal, la cantidad de casillas que quieras."<<endl;
    cout<<"Reina (R): combina el movimiento de la Torre y el Alfil (RECTA O DIAGONAL)."<<endl;
    cout<<"Rey (K): se mueve 1 sola casilla, en cualquier direccion(NO LA PIERDAS)."<<endl;
    cout<<"\n===COMO GANAR Y COMO PERDER==="<<endl;
    cout<<"(GANAS) si capturas al Rey del equipo contrario."<<endl;
    cout<<"(PIERDES) si tu Rey es capturado por el equipo contrario."<<endl;
    cout<<"Ninguna pieza puede capturar a otra pieza de su mismo color."<<endl;
    cout<<"\nSi deseas salir de una partida en juego solo escribes 'salir' cuando sea tu turno."<<endl;
}