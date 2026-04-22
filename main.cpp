#include <iostream>
#include "gestordatos.h"
#include "lista.h"
#include "equipo.h"

using namespace std;

int main()
{
    try
    {
        Lista<Equipo> equipos;
        GestorDatos gestor;


        gestor.cargarEquiposDesdeCSV("C:/Users/Andres/OneDrive - Universidad de Antioquia/Escritorio/Desafio 2/selecciones_clasificadas_mundial.csv", equipos);

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
