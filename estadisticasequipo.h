#ifndef ESTADISTICASEQUIPO_H
#define ESTADISTICASEQUIPO_H

class EstadisticasEquipo // Aquí representamos el histórico acumulado de un equipo
{
private:
    // Atributos
    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    // Constructor por defecto
    EstadisticasEquipo();

    // Constructor con parámetros para inicializar el objeto con valores específicos
    EstadisticasEquipo(int gf, int gc, int pg, int pe, int pp, int ta, int tr, int f);

    // Constructor de copia
    EstadisticasEquipo(const EstadisticasEquipo& otra);

    // Destructor
  // ~EstadisticasEquipo();

    // Getters
    int getGolesAFavor() const;
    int getGolesEnContra() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    // Setters
    void setGolesAFavor(int gf);
    void setGolesEnContra(int gc);
    void setPartidosGanados(int pg);
    void setPartidosEmpatados(int pe);
    void setPartidosPerdidos(int pp);
    void setTarjetasAmarillas(int ta);
    void setTarjetasRojas(int tr);
    void setFaltas(int f);

    EstadisticasEquipo& operator=(const EstadisticasEquipo& otra);
    int memoryUsage() const;
};

#endif
