#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <string>
#include "equipo.h"
#include "grupo.h"
#include "jugador.h"
#include "lista.h"

using namespace std;

class GestorDatos
{
public:
    GestorDatos();
    GestorDatos(const GestorDatos& otro);
    ~GestorDatos();

    void cargarEquiposDesdeCSV(const string& rutaArchivo, Lista<Equipo>& equipos);

    void guardarHistoricoEquipos(const string& rutaArchivo, Lista<Grupo>& grupos);
    void guardarHistoricoJugadores(const string& rutaArchivo, Lista<Grupo>& grupos);

};

#endif // GESTORDATOS_H
