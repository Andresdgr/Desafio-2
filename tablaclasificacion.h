#ifndef TABLACLASIFICACION_H
#define TABLACLASIFICACION_H

#include "filaclasificacion.h"
#include "grupo.h"
#include "lista.h"

class TablaClasificacion
{
private:
    Lista<FilaClasificacion> filas;

public:
    TablaClasificacion();
    TablaClasificacion(const Grupo& grupo);
    TablaClasificacion(const TablaClasificacion& otra);
    TablaClasificacion& operator=(const TablaClasificacion& otra);
    ~TablaClasificacion();

    void generarDesdeGrupo(const Grupo& grupo);
    void ordenar();
    void imprimir() const;

    FilaClasificacion getFila(int posicion) const;
    int tamano() const;

    Lista<FilaClasificacion>& getFilas();
    const Lista<FilaClasificacion>& getFilas() const;
};

#endif // TABLACLASIFICACION_H
