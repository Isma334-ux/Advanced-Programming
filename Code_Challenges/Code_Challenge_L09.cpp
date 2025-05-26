#include <iostream>
#include <string>
#include <concepts>



// Part 1: Basic Template Functions
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;

}

template <typename T>
T maxValue(T a, T b, T c) {
    return maxValue(a, maxValue(b, c));


}

// Part 2: Concepts
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
T add(T a, T b) {
    return a + b;

}

// Parrt 3: Variadic Templates
void printAll() { std::cout << std::endl; } // Base Case for recursion

template <typename T, typename... Args>

void printAll(T t, Args... args) {
    std::cout << t << " ";
    printAll(args...);

}

template <typename T>
T sum(T t) { return t; }

template <typename T, typename... Args>
T sum(T t, Args... args) {
    return t + sum(args...);

}

// Part 4: Template Metaprogramming
template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;

};


template <>
struct Factorial<0> {
    static constexpr int value = 1;

};

template <int N>
struct Fibonacci {

    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;


};

template <>
struct Fibonacci<0> { static constexpr int value = 0; };

template <>
struct Fibonacci<1> { static constexpr int value = 1; };

int main() {
    // Test of all the functions
    std::cout << "Basic Template Functions" << std::endl;
    std::cout << maxValue(5, 10) << std::endl;
    std::cout << maxValue(3.5, 2.1) << std::endl;
    std::cout << maxValue(std::string("apple"), std::string("orange")) << std::endl;
    std::cout << maxValue(1, 5, 3) << std::endl;
    std::cout << maxValue(2.1, 3.7, 1.9) << std::endl;


    std::cout << "\nConcepts" << std::endl;
    std::cout << add(3, 4) << std::endl;
    std::cout << add(2.5, 3.1) << std::endl;

    
    std::cout << "\nVariadic Templates" << std::endl;
    printAll(1, 2.5, "Hello", 'c');
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << sum(1.1, 2.2, 3.3) << std::endl;


    std::cout << "\nTemplate Metaprogramming" << std::endl;
    constexpr int fact = Factorial<5>::value;
    constexpr int fib = Fibonacci<10>::value;
    std::cout << "The factorial of 5 is: " << fact << std::endl;
    std::cout << "Fibonacci(10): " << fib << std::endl;

    return 0;


}