#include <iostream>
#include <vector>
using namespace std;

// Función para la interpolación de Lagrange
double LagrangeInterpolation(vector<double>& x, vector<double>& y, double xi) {
    double result = 0.0;
    int n = x.size();
    
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i)
                term = term * (xi - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }
    return result;
}

// Función principal para multiplicar polinomios usando Lagrange
void multiplyPolynomialsLagrange(vector<vector<double>>& polys) {
    vector<double> x = {1, 2, 3}; // Puntos para la interpolación
    vector<double> y(polys[0].size(), 0);

    for (size_t i = 0; i < polys.size(); i++) {
        for (size_t j = 0; j < polys[i].size(); j++) {
            y[j] += polys[i][j];
        }
    }
    
    cout << "Resultado (Interpolación Lagrange): ";
    for (double xi : x) {
        cout << LagrangeInterpolation(x, y, xi) << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<double>> polys = {{1, 2, 1}, {1, 1, 0}};
    multiplyPolynomialsLagrange(polys);
    return 0;
}
