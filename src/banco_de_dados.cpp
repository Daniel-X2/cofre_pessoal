#include "../include/banco_de_dados.h"
#include <iostream>
#include <sodium.h>

// Definição das variáveis globais
sqlite3* db;
char* errMsg = nullptr;
int rc;

int init_sql() {
    rc = sqlite3_open("meu_banco.db", &db);
    if (rc) {
        std::cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY, nonce TEXT, salt TEXT, texto_cryptado TEXT);";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}

int inserir_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado)
{
    char SQL_contatedado[1024];
    sprintf(SQL_contatedado,
            "INSERT INTO usuarios(salt,nonce,texto_cryptado) VALUES ('%s','%s','%s');",
            salt.c_str(), nonce.c_str(), texto_cryptado.c_str());

    rc = sqlite3_exec(db, SQL_contatedado, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao adicionar ao banco: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}

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

void fechar_banco() {
    sqlite3_close(db);
}
