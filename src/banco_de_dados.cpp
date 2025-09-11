#include "../include/banco_de_dados.h"
#include <iostream>
#include <sodium.h>

// Definição das variáveis globais
sqlite3* db;
char* errMsg = nullptr;
int rc;

int init_sql() {
    
    rc = sqlite3_open("/home/daniel/Área de trabalho/cofre_pessoal/meu_banco.db", &db);
    
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

int inserir_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado, int id)
{
    
    char SQL_contatedado[2024];
    sprintf(SQL_contatedado,
            "INSERT INTO usuarios(salt,nonce,texto_cryptado) VALUES ('%s','%s','%s');",
            salt.c_str(), nonce.c_str(), texto_cryptado.c_str());
    int n1 = sqlite3_exec(db, SQL_contatedado, nullptr, nullptr, &errMsg);

    if (n1 != SQLITE_OK) {
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
    printf("ola aaqui no sql de fechar\n");
    sqlite3_close(db);
}
int retorna_quantidade()
{
    //init_sql();
    const char* SQL = "SELECT COUNT(*) FROM usuarios;";
sqlite3_stmt* stmt;
int rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, nullptr);



if (rc != SQLITE_OK) {
    printf("Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
    return -1;
}

rc = sqlite3_step(stmt);
if (rc == SQLITE_ROW) {
    
}
int total = sqlite3_column_int(stmt, 0);  // pega o COUNT(*)
    return total;
sqlite3_finalize(stmt);

}
int atualizar_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado,int id)
{
   

    
    char SQL_contatedado[1024];
    sprintf(SQL_contatedado,
            "UPDATE usuarios SET  salt = %s nonce =%s texto_cryptado= %s WHERE id = '%i';",
            salt.c_str(), nonce.c_str(), texto_cryptado.c_str(),id);

    rc = sqlite3_exec(db, SQL_contatedado, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao adicionar ao banco: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}