

````md
### Cofre Pessoal

### 📌 Descrição
Um aplicativo de desktop seguro para gerenciamento de notas, que utiliza criptografia para proteger os dados do usuário.

Este projeto é uma aplicação de desktop desenvolvida em **C**, que combina:  
- Uma interface de usuário elegante e nativa com **GTK+ 3**;  
- Um sistema de banco de dados leve e eficiente com **SQLite**;  
- Um forte sistema de criptografia com a biblioteca **libsodium**.  

---

### 🚀 Tecnologias Usadas
- **Linguagem de Programação:** C/C++  
- **Interface Gráfica:** GTK+ 3  
- **Banco de Dados:** SQLite  
- **Criptografia:** libsodium  
- **Sistema de Build:** CMake  

---

### 📦 Requisitos
Para compilar e executar o projeto, você precisará ter as seguintes bibliotecas instaladas no seu sistema:

- CMake  
- GTK+ 3 (`libgtk-3-dev`)  
- SQLite3 (`libsqlite3-dev`)  
- libsodium (`libsodium-dev`)  

---

### 🛠 Instalação

### Debian/Ubuntu
```bash
sudo apt-get install libgtk-3-dev libsqlite3-dev libsodium-dev cmake
````

### Fedora

```bash
sudo dnf install gtk3-devel sqlite-devel libsodium-devel cmake
```

### Arch Linux

```bash
sudo pacman -S gtk3 sqlite libsodium cmake
```

---

## ⚙️ Compilação

O projeto usa o **CMake** para gerenciar a compilação.

1. Crie um diretório de build e entre nele:

   ```bash
   mkdir build
   cd build
   ```

2. Configure o projeto (o `..` indica que o `CMakeLists.txt` está no diretório pai):

   ```bash
   cmake ..
   ```

3. Compile:

   ```bash
   make
   ```

---

## ▶️ Como Executar

Após a compilação, o executável estará no diretório `build`.

Exemplo (supondo que no `CMakeLists.txt` o executável se chame `meu_app`):

```bash
./build/meu_app
```

---

## 🤝 Contribuição

Contribuições são bem-vindas!

* Abra uma *issue* para discutir mudanças propostas;
* Ou envie um *pull request* com suas alterações.

---

## 📄 Licença

Este projeto está licenciado sob a Licença **MIT**.
Veja o arquivo [`LICENSE`](LICENSE) para mais detalhes.

---

## 👨‍💻 Autor

**Daniel-X2**

* GitHub: [github.com/Daniel-X2](https://github.com/Daniel-X2)
* LinkedIn: [linkedin.com/in/daniel-da-silva-32814636b](https://www.linkedin.com/in/daniel-da-silva-32814636b/)




