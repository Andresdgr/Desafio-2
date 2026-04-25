#ifndef ESTADISTICASTORNEOEQUIPO_H
#define ESTADISTICASTORNEOEQUIPO_H

class EstadisticasTorneoEquipo
{
private:
    int puntos;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int golesAFavor;
    int golesEnContra;

public:
    EstadisticasTorneoEquipo();
    EstadisticasTorneoEquipo(const EstadisticasTorneoEquipo& otra);
    EstadisticasTorneoEquipo& operator=(const EstadisticasTorneoEquipo& otra);
    ~EstadisticasTorneoEquipo();

    int getPuntos() const;
    int getPartidosJugados() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getGolesAFavor() const;
    int getGolesEnContra() const;
    int getDiferenciaGoles() const;

    void registrarVictoria(int gf, int gc);
    void registrarEmpate(int gf, int gc);
    void registrarDerrota(int gf, int gc);

    int memoryUsage() const;
};

#endif
