
#ifdef __cplusplus
extern "C" {
#endif
int retornar_quantidade_init();
int *verificar_id();
int init_cripto(const char *senha, const char *messagem,int verificar_update,int id);
char* descriptografar(const char *senha,int id);
void fechar_banco_init();
void iniciar_banco();
void delete_init(int id);
void destruir(void* ptr);
#ifdef __cplusplus
}
#endif
