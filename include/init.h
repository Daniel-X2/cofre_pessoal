#ifdef __cplusplus
extern "C" {
#endif

int init_cripto(const char *senha, const char *messagem);
int descriptografar(const char *senha,int id);

#ifdef __cplusplus
}
#endif
