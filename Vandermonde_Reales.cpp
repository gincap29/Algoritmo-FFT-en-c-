#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
using namespace std;

// Definir constantes
const double PI = acos(-1);

// FFT recursivo
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
    complex<double> w(1), wn(cos(angle), sin(angle));
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
    while (n < A.size() + B.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FFT(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main() {
    vector<int> A = {1, 2, 3}, B = {4, 5, 6};
    vector<int> result = multiplyPolynomialsFFT(A, B);
    
    cout << "Resultado (FFT Reales): ";
    for (int x : result) cout << x << " ";
    cout << endl;
    return 0;
}
