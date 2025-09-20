#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include <string>
#include <sqlite3.h>

struct Usuario {
    std::string salt;
    std::string nonce;
    std::string texto_cryptado;
};

// Variáveis globais do DB
extern sqlite3* db;
extern char* errMsg;
extern int rc;

// Funções
int retornar_quantidade();
int *retorna_id();
int atualizar_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado,int id);
int init_sql();
int inserir_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado,int id,int update);
Usuario buscar_usuario(int id);
void fechar_banco();
void deletar(int id);
#endif // BANCO_DE_DADOS_H
