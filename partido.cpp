#include "partido.h"
#include <cstdlib>

Partido::Partido(Equipo* e1, Equipo* e2)
{
    equipo1 = e1;
    equipo2 = e2;

    goles1 = 0;
    goles2 = 0;
}

void Partido::simular()
{
    // seleccionar titulares
    titulares1 = equipo1->seleccionarTitulares();
    titulares2 = equipo2->seleccionarTitulares();

    // goles simples (temporal)
    goles1 = rand() % 5;
    goles2 = rand() % 5;
}

int Partido::getGoles1() const { return goles1; }
int Partido::getGoles2() const { return goles2; }
