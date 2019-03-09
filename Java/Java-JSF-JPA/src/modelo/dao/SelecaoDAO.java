package modelo.dao;

import java.util.List;

import javax.persistence.Query;

import modelo.Selecao;

public class SelecaoDAO extends GenericDAO<Selecao> {
	private static final long serialVersionUID = 1L;
	
	
	@SuppressWarnings("unchecked")
	public List<Selecao> listar() {
		System.out.println(super.getEm());
		super.getEm().clear();
		Query q = super.getEm().createQuery("SELECT s FROM Selecao s");
		return q.getResultList();
	}
	
}
