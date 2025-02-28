#include <iostream>
#include <string>

// Part 4: Structured Binding
struct Point {
    int x;
    int y;
    int z;
};

int main() {
    // Part 1: Variable Initialization

    // All of these are direct initialization
    int a = 10; 
    double b = 3.14;  
    std::string c = "Hello"; 
    bool d = true; 

    // All of these are Uniform initialization
    int e{20};  
    double f{2.71};  
    std::string g{"World"};  
    bool h{false};  

    // Print of the initial values
    std::cout << "Initial values:\n";
    std::cout << "int: " << a << ", double: " << b << ", string: " << c << ", bool: " << d << "\n";
    std::cout << "Uniform initialization values:\n";
    std::cout << "int: " << e << ", double: " << f << ", string: " << g << ", bool: " << h << "\n\n";

    // Part 3: References
    int& refA = a;  // Reference to 'a'
    double& refB = b;  // Reference to 'b'
    std::string& refC = c;  // Reference to 'c'
    bool& refD = d;  // Reference to 'd'

    // Modify values using references
    refA = 20;
    refB = 2.71;
    refC = "World";
    refD = false;

    // Print modified values
    std::cout << "Modified values:\n";
    std::cout << "int: " << a << ", double: " << b << ", string: " << c << ", bool: " << d << "\n\n";

    // Part 4: Structured Binding
    Point p{5, 10, 15};  // Create an instance of Point
    auto [x, y, z] = p;  // Structured binding to unpack members

    // Print unpacked values
    std::cout << "Structured Binding:\n";
    std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n\n";

    // Part 5: Identifying l-values and r-values
    // 1. a = 42;
    a = 42;  // 'a' is an l-value, 42 is an r-value

    // 2. int x = a + b;
    int xVal = a + b;  // 'a' and 'b' are l-values, (a + b) is an r-value

    // 3. &a;
    int* ptrA = &a;  // 'a' is an l-value, &a is an r-value (address of 'a')

    // 4. std::string s = c + " World";
    std::string s = c + " World";  // 'c' is an l-value, "World" is an r-value, (c + " World") is an r-value

    // 5. int& refX = xVal;
    int& refX = xVal;  // 'xVal' is an l-value, refX is an l-value reference

    // 6. int&& rref = 100;
    int&& rref = 100;  // 100 is an r-value, rref is an r-value reference

    // Print value categories (comments in code)
    std::cout << "Value Categories\n";
    std::cout << "a = 42; // l-value\n";
    std::cout << "int x = a + b; // a and b are l-values, (a + b) is an r-value\n";
    std::cout << "&a; // l-value\n";
    std::cout << "std::string s = c + \" World\"; // c is an l-value, \"World\" is an r-value, (c + \" World\") is an r-value\n";
    std::cout << "int& refX = x; // l-value reference\n";
    std::cout << "int&& rref = 100; // r-value reference\n";

    return 0;
}
