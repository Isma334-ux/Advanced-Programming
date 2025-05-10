// main.cpp
#include "ecc_utils.h"
#include <iostream>
#include <fstream>
#include <cstring>

int main() {
    if (sodium_init() < 0) {
        std::cerr << "Libsodium could not be initialized." << std::endl;
        return 1;
    }

    const char* message = "Welcome to Yachay Tech";
    unsigned long long message_len = strlen(message);

    unsigned char pk_A[crypto_box_PUBLICKEYBYTES], sk_A[crypto_box_SECRETKEYBYTES];
    unsigned char pk_B[crypto_box_PUBLICKEYBYTES], sk_B[crypto_box_SECRETKEYBYTES];

    generate_keypair(pk_A, sk_A);
    generate_keypair(pk_B, sk_B);

    std::ofstream csv_file("results/results.csv");
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open CSV file." << std::endl;
        return 1;
    }
    csv_file << "Encryption Time (μs),Decryption Time (μs)\n";

    const int NUM_ITERATIONS = 1000;
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        unsigned char nonce[crypto_box_NONCEBYTES];
        unsigned char ciphertext[message_len + crypto_box_MACBYTES];
        unsigned char decrypted[message_len + 1];
        long long encrypt_time = 0, decrypt_time = 0;

        if (!encrypt_message(reinterpret_cast<const unsigned char*>(message), message_len,
                             pk_B, sk_A, nonce, ciphertext, encrypt_time)) {
            std::cerr << "Encryption failed at iteration " << i << std::endl;
            continue;
        }

        if (!decrypt_message(ciphertext, message_len + crypto_box_MACBYTES,
                             pk_A, sk_B, nonce, decrypted, decrypt_time)) {
            std::cerr << "Decryption failed at iteration " << i << std::endl;
            continue;
        }

        decrypted[message_len] = '\0';
        csv_file << encrypt_time << "," << decrypt_time << "\n";
    }

    csv_file.close();
    return 0;
}
