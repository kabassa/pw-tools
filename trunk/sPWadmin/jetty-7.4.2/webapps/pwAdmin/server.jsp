<%@page import="protocol.*"%>
<%@include file="WEB-INF/.pwadminconf.jsp"%>

<%
	boolean allowed = false;

	if(request.getSession().getAttribute("ssid") == null)
	{
		out.println("<p align=\"right\"><font color=\"#ee0000\"><b>Login for Server configuration...</b></font></p>");
	}
	else
	{
		allowed = true;
	}
%>

<table width="800" cellpadding="0" cellspacing="0" border="0">

<tr>
	<td colspan="2">
		<br>
	</td>
</tr>

<tr>
<td align="center" valign="top">

	<table cellpadding="2" cellspacing="0" style="border: 1px solid #cccccc;">
	<tr>
		<th colspan="2" align="center" style="padding: 5;">
			<font color="#ffffff"><b><%out.println(pw_server_name);%></b></font>
		</th>
	</tr>
	<tr>
		<td colspan="2" align="left" valign="middle" style="border-bottom: 1px solid #cccccc;">
			<iframe src="status.jsp" width="120" height="32" scrolling="no" frameborder="no" style="border: 0;"></iframe>
		</td>
	</tr>
	<tr>
		<td>
			EXP Rate:
		</td>
		<td>
			<%out.println(pw_server_exp);%>
		</td>
	</tr>
	<tr>
		<td>
			SP Rate:
		</td>
		<td>
			<%out.println(pw_server_sp);%>
		</td>
	</tr>
	<tr>
		<td>
			Drop Rate:
		</td>
		<td>
			<%out.println(pw_server_drop);%>
		</td>
	</tr>
	<tr>
		<td>
			Coins Rate:
		</td>
		<td>
			<%out.println(pw_server_coins);%>
		</td>
	</tr>
	<tr>
		<td colspan="2" style="border-top: 1px solid #cccccc;">
			<%out.println(pw_server_description);%>
		</td>
	</tr>
	</table>

</td>

<td align="center" valign="top">
<%
	if(allowed)
	{
		String message = new String("<br>");

		// ### Apply Changes ###

			if(request.getParameter("process") != null)
			{
				if(request.getParameter("process").compareTo("save") == 0)
				{
					message = "<font color=\"#00cc00\"><b>Saved All Values<b></font>";

					try
					{
						int max = Integer.parseInt(request.getParameter("users_max"));
						if(DeliveryDB.SetMaxOnlineNum(max, max))
						{
							//message += "<font color=\"#00cc00\"><b>Saved Maximum User Number<b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving Maximum User Number Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving Maximum User Number Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						int lambda_value = Integer.parseInt(request.getParameter("lambda_value"));
						if(DeliveryDB.GMSetLambda(lambda_value))
						{
							//message += "<font color=\"#00cc00\"><b>Saved Lambda Value<b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving Lambda Value Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving Lambda Value Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String dblexp_on = request.getParameter("dblexp_on");
						if(dblexp_on == null){dblexp_on = "false";}
						if(DeliveryDB.GMSetDoubleExp(dblexp_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved Double Experience Points</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving Double Experience Points Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving Double Experience Points Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String dblsp_on = request.getParameter("dblsp_on");
						if(dblsp_on == null){dblsp_on = "false";}
						if(DeliveryDB.GMSetDoubleSP(dblsp_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved Double Skill Points</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving Double Skill Points Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving Double Skill Points Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String dbldrop_on = request.getParameter("dbldrop_on");
						if(dbldrop_on == null){dbldrop_on = "false";}
						if(DeliveryDB.GMSetDoubleObject(dbldrop_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved Double Droprate</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving Double Droprate Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving Double Droprate Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String dblcoin_on = request.getParameter("dblcoin_on");
						if(dblcoin_on == null){dblcoin_on = "false";}
						if(DeliveryDB.GMSetDoubleMoney(dblcoin_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved Double Coins</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving Double Coins Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving Double Coins Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String nomail_on = request.getParameter("nomail_on");
						if(nomail_on == null){nomail_on = "false";}
						if(DeliveryDB.GMSetNoMail(nomail_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved No-Mail Mode</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving No-Mail Mode Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving No-Mail Mode Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String nofaction_on = request.getParameter("nofaction_on");
						if(nofaction_on == null){nofaction_on = "false";}
						if(DeliveryDB.GMSetNoFaction(nofaction_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved No-Faction Mode</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving No-Faction Mode Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving No-Faction Mode Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String notrade_on = request.getParameter("notrade_on");
						if(notrade_on == null){notrade_on = "false";}
						if(DeliveryDB.GMSetNoTrade(notrade_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved No-Trade Mode</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving No-Trade Mode Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving No-Trade Mode Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String noshop_on = request.getParameter("noshop_on");
						if(noshop_on == null){noshop_on = "false";}
						if(DeliveryDB.GMSetNoSellPoint(noshop_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved No-PlayerShop Mode</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving No-PlayerShop Mode Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving No-PlayerShop Mode Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}

					try
					{
						String noauction_on = request.getParameter("noauction_on");
						if(noauction_on == null){noauction_on = "false";}
						if(DeliveryDB.GMSetNoAuction(noauction_on.equals("true")))
						{
							//message += "<font color=\"#00cc00\"><b>Saved No-Auction Mode</b></font><br>";
						}
						else
						{
							//message += "<font color=\"#ee0000\"><b>Saving No-Auction Mode Failed</b></font><br>";
							message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
						}
					}
					catch(Exception e)
					{
						//message += "<font color=\"#ee0000\"><b>Saving No-Auction Mode Failed</b></font><br>";
						message = "<font color=\"#ee0000\"><b>Saving of one or more Values Failed<b></font>";
					}
				}
			}

		// ### END Apply Changes ###

		// ### Get Current Values ###

			String users_max = new String("");
			String users_vmax = new String("");
			String users_online = new String("");
			{
				Integer[] user = new Integer[3];
				DeliveryDB.GetMaxOnlineNum(user);
				if(user[0] == null){user[0] = new Integer(-1);}
				if(user[1] == null){user[1] = new Integer(-1);}
				if(user[2] == null){user[2] = new Integer(-1);}
				users_max = user[0].toString();
				users_vmax = user[1].toString();
				users_online = user[2].toString();
			}

			String lambda = new String("");
			{
				lambda = Integer.toString(DeliveryDB.GMGetLambda());
			}

			String double_exp = new String("");
			{
				byte status = DeliveryDB.GMGetDoubleExp();
				if(status == (byte)1){double_exp = "checked=\"checked\"";}
			}

			String double_sp = new String("");
			{
				byte status = DeliveryDB.GMGetDoubleSP();
				if(status == (byte)1){double_sp = "checked=\"checked\"";}
			}

			String double_drop = new String("");
			{
				byte status = DeliveryDB.GMGetDoubleObject();
				if(status == (byte)1){double_drop = "checked=\"checked\"";}
			}

			String double_coin = new String("");
			{
				byte status = DeliveryDB.GMGetDoubleMoney();
				if(status == (byte)1){double_coin = "checked=\"checked\"";}
			}

			String mail = new String("");
			{
				byte status = DeliveryDB.GMGetNoMail();
				if(status == (byte)1){mail = "checked=\"checked\"";}
			}

			String faction = new String("");
			{
				byte status = DeliveryDB.GMGetNoFaction();
				if(status == (byte)1){faction = "checked=\"checked\"";}
			}

			String trade = new String("");
			{
				byte status = DeliveryDB.GMGetNoTrade();
				if(status == (byte)1){trade = "checked=\"checked\"";}
			}

			String shop = new String("");
			{
				byte status = DeliveryDB.GMGetNoSellPoint();
				if(status == (byte)1){shop = "checked=\"checked\"";}
			}

			String auction = new String("");
			{
				byte status = DeliveryDB.GMGetNoAuction();
				if(status == (byte)1){auction = "checked=\"checked\"";}
			}

		// ### END Get Current Values ###

		// ### Show Form ###

			out.println("<form action=\"index.jsp?page=server&process=save\" method=\"post\" style=\"margin: 0px;\">");
			out.println("<table cellpadding=\"2\" cellspacing=\"0\" style=\"border: 1px solid #cccccc;\">");
			out.println("<tr><th colspan=\"3\" align=\"center\" style=\"padding: 5px;\">SERVER CONFIGURATION</th>");
			out.println("<tr bgcolor=\"#f0f0f0\"><td colspan=\"3\" align=\"center\">" + message + "</td>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Max. Online Users / Virtual Max. Online Users</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"users_max\" type=\"text\" value=\"" + users_max + "\" style=\"width: 40px; text-align: center;\"></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Set Lambda Value</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"lambda_value\" type=\"text\" value=\"" + lambda + "\" style=\"width: 40px; text-align: center;\"></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn Double Experience Points On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"dblexp_on\" type=\"checkbox\" value=\"true\" " + double_exp + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn Double Skill Points On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"dblsp_on\" type=\"checkbox\" value=\"true\" " + double_sp + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn Double Droprate On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"dbldrop_on\" type=\"checkbox\" value=\"true\" " + double_drop + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn Double Coins On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"dblcoin_on\" type=\"checkbox\" value=\"true\" " + double_coin + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn No-Mail Mode On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"nomail_on\" type=\"checkbox\" value=\"true\" " + mail + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn No-Faction Mode On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"nofaction_on\" type=\"checkbox\" value=\"true\" " + faction + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn No-Trade Mode On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"notrade_on\" type=\"checkbox\" value=\"true\" " + trade + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn No-PlayerShop Mode On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"noshop_on\" type=\"checkbox\" value=\"true\" " + shop + "></td></tr>");
			out.println("<tr><td style=\"border-top: 1px solid #cccccc;\">Turn No-Auction Mode On / Off</td><td align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input name=\"noauction_on\" type=\"checkbox\" value=\"true\" " + auction + "></td></tr>");
			out.println("<tr><td colspan=\"2\" align=\"center\" style=\"border-top: 1px solid #cccccc;\"><input type=\"image\" src=\"include/btn_save.jpg\" style=\"border: 0px;\"></td></tr>");
			out.println("</table>");
			out.println("</form>");

		// ### END Show Form ###
	}
%>
</td>
</tr>
</table>