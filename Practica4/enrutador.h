#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

// Un enrutador solo conoce informacion LOCAL:
//  - su nombre
//  - sus vecinos directos y el costo de cada enlace
//  - su tabla de costos hacia otros destinos (la actualiza la Red)
class Enrutador {
private:
    std::string nombre;
    std::map<std::string, int> vecinos; // vecino -> costo del enlace directo
    std::map<std::string, int> tabla;   // destino -> costo conocido

public:
    // Constructor de inicializacion
    explicit Enrutador(const std::string& nombre);

    // Getters
    const std::string& getNombre() const;
    const std::map<std::string, int>& getVecinos() const;
    const std::map<std::string, int>& getTabla() const;

    // Vecinos (enlaces directos)
    void agregarVecino(const std::string& vecino, int costo); // agrega o actualiza el costo
    bool eliminarVecino(const std::string& vecino);           // false si no existia
    int costoEnlace(const std::string& vecino) const;         // -1 si no es vecino

    // Tabla de costos
    void reiniciarTabla();                                       // 0 a si mismo + vecinos directos
    void actualizarCosto(const std::string& destino, int costo); // la Red lo usa para dar un costo
    int costoA(const std::string& destino) const;                // -1 si no hay ruta conocida

    // Impresion
    void mostrarVecinos() const;
    void mostrarTabla() const;
};

#endif // ENRUTADOR_H
