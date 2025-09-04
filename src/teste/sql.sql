-- Active: 1756937965341@@127.0.0.1@3306
CREATE TABLE IF NOT EXISTS  anotacoes
(
    id INTEGER PRIMARY KEY ,
    nome_item VARCHAR(30),
    descricao TEXT
);
CREATE TABLE IF NOT EXISTS usuarios 
(
    id INTEGER PRIMARY KEY ,
    nome_item VARCHAR(30),
    nome_usuario VARCHAR(50),
    senha TEXT
);


INSERT INTO usuarios(nome_item,nome_usuario,senha) VALUES ('daniel nesse teste','nome do usuario','aqui e a senha criptograda')

