<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="java.text.SimpleDateFormat"%>
<%@page import="org.apache.axis.encoding.Base64"%>
<%@include file="../../WEB-INF/.pwadminconf.jsp"%>

<%
	String message = "<br>";
	boolean allowed = false;

	if(request.getSession().getAttribute("ssid") == null)
	{
		message = "<font color=\"#ee0000\"><b>Login to use Live Chat...</b></font>";
	}
	else
	{
		allowed = true;
	}
%>

<%
	if(request.getParameter("process") != null && allowed)
	{
		if(request.getParameter("process").compareTo("delete") == 0)
		{
			try
			{
				FileWriter fw = new FileWriter(pw_server_path + "logs/world2.chat");
				fw.close();
				message = "<font color=\"#00cc00\"><b>Chat Log File Cleared</b></font>";
			}
			catch(Exception e)
			{
				message = "<font color=\"#ee0000\"><b>Clearing Chat Log File Failed</b></font>";
			}
		}

		if(request.getParameter("broadcast") != null)
		{
			String broadcast = request.getParameter("broadcast");

			if(protocol.DeliveryDB.broadcast((byte)9, -1, broadcast))
			{
				message = "<font color=\"#00cc00\"><b>Message Send</b></font>";
				try
				{
					BufferedWriter bw = new BufferedWriter(new FileWriter(pw_server_path + "logs/world2.chat", true));
					bw.write((new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(Calendar.getInstance().getTime())) + " pwserver glinkd-0: chat : Chat: src=-1 chl=9 msg=" + Base64.encode(broadcast.getBytes("UTF-16LE")) + "\n") ;
					bw.close();
				}
				catch(Exception e)
				{
					message += "<br><font color=\"#ee0000\">Appending Message to Log File Failed</font>";
				}
			}
			else
			{
				message = "<font color=\"#ee0000\"><b>Sending Message Failed</b></font>";
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

<table width="100%" height="100%" cellpadding="2" cellspacing="0" style="border: 1px solid #cccccc;">
	<tr>
		<th height="1" colspan="2" style="padding: 5;">
			<b>LIVE CHAT</b>
		</th>
	</tr>
	<tr bgcolor="#f0f0f0">
		<td colspan="2" align="center" height="1" width="100%">
			<% out.print(message); %>
		</td>
	</tr>
	<tr bgcolor="#f0f0f0">
		<form action="index.jsp?process=broadcast" method="post">
		<td height="1" width="100%">
			<input type="text" name="broadcast" value="Broadcast System Message" style="width: 100%; text-align: left;"></input>
		</td>
		<td height="1">
			<input type="image" src="../../include/btn_submit.jpg" style="border: 0;"></input>
		</td>
		</form>
	</tr>
	<tr>
		<td colspan="2" style="border-top: 1px solid #cccccc; border-bottom: 1px solid #cccccc;  padding: 0;">
			<iframe src="chat.jsp" width="100%" height="100%" frameborder="0" style="margin: 0px;"></iframe>
		</td>
	</tr>
	<tr bgcolor="#f0f0f0">
		<td colspan="2" align="center" height="1">
			<a href="index.jsp?process=delete" title="Clear The Entire Chat Log File"><img src="../../include/btn_delete.jpg" style="border: 0;"></img></a>
		</td>
	</tr>
</table>

</body>

</html>