#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <vector>
#include <sstream>
#include <iostream>

class PolynomialMultiplicationApp : public QWidget {
public:
    PolynomialMultiplicationApp(QWidget *parent = nullptr);

private slots:
    void addPolynomial();
    void multiplyPolynomials();
    void clearFields();

private:
    QComboBox *algorithmSelector;
    QLineEdit *inputField;
    QTextEdit *polynomialDisplay;
    QLabel *resultLabel;
    std::vector<std::vector<int>> polynomials; // Almacena los polinomios agregados

    std::vector<int> parsePolynomial(const QString &input);
    std::vector<int> multiplyWithLagrange(const std::vector<int> &p1, const std::vector<int> &p2);
    // Agrega otras funciones de multiplicación de polinomios según los algoritmos
};

PolynomialMultiplicationApp::PolynomialMultiplicationApp(QWidget *parent) : QWidget(parent) {
    // Diseño básico de la interfaz
    algorithmSelector = new QComboBox();
    algorithmSelector->addItem("Lagrange");
    algorithmSelector->addItem("FFT Reales");
    algorithmSelector->addItem("FFT Imaginarios");
    algorithmSelector->addItem("Iterativo con Reverso de Bits");

    inputField = new QLineEdit();
    QPushButton *addButton = new QPushButton("Agregar");
    QPushButton *multiplyButton = new QPushButton("Multiplicar");
    QPushButton *clearButton = new QPushButton("Limpiar");
    polynomialDisplay = new QTextEdit();
    resultLabel = new QLabel("Resultado:");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Elija un algoritmo:"));
    layout->addWidget(algorithmSelector);
    layout->addWidget(new QLabel("Ingrese un polinomio (coeficientes separados por espacios):"));
    layout->addWidget(inputField);
    layout->addWidget(addButton);
    layout->addWidget(multiplyButton);
    layout->addWidget(clearButton);
    layout->addWidget(polynomialDisplay);
    layout->addWidget(resultLabel);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &PolynomialMultiplicationApp::addPolynomial);
    connect(multiplyButton, &QPushButton::clicked, this, &PolynomialMultiplicationApp::multiplyPolynomials);
    connect(clearButton, &QPushButton::clicked, this, &PolynomialMultiplicationApp::clearFields);
}

std::vector<int> PolynomialMultiplicationApp::parsePolynomial(const QString &input) {
    std::vector<int> polynomial;
    std::istringstream iss(input.toStdString());
    int coef;

    while (iss >> coef) {
        polynomial.push_back(coef);
    }

    return polynomial;
}

void PolynomialMultiplicationApp::addPolynomial() {
    QString polynomialText = inputField->text();
    std::vector<int> polynomial = parsePolynomial(polynomialText);
    
    if (!polynomial.empty()) {
        polynomials.push_back(polynomial);
        polynomialDisplay->append("Polinomio agregado: " + polynomialText);
    } else {
        // Manejo de errores: Mostrar un mensaje al usuario si el polinomio es inválido
        polynomialDisplay->append("Error: Polinomio inválido.");
    }
}

void PolynomialMultiplicationApp::multiplyPolynomials() {
    if (polynomials.size() < 2) {
        resultLabel->setText("Error: Necesita al menos dos polinomios para multiplicar.");
        return;
    }

    QString algorithm = algorithmSelector->currentText();
    std::vector<int> result;

    if (algorithm == "Lagrange") {
        // Asumiendo que los polinomios a multiplicar son los dos primeros en el vector
        result = multiplyWithLagrange(polynomials[0], polynomials[1]);
    } else if (algorithm == "FFT Reales") {
        // Implementar FFT con números reales
    } else if (algorithm == "FFT Imaginarios") {
        // Implementar FFT con números imaginarios
    } else if (algorithm == "Iterativo con Reverso de Bits") {
        // Implementar FFT iterativo con reverso de bits
    }

    // Mostrar el resultado
    QString resultStr = "Resultado: ";
    for (const int &coef : result) {
        resultStr += QString::number(coef) + " ";
    }
    resultLabel->setText(resultStr);
}

void PolynomialMultiplicationApp::clearFields() {
    inputField->clear();
    polynomialDisplay->clear();
    resultLabel->clear();
    polynomials.clear();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PolynomialMultiplicationApp window;
    window.setWindowTitle("Multiplicación de Polinomios");
    window.resize(400, 400);
    window.show();

    return app.exec();
}

// Implementar la función para multiplicar polinomios usando Lagrange
std::vector<int> PolynomialMultiplicationApp::multiplyWithLagrange(const std::vector<int> &p1, const std::vector<int> &p2) {
    // Implementación de la multiplicación de polinomios usando el método de Lagrange
    // Retornar el resultado como un vector de coeficientes
    std::vector<int> result; // Implementar la lógica
    return result;
}