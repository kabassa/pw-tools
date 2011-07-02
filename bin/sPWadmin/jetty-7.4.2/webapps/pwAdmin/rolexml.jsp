<%@page import="java.sql.*"%>
<%@page import="protocol.*"%>
<%@page import="java.io.*"%>
<%@page import="java.text.*"%>
<%@page import="java.util.Iterator"%>
<%@page import="com.goldhuman.Common.Octets"%>
<%@page import="com.goldhuman.IO.Protocol.Rpc.Data.DataVector"%>
<%@page import="org.apache.commons.lang.StringEscapeUtils"%>
<%@include file="WEB-INF/.pwadminconf.jsp"%>

<%
	String message = "<br>";
	boolean allowed = false;

	if(request.getSession().getAttribute("ssid") == null)
	{
		out.println("<p align=\"right\"><font color=\"#ee0000\"><b>Login for Character administration...</b></font></p>");
	}
	else
	{
		allowed = true;
	}

	int id = -1;
	int uid = -1;
	String xml = "";

	if(allowed && request.getParameter("ident") != null)
	{
		try
		{
			id = Integer.parseInt(request.getParameter("ident"));
			uid = GameDB.get(id).user.userid;

			if(request.getParameter("process") != null && request.getParameter("process").compareTo("save") == 0)
			{
				//### Apply Modifications

				try
				{
					xml = request.getParameter("xml");
					XmlRole.Role role = XmlRole.fromXML(xml.getBytes("UTF-8"));
					role.base.id = id;
					XmlRole.putRoleToDB(id, role);
					message = "<font color=\"#00cc00\"><b>Character Data Saved</b></font>";
				}
				catch(Exception e)
				{
					message = "<font color=\"#ee0000\"><b>Saving Character Data Failed</b></font>";
				}
			}
			else
			{
				//### Get Values

				try
				{
					if(id > 31)
					{
						xml = new String(XmlRole.toXMLByteArray(XmlRole.getRoleFromDB(id)), "UTF-8");
					}
					else
					{
    						XmlRole.Role role = new XmlRole.Role();
						role.base = GameDB.getRoleBase(id);
						role.status = GameDB.getRoleStatus(id);
						role.pocket = GameDB.getRolePocket(id);
						role.equipment = GameDB.getRoleEquipment(id);
						role.storehouse = GameDB.getRoleStorehouse(id);
						role.task = GameDB.getRoleTask(id);
						if(role.task == null)
						{
							role.task = new GRoleTask();
						}
						xml = new String(XmlRole.toXMLByteArray(role), "UTF-8");
					}

				}
				catch(Exception e)
				{
					message = "<font color=\"#ee0000\"><b>Loading Character Data Failed</b></font>";
				}
			}
		}
		catch(Exception e)
		{
			message = "<font color=\"#ee0000\"><b>Invalid Character ID</b></font>";
		}
	}
%>

<table width="800" cellpadding="0" cellspacing="0" border="0">

	<tr>
		<td colspan="3">
			<br>
		</td>
	</tr>

	<tr>
		<th height="1" align="left" valign="middle" style="padding: 5px;">
			<font size="+1"><b>
			<%
				out.print("Character ID: " + id);
			%>
			</b></font>
		</th>
		<form action="index.jsp?page=role&show=details" method="post" style="margin: 0px;">
		<th height="1" colspan="2" align="right" valign="middle" style="padding: 5px;">
			<table cellpadding="0" cellspacing="2" border="0">
				<tr>
					<td width="1"><input name="ident" type="text" value="<% out.print(id); %>"style="width: 75px; text-align: center;"></input></td>
					<td width="1"><select name="type" style="width: 75px; text-align: center;"><option value="id">by ID</option><option value="name">by NAME</option></select></td>
					<td width="1"><input type="image" src="include/btn_goto.jpg" style="border: 0px;"></input></td>
				</tr>
			</table>
		</th>
		</form>
	</tr>

	<tr bgcolor="#f0f0f0">
		<td colspan="3" align="center" style="padding: 5px;">
			<%= message %>
		</td>
	</tr>

	<%
		if(allowed)
		{
			out.println("<tr><td colspan=\"3\" valign=\"middle\" style=\"border-bottom: 1px solid #cccccc;\">");
				out.println("<table width=\"100%\" cellpadding=\"0\" cellspacing=\"2\" border=\"0\"><tr>");
					out.println("<td align=\"left\">Switch to another Characters of this"); 
					try
					{
						Class.forName("com.mysql.jdbc.Driver").newInstance();
						Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
						Statement statement = connection.createStatement();
						ResultSet rs = statement.executeQuery("SELECT zoneid FROM point WHERE uid='" + uid + "'");
						rs.next();
						if(rs.getString("zoneid") != null)
						{
							out.print(" <font color=\"#00cc00\">currently Logged in Account</font>");
						}
						else
						{
							out.print(" <font color=\"#ee0000\">currently Logged out Account</font>");
						}
						rs.close();
						statement.close();
						connection.close();
					}
					catch(Exception e)
					{
						out.print(" <font color=\"#ee0000\">currently Logged out Account</font>");
					}

					out.print(" ID=" + uid + "</td>");
					out.println("<td width=\"164\"><form name=\"changechar\" action=\"index.jsp?page=role&show=details&type=id\" method=\"post\" style=\"margin: 0px;\">");
						out.println("<select name=\"ident\" onchange=\"document['changechar'].submit();\" style=\"width: 100%; text-align: center;\">");

							// Get all character of current userid
							DataVector dv = GameDB.getRolelist(uid);
							if(dv != null)
							{
								Iterator itr = dv.iterator();
								while(itr.hasNext())
								{
								       IntOctets ios = (IntOctets)itr.next();
								       int roleid = ios.m_int;
								       String rolename = ios.m_octets.getString();
									if(roleid == id)
									{
										out.println("<option value=\"" + roleid + "\" selected=\"selected\">" + rolename + "</option>");
									}
									else
									{
										out.println("<option value=\"" + roleid + "\">" + rolename + "</option>");
									}
								}	
							}

						out.println("</select>");
					out.println("</form></td>");
				out.println("</tr></table>");
			out.println("</td></tr>");

			out.println("<tr><td colspan=\"3\" valign=\"middle\" style=\"border-bottom: 1px solid #cccccc;\">");
				out.println("<table width=\"100%\" cellpadding=\"0\" cellspacing=\"2\" border=\"0\"><tr>");
					out.println("<td align=\"left\">Delete this Character</td>");
					out.println("<td width=\"1\"><a href=\"index.jsp?page=role&show=details&ident=" + id + "&type=id&process=delete\"><img src=\"include/btn_delete.jpg\" style=\"border: 0;\"></img></a></td>");
				out.println("</tr></table>");
			out.println("</td></tr>");
		}
	%>

	<tr>
		<td colspan="3" align="center" style="padding: 5px;">
			<%
				if(id > -1)
				{
					out.println("<a href=\"index.jsp?page=role&show=details&ident=" + id + "&type=id\"><img src=\"include/btn_gui.jpg\" border=\"0\"></img></a>");
				}
			%>
		</td>
	</tr>
	
	<form name="update" action="index.jsp?page=rolexml&ident=<% out.print(id); %>&process=save" method="post" style="margin: 0px;">

	<tr>
		<td colspan="3" align="left" valign="top">
			<textarea name="xml" rows="24" style="width: 100%;"><% out.print(xml); %></textarea>
		</td>
	</tr>

	<tr>
		<td colspan="3">
			<br>
		</td>
	</tr>

	<%
		if(allowed)
		{
			out.println("<tr>");
				out.println("<td colspan=\"3\" align=\"center\" style=\"border-top: 1px solid #cccccc; border-bottom: 1px solid #cccccc; padding: 2px;\"><input type=\"image\" src=\"include/btn_save.jpg\" style=\"border: 0;\"></input></td>");
			out.println("</tr>");
		}
	%>

	</form>
	
</table>