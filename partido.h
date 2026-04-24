#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"
#include "lista.h"
#include "jugador.h"

class Partido
{
private:
    Equipo* equipo1;
    Equipo* equipo2;

    Lista<Jugador*> titulares1;
    Lista<Jugador*> titulares2;

    int goles1;
    int goles2;

    // funciones auxiliares internas
    double calcularLambda(Equipo* A, Equipo* B);
    int generarGoles(double lambda);

public:
    Partido();
    Partido(Equipo* e1, Equipo* e2);
    bool ocurre(double probabilidad);
    void simular();

    int getGoles1() const;
    int getGoles2() const;
    Lista<Jugador*>& getTitulares1();
    Lista<Jugador*>& getTitulares2();
};

#endif
