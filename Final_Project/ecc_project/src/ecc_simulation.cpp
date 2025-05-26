#include "ecc_simulation.h"
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/resource.h>

bool initialize_sodium() {
    return sodium_init() >= 0;
}

KeyPair generate_keypair() {
    KeyPair kp;
    crypto_box_keypair(kp.public_key, kp.private_key);
    return kp;
}

bool encrypt_message(const std::string& message, unsigned char* ciphertext,
                     unsigned char* nonce,
                     const unsigned char* receiver_pk,
                     const unsigned char* sender_sk,
                     long long& duration_us) {
    randombytes_buf(nonce, crypto_box_NONCEBYTES);
    auto start = std::chrono::high_resolution_clock::now();

    int result = crypto_box_easy(ciphertext,
                                 reinterpret_cast<const unsigned char*>(message.c_str()),
                                 message.length(),
                                 nonce,
                                 receiver_pk,
                                 sender_sk);

    auto end = std::chrono::high_resolution_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return result == 0;
}

bool decrypt_message(unsigned char* decrypted, const unsigned char* ciphertext,
                     unsigned long long ciphertext_len,
                     const unsigned char* nonce,
                     const unsigned char* sender_pk,
                     const unsigned char* receiver_sk,
                     long long& duration_us) {
    auto start = std::chrono::high_resolution_clock::now();

    int result = crypto_box_open_easy(decrypted,
                                      ciphertext,
                                      ciphertext_len,
                                      nonce,
                                      sender_pk,
                                      receiver_sk);

    auto end = std::chrono::high_resolution_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return result == 0;
}

void run_simulation(const std::string& message, const KeyPair& sender,
                    const KeyPair& receiver, const std::string& csv_path,
                    int iterations) {
    unsigned long long message_len = message.length();
    unsigned long long ciphertext_len = message_len + crypto_box_MACBYTES;

    unsigned char ciphertext[ciphertext_len];
    unsigned char decrypted[message_len + 1];
    unsigned char nonce[crypto_box_NONCEBYTES];

    std::ofstream csv(csv_path);
    if (!csv.is_open()) {
        std::cerr << "Cannot open file " << csv_path << std::endl;
        return;
    }

    csv << "Encryption Time (μs),Decryption Time (μs),Message Size (B),Ciphertext Size (B),Overhead (B)\n";

    for (int i = 0; i < iterations; ++i) {
        long long enc_time = 0, dec_time = 0;

        if (!encrypt_message(message, ciphertext, nonce,
                             receiver.public_key, sender.private_key, enc_time)) {
            std::cerr << "Encryption failed at iteration " << i << "\n";
            continue;
        }

        if (!decrypt_message(decrypted, ciphertext,
                             ciphertext_len,
                             nonce, sender.public_key, receiver.private_key,
                             dec_time)) {
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
