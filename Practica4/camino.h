#ifndef CAMINO_H
#define CAMINO_H

#include <string>
#include <list>

class Camino {
private:
    std::list<std::string> nodos; // origen ... destino, en orden
    int costo;                    // -1 si no hay camino

public:
    Camino();

    void agregarAlInicio(const std::string& nodo);
    void setCosto(int c);

    int getCosto() const;
    bool estaVacio() const;
    const std::list<std::string>& getNodos() const;

    void mostrar() const;
};

#endif // CAMINO_H
