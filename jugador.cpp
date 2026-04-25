#include "jugador.h"

Jugador::Jugador()
{
    nombre = "";
    numeroCamiseta = 0;
    posicion = "";
}

Jugador::Jugador(const string& nombre, int numeroCamiseta, const string& posicion)
{
    this->nombre = nombre;
    this->numeroCamiseta = numeroCamiseta;
    this->posicion = posicion;
}

Jugador::Jugador(const string& nombre, int numeroCamiseta, const string& posicion,
                 const EstadisticasJugador& estadisticas)
{
    this->nombre = nombre;
    this->numeroCamiseta = numeroCamiseta;
    this->posicion = posicion;
    this->estadisticas = estadisticas;
}

Jugador::Jugador(const Jugador& otro)
{
    nombre = otro.nombre;
    numeroCamiseta = otro.numeroCamiseta;
    posicion = otro.posicion;
    estadisticas = otro.estadisticas;
}

Jugador& Jugador::operator=(const Jugador& otro)
{
    if (this != &otro)
    {
        nombre = otro.nombre;
        numeroCamiseta = otro.numeroCamiseta;
        posicion = otro.posicion;
        estadisticas = otro.estadisticas;
    }

    return *this;
}

Jugador::~Jugador()
{
}

string Jugador::getNombre() const
{
    return nombre;
}

int Jugador::getNumeroCamiseta() const
{
    return numeroCamiseta;
}

string Jugador::getPosicion() const
{
    return posicion;
}

EstadisticasJugador Jugador::getEstadisticas() const
{
    return estadisticas;
}

void Jugador::setNombre(const string& nombre)
{
    this->nombre = nombre;
}

void Jugador::setNumeroCamiseta(int numero)
{
    numeroCamiseta = numero;
}

void Jugador::setPosicion(const string& posicion)
{
    this->posicion = posicion;
}

void Jugador::setEstadisticas(const EstadisticasJugador& estadisticas)
{
    this->estadisticas = estadisticas;
}

bool Jugador::operator==(const Jugador& otro) const
{
    return numeroCamiseta == otro.numeroCamiseta;
}

bool Jugador::operator<(const Jugador& otro) const
{
    return numeroCamiseta < otro.numeroCamiseta;
}

int Jugador::memoryUsage() const
{
    return sizeof(numeroCamiseta)
    + nombre.capacity()
        + posicion.capacity()
        + estadisticas.memoryUsage();
}
