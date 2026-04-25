#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "estadisticasjugador.h"

using namespace std;

class Jugador
{
private:
    string nombre;
    int numeroCamiseta;
    string posicion;
    EstadisticasJugador estadisticas;

public:
    Jugador();
    Jugador(const string& nombre, int numeroCamiseta, const string& posicion);
    Jugador(const string& nombre, int numeroCamiseta, const string& posicion,
            const EstadisticasJugador& estadisticas);
    Jugador(const Jugador& otro);
    Jugador& operator=(const Jugador& otro);
    ~Jugador();

    string getNombre() const;
    int getNumeroCamiseta() const;
    string getPosicion() const;
    EstadisticasJugador getEstadisticas() const;

    void setNombre(const string& nombre);
    void setNumeroCamiseta(int numero);
    void setPosicion(const string& posicion);
    void setEstadisticas(const EstadisticasJugador& estadisticas);

    bool operator==(const Jugador& otro) const;
    bool operator<(const Jugador& otro) const;

    int memoryUsage() const;
};

#endif
