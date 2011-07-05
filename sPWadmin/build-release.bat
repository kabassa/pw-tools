7za.exe a -ttar -r -xr!.svn jetty-7.4.2.tar jetty-7.4.2\*
7za.exe a -tbzip2 -mx9 ..\bin\sPWadmin\jetty-7.4.2.tar.bz2 jetty-7.4.2.tar
DEL jetty-7.4.2.tar
PAUSE