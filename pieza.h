#ifndef PIEZA_H
#define PIEZA_H

class Pieza{
private:
    char color;
    char simbolo;
    int fila;
    int columna;

public:
    Pieza(char color, char simbolo, int fila, int columna);
    virtual ~Pieza();

    char getColor() const;
    char getSimbolo() const;
    int getFila() const;
    int getColumna() const;

    void setPosicion(int fila, int columna);

    virtual bool esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia);
};

#endif