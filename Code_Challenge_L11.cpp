#include <iostream>
#include <algorithm>
#include <chrono>
#include <utility> 



// PART 2: BUFFER CLASS IMPLEMENTATION
class Buffer {
private:
    int* data;
    size_t size;

public:
    // Constructor
    Buffer(size_t s) : size(s), data(new int[s]) {
        std::cout << "Constructor called (size " << size << ")\n";
    }

    // Destructor
    ~Buffer() {
        delete[] data;
        std::cout << "Destructor called (size " << size << ")\n";
    }

    // Copy constructor
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called (size " << size << ")\n";
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "Copy assignment called (size " << size << ")\n";
        }
        return *this;
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor called (size " << size << ")\n";
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "Move assignment called (size " << size << ")\n";
        }
        return *this;
    }

    size_t getSize() const { return size; }
};

// PART 1: COPY VS MOVE DEMONSTRATION 
void demonstrateCopyVsMove() {
    std::cout << "\n=== Part 1: Demonstrating std::vector copy vs move ===\n";
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = v1;        // Copy
    std::vector<int> v3 = std::move(v1); // Move

    std::cout << "v1 size: " << v1.size() << " (after move)\n";
    std::cout << "v2 size: " << v2.size() << " (copy)\n";
    std::cout << "v3 size: " << v3.size() << " (moved from v1)\n";
}

// PART 3: BUFFER CLASS USAGE
void testBufferOperations() {
    std::cout << "\n=== Part 3: Testing Buffer operations ===\n";
    
    std::cout << "\nCreating b1...\n";
    Buffer b1(100);
    
    std::cout << "\nCreating b2 (copy)...\n";
    Buffer b2 = b1;           // Copy constructor
    
    std::cout << "\nCreating b3 (move)...\n";
    Buffer b3 = std::move(b1); // Move constructor
    
    std::cout << "\nCreating b4...\n";
    Buffer b4(50);
    
    std::cout << "\nAssigning b4 (copy)...\n";
    b4 = b2;                  // Copy assignment
    
    std::cout << "\nAssigning b4 (move)...\n";
    b4 = std::move(b2);       // Move assignment
    
    std::cout << "\nFinal sizes:\n";
    std::cout << "b1: " << b1.getSize() << " (should be 0 after move)\n";
    std::cout << "b2: " << b2.getSize() << " (should be 0 after move)\n";
    std::cout << "b3: " << b3.getSize() << " (should be 100)\n";
    std::cout << "b4: " << b4.getSize() << " (should be 100)\n";
}

// PART 4: PERFORMANCE COMPARISON 
void comparePerformance() {
    std::cout << "\n=== Part 4: Performance Comparison ===\n";
    const size_t largeSize = 10'000'000;
    
    // Test coppy
    auto start = std::chrono::high_resolution_clock::now();
    {
        Buffer b1(largeSize);
        Buffer b2 = b1;  // Copy
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Copy duration: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";
    
    // Test move
    start = std::chrono::high_resolution_clock::now();
    {
        Buffer b1(largeSize);
        Buffer b2 = std::move(b1);  // Move
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Move duration: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";
}

// MAIN FUNCTION 
int main() {
    std::cout << "=== Move Semantics Assignment ===\n";
    
    demonstrateCopyVsMove();
    testBufferOperations();
    comparePerformance();
    
    std::cout << "\n=== Program End ===\n";
    return 0;
}