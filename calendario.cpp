#include "calendario.h"
#include "medidorrecursos.h"

#include <sstream>
#include <iomanip>

using namespace std;

Calendario::Calendario()
{
    fechaInicial = "20/06/2026";
}

Calendario::Calendario(const string& fechaInicial)
{
    this->fechaInicial = fechaInicial;
}

Calendario::Calendario(const Calendario& otro)
{
    fechaInicial = otro.fechaInicial;
}

Calendario& Calendario::operator=(const Calendario& otro)
{
    if (this != &otro)
        fechaInicial = otro.fechaInicial;

    return *this;
}

Calendario::~Calendario()
{
}

string Calendario::getFechaInicial() const
{
    return fechaInicial;
}

void Calendario::setFechaInicial(const string& fechaInicial)
{
    this->fechaInicial = fechaInicial;
}

string Calendario::calcularFecha(int dia) const
{
    int diaBase = 20;
    int mesBase = 6;
    int anioBase = 2026;

    int diaCalculado = diaBase + dia;

    if (diaCalculado > 30)
    {
        diaCalculado -= 30;
        mesBase = 7;
    }

    stringstream ss;

    if (diaCalculado < 10)
        ss << "0";

    ss << diaCalculado << "/";

    if (mesBase < 10)
        ss << "0";

    ss << mesBase << "/" << anioBase;

    return ss.str();
}

bool Calendario::equipoJugoRecientemente(const string&,
                                         Lista<string>&,
                                         Lista<int>&,
                                         int) const
{
    return false;
}

Lista<Partido> Calendario::generarCalendarioFaseGrupos(Lista<Grupo>& grupos)
{
    Lista<Partido> partidos;

    int partidoGlobal = 0;

    for (int ronda = 0; ronda < 3; ronda++)
    {
        MedidorRecursos::sumarIteracion();

        for (int i = 0; i < grupos.tamano(); i++)
        {
            MedidorRecursos::sumarIteracion();

            Grupo& grupo = grupos.consultar(i);

            int a1, a2, b1, b2;

            if (ronda == 0)
            {
                a1 = 0; a2 = 1;
                b1 = 2; b2 = 3;
            }
            else if (ronda == 1)
            {
                a1 = 0; a2 = 2;
                b1 = 1; b2 = 3;
            }
            else
            {
                a1 = 0; a2 = 3;
                b1 = 1; b2 = 2;
            }

            int dia1 = partidoGlobal / 4;
            Partido p1(&grupo.getEquipos().consultar(a1),
                       &grupo.getEquipos().consultar(a2));
            p1.configurarLogistica(calcularFecha(dia1));
            partidos.agregar(p1, partidos.tamano());
            partidoGlobal++;

            int dia2 = partidoGlobal / 4;
            Partido p2(&grupo.getEquipos().consultar(b1),
                       &grupo.getEquipos().consultar(b2));
            p2.configurarLogistica(calcularFecha(dia2));
            partidos.agregar(p2, partidos.tamano());
            partidoGlobal++;
        }
    }

    return partidos;
}
