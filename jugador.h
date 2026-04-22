#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

class Jugador
{
private:
    string nombre;
    string apellido;
    int numeroCamiseta;

    int partidosJugados;
    int goles;
    int minutosJugados;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    // Constructor
    Jugador();

    Jugador(string nombre, string apellido, int numero);

    // Getters
    string getNombre() const;
    string getApellido() const;
    int getNumeroCamiseta() const;
    int getGoles() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    // Setters básicos
    void setGoles(int goles);
    void agregarGol();
    void agregarMinutos(int minutos);
    void agregarAsistencia();
    void agregarAmarilla();
    void agregarRoja();
    void agregarFalta();
    void incrementarPartidos();
};

#endif
