#include <iostream>
#include <string>
#include "red.h"

using namespace std;

string leerRuta() {
    string ruta;
    cout << "Ruta completa del archivo: ";
    getline(cin >> ws, ruta);
    return ruta;
}

void mostrarMenu() {
    cout << endl << " SIMULADOR DE RED DE ENRUTADORES " << endl;
    cout << "1. Cargar otra topologia desde archivo" << endl;
    cout << "2. Mostrar red" << endl;
    cout << "3. Mostrar tablas de costos" << endl;
    cout << "4. Agregar enrutador" << endl;
    cout << "5. Eliminar enrutador" << endl;
    cout << "6. Agregar o modificar enlace" << endl;
    cout << "7. Eliminar enlace" << endl;
    cout << "8. Consultar camino mas corto" << endl;
    cout << "9. Guardar topologia en archivo" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

int main() {
    Red red;

    // Al iniciar se obliga a cargar una topologia
    bool cargada = false;
    while (!cargada) {
        string ruta = leerRuta();
        if (ruta == "salir") return 0;
        cargada = red.cargarDesdeArchivo(ruta);
        if (!cargada) cout << "No se pudo cargar. Revise la ruta y el formato" << endl;
    }
    cout << "Topologia cargada." << endl;

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        if (!(cin >> opcion)) { // entrada no numerica
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
            continue;
        }

        string a, b, ruta;
        int costo;

        switch (opcion) {
        case 1:
            ruta = leerRuta();
            if (ruta == "salir") break;
            if (red.cargarDesdeArchivo(ruta)) cout << "Topologia cargada." << endl;
            else cout << "No se pudo cargar. Se conserva la red actual" << endl;
            break;
        case 2:
            red.mostrarRed();
            break;
        case 3:
            red.mostrarTablas();
            break;
        case 4:
            cout << "Nombre del nuevo enrutador: ";
            cin >> a;
            if (red.agregarEnrutador(a)) cout << "Enrutador agregado" << endl;
            else cout << "No se pudo agregar (ya existe)" << endl;
            break;
        case 5:
            cout << "Enrutador a eliminar: ";
            cin >> a;
            if (red.eliminarEnrutador(a)) cout << "Enrutador eliminado" << endl;
            else cout << "El enrutador no existe" << endl;
            break;
        case 6:
            cout << "Enrutador 1, enrutador 2 y costo: ";
            cin >> a >> b >> costo;
            if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Costo invalido" << endl; break; }
            if (red.agregarEnlace(a, b, costo)) cout << "Enlace guardado" << endl;
            else cout << "No se pudo (enrutadores inexistentes, iguales o costo <= 0)" << endl;
            break;
        case 7:
            cout << "Enrutador 1 y enrutador 2: ";
            cin >> a >> b;
            if (red.eliminarEnlace(a, b)) cout << "Enlace eliminado" << endl;
            else cout << "El enlace no existe" << endl;
            break;
        case 8: {
            cout << "Origen y destino: ";
            cin >> a >> b;
            if (!red.existeEnrutador(a) || !red.existeEnrutador(b)) {
                cout << "Alguno de los enrutadores no existe" << endl;
                break;
            }
            Camino c = red.caminoMasCorto(a, b);
            if (c.estaVacio()) cout << "No hay camino entre " << a << " y " << b << endl;
            else c.mostrar();
            break;
        }
        case 9:
            ruta = leerRuta();
            if (ruta == "salir") break;
            if (red.guardarEnArchivo(ruta)) cout << "Topologia guardada" << endl;
            else cout << "No se pudo escribir el archivo" << endl;
            break;
        case 0:
            cout << "Hasta luego" << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
        }
    }
    return 0;
}
