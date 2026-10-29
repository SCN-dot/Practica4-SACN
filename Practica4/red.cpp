#include "red.h"
#include <iostream>
#include <fstream>

using namespace std;

void Red::buscarCostoBarato(const string& origen, map<string, int>& costos, map<string, string>& previo) const {
    for (const auto& par : enrutadores) {
        costos[par.first] = -1;      // -1 = aun no se sabe llegar
    }
    costos[origen] = 0;

    bool huboCambios = true;
    while (huboCambios) {
        huboCambios = false;
        for (const auto& par : enrutadores) {
            const string& actual = par.first;
            if (costos[actual] == -1) continue; // todavia no se llega a este

            for (const auto& v : par.second.getVecinos()) {
                int nuevo = costos[actual] + v.second;
                if (costos[v.first] == -1 || nuevo < costos[v.first]) {
                    costos[v.first] = nuevo;
                    previo[v.first] = actual;
                    huboCambios = true;
                }
            }
        }
    }
}

void Red::actualizarTablas() {
    for (auto& par : enrutadores) {
        map<string, int> costos;
        map<string, string> previo;
        buscarCostoBarato(par.first, costos, previo);

        par.second.reiniciarTabla();
        for (const auto& c : costos) {
            par.second.actualizarCosto(c.first, c.second);
        }
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

Camino Red::caminoMasCorto(const string& origen, const string& destino) const {
    Camino camino; // vacio y con costo -1 significa "sin camino"
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) return camino;

    map<string, int> costos;
    map<string, string> previo;
    buscarCostoBarato(origen, costos, previo);

    if (costos[destino] == -1) return camino;

    camino.setCosto(costos[destino]);
    // Se reconstruye desde el destino hacia atras
    string actual = destino;
    camino.agregarAlInicio(actual);
    while (actual != origen) {
        actual = previo[actual];
        camino.agregarAlInicio(actual);
    }
    return camino;
}

// Formato: N, N nombres, M, M lineas "A B costo"
bool Red::cargarDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return false;

    // Se arma en una red temporal; solo si todo sale bien reemplaza la actual
    Red nueva;

    int n;
    if (!(archivo >> n) || n < 0) return false;
    for (int i = 0; i < n; i++) {
        string nombre;
        if (!(archivo >> nombre) || !nueva.agregarEnrutador(nombre)) return false;
    }

    int m;
    if (!(archivo >> m) || m < 0) return false;
    for (int i = 0; i < m; i++) {
        string a, b;
        int costo;
        if (!(archivo >> a >> b >> costo) || !nueva.agregarEnlace(a, b, costo)) return false;
    }

    enrutadores = nueva.enrutadores;
    return true;
}

bool Red::guardarEnArchivo(const string& ruta) const {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return false;

    archivo << enrutadores.size() << endl;
    for (const auto& par : enrutadores) {
        archivo << par.first << endl;
    }

    // Cada enlace es bidireccional: se escribe una sola vez (nombre menor primero)
    int m = 0;
    for (const auto& par : enrutadores) {
        for (const auto& v : par.second.getVecinos()) {
            if (par.first < v.first) m++;
        }
    }
    archivo << m << endl;
    for (const auto& par : enrutadores) {
        for (const auto& v : par.second.getVecinos()) {
            if (par.first < v.first) {
                archivo << par.first << " " << v.first << " " << v.second << endl;
            }
        }
    }
    return true;
}

void Red::mostrarRed() const {
    cout << " Red (" << enrutadores.size() << " enrutadores) " << endl;
    for (const auto& par : enrutadores) {
        par.second.mostrarVecinos();
    }
}

void Red::mostrarTablas() const {
    cout << " Tablas de costos (-1 = sin ruta) " << endl;
    for (const auto& par : enrutadores) {
        par.second.mostrarTabla();
    }
}
