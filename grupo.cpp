#include "grupo.h"

Grupo::Grupo()
{
    nombre = ' ';
}

Grupo::Grupo(char nombre)
{
    this->nombre = nombre;
}

Grupo::Grupo(const Grupo& otro)
{
    nombre = otro.nombre;
    equipos = otro.equipos;
}

Grupo& Grupo::operator=(const Grupo& otro)
{
    if (this != &otro)
    {
        nombre = otro.nombre;
        equipos = otro.equipos;
    }

    return *this;
}

Grupo::~Grupo()
{
}

char Grupo::getNombre() const
{
    return nombre;
}

Lista<Equipo>& Grupo::getEquipos()
{
    return equipos;
}

const Lista<Equipo>& Grupo::getEquipos() const
{
    return equipos;
}

void Grupo::setNombre(char nombre)
{
    this->nombre = nombre;
}

void Grupo::setEquipos(const Lista<Equipo>& equipos)
{
    this->equipos = equipos;
}

void Grupo::agregarEquipo(const Equipo& equipo)
{
    equipos.agregar(equipo, equipos.tamano());
}

int Grupo::tamano() const
{
    return equipos.tamano();
}

bool Grupo::estaVacio() const
{
    return equipos.esVacia();
}

int Grupo::memoryUsage() const
{
    return sizeof(nombre) + equipos.memoryUsage();
}
