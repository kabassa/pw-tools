<%@page import="java.io.*"%>

<html>

<head>
	<link rel="shortcut icon" href="../../include/fav.ico">
	<link rel="stylesheet" type="text/css" href="../../include/style.css">
</head>

<body>

<table align="center" width="250" cellpadding="2" cellspacing="0" style="border: 1px solid #cccccc;">
	<tr><th align="center" style="padding: 5;"><font color="#ffffff"><b>LIST OF AVAILABLE PLUGINS</b></font></th></tr>
	<%
		File f = new File(request.getRealPath("addons"));
		String[] files = f.list();
		java.util.Arrays.sort(files);
		if (files.length > 0)
		{
			for (int i=0; i<files.length; i++)
			{
  				f = new File(request.getRealPath("addons") + "/" + files[i]);
  				if (f.isDirectory())
				{
					out.println("<tr><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><a href=\"../../index.jsp?plugin=" + files[i] + "\" target=\"_parent\">" + files[i] + "</a></td></tr>");
     				}
  			}
		}
	%>
	<tr><td align="center" style="border-top: 1px solid #cccccc;"><a href="http://pwadmin.codeplex.com/Thread/List.aspx">+ Search Plugins +</a></td></tr>
</table>

</body>

</html>