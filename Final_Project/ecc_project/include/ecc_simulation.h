#ifndef ECC_SIMULATION_H
#define ECC_SIMULATION_H

#include <sodium.h>
#include <string>

// Estructura para guardar claves públicas y privadas
struct KeyPair {
    unsigned char public_key[crypto_box_PUBLICKEYBYTES];
    unsigned char private_key[crypto_box_SECRETKEYBYTES];
};

// Inicializa Libsodium
bool initialize_sodium();

// Genera un par de claves (públicas y privadas)
KeyPair generate_keypair();

// Cifra un mensaje
bool encrypt_message(const std::string& message, unsigned char* ciphertext,
                     unsigned char* nonce,
                     const unsigned char* receiver_pk,
                     const unsigned char* sender_sk,
                     long long& duration_us);

// Descifra un mensaje
bool decrypt_message(unsigned char* decrypted, const unsigned char* ciphertext,
                     unsigned long long ciphertext_len,
                     const unsigned char* nonce,
                     const unsigned char* sender_pk,
                     const unsigned char* receiver_sk,
                     long long& duration_us);

// Ejecuta múltiples iteraciones y guarda los resultados en CSV
void run_simulation(const std::string& message, const KeyPair& sender,
                    const KeyPair& receiver, const std::string& csv_path,
                    int iterations = 1000);

#endif
