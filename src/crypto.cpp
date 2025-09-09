#include "../include/crypto.h"
#include <sodium.h>
#include <stdexcept>

std::string to_base64(const std::vector<unsigned char>& data) {
    std::vector<char> encoded(sodium_base64_ENCODED_LEN(data.size(), sodium_base64_VARIANT_ORIGINAL));
    sodium_bin2base64(encoded.data(), encoded.size(), data.data(), data.size(), sodium_base64_VARIANT_ORIGINAL);
    return std::string(encoded.data());
}

std::vector<unsigned char> from_base64(const std::string& b64) {
    size_t bin_len;
    std::vector<unsigned char> bin(b64.size());
    if (sodium_base642bin(bin.data(), bin.size(), b64.c_str(), b64.size(), nullptr, &bin_len, nullptr, sodium_base64_VARIANT_ORIGINAL) != 0) 
        throw std::runtime_error("Base64 inválida");
    bin.resize(bin_len);
    return bin;
}

std::vector<unsigned char> generate_key(const std::string& password, const std::vector<unsigned char>& salt) {
    std::vector<unsigned char> key(crypto_secretbox_KEYBYTES);
    if(crypto_pwhash(key.data(), key.size(), password.c_str(), password.size(), salt.data(),
                     crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                     crypto_pwhash_ALG_DEFAULT) != 0)
        throw std::runtime_error("Falha no hash da senha");
    return key;
}

std::vector<unsigned char> encrypt(const std::vector<unsigned char>& key, const std::string& message, std::vector<unsigned char>& nonce_out) {
    std::vector<unsigned char> ciphertext(crypto_secretbox_MACBYTES + message.size());
    nonce_out.resize(crypto_secretbox_NONCEBYTES);
    randombytes_buf(nonce_out.data(), nonce_out.size());
    crypto_secretbox_easy(ciphertext.data(), reinterpret_cast<const unsigned char*>(message.data()), message.size(), nonce_out.data(), key.data());
    return ciphertext;
}

std::string decrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& nonce) {
    std::vector<unsigned char> decrypted(ciphertext.size() - crypto_secretbox_MACBYTES);
    if(crypto_secretbox_open_easy(decrypted.data(), ciphertext.data(), ciphertext.size(), nonce.data(), key.data()) != 0)
        throw std::runtime_error("Falha ao descriptografar");
    return std::string(decrypted.begin(), decrypted.end());
}
