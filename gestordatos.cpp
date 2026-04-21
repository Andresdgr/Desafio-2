#include "gestordatos.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Constructor por defecto
GestorDatos::GestorDatos()
{
}

// Constructor de copia
GestorDatos::GestorDatos(const GestorDatos& otro)
{
}

// Destructor
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

    // Saltar la primera línea (título)
    getline(archivo, linea);

    // Saltar la segunda línea (encabezados)
    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        stringstream ss(linea);
        string campo;

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
//contruir equipo
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
