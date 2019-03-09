package br.ucb.modelo.bean;

import java.io.Serializable;

public class Curso implements Serializable{
	private static final long serialVersionUID = 1L;
	private long id;
	private String nome;
	private int semestres;
	private float valor;

	public Curso() {
	}

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public int getSemestres() {
		return semestres;
	}

	public void setSemestres(int semestres) {
		this.semestres = semestres;
	}

	public float getValor() {
		return valor;
	}

	public void setValor(float valor) {
		this.valor = valor;
	}
}
