#include "historial.h"
#include <iostream>

using namespace std;

Historial::Historial(){
    capacidad=8;
    cantidad=0;
    movimientos=new Movimiento*[capacidad];
}

Historial::~Historial(){
    for(int i=0 ; i<cantidad ; i++){
        delete movimientos[i];
    }

    delete[] movimientos;
}

void Historial::agregarMovimiento(Movimiento* movimiento){
    if(cantidad==capacidad){
        int nuevaCapacidad=capacidad*2;
        Movimiento** nuevoArreglo=new Movimiento*[nuevaCapacidad];

        for(int i=0 ; i<cantidad ; i++){
            nuevoArreglo[i]=movimientos[i];
        }

        delete[] movimientos;
        movimientos=nuevoArreglo;
        capacidad=nuevaCapacidad;
    }

    movimientos[cantidad]=movimiento;
    cantidad++;
}

void Historial::mostrarHistorial(){
    cout<<"===== HISTORIAL DE MOVIMIENTOS ====="<<endl;

    for(int i=0 ; i<cantidad ; i++){
        cout<<(i+1)<<". ("<<movimientos[i]->getFilaOrigen()<<","<<movimientos[i]->getColumnaOrigen()<<") -> ("<<movimientos[i]->getFilaDestino()<<","<<movimientos[i]->getColumnaDestino()<<")"<<endl;
    }
}