#ifndef CHACHA_SIMULATION_H
#define CHACHA_SIMULATION_H

#include <sodium.h>
#include <string>

// Estructura para clave y nonce
struct ChaChaKey {
    unsigned char key[crypto_aead_chacha20poly1305_ietf_KEYBYTES];
    unsigned char nonce[crypto_aead_chacha20poly1305_ietf_NPUBBYTES];
};

// Inicializa Libsodium
bool initialize_sodium_chacha();

// Genera clave y nonce
ChaChaKey generate_chacha_key();

// Cifra mensaje
bool chacha_encrypt(const std::string& message, unsigned char* ciphertext,
                    unsigned long long& ciphertext_len,
                    const ChaChaKey& chacha_key,
                    long long& duration_us);

// Descifra mensaje
bool chacha_decrypt(unsigned char* decrypted,
                    const unsigned char* ciphertext,
                    unsigned long long ciphertext_len,
                    const ChaChaKey& chacha_key,
                    long long& duration_us);

// Corre simulación
void run_chacha_simulation(const std::string& message,
                           const std::string& csv_path,
                           int iterations = 1000);

#endif
