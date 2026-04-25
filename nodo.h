#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo
{
private:
    T data;
    Nodo<T>* ptrNext;

public:
    Nodo(const T& data);
    Nodo(const Nodo<T>& otro);
    ~Nodo();

    T& getData();
    const T& getData() const;

    Nodo<T>* getPtrNext() const;

    void setData(const T& data);
    void setPtrNext(Nodo<T>* ptrNext);
};

template <typename T>
Nodo<T>::Nodo(const T& data)
    : data(data), ptrNext(nullptr)
{
}

template <typename T>
Nodo<T>::Nodo(const Nodo<T>& otro)
    : data(otro.data), ptrNext(nullptr)
{
}

template <typename T>
Nodo<T>::~Nodo()
{
}

template <typename T>
T& Nodo<T>::getData()
{
    return data;
}

template <typename T>
const T& Nodo<T>::getData() const
{
    return data;
}

template <typename T>
Nodo<T>* Nodo<T>::getPtrNext() const
{
    return ptrNext;
}

template <typename T>
void Nodo<T>::setData(const T& data)
{
    this->data = data;
}

template <typename T>
void Nodo<T>::setPtrNext(Nodo<T>* ptrNext)
{
    this->ptrNext = ptrNext;
}

#endif
