#ifndef ELIMINATORIAS_H
#define ELIMINATORIAS_H

#include "partido.h"
#include "filaclasificacion.h"
#include "lista.h"
#include <string>

using namespace std;

class Eliminatorias
{
private:
    Lista<Equipo> equiposRonda;

    void agregarCruce(const FilaClasificacion& filaA,
                      const FilaClasificacion& filaB,
                      Lista<Partido>& partidos);

    void agregarCruceEquipos(const Equipo& equipoA,
                             const Equipo& equipoB,
                             Lista<Partido>& partidos);

    int buscarCompatible(Lista<FilaClasificacion>& lista,
                         char grupoProhibido,
                         int inicio,
                         int fin) const;

public:
    Eliminatorias();
    Eliminatorias(const Eliminatorias& otra);
    Eliminatorias& operator=(const Eliminatorias& otra);
    ~Eliminatorias();

    Lista<Partido> generarDieciseisavos(Lista<FilaClasificacion>& primeros,
                                        Lista<FilaClasificacion>& segundos,
                                        Lista<FilaClasificacion>& terceros);

    Lista<Equipo> obtenerGanadores(Lista<Partido>& partidos);
    Lista<Equipo> obtenerPerdedores(Lista<Partido>& partidos);

    Lista<Partido> generarSiguienteRonda(Lista<Equipo>& ganadores,
                                         const string& nombreRonda);

    Lista<Partido> generarTercerPuesto(Lista<Equipo>& perdedoresSemifinal);

    void simularRonda(Lista<Partido>& partidos);

    void imprimirRonda(Lista<Partido>& partidos, const string& nombreRonda) const;
    void imprimirRondaConfigurada(Lista<Partido>& partidos, const string& nombreRonda) const;
};

#endif
