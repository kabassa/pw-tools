<%@page import="java.sql.*"%>
<%@page import="protocol.*"%>
<%@page import="java.io.*"%>
<%@page import="java.text.*"%>
<%@page import="java.util.*"%>
<%@page import="java.util.Iterator"%>
<%@page import="com.goldhuman.Common.Octets"%>
<%@page import="com.goldhuman.IO.Protocol.Rpc.Data.DataVector"%>
<%@page import="org.apache.commons.lang.StringEscapeUtils"%>
<%@include file="WEB-INF/.pwadminconf.jsp"%>

<div align="left" id="sqltip" style="background: #ffffff; border: 1px solid #000000; white-space: nowrap; visibility: hidden; padding: 5px; position: absolute;">
	<b><u>Synchronize GameDB with MySQL Role Table</u></b><br>
	<b>&#9679; </b>Make sure Perfect World Server is running<br>
	<b>&#9679; </b>Make sure maps are stopped (inconsistence & lag)<br>
	<b>&#9679; </b>Process may take a while depending on role amount
</div>

<script type="text/javascript">

	function move_tip(id, event)
	{
		document.getElementById(id).style.left = event.clientX -5 + document.body.scrollLeft;
		document.getElementById(id).style.top = event.clientY + 25 + document.body.scrollTop;
	}

	function show_tip(id)
	{
		document.getElementById(id).style.visibility = "visible";
	}

	function hide_tip(id)
	{
		document.getElementById(id).style.visibility = "hidden";
	}

	function select_item(itemname, itemgroup, itemindex, itemid, itemguid1, itemguid2, itemmask, itemproctype, itempos, itemcount, itemcountmax, itemexpire, itemdata)
	{
		document.getElementById("itemname").href = "http://www.pwdatabase.com/items/" + itemid;
		document.getElementById("itemname").innerHTML = itemname;
		if(itemgroup == "equipment")
		{
			document.update.itemgroup[0].selected = "1";
		}
		if(itemgroup == "inventory")
		{
			document.update.itemgroup[1].selected = "1";
		}
		if(itemgroup == "storage")
		{
			document.update.itemgroup[2].selected = "1";
		}
		document.update.itemindex.value = itemindex;
		document.update.itemid.value = itemid;
		document.update.itemguid1.value = itemguid1;
		document.update.itemguid2.value = itemguid2;
		document.update.itemmask.value = itemmask;
		document.update.itemproctype.value = itemproctype;
		document.update.itempos.value = itempos;
		document.update.itemcount.value = itemcount;
		document.update.itemcountmax.value = itemcountmax;
		document.update.itemexpire.value = itemexpire;
		document.update.itemdata.value = itemdata;
	}

</script>

<%!
	HashMap<Integer, Object[]> loadFactions(String path)
	{
		HashMap<Integer, Object[]> factions = new HashMap<Integer, Object[]>();

		try
		{
			String command = path + "gamedbd/gamedbd " + path + "gamedbd/gamesys.conf listfaction";
			File working_directory = new File(path + "gamedbd/");
			Process p = Runtime.getRuntime().exec(command, null, working_directory);
			BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line;
			String[] values;
			// skip header line
			input.readLine();
			while((line = input.readLine()) != null)
			{
				values = line.split(",");
				factions.put(Integer.parseInt(values[0]), new Object[]{values[1], Integer.parseInt(values[2]), Integer.parseInt(values[5])});
			}
		}
		catch(Exception e)
		{
			// error loading factions
		}

		return factions;
	}
%>

<%!
	HashMap<Integer, Integer[]> loadFactionMembers(String path)
	{
		HashMap<Integer, Integer[]> members = new HashMap<Integer, Integer[]>();

		try
		{
			String command = path + "gamedbd/gamedbd " + path + "gamedbd/gamesys.conf listfactionuser";
			File working_directory = new File(path + "gamedbd/");
			Process p = Runtime.getRuntime().exec(command, null, working_directory);
			BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line;
			String[] values;
			// skip header line
			input.readLine();
			while((line = input.readLine()) != null)
			{
				values = line.split(",");
				members.put(Integer.parseInt(values[0]), new Integer[]{Integer.parseInt(values[2]), Integer.parseInt(values[4])});
			}
		}
		catch(Exception e)
		{
			// error loading members
		}

		return members;
	}
%>

<%!
	HashMap<Integer, String> loadFactionDomains(String path)
	{
		HashMap<Integer, String> domains = new HashMap<Integer, String>();

		try
		{
			String command = path + "gamedbd/gamedbd " + path + "gamedbd/gamesys.conf listcity";
			File working_directory = new File(path + "gamedbd/");
			Process p = Runtime.getRuntime().exec(command, null, working_directory);
			BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line;
			String[] values;
			// skip header line
			Integer faction;
			input.readLine();
			while((line = input.readLine()) != null)
			{
				values = line.split(",");
				faction = Integer.parseInt(values[2]);
				if(faction > 0)
				{
					if(domains.containsKey(faction))
					{
						domains.put(faction, domains.get(faction) + ";" + values[0]);
					}
					else
					{
						domains.put(faction, values[0]);
					}
				}
			}
		}
		catch(Exception e)
		{
			// error loading domains
		}

		return domains;
	}
%>

<%!
	HashMap<Integer, Integer[]> loadPvP(String logfile)
	{
		HashMap<Integer, Integer[]> pvp_table = new HashMap<Integer, Integer[]>();

		try
		{
			String line;
			int victim;
			int attacker;

			Integer[] pvp_entry;

			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(logfile)));

			while((line = br.readLine()) != null)
			{
				if(line.indexOf(":die:") > -1 && line.indexOf("type=2") > -1) // i.e. "type=258" -> killed by player, "type=4" -> killed by mob
				{
					victim = Integer.parseInt(line.substring(line.indexOf("roleid=")+7, line.indexOf(":type=")));
					attacker = Integer.parseInt(line.substring(line.indexOf("attacker=")+9));

					if(pvp_table.containsKey(victim))
					{
						pvp_entry = pvp_table.get(victim);
						pvp_entry[1]++;
						pvp_table.put(victim, pvp_entry);
					}
					else
					{
						pvp_table.put(victim, new Integer[]{0, 1});
					}

					if(pvp_table.containsKey(attacker))
					{
						pvp_entry = pvp_table.get(attacker);
						pvp_entry[0]++;
						pvp_table.put(attacker, pvp_entry);
					}
					else
					{
						pvp_table.put(attacker, new Integer[]{1, 0});
					}
				}
			}

			br.close();
		}
		catch(Exception e)
		{
			// Error loading file
		}

		return pvp_table;
	}
%>

<%!
 	String toHexString(byte[] x)
  	{
    		StringBuffer sb = new StringBuffer(x.length * 2);
    		for (int i = 0; i < x.length; ++i)
    		{
      			byte n = x[i];
      			int nibble = n >> 4 & 0xF;
      			sb.append((char)((nibble >= 10) ? 97 + nibble - 10 : 48 + nibble));
      			nibble = n & 0xF;
      			sb.append((char)((nibble >= 10) ? 97 + nibble - 10 : 48 + nibble));
    		}
    		return sb.toString();
  	}
%>

<%!
	byte[] hextoByteArray(String x)
  	{
    		if (x.length() < 2)
		{
      			return new byte[0];
		}
    		if (x.length() % 2 != 0)
		{
      			System.err.println("hextoByteArray error! hex size=" + Integer.toString(x.length()));
    		}
    		byte[] rb = new byte[x.length() / 2];
   		for (int i = 0; i < rb.length; ++i)
    		{
      			rb[i] = 0;

      			int n = x.charAt(i + i);
      			if ((n >= 48) && (n <= 57))
        			n -= 48;
      			else
				if ((n >= 97) && (n <= 102))
        				n = n - 97 + 10;
      					rb[i] = (byte)(rb[i] | n << 4 & 0xF0);

      					n = x.charAt(i + i + 1);
      					if ((n >= 48) && (n <= 57))
        					n -= 48;
      					else
					if ((n >= 97) && (n <= 102))
        					n = n - 97 + 10;
      				rb[i] = (byte)(rb[i] | n & 0xF);
    	}
    	return rb;
  }
%>

<%!
	String int2occupation(String mode, int c)
	{
		if(mode.compareTo("pwi") == 0)
		{
	    		switch(c)
	    		{
				case 0:	return "Blademaster";
				case 1:	return "Wizard";
				case 2:	return "Psychic";
				case 3:	return "Venomancer";
				case 4:	return "Barbarian";
				case 5:	return "Assassin";
				case 6:	return "Archer";
				case 7:	return "Cleric";
	    		}
		}
		else
		{
	    		switch(c)
	    		{
				case 0:	return "Warrior";
				case 1:	return "Mage";
				case 2:	return "Monk";
				case 3:	return "WereFox";
				case 4:	return "WereBeast";
				case 5:	return "Genie";
				case 6:	return "Archer";
				case 7:	return "Priest";
	    		}
		}
		return "unknown";
	}
%>

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
	String name = "<br>";
	String level = "";
	String reputation = "";
	String health = "";
	String mana = "";
	String exp = "";
	String spirit = "";
	String[] cultivation = new String[33];
	String vigor = "<option value=\"0\"></option>";
	String race = "";
	String occupation = "";
	String gender = "";
	String spouse = "";
	String faction = "";
	String attribute = "";
	String constitution = "";
	String intelligence = "";
	String strength = "";
	String agility = "";
	String patk_min = "";
	String patk_max = "";
	String pdef = "";
	String matk_min = "";
	String matk_max = "";
	String mdef = "";

	String status = "";
	String creationtime = "";
	String deletiontime = "";
	String lastlogin = "";
	String world = "";
	String coordinateX = "";
	String coordinateY = "";
	String coordinateZ = "";
	String cubiamount = "";
	String cubipurchased = "";
	String cubibought = "";
	String cubiused = "";
	String cubisold = "";
	String pkmode = "";
	String pkinvadertime = "";
	String pkpariahtime = "";

	int breakcol = 6;

	String equipment = "<option value=\"0\"></option>";
	String inventory = "<option value=\"0\"></option>";
	String storage = "<option value=\"0\"></option>";
	String pocket_coins = "";
	String storehouse_coins = "";

	if(allowed && request.getParameter("process") != null && request.getParameter("process").compareTo("sqlsync") == 0)
	{
		try
		{
			// { faction-id , [(String)name , (Integer)level, (Integer)member-count] }
			HashMap<Integer, Object[]> factions = loadFactions(pw_server_path);

			// { role-id , [faction-id , faction-rank] }
			HashMap<Integer, Integer[]> faction_members = loadFactionMembers(pw_server_path);

			// { faction-id , "domain_1;domain_2;domain_3" }
			HashMap<Integer, String> faction_domains = loadFactionDomains(pw_server_path);

			// { role-id , [kills , deaths] }
			HashMap<Integer, Integer[]> pvp = loadPvP(pw_server_path + "logs/world2.formatlog");

			Class.forName("com.mysql.jdbc.Driver").newInstance();
			Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
			Statement statement = connection.createStatement();
			Statement update = connection.createStatement();
			ResultSet rs;

			// drop table and re-create it (autoincrement reset)
			//statement.execute("TRUNCATE TABLE roles");
			statement.executeUpdate("DROP TABLE IF EXISTS roles");
			statement.executeUpdate
			(
				"CREATE TABLE roles(" +
				"account_id int(11) NOT NULL, " +
				"role_id int(11) NOT NULL, " +
				"role_name varchar(32) NOT NULL, " +
				"role_level smallint(6) NOT NULL, " +
				"role_race tinyint(4) NOT NULL, " +
				"role_occupation tinyint(4) NOT NULL, " +
				"role_gender tinyint(4) NOT NULL, " +
				"role_spouse int(11) NOT NULL, " +
				"faction_id int(11) NOT NULL, " +
				"faction_name varchar(32) NOT NULL, " +
				"faction_level int(11) NOT NULL, " +
				"faction_domains varchar(132) NOT NULL, " +
				"role_faction_rank int(11) NOT NULL, " +
				"pvp_time int(11) NOT NULL, " +
				"pvp_kills int(11) NOT NULL, " +
				"pvp_deads int(11) NOT NULL" +
				") " +
				"ENGINE=InnoDB DEFAULT CHARSET=utf8;"
			);

			rs = (statement.executeQuery("SELECT ID FROM users"));

			// go through all account id's and fetch roles + properties
			Integer roleid;
			RoleBean chr;
			String rolename;
			Object[] faction_entry;
			Integer[] faction_member_entry;
			String domains;
			Integer[] pvp_entry;
			while(rs.next())
			{
				// Get all character of current userid
				DataVector dv = GameDB.getRolelist(rs.getInt("ID"));
				if(dv != null)
				{
					Iterator itr = dv.iterator();
					while(itr.hasNext())
					{
						IntOctets ios = (IntOctets)itr.next();
						chr = GameDB.get(ios.m_int);
						roleid = new Integer(ios.m_int);
						rolename = StringEscapeUtils.escapeHtml(chr.base.name.getString());

						if(pvp.containsKey(roleid))
						{
							pvp_entry = pvp.get(roleid);
						}
						else
						{
							pvp_entry = new Integer[]{0, 0};
						}

						if(faction_members.containsKey(roleid))
						{
							faction_member_entry = faction_members.get(roleid);
						}
						else
						{
							faction_member_entry = new Integer[]{0, 0};
						}

						if(factions.containsKey(faction_member_entry[0]))
						{
							faction_entry = factions.get(faction_member_entry[0]);
							faction_entry[0] = new String();
						}
						else
						{
							faction_entry = new Object[]{new String(), (Integer)0, (Integer)0};
						}

						if(faction_domains.containsKey(faction_member_entry[0]))
						{
							domains = faction_domains.get(faction_member_entry[0]);
						}
						else
						{
							domains = "";
						}

						// insert row into table
						update.executeUpdate("INSERT INTO roles VALUES (" + chr.user.userid + ", " + roleid + ", '" + rolename + "', " + chr.status.level + ", " + chr.base.race + ", " + chr.base.cls + ", " + chr.base.gender + ", " + chr.base.reserved1 + ", " + faction_member_entry[0] + ", '" + (String)(faction_entry[0]) + "', " + (Integer)(faction_entry[1]) + ", '" + domains + "', " + faction_member_entry[1] + ", " + chr.status.invader_time + ", " + pvp_entry[0] + ", " + pvp_entry[1] + ")");
					}
				}
			}

			update.close();
			rs.close();
			statement.close();
			connection.close();

			message = "<font color=\"#00cc00\"><b>Roles Imported to MySQL Table</b></font>";
		}
		catch(Exception e)
		{
			message = "<font color=\"#ee0000\"><b>Importing Roles to MySQL Failed</b></font>";
		}
	}

	if(request.getParameter("show") != null && request.getParameter("show").compareTo("details") == 0)
	{
		//### Get Values

		try
		{
			RoleBean character;
			if(request.getParameter("type") != null && request.getParameter("type").compareTo("id") == 0)
			{
				id = Integer.parseInt(request.getParameter("ident"));
			}
			else
			{
				id = GameDB.getRoleIdByName(request.getParameter("ident"));
				//id =  GameDB.getRoleIdByName(new String(request.getParameter("ident").getBytes(), "GBK"));
			}
			character = GameDB.get(id);
			uid = character.user.userid;

			//### Apply Modifications

			if(request.getParameter("process") != null && allowed)
			{
				if(request.getParameter("process").compareTo("save") == 0)
				{
					message = "";
					boolean error = false;

					try
					{
						character.status.worldtag = Integer.parseInt(request.getParameter("world"));
					}
					catch(Exception e)
					{
						message += "Invalid Value for World ID<br>";
						error = true;
					}
					try
					{
						character.status.posx = Float.valueOf(request.getParameter("coordinateX").trim()).floatValue();
					}
					catch(Exception e)
					{
						message += "Invalid Value for Position X<br>";
						error = true;
					}
					try
					{
						character.status.posz = Float.valueOf(request.getParameter("coordinateZ").trim()).floatValue();
					}
					catch(Exception e)
					{
						message += "Invalid Value for Position Z<br>";
						error = true;
					}
					try
					{
						character.status.posy = Float.valueOf(request.getParameter("coordinateY").trim()).floatValue();
					}
					catch(Exception e)
					{
						message += "Invalid Value for Altitude<br>";
						error = true;
					}
					try
					{
						character.status.reputation = Integer.parseInt(request.getParameter("reputation"));
					}
					catch(Exception e)
					{
						message += "Invalid Value for Reputation<br>";
						error = true;
					}
					try
					{
						character.status.exp = Integer.parseInt(request.getParameter("exp"));
					}
					catch(Exception e)
					{
						message += "Invalid Value for EXP<br>";
						error = true;
					}
					try
					{
						character.status.sp = Integer.parseInt(request.getParameter("sp"));
					}
					catch(Exception e)
					{
						message += "Invalid Value for SP<br>";
						error = true;
					}
					try
					{
						character.status.level2 = Integer.parseInt(request.getParameter("cultivation"));
					}
					catch(Exception e)
					{
						message += "Invalid Value for Cultivation<br>";
						error = true;
					}
					try
					{
						character.ep.max_ap = Integer.parseInt(request.getParameter("vigor"));
					}
					catch(Exception e)
					{
						message += "Invalid Value for Vigor Points<br>";
						error = true;
					}
					try
					{
						character.pocket.money = Integer.parseInt(request.getParameter("pocketcoins"));
						if(character.pocket.money > 200000000)
						{
							character.pocket.money = 200000000;
						}
					}
					catch(Exception e)
					{
						message += "Invalid Value for Coins (Inventory)<br>";
						error = true;
					}
					try
					{
						character.storehouse.money = Integer.parseInt(request.getParameter("storehousecoins"));
						if(character.storehouse.money > 200000000)
						{
							character.storehouse.money = 200000000;
						}
					}
					catch(Exception e)
					{
						message += "Invalid Value for Coins (Storage)<br>";
						error = true;
					}

					try
					{
						if(request.getParameter("itemgroup") != "" && request.getParameter("itemindex") != "")
						{
							String group = request.getParameter("itemgroup");
							int index = Integer.parseInt(request.getParameter("itemindex"));

							if(request.getParameter("itemaction").equals("remove"))
							{
								if(group.equals("equipment"))
								{
									character.equipment.removeElementAt(index);
								}
								if(group.equals("inventory"))
								{
									character.pocket.items.removeElementAt(index);
								}
								if(group.equals("storage"))
								{
									character.storehouse.items.removeElementAt(index);
								}
							}
							else
							{
								GRoleInventory gri = new GRoleInventory();

								gri.id = Integer.parseInt(request.getParameter("itemid"));
								gri.guid1 = Integer.parseInt(request.getParameter("itemguid1"));
								gri.guid2 = Integer.parseInt(request.getParameter("itemguid2"));
								gri.mask = Integer.parseInt(request.getParameter("itemmask"));
								gri.proctype = Integer.parseInt(request.getParameter("itemproctype"));
								gri.pos = Integer.parseInt(request.getParameter("itempos"));
								gri.count = Integer.parseInt(request.getParameter("itemcount"));
								gri.max_count = Integer.parseInt(request.getParameter("itemcountmax"));
								gri.expire_date = Integer.parseInt(request.getParameter("itemexpire"));
								gri.data = new Octets(hextoByteArray(request.getParameter("itemdata")));

								if(request.getParameter("itemaction").equals("add"))
								{
									if(group.equals("equipment"))
									{
										character.equipment.addElement(gri);
									}
									if(group.equals("inventory"))
									{
										character.pocket.items.addElement(gri);
									}
									if(group.equals("storage"))
									{
										character.storehouse.items.addElement(gri);
									}
								}
								if(request.getParameter("itemaction").equals("edit"))
								{
									if(group.equals("equipment"))
									{
										character.equipment.setElementAt(gri, index);
									}
									if(group.equals("inventory"))
									{
										character.pocket.items.setElementAt(gri, index);
									}
									if(group.equals("storage"))
									{
										character.storehouse.items.setElementAt(gri, index);
									}
								}
							}
						}
					}
					catch(Exception e)
					{
						message += "Invalid Values for Selected Item<br>";
						error = true;
					}

					if(error)
					{
						message += "<font color=\"#ee0000\"><b>Check the Fields for incorrect Data</b></font>";
					}
					else
					{
						try
						{
							GameDB.update(character);
							message = "<font color=\"#00cc00\"><b>Character Data Saved</b></font>";
						}
						catch(Exception e)
						{
							message = "<font color=\"#ee0000\"><b>Saving Character Data Failed</b></font>";
						}
					}
				}

				if(request.getParameter("process").compareTo("rename") == 0)
				{
					try
					{
						String newname = request.getParameter("rolename");
						if(newname.length() < 1 || newname.length() > 9)
						{
							message = "<font color=\"#ee0000\"><b>Only 1-9 Characters</b></font>";
						}
						else
						{
							String alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
							boolean check = true;
							char c;
							for(int i=0; i<newname.length(); i++)
							{
								c = newname.charAt(i);
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
								if(GameDB.renameRole(id, character.base.name.getString(), newname) == 0)
								{
									// Register the new name
									//UniquenameDB.PostCreateRole((byte)1, 1, id, newname);
									// Unregister the old name / don't work for the origin name :-(
									UniquenameDB.PostDeleteRole(0, id, character.base.name.getString());
									message = "<font color=\"#00cc00\"><b>Character Renamed</b></font>";
								}
								else
								{
									message = "<font color=\"#ee0000\"><b>Another Character with this Name exists</b></font>";
								}
							}
						}
					}
					catch(Exception e)
					{
						message = "<font color=\"#ee0000\"><b>Renaming Character Failed</b></font>";
					}
				}

				if(request.getParameter("process").compareTo("delete") == 0)
				{
					try
					{
						if(GameDB.deleteRolePermanent(id))
						{
							// Make the name available
							UniquenameDB.PostDeleteRole(0, id, character.base.name.getString());
							character = GameDB.get(id);
							message = "<font color=\"#00cc00\"><b>Character Deleted</b></font>";
						}
						else
						{
							message = "<font color=\"#ee0000\"><b>Deleting Character Failed</b></font>";
						}
					}
					catch(Exception e)
					{
						message = "<font color=\"#ee0000\"><b>Deleting Character Failed</b></font>";
					}
				}
			}

			//### End Apply

			name = StringEscapeUtils.escapeHtml(character.base.name.getString());
			level = Integer.toString(character.status.level);
			reputation = Integer.toString(character.status.reputation);
			health = Integer.toString(character.ep.max_hp);
			mana = Integer.toString(character.ep.max_mp);
			exp = Integer.toString(character.status.exp);
			spirit = Integer.toString(character.status.sp);

			cultivation = new String[32+1];
			for(int i=0; i<cultivation.length; i++)
			{
				if(i == character.status.level2)
				{
					cultivation[i] = " selected=\"selected\"";
				}
				else
				{
					cultivation[i] = "";
				}
			}

			switch(character.ep.max_ap)
			{
				case 99:	vigor = "<option value=\"0\">000</option><option value=\"99\" selected=\"selected\">099</option><option value=\"199\">199</option><option value=\"299\">299</option><option value=\"399\">399</option>"; break;
				case 199:	vigor = "<option value=\"0\">000</option><option value=\"99\">099</option><option value=\"199\" selected=\"selected\">199</option><option value=\"299\">299</option><option value=\"399\">399</option>"; break;
				case 299:	vigor = "<option value=\"0\">000</option><option value=\"99\">099</option><option value=\"199\">199</option><option value=\"299\" selected=\"selected\">299</option><option value=\"399\">399</option>"; break;
				case 399:	vigor = "<option value=\"0\">000</option><option value=\"99\">099</option><option value=\"199\">199</option><option value=\"299\">299</option><option value=\"399\" selected=\"selected\">399</option>"; break;
				default:	vigor = "<option value=\"0\" selected=\"selected\">000</option><option value=\"99\">099</option><option value=\"199\">199</option><option value=\"299\">299</option><option value=\"399\">399</option>"; break;
			}

			switch(character.base.race)
			{
				case 0:	race = "Human"; break;
				case 1:	race = "Beast"; break;
				case 2:	race = "Beast"; break;
				case 3:	race = "Tideborn"; break;
				case 4:	race = "Elf"; break;
				case 5:	race = "Elf"; break;
				default:	race = "Unknown";
			}

			occupation = int2occupation(item_labels, character.base.cls);

			gender = (character.base.gender == 0) ? "Male" : "Female";

			if(character.base.reserved1 != 0)
			{
				try
				{
					spouse = StringEscapeUtils.escapeHtml(GameDB.get(character.base.reserved1).base.name.getString());
				}
				catch(Exception e)
				{
					spouse = "INVALID";
				}
			}

			faction = "";

			attribute = Integer.toString(character.status.pp);
			constitution = Integer.toString(character.ep.vitality);
			intelligence = Integer.toString(character.ep.energy);
			strength = Integer.toString(character.ep.strength);
			agility = Integer.toString(character.ep.agility);
			patk_min = Integer.toString(character.ep.damage_low);
			patk_max = Integer.toString(character.ep.damage_high);
			pdef = Integer.toString(character.ep.defense);
			matk_min = Integer.toString(character.ep.damage_magic_low);
			matk_max = Integer.toString(character.ep.damage_magic_high);
			mdef = Integer.toString(character.ep.resistance[0]);

			status = Integer.toString(character.base.status);
	 		creationtime = (character.base.create_time <= 0) ? "-" : (new SimpleDateFormat("yyyy-MM-dd - HH:mm:ss")).format(new java.util.Date(1000*(long)character.base.create_time));
	 		deletiontime = (character.base.delete_time <= 0) ? "-" : (new SimpleDateFormat("yyyy-MM-dd - HH:mm:ss")).format(new java.util.Date(1000*(long)character.base.delete_time));
			lastlogin = (character.base.lastlogin_time <= 0) ? "-" : (new SimpleDateFormat("yyyy-MM-dd - HH:mm:ss")).format(new java.util.Date(1000*(long)character.base.lastlogin_time));
	 		world = Integer.toString(character.status.worldtag);
			coordinateX = (new DecimalFormat("#.##")).format(character.status.posx);
			coordinateY = (new DecimalFormat("#.##")).format(character.status.posy);
			coordinateZ = (new DecimalFormat("#.##")).format(character.status.posz);
			cubiamount = (new DecimalFormat("#.##")).format((double)character.user.cash/100);
			cubipurchased = (new DecimalFormat("#.##")).format((double)character.user.cash_add/100);
			cubibought = (new DecimalFormat("#.##")).format((double)character.user.cash_buy/100);;
			cubiused = (new DecimalFormat("#.##")).format((double)character.user.cash_used/100);;
			cubisold = (new DecimalFormat("#.##")).format((double)character.user.cash_sell/100);;
			pkmode = (character.status.invader_state == 0) ? "Off" : "On";
			pkinvadertime = Integer.toString(character.status.invader_time);
			pkpariahtime = Integer.toString(character.status.pariah_time);

			pocket_coins = Integer.toString(character.pocket.money);
			storehouse_coins = Integer.toString(character.storehouse.money);

			String[] item_db = (String[])request.getSession().getAttribute("items");

			equipment = "";
			String icon = "";
			if(character.equipment != null)
			{
				Iterator itr = character.equipment.iterator();
				GRoleInventory gre;
				String label;
				int br = 0;
				while(itr.hasNext())
				{
					if(br%breakcol == 0)
					{
						equipment += "<tr>";
					}
					gre = (GRoleInventory)itr.next();
					try
					{
						label = item_db[gre.id];
					}
					catch(Exception e)
					{
						label = "<span class=\\'item_color0\\'>Item not found</span>";
					}
					if((new File(request.getRealPath("/include/icons/" + gre.id + ".gif"))).exists())
					{
						icon = "./include/icons/" + gre.id + ".gif";
					}
					else
					{
						icon = "./include/icons/0.gif";
					}
					equipment += "<td align=\"center\" onclick=\"select_item('" + label + "', 'equipment', '" + br + "', '" + gre.id + "', '" + gre.guid1 + "', '" + gre.guid2 + "', '" + gre.mask + "', '" + gre.proctype + "', '" + gre.pos + "', '" + gre.count + "', '" + gre.max_count + "', '" + gre.expire_date + "', '" + toHexString(gre.data.getBytes()) + "');\"><img title=\"" + gre.id + "\" src=\"" + icon + "\"></img></td>";
					br++;
					if(br%breakcol == 0)
					{
						equipment += "</tr>";
					}
				}
				if(br%breakcol != 0)
				{
					// Fill Rest
					while(br%breakcol != 0)
					{
						equipment += "<td><br></td>";
						br++;
					}
					equipment += "</tr>";
				}
			}

			inventory = "";
			if(character.pocket.items != null)
			{
				Iterator itr = character.pocket.items.iterator();
				GRoleInventory grp;
				String label;
				int br = 0;
				while(itr.hasNext())
				{
					if(br%breakcol == 0)
					{
						inventory += "<tr>";
					}
					grp = (GRoleInventory)itr.next();
					try
					{
						label = item_db[grp.id];
					}
					catch(Exception e)
					{
						label = "<span class=\\'item_color0\\'>Item not found</span>";
					}
					if((new File(request.getRealPath("/include/icons/" + grp.id + ".gif"))).exists())
					{
						icon = "./include/icons/" + grp.id + ".gif";
					}
					else
					{
						icon = "./include/icons/0.gif";
					}
					inventory += "<td align=\"center\" onclick=\"select_item('" + label + "', 'inventory', '" + br + "', '" + grp.id + "', '" + grp.guid1 + "', '" + grp.guid2 + "', '" + grp.mask + "', '" + grp.proctype + "', '" + grp.pos + "', '" + grp.count + "', '" + grp.max_count + "', '" + grp.expire_date + "', '" + toHexString(grp.data.getBytes()) + "');\"><img title=\"" + grp.id + "\" src=\"" + icon + "\"></img></td>";
					br++;
					if(br%breakcol == 0)
					{
						inventory += "</tr>";
					}
				}
				if(br%breakcol != 0)
				{
					// Fill Rest
					while(br%breakcol != 0)
					{
						inventory += "<td><br></td>";
						br++;
					}
					inventory += "</tr>";
				}
			}

			storage = "";
			if(character.storehouse.items != null)
			{
				Iterator itr = character.storehouse.items.iterator();
				GRoleInventory grs;
				String label;
				int br = 0;
				while(itr.hasNext())
				{
					if(br%breakcol == 0)
					{
						storage += "<tr>";
					}
					grs = (GRoleInventory)itr.next();
					try
					{
						label = item_db[grs.id];
					}
					catch(Exception e)
					{
						label = "<span class=\\'item_color0\\'>Item not found</span>";
					}
					if((new File(request.getRealPath("/include/icons/" + grs.id + ".gif"))).exists())
					{
						icon = "./include/icons/" + grs.id + ".gif";
					}
					else
					{
						icon = "./include/icons/0.gif";
					}
					storage += "<td align=\"center\" onclick=\"select_item('" + label + "', 'storage', '" + br + "', '" + grs.id + "', '" + grs.guid1 + "', '" + grs.guid2 + "', '" + grs.mask + "', '" + grs.proctype + "', '" + grs.pos + "', '" + grs.count + "', '" + grs.max_count + "', '" + grs.expire_date + "', '" + toHexString(grs.data.getBytes()) + "');\"><img title=\"" + grs.id + "\" src=\"" + icon + "\"></img></td>";
					br++;
					if(br%breakcol == 0)
					{
						storage += "</tr>";
					}
				}
				if(br%breakcol != 0)
				{
					// Fill Rest
					while(br%breakcol != 0)
					{
						storage += "<td><br></td>";
						br++;
					}
					storage += "</tr>";
				}
			}
		}
		catch(Exception e)
		{
			message = "<font color=\"#ee0000\"><b>Loading Character Data Failed</b></font>";
		}

		//### End Get
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
				if(request.getParameter("show") != null && request.getParameter("show").compareTo("details") == 0)
				{
					out.print("Character ID: " + id);
				}
				else
				{
					out.print("Character List:");
				}
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
		if(request.getParameter("show") != null && request.getParameter("show").compareTo("details") == 0 && allowed)
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
			//out.println("<tr><td colspan=\"3\" valign=\"middle\" style=\"border-bottom: 1px solid #cccccc;\">");
			//	out.println("<form action=\"index.jsp?page=role&show=details&ident=" + id + "&type=id&process=rename\" method=\"post\" style=\"margin: 0px;\"><table width=\"100%\" cellpadding=\"0\" cellspacing=\"2\" border=\"0\"><tr>");
			//		out.println("<td align=\"left\">Rename Character</td>");
			//		out.println("<td width=\"1\"><input name=\"rolename\" type=\"text\" value=\"NEW NAME\" style=\"width: 100px; text-align: center;\"></input></td>");
			//		out.println("<td width=\"1\"><input type=\"image\" src=\"include/btn_rename.jpg\" style=\"border: 0;\"></input></td>");
			//	out.println("</tr></table></form>");
			//out.println("</td></tr>");
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
				if(allowed && id > -1)
				{
					out.println("<a href=\"index.jsp?page=rolexml&ident=" + id + "\"><img src=\"include/btn_xml.jpg\" border=\"0\"></img></a>");
				}
				else
				{
					out.println("<br>");
				}
			%>
		</td>
	</tr>

	<%
		if(request.getParameter("show") != null && request.getParameter("show").compareTo("details") == 0)
		{
			out.println("<form name=\"update\" action=\"index.jsp?page=role&show=details&ident=" + id + "&type=id&process=save\" method=\"post\" style=\"margin: 0px;\">");
			out.println("<tr>");

				out.println("<td width=\"33%\" align=\"left\" valign=\"top\">");
				if(allowed)
				{
					out.println("<table width=\"250\" cellpadding=\"2\" cellspacing=\"0\" style=\"border: 1px solid #cccccc;\">");
					out.println("<tr><th colspan=\"2\" style=\"padding: 5;\">CHARACTER INFO</th></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"2\" align=\"center\"><b>General</b></td></tr>");
					out.println("<tr><td><b>Status:</b></td><td>" + status + "</td></tr>");
					out.println("<tr><td><b>Creation Time:</b></td><td>" + creationtime + "</td></tr>");
					out.println("<tr><td><b>Deletion Time:</b></td><td>" + deletiontime + "</td></tr>");
					out.println("<tr><td><b>Last Login:</b></td><td>" + lastlogin + "</td></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"2\" align=\"center\"><b>Location</b></td></tr>");
					out.println("<tr><td><b>World ID:</b></td><td><input name=\"world\" type=\"text\" value=\"" + world + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Position X:</b></td><td><input name=\"coordinateX\" type=\"text\" value=\"" + coordinateX + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Position Z:</b></td><td><input name=\"coordinateZ\" type=\"text\" value=\"" + coordinateZ + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Altitude:</b></td><td><input name=\"coordinateY\" type=\"text\" value=\"" + coordinateY + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"2\" align=\"center\"><b>Purchase</b></td></tr>");
					out.println("<tr><td><b>Cubi Balance:</b></td><td>" + cubiamount + "</td></tr>");
					out.println("<tr><td><b>Cubi Purchased:</b></td><td>" + cubipurchased + "</td></tr>");
					out.println("<tr><td><b>Cubi Bought:</b></td><td>" + cubibought + "</td></tr>");
					out.println("<tr><td><b>Cubi Used:</b></td><td>" + cubiused + "</td></tr>");
					out.println("<tr><td><b>Cubi Sold:</b></td><td>" + cubisold + "</td></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"2\" align=\"center\"><b>PK</b></td></tr>");
					out.println("<tr><td><b>PK Mode:</b></td><td>" + pkmode + "</td></tr>");
					out.println("<tr><td><b>Invader Time:</b></td><td>" + pkinvadertime + "</td></tr>");
					out.println("<tr><td><b>Pariah Time:</b></td><td>" + pkpariahtime + "</td></tr>");
					out.println("</table>");
				}
				out.println("</td>");

				out.println("<td width=\"34%\" align=\"center\" valign=\"top\">");
					out.println("<table width=\"250\" cellpadding=\"2\" cellspacing=\"0\" style=\"border: 1px solid #cccccc;\">");
					out.println("<tr><th colspan=\"4\" style=\"padding: 5;\">CHARACTER PROPERTIES</th></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"4\" align=\"center\"><font color=\"#000000\"><b>" + name + "</b></font></td></tr>");
					out.println("<tr><td><b>Level:</b></td><td>" + level + "</td><td><b>Reputation:</b></td><td><input name=\"reputation\" type=\"text\" value=\"" + reputation + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr><td width=\"50\"><b>HP:</b></td><td width=\"50\">" + health + "</td><td><b width=\"50\">EXP:</b></td><td><input name=\"exp\" type=\"text\" value=\"" + exp + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>MP:</b></td><td>" + mana + "</td><td><b>SP:</b></td><td><input name=\"sp\" type=\"text\" value=\"" + spirit + "\" style=\"width: 100%; text-align: center;\"></input></td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Cultivation:</b></td><td colspan=\"2\"><select name=\"cultivation\" style=\"width: 100%;\"><option value=\"0\" " + cultivation[0] + ">0 - Inchoation</option><option value=\"1\" " + cultivation[1] + ">9 - Autoscopy</option><option value=\"2\" " + cultivation[2] + ">19 - Transform</option><option value=\"3\" " + cultivation[3] + ">29 - Naissance</option><option value=\"4\" " + cultivation[4] + ">39 - Reborn</option><option value=\"5\" " + cultivation[5] + ">49 - Vigilance</option><option value=\"6\" " + cultivation[6] + ">59 - Doom</option><option value=\"7\" " + cultivation[7] + ">69 - Disengage</option><option value=\"8\" " + cultivation[8] + ">79 - Nirvana</option><option value=\"20\" " + cultivation[20] + ">89 - Prime Immortal</option><option value=\"30\" " + cultivation[30] + ">89 - Daiman Baresark</option><option value=\"21\" " + cultivation[21] + ">99 - Pure Immortal</option><option value=\"31\" " + cultivation[31] + ">99 - Daimon Saint</option><option value=\"22\" " + cultivation[22] + ">109 - Ether Immortal</option><option value=\"32\" " + cultivation[32] + ">109 - Daimon Elder</option></select></td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Vigor Points:</b></td><td colspan=\"2\"><select name=\"vigor\" style=\"width: 100%;\">" + vigor + "</select></td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Race:</b></td><td colspan=\"2\">" + race + "</td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Occupation:</b></td><td colspan=\"2\">" + occupation + "</td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Gender:</b></td><td colspan=\"2\">" + gender + "</td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Spouse:</b></td><td colspan=\"2\"><a href=\"index.jsp?page=role&show=details&ident=" + spouse + "&type=ident\"><u>" + spouse + "</u></a></td></tr>");
					out.println("<tr><td colspan=\"2\"><b>Faction:</b></td><td colspan=\"2\">" + faction + "</td></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"4\" align=\"center\"><b>Attributes</b></td></tr>");
					out.println("<tr><td colspan=\"1\"><b>Points:</b></td><td colspan=\"3\">" + attribute + "</td></tr>");
					out.println("<tr><td><b>CON:</b></td><td>" + constitution + "</td><td><b>INT:</td><td>" + intelligence + "</b></td></tr>");
					out.println("<tr><td><b>STR:</b></td><td>" + strength + "</td><td><b>AGI:</td><td>" + agility + "</b></td></tr>");
					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"4\" align=\"center\"><b>Base Stats</b></td></tr>");
					out.println("<tr><td><b>P-Def:</b></td><td>" + pdef + "</td><td><b>P-Atk:</b></td><td>" + patk_min + " - " + patk_max + "</td></tr>");
					out.println("<tr><td><b>M-Def:</b></td><td>" + mdef + "</td><td><b>M-Atk:</b></td><td>" + matk_min + " - " + matk_max + "</td></tr>");
					out.println("</table>");
				out.println("</td>");

				out.println("<td width=\"33%\" align=\"right\" valign=\"top\">");
				if(allowed)
				{
					out.println("<table width=\"250\" cellpadding=\"2\" cellspacing=\"0\" style=\"border: 1px solid #cccccc;\">");
					out.println("<tr><th colspan=\"4\" style=\"padding: 5;\">CHARACTER ITEMS</th></tr>");
					out.println("<tr><td align=\"center\" colspan=\"4\" style=\"border: 0px solid #cccccc;\"><div style=\"height: 130px; overflow: auto;\">");
						out.println("<table width=\"100%\" cellpadding=\"2\"cellspacing=\"0\" border=\"0\">");
						out.println("<tr><td align=\"center\" colspan=\"" + breakcol + "\" style=\"padding: 5px;\"><b>Equipment</b></td></tr>" + equipment);
						out.println("<tr><td align=\"center\" colspan=\"" + breakcol + "\" style=\"padding: 5px;\"><b>Inventory</b></td></tr>" + inventory);
						out.println("<tr><td align=\"center\" colspan=\"" + breakcol + "\" style=\"padding: 5px;\"><b>Storehouse</b></td></tr>" + storage);
						out.println("</table>");
					out.println("</div></td></tr>");

					out.println("<tr><th colspan=\"4\" style=\"padding: 5;\"><b><a href=\"#\" id=\"itemname\"><br></a><b></th></tr>");

					out.println("<input name=\"itemindex\" type=\"hidden\"></input>");

					out.println("<tr><td><b>Item ID:</b></td><td colspan=\"3\"><input name=\"itemid\" type=\"text\" style=\"width: 65px; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Group:</b></td><td><select name=\"itemgroup\" style=\"width: 65px;\"><option value=\"equipment\">Equipment</option><option value=\"inventory\" selected=\"selected\">Inventory</option><option value=\"storage\">Storage</option></select></td><td><b>Action:</b></td><td align=\"right\"><select name=\"itemaction\" style=\"width: 65px;\"><option value=\"edit\">Edit</option><option value=\"remove\">Delete</option><option value=\"add\">Add New</option></select></td></tr>");
					out.println("<tr><td><b>GuID 1:</b></td><td><input name=\"itemguid1\" type=\"text\" style=\"width: 65px; text-align: center;\"></input></td><td><b>GuID 2:</b></td><td align=\"right\"><input name=\"itemguid2\" type=\"text\" style=\"width: 65px; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Proctype:</b></td><td><input name=\"itemproctype\" type=\"text\" style=\"width: 65px; text-align: center;\"></input></td><td><b>Mask:</b></td><td align=\"right\"><input name=\"itemmask\" type=\"text\" style=\"width: 65px; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Position:</b></td><td><input type=\"text\" name=\"itempos\" style=\"width: 65px; text-align: center;\"></input></td><td><b>Expire:</b></td><td align=\"right\"><input type=\"text\" name=\"itemexpire\" style=\"width: 65px; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>Stacked:</b></td><td><input type=\"text\" name=\"itemcount\" style=\"width: 65px; text-align: center;\"></input></td><td><b>Max:</b></td><td align=\"right\"><input type=\"text\" name=\"itemcountmax\" style=\"width: 65px; text-align: center;\"></input></td></tr>");
					out.println("<tr><td><b>HexData:</b></td><td colspan=\"3\"><input type=\"text\" name=\"itemdata\" style=\"width: 100%;\"></input></td></tr>");

					out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"4\" align=\"center\"><b>Coins</b></td></tr>");
					out.println("<tr><td><b>Pocket:</b></td><td><input name=\"pocketcoins\" type=\"text\" value=\"" + pocket_coins + "\" style=\"width: 65px; text-align: center;\"></input></td><td><b>Store:</b></td><td align=\"right\"><input name=\"storehousecoins\" type=\"text\" value=\"" + storehouse_coins + "\" style=\"width: 65px; text-align: center;\"></input></td></tr>");

					out.println("</table>");		
				}
				out.println("</td>");

			out.println("</tr><tr><td colspan=\"3\"><br></td></tr>");

			if(allowed)
			{
				out.println("<tr>");
					out.println("<td colspan=\"3\" align=\"center\" style=\"border-top: 1px solid #cccccc; border-bottom: 1px solid #cccccc; padding: 2px;\"><input type=\"image\" src=\"include/btn_save.jpg\" style=\"border: 0;\"></input></td>");
				out.println("</tr>");
			}

			out.println("</form>");
		}
		else
		{
			out.println("<tr><td colspan=\"3\" align=\"center\" valign=\"top\">");
				out.println("<table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\"><tr><td align=\"center\" valign=\"top\">");
					out.println("<table width=\"350\" cellpadding=\"2\" cellspacing=\"0\" style=\"border: 1px solid #cccccc;\">");
						if(allowed)
						{
							out.println("<tr><th></th><th align=\"center\" style=\"padding: 5;\">PLAYERS</th><th align=\"right\" style=\"padding: 5;\"><a href=\"index.jsp?page=role&process=sqlsync\"><img src=\"include/btn_sync.png\" border=\"0\" onmouseover=\"javascript:show_tip('sqltip');\" onmousemove=\"javascript:move_tip('sqltip', event);\" onmouseout=\"javascript:hide_tip('sqltip');\"></img></a></th></tr>");
						}
						else
						{
							out.println("<tr><th align=\"center\" colspan=\"3\" style=\"padding: 5;\">PLAYERS</th></tr>");
						}
						out.println("<tr bgcolor=\"#f0f0f0\"><td><b><a href=\"index.jsp?page=role&order=role_name\">Name</a></b></td><td><b><a href=\"index.jsp?page=role&order=role_occupation\">Occupation</a></b></td><td align=\"center\"><b><a href=\"index.jsp?page=role&order=role_level\">Level</a></b></td></tr>");
						if(enable_character_list)
						{
							//try
							//{
// realtime character list is replaced by MySQL role table
/*
								Class.forName("com.mysql.jdbc.Driver").newInstance();
								Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
								Statement statement = connection.createStatement();
								ResultSet rs;
								rs = (statement.executeQuery("SELECT ID FROM users"));
								// Get registered users
								while(rs.next())
								{
									// Get all character of current userid
									DataVector dv = GameDB.getRolelist(rs.getInt("ID"));
									if(dv != null)
									{
										Iterator itr = dv.iterator();
										while(itr.hasNext())
										{
								       		IntOctets ios = (IntOctets)itr.next();
								       		int roleid = ios.m_int;
											RoleBean chr = GameDB.get(roleid);
								       		//String rolename = ios.m_octets.getString();
											String rolename = StringEscapeUtils.escapeHtml(chr.base.name.getString());
								     	  		//int rolelevel = GameDB.getRoleStatus(roleid).level;
								     	  		int rolelevel = chr.status.level;
								      	 		//String roleoccupation = int2occupation(item_labels, GameDB.get(roleid).base.cls);
								      	 		String roleoccupation = int2occupation(item_labels, chr.base.cls);
											out.println("<tr><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=" + roleid + "&type=id\">" + rolename + "</a></td><td style=\"border-top: 1px solid #cccccc\">" + roleoccupation + "</td><td align=\"center\" style=\"border-top: 1px solid #cccccc\">" + rolelevel + "</td></tr>");
										}	
									}
								}
*/
								Class.forName("com.mysql.jdbc.Driver").newInstance();
								Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
								Statement statement = connection.createStatement();
								ResultSet rs;

								String sort = "";

								if(request.getParameter("order") != null && request.getParameter("order").compareTo("role_level") == 0)
								{
									sort = " DESC";
								}

								rs = statement.executeQuery("SELECT * FROM roles ORDER BY " + request.getParameter("order") + sort);
			
								while(rs.next())
								{
								       int roleid = rs.getInt("role_id");
									String rolename = StringEscapeUtils.escapeHtml(rs.getString("role_name"));
									int rolelevel = rs.getInt("role_level");
									String roleoccupation = int2occupation(item_labels, rs.getInt("role_occupation"));
									out.println("<tr><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=" + roleid + "&type=id\">" + rolename + "</a></td><td style=\"border-top: 1px solid #cccccc\">" + roleoccupation + "</td><td align=\"center\" style=\"border-top: 1px solid #cccccc\">" + rolelevel + "</td></tr>");
								}

								rs.close();
								statement.close();
								connection.close();
							//}
							//catch(Exception e)
							//{
							//	out.println("<tr><td align=\"center\" colspan=\"3\" style=\"border-top: 1px solid #cccccc\"><font color=\"#ee0000\"><b>Connection to MySQL Database Failed</b></font></td></tr>");
							//}
						}
						else
						{
							out.println("<tr><td align=\"center\" colspan=\"3\" style=\"border-top: 1px solid #cccccc\"><font color=\"#ee0000\"><b>Character List is Disabled</b></font></td></tr>");
						}
					out.println("</table>");
				out.println("<td align=\"center\" valign=\"top\">");
					if(allowed)
					{
						out.println("<table width=\"350\" cellpadding=\"2\" cellspacing=\"0\" style=\"border: 1px solid #cccccc;\">");
						if(item_labels.compareTo("pwi") == 0)
						{
							out.println("<tr><th align=\"center\" colspan=\"2\" style=\"padding: 5;\">TEMPLATES</th></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=16&type=id\">TEMPLATE BLADEMASTER MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Blademaster</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=17&type=id\">TEMPLATE BLADEMASTER FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Blademaster</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=18&type=id\">TEMPLATE WIZARD MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Wizard</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=19&type=id\">TEMPLATE WIZARD FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Wizard</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=20&type=id\">TEMPLATE PSYCHIC MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Psychic</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=21&type=id\">TEMPLATE PSYCHIC FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Psychic</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=22&type=id\">TEMPLATE VENOMANCER MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Venomancer</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=23&type=id\">TEMPLATE VENOMANCER FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Venomancer</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=24&type=id\">TEMPLATE BARBARIAN MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Barbarian</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=25&type=id\">TEMPLATE BARBARIAN FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Barbarian</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=26&type=id\">TEMPLATE ASSASSIN MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Assassin</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=27&type=id\">TEMPLATE ASSASSIN FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Assassin</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=28&type=id\">TEMPLATE ARCHER MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Archer</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=29&type=id\">TEMPLATE ARCHER FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Archer</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=30&type=id\">TEMPLATE CLERIC MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Cleric</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=31&type=id\">TEMPLATE CLERIC FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Cleric</td></tr>");
						}
						else
						{
							out.println("<tr><th align=\"center\" colspan=\"2\" style=\"padding: 5;\">TEMPLATES</th></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=16&type=id\">TEMPLATE WR MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Warrior</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=17&type=id\">TEMPLATE WR FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Warrior</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=18&type=id\">TEMPLATE MG MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Mage</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=19&type=id\">TEMPLATE MG FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Mage</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=20&type=id\">TEMPLATE MK MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Monk</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=21&type=id\">TEMPLATE MK FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Monk</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=22&type=id\">TEMPLATE WF MALE</a></td><td style=\"border-top: 1px solid #cccccc\">WereFox</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=23&type=id\">TEMPLATE WF FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">WereFox</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=24&type=id\">TEMPLATE WB MALE</a></td><td style=\"border-top: 1px solid #cccccc\">WereBeast</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=25&type=id\">TEMPLATE WB FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">WereBeast</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=26&type=id\">TEMPLATE GN MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Genie</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=27&type=id\">TEMPLATE GN FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Genie</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=28&type=id\">TEMPLATE EA MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Archer</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=29&type=id\">TEMPLATE EA FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Archer</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=30&type=id\">TEMPLATE EP MALE</a></td><td style=\"border-top: 1px solid #cccccc\">Priest</td></tr>");
							out.println("<tr bgcolor=\"#f0f0f0\"><td style=\"border-top: 1px solid #cccccc\"><a href=\"index.jsp?page=role&show=details&ident=31&type=id\">TEMPLATE EP FEMALE</a></td><td style=\"border-top: 1px solid #cccccc\">Priest</td></tr>");
						}
						out.println("</table></td>");
					}
				out.println("</td></tr></table>");
			out.println("</td></tr>");
		}
	%>
</table>