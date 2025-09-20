
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
DROP TABLE nome_tabela;


ALTER TABLE nome_tabela ADD COLUMN email TEXT;
UPDATE nome_tabela SET idade = 26 WHERE id = '1';

INSERT INTO usuarios(nome_item,nome_usuario,senha) VALUES ('daniel nesse teste','nome do usuario','aqui e a senha criptograda')

DELETE FROM nome_tabela WHERE nome = 'Maria';

SELECT * FROM nome_tabela;

