#include "ecc_simulation.h"
#include <iostream>
#include <string>
#include <vector>

// Generates a random message of a given size
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

    std::vector<size_t> sizes = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

    for (size_t size : sizes) {
        std::string message = generate_random_message(size);
        std::string csv_path = "results/ecc_results_" + std::to_string(size) + "B.csv";

        std::cout << "Running simulation for message size: " << size << " bytes...\n";
        run_simulation(message, device_A, device_B, csv_path, 1000);
        std::cout << "Finished. Results saved to: " << csv_path << "\n\n";
    }

    return 0;
}
