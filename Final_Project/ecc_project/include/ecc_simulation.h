#ifndef ECC_SIMULATION_H
#define ECC_SIMULATION_H

#include <sodium.h>
#include <string>

// Structure for public and private keys
struct KeyPair {
    unsigned char public_key[crypto_box_PUBLICKEYBYTES];
    unsigned char private_key[crypto_box_SECRETKEYBYTES];
};

// Initialize Libsodium
bool initialize_sodium();

// Generation of a pair of keys (Public and Private)
KeyPair generate_keypair();

// Encrypt the message
bool encrypt_message(const std::string& message, unsigned char* ciphertext,
                     unsigned char* nonce,
                     const unsigned char* receiver_pk,
                     const unsigned char* sender_sk,
                     long long& duration_us);

// Decrypt the message
bool decrypt_message(unsigned char* decrypted, const unsigned char* ciphertext,
                     unsigned long long ciphertext_len,
                     const unsigned char* nonce,
                     const unsigned char* sender_pk,
                     const unsigned char* receiver_sk,
                     long long& duration_us);

// Run the simulation 
void run_simulation(const std::string& message, const KeyPair& sender,
                    const KeyPair& receiver, const std::string& csv_path,
                    int iterations = 1000);

#endif
