#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS
void fechar_banco();
int inserir_dados(char salt[],char nonce[],char texto_cryptado[]);
int deletar_dados(int tabela,int id);
int update_dados(int tabela,int id,char nome_item[],char nome_usuario[],char senha[],char anotacoes[]);
int init_sql ();

#endif