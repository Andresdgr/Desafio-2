#include "equipo.h"
#include "jugador.h"
#include <cstdlib>

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

Lista<Jugador>& Equipo::getJugadores()
{
    return jugadores;
}

void Equipo::inicializarJugadores()
{
    int golesEquipo = estadisticas.getGolesAFavor();
    int n = 26;
    int base = golesEquipo / n;
    int extra = golesEquipo % n;

    for (int i = 1; i <= 26; i++)
    {
        string nombre = "nombre" + to_string(i);
        string apellido = "apellido" + to_string(i);

        Jugador jugador(nombre, apellido, i);

        jugadores.agregar(jugador, jugadores.tamano());
    }


    // repartir base a todos
    for (int i = 0; i < n; i++)
    {
        Jugador& j = jugadores.consultar(i);
        j.setGoles(base);
    }

    // repartir sobrantes a los primeros "extra"
    for (int i = 0; i < extra; i++)
    {
        Jugador& j = jugadores.consultar(i);
        j.setGoles(j.getGoles() + 1);
    }
}

Lista<Jugador> Equipo::seleccionarTitulares()
{
    Lista<Jugador> titulares;

    int n = jugadores.tamano();

    while (titulares.tamano() < 11)
    {
        int idx = rand() % n;

        Jugador& candidato = jugadores.consultar(idx);

        bool repetido = false;

        for (int i = 0; i < titulares.tamano(); i++)
        {
            if (titulares.consultar(i).getNumeroCamiseta() == candidato.getNumeroCamiseta())
            {
                repetido = true;
                break;
            }
        }

        if (!repetido)
        {
            titulares.agregar(candidato, titulares.tamano());
        }
    }

    return titulares;
}
