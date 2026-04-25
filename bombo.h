#ifndef BOMBO_H
#define BOMBO_H

#include "equipo.h"
#include "lista.h"

class Bombo
{
private:
    int numero;
    Lista<Equipo> equipos;

public:
    // Constructores
    Bombo();
    Bombo(int numero);
    Bombo(const Bombo& otro);

    // Operador de asignación
    Bombo& operator=(const Bombo& otro);

    // Destructor
    ~Bombo();

    // Getters
    int getNumero() const;
    Lista<Equipo>& getEquipos();
    const Lista<Equipo>& getEquipos() const;

    // Setters
    void setNumero(int numero);
    void setEquipos(const Lista<Equipo>& equipos);

    // Métodos propios
    void agregarEquipo(const Equipo& equipo);
    int tamano() const;
    bool estaVacio() const;

    // Medición de memoria
    int memoryUsage() const;
};

#endif // BOMBO_H
