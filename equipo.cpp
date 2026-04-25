#include "equipo.h"

// Constructor por defecto
Equipo::Equipo()
{
    rankingFIFA = 0;
    pais = "";
    directorTecnico = "";
    federacion = "";
    confederacion = "";
}

// Constructor con parámetros
Equipo::Equipo(int rankingFIFA,
               const string& pais,
               const string& directorTecnico,
               const string& federacion,
               const string& confederacion,
               const EstadisticasEquipo& estadisticas)
{
    this->rankingFIFA = rankingFIFA;
    this->pais = pais;
    this->directorTecnico = directorTecnico;
    this->federacion = federacion;
    this->confederacion = confederacion;
    this->estadisticas = estadisticas;

    generarJugadores();
}

// Constructor de copia
Equipo::Equipo(const Equipo& otro)
{
    rankingFIFA = otro.rankingFIFA;
    pais = otro.pais;
    directorTecnico = otro.directorTecnico;
    federacion = otro.federacion;
    confederacion = otro.confederacion;
    estadisticas = otro.estadisticas;
    jugadores = otro.jugadores;
    estadisticasTorneo = otro.estadisticasTorneo;
}

// Operador de asignación
Equipo& Equipo::operator=(const Equipo& otro)
{
    if (this != &otro)
    {
        rankingFIFA = otro.rankingFIFA;
        pais = otro.pais;
        directorTecnico = otro.directorTecnico;
        federacion = otro.federacion;
        confederacion = otro.confederacion;
        estadisticas = otro.estadisticas;
        jugadores = otro.jugadores;
        estadisticasTorneo = otro.estadisticasTorneo;
    }

    return *this;
}

// Destructor
Equipo::~Equipo()
{
}

// Getters
int Equipo::getRankingFIFA() const
{
    return rankingFIFA;
}

string Equipo::getPais() const
{
    return pais;
}

string Equipo::getDirectorTecnico() const
{
    return directorTecnico;
}

string Equipo::getFederacion() const
{
    return federacion;
}

string Equipo::getConfederacion() const
{
    return confederacion;
}

EstadisticasEquipo Equipo::getEstadisticas() const
{
    return estadisticas;
}

Lista<Jugador>& Equipo::getJugadores()
{
    return jugadores;
}

const Lista<Jugador>& Equipo::getJugadores() const
{
    return jugadores;
}

// Setters
void Equipo::setRankingFIFA(int rankingFIFA)
{
    this->rankingFIFA = rankingFIFA;
}

void Equipo::setPais(const string& pais)
{
    this->pais = pais;
}

void Equipo::setDirectorTecnico(const string& directorTecnico)
{
    this->directorTecnico = directorTecnico;
}

void Equipo::setFederacion(const string& federacion)
{
    this->federacion = federacion;
}

void Equipo::setConfederacion(const string& confederacion)
{
    this->confederacion = confederacion;
}

void Equipo::setEstadisticas(const EstadisticasEquipo& estadisticas)
{
    this->estadisticas = estadisticas;
}

// Genera una plantilla básica de 23 jugadores
void Equipo::generarJugadores()
{
    if (!jugadores.esVacia())
    {
        return;
    }

    for (int i = 1; i <= 23; i++)
    {
        string nombre = pais + "_Jugador_" + to_string(i);
        int numero = i;
        string posicion;

        if (i == 1)
        {
            posicion = "Portero";
        }
        else if (i <= 8)
        {
            posicion = "Defensa";
        }
        else if (i <= 16)
        {
            posicion = "Mediocampo";
        }
        else
        {
            posicion = "Delantero";
        }

        Jugador jugador(nombre, numero, posicion);
        jugadores.agregar(jugador, jugadores.tamano());
    }
}

// Operadores
bool Equipo::operator==(const Equipo& otro) const
{
    return pais == otro.pais;
}

bool Equipo::operator<(const Equipo& otro) const
{
    return rankingFIFA < otro.rankingFIFA;
}

// Memoria aproximada
int Equipo::memoryUsage() const
{
    return sizeof(rankingFIFA)
    + pais.capacity()
        + directorTecnico.capacity()
        + federacion.capacity()
        + confederacion.capacity()
        + estadisticas.memoryUsage()
        + jugadores.memoryUsage();
        + estadisticasTorneo.memoryUsage();
}

EstadisticasTorneoEquipo Equipo::getEstadisticasTorneo() const
{
    return estadisticasTorneo;
}

void Equipo::setEstadisticasTorneo(const EstadisticasTorneoEquipo& estadisticasTorneo)
{
    this->estadisticasTorneo = estadisticasTorneo;
}
