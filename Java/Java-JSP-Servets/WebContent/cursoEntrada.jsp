<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
	<c:if test="${curso == null}">
		<h2>Inclus&atilde;o de Curso</h2>
	</c:if>
	<c:if test="${curso != null}">
		<h2>Edi&ccedil;&atilde;o de Curso</h2>
	</c:if>
	<font color="#FF0000">${erro}</font>
	<font color="#00FF00">${mensagem}</font>
	<form method="get" action="Controlador">
		<input type="hidden" name="acao" value="salvar">
		<input type="hidden" name="id" value="${curso.id}">
		<label>Nome</label><br />
		<input type="text" name="nome" value="${curso.nome}" size="50" maxlength="50" /><p />
		<label>Semestres (QTD)</label><br />
		<input type="text" name="semestres" value="${curso.semestres}" size="2" maxlength="2" /><p />
		<label>Valor (R$)</label><br />
		<input type="text" name="valor" value="${curso.valor}" size="10" maxlength="10" /><p />
		<input type="submit" value="Salvar" />
	</form>
	<a href="home.html">Voltar</a>
</body>
</html>