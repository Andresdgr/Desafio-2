#include "estadisticastorneoequipo.h"

EstadisticasTorneoEquipo::EstadisticasTorneoEquipo()
{
    puntos = 0;
    partidosJugados = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    golesAFavor = 0;
    golesEnContra = 0;
}

EstadisticasTorneoEquipo::EstadisticasTorneoEquipo(const EstadisticasTorneoEquipo& otra)
{
    puntos = otra.puntos;
    partidosJugados = otra.partidosJugados;
    partidosGanados = otra.partidosGanados;
    partidosEmpatados = otra.partidosEmpatados;
    partidosPerdidos = otra.partidosPerdidos;
    golesAFavor = otra.golesAFavor;
    golesEnContra = otra.golesEnContra;
}

EstadisticasTorneoEquipo& EstadisticasTorneoEquipo::operator=(const EstadisticasTorneoEquipo& otra)
{
    if (this != &otra)
    {
        puntos = otra.puntos;
        partidosJugados = otra.partidosJugados;
        partidosGanados = otra.partidosGanados;
        partidosEmpatados = otra.partidosEmpatados;
        partidosPerdidos = otra.partidosPerdidos;
        golesAFavor = otra.golesAFavor;
        golesEnContra = otra.golesEnContra;
    }

    return *this;
}

EstadisticasTorneoEquipo::~EstadisticasTorneoEquipo()
{
}

int EstadisticasTorneoEquipo::getPuntos() const { return puntos; }
int EstadisticasTorneoEquipo::getPartidosJugados() const { return partidosJugados; }
int EstadisticasTorneoEquipo::getPartidosGanados() const { return partidosGanados; }
int EstadisticasTorneoEquipo::getPartidosEmpatados() const { return partidosEmpatados; }
int EstadisticasTorneoEquipo::getPartidosPerdidos() const { return partidosPerdidos; }
int EstadisticasTorneoEquipo::getGolesAFavor() const { return golesAFavor; }
int EstadisticasTorneoEquipo::getGolesEnContra() const { return golesEnContra; }
int EstadisticasTorneoEquipo::getDiferenciaGoles() const { return golesAFavor - golesEnContra; }

void EstadisticasTorneoEquipo::registrarVictoria(int gf, int gc)
{
    partidosJugados++;
    partidosGanados++;
    puntos += 3;
    golesAFavor += gf;
    golesEnContra += gc;
}

void EstadisticasTorneoEquipo::registrarEmpate(int gf, int gc)
{
    partidosJugados++;
    partidosEmpatados++;
    puntos += 1;
    golesAFavor += gf;
    golesEnContra += gc;
}

void EstadisticasTorneoEquipo::registrarDerrota(int gf, int gc)
{
    partidosJugados++;
    partidosPerdidos++;
    golesAFavor += gf;
    golesEnContra += gc;
}

int EstadisticasTorneoEquipo::memoryUsage() const
{
    return sizeof(puntos)
    + sizeof(partidosJugados)
        + sizeof(partidosGanados)
        + sizeof(partidosEmpatados)
        + sizeof(partidosPerdidos)
        + sizeof(golesAFavor)
        + sizeof(golesEnContra);
}
