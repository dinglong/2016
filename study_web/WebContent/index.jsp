<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Simple title</title>
</head>
<body>
	<%
		java.util.Date d = new java.util.Date();
	%>
	<h1>
		Today's date is
		<%=d.toString()%>
		and this jsp page worked!
	</h1>

	<form action="HelloServlet" method=POST>
		First Name: <input type=text size=20 name=firstname> <br>
		Last Name: <input type=text size=20 name=lastname> <br>
		<input type=submit>
	</form>
</body>
</html>