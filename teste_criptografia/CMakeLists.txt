cmake_minimum_required(VERSION 3.10)
project(teste_criptografia C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

# GTK3
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Sodium
pkg_check_modules(SODIUM REQUIRED libsodium)

# Cria o executável
add_executable(meu_app main.c)

# Includes
target_include_directories(meu_app PRIVATE ${GTK3_INCLUDE_DIRS} ${SODIUM_INCLUDE_DIRS})

# Flags extras do compilador
target_compile_options(meu_app PRIVATE ${GTK3_CFLAGS_OTHER} ${SODIUM_CFLAGS_OTHER})

# Linka as libs
target_link_libraries(meu_app PRIVATE ${GTK3_LIBRARIES} ${SODIUM_LIBRARIES})



set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
