#include "red.h"
#include <iostream>

using namespace std;

void Red::actualizarTablas() {
    for (auto& par : enrutadores) {
        par.second.reiniciarTabla();
    }
}

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || existeEnrutador(nombre)) return false;
    enrutadores.insert(make_pair(nombre, Enrutador(nombre)));
    actualizarTablas();
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    auto it = enrutadores.find(nombre);
    if (it == enrutadores.end()) return false;

    // Primero se quita de la lista de vecinos de todos los demas
    for (auto& par : enrutadores) {
        par.second.eliminarVecino(nombre);
    }
    enrutadores.erase(it);
    actualizarTablas();
    return true;
}

bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

bool Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (a == b || costo <= 0) return false;
    auto ia = enrutadores.find(a);
    auto ib = enrutadores.find(b);
    if (ia == enrutadores.end() || ib == enrutadores.end()) return false;

    ia->second.agregarVecino(b, costo);
    ib->second.agregarVecino(a, costo);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    auto ia = enrutadores.find(a);
    auto ib = enrutadores.find(b);
    if (ia == enrutadores.end() || ib == enrutadores.end()) return false;

    bool existia = ia->second.eliminarVecino(b);
    ib->second.eliminarVecino(a);
    if (existia) actualizarTablas();
    return existia;
}

void Red::mostrarRed() const {
    cout << " Red (" << enrutadores.size() << " enrutadores) " << endl;
    for (const auto& par : enrutadores) {
        par.second.mostrarVecinos();
    }
}

void Red::mostrarTablas() const {
    cout << " Tablas de costos " << endl;
    for (const auto& par : enrutadores) {
        par.second.mostrarTabla();
    }
}
