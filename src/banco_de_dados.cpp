/**
 * @file banco_de_dados.cpp
 * @brief Implementação das funções de manipulação do banco de dados SQLite para o cofre pessoal.
 */
#include "../include/banco_de_dados.h"


// Variáveis globais para conexão e controle do banco de dados
sqlite3* db;
char* errMsg = nullptr;
int rc;

/**
 * @brief Inicializa o banco de dados SQLite e cria a tabela de usuários, se não existir.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int init_sql() {
    if (db != NULL) {  // ⬅️ Evitar abrir banco duas vezes
        return 0;      // Já está aberto
    }
    rc = sqlite3_open("meu_banco.db", &db);
    
    if (rc!= SQLITE_OK) {
        std::cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << std::endl;
        
        sqlite3_close(db);
        return 1;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY, nonce TEXT, salt TEXT, texto_cryptado TEXT);";
    
    int exec_sqlite = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (exec_sqlite != SQLITE_OK) {
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
    
    sqlite3_close(db);
}

/**
 * @brief Retorna a quantidade de usuários cadastrados na tabela.
 * @return Número de usuários cadastrados, ou -1 em caso de erro.
 */

int retornar_quantidade()
{
     const char* SQL = "SELECT COUNT (*) FROM usuarios;";
   
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, nullptr);



    if (rc != SQLITE_OK) {
        printf("Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
    
    }
     int quantidade = sqlite3_column_int(stmt, 0);
    return quantidade;
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






int* retorna_id(int* total_ids) {
    if (!db) {  // Add database check
        printf("Erro: Conexão com banco de dados inválida\n");
        return NULL;
    }

    const char* SQL = "SELECT id FROM usuarios ORDER BY id;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        printf("Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    int capacity = 100; // capacidade inicial
    int* ids =(int*) malloc(sizeof(int) * capacity);
    if (!ids) {
        printf("Erro de alocação de memória\n");
        sqlite3_finalize(stmt);
        return NULL;
    }

    int count = 0;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        if (count >= capacity) {
            capacity *= 2;
            int* new_ids = (int*)realloc(ids, sizeof(int) * capacity);
            if (!new_ids) {
                printf("Erro ao realocar memória\n");
                free(ids);
                sqlite3_finalize(stmt);
                return NULL;
            }
            ids = new_ids;
        }

        ids[count++] = sqlite3_column_int(stmt, 0);
    }

    // Add error handling for sqlite3_step
    if (rc != SQLITE_DONE) {
        printf("Erro ao executar query: %s\n", sqlite3_errmsg(db));
        free(ids);
        sqlite3_finalize(stmt);
        return NULL;
    }

    sqlite3_finalize(stmt);
    
    return ids;
}