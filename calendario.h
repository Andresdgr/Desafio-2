#ifndef CALENDARIO_H
#define CALENDARIO_H

#include "grupo.h"
#include "partido.h"
#include "lista.h"
#include <string>

using namespace std;

class Calendario
{
private:
    string fechaInicial;

    string calcularFecha(int dia) const;
    bool equipoJugoRecientemente(const string& pais,
                                 Lista<string>& equipos,
                                 Lista<int>& dias,
                                 int diaActual) const;

public:
    Calendario();
    Calendario(const string& fechaInicial);
    Calendario(const Calendario& otro);
    Calendario& operator=(const Calendario& otro);
    ~Calendario();

    string getFechaInicial() const;
    void setFechaInicial(const string& fechaInicial);

    Lista<Partido> generarCalendarioFaseGrupos(Lista<Grupo>& grupos);
};

#endif // CALENDARIO_H
