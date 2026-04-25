#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <string>

using namespace std;

class MedidorRecursos
{
private:
    static long long iteraciones;

public:
    static void reiniciar();
    static void sumarIteracion();
    static void sumarIteraciones(long long cantidad);
    static long long getIteraciones();

    static void mostrarReporte(const string& funcionalidad, long long memoriaTotal);
};

#endif
