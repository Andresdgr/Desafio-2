#ifndef BOMBO_H
#define BOMBO_H

#include "equipo.h"
#include "lista.h"

class Bombo
{
private:
    Lista<Equipo*> equipos;

public:
    void agregarEquipo(Equipo* e);
    Equipo* sacarAleatorio();
    int tamano() const;

    Lista<Equipo*>& getEquipos();
};

#endif
