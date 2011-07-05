<%@ page import="java.util.*"%>

<%!
 	String toHexString(int x)
  	{
		String result = Integer.toHexString(x);
		if(result.length() == 1)
		{
			result = "0" + result;
		}

		result += "000000";

		return result;
  	}
%>

<%
	String skillName;
	int skillValue;
	String skillList = "";
	int skillCount=0;

	for(Enumeration e = request.getParameterNames(); e.hasMoreElements();)
	{
		skillName = (String)e.nextElement();
		skillValue = Integer.parseInt(request.getParameter(skillName));
		if(skillValue>0 && skillCount<256 && skillValue<11 && skillName.length()==8)
		{
			//out.println(skillName + "=" + toHexString(skillValue) + "<br>");
			skillList += skillName + "00000000" + toHexString(skillValue);
			skillCount++;
		}
	}
%>

<html>

<head>
	<link rel="shortcut icon" href="../../include/fav.ico">
	<link rel="stylesheet" type="text/css" href="../../include/style.css">
</head>

<body>

<table width="500px" align="center" cellpadding="0" cellspacing="0" style="table-layout: fixed; border: 1px solid #cccccc;">

<tr>
	<th align="center" style="padding: 5px;">XML</th>
</tr>

<tr bgcolor="#f0f0f0">
	<td align="center"><b>&lt;variable name="skills" type="Octets"&gt;</b></td>
</tr>

<tr>
	<td align="center" valign="top"><textarea name="skill" wrap="hard" rows="5" style="width: 100%;"><%out.println(toHexString(skillCount)+skillList);%></textarea></td>
</tr>

<tr bgcolor="#f0f0f0">
	<td align="center"><b>&lt;/variable&gt;</b></td>
</tr>

</table>

<br>
<br>
<center>
<a href="javascript: history.back()">back</a>
</center>

</body>

</html>