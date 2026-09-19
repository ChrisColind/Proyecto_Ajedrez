#include "ranking.h"
#include <iostream>

using namespace std;

Ranking::Ranking(){
    capacidad=4;
    cantidad=0;
    jugadores=new Jugador*[capacidad];
}

Ranking::~Ranking(){
    for(int i=0 ; i<cantidad ; i++){
        delete jugadores[i];
    }

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

void Ranking::ordenarPorPuntaje(){
    for(int i=0 ; i<cantidad-1 ; i++){
        for(int j=0 ; j<cantidad-1-i ; j++){
            if(jugadores[j]->getPuntaje() < jugadores[j+1]->getPuntaje()){
                Jugador* temporal=jugadores[j];
                jugadores[j]=jugadores[j+1];
                jugadores[j+1]=temporal;
            }
        }
    }
}

void Ranking::mostrarRanking(){
    ordenarPorPuntaje();

    cout<<"===== RANKING DE JUGADORES ====="<<endl;

    for(int i=0 ; i<cantidad ; i++){
        cout<<(i+1)<<". "<<jugadores[i]->getNombre()<<" | Puntaje: "<<jugadores[i]->getPuntaje()<<" | Partidas Jugadas: "<<jugadores[i]->getPartidasJugadas()<<" | Partidas Ganadas: "<<jugadores[i]->getPartidasGanadas()<<endl;
    }
}