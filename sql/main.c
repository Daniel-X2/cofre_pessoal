#include <stdio.h>
#include <sqlite3.h>
sqlite3 * db;
char *errMsg=0;
int rc;

int inserir_dados(char nome_item[],char nome_usuario[],char senha[]);
int deletar_dados();
int main ()
{
   

    rc= sqlite3_open("meu_banco.db",&db);

    if(rc) {
        fprintf(stderr,"erro ao abrir banco: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;

    }
    const char *sql ="CREATE TABLE IF NOT EXISTS  anotacoes(id INTEGER PRIMARY KEY ,nome_item VARCHAR(30),descricao TEXT);";
    rc = sqlite3_exec(db,sql,0,0,&errMsg);

    
    
    if(rc!= SQLITE_OK)
    {
        fprintf(stderr,"erro SQL: %s\n",errMsg);
        sqlite3_free(errMsg);
    }

    
    sql="CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY ,nome_item VARCHAR(30),nome_usuario VARCHAR(50),senha TEXT);";
    rc = sqlite3_exec(db,sql,0,0,&errMsg);

    if(rc!= SQLITE_OK)
    {
        fprintf(stderr,"erro SQL: %s\n",errMsg);
        sqlite3_free(errMsg);
    }
    

    sqlite3_close(db);
    //vou jogar os ponteiros pra onde vou inserir os dados 
    // pra onde eu vou deletar os dados 
    //pra onde eu vou renomear algum dados 
    return 0;

}

int inserir_dados(char nome_item[],char nome_usuario[],char senha[])
{
    char teste[100];
    
    sprintf(teste,"INSERT INTO usuarios(nome_item,nome_usuario,senha) VALUES ('%s','%s','%s')",nome_item,nome_usuario,senha);
    const char * sql=teste;
    
    rc= sqlite3_exec(db,sql,0,0,&errMsg);

    if (sql!= SQLITE_OK)
    {
        fprintf(stderr,"erro ao adicionar ao banco : %s",errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}

int deletar_dados()
{

    const char* sql="";
    return 1;
    
}