#include "tablaclasificacion.h"
#include <iostream>

using namespace std;

TablaClasificacion::TablaClasificacion()
{
}

TablaClasificacion::TablaClasificacion(const Grupo& grupo)
{
    generarDesdeGrupo(grupo);
}

TablaClasificacion::TablaClasificacion(const TablaClasificacion& otra)
{
    filas = otra.filas;
}

TablaClasificacion& TablaClasificacion::operator=(const TablaClasificacion& otra)
{
    if (this != &otra)
    {
        filas = otra.filas;
    }

    return *this;
}

TablaClasificacion::~TablaClasificacion()
{
}

void TablaClasificacion::generarDesdeGrupo(const Grupo& grupo)
{
    filas = Lista<FilaClasificacion>();

    for (int i = 0; i < grupo.tamano(); i++)
    {
        Equipo equipo = grupo.getEquipos().consultar(i);

        FilaClasificacion fila(equipo, grupo.getNombre());

        filas.agregar(fila, filas.tamano());
    }
}
void TablaClasificacion::ordenar()
{
    filas.ordenar();
}

void TablaClasificacion::imprimir() const
{
    cout << "\nEquipo | PJ | PG | PE | PP | GF | GC | DG | PTS\n";

    for (int i = 0; i < filas.tamano(); i++)
    {
        const FilaClasificacion& f = filas.consultar(i);

        cout << f.getEquipo().getPais() << " | "
             << f.getPartidosJugados() << " | "
             << f.getPartidosGanados() << " | "
             << f.getPartidosEmpatados() << " | "
             << f.getPartidosPerdidos() << " | "
             << f.getGolesAFavor() << " | "
             << f.getGolesEnContra() << " | "
             << f.getDiferenciaGoles() << " | "
             << f.getPuntos()
             << endl;
    }
}

int TablaClasificacion::tamano() const
{
    return filas.tamano();
}

FilaClasificacion TablaClasificacion::getFila(int posicion) const
{
    return filas.consultar(posicion);
}

Lista<FilaClasificacion>& TablaClasificacion::getFilas()
{
    return filas;
}

const Lista<FilaClasificacion>& TablaClasificacion::getFilas() const
{
    return filas;
}
