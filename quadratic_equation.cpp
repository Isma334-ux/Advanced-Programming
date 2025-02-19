
#include <iostream>
#include <cmath>
#include <utility> 

std::pair<bool, std::pair<double, double>> solveQuadratic(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return std::make_pair(false, std::make_pair(0, 0));
    } else {
        double sqrtDiscriminant = std::sqrt(discriminant);
        double x1 = (-b + sqrtDiscriminant) / (2 * a);
        double x2 = (-b - sqrtDiscriminant) / (2 * a);
        return std::make_pair(true, std::make_pair(x1, x2));
    }
}

int main() {
    double a, b, c;
    std::cout << "Enter coefficients a, b, and c: ";
    std::cin >> a >> b >> c;

    auto result = solveQuadratic(a, b, c);

    if (result.first) {
        std::cout << "Solutions are: " << result.second.first << " and " << result.second.second << std::endl;
    } else {
        std::cout << "No real solutions." << std::endl;
    }

    return 0;
}