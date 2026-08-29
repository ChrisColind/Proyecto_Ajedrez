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
    ~Pieza();

    char getColor() const;
    char getSimbolo() const;
    int getFila() const;
    int getColumna() const;
};

#endif // PIEZA_H