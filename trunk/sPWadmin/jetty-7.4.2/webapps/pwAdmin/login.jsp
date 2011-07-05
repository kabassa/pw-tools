<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="java.security.*"%>
<%@include file="WEB-INF/.pwadminconf.jsp"%>

<%!
    	String encode(String salt, MessageDigest alg)
	{
		alg.reset(); 
		alg.update(salt.getBytes());
		byte[] digest = alg.digest();
		StringBuffer hashedpasswd = new StringBuffer();
		String hx;
		for(int i=0; i<digest.length; i++)
		{
			hx =  Integer.toHexString(0xFF & digest[i]);
			//0x03 is equal to 0x3, but we need 0x03 for our md5sum
			if(hx.length() == 1)
			{
				hx = "0" + hx;
			} 
			hashedpasswd.append(hx);
		}
		return hashedpasswd.toString();
   	}
%>

<table cellpadding="2" cellspacing="0" border="0">
<tr>
<%
	if(request.getParameter("logout") != null && request.getParameter("logout").compareTo("true") == 0)
	{
		request.getSession().removeAttribute("ssid");
		request.getSession().removeAttribute("items");
	}

	if(request.getParameter("key") != null)
	{
		// initial change of password "root" in configuration file
		if("63a9f0ea7bb98050796b649e85481845".compareTo(iweb_password) == 0)
		{
			iweb_password = encode(request.getParameter("key"), MessageDigest.getInstance("MD5"));

			Vector<String> lines = new Vector<String>();
			String line;
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(request.getRealPath("/") + "/WEB-INF/.pwadminconf.jsp")));
			while((line = br.readLine()) != null)
			{
				if(line.contains("iweb_password") && line.contains("63a9f0ea7bb98050796b649e85481845"))
				{
					line = line.replaceAll("63a9f0ea7bb98050796b649e85481845", iweb_password);
				}
				lines.add(line);
			}
			br.close();

			BufferedWriter bw = new BufferedWriter(new FileWriter(request.getRealPath("/") + "/WEB-INF/.pwadminconf.jsp"));
			for(int i=0; i<lines.size(); i++)
			{
				bw.write(lines.get(i) + "\n");
			}
			bw.close();
		}

		// compare passwords
		if(encode(request.getParameter("key"), MessageDigest.getInstance("MD5")).compareTo(iweb_password) == 0)
		{
			request.getSession().setAttribute("ssid", request.getRemoteAddr());
		}
	}

	if(request.getSession().getAttribute("ssid") == null)
	{
		if("63a9f0ea7bb98050796b649e85481845".compareTo(iweb_password) == 0)
		{
			out.println("<td align=\"left\" colspan=\"2\"><b><font color=\"#ff0000\">Change Initial Password</font></b></td></tr><tr>");
		}
		out.println("<form action=\"index.jsp?page=login\" method=\"post\"><td><input name=\"key\" type=\"password\" style=\"width: 70; text-align: center;\"></input></td><td><input type=\"image\" src=\"include/btn_login.jpg\" style=\"border: 0px;\"></input></td></form>");
	}
	else
	{
		out.println("<td><a href=\"index.jsp?page=login&logout=true\"><img src=\"include/btn_logout.jpg\" border=\"0\"></img></a></td>");
	}
%>
</tr>
</table>