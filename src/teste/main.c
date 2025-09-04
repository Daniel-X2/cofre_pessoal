#include <stdio.h>
#include <sqlite3.h>
sqlite3 * db;
char *errMsg=0;
int rc;

int inserir_dados();
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
    inserir_dados();

    sqlite3_close(db);
    //vou jogar os ponteiros pra onde vou inserir os dados 
    // pra onde eu vou deletar os dados 
    //pra onde eu vou renomear algum dados 
    return 0;

}

int inserir_dados()
{
    char teste[100];
    char n1[]="ola";
    char n2[]="teste1";
    char n3[]="senha";
    sprintf(teste,"INSERT INTO usuarios(nome_item,nome_usuario,senha) VALUES ('%s','%s','%s')",n1,n2,n3 );
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
