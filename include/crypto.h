#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>
#include <sodium.h>
#include <stdexcept>
#include "../include/funcoes_main.h"

std::string to_base64(const std::vector<unsigned char>& data);
std::vector<unsigned char> from_base64(const std::string& b64);

std::vector<unsigned char> generate_key(const std::string& password, const std::vector<unsigned char>& salt);
std::vector<unsigned char> encrypt(const std::vector<unsigned char>& key, const std::string& message, std::vector<unsigned char>& nonce_out);
std::string decrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& nonce);

#endif // CRYPTO_H
