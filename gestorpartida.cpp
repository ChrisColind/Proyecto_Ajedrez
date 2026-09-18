#include <iostream>
#include "gestorpartida.h"
#include <limits>
#include <fstream>
using namespace std;

GestorPartida::GestorPartida(){
    tablero=new Tablero();
    historial=new Historial();
    jugadorRojo=nullptr;
    jugadorAzul=nullptr;
    turno='R';
}

GestorPartida::~GestorPartida(){
    delete tablero;
    delete historial;
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

Jugador* GestorPartida::login(string colorEtiqueta){
    string nombre,contrasena;

    cout<<"Nombre del jugador "<<colorEtiqueta<<": ";
    cin>>nombre;

    if(!Jugador::existeArchivo(nombre)){
        cout<<"[ERROR] Ese usuario no existe, debe crear una cuenta primero"<<endl;
        return nullptr;
    }

    Jugador* jugadorCargado=Jugador::cargarDesdeArchivo(nombre);

    cout<<"Contrasena: ";
    cin>>contrasena;

    while(contrasena!=jugadorCargado->getContrasena()){
        cout<<"[ERROR] Contrasena incorrecta, intente de nuevo: ";
        cin>>contrasena;
    }

    return jugadorCargado;
}

Jugador* GestorPartida::crearUsuario(string colorEtiqueta){
    string nombre,contrasena;

    cout<<"Nombre de usuario nuevo ("<<colorEtiqueta<<"): ";
    cin>>nombre;

    if(Jugador::existeArchivo(nombre)){
        cout<<"[ERROR] Ese nombre ya esta en uso"<<endl;
        return nullptr;
    }

    cout<<"Cree una contrasena: ";
    cin>>contrasena;

    Jugador* jugadorNuevo=new Jugador(nombre,contrasena);
    jugadorNuevo->guardarEnArchivo();

    return jugadorNuevo;
}

Jugador* GestorPartida::obtenerJugador(string colorEtiqueta){
    int opcion;
    Jugador* jugador=nullptr;

    while(jugador==nullptr){
        cout<<"\n--- Jugador "<<colorEtiqueta<<" ---"<<endl;
        cout<<"1. Iniciar sesion"<<endl;
        cout<<"2. Crear cuenta"<<endl;
        cout<<"Seleccione una opcion: ";

        if(!(cin>>opcion)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"[ERROR] Ingrese un numero valido (1 o 2)"<<endl;
            continue;
        }

        if(opcion==1){
            jugador=login(colorEtiqueta);
        }
        else if(opcion==2){
            jugador=crearUsuario(colorEtiqueta);
        }
        else{
            cout<<"[ERROR] Opcion invalida"<<endl;
        }
    }

    return jugador;
}

bool GestorPartida::esJaquemate(char color){//revisa si hay una forma de hacer que el rey salga de jaque, true significa que no encontro ni un movimiento posible, false que si encontro
    if(!tablero->estaEnJaque(color)){
        return false;
    }

    for(int filaOrigen=0 ; filaOrigen<8 ; filaOrigen++){
        for(int columnaOrigen=0 ; columnaOrigen<8 ; columnaOrigen++){

            if(tablero->hayPiezaEn(filaOrigen,columnaOrigen) && tablero->colorEnCasilla(filaOrigen,columnaOrigen)==color){

                for(int filaDestino=0 ; filaDestino<8 ; filaDestino++){
                    for(int columnaDestino=0 ; columnaDestino<8 ; columnaDestino++){

                        bool esCasillaPropia=(tablero->hayPiezaEn(filaDestino,columnaDestino) && tablero->colorEnCasilla(filaDestino,columnaDestino)==color);

                        if(esCasillaPropia){
                            continue;
                        }

                        bool esMovimientoValido=tablero->movimientoValido(filaOrigen,columnaOrigen,filaDestino,columnaDestino);

                        if(esMovimientoValido){
                            bool siguDejandoEnJaque=tablero->dejaEnJaquePropio(filaOrigen,columnaOrigen,filaDestino,columnaDestino);

                            if(!siguDejandoEnJaque){
                                return false;
                            }
                        }
                    }
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
            cargarPartida();
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
    if(jugadorRojo!=nullptr){
        delete jugadorRojo;
    }

    if(jugadorAzul!=nullptr){
        delete jugadorAzul;
    }

    jugadorRojo=obtenerJugador("Rojo");
    jugadorAzul=obtenerJugador("Azul");

    turno='R';

    jugarTurnos();
}

void GestorPartida::jugarTurnos(){
    string entrada;
    int filaOrigen,columnaOrigen,filaDestino,columnaDestino;

    while(true){
        tablero->imprimir();

        cout<<"Turno: "<<(turno=='R' ? "Rojos" : "Azules")<<endl;
        cout<<"Casilla origen (o 'salir', o 'guardar'): ";
        cin>>entrada;

        if(entrada=="salir"){
            break;
        }

        if(entrada=="guardar"){
            guardarPartida();
            continue;
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

        if(tablero->simboloEnCasilla(filaOrigen,columnaOrigen)=='K' && entrada.length()==2){
            int filaDestinoTemp,columnaDestinoTemp;

            if(tablero->convertirCoordenada(entrada,filaDestinoTemp,columnaDestinoTemp)){
                int diferenciaColumna=columnaDestinoTemp-columnaOrigen;

                if(diferenciaColumna==2 || diferenciaColumna==-2){
                    bool esCorto=(diferenciaColumna==2);

                    if(!tablero->enroqueValido(turno,esCorto)){
                        cout<<"[ERROR] Enroque invalido"<<endl;
                        continue;
                    }

                    tablero->hacerEnroque(turno,esCorto);
                    cambiarTurno();
                    continue;
                }
            }
        }

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
        historial->agregarMovimiento(new Movimiento(filaOrigen,columnaOrigen,filaDestino,columnaDestino));

        if(tablero->esPromocion(filaDestino,columnaDestino)){
            tablero->promocionarPeon(filaDestino,columnaDestino);
            cout<<"El peon fue coronado a Reina"<<endl;
        }

        char jugadorPerdedor=(turno=='R') ? 'A' : 'R';

        if(esJaquemate(jugadorPerdedor)){
            tablero->imprimir();

            Jugador* ganador=(turno=='R') ? jugadorRojo : jugadorAzul;
            Jugador* perdedor=(turno=='R') ? jugadorAzul : jugadorRojo;

            ganador->registrarVictoria();
            perdedor->registrarDerrota();

            ganador->guardarEnArchivo();
            perdedor->guardarEnArchivo();

            cout<<"Jaque mate, ganan los "<<(turno=='R' ? "Rojos" : "Azules")<<"! ("<<ganador->getNombre()<<")"<<endl;
            break;
        }
        else if(tablero->estaEnJaque(jugadorPerdedor)){
            cout<<"Jaque al Rey "<<(jugadorPerdedor=='R' ? "Rojo" : "Azul")<<"!"<<endl;
        }

        cambiarTurno();
    }
}

void GestorPartida::guardarPartida(){
    ofstream archivo("Partidas/partida_guardada.txt");

    archivo<<turno<<endl;
    archivo<<jugadorRojo->getNombre()<<endl;
    archivo<<jugadorAzul->getNombre()<<endl;

    tablero->guardarEnArchivo(archivo);

    archivo.close();

    cout<<"Partida guardada con exito!"<<endl;
}

void GestorPartida::cargarPartida(){
    ifstream archivo("Partidas/partida_guardada.txt");

    if(!archivo.good()){
        cout<<"[ERROR] No hay ninguna partida guardada"<<endl;
        return;
    }

    string nombreRojo,nombreAzul;

    archivo>>turno;
    archivo>>nombreRojo;
    archivo>>nombreAzul;

    if(jugadorRojo!=nullptr){
        delete jugadorRojo;
    }

    if(jugadorAzul!=nullptr){
        delete jugadorAzul;
    }

    jugadorRojo=Jugador::cargarDesdeArchivo(nombreRojo);
    jugadorAzul=Jugador::cargarDesdeArchivo(nombreAzul);

    tablero->cargarDesdeArchivo(archivo);

    archivo.close();

    jugarTurnos();
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