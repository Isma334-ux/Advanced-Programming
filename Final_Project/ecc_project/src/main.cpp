#include "ecc_simulation.h"
#include <iostream>
#include <string>
#include <vector>

// Función para generar un string aleatorio del tamaño dado
std::string generate_random_message(size_t size) {
    std::string msg;
    msg.resize(size);
    randombytes_buf(&msg[0], size);
    return msg;
}

int main() {
    if (!initialize_sodium()) {
        std::cerr << "Failed to initialize Libsodium." << std::endl;
        return 1;
    }

    KeyPair device_A = generate_keypair();
    KeyPair device_B = generate_keypair();

    std::vector<size_t> sizes = {10, 100, 1024, 10240}; // 10B, 100B, 1KB, 10KB

    for (size_t size : sizes) {
        std::string message = generate_random_message(size);
        std::string csv_path = "results/ecc_results_" + std::to_string(size) + "B.csv";

        std::cout << "Running simulation for message size: " << size << " bytes...\n";
        run_simulation(message, device_A, device_B, csv_path, 1000);
        std::cout << "Finished. Results saved to: " << csv_path << "\n\n";
    }

    return 0;
}
