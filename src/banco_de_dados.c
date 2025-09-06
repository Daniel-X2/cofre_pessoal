#include <stdio.h>
#include <sqlite3.h>
sqlite3 * db;
char *errMsg=0;
int rc;


int init_sql ()
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
    
   // deletar_dados(1,"usuarios");

    

    //sqlite3_close(db);
    //vou jogar os ponteiros pra onde vou inserir os dados 
    // pra onde eu vou deletar os dados 
    //pra onde eu vou renomear algum dados 
    return 0;

}

int inserir_dados(const char nome_item[],const char nome_usuario[],const char senha[])
{
    
    char SQL_contatedado[100];
    
    
    sprintf(SQL_contatedado,"INSERT INTO usuarios(nome_item,nome_usuario,senha) VALUES ('%s','%s','%s');",nome_item,nome_usuario,senha);
    const char * sql=SQL_contatedado;
    
    rc= sqlite3_exec(db,sql,0,0,&errMsg);

    if (sql!= SQLITE_OK)
    {
        fprintf(stderr,"erro ao adicionar ao banco : %s",errMsg);
        sqlite3_free(errMsg);
        
        return 1;
    }
    
    return 0;
}

int deletar_dados(int tabela,int id)
{

    char SQL_concatenado[100];
    if(tabela==0)
    {
        sprintf(SQL_concatenado,"DELETE FROM usuarios WHERE id = '%i';",id);
        
    }
    else
    {
        sprintf(SQL_concatenado,"DELETE FROM anotacoes WHERE id = '%i';",id);
    }
    const char* sql=SQL_concatenado;
    rc=sqlite3_exec(db,sql,0,0,&errMsg);
    if (sql!=SQLITE_OK)
    {
        fprintf(stderr,"erro ao deletar no banco de dados: %s",errMsg);
        sqlite3_free(errMsg);
        return 1;
    }

    return 1;
    
}
int update_dados(int tabela,int id,char nome_item[],char nome_usuario[],char senha[],char anotacoes[])
{
     char SQL_concatenado[100];
    if(tabela==0)
    {
        sprintf(SQL_concatenado,"UPDATE anotacoes SET idade = 26 WHERE id = '%i';",id);
        
    }
    else
    {
        sprintf(SQL_concatenado,"UPDATE usuarios SET idade = 26 WHERE id = '%i';",id);
    }
    const char* sql=SQL_concatenado;
    rc=sqlite3_exec(db,sql,0,0,&errMsg);
    if (sql!=SQLITE_OK)
    {
        fprintf(stderr,"erro ao dar update no banco de dados: %s",errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
}