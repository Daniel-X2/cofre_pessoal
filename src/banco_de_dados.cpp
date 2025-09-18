/**
 * @file banco_de_dados.cpp
 * @brief Implementação das funções de manipulação do banco de dados SQLite para o cofre pessoal.
 */

#include "../include/banco_de_dados.h"
#include <iostream>
#include <sodium.h>
#include <string.h>

// Variáveis globais para conexão e controle do banco de dados
sqlite3* db;
char* errMsg = nullptr;
int rc;

/**
 * @brief Inicializa o banco de dados SQLite e cria a tabela de usuários, se não existir.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int init_sql() {
    
    rc = sqlite3_open("meu_banco.db", &db);
    
    if (rc!= SQLITE_OK) {
        std::cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << std::endl;
        
        sqlite3_close(db);
        return 1;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY, nonce TEXT, salt TEXT, texto_cryptado TEXT);";
    
    int n1 = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (n1 != SQLITE_OK) {
        std::cerr << "Erro SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }
    
    return 0;
}

/**
 * @brief Insere ou atualiza dados criptografados de um usuário na tabela.
 * @param salt Sal gerado para derivação de chave.
 * @param nonce Nonce utilizado na criptografia.
 * @param texto_cryptado Texto criptografado (senha ou dados).
 * @param id Identificador do usuário (usado para update).
 * @param update Se 1, realiza update; se 0, realiza insert.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int inserir_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado, int id, int update)
{
    if (update == 1) {
        return atualizar_dados(salt, nonce, texto_cryptado, id);
    }

    const char* sql = "INSERT INTO usuarios(salt, nonce, texto_cryptado) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar insert: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    sqlite3_bind_text(stmt, 1, salt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, nonce.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, texto_cryptado.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir dados: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

/**
 * @brief Busca os dados criptografados de um usuário pelo id.
 * @param id Identificador do usuário.
 * @return Struct Usuario preenchida com salt, nonce e texto_cryptado.
 */
Usuario buscar_usuario(int id) {
    Usuario u;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT salt, nonce, texto_cryptado FROM usuarios WHERE id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar select: " << sqlite3_errmsg(db) << std::endl;
        return u;
    }

    sqlite3_bind_int(stmt, 1, id);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        u.salt = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        u.nonce = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        u.texto_cryptado = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    } else {
        std::cerr << "Nenhum usuário encontrado para id " << id << std::endl;
    }

    sqlite3_finalize(stmt);
    return u;
}

/**
 * @brief Fecha a conexão com o banco de dados SQLite.
 */
void fechar_banco() {
    //printf("ola aaqui no sql de fechar\n");
    sqlite3_close(db);
}

/**
 * @brief Retorna a quantidade de usuários cadastrados na tabela.
 * @return Número de usuários cadastrados, ou -1 em caso de erro.
 */
int *retorna_quantidade()
{
    //init_sql();
    const char* SQL = "SELECT id FROM usuarios ORDER BY id;";
   
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, nullptr);



    if (rc != SQLITE_OK) {
        printf("Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        //return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
    
    }
     // pega o COUNT(*) 
    int pegador_de_id = sqlite3_column_int(stmt, 0);
    int id[2000];
    int contador=0;
    id[contador]=pegador_de_id;
    contador++;
    while((rc=sqlite3_step(stmt))== SQLITE_ROW)
    {

        pegador_de_id = sqlite3_column_int(stmt, 0);
        id[contador]=pegador_de_id;
        contador++;
        //printf("ola, %i\n",contador);
    }
    
    
    
    sqlite3_finalize(stmt);
    
    int *pont_id=id;
    return pont_id;


}

/**
 * @brief Atualiza os dados criptografados de um usuário existente.
 * @param salt Novo salt.
 * @param nonce Novo nonce.
 * @param texto_cryptado Novo texto criptografado.
 * @param id Identificador do usuário a ser atualizado.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int atualizar_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado, int id)
{
    const char* sql = "UPDATE usuarios SET salt = ?, nonce = ?, texto_cryptado = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar update: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    sqlite3_bind_text(stmt, 1, salt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, nonce.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, texto_cryptado.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao atualizar dados: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void deletar(int id)
{
    char SQL_contatedado[1024];
    sprintf(SQL_contatedado,
            "DELETE FROM usuarios WHERE id = %i ;",id);

    rc = sqlite3_exec(db, SQL_contatedado, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao deletar ao banco: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    
}