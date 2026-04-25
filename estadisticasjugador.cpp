#include "estadisticasjugador.h"

EstadisticasJugador::EstadisticasJugador()
{
    minutosJugados = 0;
    goles = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

EstadisticasJugador::EstadisticasJugador(int minutos, int goles, int amarillas, int rojas, int faltas)
{
    this->minutosJugados = minutos;
    this->goles = goles;
    this->tarjetasAmarillas = amarillas;
    this->tarjetasRojas = rojas;
    this->faltas = faltas;
}

EstadisticasJugador::EstadisticasJugador(const EstadisticasJugador& otra)
{
    minutosJugados = otra.minutosJugados;
    goles = otra.goles;
    tarjetasAmarillas = otra.tarjetasAmarillas;
    tarjetasRojas = otra.tarjetasRojas;
    faltas = otra.faltas;
}

EstadisticasJugador& EstadisticasJugador::operator=(const EstadisticasJugador& otra)
{
    if (this != &otra)
    {
        minutosJugados = otra.minutosJugados;
        goles = otra.goles;
        tarjetasAmarillas = otra.tarjetasAmarillas;
        tarjetasRojas = otra.tarjetasRojas;
        faltas = otra.faltas;
    }

    return *this;
}

EstadisticasJugador::~EstadisticasJugador()
{
}

int EstadisticasJugador::getMinutosJugados() const
{
    return minutosJugados;
}

int EstadisticasJugador::getGoles() const
{
    return goles;
}

int EstadisticasJugador::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

int EstadisticasJugador::getTarjetasRojas() const
{
    return tarjetasRojas;
}

int EstadisticasJugador::getFaltas() const
{
    return faltas;
}

void EstadisticasJugador::setMinutosJugados(int minutos)
{
    minutosJugados = minutos;
}

void EstadisticasJugador::setGoles(int goles)
{
    this->goles = goles;
}

void EstadisticasJugador::setTarjetasAmarillas(int amarillas)
{
    tarjetasAmarillas = amarillas;
}

void EstadisticasJugador::setTarjetasRojas(int rojas)
{
    tarjetasRojas = rojas;
}

void EstadisticasJugador::setFaltas(int faltas)
{
    this->faltas = faltas;
}

void EstadisticasJugador::agregarMinutos(int minutos)
{
    minutosJugados += minutos;
}

void EstadisticasJugador::agregarGol()
{
    goles++;
}

void EstadisticasJugador::agregarTarjetaAmarilla()
{
    tarjetasAmarillas++;
}

void EstadisticasJugador::agregarTarjetaRoja()
{
    tarjetasRojas++;
}

void EstadisticasJugador::agregarFalta()
{
    faltas++;
}

int EstadisticasJugador::memoryUsage() const
{
    return sizeof(minutosJugados)
    + sizeof(goles)
        + sizeof(tarjetasAmarillas)
        + sizeof(tarjetasRojas)
        + sizeof(faltas);
}
