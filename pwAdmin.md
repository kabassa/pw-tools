# pwAdmin - Perfect World Server Administration #

pwAdmin is an Web Interface based on JSP that uses the PW-Java API to control an Perfect World Server.

![http://pw-tools.googlecode.com/svn/wiki/pwadmin.png](http://pw-tools.googlecode.com/svn/wiki/pwadmin.png)

# pwAdmin / Jetty-7.x.x Bundle #
## Basic Installation ##
  * Jetty comes with php support, install php5-cgi and php-mysql to use it
  * pwAdmin requires JRE 1.6 (in debian you can install it by "apt-get install openjdk-6-jre")
  * extract "jetty-7.x.x.tar.bz2" package to a place of your choice
  * goto "jetty-7.x.x/webapps/pwAdmin/WEB-INF" directory
  * open the ".pwconf.conf" and replace all ip address 127.0.0.1 with the ip addi's of your pw-server (except your pw-services already listen to 127.0.0.1)
  * open the ".pwadminconf.jsp" and enter the settings depending on your server (especially mysql)
  * on first start pwAdmin ask you to enter a new password
  * later you can change the password in .pwadminconf.jsp, you must encode your new password with md5 and replace the old md5 password

## Autostart Jetty ##
  * download the jetty startup script and change the path' to fit your installation
  * put the script in /etc/init.d
  * register startup run levels (in debian by "update-rc.d jetty defaults")
  * restart your linux server
  * open a browser and enter **`http://YOUR-SERVER-IP:8080`** and you see a welcome page with link to pwAdmin, link to adminer and the phpinfo()

## Important Notes ##
  * jetty's document root is in "jetty/webapps/ROOT"
  * the included jetty is configured for port 8080, you can change the port of jetty in the "jetty-7.x.x/etc/jetty.xml" file
```
<Set name="port"><Property name="jetty.port" default="8080"/></Set>
```
  * when deleting an account the characters of this account won't be deleted, but you get a message which character id's to check and delete manually
  * you can only edit one character item at once, please be careful when editing items!
  * you need javascript enabled to use the item viewer
  * affected pw-server log files must be in /pw-server-path/logs/