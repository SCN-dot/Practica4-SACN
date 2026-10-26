#include <iostream>
#include "red.h"

using namespace std;

void probarEnrutador() {
    cout << "   Prueba de Enrutador   " << endl;

    Enrutador a("A");
    a.agregarVecino("B", 4);
    a.agregarVecino("D", 5);
    a.agregarVecino("C", 10);
    a.mostrarVecinos();

    a.reiniciarTabla(); // tabla inicial: el mismo enrutador + vecinos directos
    a.mostrarTabla();

    cout << "Costo del enlace A-B: " << a.costoEnlace("B") << endl;
    cout << "Costo del enlace A-Z: " << a.costoEnlace("Z") << " (-1 = no es vecino)" << endl;

    a.actualizarCosto("C", 7); // asi la Red le dara luego el camino mas corto
    a.mostrarTabla();
    cout << "Costo a C: " << a.costoA("C") << endl;

    a.eliminarVecino("C");
    a.mostrarVecinos();
}

// Prueba de la clase Red
void probarRed() {
    cout << "\n   Prueba de Red   " << endl;

    Red red;
    red.agregarEnrutador("A");
    red.agregarEnrutador("B");
    red.agregarEnrutador("C");
    red.agregarEnrutador("D");

    red.agregarEnlace("A", "B", 4);
    red.agregarEnlace("A", "D", 5);
    red.agregarEnlace("A", "C", 10);
    red.agregarEnlace("B", "C", 3);
    red.agregarEnlace("B", "D", 1);
    red.agregarEnlace("D", "C", 2);

    red.mostrarRed();
    red.mostrarTablas();

    cout << "\n   Eliminando enlace A-C" << endl;
    red.eliminarEnlace("A", "C");
    red.mostrarRed();
    red.mostrarTablas();

    cout << "\n   Eliminando enrutador D" << endl;
    red.eliminarEnrutador("D");
    red.mostrarRed();
    red.mostrarTablas();

    cout << "\n   Casos invalidos" << endl;
    cout << "Agregar B repetido: " << (red.agregarEnrutador("B") ? "ok" : "rechazado") << endl;
    cout << "Enlace A-Z (Z no existe): " << (red.agregarEnlace("A", "Z", 3) ? "ok" : "rechazado") << endl;
    cout << "Enlace A-A: " << (red.agregarEnlace("A", "A", 3) ? "ok" : "rechazado") << endl;
    cout << "Enlace A-B con costo 0: " << (red.agregarEnlace("A", "B", 0) ? "ok" : "rechazado") << endl;
}

int main() {
    probarEnrutador();
    probarRed();
    return 0;
}
