#include "partido.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Partido::Partido()
{
    equipo1 = nullptr;
    equipo2 = nullptr;
    goles1 = 0;
    goles2 = 0;
}

Partido::Partido(Equipo* e1, Equipo* e2)
{
    equipo1 = e1;
    equipo2 = e2;

    goles1 = 0;
    goles2 = 0;
}


int Partido::getGoles1() const { return goles1; }
int Partido::getGoles2() const { return goles2; }

double Partido::calcularLambda(Equipo* A, Equipo* B)
{
    double GF = A->getEstadisticas().getGolesAFavor();
    double GC = B->getEstadisticas().getGolesEnContra();

    double alpha = 0.6;
    double beta = 0.4;
    double mu = 1.35;

    return mu * (alpha * GF + beta * GC) / 70.0;
}

int Partido::generarGoles(double lambda)
{
    int goles = 0;

    for (int i = 0; i < 10; i++)
    {
        double r = (double) rand() / RAND_MAX;
        if (r < lambda)
        {
            goles++;
        }
    }

    return goles;
}

bool Partido::ocurre(double probabilidad)
{
    double r = (double) rand() / RAND_MAX;
    //cout<<RAND_MAX<<" "<<r<<endl;
    return r < probabilidad;
}

void Partido::simular()
{
    // titulares reales
    titulares1 = equipo1->seleccionarTitulares();
    titulares2 = equipo2->seleccionarTitulares();

    // calcular lambda
    double lambda1 = calcularLambda(equipo1, equipo2);
    double lambda2 = calcularLambda(equipo2, equipo1);

    // generar goles
    goles1 = generarGoles(lambda1);
    goles2 = generarGoles(lambda2);

    // asignar minutos a todos
    for (int i = 0; i < 11; i++)
    {
        titulares1.consultar(i)->agregarMinutos(90);
        titulares1.consultar(i)->incrementarPartidos();

        titulares2.consultar(i)->agregarMinutos(90);
        titulares2.consultar(i)->incrementarPartidos();
    }

    // repartir goles equipo 1
    for (int i = 0; i < goles1; i++)
    {
        int idx = rand() % 11;
        titulares1.consultar(idx)->agregarGol();
    }

    // repartir goles equipo 2
    for (int i = 0; i < goles2; i++)
    {
        int idx = rand() % 11;
        titulares2.consultar(idx)->agregarGol();
    }

    for (int i = 0; i < 11; i++)
    {
        Jugador* j1 = titulares1.consultar(i);
        Jugador* j2 = titulares2.consultar(i);

        // EQUIPO 1
        // Amarillas
        int amarillas1 = 0;

        if (ocurre(0.06))
        {
            j1->agregarAmarilla();
            amarillas1++;
        }

        if (amarillas1 == 1 && ocurre(0.0115))
        {
            j1->agregarAmarilla();
            j1->agregarRoja();
        }

        // Faltas
        if (ocurre(0.13))
        {
            j1->agregarFalta();

            if (ocurre(0.0275))
            {
                j1->agregarFalta();

                if (ocurre(0.007))
                {
                    j1->agregarFalta();
                }
            }
        }

        // EQUIPO 2
        int amarillas2 = 0;

        if (ocurre(0.06))
        {
            j2->agregarAmarilla();
            amarillas2++;
        }

        if (amarillas2 == 1 && ocurre(0.0115))
        {
            j2->agregarAmarilla();
            j2->agregarRoja();
        }

        if (ocurre(0.13))
        {
            j2->agregarFalta();

            if (ocurre(0.0275))
            {
                j2->agregarFalta();

                if (ocurre(0.007))
                {
                    j2->agregarFalta();
                }
            }
        }
    }

    // actualizar estadísticas equipo 1
    EstadisticasEquipo est1 = equipo1->getEstadisticas();
    EstadisticasEquipo est2 = equipo2->getEstadisticas();

    // goles
    est1.setGolesAFavor(est1.getGolesAFavor() + goles1);
    est1.setGolesEnContra(est1.getGolesEnContra() + goles2);

    est2.setGolesAFavor(est2.getGolesAFavor() + goles2);
    est2.setGolesEnContra(est2.getGolesEnContra() + goles1);

    // resultado
    if (goles1 > goles2)
    {
        est1.setPartidosGanados(est1.getPartidosGanados() + 1);
        est2.setPartidosPerdidos(est2.getPartidosPerdidos() + 1);
    }
    else if (goles1 < goles2)
    {
        est2.setPartidosGanados(est2.getPartidosGanados() + 1);
        est1.setPartidosPerdidos(est1.getPartidosPerdidos() + 1);
    }
    else
    {
        est1.setPartidosEmpatados(est1.getPartidosEmpatados() + 1);
        est2.setPartidosEmpatados(est2.getPartidosEmpatados() + 1);
    }

    // guardar cambios
    equipo1->setEstadisticas(est1);
    equipo2->setEstadisticas(est2);
}

Lista<Jugador*>& Partido::getTitulares1() { return titulares1; }
Lista<Jugador*>& Partido::getTitulares2() { return titulares2; }
