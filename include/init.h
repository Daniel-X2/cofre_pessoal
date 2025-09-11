
#ifdef __cplusplus
extern "C" {
#endif
int verificar_quantidade();
int init_cripto(const char *senha, const char *messagem,int verificar_update,int id);
char* descriptografar(const char *senha,int id);
void fechar_banco_init();
void iniciar_banco();
#ifdef __cplusplus
}
#endif
