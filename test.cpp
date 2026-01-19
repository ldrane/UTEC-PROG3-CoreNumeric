#include "core_numeric.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ------------------------------------------------------------
// CLASES PERSONALIZADAS PARA PRUEBAS
// ------------------------------------------------------------

class Coordenada {
public:
    double x, y;

    Coordenada(double x = 0, double y = 0) : x(x), y(y) {}

    // operator+ para que sea Addable
    Coordenada operator+(const Coordenada& other) const {
        return Coordenada(x + other.x, y + other.y);
    }

    // operator- para variance
    Coordenada operator-(const Coordenada& other) const {
        return Coordenada(x - other.x, y - other.y);
    }

    // operator* para variance
    Coordenada operator*(const Coordenada& other) const {
        return Coordenada(x * other.x, y * other.y);
    }

    // operator/ para que sea Divisible
    Coordenada operator/(size_t n) const {
        return Coordenada(x / n, y / n);
    }

    // operator< para que sea Comparable
    bool operator<(const Coordenada& other) const {
        return (x * x + y * y) < (other.x * other.x + other.y * other.y);
    }

    bool operator>(const Coordenada& other) const {
        return (x * x + y * y) > (other.x * other.x + other.y * other.y);
    }

    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

// Clase Vector3D (NO tiene operator< -> NO es Comparable)
class Vector3D {
public:
    double x, y, z;

    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    // operator+ para que sea Addable
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    // operator- para variance
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // operator* para variance
    Vector3D operator*(const Vector3D& other) const {
        return Vector3D(x * other.x, y * other.y, z * other.z);
    }

    // operator/ para que sea Divisible
    Vector3D operator/(size_t n) const {
        return Vector3D(x / n, y / n, z / n);
    }

    // NO tiene operator< ni operator>

    void print() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

int main() {
    cout << "=== TESTS - CASOS QUE COMPILAN Y NO COMPILAN ===" << endl << endl;

    // ------------------------------------------------------------
    // CASOS QUE COMPILAN
    // ------------------------------------------------------------

    cout << "=== CASOS QUE COMPILAN ===" << endl << endl;

    // 1. sum con int
    vector<int> v_int{1, 2, 3, 4};
    cout << "sum con vector<int>: " << core_numeric::sum(v_int) << endl;

    // 2. sum con double
    vector<double> v_double{1.5, 2.5, 3.5};
    cout << "sum con vector<double>: " << core_numeric::sum(v_double) << endl;

    // 3. sum con Coordenada (tiene operator+)
    vector<Coordenada> v_coord{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    auto sum_coord = core_numeric::sum(v_coord);
    cout << "sum con vector<Coordenada>: ";
    sum_coord.print();
    cout << endl;

    // 4. mean con double
    cout << "mean con vector<double>: " << core_numeric::mean(v_double) << endl;

    // 5. mean con Coordenada (tiene operator+ y operator/)
    auto mean_coord = core_numeric::mean(v_coord);
    cout << "mean con vector<Coordenada>: ";
    mean_coord.print();
    cout << endl;

    // 6. variance con double
    cout << "variance con vector<double>: " << core_numeric::variance(v_double) << endl;

    // 7. variance con Coordenada
    auto var_coord = core_numeric::variance(v_coord);
    cout << "variance con vector<Coordenada>: ";
    var_coord.print();
    cout << endl;

    // 8. max con int
    cout << "max con vector<int>: " << core_numeric::max(v_int) << endl;

    // 9. max con Coordenada (tiene operator<)
    auto max_coord = core_numeric::max(v_coord);
    cout << "max con vector<Coordenada>: ";
    max_coord.print();
    cout << endl;

    // 10. transform_reduce con lambda
    auto tr = core_numeric::transform_reduce(v_double, [](double x) { return x * x; });
    cout << "transform_reduce con lambda: " << tr << endl;

    // 11. sum_variadic con int
    cout << "sum_variadic(1, 2, 3): " << core_numeric::sum_variadic(1, 2, 3) << endl;

    // 12. mean_variadic con double
    cout << "mean_variadic(1.0, 2.0, 3.0): "
         << core_numeric::mean_variadic(1.0, 2.0, 3.0) << endl;

    // 13. max_variadic con double
    cout << "max_variadic(1.5, 2.7, 0.3): "
         << core_numeric::max_variadic(1.5, 2.7, 0.3) << endl;

    cout << endl;

    // ========================================
    // CASOS QUE NO COMPILAN (COMENTADOS)
    // ========================================

    cout << "=== CASOS QUE NO COMPILAN ===" << endl << endl;

    // 1. sum con vector<string>
    // FALLA: std::string no cumple Addable (operator+ devuelve string, no mismo tipo)
    // vector<string> v_str{"hola", "mundo"};
    // auto sum_str = core_numeric::sum(v_str);
    // ERROR PRESENTE: Concept Addable no se cumple

    cout << "1. sum con vector<string> - FALLA: string no es Addable" << endl;

    // 2. mean con vector<string>
    // FALLA: std::string no cumple Divisible
    // auto mean_str = core_numeric::mean(v_str);
    // ERROR PRESENTE: Concept Divisible no se cumple

    cout << "2. mean con vector<string> - FALLA: string no es Divisible" << endl;

    // 3. variance con vector<string>
    // FALLA: std::string no cumple Addable ni tiene operator-
    // vector<string> v_str2{"a", "b", "c"};
    // auto var_str = core_numeric::variance(v_str2);
    // ERROR PRESENTE: Concepts Addable/Divisible no se cumplen

    cout << "3. variance con vector<string> - FALLA: string no soporta operaciones aritméticas" << endl;

    // 4. max con Vector3D
    // FALLA: Vector3D noO tiene operator< (no es Comparable)
    // vector<Vector3D> v_vec3d{{1,2,3}, {4,5,6}};
    // auto max_vec = core_numeric::max(v_vec3d);
    // ERROR PRESENTE: Concept Comparable no se cumple

    cout << "4. max con vector<Vector3D> - FALLA: Vector3D no es Comparable (no tiene operator<)" << endl;

    // 5. sum_variadic con tipos mixtos incompatibles
    // FALLA: No se puede sumar int + string
    // auto mixed = core_numeric::sum_variadic(1, "hola", 3);
    // ERROR PRESENTE: Tipos no son compatibles para suma

    cout << "5. sum_variadic con tipos mixtos - FALLA: int y string no son compatibles" << endl;

    // 6. mean_variadic con string
    // FALLA: string no es Divisible
    // auto mean_strings = core_numeric::mean_variadic("a", "b", "c");
    // ERROR PRESENTE: Concept Divisible no se cumple

    cout << "6. mean_variadic con string - FALLA: string no es Divisible" << endl;

    // 7. max_variadic con Vector3D
    // FALLA: Vector3D no es Comparable
    // auto max_vec_var = core_numeric::max_variadic(
    //     Vector3D{1,2,3}, Vector3D{4,5,6}
    // );
    // ERROR PRESENTE: Concept Comparable no se cumple

    cout << "7. max_variadic con Vector3D - FALLA: Vector3D no es Comparable" << endl;

    // 8. sum con tipos no iterables
    // FALLA: int no es Iterable
    // int x = 5;
    // auto sum_int = core_numeric::sum(x);
    // ERROR: Concept Iterable no se cumple

    cout << "8. sum con int (no contenedor) - FALLA: int no es Iterable" << endl;

    // 9. transform_reduce sin lambda compatible
    // FALLA: lambda retorna string, no se puede sumar
    // auto tr_bad = core_numeric::transform_reduce(v_int, [](int x) { 
    //     return to_string(x); 
    // });
    // ERROR: string no es Addable

    cout << "9. transform_reduce con lambda que retorna string - FALLA: string no es Addable" << endl;

    // 10. variance_variadic con un solo argumento
    // Compila pero matemáticamente da 0 (varianza de un elemento)
    auto var_one = core_numeric::variance_variadic(5.0);
    cout << "10. variance_variadic(5.0) - Compila pero da 0: " << var_one << endl;

    cout << endl;
    cout << "=== FIN DE LOS TESTS ===" << endl;

    return 0;
}