#include <stdio.h>
#include <sodium.h>
#include <stdlib.h>
#include <string.h>
/* Versão do formato */
#define SENHA "Correct Horse Battery Staple"
#define MESSAGE ((const unsigned char *) "test")
#define MESSAGE_len (strlen(MESSAGE)+1)
#define KEY_LEN crypto_box_SEEDBYTES
#define CIPHETEXT_LEN (crypto_secretbox_MACBYTES+MESSAGE_len)

int main()
{
    
    if (sodium_init()<0)
    {
        
        return 1;
    }    
    //char senha []="ola mano";
   // int KEY_LEN=crypto_box_SEEDBYTES;

    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char key[KEY_LEN];

    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    unsigned char ciphertext[CIPHETEXT_LEN];



    randombytes_buf(salt,sizeof salt);
    randombytes_buf(nonce,sizeof nonce);

    
    if(crypto_pwhash(key,sizeof key,SENHA,strlen(SENHA),salt,crypto_pwhash_OPSLIMIT_INTERACTIVE,crypto_pwhash_MEMLIMIT_INTERACTIVE,crypto_pwhash_ALG_DEFAULT)!=0)
        {
            
        }
    crypto_secretbox_easy(ciphertext,MESSAGE,MESSAGE_len,nonce,key);

    unsigned char decript[MESSAGE_len];
    
    if(crypto_secretbox_open_easy(decript,ciphertext,CIPHETEXT_LEN,nonce,key)!=0)
        {

        }
    
    return 0;
}

