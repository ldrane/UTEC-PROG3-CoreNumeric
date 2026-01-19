#ifndef CORE_NUMERIC_H
#define CORE_NUMERIC_H

#include <concepts>
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <cmath>


//Como estas tareas me permiten me permiten tener mayor profundidad y tiempo decidí:
// Dejar de usar "using namespace std;" porque encontré que comentan que contamina el namespace global.
// Ahora uso std:: explícitamente para evitar conflictos de nombres y seguir esa buena práctica.



// Concepts obligatorios (Dados en la tarea)
namespace core_numeric {
    template <typename C>
    concept Iterable = requires(C c) {
        std::begin(c);
        std::end(c);
    };

    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> std::same_as<T>; //En este caso std::same_as<T> verifica que el tipo de retorno sea exactamente T
    };

    template <typename T>
    concept Divisible = requires(T a, std::size_t n) {
        { a / n } -> std::same_as<T>;
    };


// CONCEPTS PROPIOS (creaciones)
// 1. Concept para tipos que se pueden comparar con operator<
    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a < b } -> std::convertible_to<bool>; //Verifica si es posible convertirlo a booleano
        { a > b } -> std::convertible_to<bool>;
    };


// 2. ALGORITMO: sum
    template <Iterable C>
    requires Addable<typename C::value_type> // value_type lo uso como alias del tipo de elemento almacenado en el contenedor C
    auto sum(const C& container) {
        using T = typename C::value_type;
        T result{};  // Inicializa en 0

        for (const auto& value : container) {
            result = result + value;
        }

        return result;
    }


// 3. ALGORITMO: mean

    template <Iterable C>
    //Primeramente, debemos asegurar que Los elementos del contenedor deben poder sumarse (Addable) Y dividirse (Divisible)
    requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    auto mean(const C& container) {
        using T = typename C::value_type;

        // Reutilizamos sum
        T total = sum(container);
        std::size_t count = 0;

        for ([[maybe_unused]] const auto& _ : container) {
            ++count;
        }

        return total / count;
    }


// 4. ALGORITMO: variance
    template <Iterable C>
    requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    auto variance(const C& container) {
        using T = typename C::value_type;

        // Reutilizamos mean
        T avg = mean(container);
        T sum_squared_diff{};
        std::size_t count = 0;

        for (const auto& value : container) {
            T diff = value - avg;
            sum_squared_diff = sum_squared_diff + (diff * diff);
            ++count;
        }

        return sum_squared_diff / count;
    }


// 5. ALGORITMO: max (le integré concept propio Comparable)
    template <Iterable C>
    requires Comparable<typename C::value_type>
    auto max(const C& container) {
        using T = typename C::value_type;

        auto it = std::begin(container);
        auto end_it = std::end(container);

        T max_value = *it;
        ++it;

        for (; it != end_it; ++it) {
            if (*it > max_value) {
                max_value = *it;
            }
        }

        return max_value;
    }


// 6. ALGORITMO: transform_reduce
    template <Iterable C, typename Func>
    requires Addable<typename C::value_type>
    auto transform_reduce(const C& container, Func func) {
        using T = typename C::value_type;
        using R = decltype(func(std::declval<T>()));

        R result{};

        for (const auto& value : container) {
            result = result + func(value);
        }

        return result;
    }


// 7. VARIADIC TEMPLATES: sum_variadic
    template <Addable... Args>
    auto sum_variadic(Args... args) {
        return (args + ...);
    }


// 8. VARIADIC TEMPLATES: mean_variadic
    template <typename... Args>
    requires (Addable<Args> && ...) && (Divisible<Args> && ...)
    auto mean_variadic(Args... args) {
        // Usamos sum_variadic y dividimos por cantidad de argumentos
        auto total = sum_variadic(args...);
        return total / sizeof...(args);
    }


// 9. VARIADIC TEMPLATES: variance_variadic
    template <typename... Args>
    requires (Addable<Args> && ...) && (Divisible<Args> && ...)
    auto variance_variadic(Args... args) {
        // Calculamos media
        auto avg = mean_variadic(args...);

        // Calculamos suma de diferencias cuadradas
        auto sum_sq_diff = (((args - avg) * (args - avg)) + ...);

        return sum_sq_diff / sizeof...(args);
    }


// 10. VARIADIC TEMPLATES: max_variadic
    template <Comparable T, Comparable... Args>
    auto max_variadic(T first, Args... rest) {
        if constexpr (sizeof...(rest) == 0) {
            //Caso base: Sólo un argumento
            return first;
        } else {
            // Caso recursivo: comparar primero con el máximo del resto
            auto max_rest = max_variadic(rest...);
            return (first > max_rest) ? first : max_rest;
        }
    }


// 11. USO DE if constexpr
    template <typename T>
    requires Addable<T>
    auto process_number(T value) {
        if constexpr (std::is_integral_v<T>) {
            // Para int: retornamos el doble
            return value + value;
        } else {
            // Para floats: retornamos el cuadrado
            return value * value;
        }
    }

} // namespace core_numeric

#endif