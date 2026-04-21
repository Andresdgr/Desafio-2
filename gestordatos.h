#ifndef GESTORDATOS_H
#define GESTORDATOS_H
#include <string>
#include "equipo.h"
#include "lista.h"

using namespace std;

class GestorDatos
{
public:
    GestorDatos();
    GestorDatos(const GestorDatos& otro);
    ~GestorDatos();

    void cargarEquiposDesdeCSV(const string& rutaArchivo, Lista<Equipo>& equipos);
};
#endif // GESTORDATOS_H
