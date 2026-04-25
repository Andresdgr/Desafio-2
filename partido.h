#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"
#include "jugador.h"
#include "lista.h"
#include <string>

using namespace std;

class Partido
{
private:
    Equipo* equipo1;
    Equipo* equipo2;

    int golesEquipo1;
    int golesEquipo2;
    bool jugado;

    string sede;
    string arbitro1;
    string arbitro2;
    string arbitro3;
    string hora;
    string fecha;

    Lista<Jugador*> titularesEquipo1;
    Lista<Jugador*> titularesEquipo2;

    Lista<int> goleadoresEquipo1;
    Lista<int> goleadoresEquipo2;

    void seleccionarTitulares(Equipo* equipo, Lista<Jugador*>& titulares);
    bool camisetaYaSeleccionada(Lista<int>& camisetas, int numero) const;

    void asignarGolesAJugadores(Lista<Jugador*>& titulares, Lista<int>& goleadores, int goles);
    void simularEventosJugadores(Lista<Jugador*>& titulares, int minutos);

    void actualizarEstadisticasEquipos();

    void simularConConfiguracion(int minutos, bool romperEmpate);

public:
    Partido();
    Partido(Equipo* equipo1, Equipo* equipo2);
    Partido(const Partido& otro);
    Partido& operator=(const Partido& otro);
    ~Partido();

    Equipo* getEquipo1() const;
    Equipo* getEquipo2() const;

    int getGolesEquipo1() const;
    int getGolesEquipo2() const;
    bool estaJugado() const;

    string getSede() const;
    string getArbitro1() const;
    string getArbitro2() const;
    string getArbitro3() const;
    string getHora() const;
    string getFecha() const;

    void configurarLogistica(const string& fecha);

    void simular();              // fase de grupos: 90 minutos
    void simularEliminacion();   // eliminatorias: 120 minutos y rompe empate

    void imprimirResultado() const;
};

#endif
