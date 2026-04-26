#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

#include "gestordatos.h"
#include "lista.h"
#include "equipo.h"
#include "bombo.h"
#include "grupo.h"
#include "partido.h"
#include "calendario.h"
#include "tablaclasificacion.h"
#include "filaclasificacion.h"
#include "eliminatorias.h"
#include "medidorrecursos.h"

using namespace std;
//ambito global


Lista<Equipo> campeonGlobal;
bool campeonDisponible = false;

Lista<Equipo> subcampeonGlobal;
Lista<Equipo> tercerLugarGlobal;
Lista<Equipo> cuartoLugarGlobal;

Lista<Equipo> r16Global;
Lista<Equipo> r8Global;
Lista<Equipo> r4Global;

bool eliminatoriasSimuladas = false;

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
                 << " | DG: " << est.getDiferenciaGoles()
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

void obtenerClasificados(Lista<Grupo>& grupos,
                         Lista<FilaClasificacion>& primeros,
                         Lista<FilaClasificacion>& segundos,
                         Lista<FilaClasificacion>& terceros)
{
    for (int i = 0; i < grupos.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        Grupo& grupo = grupos.consultar(i);

        TablaClasificacion tabla(grupo);
        tabla.ordenar();

        primeros.agregar(tabla.getFila(0), primeros.tamano());
        segundos.agregar(tabla.getFila(1), segundos.tamano());
        terceros.agregar(tabla.getFila(2), terceros.tamano());
    }

    terceros.ordenar();
}

void imprimirClasificados(Lista<FilaClasificacion>& primeros,
                          Lista<FilaClasificacion>& segundos,
                          Lista<FilaClasificacion>& terceros)
{
    cout << "\n===== CLASIFICACION A DIECISEISAVOS =====\n";

    int total = 0;

    cout << "\n--- Primeros de grupo ---\n";
    for (int i = 0; i < primeros.tamano(); i++)
    {
        Equipo e = primeros.consultar(i).getEquipo();

        cout << e.getPais()
             << " (Grupo "
             << primeros.consultar(i).getGrupoOrigen()
             << ")"
             << endl;

        total++;
    }

    cout << "\n--- Segundos de grupo ---\n";
    for (int i = 0; i < segundos.tamano(); i++)
    {
        Equipo e = segundos.consultar(i).getEquipo();

        cout << e.getPais()
             << " (Grupo "
             << segundos.consultar(i).getGrupoOrigen()
             << ")"
             << endl;

        total++;
    }

    cout << "\n--- Mejores terceros clasificados ---\n";
    for (int i = 0; i < 8; i++)
    {
        Equipo e = terceros.consultar(i).getEquipo();

        cout << e.getPais()
             << " (Grupo "
             << terceros.consultar(i).getGrupoOrigen()
             << ")"
             << endl;

        total++;
    }

    cout << "\nTotal clasificados: " << total << endl;
}

void actualizarEquipoEnHistorico(Lista<Equipo>& historico, const Equipo& actualizado)
{
    for (int i = 0; i < historico.tamano(); i++)
    {
        if (historico.consultar(i).getPais() == actualizado.getPais())
        {
            historico.consultar(i) = actualizado;
            return;
        }
    }

    historico.agregar(actualizado, historico.tamano());
}

void actualizarHistoricoDesdeGrupos(Lista<Grupo>& grupos, Lista<Equipo>& historico)
{
    for (int i = 0; i < grupos.tamano(); i++)
    {
        Grupo& grupo = grupos.consultar(i);

        for (int j = 0; j < grupo.tamano(); j++)
        {
            actualizarEquipoEnHistorico(historico, grupo.getEquipos().consultar(j));
        }
    }
}

void actualizarHistoricoDesdePartidos(Lista<Partido>& partidos, Lista<Equipo>& historico)
{
    for (int i = 0; i < partidos.tamano(); i++)
    {
        Partido& partido = partidos.consultar(i);

        if (partido.getEquipo1() != nullptr)
        {
            actualizarEquipoEnHistorico(historico, *partido.getEquipo1());
        }

        if (partido.getEquipo2() != nullptr)
        {
            actualizarEquipoEnHistorico(historico, *partido.getEquipo2());
        }
    }
}

Lista<Equipo> construirClasificadosDieciseisavos(Lista<FilaClasificacion>& primeros,
                                                 Lista<FilaClasificacion>& segundos,
                                                 Lista<FilaClasificacion>& terceros)
{
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

    return clasificados;
}

void imprimirMaximoGoleadorEquipo(const Equipo& equipo, const string& titulo)
{
    cout << "\n" << titulo << endl;

    const Lista<Jugador>& jugadores = equipo.getJugadores();

    int maxGoles = -1;
    int posMax = -1;

    for (int i = 0; i < jugadores.tamano(); i++)
    {
        const Jugador& jugador = jugadores.consultar(i);
        int goles = jugador.getEstadisticas().getGoles();

        if (goles > maxGoles)
        {
            maxGoles = goles;
            posMax = i;
        }
    }

    if (posMax != -1)
    {
        const Jugador& jugador = jugadores.consultar(posMax);

        cout << jugador.getNombre()
             << " (#" << jugador.getNumeroCamiseta() << ")"
             << " | Equipo: " << equipo.getPais()
             << " | Goles: " << maxGoles
             << endl;
    }
}

void imprimirTop3Goleadores(Lista<Equipo>& equipos)
{
    cout << "\n--- Tres mayores goleadores del mundial ---\n";

    string nombres[3] = {"", "", ""};
    string paises[3] = {"", "", ""};
    int camisetas[3] = {0, 0, 0};
    int golesTop[3] = {-1, -1, -1};

    for (int i = 0; i < equipos.tamano(); i++)
    {
        Equipo& equipo = equipos.consultar(i);
        Lista<Jugador>& jugadores = equipo.getJugadores();

        for (int j = 0; j < jugadores.tamano(); j++)
        {
            Jugador& jugador = jugadores.consultar(j);
            int goles = jugador.getEstadisticas().getGoles();

            for (int k = 0; k < 3; k++)
            {
                if (goles > golesTop[k])
                {
                    for (int m = 2; m > k; m--)
                    {
                        golesTop[m] = golesTop[m - 1];
                        nombres[m] = nombres[m - 1];
                        paises[m] = paises[m - 1];
                        camisetas[m] = camisetas[m - 1];
                    }

                    golesTop[k] = goles;
                    nombres[k] = jugador.getNombre();
                    paises[k] = equipo.getPais();
                    camisetas[k] = jugador.getNumeroCamiseta();
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << ". "
             << nombres[i]
             << " (#" << camisetas[i] << ")"
             << " - " << paises[i]
             << " | Goles: " << golesTop[i]
             << endl;
    }
}

void imprimirEquipoMasGoleadorHistorico(Lista<Equipo>& equipos)
{
    cout << "\n--- Equipo con mas goles historicos actualizados ---\n";

    int posMax = -1;
    int maxGoles = -1;

    for (int i = 0; i < equipos.tamano(); i++)
    {
        int goles = equipos.consultar(i).getEstadisticas().getGolesAFavor();

        if (goles > maxGoles)
        {
            maxGoles = goles;
            posMax = i;
        }
    }

    if (posMax != -1)
    {
        Equipo& equipo = equipos.consultar(posMax);

        cout << equipo.getPais()
             << " | Goles historicos actualizados: "
             << maxGoles
             << endl;
    }
}

string confederacionMasPresente(Lista<Equipo>& equipos)
{
    string confederaciones[10];
    int conteos[10];
    int total = 0;

    for (int i = 0; i < 10; i++)
    {
        conteos[i] = 0;
    }

    for (int i = 0; i < equipos.tamano(); i++)
    {
        string conf = equipos.consultar(i).getConfederacion();
        bool encontrada = false;

        for (int j = 0; j < total; j++)
        {
            if (confederaciones[j] == conf)
            {
                conteos[j]++;
                encontrada = true;
                break;
            }
        }

        if (!encontrada && total < 10)
        {
            confederaciones[total] = conf;
            conteos[total] = 1;
            total++;
        }
    }

    if (total == 0)
    {
        return "Sin datos";
    }

    int posMax = 0;

    for (int i = 1; i < total; i++)
    {
        if (conteos[i] > conteos[posMax])
        {
            posMax = i;
        }
    }

    return confederaciones[posMax] + " (" + to_string(conteos[posMax]) + " equipos)";
}

void imprimirInformeFinalTorneo(Lista<Equipo>& historicoFinal,
                                Lista<Equipo>& campeon,
                                Lista<Equipo>& subcampeon,
                                Lista<Equipo>& tercerLugar,
                                Lista<Equipo>& cuartoLugar,
                                Lista<Equipo>& r16,
                                Lista<Equipo>& r8,
                                Lista<Equipo>& r4)
{
    cout << "\n===== INFORME FINAL DEL TORNEO =====\n";

    cout << "\n--- Ranking de los 4 primeros puestos ---\n";
    cout << "1. Campeon: " << campeon.consultar(0).getPais() << endl;
    cout << "2. Subcampeon: " << subcampeon.consultar(0).getPais() << endl;
    cout << "3. Tercer lugar: " << tercerLugar.consultar(0).getPais() << endl;
    cout << "4. Cuarto lugar: " << cuartoLugar.consultar(0).getPais() << endl;

    imprimirMaximoGoleadorEquipo(
        campeon.consultar(0),
        "--- Maximo goleador del equipo campeon ---"
        );

    imprimirTop3Goleadores(historicoFinal);
    imprimirEquipoMasGoleadorHistorico(historicoFinal);

    cout << "\n--- Confederacion con mayor presencia ---\n";
    cout << "R16: " << confederacionMasPresente(r16) << endl;
    cout << "R8: " << confederacionMasPresente(r8) << endl;
    cout << "R4: " << confederacionMasPresente(r4) << endl;
}

int main()
{
    srand(time(nullptr));

    Lista<Equipo> equipos;
    Lista<Grupo> grupos;
    Lista<Partido> partidos;
    Lista<Equipo> historicoFinal;

    Bombo bombo1(1), bombo2(2), bombo3(3), bombo4(4);

    GestorDatos gestor;
    Calendario calendario("20/06/2026");
    Eliminatorias eliminatorias;

    Lista<FilaClasificacion> primeros, segundos, terceros;

    bool equiposCargados = false;
    bool bombosCreados = false;
    bool gruposCreados = false;
    bool calendarioGenerado = false;
    bool gruposSimulados = false;
    bool clasificadosListos = false;

    int opcion;

    do
    {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Cargar equipos\n";
        cout << "2. Crear bombos\n";
        cout << "3. Crear grupos\n";
        cout << "4. Generar calendario\n";
        cout << "5. Simular fase de grupos\n";
        cout << "6. Mostrar tablas de clasificacion\n";
        cout << "7. Obtener clasificados\n";
        cout << "8. Simular eliminatorias\n";
        cout << "9. Mostrar campeon\n";
        cout << "10. Guardar historicos\n";
        cout << "11. Generar estadisticas finales del torneo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            if (equiposCargados)
            {
                cout << "Los equipos ya fueron cargados.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            gestor.cargarEquiposDesdeCSV(
                "C:/udea/informatica_2/DESAFIO2/selecciones_clasificadas_mundial.csv",
                equipos
                );

            equiposCargados = true;
            cout << "Equipos cargados correctamente.\n";

            MedidorRecursos::mostrarReporte(
                "Carga de equipos desde CSV",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 2:
        {
            if (!equiposCargados)
            {
                cout << "Primero cargue los equipos.\n";
                break;
            }

            if (bombosCreados)
            {
                cout << "Los bombos ya fueron creados.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            cout << "Ordenando equipos por ranking...\n";
            equipos.ordenar();

            cout << "Ajustando anfitrion...\n";

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

            cout << "Creando bombos...\n";

            bombo1 = Bombo(1);
            bombo2 = Bombo(2);
            bombo3 = Bombo(3);
            bombo4 = Bombo(4);

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

            bombosCreados = true;
            cout << "\nBombos creados correctamente.\n";

            MedidorRecursos::mostrarReporte(
                "Creacion de bombos",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 3:
        {
            if (!bombosCreados)
            {
                cout << "Primero cree los bombos.\n";
                break;
            }

            if (gruposCreados)
            {
                cout << "Los grupos ya fueron creados.\n";
                break;
            }

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

            gruposCreados = true;
            cout << "\nGrupos creados correctamente.\n";

            MedidorRecursos::mostrarReporte(
                "Creacion de grupos",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 4:
        {
            if (!gruposCreados)
            {
                cout << "Primero cree los grupos.\n";
                break;
            }

            if (calendarioGenerado)
            {
                cout << "El calendario ya fue generado.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            partidos = calendario.generarCalendarioFaseGrupos(grupos);
            calendarioGenerado = true;

            cout << "Calendario generado correctamente.\n";

            MedidorRecursos::mostrarReporte(
                "Generacion de calendario de fase de grupos",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 5:
        {
            if (!calendarioGenerado)
            {
                cout << "Primero genere el calendario.\n";
                break;
            }

            if (gruposSimulados)
            {
                cout << "La fase de grupos ya fue simulada.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            for (int i = 0; i < partidos.tamano(); i++)
            {
                MedidorRecursos::sumarIteracion();
                partidos.consultar(i).simular();
            }

            imprimirPartidosPorGrupo(partidos);
            actualizarHistoricoDesdeGrupos(grupos, historicoFinal);

            gruposSimulados = true;
            cout << "\nFase de grupos simulada correctamente.\n";

            MedidorRecursos::mostrarReporte(
                "Simulacion de fase de grupos",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 6:
        {
            if (!gruposSimulados)
            {
                cout << "Primero simule la fase de grupos.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            imprimirEstadisticasGrupos(grupos);
            imprimirTablasClasificacion(grupos);

            MedidorRecursos::mostrarReporte(
                "Visualizacion de tablas y estadisticas de grupos",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 7:
        {
            if (!gruposSimulados)
            {
                cout << "Primero simule la fase de grupos.\n";
                break;
            }

            if (clasificadosListos)
            {
                cout << "Los clasificados ya fueron obtenidos.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            obtenerClasificados(grupos, primeros, segundos, terceros);
            imprimirClasificados(primeros, segundos, terceros);

            clasificadosListos = true;

            MedidorRecursos::mostrarReporte(
                "Obtencion de clasificados",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 8:
        {
            if (!clasificadosListos)
            {
                cout << "Primero obtenga los clasificados.\n";
                break;
            }

            if (eliminatoriasSimuladas)
            {
                cout << "Las eliminatorias ya fueron simuladas.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            Lista<Partido> dieciseisavos =
                eliminatorias.generarDieciseisavos(primeros, segundos, terceros);

            eliminatorias.simularRonda(dieciseisavos);
            eliminatorias.imprimirRonda(dieciseisavos, "DIECISEISAVOS DE FINAL");
            actualizarHistoricoDesdePartidos(dieciseisavos, historicoFinal);

            Lista<Equipo> ganadoresDieciseisavos =
                eliminatorias.obtenerGanadores(dieciseisavos);

            Lista<Partido> octavos =
                eliminatorias.generarSiguienteRonda(ganadoresDieciseisavos, "Octavos");

            eliminatorias.simularRonda(octavos);
            eliminatorias.imprimirRonda(octavos, "OCTAVOS DE FINAL");
            actualizarHistoricoDesdePartidos(octavos, historicoFinal);

            Lista<Equipo> ganadoresOctavos =
                eliminatorias.obtenerGanadores(octavos);

            Lista<Partido> cuartos =
                eliminatorias.generarSiguienteRonda(ganadoresOctavos, "Cuartos");

            eliminatorias.simularRonda(cuartos);
            eliminatorias.imprimirRonda(cuartos, "CUARTOS DE FINAL");
            actualizarHistoricoDesdePartidos(cuartos, historicoFinal);

            Lista<Equipo> ganadoresCuartos =
                eliminatorias.obtenerGanadores(cuartos);

            Lista<Partido> semifinales =
                eliminatorias.generarSiguienteRonda(ganadoresCuartos, "Semifinales");

            eliminatorias.simularRonda(semifinales);
            eliminatorias.imprimirRonda(semifinales, "SEMIFINALES");
            actualizarHistoricoDesdePartidos(semifinales, historicoFinal);

            Lista<Equipo> ganadoresSemifinales =
                eliminatorias.obtenerGanadores(semifinales);

            Lista<Equipo> perdedoresSemifinales =
                eliminatorias.obtenerPerdedores(semifinales);

            Lista<Partido> tercerPuesto =
                eliminatorias.generarTercerPuesto(perdedoresSemifinales);

            eliminatorias.simularRonda(tercerPuesto);
            eliminatorias.imprimirRonda(tercerPuesto, "PARTIDO POR EL TERCER PUESTO");
            actualizarHistoricoDesdePartidos(tercerPuesto, historicoFinal);

            tercerLugarGlobal = eliminatorias.obtenerGanadores(tercerPuesto);
            cuartoLugarGlobal = eliminatorias.obtenerPerdedores(tercerPuesto);

            Lista<Partido> final =
                eliminatorias.generarSiguienteRonda(ganadoresSemifinales, "Final");

            eliminatorias.simularRonda(final);
            eliminatorias.imprimirRonda(final, "FINAL");
            actualizarHistoricoDesdePartidos(final, historicoFinal);

            campeonGlobal = eliminatorias.obtenerGanadores(final);
            subcampeonGlobal = eliminatorias.obtenerPerdedores(final);
            campeonDisponible = true;

            r16Global = ganadoresDieciseisavos;
            r8Global = ganadoresOctavos;
            r4Global = ganadoresCuartos;

            eliminatoriasSimuladas = true;

            cout << "\nEliminatorias simuladas correctamente.\n";

            if (!campeonGlobal.esVacia())
            {
                cout << "\n===== CAMPEON DEL MUNDIAL =====\n";
                cout << campeonGlobal.consultar(0).getPais() << endl;
            }

            MedidorRecursos::mostrarReporte(
                "Simulacion de eliminatorias",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, final)
                );

            break;
        }

        case 9:
        {
            if (!campeonDisponible || campeonGlobal.esVacia())
            {
                cout << "Primero simule las eliminatorias.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            cout << "\n===== CAMPEON DEL MUNDIAL =====\n";
            cout << campeonGlobal.consultar(0).getPais() << endl;

            MedidorRecursos::mostrarReporte(
                "Visualizacion del campeon",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 10:
        {
            if (!eliminatoriasSimuladas)
            {
                cout << "Primero simule todo el torneo antes de guardar historicos.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            gestor.guardarHistoricoEquipoDesdeLista(
                "C:/udea/informatica_2/DESAFIO2/historico_equipos.csv",
                historicoFinal
                );

            gestor.guardarHistoricoJugadoresDesdeLista(
                "C:/udea/informatica_2/DESAFIO2/historico_jugadores.csv",
                historicoFinal
                );

            cout << "Historicos guardados correctamente.\n";

            MedidorRecursos::mostrarReporte(
                "Guardado de historicos",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 11:
        {
            if (!eliminatoriasSimuladas)
            {
                cout << "Primero simule las eliminatorias.\n";
                break;
            }

            MedidorRecursos::reiniciar();

            imprimirInformeFinalTorneo(
                historicoFinal,
                campeonGlobal,
                subcampeonGlobal,
                tercerLugarGlobal,
                cuartoLugarGlobal,
                r16Global,
                r8Global,
                r4Global
                );

            MedidorRecursos::mostrarReporte(
                "Generacion de estadisticas finales del torneo",
                calcularMemoriaTotal(equipos, bombo1, bombo2, bombo3, bombo4, grupos, partidos)
                );

            break;
        }

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    return 0;
}
