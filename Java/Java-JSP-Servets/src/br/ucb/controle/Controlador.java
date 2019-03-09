package br.ucb.controle;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import br.ucb.modelo.bean.Curso;
import br.ucb.modelo.dao.CursoDAO;

/**
 * Servlet implementation class Controlador
 */
@WebServlet("/Controlador")
public class Controlador extends HttpServlet {
	private static final long serialVersionUID = 1L;


	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		RequestDispatcher dispatcher;
		Curso curso;
		CursoDAO cursoDao;
		List<Curso> cursos;
		String acao = request.getParameter("acao");
		String psq = request.getParameter("pesq");
		String visao=null;
		switch (acao) {
		case "listar":
			try {
				visao = "cursoLista.jsp";
				cursoDao = new CursoDAO();
				if(psq != null) {
					cursos = cursoDao.listar(psq);
				}else {
					cursos = cursoDao.listar();
				}
				request.setAttribute("cursos", cursos);
			} catch (SQLException e) {
				request.setAttribute("erro", "Erro de banco de dados");
			}
			break;
		case "salvar":
			visao = "cursoEntrada.jsp";
			try {
				cursoDao = new CursoDAO();
				curso = new Curso();
				if(!request.getParameter("id").equals("")) {
					curso.setId(Long.parseLong(request.getParameter("id")));
				}
				curso.setNome(request.getParameter("nome"));
				curso.setSemestres(Integer.parseInt(request.getParameter("semestres")));
				curso.setValor(Float.parseFloat(request.getParameter("valor")));
				if (request.getParameter("id") == "") {
					if (cursoDao.incluir(curso) > 0) {
						request.setAttribute("mensagem", "Incluído com sucesso");
						cursos = cursoDao.listar();
						request.setAttribute("cursos", cursos);
						visao = "cursoLista.jsp";
					}
					else
						request.setAttribute("erro", "Erro de inclusão");
				}
				else {
					if (cursoDao.alterar(curso) > 0) {
						request.setAttribute("mensagem", "Alterado com sucesso");
						cursos = cursoDao.listar();
						request.setAttribute("cursos", cursos);
						visao = "cursoLista.jsp";
					}
					else
						request.setAttribute("erro", "Erro de alteração");
				}
			}
		
			catch (SQLException e) {
				request.setAttribute("erro", "Erro de banco de dados");
			}
			break;
		case "excluir":
			try {
				visao = "cursoLista.jsp";
				cursoDao = new CursoDAO();
				try {
					curso = new Curso();
					curso.setId(Long.parseLong(request.getParameter("id")));
					if (cursoDao.excluir(curso) > 0)
						request.setAttribute("mensagem", "Excluído com sucesso");
					else
						request.setAttribute("erro", "Erro de exclusão");
					cursos = cursoDao.listar();
					request.setAttribute("cursos", cursos);
				}
				catch (NumberFormatException e) {
					request.setAttribute("erro", "Erro de conversao");
				}
			} catch (SQLException e) {
				request.setAttribute("erro", "Erro de banco de dados");
			}
			break;
		case "consultar":
			visao = "cursoEntrada.jsp";
			try {
				cursoDao = new CursoDAO();
				try {
					curso = cursoDao.consultar(Long.parseLong(request.getParameter("id")));
					if (curso != null)
						request.setAttribute("curso", curso);
					else
						request.setAttribute("erro", "Erro de consulta");
				}
				catch (NumberFormatException e) {
					request.setAttribute("erro", "Erro de conversao");
				}
			} catch (SQLException e) {
				request.setAttribute("erro", "Erro de banco de dados");
			}
		}
		dispatcher = request.getRequestDispatcher(visao);
		dispatcher.forward(request, response);
	}
}

