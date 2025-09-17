# cofre _pessoal
Descrição

[Um aplicativo de desktop seguro para gerenciamento de notas, que utiliza criptografia para proteger os dados do usuário.]

Este projeto é uma aplicação de desktop desenvolvida em C, que combina uma interface de usuário elegante e nativa com o GTK+ 3, um sistema de banco de dados leve e eficiente com o SQLite, e um forte sistema de criptografia com a biblioteca libsodium.

Tecnologias Usadas

    Linguagem de Programação: C/C++

    Interface Gráfica: GTK+ 3

    Banco de Dados: SQLite

    Criptografia: libsodium
    
    Sistema de Build: CMake
Requisitos

Para compilar e executar o projeto, você precisará ter as seguintes bibliotecas instaladas no seu sistema:
    
    CMake: Para gerenciar o processo de build.
    
    GTK+ 3: libgtk-3-dev

    SQLite3: libsqlite3-dev

    libsodium: libsodium-dev

Instalação no Debian/Ubuntu

Bash

sudo apt-get install libgtk-3-dev libsqlite3-dev libsodium-dev cmake

Instalação no Fedora

Bash

sudo dnf install gtk3-devel sqlite-devel libsodium-devel cmake

Instalação no Arch Linux

Bash

sudo pacman -S gtk3 sqlite libsodium cmake

Compilação

O projeto usa o CMake para gerenciar a compilação. Siga os passos abaixo:

    Crie um diretório de build e entre nele:
    Bash

mkdir build
cd build

Execute o CMake para configurar o projeto. O .. indica que o arquivo CMakeLists.txt está no diretório pai.
Bash

cmake ..

Compile o projeto:
Bash

    make

Como Executar

Após a compilação, o executável estará no diretório build. Você pode executá-lo com o comando:
Bash

./build/[NOME_DO_EXECUTAVEL]

Exemplo:

o nome do executável esta como meu_app no  CMakeLists.txt:
Bash

./build/meu_app

Contribuição

Contribuições são bem-vindas! Se você quiser contribuir, por favor, abra uma issue para discutir as mudanças propostas ou crie um pull request com suas alterações.

Licença

Este projeto está licenciado sob a Licença [MIT]. Veja o arquivo [NOME DO ARQUIVO DA LICENÇA] para mais detalhes.

Autor

[Daniel-X2]

    GitHub: [https://github.com/Daniel-X2]
    Linkedln [https://www.linkedin.com/in/daniel-da-silva-32814636b/]
    
