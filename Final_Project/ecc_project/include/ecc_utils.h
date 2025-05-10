// ecc_utils.h
#ifndef ECC_UTILS_H
#define ECC_UTILS_H

#include <sodium.h>
#include <string>

bool generate_keypair(unsigned char* public_key, unsigned char* private_key);
bool encrypt_message(const unsigned char* message, unsigned long long message_len,
                     const unsigned char* receiver_pk, const unsigned char* sender_sk,
                     unsigned char* nonce, unsigned char* ciphertext, long long& duration_us);
bool decrypt_message(const unsigned char* ciphertext, unsigned long long ciphertext_len,
                     const unsigned char* sender_pk, const unsigned char* receiver_sk,
                     const unsigned char* nonce, unsigned char* decrypted, long long& duration_us);

#endif // ECC_UTILS_H
