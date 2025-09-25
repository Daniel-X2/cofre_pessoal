
/**
 * @file init.cpp
 * @brief Funções de inicialização, criptografia, descriptografia e integração entre C e C++ para o cofre pessoal.
 */
#include "../include/init.h"


/**
 * @brief Inicializa a criptografia, gera salt, chave, nonce e cifra a mensagem, salvando no banco de dados.
 * @param senha Senha em texto puro para derivação da chave.
 * @param messagem Mensagem a ser criptografada.
 * @param verificar_update Se 0, insere novo registro; se 1, atualiza registro existente.
 * @param id Identificador do usuário.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int init_cripto(const char *senha, const char *messagem, int verificar_update, int id) {
    if(sodium_init() < 0) 
    {
        
        return 1;
    }
    
    
    const std::string SENHA = senha;
    const std::string MESSAGE = messagem;
    
    std::vector<unsigned char> salt(crypto_pwhash_SALTBYTES);
    randombytes_buf(salt.data(), salt.size());
    std::vector<unsigned char> key = generate_key(SENHA, salt);

    // Criptografar
    std::vector<unsigned char> nonce;
    std::vector<unsigned char> cipher = encrypt(key, MESSAGE, nonce);

    // Converter para Base64 e salvar
    if (verificar_update==0)
    {
        if (inserir_dados(to_base64(salt), to_base64(nonce), to_base64(cipher),id,0) != 0) 
        {
            return 0;
        }   
    }
    else{
        if (inserir_dados(to_base64(salt), to_base64(nonce), to_base64(cipher),id,1) != 0) 
        {
            return 0;
        }   
    }
    
    // Recuperar e descriptografar
   return 0;
}


// Sua função de descriptografia
char * descriptografar(const char* senha, int id,int verificar) {
    
    // Pega usuário do banco
    Usuario u = buscar_usuario(id);

    // Converte dados do usuário para bytes
    std::vector<unsigned char> salt_bytes = from_base64(u.salt);
    std::vector<unsigned char> nonce_bytes = from_base64(u.nonce);
    std::vector<unsigned char> cipher_bytes = from_base64(u.texto_cryptado);

    // Gera chave a partir da senha
    std::vector<unsigned char> key_from_db = generate_key(senha, salt_bytes);

    std::string decrypted;
    try {
        decrypted = decrypt(key_from_db, cipher_bytes, nonce_bytes);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro na descriptografia: " << e.what() << std::endl;
        return nullptr;
    }

    // Aloca buffer para C
    char* buffer = new char[decrypted.size() + 1]; 
    strcpy(buffer, decrypted.c_str());
    
    if(verificar==0)
    {
        return buffer; // ⚠️ quem chamar deve liberar com delete[]
    }
    else
    {
        char*funcionou="0";
        return funcionou;
    }
}

int *verificar_id()
{
    int total;
    int* ids = retorna_id(&total);
    if (ids == NULL ) {
        printf("Nenhum usuário encontrado ou erro ao recuperar IDs.\n");
        return NULL;  
    }
    
    return ids;
}

void fechar_banco_init()
{
    // essa funçao serve como uma ponte entre arquivos c e c++
    fechar_banco();
}
void iniciar_banco()
{
    // essa funçao serve como uma ponte entre arquivos c e c++
    init_sql();
}
void delete_init(int id)
{
    deletar(id);
}
int retornar_quantidade_init()
{
    int quantidade=retornar_quantidade();
    return quantidade;
}
void destruir(void* ptr)
{
    delete[] static_cast<char*>(ptr);
}
