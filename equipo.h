#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "estadisticasequipo.h"
#include "jugador.h"
#include "lista.h"
#include "estadisticastorneoequipo.h"

using namespace std;

class Equipo
{
private:
    int rankingFIFA;
    string pais;
    string directorTecnico;
    string federacion;
    string confederacion;
    Lista<Jugador> jugadores;
    EstadisticasEquipo estadisticas; // datos cargados desde el CSV
    EstadisticasTorneoEquipo estadisticasTorneo;// datos generados durante la sumulacion

public:
    Equipo();

    Equipo(int rankingFIFA,
           const string& pais,
           const string& directorTecnico,
           const string& federacion,
           const string& confederacion,
           const EstadisticasEquipo& estadisticas);

    Equipo(const Equipo& otro);
    Equipo& operator=(const Equipo& otro);
    ~Equipo();

    int getRankingFIFA() const;
    string getPais() const;
    string getDirectorTecnico() const;
    string getFederacion() const;
    string getConfederacion() const;
    EstadisticasEquipo getEstadisticas() const;

    Lista<Jugador>& getJugadores();
    const Lista<Jugador>& getJugadores() const;

    void setRankingFIFA(int rankingFIFA);
    void setPais(const string& pais);
    void setDirectorTecnico(const string& directorTecnico);
    void setFederacion(const string& federacion);
    void setConfederacion(const string& confederacion);
    void setEstadisticas(const EstadisticasEquipo& estadisticas);

    void generarJugadores();

    bool operator==(const Equipo& otro) const;
    bool operator<(const Equipo& otro) const;

    int memoryUsage() const;
    EstadisticasTorneoEquipo getEstadisticasTorneo() const;
    void setEstadisticasTorneo(const EstadisticasTorneoEquipo& estadisticasTorneo);


};

#endif
