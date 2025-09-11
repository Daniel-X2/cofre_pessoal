#include <sodium.h>
#include "../include/banco_de_dados.h"
#include "../include/crypto.h"
#include "../include/init.h"
#include <strings.h>
#include <iostream>
#include <sodium.h>
#include <string.h>
    

#include <vector>


int init_cripto(const char *senha,const char *messagem,int verificar_update,int id) {
    if(sodium_init() < 0) 
    {
        
        return 1;
    }
    //init_sql();
    
    const std::string SENHA = senha;
    const std::string MESSAGE = messagem;
    // Banco
    //if (init_sql() != 0) 
    //{
    //return 1;
   // }
    // Salt + key
    std::vector<unsigned char> salt(crypto_pwhash_SALTBYTES);
    randombytes_buf(salt.data(), salt.size());
    std::vector<unsigned char> key = generate_key(SENHA, salt);

    // Criptografar
    std::vector<unsigned char> nonce;
    std::vector<unsigned char> cipher = encrypt(key, MESSAGE, nonce);

    // Converter para Base64 e salvar
    if (verificar_update==0)
    {
        if (inserir_dados(to_base64(salt), to_base64(nonce), to_base64(cipher),id,0) != 0) 
        {
            return 1;
        }   
    }
    else{
        if (inserir_dados(to_base64(salt), to_base64(nonce), to_base64(cipher),id,1) != 0) 
        {
            return 1;
        }   
    }
    
    // Recuperar e descriptografar
   return 1;
}



// Sua função de descriptografia
char* descriptografar(const char* senha, int id) {
    // Inicializa SQL
    //if (init_sql() != 0) {
      //  std::cerr << "Falha ao inicializar o banco de dados." << std::endl;
        //return nullptr;
    //}

    // Pega usuário do banco
    Usuario u = buscar_usuario(id);

    // Converte dados do usuário para bytes
    std::vector<unsigned char> salt_bytes = from_base64(u.salt);
    std::vector<unsigned char> nonce_bytes = from_base64(u.nonce);
    std::vector<unsigned char> cipher_bytes = from_base64(u.texto_cryptado);

    // Gera chave a partir da senha
    std::vector<unsigned char> key_from_db = generate_key(senha, salt_bytes);

    std::string decrypted;
    try {
        decrypted = decrypt(key_from_db, cipher_bytes, nonce_bytes);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro na descriptografia: " << e.what() << std::endl;
        return nullptr;
    }

    // Aloca buffer para C
    char* buffer = new char[decrypted.size() + 1]; // +1 para o '\0'
    strcpy(buffer, decrypted.c_str());
    //printf("ola mund %s\n",buffer);
    return buffer; // ⚠️ quem chamar deve liberar com delete[]
}


int verificar_quantidade()
{
    
    int quantidade=retorna_quantidade();
   
    return quantidade;
}
void fechar_banco_init()
{
    fechar_banco();
}
void iniciar_banco()
{
    init_sql();
}