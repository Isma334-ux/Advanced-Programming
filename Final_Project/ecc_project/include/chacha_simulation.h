#ifndef CHACHA_SIMULATION_H
#define CHACHA_SIMULATION_H

#include <sodium.h>
#include <string>

// Structure for the key and the nonce
struct ChaChaKey {
    unsigned char key[crypto_aead_chacha20poly1305_ietf_KEYBYTES];
    unsigned char nonce[crypto_aead_chacha20poly1305_ietf_NPUBBYTES];
};

// Initialization of libsodium
bool initialize_sodium_chacha();

// Generate key and nonce
ChaChaKey generate_chacha_key();

// Encrypt message
bool chacha_encrypt(const std::string& message, unsigned char* ciphertext,
                    unsigned long long& ciphertext_len,
                    const ChaChaKey& chacha_key,
                    long long& duration_us);

// Decrypt mensaje
bool chacha_decrypt(unsigned char* decrypted,
                    const unsigned char* ciphertext,
                    unsigned long long ciphertext_len,
                    const ChaChaKey& chacha_key,
                    long long& duration_us);

// Run simulation
void run_chacha_simulation(const std::string& message,
                           const std::string& csv_path,
                           int iterations = 1000);

#endif
