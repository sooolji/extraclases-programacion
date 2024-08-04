#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <iomanip> // Para std::setw

using namespace std;

class Horario {
private:
    vector<pair<string, int>> asignaturas; // Asignaturas con su frecuencia
    static const int MAX_DIAS = 5;  // Lunes a Viernes
    static const int MAX_TURNOS = 3; // Tres turnos por día
    vector<vector<string>> horario; // Matriz del horario
    unordered_set<string> asignaturasSet; // Para verificar duplicados

    // Días de la semana
    const vector<string> diasSemana = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes"};

public:
    Horario() : horario(MAX_TURNOS, vector<string>(MAX_DIAS, "")) { 
        // Inicializa la matriz del horario
    }

    bool insertarAsignatura(const string& asignatura, int frecuencia) {
        if (frecuencia < 1 || frecuencia > 3) {
            cerr << "Frecuencia inválida. Debe ser 1, 2 o 3." << endl;
            return false;
        }
        if (asignaturasSet.find(asignatura) != asignaturasSet.end()) {
            cerr << "La asignatura '" << asignatura << "' ya está registrada." << endl;
            return false;
        }
        asignaturas.emplace_back(asignatura, frecuencia);
        asignaturasSet.insert(asignatura); // Agregar a conjunto para evitar duplicados
        return true;
    }

    void agregarAsignaturaEnDiaTurno(const string& asignatura, int dia, int turno) {
        if (dia < 0 || dia >= MAX_DIAS || turno < 0 || turno >= MAX_TURNOS) {
            cerr << "Día o turno inválido." << endl;
            return;
        }
        if (horario[turno][dia].empty()) {
            horario[turno][dia] = asignatura;
            cout << "Asignatura '" << asignatura << "' añadida en " << diasSemana[dia] << " en el turno " << turno + 1 << "." << endl;
        } else {
            cerr << "El turno " << turno + 1 << " en " << diasSemana[dia] << " ya está ocupado." << endl;
        }
    }

    void generarHorario() {
        // Reinicia la matriz
        for (int i = 0; i < MAX_TURNOS; ++i) {
            for (int j = 0; j < MAX_DIAS; ++j) {
                horario[i][j] = "";
            }
        }

        // Asigna las clases según la frecuencia
        for (const auto& par : asignaturas) {
            const string& asignatura = par.first;
            int frecuencia = par.second;

            for (int f = 0; f < frecuencia; ++f) {
                bool assigned = false;
                for (int dia = 0; dia < MAX_DIAS && !assigned; ++dia) {
                    for (int turno = 0; turno < MAX_TURNOS; ++turno) {
                        if (horario[turno][dia].empty()) {
                            horario[turno][dia] = asignatura;
                            assigned = true;
                            break; 
                        }
                    }
                }
            }
        }
    }

    void imprimirHorario() const {
        // Imprimir encabezado
        cout << "Horario:\n";
        
        // Imprimir días de la semana
        cout << setw(8) << " " ; // Espacio para el encabezado de turnos
        for (const string& dia : diasSemana) {
            cout << setw(12) << dia; // Ajustar el ancho para alineación
        }
        cout << endl;

        // Imprimir líneas divisorias
        cout << setw(8) << " " ; // Espacio para el encabezado de turnos
        for (int i = 0; i < MAX_DIAS; ++i) {
            cout << setw(12) << "--------"; // Línea divisoria para cada día
        }
        cout << endl;

        // Imprimir horario
        for (int turno = 0; turno < MAX_TURNOS; ++turno) {
            cout << setw(8) << (turno + 1); // Número de turno
            for (int dia = 0; dia < MAX_DIAS; ++dia) {
                cout << setw(12) << (horario[turno][dia].empty() ? "Libre" : horario[turno][dia]);
                cout << "|"; // Línea divisoria vertical
            }
            cout << endl;

            // Imprimir línea divisoria entre filas
            cout << setw(8) << " " ; // Espacio para el encabezado de turnos
            for (int i = 0; i < MAX_DIAS; ++i) {
                cout << setw(12) << "--------"; // Línea divisoria para cada día
                cout << "|"; // Línea divisoria vertical
            }
            cout << endl;
        }
    }
};

int main() {
    Horario horario;

    // Inserción de asignaturas con frecuencia
    horario.insertarAsignatura("Matemáticas", 2);
    horario.insertarAsignatura("Historia", 1);
    horario.insertarAsignatura("Ciencias", 3);
    horario.insertarAsignatura("Arte", 2);

    // Agregar asignaturas en días y turnos específicos
    string asignatura;
    int dia, turno;

    // Ejemplo de ingreso por parte del usuario
    cout << "Ingrese la asignatura, día (1-5) y turno (1-3):" << endl;
    while (true) {
        cout << "Asignatura (o 'salir' para terminar): ";
        cin >> asignatura;
        if (asignatura == "salir") break;

        cout << "Día (1-Lunes, 2-Martes, 3-Miércoles, 4-Jueves, 5-Viernes): ";
        cin >> dia;
        cout << "Turno (1-3): ";
        cin >> turno;

        // Ajustar a índice 0
        horario.agregarAsignaturaEnDiaTurno(asignatura, dia - 1, turno - 1);
    }

    // Generar el horario después de que el usuario haya ingresado todos los datos
    horario.generarHorario();

    // Imprimir el horario
    horario.imprimirHorario();

    return 0;
}
