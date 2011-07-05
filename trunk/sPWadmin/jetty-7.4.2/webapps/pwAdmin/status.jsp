<%@page import="protocol.*"%>
<%@page import="java.sql.*"%>
<%@include file="WEB-INF/.pwadminconf.jsp"%>

<head>
	<link rel="shortcut icon" href="include/fav.ico">
	<link rel="stylesheet" type="text/css" href="include/style.css">
	<meta http-equiv="refresh" content="30" >

	<%
		String status = "<font color=\"#00cc00\">Online</font>";;
		String users;
		int count = 0;

		try
		{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
			Statement statement = connection.createStatement();
			ResultSet rs = statement.executeQuery("SELECT COUNT(*) FROM users");
			rs.next();
			count = rs.getInt(1);
			rs.close();
			statement.close();
			connection.close();
		}
		catch(Exception e)
		{
			count = -1;
		}

		try
		{
			Integer[] user = new Integer[3];
			DeliveryDB.GetMaxOnlineNum(user);
			if(user[2] == null)
			{
				status = "<font color=\"#ee0000\">Offline</font>";
				user[2] = 0;
			}
			users = user[2] + " / " + count;
		}
		catch(Exception e)
		{
			users = "-1" + " / " + count;
		}
	%>
</head>

<body style="margin: 0;">
Status: <b><%out.print(status);%></b>
<br>
Users: <font color="#000000"><b><%out.print(users);%></b></font>

</body>