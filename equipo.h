#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "estadisticasequipo.h"
#include "lista.h"
#include "jugador.h"


using namespace std;

class Equipo
{
private:
    int rankingFIFA;
    string pais;
    string directorTecnico;
    string federacion;
    string confederacion;
    EstadisticasEquipo estadisticas;
    Lista<Jugador> jugadores;

public:
    // Constructores
    Equipo();
    Equipo(int rankingFIFA, const string& pais, const string& directorTecnico,
           const string& federacion, const string& confederacion,
           const EstadisticasEquipo& estadisticas);
    Equipo(const Equipo& copia);
    //~Equipo();

    // GETTERS
    int getRankingFIFA() const;
    string getPais() const;
    string getDirectorTecnico() const;
    string getFederacion() const;
    string getConfederacion() const;
    EstadisticasEquipo getEstadisticas() const;//estadisticas es un objeto de estadisticasEquipo

    // SETTERS
    void setRankingFIFA(int rankingFIFA);
    void setPais(const string& pais);
    void setDirectorTecnico(const string& directorTecnico);
    void setFederacion(const string& federacion);
    void setConfederacion(const string& confederacion);
    void setEstadisticas(const EstadisticasEquipo& estadisticas);


    // recarga de Operador ==
    bool operator==(const Equipo& otro) const;

    Lista<Jugador>& getJugadores();
    void inicializarJugadores();
};

#endif // EQUIPO_H
