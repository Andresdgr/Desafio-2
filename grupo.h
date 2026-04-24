#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"
#include "partido.h"
#include "lista.h"

class Grupo
{
private:
    char letra;
    Lista<Equipo*> equipos;
    Lista<Partido> partidos;

public:
    Grupo(char letra);

    void agregarEquipo(Equipo* equipo);

    void generarPartidos();
    void simular();

    void imprimir();

};

#endif
