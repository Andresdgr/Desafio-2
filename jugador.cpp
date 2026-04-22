#include "jugador.h"

Jugador::Jugador()
{
    nombre = "";
    apellido = "";
    numeroCamiseta = 0;
    partidosJugados = 0;
    goles = 0;
    minutosJugados = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

Jugador::Jugador(string nombre, string apellido, int numero)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->numeroCamiseta = numero;

    partidosJugados = 0;
    goles = 0;
    minutosJugados = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

string Jugador::getNombre() const { return nombre; }
string Jugador::getApellido() const { return apellido; }
int Jugador::getNumeroCamiseta() const { return numeroCamiseta; }
int Jugador::getGoles() const { return goles; }
int Jugador::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

int Jugador::getTarjetasRojas() const
{
    return tarjetasRojas;
}

int Jugador::getFaltas() const
{
    return faltas;
}

void Jugador::setGoles(int goles)
{
    this->goles = goles;
}

void Jugador::agregarGol()
{
    goles++;
}

void Jugador::agregarMinutos(int minutos)
{
    minutosJugados += minutos;
}

void Jugador::agregarAsistencia()
{
    asistencias++;
}

void Jugador::agregarAmarilla()
{
    tarjetasAmarillas++;
}

void Jugador::agregarRoja()
{
    tarjetasRojas++;
}

void Jugador::agregarFalta()
{
    faltas++;
}

void Jugador::incrementarPartidos()
{
    partidosJugados++;
}
