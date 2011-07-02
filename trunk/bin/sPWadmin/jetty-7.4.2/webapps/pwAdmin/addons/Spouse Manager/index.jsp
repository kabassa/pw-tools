<%@page import="protocol.*"%>
<%@page import="org.apache.commons.lang.StringEscapeUtils"%>
<%@include file="../../WEB-INF/.pwadminconf.jsp"%>

<%
	Boolean same_sex = false;
%>

<%
	String message = "<br>";
	boolean allowed = false;

	if(request.getSession().getAttribute("ssid") == null)
	{
		message = "<font color=\"#ee0000\"><b>Login to use Marriage...</b></font>";
	}
	else
	{
		allowed = true;
	}
%>

<%
	if(allowed && request.getParameter("process") != null)
	{
		if(request.getParameter("process").compareTo("marry") == 0)
		{
			if(request.getParameter("groom") != null && request.getParameter("bride") != null)
			{
				message = "";

				int groomid = GameDB.getRoleIdByName(request.getParameter("groom"));
				if(groomid < 0)
				{
					try
					{
						groomid = Integer.parseInt(request.getParameter("groom"));
					}
					catch(Exception e)
					{
						message += "<font color=\"#ee0000\"><b>Invalid Groom</b></font><br>";
					}
				}

				int brideid = GameDB.getRoleIdByName(request.getParameter("bride"));
				if(brideid < 0)
				{
					try
					{
						brideid = Integer.parseInt(request.getParameter("bride"));
					}
					catch(Exception e)
					{
						message += "<font color=\"#ee0000\"><b>Invalid Bride</b></font><br>";
					}
				}

				if(groomid > 31 && brideid > 31)
				{
					if(groomid != brideid)
					{
						XmlRole.Role groom = XmlRole.getRoleFromDB(groomid);
						XmlRole.Role bride = XmlRole.getRoleFromDB(brideid);

						if(groom != null && bride != null)
						{
							if(groom.base.reserved1 == 0 && bride.base.reserved1 == 0)
							{
								if(same_sex || groom.base.gender != bride.base.gender)
								{
									try
									{
										//role.base.id = groomid;

										groom.base.reserved1 = brideid;
										bride.base.reserved1 = groomid;

										XmlRole.putRoleToDB(groomid, groom);
										XmlRole.putRoleToDB(brideid, bride);

										message += "<font color=\"#00cc00\"><b>Characters Married</b></font>";
									}
									catch(Exception e)
									{
										message += "<font color=\"#ee0000\"><b>Marriage Failed</b></font>";
									}
								}
								else
								{
									message += "<font color=\"#ee0000\"><b>Same Gender</b></font>";
								}
							}
							else
							{
								message += "<font color=\"#ee0000\"><b>Groom or Bride already Married</b></font>";
							}
						}
						else
						{
							message += "<font color=\"#ee0000\"><b>Invalid Groom or Bride</b></font>";
						}
					}
					else
					{
						message += "<font color=\"#ee0000\"><b>Groom and Bride are Identical</b></font>";
					}
				}
				else
				{
					//message += "<font color=\"#ee0000\"><b>Invalid Spouse (ID < 32)</b></font>";
				}
			}
		}

		if(request.getParameter("process").compareTo("divorce") == 0)
		{
			if(request.getParameter("spouse") != null)
			{
				message = "";

				int groomid = GameDB.getRoleIdByName(request.getParameter("spouse"));
				int brideid = -1;

				if(groomid < 0)
				{
					try
					{
						groomid = Integer.parseInt(request.getParameter("spouse"));
					}
					catch(Exception e)
					{
						message += "<font color=\"#ee0000\"><b>Invalid Spouse</b></font><br>";
					}
				}

				if(groomid > 31)
				{
					XmlRole.Role groom = XmlRole.getRoleFromDB(groomid);

					if(groom != null)
					{
						if(groom.base.reserved1 != 0)
						{
							brideid = groom.base.reserved1;

							try
							{
								groom.base.reserved1 = 0;
								XmlRole.putRoleToDB(groomid, groom);
								message += "<font color=\"#00cc00\"><b>Groom Divorced</b></font>";
							}
							catch(Exception e)
							{
								message += "<font color=\"#ee0000\"><b>Groom Divorce Failed</b></font>";
							}
						}
						else
						{
							message += "<font color=\"#ee0000\"><b>Groom already Divorced</b></font>";
						}
					}
					else
					{
						message += "<font color=\"#ee0000\"><b>Invalid Groom</b></font>";
					}
				}
				else
				{
					//message += "<font color=\"#ee0000\"><b>Invalid Groom (ID < 32)</b></font>";
				}

				message += "<br>";

				if(brideid > 31)
				{
					XmlRole.Role bride = XmlRole.getRoleFromDB(brideid);
					if(bride != null)
					{
						if(bride.base.reserved1 == groomid)
						{
							try
							{
								bride.base.reserved1 = 0;
								XmlRole.putRoleToDB(brideid, bride);
								message += "<font color=\"#00cc00\"><b>Bride Divorced</b></font>";
							}
							catch(Exception e)
							{
								message += "<font color=\"#ee0000\"><b>Bride Divorce Failed</b></font>";
							}
						}
						else
						{
							message += "<font color=\"#ee0000\"><b>Bride not married with Groom</b></font>";
						}
					}
					else
					{
						message += "<font color=\"#ee0000\"><b>Invalid Bride</b></font>";
					}
				}
				else
				{
					//message += "<font color=\"#ee0000\"><b>Invalid Bride (ID < 32)</b></font>";
				}
			}
		}
	}
%>

<html>

<head>
	<link rel="shortcut icon" href="../../include/fav.ico">
	<link rel="stylesheet" type="text/css" href="../../include/style.css">
</head>

<body>

<table align="center" cellpadding="2" cellspacing="0" style="border: 1px solid #cccccc;">
	<tr>
		<th colspan="3" height="1" style="padding: 5;">
			<b>SPOUSE MANAGER*</b>
		</th>
	</tr>
	<tr>
		<td align="center" colspan="3" height="1">
			<% out.print(message); %>
		</td>
	</tr>

	<form action="index.jsp?process=marry" method="post">
	<tr bgcolor="#f0f0f0">
		<td align="center" colspan="3" height="1">
			<b>Marry</b>
		</td>
	</tr>
	<tr>
		<td align="left">Groom + Bride:</td>
		<td align="left">
			<input type="text" name="groom" style="width: 100px;"></input> + <input type="text" name="bride" style="width: 100px;">
		</input></td>
		<td align="center" style="padding: 5;">
			<input type="image" src="../../include/btn_submit.jpg" style="border: 0;"></input>
		</td>
	</tr>
	</form>

	<form action="index.jsp?process=divorce" method="post">
	<tr bgcolor="#f0f0f0">
		<td align="center" colspan="3" height="1">
			<b>Divorce</b>
		</td>
	</tr>
	<tr>
		<td align="left">Spouse:</td>
		<td align="left">
			<input type="text" name="spouse" style="width: 100%;"></input>
		</td>
		<td align="center" style="padding: 5;">
			<input type="image" src="../../include/btn_submit.jpg" style="border: 0;"></input>
		</td>
	</tr>
	</form>

</table>

<center>
	<br>
	*characters should be logged out
</center>

</body>

</html>