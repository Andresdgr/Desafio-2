#include <iostream>
#include <ctime>
#include <cstdlib>

#include "gestordatos.h"
#include "lista.h"
#include "equipo.h"
#include "bombo.h"
#include "grupo.h"
#include "partido.h"
#include "calendario.h"
#include "tablaclasificacion.h"
#include "filaclasificacion.h"
#include "medidorrecursos.h"

using namespace std;

long long calcularMemoriaTotal(Lista<Equipo>& equipos,
                               Bombo& bombo1,
                               Bombo& bombo2,
                               Bombo& bombo3,
                               Bombo& bombo4,
                               Lista<Grupo>& grupos,
                               Lista<Partido>& partidos)
{
    return equipos.memoryUsage()
    + bombo1.memoryUsage()
        + bombo2.memoryUsage()
        + bombo3.memoryUsage()
        + bombo4.memoryUsage()
        + grupos.memoryUsage()
        + partidos.memoryUsage();
}

void imprimirBombo(Bombo& bombo)
{
    cout << "\n===== BOMBO " << bombo.getNumero() << " =====\n";

    for (int i = 0; i < bombo.tamano(); i++)
    {
        Equipo& e = bombo.getEquipos().consultar(i);

        cout << e.getPais()
             << " - Ranking: "
             << e.getRankingFIFA()
             << endl;
    }
}

void imprimirGrupos(Lista<Grupo>& grupos)
{
    cout << "\n===== GRUPOS =====\n";

    for (int i = 0; i < grupos.tamano(); i++)
    {
        Grupo& grupo = grupos.consultar(i);

        cout << "\nGrupo " << grupo.getNombre() << endl;

        for (int j = 0; j < grupo.tamano(); j++)
        {
            Equipo& equipo = grupo.getEquipos().consultar(j);

            cout << "- "
                 << equipo.getPais()
                 << " (Ranking "
                 << equipo.getRankingFIFA()
                 << ")"
                 << endl;
        }
    }
}

void imprimirPartidosPorGrupo(Lista<Partido>& partidos)
{
    cout << "\n===== RESULTADOS FASE DE GRUPOS POR GRUPO =====\n";

    for (int g = 0; g < 12; g++)
    {
        char nombreGrupo = 'A' + g;

        cout << "\n--- Grupo " << nombreGrupo << " ---\n";

        partidos.consultar(g * 2).imprimirResultado();
        partidos.consultar(g * 2 + 1).imprimirResultado();

        partidos.consultar(24 + g * 2).imprimirResultado();
        partidos.consultar(24 + g * 2 + 1).imprimirResultado();

        partidos.consultar(48 + g * 2).imprimirResultado();
        partidos.consultar(48 + g * 2 + 1).imprimirResultado();
    }
}

void imprimirEstadisticasGrupos(Lista<Grupo>& grupos)
{
    cout << "\n===== ESTADISTICAS DE EQUIPOS POR GRUPO =====\n";

    for (int i = 0; i < grupos.tamano(); i++)
    {
        Grupo& grupo = grupos.consultar(i);

        cout << "\nGrupo " << grupo.getNombre() << endl;

        for (int j = 0; j < grupo.tamano(); j++)
        {
            Equipo& equipo = grupo.getEquipos().consultar(j);
            EstadisticasTorneoEquipo est = equipo.getEstadisticasTorneo();

            cout << equipo.getPais()
                 << " | PJ: " << est.getPartidosJugados()
                 << " | GF: " << est.getGolesAFavor()
                 << " | GC: " << est.getGolesEnContra()
                 << " | PG: " << est.getPartidosGanados()
                 << " | PE: " << est.getPartidosEmpatados()
                 << " | PP: " << est.getPartidosPerdidos()
                 << " | PTS: " << est.getPuntos()
                 << endl;
        }
    }
}

void imprimirTablasClasificacion(Lista<Grupo>& grupos)
{
    cout << "\n===== TABLAS DE POSICIONES =====\n";

    for (int i = 0; i < grupos.tamano(); i++)
    {
        Grupo& grupo = grupos.consultar(i);

        cout << "\nGrupo " << grupo.getNombre() << endl;

        TablaClasificacion tabla(grupo);
        tabla.ordenar();
        tabla.imprimir();
    }
}

void imprimirClasificados(Lista<Grupo>& grupos)
{
    cout << "\n===== CLASIFICACION A DIECISEISAVOS =====\n";

    Lista<FilaClasificacion> primeros;
    Lista<FilaClasificacion> segundos;
    Lista<FilaClasificacion> terceros;

    for (int i = 0; i < grupos.tamano(); i++)
    {
        Grupo& grupo = grupos.consultar(i);

        TablaClasificacion tabla(grupo);
        tabla.ordenar();

        primeros.agregar(tabla.getFila(0), primeros.tamano());
        segundos.agregar(tabla.getFila(1), segundos.tamano());
        terceros.agregar(tabla.getFila(2), terceros.tamano());
    }

    terceros.ordenar();

    Lista<Equipo> clasificados;

    for (int i = 0; i < primeros.tamano(); i++)
    {
        clasificados.agregar(primeros.consultar(i).getEquipo(), clasificados.tamano());
    }

    for (int i = 0; i < segundos.tamano(); i++)
    {
        clasificados.agregar(segundos.consultar(i).getEquipo(), clasificados.tamano());
    }

    for (int i = 0; i < 8; i++)
    {
        clasificados.agregar(terceros.consultar(i).getEquipo(), clasificados.tamano());
    }

    for (int i = 0; i < clasificados.tamano(); i++)
    {
        cout << i + 1 << ". "
             << clasificados.consultar(i).getPais()
             << endl;
    }
}

int main()
{
    try
    {
        srand(time(nullptr));

        Lista<Equipo> equipos;
        GestorDatos gestor;

        Bombo bombo1(1);
        Bombo bombo2(2);
        Bombo bombo3(3);
        Bombo bombo4(4);

        Lista<Grupo> grupos;
        Lista<Partido> partidos;

        MedidorRecursos::reiniciar();

        gestor.cargarEquiposDesdeCSV(
            "C:/udea/informatica_2/DESAFIO2/selecciones_clasificadas_mundial.csv",
            equipos
            );

        cout << "Equipos cargados: " << equipos.tamano() << endl;

        MedidorRecursos::mostrarReporte(
            "Carga de equipos desde CSV",
            calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
            );

        MedidorRecursos::reiniciar();

        equipos.ordenar();

        for (int i = 0; i < equipos.tamano(); i++)
        {
            MedidorRecursos::sumarIteracion();

            string pais = equipos.consultar(i).getPais();

            if (pais == "United States" || pais == "Estados Unidos")
            {
                Equipo usa = equipos.consultar(i);

                for (int j = i; j > 0; j--)
                {
                    MedidorRecursos::sumarIteracion();
                    equipos.consultar(j) = equipos.consultar(j - 1);
                }

                equipos.consultar(0) = usa;
                break;
            }
        }

        MedidorRecursos::mostrarReporte(
            "Ordenamiento por ranking y ajuste de anfitrion",
            calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
            );

        MedidorRecursos::reiniciar();

        for (int i = 0; i < equipos.tamano(); i++)
        {
            MedidorRecursos::sumarIteracion();

            if (i < 12)
                bombo1.agregarEquipo(equipos.consultar(i));
            else if (i < 24)
                bombo2.agregarEquipo(equipos.consultar(i));
            else if (i < 36)
                bombo3.agregarEquipo(equipos.consultar(i));
            else
                bombo4.agregarEquipo(equipos.consultar(i));
        }

        imprimirBombo(bombo1);
        imprimirBombo(bombo2);
        imprimirBombo(bombo3);
        imprimirBombo(bombo4);

        MedidorRecursos::mostrarReporte(
            "Creacion de bombos",
            calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
            );

        MedidorRecursos::reiniciar();

        for (int i = 0; i < 12; i++)
        {
            MedidorRecursos::sumarIteracion();

            Grupo grupo('A' + i);

            grupo.agregarEquipo(bombo1.getEquipos().consultar(i));
            grupo.agregarEquipo(bombo2.getEquipos().consultar(i));
            grupo.agregarEquipo(bombo3.getEquipos().consultar(i));
            grupo.agregarEquipo(bombo4.getEquipos().consultar(i));

            grupos.agregar(grupo, grupos.tamano());
        }

        imprimirGrupos(grupos);

        MedidorRecursos::mostrarReporte(
            "Creacion de grupos",
            calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
            );

        MedidorRecursos::reiniciar();

        Calendario calendario("20/06/2026");
        partidos = calendario.generarCalendarioFaseGrupos(grupos);

        MedidorRecursos::mostrarReporte(
            "Generacion de calendario de fase de grupos",
            calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
            );

        MedidorRecursos::reiniciar();

        for (int i = 0; i < partidos.tamano(); i++)
        {
            MedidorRecursos::sumarIteracion();
            partidos.consultar(i).simular();
        }

        imprimirPartidosPorGrupo(partidos);

        MedidorRecursos::mostrarReporte(
            "Simulacion de partidos de fase de grupos",
            calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
            );

        imprimirEstadisticasGrupos(grupos);

        imprimirTablasClasificacion(grupos);

        imprimirClasificados(grupos);
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
