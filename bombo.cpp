#include "bombo.h"

Bombo::Bombo()
{
    numero = 0;
}

Bombo::Bombo(int numero)
{
    this->numero = numero;
}

Bombo::Bombo(const Bombo& otro)
{
    numero = otro.numero;
    equipos = otro.equipos;
}

Bombo& Bombo::operator=(const Bombo& otro)
{
    if (this != &otro)
    {
        numero = otro.numero;
        equipos = otro.equipos;
    }

    return *this;
}

Bombo::~Bombo()
{
}

int Bombo::getNumero() const
{
    return numero;
}

Lista<Equipo>& Bombo::getEquipos()
{
    return equipos;
}

const Lista<Equipo>& Bombo::getEquipos() const
{
    return equipos;
}

void Bombo::setNumero(int numero)
{
    this->numero = numero;
}

void Bombo::setEquipos(const Lista<Equipo>& equipos)
{
    this->equipos = equipos;
}

void Bombo::agregarEquipo(const Equipo& equipo)
{
    equipos.agregar(equipo, equipos.tamano());
}

int Bombo::tamano() const
{
    return equipos.tamano();
}

bool Bombo::estaVacio() const
{
    return equipos.esVacia();
}

int Bombo::memoryUsage() const
{
    return sizeof(numero) + equipos.memoryUsage();
}
