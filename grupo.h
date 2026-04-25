#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"
#include "lista.h"

class Grupo
{
private:
    char nombre;
    Lista<Equipo> equipos;

public:
    // Constructores
    Grupo();
    Grupo(char nombre);
    Grupo(const Grupo& otro);

    // Operador de asignación
    Grupo& operator=(const Grupo& otro);

    // Destructor
    ~Grupo();

    // Getters
    char getNombre() const;
    Lista<Equipo>& getEquipos();
    const Lista<Equipo>& getEquipos() const;

    // Setters
    void setNombre(char nombre);
    void setEquipos(const Lista<Equipo>& equipos);

    // Métodos propios
    void agregarEquipo(const Equipo& equipo);
    int tamano() const;
    bool estaVacio() const;

    // Medición de memoria
    int memoryUsage() const;
};

#endif // GRUPO_H
