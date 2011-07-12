<%@page import="java.sql.*"%>
<%@page import="java.util.*"%>
<%@page import="java.security.*"%>
<%@include file="WEB-INF/.pwadminconf.jsp"%>

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

<%
	boolean allowed = false;

	if(request.getSession().getAttribute("ssid") == null)
	{
		out.println("<p align=\"right\"><font color=\"#ee0000\"><b>Login for Account administration...</b></font></p>");
	}
	else
	{
		allowed = true;
	}

	String message = "<br>";
	if(request.getParameter("action") != null)
	{
			String action = new String(request.getParameter("action"));

			if(action.compareTo("adduser") == 0)
			{
				String login = request.getParameter("login");
				String password = request.getParameter("password");
				String mail = request.getParameter("mail");

				if(login.length() > 0 && password.length() > 0)
				{
					if(login.length() < 4 || login.length() > 10 || password.length() < 4 || password.length() > 10)
					{
						message = "<font color=\"ee0000\">Only 4-10 Characters</font>";
					}
					else
					{
						String alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
						boolean check = true;
						char c;
						for(int i=0; i<login.length(); i++)
						{
							c = login.charAt(i);
							if (alphabet.indexOf(c) == -1)
							{
								check = false;
								break;
							}
						}
						for(int i=0; i<password.length(); i++)
						{
							c = password.charAt(i);
							if (alphabet.indexOf(c) == -1)
							{
								check = false;
								break;
							}
						}

						if(!check)
						{
							message = "<font color=\"ee0000\">Forbidden Characters</font>";
						}
						else
						{
							try
							{
								Class.forName("com.mysql.jdbc.Driver").newInstance();
								Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
								Statement statement = connection.createStatement();
								ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE name='" + login + "'");
								int count = 0;

								while (rs.next())
								{
									count++;
								}
								if(count > 0)
								{
									message = "<font color=\"ee0000\">User Already Exists</font>";
								}
								else
								{
									password = pw_encode(login + password, MessageDigest.getInstance("MD5"));
									rs = statement.executeQuery("CALL adduser('" + login + "', " + password + ", '0', '0', '0', '0', '', '0', '0', '0', '0', '0', '0', '0', '', '', " + password + ")");
									message = "<font color=\"00cc00\">Account Created</font>";
								}

								rs.close();
								statement.close();
								connection.close();
							}
							catch(Exception e)
							{
								message = "<font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font>";
							}
						}
					}
				}
			}

			if(action.compareTo("passwd") == 0)
			{
				String login = request.getParameter("login");
				String password_old = request.getParameter("password_old");
				String password_new = request.getParameter("password_new");

				if(login.length() > 0 && password_old.length() > 0 && password_new.length() > 0)
				{
					if(password_new.length() < 4 || password_new.length() > 10)
					{
						message = "<font color=\"ee0000\">Only 4-10 Characters</font>";
					}
					else
					{
						String alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
						boolean check = true;
						char c;
						for(int i=0; i<password_new.length(); i++)
						{
							c = password_new.charAt(i);
							if (alphabet.indexOf(c) == -1)
							{
								check = false;
								break;
							}
						}

						if(!check)
						{
							message = "<font color=\"ee0000\">Forbidden Characters</font>";
						}
						else
						{
							try
							{
								Class.forName("com.mysql.jdbc.Driver").newInstance();
								Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
								Statement statement = connection.createStatement();
								ResultSet rs = statement.executeQuery("SELECT ID, passwd FROM users WHERE name='" + login + "'");
								String password_stored = "";
								String id_stored = "";
								int count = 0;
								while(rs.next())
								{
									id_stored = rs.getString("ID");
									password_stored = rs.getString("passwd");
									count++;
								}

								if(count <= 0)
								{
									message = "<font color=\"ee0000\">User Don't Exists</font>";
								}
								else
								{
									password_old = pw_encode(login + password_old, MessageDigest.getInstance("MD5"));
/*
									// Some hard encoding problems requires a strange solution...
									// changePasswd -> wrong encoding password destroyed...
									// Only a temp entry in database gives us a correct encoded password for comparsion

									rs = statement.executeQuery("call adduser('" + login + "_TEMP_USER', " + password_old + ", '0', '0', '0', '0', '', '0', '0', '0', '0', '0', '0', '0', '', '', " + password_old + ")");
									rs = statement.executeQuery("SELECT passwd FROM users WHERE name='" + login + "_TEMP_USER'");
									rs.next();
									password_old = rs.getString("passwd");

									// Delete temp entry
									statement.executeUpdate("DELETE FROM users WHERE name='" + login + "_TEMP_USER'");

									if(password_old.compareTo(password_stored) != 0)
									{
										message = "<font color=\"ee0000\">Old Password Mismatch</font>";
									}
									else
									{
										password_new = pw_encode(login + password_new, MessageDigest.getInstance("MD5"));

										// LOCK TABLE to ensure that nobody else get the original ID of the user
										statement.executeUpdate("LOCK TABLE users WRITE");
										// Delete old entry
										statement.executeUpdate("DELETE FROM users WHERE name='" + login + "'");
										// Add new entry
										rs = statement.executeQuery("call adduser('" + login + "', " + password_new + ", '0', '0', '0', '0', '', '0', '0', '0', '0', '0', '0', '0', '', '', " + password_new + ")");
										// change new entry ID to original ID - necessary to keep characters of this account
										statement.executeUpdate("UPDATE users SET ID='" + id_stored + "' WHERE name='" + login + "'");
										// UNLOCK TABLES
										statement.executeUpdate("UNLOCK TABLES");

										message = "<font color=\"00cc00\">Password Changed</font>";
									}
*/
									CallableStatement cs = connection.prepareCall("{call acquireuserpasswd(?,?,?)}");
									cs.setString(1, login);
									cs.registerOutParameter(3, Types.VARCHAR);
									cs.execute();
		
									if(password_old.compareTo(cs.getString(3)) != 0)
									{
										message = "<font color=\"ee0000\">Old Password Mismatch</font>";
									}
									else
									{
										password_new = pw_encode(login + password_new, MessageDigest.getInstance("MD5"));
										statement.executeQuery("CALL changePasswd('" + login + "', " + password_new + ")");
										statement.executeQuery("CALL changePasswd2('" + login + "', " + password_new + ")");
										message = "<font color=\"00cc00\">Password Changed</font>";
									}
								}

								rs.close();
								statement.close();
								connection.close();
							}
							catch(Exception e)
							{
								message = "<font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font>";
							}
						}
					}
				}
			}

			if(action.compareTo("deluser") == 0)
			{
				if(request.getSession().getAttribute("ssid") == null)
				{
					message = "<font color=\"ee0000\">Acces Denied</font>";
				}
				else
				{
					String type = request.getParameter("type");
					String ident = request.getParameter("ident");
					String character = request.getParameter("character");

					if(type.length() > 0 && ident.length() > 0 && character.length() > 0)
					{
						try
						{
							Class.forName("com.mysql.jdbc.Driver").newInstance();
							Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
							Statement statement = connection.createStatement();
							ResultSet rs;
							int count;

							if(type.compareTo("id") == 0)
							{
								rs = statement.executeQuery("SELECT ID FROM users WHERE ID='" + ident + "'");
								count = 0;
								while(rs.next())
								{
									count++;
								}
							}

							else
							{
								rs = statement.executeQuery("SELECT ID FROM users WHERE name='" + ident + "'");
								count = 0;
								while(rs.next())
								{
									ident = rs.getString("ID");
									count++;
								}
							}

							if(count <= 0)
							{
								message = "<font color=\"ee0000\">User Don't Exists</font>";
							}
							else
							{
								statement.executeUpdate("DELETE FROM users WHERE ID='" + ident + "'");
								message = "<font color=\"00cc00\">Account Deleted</font><br><font color=\"ee0000\">Please Check for Existing Characters (ID " + ident + " - " + (15+Integer.parseInt(ident)) + ")</font>";
							}

							rs.close();
							statement.close();
							connection.close();
						}
						catch(Exception e)
						{
							message = "<font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font>";
						}
					}
				}
			}

			if(action.compareTo("changegm") == 0)
			{
				if(request.getSession().getAttribute("ssid") == null)
				{
					message = "<font color=\"ee0000\">Acces Denied</font>";
				}
				else
				{
					String type = request.getParameter("type");
					String ident = request.getParameter("ident");
					String act = request.getParameter("act");

					if(type.length() > 0 && ident.length() > 0 && act.length() > 0)
					{
						try
						{
							Class.forName("com.mysql.jdbc.Driver").newInstance();
							Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
							Statement statement = connection.createStatement();
							ResultSet rs;
							int count;

							if(type.compareTo("id") == 0)
							{
								rs = statement.executeQuery("SELECT ID FROM users WHERE ID='" + ident + "'");
								count = 0;
								while(rs.next())
								{
									count++;
								}
							}

							else
							{
								rs = statement.executeQuery("SELECT ID FROM users WHERE name='" + ident + "'");
								count = 0;
								while(rs.next())
								{
									ident = rs.getString("ID");
									count++;
								}
							}

							if(count <= 0)
							{
								message = "<font color=\"ee0000\">User Don't Exists</font>";
							}
							else
							{
								rs = statement.executeQuery("SELECT userid FROM auth WHERE userid='" + ident + "'");
								count = 0;
								while(rs.next())
								{
									count++;
								}
								if(count > 0)
								{
									if(act.compareTo("delete") == 0)
									{
										statement.executeUpdate("DELETE FROM auth WHERE userid='" + ident + "'");
										message = "<font color=\"00cc00\">GM Access Removed From User</font>";
									}
									else
									{
										message = "<font color=\"ee0000\">User Already Have GM Access</font>";
									}
								}
								else
								{
									if(act.compareTo("add") == 0)
									{
										rs = statement.executeQuery("CALL addGM('" + ident + "', '1')");
										message = "<font color=\"00cc00\">GM Access Added For User</font>";
									}
									else
									{
										message = "<font color=\"ee0000\">User Don't Have GM Access</font>";
									}
								}
							}

							rs.close();
							statement.close();
							connection.close();
						}
						catch(Exception e)
						{
							message = "<font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font>";
						}
					}
				}
			}

			if(action.compareTo("addcubi") == 0)
			{
				if(request.getSession().getAttribute("ssid") == null)
				{
					message = "<font color=\"ee0000\">Acces Denied</font>";
				}
				else
				{
					String type = request.getParameter("type");
					String ident = request.getParameter("ident");
					int amount = 0;
					try
					{
						amount = Integer.parseInt(request.getParameter("amount"));
					}
					catch(Exception e)
					{}

					if(type.length() > 0 && ident.length() > 0)
					{
						if(amount < 1 || amount > 999999)
						{
							message = "<font color=\"ee0000\">Invalid Amount (1-999999)</font>";
						}
						else
						{
							try
							{
								Class.forName("com.mysql.jdbc.Driver").newInstance();
								Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
								Statement statement = connection.createStatement();
								ResultSet rs;
								int count;

								if(type.compareTo("id") == 0)
								{
									rs = statement.executeQuery("SELECT ID FROM users WHERE ID='" + ident + "'");
									count = 0;
									while(rs.next())
									{
										count++;
									}
								}

								else
								{
									rs = statement.executeQuery("SELECT ID FROM users WHERE name='" + ident + "'");
									count = 0;
									while(rs.next())
									{
										ident = rs.getString("ID");
										count++;
									}
								}

								if(count <= 0)
								{
									message = "<font color=\"ee0000\">User Don't Exists</font>";
								}
								else
								{
									rs = statement.executeQuery("CALL usecash ( '" + ident + "' , 1, 0, 1, 0, '" + 100*amount + "', 1, @error)");
									message = "<font color=\"00cc00\">" + amount + ".00 Cubi Gold Added</font><br><font color=\"ee0000\">Transaction May Take Up To 5 Minutes<br>Relog Required To Receive Cubi</font>";
								}
								
								rs.close();
								statement.close();
								connection.close();
							}
							catch(Exception e)
							{
								message = "<font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font>";
							}
						}
					}
				}
			}
	}
%>

<table width="800" cellpadding="0" cellspacing="0" border="0">

<tr>
	<td height="1" align="center" valign="top" colspan="3">
		<b><% out.print(message); %></b>
	</td>
</tr>

<tr>
	<td height="1" align="center" valign="top" colspan="3">
		<br>
	</td>
</tr>

<tr>
	<td align="center" valign="top">
		<form action="index.jsp?page=account&action=adduser" method="post" style="margin: 0px;">
			<table width="240" cellpadding="5" cellspacing="0" style="border:1px solid #cccccc;">
				<tr>
					<th align="center" colspan="2">
						<b><font color="#ffffff">ACCOUNT REGISTRATION</font></b>
					</th>
				</tr>
				<tr>
					<td>Login:</td><td align="right"><input type="text" name="login" style="width: 100; text-align: center;"></td>
				</tr>
				<tr>
					<td>Password:</td><td align="right"><input type="password" name="password" style="width: 100; text-align: center;"></td>
				</tr>
				<tr>
					<td>E-Mail</td><td align="right"><input type="text" name="mail" value="NOT NEEDED" style="width: 100; text-align: center;"></td>
				</tr>
				<tr>
					<td align="center" colspan="2"><input type="image" name="submit" src="include/btn_register.jpg" style="border: 0px;"></td>
				</tr>
			</table>
		</form>
	</td>

	<td align="center" valign="top">
		<form action="index.jsp?page=account&action=passwd" method="post" style="margin: 0px;">
			<table width="240" cellpadding="5" cellspacing="0" style="border:1px solid #cccccc;">
				<tr>
					<th align="center" colspan="2">
						<b><font color="#ffffff">CHANGE ACCOUNT PASSWORD</font></b>
					</th>
				</tr>
				<tr>
					<td>Login:</td><td align="right"><input type="text" name="login" style="width: 100; text-align: center;"></td>
				</tr>
				<tr>
					<td>Old Password:</td><td align="right"><input type="password" name="password_old" style="width: 100; text-align: center;"></td>
				</tr>
				<tr>
					<td>New Password:</td><td align="right"><input type="password" name="password_new" style="width: 100; text-align: center;"></td>
				</tr>
				<tr>
					<td align="center" colspan="2"><input type="image" name="submit" src="include/btn_change.jpg" style="border: 0px;"></td>
				</tr>
			</table>
		</form>
	</td>

	<td align="center" valign="top">
		<%
			if(allowed)
			{
				out.println("<form action=\"index.jsp?page=account&action=deluser\" method=\"post\" style=\"margin: 0px;\"><table width=\"240\" cellpadding=\"5\" cellspacing=\"0\" style=\"border:1px solid #cccccc;\">");
				out.println("<tr><th align=\"center\" colspan=\"2\"><b><font color=\"#ffffff\">DELETE ACCOUNT</font></b></th></tr>");
				out.println("<tr><td>Type:</td><td align=\"right\"><select name=\"type\" style=\"width: 100; text-align: center;\"><option value=\"id\">by ID</option><option value=\"login\">by Login</option></select></td></tr>");
				out.println("<tr><td>Identifier:</td><td align=\"right\"><input type=\"text\" name=\"ident\" style=\"width: 100; text-align: center;\"></td></tr>");
				out.println("<tr><td>Characters:</td><td align=\"right\"><select name=\"character\" style=\"width: 100; text-align: center;\"><option value=\"keep\">Keep</option></select></td></tr>");
				out.println("<tr><td align=\"center\" colspan=\"2\"><input type=\"image\" name=\"submit\" src=\"include/btn_delete.jpg\" style=\"border: 0px;\"></td></tr>");
				out.println("</table></form>");
			}
		%>
	</td>
</tr>

<tr>
	<td height="1" colspan="3">
		<br>
	</td>
</tr>

<tr>
	<td align="center" valign="top">
		<%
			if(allowed)
			{
				out.println("<form action=\"index.jsp?page=account&action=changegm\" method=\"post\" style=\"margin: 0px;\"><table width=\"240\" cellpadding=\"5\" cellspacing=\"0\" style=\"border:1px solid #cccccc;\">");
				out.println("<tr><th align=\"center\" colspan=\"2\"><b><font color=\"#ffffff\">GAME MASTER</font></b></th></tr>");
				out.println("<tr><td>Type:</td><td align=\"right\"><select name=\"type\" style=\"width: 100; text-align: center;\"><option value=\"id\">by ID</option><option value=\"login\">by Login</option></select></td></tr>");
				out.println("<tr><td>Identifier:</td><td align=\"right\"><input type=\"text\" name=\"ident\" style=\"width: 100; text-align: center;\"></td></tr>");
				out.println("<tr><td>Action:</td><td align=\"right\"><select name=\"act\" style=\"width: 100; text-align: center;\"><option value=\"add\">Grant GM</option><option value=\"delete\">Deny GM</option></select></td></tr>");
				out.println("<tr><td align=\"center\" colspan=\"2\"><input type=\"image\" name=\"submit\" src=\"include/btn_submit.jpg\" style=\"border: 0px;\"></td></tr>");
				out.println("</table></form>");
			}
		%>
	</td>

	<td align="center" valign="top">
		<%
			if(allowed)
			{
				out.println("<form action=\"index.jsp?page=account&action=addcubi\" method=\"post\" style=\"margin: 0px;\"><table width=\"240\" cellpadding=\"5\" cellspacing=\"0\" style=\"border:1px solid #cccccc;\">");
				out.println("<tr><th align=\"center\" colspan=\"2\"><b><font color=\"#ffffff\">CUBI TRANSFER</font></b></th></tr>");
				out.println("<tr><td>Type:</td><td align=\"right\"><select name=\"type\" style=\"width: 100; text-align: center;\"><option value=\"id\">by ID</option><option value=\"login\">by Login</option></select></td></tr>");
				out.println("<tr><td>Identifier:</td><td align=\"right\"><input type=\"text\" name=\"ident\" style=\"width: 100; text-align: center;\"></td></tr>");
				out.println("<tr><td>Amount:</td><td align=\"right\"><input type=\"text\" name=\"amount\" style=\"width: 100; text-align: center;\"></td></tr>");
				out.println("<tr><td align=\"center\" colspan=\"2\"><input type=\"image\" name=\"submit\" src=\"include/btn_submit.jpg\" style=\"border: 0px;\"></td></tr>");
				out.println("</table></form>");
			}
		%>
	</td>

	<td align="center" valign="top">
		<%
			if(allowed)
			{
				out.println("<table cellpadding=\"0\" cellspacing=\"0\" style=\"border:1px solid #cccccc;\">");
				out.println("<tr><th height=\"1\" align=\"center\" colspan=\"3\" style=\"padding: 5;\"><b><font color=\"#ffffff\">BROWSE ACCOUNTS</font></b></th></tr>");
				out.println("<tr bgcolor=\"f0f0f0\"><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"><b>ID</b></td><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"><b>Name</b></td><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"><b>Creation Time</b></td></tr>");
				out.println("<tr><td colspan=\"3\" ><div style=\"width: 240; height: 96; overflow: auto;\">");
				out.println("<table width=\"100%\" cellpadding=\"3\" cellspacing=\"0\" style=\"border:0px solid #cccccc;\">");

				try
				{
					Class.forName("com.mysql.jdbc.Driver").newInstance();
					Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
					Statement statement = connection.createStatement();
					ResultSet rs;

					rs = statement.executeQuery("SELECT DISTINCT userid FROM auth");
					ArrayList gm = new ArrayList();

					while(rs.next())
					{
						gm.add(rs.getInt("userid"));
					}

					rs = statement.executeQuery("SELECT ID, name, creatime FROM users");
					while(rs.next())
					{
						if(gm.contains(rs.getInt("ID")))
						{
							out.print("<tr><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\">" + rs.getString("ID") + "</td><td style=\"border-bottom: 1px solid #cccccc;\"><font color=\"#ee0000\">" + rs.getString("name") + "</font></td><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\">" + rs.getString("creatime").substring(0, 16) + "</td></tr>");
						}
						else
						{
							out.print("<tr><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\">" + rs.getString("ID") + "</td><td style=\"border-bottom: 1px solid #cccccc;\">" + rs.getString("name") + "</td><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\">" + rs.getString("creatime").substring(0, 16) + "</td></tr>");
						}
					}

					rs.close();
					statement.close();
					connection.close();
				}
				catch(Exception e)
				{
					out.println("<tr><td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"><font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font></table></div></td></tr>");
				}

				out.println("</table></div></td></tr></table>");
			}
		%>
	</td>
</tr>

</table>