#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

// Declaración de funciones
double euclidean_distance(vector<int>, vector<int>);

// Variables globales
int dimensions = 2; // Dimensiones de cada punto cambiar por 2, 5, 10, 15, 20, 25

int main() {

    // Inicialización de las variables y la uniform int distribution

    random_device rd;       // Semilla del aleatorio
    mt19937 gen(rd());      // Semilla del aleatorio
    int rand_min = 1;       // Valor mínimo del aleatorio
    int rand_max = 1000;    // Valor máximo del aleatorio
    int n_points = 20000;   // Número de puntos generados
    uniform_int_distribution<> distrib(rand_min, rand_max); // Generador de aleatorios
    vector<vector<int>> mat_points; // Vector de los puntos generados


    // Inicio del cronometro

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();


    // Generador de los puntos aleatorios con n dimensiones

    for (int n = 0; n < n_points; ++n) {
        vector<int> point;
        for (int i = 0; i < dimensions; ++i) {
            point.push_back(distrib(gen));
        }
        mat_points.push_back(point);
    }


    // Calcular distancias euclidianas y la distancia máxima y mínima

    vector<int> selector = mat_points[n_points / 2]; // Punto seleccionado del medio para calcular sus distancias con los demás
    vector<double> distances;   // Vector de distancias
    double min;                 // Elemento mínimo
    double max;                 // Elemento máximo
    for (int i = 0; i < mat_points.size(); ++i) {
        double distance = euclidean_distance(selector, mat_points[i]); // Distancia Euclidiana
        distances.push_back(distance);
        if (i == 0) {
            min = distance;
            max = distance;
        }
        if (distance > max) {
            max = distance;
        } else {
            if (distance < min and distance != 0) {
                min = distance;
            }
        }
    }


    // Conteo de frecuencias

    int frec[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (double distance: distances) {
        double percentage = (distance - min) / (max - min);
        frec[(int) (percentage * 10)]++;
    }


    // Fin del cronómetro

    end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start).count(); // duration is holding the elapsed time


    // Imprimir resultado

    cout << "Demoro: " << duration << "ms"<< endl;
    cout << "Valor\tCantidad" << endl;
    for (int i = 0; i < 11; ++i) {
        cout << (double) i / 10 << "\t" << frec[i] << endl;
    }
    return 0;
}
// Fin del main

//Función distancia Euclidiana
double euclidean_distance(vector<int> selector, vector<int> temp) {
    double distance = 0;
    for (int j = 0; j < dimensions; ++j) {
        distance += (pow(selector[j] - temp[j], 2));
    }
    return pow(distance, 0.5);
}
