#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"
#include "medidorrecursos.h"
#include <stdexcept>

template <typename T>
class Lista
{
private:
    Nodo<T>* head;
    int size;
    static int totalMemory;

public:
    Lista();
    Lista(const Lista<T>& otra);
    Lista<T>& operator=(const Lista<T>& otra);
    ~Lista();

    int tamano() const;
    bool esVacia() const;

    T& primero();
    const T& primero() const;

    T& ultimo();
    const T& ultimo() const;

    T& consultar(int i);
    const T& consultar(int i) const;

    void agregar(const T& e, int i);
    void ordenar();

    int memoryUsage() const;

private:
    void destruirLista();
};

template <typename T>
int Lista<T>::totalMemory = sizeof(Lista<T>);

template <typename T>
Lista<T>::Lista()
{
    head = nullptr;
    size = 0;
}

template <typename T>
Lista<T>::Lista(const Lista<T>& otra)
{
    head = nullptr;
    size = 0;

    Nodo<T>* actual = otra.head;

    while (actual != nullptr)
    {
        MedidorRecursos::sumarIteracion();

        agregar(actual->getData(), size);
        actual = actual->getPtrNext();
    }
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra)
{
    if (this != &otra)
    {
        destruirLista();

        Nodo<T>* actual = otra.head;

        while (actual != nullptr)
        {
            MedidorRecursos::sumarIteracion();

            agregar(actual->getData(), size);
            actual = actual->getPtrNext();
        }
    }

    return *this;
}

template <typename T>
Lista<T>::~Lista()
{
    destruirLista();
}

template <typename T>
int Lista<T>::tamano() const
{
    return size;
}

template <typename T>
bool Lista<T>::esVacia() const
{
    return head == nullptr;
}

template <typename T>
T& Lista<T>::primero()
{
    if (esVacia())
        throw std::out_of_range("Lista vacia");

    return head->getData();
}

template <typename T>
const T& Lista<T>::primero() const
{
    if (esVacia())
        throw std::out_of_range("Lista vacia");

    return head->getData();
}

template <typename T>
T& Lista<T>::ultimo()
{
    if (esVacia())
        throw std::out_of_range("Lista vacia");

    Nodo<T>* actual = head;

    while (actual->getPtrNext() != nullptr)
    {
        MedidorRecursos::sumarIteracion();
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
const T& Lista<T>::ultimo() const
{
    if (esVacia())
        throw std::out_of_range("Lista vacia");

    Nodo<T>* actual = head;

    while (actual->getPtrNext() != nullptr)
    {
        MedidorRecursos::sumarIteracion();
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
T& Lista<T>::consultar(int i)
{
    if (i < 0 || i >= size)
        throw std::out_of_range("Posicion invalida");

    Nodo<T>* actual = head;

    for (int pos = 0; pos < i; pos++)
    {
        MedidorRecursos::sumarIteracion();
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
const T& Lista<T>::consultar(int i) const
{
    if (i < 0 || i >= size)
        throw std::out_of_range("Posicion invalida");

    Nodo<T>* actual = head;

    for (int pos = 0; pos < i; pos++)
    {
        MedidorRecursos::sumarIteracion();
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
void Lista<T>::agregar(const T& e, int i)
{
    if (i < 0 || i > size)
        throw std::out_of_range("Posicion invalida");

    Nodo<T>* nuevo = new Nodo<T>(e);
    totalMemory += sizeof(Nodo<T>);

    if (i == 0)
    {
        nuevo->setPtrNext(head);
        head = nuevo;
    }
    else
    {
        Nodo<T>* actual = head;

        for (int pos = 0; pos < i - 1; pos++)
        {
            MedidorRecursos::sumarIteracion();
            actual = actual->getPtrNext();
        }

        nuevo->setPtrNext(actual->getPtrNext());
        actual->setPtrNext(nuevo);
    }

    size++;
}

template <typename T>
void Lista<T>::ordenar()
{
    if (size <= 1)
        return;

    bool cambio;

    do
    {
        cambio = false;
        Nodo<T>* actual = head;

        while (actual != nullptr && actual->getPtrNext() != nullptr)
        {
            MedidorRecursos::sumarIteracion();

            Nodo<T>* siguiente = actual->getPtrNext();

            if (siguiente->getData() < actual->getData())
            {
                T temp = actual->getData();
                actual->setData(siguiente->getData());
                siguiente->setData(temp);

                cambio = true;
            }

            actual = actual->getPtrNext();
        }

    } while (cambio);
}

template <typename T>
int Lista<T>::memoryUsage() const
{
    return totalMemory;
}

template <typename T>
void Lista<T>::destruirLista()
{
    Nodo<T>* actual = head;

    while (actual != nullptr)
    {
        MedidorRecursos::sumarIteracion();

        Nodo<T>* temp = actual;
        actual = actual->getPtrNext();

        delete temp;
        totalMemory -= sizeof(Nodo<T>);
    }

    head = nullptr;
    size = 0;
}

#endif
