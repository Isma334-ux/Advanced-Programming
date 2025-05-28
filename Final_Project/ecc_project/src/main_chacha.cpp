#include "chacha_simulation.h"

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
    if (!initialize_sodium_chacha()) {
        std::cerr << "Failed to initialize Libsodium.\n";
        return 1;
    }

    std::vector<size_t> sizes = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

    for (size_t size : sizes) {
        std::string message = generate_random_message(size);
        std::string csv_path = "results/chacha_results_" + std::to_string(size) + "B.csv";

        std::cout << "Running ChaCha20 simulation for message size: " << size << " bytes...\n";
        run_chacha_simulation(message, csv_path, 1000);
        std::cout << "Finished. Results saved to: " << csv_path << "\n\n";
    }

    return 0;
}
