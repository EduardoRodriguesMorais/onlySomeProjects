package modelo.managedBean;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

import modelo.Jogo;
import modelo.Selecao;
import modelo.dao.JogoDAO;
import modelo.dao.SelecaoDAO;

@ManagedBean
@SessionScoped
public class CopaMB implements Serializable {
	private static final long serialVersionUID = 1L;
	private JogoDAO jogoDAO;
	private SelecaoDAO selecaoDAO;
	private List<Jogo> jogos = new ArrayList<Jogo>();
	private List<Selecao> selecoes;
	
	public CopaMB() {
		this.jogoDAO = new JogoDAO();
		this.selecaoDAO = new SelecaoDAO();
	}
	
	public String listarSelecoes() {

		
		this.selecoes = this.selecaoDAO.listar();
		return "selecoes";
	}
	
	public String listarJogos() {
		this.jogos = this.jogoDAO.listar();
		return "jogos";
	}

	public void salvar(Jogo jogo) {
		this.jogoDAO.alterar(jogo);
	}

	public List<Jogo> getJogos() {
		return jogos;
	}

	public void setJogos(List<Jogo> jogos) {
		this.jogos = jogos;
	}

	public List<Selecao> getSelecoes() {
		return selecoes;
	}

	public void setSelecoes(List<Selecao> selecoes) {
		this.selecoes = selecoes;
	}

}
