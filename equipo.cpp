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
Equipo::Equipo(int rankingFIFA, const string& pais, const string& directorTecnico,
               const string& federacion, const string& confederacion,
               const EstadisticasEquipo& estadisticas)
{
    this->rankingFIFA = rankingFIFA;
    this->pais = pais;
    this->directorTecnico = directorTecnico;
    this->federacion = federacion;
    this->confederacion = confederacion;
    this->estadisticas = estadisticas;
}

// Constructor de copia
Equipo::Equipo(const Equipo& copia)
{
    rankingFIFA = copia.rankingFIFA;
    pais = copia.pais;
    directorTecnico = copia.directorTecnico;
    federacion = copia.federacion;
    confederacion = copia.confederacion;
    estadisticas = copia.estadisticas;
}

// Destructor
//Equipo::~Equipo()
//{
//}

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

// Setters
void Equipo::setRankingFIFA(int rankingFIFA)
{
    this->rankingFIFA = rankingFIFA;
}

void Equipo::setPais(const string& pais)
{
    this->pais = pais; // this->pais representa el atributo pais del objeto actual.
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

// Sobrecarga del operador ==
bool Equipo::operator==(const Equipo& otro) const
{
    return pais == otro.pais;
}
