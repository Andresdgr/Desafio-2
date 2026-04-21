#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"
#include <stdexcept>

template <typename T>
class Lista
{
private:
    Nodo<T>* head;
    int size;

public:
    // Constructor por defecto
    Lista();

    // Constructor de copia
    Lista(const Lista<T>& otra);

    // Destructor
    ~Lista();

    // Métodos básicos
    int tamano() const;
    bool esVacia() const;
    T& primero();
    const T& primero() const;
    T& ultimo();
    const T& ultimo() const;

    //agregar
    void agregar(const T& e, int i);

    //consultar
    T& consultar(int i);
    const T& consultar(int i) const;

private:
    void destruirLista();
};

// Implementación

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
    Nodo<T>* ultimoNodo = nullptr;

    while (actual != nullptr)
    {
        Nodo<T>* nuevo = new Nodo<T>(actual->getData());

        if (head == nullptr)
        {
            head = nuevo;
        }
        else
        {
            ultimoNodo->setPtrNext(nuevo);
        }

        ultimoNodo = nuevo;
        actual = actual->getPtrNext();
        size++;
    }
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
    {
        throw std::out_of_range("La lista esta vacia");
    }

    return head->getData();
}

template <typename T>
const T& Lista<T>::primero() const
{
    if (esVacia())
    {
        throw std::out_of_range("La lista esta vacia");
    }

    return head->getData();
}

template <typename T>
T& Lista<T>::ultimo()
{
    if (esVacia())
    {
        throw std::out_of_range("La lista esta vacia");
    }

    Nodo<T>* actual = head;

    while (actual->getPtrNext() != nullptr)
    {
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
const T& Lista<T>::ultimo() const
{
    if (esVacia())
    {
        throw std::out_of_range("La lista esta vacia");
    }

    Nodo<T>* actual = head;

    while (actual->getPtrNext() != nullptr)
    {
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
void Lista<T>::destruirLista()
{
    Nodo<T>* actual = head;

    while (actual != nullptr)
    {
        Nodo<T>* temporal = actual;
        actual = actual->getPtrNext();
        delete temporal;
    }

    head = nullptr;
    size = 0;
}
// agregar
template <typename T>
void Lista<T>::agregar(const T& e, int i)
{
    if (i < 0 || i > size)
    {
        throw std::out_of_range("Posicion invalida para insertar");
    }

    Nodo<T>* nuevo = new Nodo<T>(e);

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
            actual = actual->getPtrNext();
        }

        nuevo->setPtrNext(actual->getPtrNext());
        actual->setPtrNext(nuevo);
    }

    size++;
}

// consultar

template <typename T>
T& Lista<T>::consultar(int i)
{
    if (i < 0 || i >= size)
    {
        throw std::out_of_range("Posicion invalida para consultar");
    }

    Nodo<T>* actual = head;

    for (int pos = 0; pos < i; pos++)
    {
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

template <typename T>
const T& Lista<T>::consultar(int i) const
{
    if (i < 0 || i >= size)
    {
        throw std::out_of_range("Posicion invalida para consultar");
    }

    Nodo<T>* actual = head;

    for (int pos = 0; pos < i; pos++)
    {
        actual = actual->getPtrNext();
    }

    return actual->getData();
}

#endif // LISTA_H
