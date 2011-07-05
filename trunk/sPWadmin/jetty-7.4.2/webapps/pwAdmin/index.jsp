<%@page import="java.io.*"%>

<html>

<head>
	<link rel="shortcut icon" href="include/fav.ico">
	<link rel="stylesheet" type="text/css" href="include/style.css">
	<link rel="stylesheet" type="text/css" href="include/menu.css">
	<script type="text/javascript" src="include/menu.js"></script>
</head>

<body style="margin: 10;">

<table height="100%" align="center" cellpadding="0" cellspacing="0" border="0">

	<tr height="1">
		<td colspan="3">
			<img src="include/banner.jpg">
		</td>
	</tr>

	<tr height="1">
		<td align="left" style="padding-left: 8px; padding-right: 8px;"><img src="include/logo.jpg" border="0"></img></td>
		<td align="left">
			<table cellpadding="3" cellspacing="0" border="0">
				<tr>
					<td align="left" valign="middle">

						<a href="index.jsp?page=account"><b>
							<%
								if(request.getParameter("page") != null && request.getParameter("page").compareTo("account") == 0)
								{
									out.print("<font color=\"#444444\">ACCOUNTS</font>");
								}
								else
								{
									out.print("<font color=\"#aaaaaa\">ACCOUNTS</font>");
								}
							%>
						</b></a>
					</td>
					<td>
						|
					</td>
					<td>
						<a href="index.jsp?page=role"><b>
							<%
								if(request.getParameter("page") != null && (request.getParameter("page").compareTo("role") == 0 || request.getParameter("page").compareTo("rolexml") == 0))
								{
									out.print("<font color=\"#444444\">CHARACTERS</font>");
								}
								else
								{
									out.print("<font color=\"#aaaaaa\">CHARACTERS</font>");
								}
							%>
						</b></a>
					</td>
					<td>
						|
					</td>
					<td>
						<a href="index.jsp?page=server"><b>
							<%
								if(request.getParameter("page") != null && request.getParameter("page").compareTo("server") == 0)
								{
									out.print("<font color=\"#444444\">SERVER CONFIGURATION</font>");
								}
								else
								{
									out.print("<font color=\"#aaaaaa\">SERVER CONFIGURATION</font>");
								}
							%>
						</b></a>
					</td>
					<td>
						|
					</td>
					<td>
						<a href="index.jsp?page=serverctrl"><b>
							<%
								if(request.getParameter("page") != null && request.getParameter("page").compareTo("serverctrl") == 0)
								{
									out.print("<font color=\"#444444\">SERVER CONTROL</font>");
								}
								else
								{
									out.print("<font color=\"#aaaaaa\">SERVER CONTROL</font>");
								}
							%>
						</b></a>
					</td>
					<td>
						|
					</td>
					<td>
						<ul id="menu">
							<li onmouseover="javascript:show_submenu('sub_plugins');" onmouseout="javascript:hide_submenu('sub_plugins');">
								<a href="index.jsp?plugin"><b><font color="#aaaaaa">&#9660;ADDONS</font></b></a>
								<ul id="sub_plugins">
									<%
										File f = new File(request.getRealPath("addons"));
										String[] files = f.list();
										java.util.Arrays.sort(files);
										if (files.length > 0)
										{
											for (int i=0; i<files.length; i++)
											{
  												f = new File(request.getRealPath("addons") + "/" + files[i]);
  												if(f.isDirectory())
												{
													out.print("<li><a href=\"index.jsp?plugin=" + files[i] + "\"> <b>&#9679; </b>" + files[i] + "</a></li>");
     												}
  											}
										}
									%><li style="border-bottom: 1px solid #cccccc;"><a href="http://pwadmin.codeplex.com/Thread/List.aspx">Search Plugins...</a></li>
								</ul>
							</li>
						</ul>
					</td>
				</tr>
			</table>
		</td>
		<td align="right" valign="middle" style="padding-right: 8px;"><%pageContext.include("login.jsp");%></td>
	</tr>

	<tr height="1">
		<td colspan="3">
			<br>
		</td>
	</tr>

	<tr>
		<td align="center" valign="top" colspan="3">
			<%
				if(request.getParameter("page") != null)
				{
					if(request.getParameter("page").compareTo("account") == 0)
					{
						pageContext.include("account.jsp");
					}
					if(request.getParameter("page").compareTo("role") == 0)
					{
						pageContext.include("role.jsp");
					}
					if(request.getParameter("page").compareTo("rolexml") == 0)
					{
						pageContext.include("rolexml.jsp");
					}
					if(request.getParameter("page").compareTo("server") == 0)
					{
						pageContext.include("server.jsp");
					}
					if(request.getParameter("page").compareTo("serverctrl") == 0)
					{
						pageContext.include("serverctrl.jsp");
					}
					if(request.getParameter("page").compareTo("login") == 0)
					{
						pageContext.include("login.jsp");
					}
				}
				if(request.getParameter("plugin") != null)
				{
					out.print("<iframe src=\"addons/" + request.getParameter("plugin") + "/\" width=\"100%\" height=\"100%\" frameborder=\"0\"></iframe>");
				}
			%>
		</td>
	</tr>
</table>

</body>

</html>