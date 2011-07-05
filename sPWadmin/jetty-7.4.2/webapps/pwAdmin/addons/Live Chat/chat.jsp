<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="protocol.*"%>
<%@page import="org.apache.axis.encoding.Base64"%>
<%@include file="../../WEB-INF/.pwadminconf.jsp"%>

<%
	//------------------------------------
	//----------- SETTINGS ---------------
	//------------------------------------

	// number of last lines that are shown from the chat log file
	int show_lines = 20;
	// shows chat messages in the corresponding color
	boolean show_colors = true;
	// show a default smiley picture instead of the smiley code
	boolean show_smiley_picture = true;
	// set visibility filters
	boolean show_whisper = true;
	boolean show_faction = true;
	boolean show_rooms = true;
	boolean show_common = true;
	boolean show_world = true;
	boolean show_squad = true;
	boolean show_trade = true;

	//------------------------------------
	//--------- END SETTINGS -------------
	//------------------------------------
%>

<%
	boolean allowed = false;

	if(request.getSession().getAttribute("ssid") != null)
	{
		allowed = true;
	}
%>

<html>

<head>
	<meta http-equiv="refresh" content="5">
	<meta http-equiv="Content-Type" content="text/html; charset=GBK">
	<link rel="shortcut icon" href="../../include/fav.ico">
	<link rel="stylesheet" type="text/css" href="../../include/style.css">
</head>

<body background="#aaaaaa" style="margin: 0px;">

<table width="100%" cellpadding="2" cellspacing="0" border="0">

<%
if(allowed)
{
	Vector<String> lines = new Vector<String>();
	String line;
	String time;
	String sender;
	String recipient;
	String message;
	String debug;
	String color;

	BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(pw_server_path + "logs/world2.chat")));

	while((line = br.readLine()) != null)
	{
		lines.add(line);
	}

	br.close();

	int i = lines.size()-1;
	while(i>lines.size()-show_lines && i>=0)
	{
		line = lines.get(i);

		color = "<font color=\"#aaaaaa\">";
		time = line.substring(0, 19);
		line = line.substring(line.indexOf(": chat :")+9);
		sender = "*****";
		recipient = "*****";
		message = new String("*****");
		byte[] temp = Base64.decode(line.substring(line.indexOf("msg=")+4));

		// Whisper
		if(show_whisper && line.startsWith("Whisper"))
		{
			message = new String(temp, "UTF-16LE");
			sender = line.substring(line.indexOf("src=")+4);
			sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
			recipient = line.substring(line.indexOf("dst=")+4);
			recipient = "Player(" + recipient.substring(0, recipient.indexOf(" ")) + ")";
			color = "<font color=\"#ff00dd\">";
		}
		// Faction
		if(show_faction && line.startsWith("Guild"))
		{
			message = new String(temp, "UTF-16LE");
			sender = line.substring(line.indexOf("src=")+4);
			sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
			recipient = line.substring(line.indexOf("fid=")+4);
			recipient = "Faction(" + recipient.substring(0, recipient.indexOf(" ")) + ")";
			color = "<font color=\"#00fffc\">";
		}
		// Chatroom
		if(show_rooms && line.startsWith("Group"))
		{
			message = new String(temp, "UTF-16LE");
			sender = line.substring(line.indexOf("src=")+4);
			sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
			recipient = line.substring(line.indexOf("room=")+5);
			recipient = "Room(" + recipient.substring(0, recipient.indexOf(" ")) + ")";
			color = "<font color=\"#000000\">";
		}
		if(line.startsWith("Chat"))
		{
			// Common
			if(show_common && line.indexOf("chl=0") != -1)
			{
				message = new String(temp, "UTF-16LE");
				sender = line.substring(line.indexOf("src=")+4);
				sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
				recipient = "Common";
				color = "<font color=\"#000000\">";
			}
			// World
			if(show_world && line.indexOf("chl=1") != -1)
			{
				message = new String(temp, "UTF-16LE");
				sender = line.substring(line.indexOf("src=")+4);
				sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
				recipient = "World";
				color = "<font color=\"#ffee00\">";
			}
			// Squad
			if(show_squad && line.indexOf("chl=2") != -1)
			{
				message = new String(temp, "UTF-16LE");
				sender = line.substring(line.indexOf("src=")+4);
				sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
				recipient = "Squad";
				color = "<font color=\"#00ff00\">";
			}
			// Trade
			if(show_trade && line.indexOf("chl=7") != -1)
			{
				message = new String(temp, "UTF-16LE");
				sender = line.substring(line.indexOf("src=")+4);
				sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
				recipient = "Trade";
				color = "<font color=\"#ff8800\">";
			}
			// Broadcast
			if(line.indexOf("chl=9") != -1)
			{
				message = new String(temp, "UTF-16LE");
				sender = line.substring(line.indexOf("src=")+4);
				sender = "Player(" + sender.substring(0, sender.indexOf(" ")) + ")";
				recipient = "System";
				color = "<font color=\"#ff2200\">";
			}
		}
/*
		// Smileys causing errors... removing entries == 0 from byte array
		for(int n=0; n<temp.length; n++)
		{
			if(temp[n] != 0)
			{
				message += (char)(temp[n]);
			}
		}
*/
		if(show_smiley_picture)
		{
			message = message.replaceAll(".<\\d+>...<\\d+.\\d+>", "<img src=\"smiley.gif\" align=\"absmiddle\"></img>");
		}

		if(!show_colors)
		{
			color = "<font color=\"#000000\">";
		}

		out.print("<tr>");
		out.print("<td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"> time: </td>");
		out.print("<td style=\"border-bottom: 1px solid #cccccc;\"><b>" + time + "</b></td>");
		out.print("<td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"> from: </td>");
		out.print("<td style=\"border-bottom: 1px solid #cccccc;\"><b>" + color + sender + "</font></b></td>");
		out.print("<td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"> to: </td>");
		out.print("<td style=\"border-bottom: 1px solid #cccccc;\"><b>" + color + recipient + "</font></b></td>");
		out.print("<td align=\"center\" style=\"border-bottom: 1px solid #cccccc;\"> msg: </td>");
		out.print("<td style=\"border-bottom: 1px solid #cccccc;\"><b>" + color + message + "</font></b></td>");
		out.println("</tr>");

		i--;
	}
}
%>
</table>

</body>

</html>