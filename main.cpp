#include <iostream>
#include <ctime>
#include "gestordatos.h"
#include "lista.h"
#include "equipo.h"
#include "partido.h"
#include "grupo.h"
#include "bombo.h"

using namespace std;

void ordenarEquiposPorRanking(Lista<Equipo>& equipos)
{
    for (int i = 0; i < equipos.tamano(); i++)
    {
        for (int j = i + 1; j < equipos.tamano(); j++)
        {
            if (equipos.consultar(j).getRankingFIFA() < equipos.consultar(i).getRankingFIFA())
            {
                Equipo temp = equipos.consultar(i);
                equipos.consultar(i) = equipos.consultar(j);
                equipos.consultar(j) = temp;
            }
        }
    }
}

void crearBombos(Lista<Equipo>& equipos, Bombo bombos[4])
{
    ordenarEquiposPorRanking(equipos);

    int idx = 0;

    for (int b = 0; b < 4; b++)
    {
        for (int i = 0; i < 12; i++)
        {
            bombos[b].agregarEquipo(&equipos.consultar(idx));
            idx++;
        }
    }
}

int main()
{
    srand(time(0));
    try
    {
        Lista<Equipo> equipos;
        GestorDatos gestor;


        gestor.cargarEquiposDesdeCSV("C:/Users/Andres/OneDrive - Universidad de Antioquia/Escritorio/Desafio 2/selecciones_clasificadas_mundial.csv", equipos);


        cout << "Cantidad de equipos cargados: " << equipos.tamano() << endl;
        cout << "----------------------------------------" << endl;

        // tomar dos equipos
        Equipo& e1 = equipos.consultar(12);
        Equipo& e2 = equipos.consultar(1);

        // inicializar jugadores UNA sola vez
        e1.inicializarJugadores();
        e2.inicializarJugadores();

        // crear partido
        Partido p(&e1, &e2);

        // simular
        p.simular();

        // resultado
        cout << endl;
        cout << e1.getPais() << " " << p.getGoles1() << " vs " << p.getGoles2() << " " << e2.getPais() << endl;

        Jugador& j = e1.getJugadores().consultar(0);

        cout << "Goles primer jugador: " << j.getGoles() << endl;
        cout << "Amarillas: " << j.getTarjetasAmarillas() << endl;
        cout << "Rojas: " << j.getTarjetasRojas() << endl;
        cout << "Faltas: " << j.getFaltas() << endl;


        // verificar que los jugadores si cambiaron
        cout << endl;
        cout << "Goleadores equipo 1:" << endl;
        for (int i = 0; i < 11; i++)
        {
            Jugador* j = p.getTitulares1().consultar(i);
            if (j->getGoles() > 0)
            {
                cout << "Camiseta " << j->getNumeroCamiseta()<<" Goles: "<< j->getGoles() << endl;
            }
        }
        cout << endl;

        Grupo grupoA('A');

        for (int i = 0; i < 4; i++)
        {
            Equipo& e = equipos.consultar(i);
            e.inicializarJugadores();
            grupoA.agregarEquipo(&e);
        }

        grupoA.generarPartidos();
        grupoA.simular();
        grupoA.imprimir();




        Bombo bombos[4];

        crearBombos(equipos, bombos);

        for (int b = 0; b < 4; b++)
        {
            cout << "Bombo " << b+1 << endl;

            for (int i = 0; i < bombos[b].tamano(); i++)
            {
                cout << bombos[b].getEquipos().consultar(i)->getPais() << endl;
            }

            cout << "-------------------" << endl;
        }
        /*
        for (int i = 0; i < equipos.tamano(); i++)
        {
            Equipo& equipo = equipos.consultar(i);
            equipo.inicializarJugadores();
            Jugador& jugador = equipo.getJugadores().consultar(i);


            cout << "Cantidad jugadores: " << equipo.getJugadores().tamano() << endl;

            cout << "Primer jugador: " << equipo.getJugadores().consultar(0).getNombre();
            cout << endl;
            cout<< "Goles Primer jugador: "<< jugador.getGoles() << endl;

            cout << "Equipo #" << i + 1 << endl;
            cout << "Ranking FIFA: " << equipo.getRankingFIFA() << endl;
            cout << "Pais: " << equipo.getPais() << endl;
            cout << "Director tecnico: " << equipo.getDirectorTecnico() << endl;
            cout << "Federacion: " << equipo.getFederacion() << endl;
            cout << "Confederacion: " << equipo.getConfederacion() << endl;
            cout << "Goles a favor: " << equipo.getEstadisticas().getGolesAFavor() << endl;
            cout << "Goles en contra: " << equipo.getEstadisticas().getGolesEnContra() << endl;
            cout << "Partidos ganados: " << equipo.getEstadisticas().getPartidosGanados() << endl;
            cout << "Partidos empatados: " << equipo.getEstadisticas().getPartidosEmpatados() << endl;
            cout << "Partidos perdidos: " << equipo.getEstadisticas().getPartidosPerdidos() << endl;
            cout << "----------------------------------------" << endl;
        }*/
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
