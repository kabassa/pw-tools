<%@page import="java.sql.*"%>
<%@page import="java.security.*"%>
<%@include file="../../WEB-INF/.pwadminconf.jsp"%>

<%!
    	String pw_encode(String salt, MessageDigest alg)
	{
		alg.reset(); 
		alg.update(salt.getBytes());
		byte[] digest = alg.digest();
		StringBuffer hashedpasswd = new StringBuffer();
		String hx;
		for(int i=0; i<digest.length; i++)
		{
			hx =  Integer.toHexString(0xFF & digest[i]);
			//0x03 is equal to 0x3, but we need 0x03 for our md5sum
			if(hx.length() == 1)
			{
				hx = "0" + hx;
			} 
			hashedpasswd.append(hx);
		}
		salt = "0x" + hashedpasswd.toString();

        	return salt;
   	}
%>

<table cellpadding="2" cellspacing="0" border="0">
<tr>
<%
	if(request.getParameter("logout") != null && request.getParameter("logout").compareTo("true") == 0)
	{
		request.getSession().removeAttribute("user");
	}

	if(request.getParameter("username") != null && request.getParameter("password") != null)
	{
		String username = request.getParameter("username");
		String password = pw_encode(username + request.getParameter("password"), MessageDigest.getInstance("MD5"));

		Class.forName("com.mysql.jdbc.Driver").newInstance();
		Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
		CallableStatement cs = connection.prepareCall("{call acquireuserpasswd(?,?,?)}");
		cs.setString(1, username);
		cs.registerOutParameter(3, Types.VARCHAR);
		cs.execute();
		
		if(username != "" && password.compareTo(cs.getString(3)) == 0)
		{
			Statement statement = connection.createStatement();
			ResultSet rs = statement.executeQuery("SELECT ID FROM users WHERE name='" + username + "'");
			rs.next();
			request.getSession().setAttribute("user", rs.getString("ID"));
		}
	}

	if(request.getSession().getAttribute("user") == null)
	{
		out.println("<form action=\"index.jsp\" method=\"post\"><td><td>Login: <input type=\"text\" name=\"username\" style=\"width: 100; text-align: center;\"></input></td><td>Pass: <input type=\"password\" name=\"password\" style=\"width: 100; text-align: center;\"></input></td></td><td><input type=\"image\" src=\"../../include/btn_login.jpg\" style=\"border: 0px;\"></input></td></form>");
	}
	else
	{
		out.println("<td><a href=\"index.jsp?logout=true\"><img src=\"../../include/btn_logout.jpg\" border=\"0\"></img></a></td>");
	}
%>
</tr>
</table>