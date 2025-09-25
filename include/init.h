
#ifdef __cplusplus
#include <iostream>
#include <vector>
#include "../include/crypto.h"
#include "../include/banco_de_dados.h"
extern "C" {
#endif
#include <sodium.h>
#include <strings.h>
#include <sodium.h>
#include <string.h>







int retornar_quantidade_init();
int *verificar_id();
int init_cripto(const char *senha, const char *messagem,int verificar_update,int id);
char * descriptografar(const char *senha,int id,int verificar);
void fechar_banco_init();
void iniciar_banco();
void delete_init(int id);
void destruir(void* ptr);
#ifdef __cplusplus

}
#endif
