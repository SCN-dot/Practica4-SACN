#include "enrutador.h"
#include <iostream>

using namespace std;

Enrutador::Enrutador(const string& nombre) : nombre(nombre) { //atr(par)
    reiniciarTabla();
}
//devuelven atributo
const string& Enrutador::getNombre() const { return nombre; }
const map<string, int>& Enrutador::getVecinos() const { return vecinos; }
const map<string, int>& Enrutador::getTabla() const { return tabla; }

void Enrutador::agregarVecino(const string& vecino, int costo) {
    vecinos[vecino] = costo; // si ya existia, solo cambia el costo
}

bool Enrutador::eliminarVecino(const string& vecino) {
    return vecinos.erase(vecino) > 0;
}

int Enrutador::costoEnlace(const string& vecino) const {
    auto it = vecinos.find(vecino);
    if (it == vecinos.end()) return -1;
    return it->second; //desre acce
}

// Estado inicial segun la guia: solo se conocen los destinos directamente conectados
void Enrutador::reiniciarTabla() {
    tabla.clear();
    tabla[nombre] = 0;
    for (const auto& v : vecinos) {
        tabla[v.first] = v.second;
    }
}

void Enrutador::actualizarCosto(const string& destino, int costo) {
    tabla[destino] = costo;
}

int Enrutador::costoA(const string& destino) const {
    auto it = tabla.find(destino);
    if (it == tabla.end()) return -1;
    return it->second;
}

void Enrutador::mostrarVecinos() const {
    cout << "Vecinos de " << nombre << ": ";
    if (vecinos.empty()) cout << "(ninguno)";
    for (const auto& v : vecinos) { //name cost
        cout << v.first << "(" << v.second << ") ";
    }
    cout << endl;
}

void Enrutador::mostrarTabla() const {
    cout << "Tabla de " << nombre << ": ";
    for (const auto& t : tabla) {
        cout << t.first << "=" << t.second << " ";
    }
    cout << endl;
}
