#include "ranking.h"
#include <iostream>

using namespace std;

Ranking::Ranking(){
    capacidad=4;
    cantidad=0;
    jugadores=new Jugador*[capacidad];
}

Ranking::~Ranking(){
    delete[] jugadores;
}
void Ranking::agregarJugador(Jugador* jugador){
    if(cantidad==capacidad){
        int nuevaCapacidad=capacidad*2;
        Jugador** nuevoArreglo=new Jugador*[nuevaCapacidad];

        for(int i=0 ; i<cantidad ; i++){
            nuevoArreglo[i]=jugadores[i];
        }

        delete[] jugadores;
        jugadores=nuevoArreglo;
        capacidad=nuevaCapacidad;
    }

    jugadores[cantidad]=jugador;
    cantidad++;
}