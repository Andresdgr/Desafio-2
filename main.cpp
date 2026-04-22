#include <iostream>
#include "gestordatos.h"
#include "lista.h"
#include "equipo.h"
#include "partido.h"

using namespace std;

int main()
{
    srand(time(0));
    try
    {
        Lista<Equipo> equipos;
        GestorDatos gestor;


        gestor.cargarEquiposDesdeCSV("C:/Users/Andres/OneDrive - Universidad de Antioquia/Escritorio/Desafio 2/selecciones_clasificadas_mundial.csv", equipos);

        // tomar dos equipos
        Equipo& e1 = equipos.consultar(0);
        Equipo& e2 = equipos.consultar(1);

        // inicializar jugadores
        e1.inicializarJugadores();
        e2.inicializarJugadores();

        // crear partido
        Partido p(&e1, &e2);

        // simular
        p.simular();

        // mostrar resultado
        cout << e1.getPais() << " " << p.getGoles1()
             << " vs "
             << p.getGoles2() << " " << e2.getPais()
             << endl;

        cout << "Cantidad de equipos cargados: " << equipos.tamano() << endl;
        cout << "----------------------------------------" << endl;

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
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
