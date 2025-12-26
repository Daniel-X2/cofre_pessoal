cmake_minimum_required(VERSION 3.10)


project(cofre_pessoal LANGUAGES C CXX)

# Padrão das linguagens
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)          
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar pacotes
find_package(PkgConfig REQUIRED)

# GTK3
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Sodium
pkg_check_modules(SODIUM REQUIRED libsodium)

# SQLite3
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

# Cria o executável
add_executable(meu_app src/main.c src/crypto.cpp src/banco_de_dados.cpp src/diretorio.c src/init.cpp src/janela.c src/login.c) 
# aqui você pode adicionar arquivos C ou CPP

# Includes
target_include_directories(meu_app PRIVATE 
    ${GTK3_INCLUDE_DIRS} 
    ${SODIUM_INCLUDE_DIRS} 
    ${SQLITE3_INCLUDE_DIRS}
)

# Flags extras do compilador
target_compile_options(meu_app PRIVATE 
    ${GTK3_CFLAGS_OTHER} 
    ${SODIUM_CFLAGS_OTHER} 
    ${SQLITE3_CFLAGS_OTHER}
)

# Linka as libs
target_link_libraries(meu_app PRIVATE 
    ${GTK3_LIBRARIES} 
    ${SODIUM_LIBRARIES} 
    ${SQLITE3_LIBRARIES}
)

# Gera compile_commands.json (bom para ferramentas como clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


