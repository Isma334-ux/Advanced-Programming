// ecc_utils.cpp
#include "ecc_utils.h"
#include <chrono>
#include <iostream>

bool generate_keypair(unsigned char* public_key, unsigned char* private_key) {
    crypto_box_keypair(public_key, private_key);
    return true;
}

bool encrypt_message(const unsigned char* message, unsigned long long message_len,
                     const unsigned char* receiver_pk, const unsigned char* sender_sk,
                     unsigned char* nonce, unsigned char* ciphertext, long long& duration_us) {

    randombytes_buf(nonce, crypto_box_NONCEBYTES);
    auto start = std::chrono::high_resolution_clock::now();
    int result = crypto_box_easy(ciphertext, message, message_len, nonce, receiver_pk, sender_sk);
    auto end = std::chrono::high_resolution_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return result == 0;
}

bool decrypt_message(const unsigned char* ciphertext, unsigned long long ciphertext_len,
                     const unsigned char* sender_pk, const unsigned char* receiver_sk,
                     const unsigned char* nonce, unsigned char* decrypted, long long& duration_us) {

    auto start = std::chrono::high_resolution_clock::now();
    int result = crypto_box_open_easy(decrypted, ciphertext, ciphertext_len, nonce, sender_pk, receiver_sk);
    auto end = std::chrono::high_resolution_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return result == 0;
}
