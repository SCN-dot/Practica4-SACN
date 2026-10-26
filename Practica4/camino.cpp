#include "camino.h"
#include <iostream>

using namespace std;

Camino::Camino() : costo(-1) {}

void Camino::agregarAlInicio(const string& nodo) { nodos.push_front(nodo); }
void Camino::setCosto(int c) { costo = c; }

int Camino::getCosto() const { return costo; }
bool Camino::estaVacio() const { return nodos.empty(); }
const list<string>& Camino::getNodos() const { return nodos; }

void Camino::mostrar() const {
    if (nodos.empty()) {
        cout << "(sin camino)" << endl;
        return;
    }
    bool primero = true;
    for (const string& n : nodos) {
        if (!primero) cout << " -> ";
        cout << n;
        primero = false;
    }
    cout << endl << "Costo total: " << costo << endl;
}
