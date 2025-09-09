#include <sodium.h>
#include "../include/banco_de_dados.h"
#include "../include/crypto.h"
#include "../include/init.h"

#include <iostream>
#include <sodium.h>

    
    
int init_cripto(const char *senha,const char *messagem) {
    if(sodium_init() < 0) 
    {
        return 1;
    }

    
    const std::string SENHA = senha;
    const std::string MESSAGE = messagem;
    // Banco
    if (init_sql() != 0) 
    {
    return 1;
    }
    // Salt + key
    std::vector<unsigned char> salt(crypto_pwhash_SALTBYTES);
    randombytes_buf(salt.data(), salt.size());
    std::vector<unsigned char> key = generate_key(SENHA, salt);

    // Criptografar
    std::vector<unsigned char> nonce;
    std::vector<unsigned char> cipher = encrypt(key, MESSAGE, nonce);

    // Converter para Base64 e salvar
    if (inserir_dados(to_base64(salt), to_base64(nonce), to_base64(cipher)) != 0) 
    {
        return 1;
    }
    // Recuperar e descriptografar
   return 1;
}

int descriptografar(const char *senha,int id)
{
    if (init_sql() != 0) 
    {
    return 1;
    }
    const std::string SENHA = senha;
    Usuario u = buscar_usuario(id);
    std::vector<unsigned char> salt_bytes = from_base64(u.salt);
    std::vector<unsigned char> nonce_bytes = from_base64(u.nonce);
    std::vector<unsigned char> cipher_bytes = from_base64(u.texto_cryptado);
    std::vector<unsigned char> key_from_db = generate_key(SENHA, salt_bytes);

    try {
        std::string decrypted = decrypt(key_from_db, cipher_bytes, nonce_bytes);
        std::cout << "Mensagem descriptografada: " << decrypted << std::endl;
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
