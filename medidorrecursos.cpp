#include "medidorrecursos.h"
#include <iostream>

using namespace std;

long long MedidorRecursos::iteraciones = 0;

void MedidorRecursos::reiniciar()
{
    iteraciones = 0;
}

void MedidorRecursos::sumarIteracion()
{
    iteraciones++;
}

void MedidorRecursos::sumarIteraciones(long long cantidad)
{
    iteraciones += cantidad;
}

long long MedidorRecursos::getIteraciones()
{
    return iteraciones;
}

void MedidorRecursos::mostrarReporte(const string& funcionalidad, long long memoriaTotal)
{
    cout << "\n===== MEDICION DE RECURSOS =====\n";
    cout << "Funcionalidad: " << funcionalidad << endl;
    cout << "Iteraciones: " << iteraciones << endl;
    cout << "Memoria total: " << memoriaTotal << " bytes" << endl;
}
