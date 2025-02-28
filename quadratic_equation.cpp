#include <iostream>
#include <cmath>
#include <utility>

std::pair<bool, std::pair<double, double>> solveQuadratic(double a, double b, double c) {
    double discriminant = pow(b,2) - (4 * a * c);

    if (a == 0) {
        std::cout << "If a is zero, then it is not a quadratic equation" << std::endl;
        return {false, {0, 0}};
    } else {
        if (discriminant < 0) {
            return {false, {0, 0}};
        } else {
            double x1 = (-b + sqrt(discriminant)) / (2*a);
            double x2 = (-b - sqrt(discriminant)) / (2*a);
    
            return {true, {x1, x2}};
        }
    }

}

int main() {
    double a, b, c;
    std::cout << "Enter the coefficients of the quadratic equation" << std::endl;
    std::cin >> a >> b >> c;

    auto result = solveQuadratic(a, b, c);


    if (result.first) {
        if (result.second.first == result.second.second) {
            std::cout << "The solution is: " << " x = " << result.second.first << std::endl;
        } else {
            std::cout << "The solutions are: " << "x1 = " << result.second.first << " and " << " x2 = " << result.second.second << std::endl;      

        }
    } else {
        std::cout << "No real solutions" << std::endl;
    }
    return 0;
}