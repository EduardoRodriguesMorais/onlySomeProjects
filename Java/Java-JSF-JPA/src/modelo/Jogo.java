package modelo;

import java.io.Serializable;
import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

@Entity
@Table(name="jogos")
public class Jogo implements Serializable {
	private static final long serialVersionUID = 1L;
	@Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	private long id;
	@ManyToOne
	@JoinColumn(name="idSelecao1")	
	private Selecao selecao1;
	private int golSelecao1;
	@ManyToOne
	@JoinColumn(name="idSelecao2")	
	private Selecao selecao2;
	private int golSelecao2;
	private boolean ocorreu;
	@Temporal(TemporalType.DATE) 
	private Date dia;
	
	public Jogo() {
	}
	
	public void apurarPontos() {
		if (this.ocorreu) {
			if (this.golSelecao1 > this.getGolSelecao2())
				this.selecao1.addPontos(3);
			else
				if (this.golSelecao2 > this.getGolSelecao1())
					this.selecao2.addPontos(3);
				else {
					this.selecao1.addPontos(1);
					this.selecao2.addPontos(1);
				}
		}
	}

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public Selecao getSelecao1() {
		return selecao1;
	}

	public void setSelecao1(Selecao selecao1) {
		this.selecao1 = selecao1;
	}

	public int getGolSelecao1() {
		return golSelecao1;
	}

	public void setGolSelecao1(int golSelecao1) {
		this.golSelecao1 = golSelecao1;
	}

	public Selecao getSelecao2() {
		return selecao2;
	}

	public void setSelecao2(Selecao selecao2) {
		this.selecao2 = selecao2;
	}

	public int getGolSelecao2() {
		return golSelecao2;
	}

	public void setGolSelecao2(int golSelecao2) {
		this.golSelecao2 = golSelecao2;
	}

	public boolean isOcorreu() {
		return ocorreu;
	}

	public void setOcorreu(boolean ocorreu) {
		this.ocorreu = ocorreu;
	}

	public Date getDia() {
		return dia;
	}

	public void setDia(Date dia) {
		this.dia = dia;
	}

}
