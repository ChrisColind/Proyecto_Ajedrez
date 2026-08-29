#include <iostream>
#include <limits>
#include "Tablero.h"
using namespace std;

int main(){
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

        switch (opcion){

        case 1:{
            Tablero tablero;
            tablero.imprimir();
            //carga el tablero
            break;
        }
        case 2:{
            //carga la partida
            break;
        }
        case 3:{
            //muestra el ranking
            break;
        }
        case 4:
            //solo cierra el programa
            break;
        }

    }while(opcion!=4);

    return 0;
}