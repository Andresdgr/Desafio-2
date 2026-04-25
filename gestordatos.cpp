#include "gestordatos.h"
#include "medidorrecursos.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

GestorDatos::GestorDatos()
{
}

GestorDatos::GestorDatos(const GestorDatos& /*otro*/)
{
}

GestorDatos::~GestorDatos()
{
}

void GestorDatos::cargarEquiposDesdeCSV(const string& rutaArchivo, Lista<Equipo>& equipos)
{
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo CSV");
    }

    string linea;

    getline(archivo, linea);
    MedidorRecursos::sumarIteracion();

    getline(archivo, linea);
    MedidorRecursos::sumarIteracion();

    while (getline(archivo, linea))
    {
        MedidorRecursos::sumarIteracion();

        if (linea.empty())
        {
            continue;
        }

        stringstream ss(linea);

        string rankingStr;
        string pais;
        string directorTecnico;
        string federacion;
        string confederacion;
        string golesAFavorStr;
        string golesEnContraStr;
        string partidosGanadosStr;
        string partidosEmpatadosStr;
        string partidosPerdidosStr;

        getline(ss, rankingStr, ';');
        getline(ss, pais, ';');
        getline(ss, directorTecnico, ';');
        getline(ss, federacion, ';');
        getline(ss, confederacion, ';');
        getline(ss, golesAFavorStr, ';');
        getline(ss, golesEnContraStr, ';');
        getline(ss, partidosGanadosStr, ';');
        getline(ss, partidosEmpatadosStr, ';');
        getline(ss, partidosPerdidosStr, ';');

        MedidorRecursos::sumarIteraciones(10);

        int rankingFIFA = stoi(rankingStr);
        int golesAFavor = stoi(golesAFavorStr);
        int golesEnContra = stoi(golesEnContraStr);
        int partidosGanados = stoi(partidosGanadosStr);
        int partidosEmpatados = stoi(partidosEmpatadosStr);
        int partidosPerdidos = stoi(partidosPerdidosStr);

        EstadisticasEquipo estadisticas(
            golesAFavor,
            golesEnContra,
            partidosGanados,
            partidosEmpatados,
            partidosPerdidos,
            0,
            0,
            0
            );

        Equipo equipo(
            rankingFIFA,
            pais,
            directorTecnico,
            federacion,
            confederacion,
            estadisticas
            );

        equipos.agregar(equipo, equipos.tamano());
    }

    archivo.close();
}

void GestorDatos::guardarHistoricoEquipos(const string& rutaArchivo, Lista<Grupo>& grupos)
{
    ofstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        throw runtime_error("No se pudo crear el archivo historico de equipos");
    }

    archivo << "pais;rankingFIFA;golesAFavor;golesEnContra;partidosGanados;"
            << "partidosEmpatados;partidosPerdidos;tarjetasAmarillas;"
            << "tarjetasRojas;faltas\n";

    for (int i = 0; i < grupos.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        Grupo& grupo = grupos.consultar(i);

        for (int j = 0; j < grupo.tamano(); j++)
        {
            MedidorRecursos::sumarIteracion();

            Equipo& equipo = grupo.getEquipos().consultar(j);
            EstadisticasEquipo est = equipo.getEstadisticas();

            archivo << equipo.getPais() << ";"
                    << equipo.getRankingFIFA() << ";"
                    << est.getGolesAFavor() << ";"
                    << est.getGolesEnContra() << ";"
                    << est.getPartidosGanados() << ";"
                    << est.getPartidosEmpatados() << ";"
                    << est.getPartidosPerdidos() << ";"
                    << est.getTarjetasAmarillas() << ";"
                    << est.getTarjetasRojas() << ";"
                    << est.getFaltas()
                    << "\n";
        }
    }

    archivo.close();
}

void GestorDatos::guardarHistoricoJugadores(const string& rutaArchivo, Lista<Grupo>& grupos)
{
    ofstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        throw runtime_error("No se pudo crear el archivo historico de jugadores");
    }

    archivo << "pais;numeroCamiseta;nombre;posicion;minutosJugados;goles;"
            << "tarjetasAmarillas;tarjetasRojas;faltas\n";

    for (int i = 0; i < grupos.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        Grupo& grupo = grupos.consultar(i);

        for (int j = 0; j < grupo.tamano(); j++)
        {
            MedidorRecursos::sumarIteracion();

            Equipo& equipo = grupo.getEquipos().consultar(j);
            Lista<Jugador>& jugadores = equipo.getJugadores();

            for (int k = 0; k < jugadores.tamano(); k++)
            {
                MedidorRecursos::sumarIteracion();

                Jugador& jugador = jugadores.consultar(k);
                EstadisticasJugador est = jugador.getEstadisticas();

                archivo << equipo.getPais() << ";"
                        << jugador.getNumeroCamiseta() << ";"
                        << jugador.getNombre() << ";"
                        << jugador.getPosicion() << ";"
                        << est.getMinutosJugados() << ";"
                        << est.getGoles() << ";"
                        << est.getTarjetasAmarillas() << ";"
                        << est.getTarjetasRojas() << ";"
                        << est.getFaltas()
                        << "\n";
            }
        }
    }

    archivo.close();
}
