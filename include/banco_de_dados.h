#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS

int inserir_dados(const char nome_item[],const char nome_usuario[],const char senha[]);
int deletar_dados(int tabela,int id);
int update_dados(int tabela,int id,char nome_item[],char nome_usuario[],char senha[],char anotacoes[]);
int init_sql ();

#endif