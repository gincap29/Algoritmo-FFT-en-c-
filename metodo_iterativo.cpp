#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
using namespace std;

const double PI = acos(-1);

// Función para invertir bits
unsigned int reverseBits(unsigned int num, int log_n) {
    unsigned int result = 0;
    for (int i = 0; i < log_n; i++) {
        if (num & (1 << i)) result |= (1 << (log_n - 1 - i));
    }
    return result;
}

// FFT iterativo con reverso de bits
void iterativeFFT(vector<complex<double>>& a, bool invert) {
    int n = a.size();
    int log_n = log2(n);
    
    for (int i = 0; i < n; i++) {
        int rev = reverseBits(i, log_n);
        if (i < rev) swap(a[i], a[rev]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        complex<double> wn(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }

    if (invert) {
        for (complex<double>& x : a) x /= n;
    }
}

// Multiplicación de polinomios usando el método iterativo FFT
vector<int> multiplyPolynomialsIterativeFFT(vector<int>& A, vector<int>& B) {
    vector<complex<double>> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    int n = 1;
    while (n < A.size() + B.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    iterativeFFT(fa, false);
    iterativeFFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    iterativeFFT(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main() {
    vector<int> A = {1, 2, 3}, B = {4, 5, 6};
    vector<int> result = multiplyPolynomialsIterativeFFT(A, B);

    cout << "Resultado (Iterativo con reverso de bits): ";
    for (int x : result) cout << x << " ";
    cout << endl;
    return 0;
}