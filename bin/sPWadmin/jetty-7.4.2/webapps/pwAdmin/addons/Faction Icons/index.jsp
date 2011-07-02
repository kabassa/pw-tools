<%@page import="java.sql.*"%>
<%@page import="java.util.zip.*"%>
<%@page import="java.util.List"%>
<%@page import="org.apache.commons.fileupload.*"%>
<%@page import="javax.imageio.ImageIO"%>
<%@page import="java.awt.Graphics2D"%>
<%@page import="java.awt.image.*"%>
<%@include file="../../WEB-INF/.pwadminconf.jsp"%>

<%
	boolean admin_mode = false;

	if(request.getSession().getAttribute("ssid") != null)
	{
		admin_mode = true;
	}
%>

<html>

<head>
	<link rel="shortcut icon" href="../../include/fav.ico">
	<link rel="stylesheet" type="text/css" href="../../include/style.css">

	<script type="text/javascript" language="JavaScript">

		var icon = new Image();

		function changeIcon()
		{
    			icon.src = "icons/1_" + document.forms["changeicon"].factionid.value + ".gif" + "?" + (new Date()).getTime();
			document.icon.src = icon.src;
		}

		function errorIcon()
		{
    			icon.src = "icons/0_0.gif" + "?" + (new Date()).getTime();
			document.icon.src = icon.src;
		}

	</script>
</head>

<body>

<table align="center" width="400" cellpadding="2" cellspacing="0" style="border: 1px solid #cccccc;">

	<tr>
		<th align="center" style="padding: 5;">
			<b>FACTION ICON MANAGER</b>
		</th>
	</tr>

	<tr bgcolor="#f0f0f0">
		<td align="right">
			<%
				if(admin_mode)
				{
					out.println("<font color=\"#00cc00\"><b>Root Access: </b></font> <a href=\"index.jsp?download\">Download</a> ");
				}
				else
				{
					pageContext.include("login.jsp");
				}
			%>
		</td>
	</tr>

	<tr>
		<td align="center" valign="middle">
			<%
				if(admin_mode && request.getParameter("download") != null)
				{
					String basePath = request.getRealPath(request.getServletPath().replaceAll("index.jsp", ""));

					File[] imageFiles = (new File(basePath + "/icons")).listFiles();

					int tile = 1;
					while(imageFiles.length > tile*tile)
					{
						tile = 2*tile;
					}

					BufferedImage iconlist = new BufferedImage(tile*16, tile*16, BufferedImage.TYPE_4BYTE_ABGR);
					Graphics2D iconGraphics = iconlist.createGraphics();
					BufferedWriter bw = new BufferedWriter(new FileWriter(basePath + "/iconlist_guild.txt"));
					bw.write("16\r\n");
					bw.write("16\r\n");
					bw.write(tile + "\r\n");
					bw.write(tile + "\r\n");

					BufferedImage bimg;
					int imageCount = 0;
					int tileX = 0;
					int tileY = 0;
					for(int i=0; i<imageFiles.length; i++)
					{
						if(imageFiles[i].getName().endsWith(".gif"))
						{
							bw.write(imageFiles[i].getName().replaceAll(".gif", ".dds") + "\r\n");
							bimg = ImageIO.read(imageFiles[i]);
							tileX = imageCount%tile;
							tileY = imageCount/tile;
							iconGraphics.drawImage(bimg, tileX*16, tileY*16, null);
							imageCount++;
						}
					}

					bw.close();
					iconGraphics.dispose();
					ImageIO.write(iconlist, "png", new File(basePath + "/iconlist_guild.png"));

					String[] zfiles = new String[]{"iconlist_guild.txt", "iconlist_guild.png"};
					ZipOutputStream z_out = new ZipOutputStream(new BufferedOutputStream(new FileOutputStream(basePath + "/iconlist_guild.zip")));
					byte[] buffer = new byte[1024];               
					for(int i=0; i<zfiles.length; i++)
					{
						BufferedInputStream z_in = new BufferedInputStream(new FileInputStream(basePath + "/" + zfiles[i]));
						z_out.putNextEntry(new ZipEntry(zfiles[i]));
						int bcount;
						while((bcount = z_in.read(buffer, 0, buffer.length)) != -1)
						{      
							z_out.write(buffer, 0, bcount);
						}
						z_in.close();
						(new File(basePath + "/" + zfiles[i])).delete();
					}
					z_out.flush();
					z_out.close();

					// Redirect to download file
					response.sendRedirect("iconlist_guild.zip"); 
				}

				if(admin_mode || request.getSession().getAttribute("user") != null)
				{
					int uid = 0;
					if(request.getSession().getAttribute("user") != null)
					{
						uid = Integer.parseInt((String)request.getSession().getAttribute("user"));
					}

					int factionid = 0;
					Boolean delete = false;
					byte[] icon = new byte[0];

					if(request.getContentType() != null && request.getContentType().indexOf("multipart/form-data") > -1)
					{
						List items = (new org.apache.commons.fileupload.servlet.ServletFileUpload(new org.apache.commons.fileupload.disk.DiskFileItemFactory())).parseRequest(request);
                
						for(int i=0; i< items.size(); i++)
						{
							FileItem item = (FileItem)items.get(i);
							if(item.isFormField())
							{
								if(item.getFieldName().equals("factionid"))
								{
									factionid = Integer.parseInt(item.getString());
								}
								if(item.getFieldName().equals("delete"))
								{
									delete = true;
								}
							}
							else
							{
								icon = new byte[(int)item.getSize()];
								item.getInputStream().read(icon, 0, icon.length);
							}
                        			}
					}

					Class.forName("com.mysql.jdbc.Driver").newInstance();
					Connection connection = DriverManager.getConnection("jdbc:mysql://" + db_host + ":" + db_port + "/" + db_database, db_user, db_password);
					Statement statement = connection.createStatement();
					ResultSet rs;

					if(factionid > 0)
					{
						rs = statement.executeQuery("SELECT account_id FROM roles WHERE faction_id=" + factionid + " AND role_faction_rank=2");
						if(rs.next())
						{
							if(admin_mode || rs.getInt("account_id") == uid)
							{
								String iconFile = request.getRealPath(request.getServletPath().replaceAll("index.jsp", "")) + "/icons/1_" + factionid + ".gif";

								if(delete)
								{
									try
									{
										(new File(iconFile)).delete();
										out.print("<font color=\"#00cc00\"><b>Icon Removed</b></font>");
									}
									catch(Exception e)
									{
										out.print("<font color=\"#ff0000\"><b>Removing Icon Failed!</b></font>");
									}
								}
								else
								{
									if(icon.length > 0 && icon[0] == 'G' && icon[1] == 'I' && icon[2] == 'F' && icon[6] == 16 && icon[8] == 16)
									{
										FileOutputStream fos = new FileOutputStream(iconFile);
										fos.write(icon);
										fos.close();
										out.print("<font color=\"#00cc00\"><b>Icon Committed</b></font>");
									}
									else
									{
										out.print("<font color=\"#ee0000\"><b>Required Image GIF 16x16!</b></font>");
									}
								}
							}
							else
							{
								out.print("<font color=\"#ee0000\"><b>No Permissions for this Operation!</b></font>");
							}
						}
						else
						{
							out.print("<font color=\"#ee0000\"><b>Faction not Found!</b></font>");
						}
					}

					if(admin_mode)
					{
						rs = statement.executeQuery("SELECT role_name, faction_id FROM roles WHERE role_faction_rank=2");
					}
					else
					{
						rs = statement.executeQuery("SELECT role_name, faction_id FROM roles WHERE account_id=" + uid + " AND role_faction_rank=2");
					}

					out.println("<table cellpadding=\"4\" cellspacing=\"0\" border=\"0\">");
					out.println("<form name=\"changeicon\" action=\"index.jsp\" method=\"post\" enctype=\"multipart/form-data\">");
					out.println("<tr><td><font color=\"#000000\"><b>Faction (Leader): </b></font></td><td><select name=\"factionid\" onchange=\"changeIcon();\" style=\"width: 100%; text-align: left;\">");

					while(rs.next())
					{
						if(factionid == 0)
						{
							factionid = rs.getInt("faction_id");
						}

						String label = rs.getString("role_name");
						if(admin_mode)
						{
							label = "FID: " + rs.getString("faction_id") + " (" + label + ")";
						}

						if(factionid == rs.getInt("faction_id"))
						{
							out.println("<option value=\"" + rs.getString("faction_id") + "\" selected>" + label + "</option>");
						}
						else
						{
							out.println("<option value=\"" + rs.getString("faction_id") + "\">" + label + "</option>");
						}
					}

					rs.close();
					connection.close();

					out.println("</select></td></tr>");

					out.println("<tr><td><font color=\"#000000\"><b>Current Icon: </b></font></td><td><img name=\"icon\" onerror=\"errorIcon();\"></img></td></tr>");
					out.println("<tr><td><font color=\"#000000\"><b>Reset Icon: </b></font></td><td><input type=\"checkbox\" name=\"delete\" value=\"true\"></input></td></tr>");
					out.println("<tr><td><font color=\"#000000\"><b>Commit Icon: </b></font></td><td><input type=\"file\" name=\"icon\"></input></td></tr>");
					out.println("<tr><td align=\"center\" colspan=\"2\"><input type=\"image\" src=\"../../include/btn_submit.jpg\" style=\"border: 0px; vertical-align: middle;\"></input></td></tr>");
					out.println("</form>");
					out.println("</table>");
				}
				else
				{
					out.println("<font color=\"#ee0000\"><b>Access Denied!</b></font>");
				}
			%>
		</td>
	</tr>

</table>

<script>
	window.onload = changeIcon; 
</script>

</body>

</html>