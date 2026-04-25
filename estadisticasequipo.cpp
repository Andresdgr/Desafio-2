#include "estadisticasequipo.h"

//class::metodocontructor
EstadisticasEquipo::EstadisticasEquipo()
{
    golesAFavor = 0;
    golesEnContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}
//recibimos todos los valores y los asignamos a los atributos
EstadisticasEquipo::EstadisticasEquipo(int gf, int gc, int pg, int pe, int pp, int ta, int tr, int f)
{
    golesAFavor = gf;
    golesEnContra = gc;
    partidosGanados = pg;
    partidosEmpatados = pe;
    partidosPerdidos = pp;
    tarjetasAmarillas = ta;
    tarjetasRojas = tr;
    faltas = f;
}


EstadisticasEquipo::EstadisticasEquipo(const EstadisticasEquipo& otra)
{
    golesAFavor = otra.golesAFavor;
    golesEnContra = otra.golesEnContra;
    partidosGanados = otra.partidosGanados;
    partidosEmpatados = otra.partidosEmpatados;
    partidosPerdidos = otra.partidosPerdidos;
    tarjetasAmarillas = otra.tarjetasAmarillas;
    tarjetasRojas = otra.tarjetasRojas;
    faltas = otra.faltas;
}

// GETTERS
int EstadisticasEquipo::getGolesAFavor() const {
    return golesAFavor;
}
int EstadisticasEquipo::getGolesEnContra() const {
    return golesEnContra;
}
int EstadisticasEquipo::getPartidosGanados() const {
    return partidosGanados;
}
int EstadisticasEquipo::getPartidosEmpatados() const {
    return partidosEmpatados;
}
int EstadisticasEquipo::getPartidosPerdidos() const {
    return partidosPerdidos;
}
int EstadisticasEquipo::getTarjetasAmarillas() const {
    return tarjetasAmarillas;
}
int EstadisticasEquipo::getTarjetasRojas() const {
    return tarjetasRojas;
}
int EstadisticasEquipo::getFaltas() const {
    return faltas;
}

// SETTERS
void EstadisticasEquipo::setGolesAFavor(int gf) {
    golesAFavor = gf;
}
void EstadisticasEquipo::setGolesEnContra(int gc) {
    golesEnContra = gc;
}
void EstadisticasEquipo::setPartidosGanados(int pg) {
    partidosGanados = pg;
}
void EstadisticasEquipo::setPartidosEmpatados(int pe) {
    partidosEmpatados = pe;
}
void EstadisticasEquipo::setPartidosPerdidos(int pp) {
    partidosPerdidos = pp;
}
void EstadisticasEquipo::setTarjetasAmarillas(int ta) {
    tarjetasAmarillas = ta;
}
void EstadisticasEquipo::setTarjetasRojas(int tr) {
    tarjetasRojas = tr;
}
void EstadisticasEquipo::setFaltas(int f) {
    faltas = f;
}

EstadisticasEquipo& EstadisticasEquipo::operator=(const EstadisticasEquipo& otra)
{
    if (this != &otra)
    {
        golesAFavor = otra.golesAFavor;
        golesEnContra = otra.golesEnContra;
        partidosGanados = otra.partidosGanados;
        partidosEmpatados = otra.partidosEmpatados;
        partidosPerdidos = otra.partidosPerdidos;
        tarjetasAmarillas = otra.tarjetasAmarillas;
        tarjetasRojas = otra.tarjetasRojas;
        faltas = otra.faltas;
    }

    return *this;
}

int EstadisticasEquipo::memoryUsage() const
{
    return sizeof(golesAFavor)
    + sizeof(golesEnContra)
        + sizeof(partidosGanados)
        + sizeof(partidosEmpatados)
        + sizeof(partidosPerdidos)
        + sizeof(tarjetasAmarillas)
        + sizeof(tarjetasRojas)
        + sizeof(faltas);
}
