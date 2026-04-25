#include "grupo.h"
#include <iostream>

using namespace std;

Grupo::Grupo()
{
    letra = '?';
}

Grupo::Grupo(char letra)
{
    this->letra = letra;
}

void Grupo::agregarEquipo(Equipo* equipo)
{
    equipos.agregar(equipo, equipos.tamano());
}

void Grupo::generarPartidos()
{
    // todos contra todos (4 equipos → 6 partidos)
    for (int i = 0; i < equipos.tamano(); i++)
    {
        for (int j = i + 1; j < equipos.tamano(); j++)
        {
            Partido p(equipos.consultar(i), equipos.consultar(j));
            partidos.agregar(p, partidos.tamano());
        }
    }
}

void Grupo::simular()
{
    for (int i = 0; i < partidos.tamano(); i++)
    {
        partidos.consultar(i).simular();
    }
}

void Grupo::imprimir()
{
    cout << "Grupo " << letra << endl;

    for (int i = 0; i < partidos.tamano(); i++)
    {
        Partido& p = partidos.consultar(i);

        cout << "Partido " << i + 1 << ": ";

        cout << p.getGoles1() << " - " << p.getGoles2() << endl;
    }

    cout << "------------------------" << endl;
}

int Grupo::getCantidadEquipos() const
{
    return equipos.tamano();
}

Equipo* Grupo::getEquipo(int i)
{
    return equipos.consultar(i);
}
