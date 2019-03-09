CREATE DATABASE copa2018;

USE copa2018;

CREATE TABLE selecao (
  id int(10) unsigned NOT NULL AUTO_INCREMENT,
  nome varchar(50) NOT NULL,
  grupo varchar(1) NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE jogos (
  id int(10) unsigned NOT NULL AUTO_INCREMENT,
  idSelecao1 int(10) unsigned NOT NULL,
  golSelecao1 int unsigned NOT NULL,
  idSelecao2 int(10) unsigned NOT NULL,
  golSelecao2 int unsigned NOT NULL,
  ocorreu boolean DEFAULT NULL,
  dia datetime NOT NULL,
  PRIMARY KEY (id),
  KEY fk_selecao1(idSelecao1),
  KEY fk_selecao2(idSelecao2),
  CONSTRAINT fk_selecao1 FOREIGN KEY(idSelecao1) REFERENCES selecao(id),
  CONSTRAINT fk_selecao2 FOREIGN KEY(idSelecao2) REFERENCES selecao(id)
);