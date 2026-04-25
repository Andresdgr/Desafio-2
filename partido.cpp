#include "partido.h"
#include "medidorrecursos.h"
#include "estadisticastorneoequipo.h"

#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

Partido::Partido()
{
    equipo1 = nullptr;
    equipo2 = nullptr;

    golesEquipo1 = 0;
    golesEquipo2 = 0;
    jugado = false;

    sede = "nombreSede";
    arbitro1 = "codArbitro1";
    arbitro2 = "codArbitro2";
    arbitro3 = "codArbitro3";
    hora = "00:00";
    fecha = "";
}

Partido::Partido(Equipo* equipo1, Equipo* equipo2)
{
    this->equipo1 = equipo1;
    this->equipo2 = equipo2;

    golesEquipo1 = 0;
    golesEquipo2 = 0;
    jugado = false;

    sede = "nombreSede";
    arbitro1 = "codArbitro1";
    arbitro2 = "codArbitro2";
    arbitro3 = "codArbitro3";
    hora = "00:00";
    fecha = "";
}

Partido::Partido(const Partido& otro)
{
    equipo1 = otro.equipo1;
    equipo2 = otro.equipo2;

    golesEquipo1 = otro.golesEquipo1;
    golesEquipo2 = otro.golesEquipo2;
    jugado = otro.jugado;

    sede = otro.sede;
    arbitro1 = otro.arbitro1;
    arbitro2 = otro.arbitro2;
    arbitro3 = otro.arbitro3;
    hora = otro.hora;
    fecha = otro.fecha;

    titularesEquipo1 = otro.titularesEquipo1;
    titularesEquipo2 = otro.titularesEquipo2;
    goleadoresEquipo1 = otro.goleadoresEquipo1;
    goleadoresEquipo2 = otro.goleadoresEquipo2;
}

Partido& Partido::operator=(const Partido& otro)
{
    if (this != &otro)
    {
        equipo1 = otro.equipo1;
        equipo2 = otro.equipo2;

        golesEquipo1 = otro.golesEquipo1;
        golesEquipo2 = otro.golesEquipo2;
        jugado = otro.jugado;

        sede = otro.sede;
        arbitro1 = otro.arbitro1;
        arbitro2 = otro.arbitro2;
        arbitro3 = otro.arbitro3;
        hora = otro.hora;
        fecha = otro.fecha;

        titularesEquipo1 = otro.titularesEquipo1;
        titularesEquipo2 = otro.titularesEquipo2;
        goleadoresEquipo1 = otro.goleadoresEquipo1;
        goleadoresEquipo2 = otro.goleadoresEquipo2;
    }

    return *this;
}

Partido::~Partido()
{
}

Equipo* Partido::getEquipo1() const
{
    return equipo1;
}

Equipo* Partido::getEquipo2() const
{
    return equipo2;
}

int Partido::getGolesEquipo1() const
{
    return golesEquipo1;
}

int Partido::getGolesEquipo2() const
{
    return golesEquipo2;
}

bool Partido::estaJugado() const
{
    return jugado;
}

string Partido::getSede() const
{
    return sede;
}

string Partido::getArbitro1() const
{
    return arbitro1;
}

string Partido::getArbitro2() const
{
    return arbitro2;
}

string Partido::getArbitro3() const
{
    return arbitro3;
}

string Partido::getHora() const
{
    return hora;
}

string Partido::getFecha() const
{
    return fecha;
}

void Partido::configurarLogistica(const string& fecha)
{
    this->fecha = fecha;

    sede = "nombreSede";
    arbitro1 = "codArbitro1";
    arbitro2 = "codArbitro2";
    arbitro3 = "codArbitro3";
    hora = "00:00";

    MedidorRecursos::sumarIteracion();
}

bool Partido::camisetaYaSeleccionada(Lista<int>& camisetas, int numero) const
{
    for (int i = 0; i < camisetas.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        if (camisetas.consultar(i) == numero)
        {
            return true;
        }
    }

    return false;
}

void Partido::seleccionarTitulares(Equipo* equipo, Lista<Jugador*>& titulares)
{
    if (equipo == nullptr)
        return;

    Lista<int> camisetasSeleccionadas;
    Lista<Jugador>& jugadores = equipo->getJugadores();

    while (titulares.tamano() < 11 && jugadores.tamano() > 0)
    {
        MedidorRecursos::sumarIteracion();

        int indice = rand() % jugadores.tamano();
        Jugador& jugador = jugadores.consultar(indice);

        if (!camisetaYaSeleccionada(camisetasSeleccionadas, jugador.getNumeroCamiseta()))
        {
            titulares.agregar(&jugador, titulares.tamano());
            camisetasSeleccionadas.agregar(jugador.getNumeroCamiseta(), camisetasSeleccionadas.tamano());
        }
    }
}

void Partido::simularEventosJugadores(Lista<Jugador*>& titulares)
{
    for (int i = 0; i < titulares.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        Jugador* jugador = titulares.consultar(i);

        if (jugador == nullptr)
            continue;

        EstadisticasJugador est = jugador->getEstadisticas();

        est.agregarMinutos(90);

        int probPrimeraAmarilla = rand() % 10000;
        if (probPrimeraAmarilla < 600)
        {
            est.agregarTarjetaAmarilla();

            int probSegundaAmarilla = rand() % 10000;
            if (probSegundaAmarilla < 115)
            {
                est.agregarTarjetaAmarilla();
                est.agregarTarjetaRoja();
            }
        }

        int probPrimeraFalta = rand() % 10000;
        if (probPrimeraFalta < 1300)
        {
            est.agregarFalta();

            int probSegundaFalta = rand() % 10000;
            if (probSegundaFalta < 275)
            {
                est.agregarFalta();

                int probTerceraFalta = rand() % 10000;
                if (probTerceraFalta < 70)
                {
                    est.agregarFalta();
                }
            }
        }

        jugador->setEstadisticas(est);
    }
}

void Partido::asignarGolesAJugadores(Lista<Jugador*>& titulares, Lista<int>& goleadores, int goles)
{
    if (titulares.tamano() == 0)
        return;

    for (int i = 0; i < goles; i++)
    {
        MedidorRecursos::sumarIteracion();

        int indice = rand() % titulares.tamano();
        Jugador* jugador = titulares.consultar(indice);

        if (jugador == nullptr)
            continue;

        EstadisticasJugador est = jugador->getEstadisticas();
        est.agregarGol();
        jugador->setEstadisticas(est);

        goleadores.agregar(jugador->getNumeroCamiseta(), goleadores.tamano());
    }
}

void Partido::simular()
{
    MedidorRecursos::sumarIteracion();

    if (equipo1 == nullptr || equipo2 == nullptr)
        return;

    seleccionarTitulares(equipo1, titularesEquipo1);
    seleccionarTitulares(equipo2, titularesEquipo2);

    EstadisticasEquipo est1 = equipo1->getEstadisticas();
    EstadisticasEquipo est2 = equipo2->getEstadisticas();

    const double alpha = 0.6;
    const double beta = 0.4;
    const double mu = 1.35;

    int pj1 = est1.getPartidosGanados()
              + est1.getPartidosEmpatados()
              + est1.getPartidosPerdidos();

    int pj2 = est2.getPartidosGanados()
              + est2.getPartidosEmpatados()
              + est2.getPartidosPerdidos();

    double gf1 = (pj1 > 0)
                     ? static_cast<double>(est1.getGolesAFavor()) / pj1
                     : mu;

    double gc1 = (pj1 > 0)
                     ? static_cast<double>(est1.getGolesEnContra()) / pj1
                     : mu;

    double gf2 = (pj2 > 0)
                     ? static_cast<double>(est2.getGolesAFavor()) / pj2
                     : mu;

    double gc2 = (pj2 > 0)
                     ? static_cast<double>(est2.getGolesEnContra()) / pj2
                     : mu;

    double lambda1 = mu * pow(gf1 / mu, alpha) * pow(gc2 / mu, beta);
    double lambda2 = mu * pow(gf2 / mu, alpha) * pow(gc1 / mu, beta);

    if (lambda1 < 0)
        lambda1 = 0;

    if (lambda2 < 0)
        lambda2 = 0;

    static random_device rd;
    static mt19937 gen(rd());

    poisson_distribution<int> distribucion1(lambda1);
    poisson_distribution<int> distribucion2(lambda2);

    golesEquipo1 = distribucion1(gen);
    golesEquipo2 = distribucion2(gen);

    asignarGolesAJugadores(titularesEquipo1, goleadoresEquipo1, golesEquipo1);
    asignarGolesAJugadores(titularesEquipo2, goleadoresEquipo2, golesEquipo2);

    simularEventosJugadores(titularesEquipo1);
    simularEventosJugadores(titularesEquipo2);

    jugado = true;

    MedidorRecursos::sumarIteraciones(30);

    actualizarEstadisticasEquipos();
}

void Partido::actualizarEstadisticasEquipos()
{
    MedidorRecursos::sumarIteracion();

    if (equipo1 == nullptr || equipo2 == nullptr)
        return;

    EstadisticasEquipo est1 = equipo1->getEstadisticas();
    EstadisticasEquipo est2 = equipo2->getEstadisticas();

    est1.setGolesAFavor(est1.getGolesAFavor() + golesEquipo1);
    est1.setGolesEnContra(est1.getGolesEnContra() + golesEquipo2);

    est2.setGolesAFavor(est2.getGolesAFavor() + golesEquipo2);
    est2.setGolesEnContra(est2.getGolesEnContra() + golesEquipo1);

    if (golesEquipo1 > golesEquipo2)
    {
        est1.setPartidosGanados(est1.getPartidosGanados() + 1);
        est2.setPartidosPerdidos(est2.getPartidosPerdidos() + 1);
    }
    else if (golesEquipo2 > golesEquipo1)
    {
        est2.setPartidosGanados(est2.getPartidosGanados() + 1);
        est1.setPartidosPerdidos(est1.getPartidosPerdidos() + 1);
    }
    else
    {
        est1.setPartidosEmpatados(est1.getPartidosEmpatados() + 1);
        est2.setPartidosEmpatados(est2.getPartidosEmpatados() + 1);
    }

    equipo1->setEstadisticas(est1);
    equipo2->setEstadisticas(est2);

    EstadisticasTorneoEquipo torneo1 = equipo1->getEstadisticasTorneo();
    EstadisticasTorneoEquipo torneo2 = equipo2->getEstadisticasTorneo();

    if (golesEquipo1 > golesEquipo2)
    {
        torneo1.registrarVictoria(golesEquipo1, golesEquipo2);
        torneo2.registrarDerrota(golesEquipo2, golesEquipo1);
    }
    else if (golesEquipo2 > golesEquipo1)
    {
        torneo2.registrarVictoria(golesEquipo2, golesEquipo1);
        torneo1.registrarDerrota(golesEquipo1, golesEquipo2);
    }
    else
    {
        torneo1.registrarEmpate(golesEquipo1, golesEquipo2);
        torneo2.registrarEmpate(golesEquipo2, golesEquipo1);
    }

    equipo1->setEstadisticasTorneo(torneo1);
    equipo2->setEstadisticasTorneo(torneo2);

    MedidorRecursos::sumarIteraciones(14);
}

void Partido::imprimirResultado() const
{
    if (equipo1 == nullptr || equipo2 == nullptr)
        return;

    cout << fecha
         << " " << hora
         << " | " << sede
         << " | "
         << arbitro1 << ", "
         << arbitro2 << ", "
         << arbitro3
         << " | "
         << equipo1->getPais()
         << " " << golesEquipo1
         << " - "
         << golesEquipo2
         << " "
         << equipo2->getPais()
         << endl;

    cout << "Goleadores " << equipo1->getPais() << ": ";
    if (goleadoresEquipo1.esVacia())
    {
        cout << "Sin goles";
    }
    else
    {
        for (int i = 0; i < goleadoresEquipo1.tamano(); i++)
        {
            cout << "#" << goleadoresEquipo1.consultar(i);

            if (i < goleadoresEquipo1.tamano() - 1)
                cout << ", ";
        }
    }

    cout << endl;

    cout << "Goleadores " << equipo2->getPais() << ": ";
    if (goleadoresEquipo2.esVacia())
    {
        cout << "Sin goles";
    }
    else
    {
        for (int i = 0; i < goleadoresEquipo2.tamano(); i++)
        {
            cout << "#" << goleadoresEquipo2.consultar(i);

            if (i < goleadoresEquipo2.tamano() - 1)
                cout << ", ";
        }
    }

    cout << endl;
}
