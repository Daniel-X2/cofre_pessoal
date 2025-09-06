#include <stdio.h>
#include <sodium.h>
#include <stdlib.h>
#include <string.h>
#include "../include/banco_de_dados.h"
#define KEY_LEN crypto_secretbox_KEYBYTES

// Função de criptografia
int criptografar(const char *senha,
                 const unsigned char *mensagem, unsigned int MESSAGE_len,
                 unsigned char *ciphertext,
                 unsigned char *nonce,
                 unsigned char *salt)
{
    if (sodium_init() < 0)
    {
        return 1;
    }

    // Gera salt e nonce aleatórios
    randombytes_buf(salt, crypto_pwhash_SALTBYTES);
    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);

    unsigned char key[KEY_LEN];

    // Deriva a chave
    if (crypto_pwhash(key, KEY_LEN,
                      senha, strlen(senha),
                      salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE,
                      crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0)
    {
        return 1;
    }

    // Criptografa
    if (crypto_secretbox_easy(ciphertext, mensagem, MESSAGE_len, nonce, key) != 0)
    {
        return 1;
    }

    return 0;
}

// Função de descriptografia
int descriptografar(const char *senha,
                    const unsigned char *ciphertext, unsigned int CIPHERTEXT_LEN,
                    const unsigned char *nonce,
                    const unsigned char *salt,
                    unsigned char *mensagem_desc)
{
    unsigned char key[KEY_LEN];

    // Recria a chave
    if (crypto_pwhash(key, KEY_LEN,
                      senha, strlen(senha),
                      salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE,
                      crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0)
    {
        return 1;
    }

    // Descriptografa
    if (crypto_secretbox_open_easy(mensagem_desc, ciphertext, CIPHERTEXT_LEN, nonce, key) != 0)
    {
        return 1;
    }

    return 0;
}

// Print em hexadecimal
void print_hex(const unsigned char *data, unsigned int len)
{
    
   len = sizeof(data) - 1; // -1 porque não conta o '\0'

    char teste[len + 1]; // espaço pra string + '\0'

    for (unsigned int i = 0; i < len; i++) {
        teste[i] = data[i]; // copia cada caractere
    }

    teste[len] = '\0'; // finaliza a string
    inserir_dados(teste,teste,teste);
    
}

// Função principal
int init_criptografia(const char *SENHA, const char *mensagem)
{
    const char *input_message = mensagem;
    unsigned int MESSAGE_LEN = strlen(input_message);
    unsigned int CIPHERTEXT_LEN = crypto_secretbox_MACBYTES + MESSAGE_LEN;

    // Variáveis que vão guardar os dados
    unsigned char ciphertext[CIPHERTEXT_LEN];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char decrypted[MESSAGE_LEN + 1]; // +1 pro \0

    // Criptografa
    if (criptografar(SENHA, (const unsigned char *)input_message, MESSAGE_LEN,
                     ciphertext, nonce, salt) != 0)
    {
        printf("Erro ao criptografar!\n");
        return 1;
    }

    // --- AGORA ESTÃO GUARDADOS NAS VARIÁVEIS ---
    // salt[] contém o salt
    // nonce[] contém o nonce
    // ciphertext[] contém a mensagem criptografada

    printf("Ciphertext (hex):\n");
    print_hex(ciphertext, CIPHERTEXT_LEN);

    printf("Nonce (hex):\n");
    print_hex(nonce, crypto_secretbox_NONCEBYTES);

    printf("Salt (hex):\n");
    print_hex(salt, crypto_pwhash_SALTBYTES);

    // Testando descriptografia
    if (descriptografar(SENHA, ciphertext, CIPHERTEXT_LEN, nonce, salt, decrypted) != 0)
    {
        printf("Erro ao descriptografar!\n");
        return 1;
    }

    decrypted[MESSAGE_LEN] = '\0';
    printf("Mensagem descriptografada: %s\n", decrypted);

    return 0;
}
