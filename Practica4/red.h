#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "enrutador.h"
#include "camino.h"

class Red {
private:
    std::map<std::string, Enrutador> enrutadores; // nombre - enrutador

    void buscarCostoBarato(const std::string& origen, std::map<std::string, int>& costos, std::map<std::string, std::string>& previo) const;

    void actualizarTablas();

public:
    bool agregarEnrutador(const std::string& nombre);  // false si ya existe o el nombre es vacio
    bool eliminarEnrutador(const std::string& nombre); // tambien borra sus enlaces
    bool existeEnrutador(const std::string& nombre) const;

    // Enlaces
    bool agregarEnlace(const std::string& a, const std::string& b, int costo);
    bool eliminarEnlace(const std::string& a, const std::string& b);

    // Caminos
    Camino caminoMasCorto(const std::string& origen, const std::string& destino) const;

    // Archivos
    bool cargarDesdeArchivo(const std::string& ruta);
    bool guardarEnArchivo(const std::string& ruta) const;

    // Impresion
    void mostrarRed() const;
    void mostrarTablas() const;
};

#endif // RED_H
