# sPatcher - Perfect World Client Autopatcher #

This patcher is an alternative to the default perfect world patcher. It offers easy client patching by connecting to a patch server, check for new patches, downloading and installing these new patches.

![http://pw-tools.googlecode.com/svn/wiki/spatch_00.jpg](http://pw-tools.googlecode.com/svn/wiki/spatch_00.jpg)
<br>
<code>*</code>minimal mode<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/spatch_01.jpg' />
<br>
<code>*</code>full mode<br>
<br>
<br>
<h1>Install & Configure Patcher:</h1>

The patcher directory must be placed in the same directory as the game client's element folder (delete or rename the original patcher directory!).<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/spatch_install.jpg' />


After placing patcher to the correct location its time to explain the included files.<br>
<ul><li>The patcher has a "skin" folder, where the graphic are stored. Simply modify/exchange the files to customize your patcher.<br>
</li><li>The "tools" folder contains some helpers for the patcher and are unimportant for you.<br>
</li><li>The "version.sw" is a file that contains only the integer number of the current client version. For first use when you hand it out to your users, i recommend set it to 0. When connecting to server, all patches above the number in "version.sw" will be downloaded and installed.<br>
</li><li>The "patcher.ini" file contains configuration parameters for the patcher. In each case this file must contain the "patch_server=" key. This is where the patcher looking for new patches. Dont forget the tailing / at the end.</li></ul>

Example: patcher.ini<br>
<pre><code>patch_server=http://87.118.104.73/public/PW/patch_test/<br>
</code></pre>

Currently you can add the additional "patch_notes=" key to this file. If you add this key, the patcher adds a custom webpage (384x246 pixel) into the launcher. If you don't define this key, the launcher stays in its small-mode.<br>
<br>
The patcher also allows local webpages, just enter the relative path to the file instead an url. Wwebpage size is 384x216.<br>
<br>
Example: patcher.ini<br>
<pre><code>patch_server=http://87.118.104.73/public/PW/patch_test/<br>
patch_notes=http://launcher.perfectworld.com/pwi/launcher.html<br>
</code></pre>


<h1>Using Patcher:</h1>

Just launch the patcher and wait while fetching patch database. Now you see the current version and available version. If your current version is below available version, you can click update to start auto-patching. Depending on which files are patched, this process can be really time consuming (especially in .pck repacking). After finishing the client can be started by click play. Don't use the manual button for patching, i made this only for developers who don't wanna download the patch each time when debugging patches.<br>
<br>
<br>
<h1>Configure Patch Server:</h1>

Any web server can act as an patch server, all you need is an directory with patch database and patch files. The patch database is called "versions.sw". It's an simple text file, each line contains version number and corresponding patch file.<br>
<br>
Example: versions.sw<br>
<pre><code>1=ec_patch_0-1.xup<br>
2=ec_patch_1-2.xup<br>
</code></pre>

Beside the "versions.sw" you have to place all your <code>"ec_patch_*.xup"</code> files in the same directory. These files are simple compressed archives.<br>
<br>
<br>
<h1>Creating a Patch:</h1>

The patch contains files that will be downloaded and replaced in the client. The directory structure in a patch file must be the same as in the client. Lets assume you want to share some new files, first we have to create a root directory i.e. "ec_patch". Inside this directory we create "element" folder and inside of this the directory we place the files to be added to using sPatch. If you want to update files in a .pck package you have to create the corresponding .pck.files folder inside the "elements" directory. Place the files you want to add/replace inside this folder.<br>
<br>
Patch Data Files 1:<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/spatch_data_00.gif' />

Patch Data Files 2:<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/spatch_data_01.gif' />


At least create a xup patch by dragging the "ec_patch" folder onto "patcher.exe". The new <code>*.xup</code> patch is created in the same directory where "ec_patch" folder is located.<br>
<br>
In our Example (by dragging...):<br>
<pre><code>patcher.exe "C:\Users\Ronny\Desktop\ec_patch"<br>
</code></pre>

a new "ec_patch_0-0.xup" file was created besides your patch root directory.<br>
<br>
Inside "ec_patch_0-0.xup" File 1:<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/spatch_data_02.gif' />

Inside "ec_patch_0-0.xup" File 2:<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/spatch_data_03.gif' />

Now rename this patch file to match your version and upload the <code>"ec_patch_*.xup"</code> to your patch-server and add the created patch with a new version to your "versions.sw" database. The client patcher will download and install it next time when it connects to the server.