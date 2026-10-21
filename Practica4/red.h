#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "enrutador.h"

// La Red guarda todos los enrutadores y gestiona los enlaces entre ellos.
// Modelo centralizado: la Red es quien tiene la vision completa de la topologia.
class Red {
private:
    std::map<std::string, Enrutador> enrutadores; // nombre -> enrutador

    // Se llama despues de cada cambio de topologia.
    // Por ahora deja las tablas con los vecinos directos; aqui se agregara
    // el calculo de caminos minimos en la segunda entrega.
    void actualizarTablas();

public:
    // Enrutadores
    bool agregarEnrutador(const std::string& nombre);  // false si ya existe o el nombre es vacio
    bool eliminarEnrutador(const std::string& nombre); // tambien borra sus enlaces
    bool existeEnrutador(const std::string& nombre) const;

    // Enlaces (bidireccionales)
    bool agregarEnlace(const std::string& a, const std::string& b, int costo);
    bool eliminarEnlace(const std::string& a, const std::string& b);

    // Impresion
    void mostrarRed() const;
    void mostrarTablas() const;
};

#endif // RED_H
