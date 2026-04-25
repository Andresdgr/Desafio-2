#ifndef FILACLASIFICACION_H
#define FILACLASIFICACION_H

#include "equipo.h"
#include "estadisticastorneoequipo.h"

class FilaClasificacion
{
private:
    Equipo equipo;

    int puntos;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int golesAFavor;
    int golesEnContra;

public:
    FilaClasificacion();
    FilaClasificacion(const Equipo& equipo);
    FilaClasificacion(const FilaClasificacion& otra);
    FilaClasificacion& operator=(const FilaClasificacion& otra);
    ~FilaClasificacion();

    Equipo getEquipo() const;

    int getPuntos() const;
    int getPartidosJugados() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getGolesAFavor() const;
    int getGolesEnContra() const;
    int getDiferenciaGoles() const;

    void setEquipo(const Equipo& equipo);

    void cargarDesdeEquipo();

    bool operator<(const FilaClasificacion& otra) const;
};

#endif // FILACLASIFICACION_H
