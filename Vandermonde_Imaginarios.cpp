#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
using namespace std;

// Definir constante de PI
const double PI = acos(-1);

// FFT recursivo con números imaginarios (dominio complejo)
void FFT(vector<complex<double>>& a, bool invert) {
    int n = a.size();
    if (n == 1) return;
    
    vector<complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }

    FFT(a0, invert);
    FFT(a1, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    complex<double> w(1), wn(cos(angle), sin(angle)); // wn es la raíz de la unidad imaginaria
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Multiplicación de polinomios usando FFT
vector<int> multiplyPolynomialsFFT(vector<int>& A, vector<int>& B) {
    vector<complex<double>> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    int n = 1;
    while (n < A.size() + B.size()) n <<= 1; // Redimensionar a la siguiente potencia de 2
    fa.resize(n);
    fb.resize(n);

    // Aplicar FFT a los coeficientes de A y B
    FFT(fa, false);
    FFT(fb, false);

    // Multiplicar punto a punto los resultados de la FFT
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    // Aplicar la FFT inversa para obtener el resultado en el dominio del tiempo
    FFT(fa, true);

    // Convertir los coeficientes complejos a números enteros redondeando el valor real
    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());

    return result;
}

int main() {
    // Definir dos polinomios para multiplicar
    vector<int> A = {1, 2, 3};  // Polinomio A(x) = 1 + 2x + 3x^2
    vector<int> B = {4, 5, 6};  // Polinomio B(x) = 4 + 5x + 6x^2

    // Llamar a la función de multiplicación de polinomios usando FFT
    vector<int> result = multiplyPolynomialsFFT(A, B);

    // Mostrar el resultado
    cout << "Resultado de la multiplicación de polinomios (FFT Imaginarios): ";
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}