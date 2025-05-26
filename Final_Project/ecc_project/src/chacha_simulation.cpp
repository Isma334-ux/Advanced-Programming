#include "chacha_simulation.h"

#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>

bool initialize_sodium_chacha() {
    return sodium_init() >= 0;
}

ChaChaKey generate_chacha_key() {
    ChaChaKey ck;
    randombytes_buf(ck.key, sizeof(ck.key));
    randombytes_buf(ck.nonce, sizeof(ck.nonce));
    return ck;
}

bool chacha_encrypt(const std::string& message, unsigned char* ciphertext,
                    unsigned long long& ciphertext_len,
                    const ChaChaKey& chacha_key,
                    long long& duration_us) {

    unsigned long long message_len = message.length();
    const unsigned char* m = reinterpret_cast<const unsigned char*>(message.c_str());

    auto start = std::chrono::high_resolution_clock::now();

    int result = crypto_aead_chacha20poly1305_ietf_encrypt(
        ciphertext, &ciphertext_len,
        m, message_len,
        nullptr, 0,               // no additional data
        nullptr,                  // no secret nonce
        chacha_key.nonce,
        chacha_key.key
    );

    auto end = std::chrono::high_resolution_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return result == 0;
}

bool chacha_decrypt(unsigned char* decrypted,
                    const unsigned char* ciphertext,
                    unsigned long long ciphertext_len,
                    const ChaChaKey& chacha_key,
                    long long& duration_us) {

    unsigned long long decrypted_len;

    auto start = std::chrono::high_resolution_clock::now();

    int result = crypto_aead_chacha20poly1305_ietf_decrypt(
        decrypted, &decrypted_len,
        nullptr,                  // no MAC check output
        ciphertext, ciphertext_len,
        nullptr, 0,               // no additional data
        chacha_key.nonce,
        chacha_key.key
    );

    auto end = std::chrono::high_resolution_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return result == 0;
}

void run_chacha_simulation(const std::string& message,
                           const std::string& csv_path,
                           int iterations) {

    unsigned long long message_len = message.length();
    unsigned long long max_ciphertext_len = message_len + crypto_aead_chacha20poly1305_ietf_ABYTES;

    unsigned char ciphertext[max_ciphertext_len];
    unsigned char decrypted[message_len + 1];

    ChaChaKey ck = generate_chacha_key();

    std::ofstream csv(csv_path);
    if (!csv.is_open()) {
        std::cerr << "Cannot open file " << csv_path << std::endl;
        return;
    }

    csv << "Encryption Time (μs),Decryption Time (μs),Message Size (B),Ciphertext Size (B),Overhead (B)\n";

    for (int i = 0; i < iterations; ++i) {
        long long enc_time = 0, dec_time = 0;
        unsigned long long ciphertext_len = 0;

        if (!chacha_encrypt(message, ciphertext, ciphertext_len, ck, enc_time)) {
            std::cerr << "Encryption failed at iteration " << i << "\n";
            continue;
        }

        if (!chacha_decrypt(decrypted, ciphertext, ciphertext_len, ck, dec_time)) {
            std::cerr << "Decryption failed at iteration " << i << "\n";
            continue;
        }

        decrypted[message_len] = '\0'; // Null-terminate
        unsigned long long overhead = ciphertext_len - message_len;

        csv << enc_time << "," << dec_time << ","
            << message_len << "," << ciphertext_len << "," << overhead << "\n";
    }

    csv.close();
}
