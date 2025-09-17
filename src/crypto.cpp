/**
 * @file crypto.cpp
 * @brief Funções utilitárias para criptografia, descriptografia e manipulação de dados em Base64 usando libsodium.
 */

#include "../include/crypto.h"
#include <sodium.h>
#include <stdexcept>

/**
 * @brief Converte um vetor de bytes para uma string em Base64.
 * @param data Vetor de bytes a ser convertido.
 * @return String codificada em Base64.
 */
std::string to_base64(const std::vector<unsigned char>& data) {
    std::vector<char> encoded(sodium_base64_ENCODED_LEN(data.size(), sodium_base64_VARIANT_ORIGINAL));
    sodium_bin2base64(encoded.data(), encoded.size(), data.data(), data.size(), sodium_base64_VARIANT_ORIGINAL);
    return std::string(encoded.data());
}

/**
 * @brief Converte uma string em Base64 para um vetor de bytes.
 * @param b64 String codificada em Base64.
 * @return Vetor de bytes decodificado.
 * @throws std::runtime_error Se a string Base64 for inválida.
 */
std::vector<unsigned char> from_base64(const std::string& b64) {
    size_t bin_len;
    std::vector<unsigned char> bin(b64.size());
    if (sodium_base642bin(bin.data(), bin.size(), b64.c_str(), b64.size(), nullptr, &bin_len, nullptr, sodium_base64_VARIANT_ORIGINAL) != 0) 
        throw std::runtime_error("Base64 inválida");
    bin.resize(bin_len);
    return bin;
}

/**
 * @brief Gera uma chave criptográfica a partir de uma senha e um salt usando Argon2.
 * @param password Senha em texto puro.
 * @param salt Vetor de bytes usado como salt.
 * @return Vetor de bytes contendo a chave derivada.
 * @throws std::runtime_error Se a derivação da chave falhar.
 */
std::vector<unsigned char> generate_key(const std::string& password, const std::vector<unsigned char>& salt) {
    std::vector<unsigned char> key(crypto_secretbox_KEYBYTES);
    if(crypto_pwhash(key.data(), key.size(), password.c_str(), password.size(), salt.data(),
                     crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                     crypto_pwhash_ALG_DEFAULT) != 0)
        throw std::runtime_error("Falha no hash da senha");
    return key;
}

/**
 * @brief Criptografa uma mensagem usando uma chave e gera um nonce aleatório.
 * @param key Chave criptográfica.
 * @param message Mensagem em texto puro a ser criptografada.
 * @param nonce_out Vetor de bytes que receberá o nonce gerado.
 * @return Vetor de bytes contendo o texto criptografado (ciphertext).
 */
std::vector<unsigned char> encrypt(const std::vector<unsigned char>& key, const std::string& message, std::vector<unsigned char>& nonce_out) {
    std::vector<unsigned char> ciphertext(crypto_secretbox_MACBYTES + message.size());
    nonce_out.resize(crypto_secretbox_NONCEBYTES);
    randombytes_buf(nonce_out.data(), nonce_out.size());
    crypto_secretbox_easy(ciphertext.data(), reinterpret_cast<const unsigned char*>(message.data()), message.size(), nonce_out.data(), key.data());
    return ciphertext;
}

/**
 * @brief Descriptografa um texto criptografado usando a chave e o nonce.
 * @param key Chave criptográfica.
 * @param ciphertext Vetor de bytes contendo o texto criptografado.
 * @param nonce Vetor de bytes contendo o nonce utilizado na criptografia.
 * @return String com o texto descriptografado.
 * @throws std::runtime_error Se a descriptografia falhar.
 */
std::string decrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& nonce) {
    std::vector<unsigned char> decrypted(ciphertext.size() - crypto_secretbox_MACBYTES);
    if(crypto_secretbox_open_easy(decrypted.data(), ciphertext.data(), ciphertext.size(), nonce.data(), key.data()) != 0)
        throw std::runtime_error("Falha ao descriptografar");
    return std::string(decrypted.begin(), decrypted.end());
}
