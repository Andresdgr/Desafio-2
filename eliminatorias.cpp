#include "eliminatorias.h"
#include "medidorrecursos.h"

#include <iostream>
#include <stdexcept>

using namespace std;

static const string FECHA_ELIMINATORIAS = "10/07/2026";

Eliminatorias::Eliminatorias()
{
    contadorPartidosEliminatorias = 0;
}



Eliminatorias::Eliminatorias(const Eliminatorias& otra)
{
    equiposRonda = otra.equiposRonda;
}

Eliminatorias& Eliminatorias::operator=(const Eliminatorias& otra)
{
    if (this != &otra)
    {
        equiposRonda = otra.equiposRonda;
    }

    return *this;
}

Eliminatorias::~Eliminatorias()
{
}

int Eliminatorias::buscarCompatible(Lista<FilaClasificacion>& lista,
                                    char grupoProhibido,
                                    int inicio,
                                    int fin) const
{
    for (int i = inicio; i <= fin; i++)
    {
        MedidorRecursos::sumarIteracion();

        if (lista.consultar(i).getGrupoOrigen() != grupoProhibido)
        {
            return i;
        }
    }

    return -1;
}

void Eliminatorias::agregarCruce(const FilaClasificacion& filaA,
                                 const FilaClasificacion& filaB,
                                 Lista<Partido>& partidos)
{
    agregarCruceEquipos(filaA.getEquipo(), filaB.getEquipo(), partidos);
}

void Eliminatorias::agregarCruceEquipos(const Equipo& equipoA,
                                        const Equipo& equipoB,
                                        Lista<Partido>& partidos)
{
    equiposRonda.agregar(equipoA, equiposRonda.tamano());
    equiposRonda.agregar(equipoB, equiposRonda.tamano());

    Equipo& e1 = equiposRonda.consultar(equiposRonda.tamano() - 2);
    Equipo& e2 = equiposRonda.consultar(equiposRonda.tamano() - 1);


    Partido partido(&e1, &e2);
    partido.configurarLogistica(FECHA_ELIMINATORIAS);

    partidos.agregar(partido, partidos.tamano());
}

Lista<Partido> Eliminatorias::generarDieciseisavos(Lista<FilaClasificacion>& primeros,
                                                   Lista<FilaClasificacion>& segundos,
                                                   Lista<FilaClasificacion>& terceros)
{
    Lista<Partido> partidos;
    equiposRonda = Lista<Equipo>();

    terceros.ordenar();
    segundos.ordenar();

    for (int i = 0; i < 8; i++)
    {
        MedidorRecursos::sumarIteracion();

        FilaClasificacion cabeza = primeros.consultar(i);

        int indiceTercero = buscarCompatible(
            terceros,
            cabeza.getGrupoOrigen(),
            i,
            terceros.tamano() - 1
            );

        if (indiceTercero == -1)
        {
            throw runtime_error("No se encontro tercero compatible para evitar cruce del mismo grupo");
        }

        FilaClasificacion tercero = terceros.consultar(indiceTercero);

        FilaClasificacion temporal = terceros.consultar(i);
        terceros.consultar(i) = tercero;
        terceros.consultar(indiceTercero) = temporal;

        agregarCruce(cabeza, tercero, partidos);
    }

    for (int i = 8; i < 12; i++)
    {
        MedidorRecursos::sumarIteracion();

        FilaClasificacion cabeza = primeros.consultar(i);

        int posicionUsada = 8 + (i - 8);

        int indiceSegundo = buscarCompatible(
            segundos,
            cabeza.getGrupoOrigen(),
            posicionUsada,
            11
            );

        if (indiceSegundo == -1)
        {
            throw runtime_error("No se encontro segundo compatible para evitar cruce del mismo grupo");
        }

        FilaClasificacion segundo = segundos.consultar(indiceSegundo);

        FilaClasificacion temporal = segundos.consultar(posicionUsada);
        segundos.consultar(posicionUsada) = segundo;
        segundos.consultar(indiceSegundo) = temporal;

        agregarCruce(cabeza, segundo, partidos);
    }

    for (int i = 0; i < 8; i += 2)
    {
        MedidorRecursos::sumarIteracion();

        FilaClasificacion segundoA = segundos.consultar(i);
        FilaClasificacion segundoB = segundos.consultar(i + 1);

        if (segundoA.getGrupoOrigen() == segundoB.getGrupoOrigen())
        {
            int indiceCompatible = buscarCompatible(
                segundos,
                segundoA.getGrupoOrigen(),
                i + 2,
                7
                );

            if (indiceCompatible != -1)
            {
                FilaClasificacion temp = segundos.consultar(i + 1);
                segundos.consultar(i + 1) = segundos.consultar(indiceCompatible);
                segundos.consultar(indiceCompatible) = temp;

                segundoB = segundos.consultar(i + 1);
            }
        }

        if (segundoA.getGrupoOrigen() == segundoB.getGrupoOrigen())
        {
            throw runtime_error("No se pudo evitar cruce entre segundos del mismo grupo");
        }

        agregarCruce(segundoA, segundoB, partidos);
    }

    return partidos;
}

void Eliminatorias::simularRonda(Lista<Partido>& partidos)
{
    for (int i = 0; i < partidos.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();
        partidos.consultar(i).simularEliminacion();
    }
}

Lista<Equipo> Eliminatorias::obtenerGanadores(Lista<Partido>& partidos)
{
    Lista<Equipo> ganadores;

    for (int i = 0; i < partidos.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        Partido& partido = partidos.consultar(i);

        Equipo* e1 = partido.getEquipo1();
        Equipo* e2 = partido.getEquipo2();

        if (e1 == nullptr || e2 == nullptr)
        {
            continue;
        }

        if (partido.getGolesEquipo1() > partido.getGolesEquipo2())
        {
            ganadores.agregar(*e1, ganadores.tamano());
        }
        else
        {
            ganadores.agregar(*e2, ganadores.tamano());
        }
    }

    return ganadores;
}

Lista<Equipo> Eliminatorias::obtenerPerdedores(Lista<Partido>& partidos)
{
    Lista<Equipo> perdedores;

    for (int i = 0; i < partidos.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();

        Partido& partido = partidos.consultar(i);

        Equipo* e1 = partido.getEquipo1();
        Equipo* e2 = partido.getEquipo2();

        if (e1 == nullptr || e2 == nullptr)
        {
            continue;
        }

        if (partido.getGolesEquipo1() > partido.getGolesEquipo2())
        {
            perdedores.agregar(*e2, perdedores.tamano());
        }
        else
        {
            perdedores.agregar(*e1, perdedores.tamano());
        }
    }

    return perdedores;
}

Lista<Partido> Eliminatorias::generarSiguienteRonda(Lista<Equipo>& ganadores,
                                                    const string& /*nombreRonda*/)
{
    Lista<Partido> partidos;
    equiposRonda = Lista<Equipo>();

    for (int i = 0; i < ganadores.tamano(); i++)
    {
        MedidorRecursos::sumarIteracion();
        equiposRonda.agregar(ganadores.consultar(i), equiposRonda.tamano());
    }

    for (int i = 0; i < equiposRonda.tamano(); i += 2)
    {
        MedidorRecursos::sumarIteracion();

        Equipo& e1 = equiposRonda.consultar(i);
        Equipo& e2 = equiposRonda.consultar(i + 1);

        Partido partido(&e1, &e2);
        partido.configurarLogistica(FECHA_ELIMINATORIAS);

        partidos.agregar(partido, partidos.tamano());
    }

    return partidos;
}

Lista<Partido> Eliminatorias::generarTercerPuesto(Lista<Equipo>& perdedoresSemifinal)
{
    Lista<Partido> partidos;
    equiposRonda = Lista<Equipo>();

    if (perdedoresSemifinal.tamano() >= 2)
    {
        agregarCruceEquipos(
            perdedoresSemifinal.consultar(0),
            perdedoresSemifinal.consultar(1),
            partidos
            );
    }

    return partidos;
}

void Eliminatorias::imprimirRonda(Lista<Partido>& partidos, const string& nombreRonda) const
{
    cout << "\n===== " << nombreRonda << " =====\n";

    for (int i = 0; i < partidos.tamano(); i++)
    {
        cout << "\nPartido " << i + 1 << endl;
        partidos.consultar(i).imprimirResultado();
    }
}

void Eliminatorias::imprimirRondaConfigurada(Lista<Partido>& partidos,
                                             const string& nombreRonda) const
{
    cout << "\n===== " << nombreRonda << " CONFIGURADOS =====\n";

    for (int i = 0; i < partidos.tamano(); i++)
    {
        Partido& partido = partidos.consultar(i);

        Equipo* e1 = partido.getEquipo1();
        Equipo* e2 = partido.getEquipo2();

        cout << "\nPartido " << i + 1 << endl;

        if (e1 != nullptr && e2 != nullptr)
        {
            cout << partido.getFecha()
            << " " << partido.getHora()
            << " | " << partido.getSede()
            << " | "
            << partido.getArbitro1() << ", "
            << partido.getArbitro2() << ", "
            << partido.getArbitro3()
            << " | "
            << e1->getPais()
            << " vs "
            << e2->getPais()
            << endl;
        }
    }
}
