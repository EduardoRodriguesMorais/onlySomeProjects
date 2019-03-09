<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
	<h1>Listagem de Cursos</h1>
	<font color="#FF0000">${erro}</font>
	<font color="#00FF00">${mensagem}</font>
	<form method="get" action="Controlador">
		<input type="hidden" name="acao" value="listar"> <input
			type="text" name="pesq"> <input type="submit" value="Filtrar">
	</form>
	<table border="1">
		<tr bgcolor="#AAAAAA">
			<th width="200" align="center">Nome</th>
			<th width="70" align="center">Semestres</th>
			<th width="80" align="center">Valor</th>
			
			<th align="center">&nbsp;Alterar Excluir</th>
		</tr>
		<c:forEach var="curso" items="${cursos}">
			<tr>
				<td align="left">${curso.nome}</td>
				<td align="center">${curso.semestres}</td>
				<td align="right"><fmt:formatNumber value="${curso.valor}"
						type="currency" /></td>
				<td align="center">
				 <a href="Controlador?acao=consultar&id=${curso.id}"><img src="img/editar.png" width="30" border="0"></a>
				 <a href="Controlador?acao=excluir&id=${curso.id}"><img	src="img/excluir.png" width="30" border="0"></a></td>
			</tr>
		</c:forEach>
	</table>
	<a href="home.html">Voltar</a>
</body>
</html>