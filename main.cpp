#include "core_numeric.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "=== CORE NUMERIC - BIBLIOTECA GENÉRICA ===" << endl << endl;

    // ----------------------------------------
    // EJEMPLOS CON CONTENEDORES
    // ----------------------------------------
    cout << "=== ALGORITMOS CON CONTENEDORES ===" << endl << endl;

    // sum
    vector<double> v1{1.0, 2.0, 3.0, 4.0, 5.0};
    cout << "sum({1.0, 2.0, 3.0, 4.0, 5.0}): "
         << core_numeric::sum(v1) << endl;

    // mean
    vector<double> v2{1.0, 2.0, 3.0};
    cout << "mean({1.0, 2.0, 3.0}): "
         << core_numeric::mean(v2) << endl;

    // variance
    vector<double> v3{1.0, 2.0, 3.0, 4.0};
    cout << "variance({1.0, 2.0, 3.0, 4.0}): "
         << core_numeric::variance(v3) << endl;

    // max
    vector<double> v4{1.5, 2.7, 0.3, 4.2};
    cout << "max({1.5, 2.7, 0.3, 4.2}): "
         << core_numeric::max(v4) << endl;

    // transform_reduce
    vector<double> v5{1.0, 2.0, 3.0};
    auto r = core_numeric::transform_reduce(v5, [](double x) {
        return x * x;
    });
    cout << "transform_reduce({1.0, 2.0, 3.0}, x*x): " << r << endl;

    cout << endl;

    // ----------------------------------------
    // EJEMPLOS CON VARIADIC TEMPLATES
    // ----------------------------------------

    cout << "=== VARIADIC TEMPLATES ===" << endl << endl;

    // sum_variadic
    auto s1 = core_numeric::sum_variadic(1, 2, 33, 4);
    cout << "sum_variadic(1, 2, 33, 4): " << s1 << endl;

    // mean_variadic
    auto s2 = core_numeric::mean_variadic(0.1, 2.0, 3.0, 4.0);
    cout << "mean_variadic(0.1, 2.0, 3.0, 4.0): " << s2 << endl;

    // variance_variadic
    auto s3 = core_numeric::variance_variadic(1.0, 2.0, 3.0, 4.0);
    cout << "variance_variadic(1.0, 2.0, 3.0, 4.0): " << s3 << endl;

    // max_variadic
    auto s4 = core_numeric::max_variadic(1.0, 2.7, 3.0, 4.0);
    cout << "max_variadic(1.0, 2.7, 3.0, 4.0): " << s4 << endl;

    cout << endl;

    // ----------------------------------------
    // EJEMPLOS CON if constexpr
    // ----------------------------------------

    cout << "=== if constexpr ===" << endl << endl;

    int entero = 5;
    double flotante = 3.5;

    cout << "process_number(5) [int]: "
         << core_numeric::process_number(entero) << endl;
    cout << "process_number(3.5) [float]: "
         << core_numeric::process_number(flotante) << endl;

    cout << endl;

    return 0;
}