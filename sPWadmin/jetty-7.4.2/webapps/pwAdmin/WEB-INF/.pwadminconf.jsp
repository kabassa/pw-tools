<%@page import="java.io.*"%>

<%
//-------------------------------------------------------------------------------------------------------------------------
//------------------------------- SETTINGS --------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

	// pwadmin access password as md5 encrypted string
	// default password is root -> 63a9f0ea7bb98050796b649e85481845
	String iweb_password = "63a9f0ea7bb98050796b649e85481845";

	// connection settings to the mysql pw database
	String db_host = "localhost";
	String db_port = "3306";
	String db_user = "root";
	String db_password = "root";
	String db_database = "pw";

	// Type of your items database required for mapping id's to names
	// Options are my or pwi
	String item_labels = "pwi";

	// Absolute path to your PW-Server main directory (startscript, stopscript, /gamed)
	// requires a tailing slash
	String pw_server_path = "/PWServer/";

	// If you have hundreds of characters or heavy web acces through this site
	// It is recommend to turn the realtime character list feature off (false)
	// to prevent server from overload injected by character list generation
	boolean enable_character_list = true;

	String pw_server_name = "Your PW Servername";
	String pw_server_description = "+ Your server description here<br>+ 2 x 2.4 GHz, 2048 MB RAM, 100 MBit LAN<br>+ all dungeons open<br>+ tideborn nirvana weapons<br>+ World bosses";

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------- END SETTINGS ------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

	String pw_server_exp = "?";
	String pw_server_sp = "?";
	String pw_server_drop = "?";
	String pw_server_coins = "?";

	BufferedReader bfr = new BufferedReader(new FileReader(pw_server_path + "gamed/ptemplate.conf"));

	String row;
	while((row = bfr.readLine()) != null)
	{
		row = row.replaceAll("\\s", "");
		if(row.indexOf("exp_bonus=") != -1)
		{
			int pos = row.length();
			if(row.indexOf("#") != -1)
			{
				pos = row.indexOf("#");
			}
			pw_server_exp = row.substring(10, pos);
		}
		if(row.indexOf("sp_bonus=") != -1)
		{
			int pos = row.length();
			if(row.indexOf("#") != -1)
			{
				pos = row.indexOf("#");
			}
			pw_server_sp = row.substring(9, pos);
		}
		if(row.indexOf("drop_bonus=") != -1)
		{
			int pos = row.length();
			if(row.indexOf("#") != -1)
			{
				pos = row.indexOf("#");
			}
			pw_server_drop = row.substring(11, pos);
		}
		if(row.indexOf("money_bonus=") != -1)
		{
			int pos = row.length();
			if(row.indexOf("#") != -1)
			{
				pos = row.indexOf("#");
			}
			pw_server_coins = row.substring(12, pos);
		}
	}

	bfr.close();

	if(request.getSession().getAttribute("items") == null)
	{
		String[] items = new String[60001];

		try
		{
			bfr = new BufferedReader(new InputStreamReader(new FileInputStream(new File(request.getRealPath("/include/items") + "/default.dat")), "UTF8"));
			if(item_labels.compareTo("my") == 0)
			{
				bfr = new BufferedReader(new InputStreamReader(new FileInputStream(new File(request.getRealPath("/include/items") + "/my.dat")), "UTF8"));
			}
			if(item_labels.compareTo("pwi") == 0)
			{
				bfr = new BufferedReader(new InputStreamReader(new FileInputStream(new File(request.getRealPath("/include/items") + "/pwi.dat")), "UTF8"));
			}
			int count = 0;
			while((row = bfr.readLine()) != null && count < 60001)
			{
				items[count] = row;
				count++;
			}
			bfr.close();
		}
		catch(Exception e)
		{
		}

		request.getSession().setAttribute("items", items);
	}
%>
