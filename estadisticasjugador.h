#ifndef ESTADISTICASJUGADOR_H
#define ESTADISTICASJUGADOR_H

class EstadisticasJugador
{
private:
    int minutosJugados;
    int goles;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    EstadisticasJugador();
    EstadisticasJugador(int minutos, int goles, int amarillas, int rojas, int faltas);
    EstadisticasJugador(const EstadisticasJugador& otra);
    EstadisticasJugador& operator=(const EstadisticasJugador& otra);
    ~EstadisticasJugador();

    int getMinutosJugados() const;
    int getGoles() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    void setMinutosJugados(int minutos);
    void setGoles(int goles);
    void setTarjetasAmarillas(int amarillas);
    void setTarjetasRojas(int rojas);
    void setFaltas(int faltas);

    void agregarMinutos(int minutos);
    void agregarGol();
    void agregarTarjetaAmarilla();
    void agregarTarjetaRoja();
    void agregarFalta();

    int memoryUsage() const;
};

#endif
