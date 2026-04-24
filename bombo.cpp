#include "bombo.h"
#include <cstdlib>

void Bombo::agregarEquipo(Equipo* e)
{
    equipos.agregar(e, equipos.tamano());
}

int Bombo::tamano() const
{
    return equipos.tamano();
}

Lista<Equipo*>& Bombo::getEquipos()
{
    return equipos;
}

Equipo* Bombo::sacarAleatorio()
{
    int idx = rand() % equipos.tamano();

    Equipo* elegido = equipos.consultar(idx);

    // mover último a la posición idx (simular eliminación)
    equipos.consultar(idx) = equipos.consultar(equipos.tamano() - 1);

    equipos.reducirTamano();

    return elegido;
}

