#include "filaclasificacion.h"

FilaClasificacion::FilaClasificacion()
{
    puntos = 0;
    partidosJugados = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    golesAFavor = 0;
    golesEnContra = 0;
}

FilaClasificacion::FilaClasificacion(const Equipo& equipo)
{
    this->equipo = equipo;

    puntos = 0;
    partidosJugados = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    golesAFavor = 0;
    golesEnContra = 0;

    cargarDesdeEquipo();
}

FilaClasificacion::FilaClasificacion(const FilaClasificacion& otra)
{
    equipo = otra.equipo;
    puntos = otra.puntos;
    partidosJugados = otra.partidosJugados;
    partidosGanados = otra.partidosGanados;
    partidosEmpatados = otra.partidosEmpatados;
    partidosPerdidos = otra.partidosPerdidos;
    golesAFavor = otra.golesAFavor;
    golesEnContra = otra.golesEnContra;
}

FilaClasificacion& FilaClasificacion::operator=(const FilaClasificacion& otra)
{
    if (this != &otra)
    {
        equipo = otra.equipo;
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

FilaClasificacion::~FilaClasificacion()
{
}

Equipo FilaClasificacion::getEquipo() const
{
    return equipo;
}

int FilaClasificacion::getPuntos() const
{
    return puntos;
}

int FilaClasificacion::getPartidosJugados() const
{
    return partidosJugados;
}

int FilaClasificacion::getPartidosGanados() const
{
    return partidosGanados;
}

int FilaClasificacion::getPartidosEmpatados() const
{
    return partidosEmpatados;
}

int FilaClasificacion::getPartidosPerdidos() const
{
    return partidosPerdidos;
}

int FilaClasificacion::getGolesAFavor() const
{
    return golesAFavor;
}

int FilaClasificacion::getGolesEnContra() const
{
    return golesEnContra;
}

int FilaClasificacion::getDiferenciaGoles() const
{
    return golesAFavor - golesEnContra;
}

void FilaClasificacion::setEquipo(const Equipo& equipo)
{
    this->equipo = equipo;
    cargarDesdeEquipo();
}

void FilaClasificacion::cargarDesdeEquipo()
{
    EstadisticasTorneoEquipo est = equipo.getEstadisticasTorneo();

    puntos = est.getPuntos();
    partidosJugados = est.getPartidosJugados();
    partidosGanados = est.getPartidosGanados();
    partidosEmpatados = est.getPartidosEmpatados();
    partidosPerdidos = est.getPartidosPerdidos();
    golesAFavor = est.getGolesAFavor();
    golesEnContra = est.getGolesEnContra();
}

bool FilaClasificacion::operator<(const FilaClasificacion& otra) const
{
    if (puntos != otra.puntos)
        return puntos > otra.puntos;

    if (getDiferenciaGoles() != otra.getDiferenciaGoles())
        return getDiferenciaGoles() > otra.getDiferenciaGoles();

    if (golesAFavor != otra.golesAFavor)
        return golesAFavor > otra.golesAFavor;

    return equipo.getRankingFIFA() < otra.equipo.getRankingFIFA();
}
