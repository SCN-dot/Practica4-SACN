#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "enrutador.h"

class Red {
private:
    std::map<std::string, Enrutador> enrutadores; // nombre -> enrutador

    void actualizarTablas(); //por ahora solo reinicias las tablas

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
