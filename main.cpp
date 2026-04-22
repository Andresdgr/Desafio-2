#include <iostream>
#include <ctime>
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
        for (int i = 0; i < e1.getJugadores().tamano(); i++)
        {
            Jugador& j = e1.getJugadores().consultar(i);

            cout << "Jugador " << j.getNumeroCamiseta()<< " goles: " << j.getGoles()<< endl;
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
