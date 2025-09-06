#ifndef CRIPTOGRAFAR

int init_criptografia(char *SENHA,const char messagem[]);
int criptografar(const char *senha, const unsigned char *mensagem, unsigned int MESSAGE_len, unsigned char *ciphertext, unsigned char *nonce, unsigned char *key);
int descriptografar(const unsigned char *ciphertext, unsigned int CIPHETEXT_LEN, const unsigned char *nonce, const unsigned char *key, unsigned char *mensagem_desc);
#endif