#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H



#include <iostream>
#include <sodium.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h> 
#include "../include/diretorio.h"



// Variáveis globais do DB
extern sqlite3* db;
extern char* errMsg;
extern int rc;

// Funções
int retornar_quantidade();
int* retorna_id(int* total_ids);
int atualizar_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado,int id);
int init_sql();

void fechar_banco();
void deletar(int id);
int inserir_dados(const std::string& salt, const std::string& nonce, const std::string& texto_cryptado,int id,int update);
struct Usuario {
    std::string salt;
    std::string nonce;
    std::string texto_cryptado;
};
Usuario buscar_usuario(int id);
#endif// BANCO_DE_DADOS_H
