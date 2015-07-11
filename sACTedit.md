# sACTedit - simple Animation Editor #

An editor`*` for character model animations of the popular MMORPG Perfect World.
<br>
(<code>*</code>currently only character animation import/export is supported)<br>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/sactedit.gif' />


<h1>Tutorial (<a href='http://forum.ragezone.com/f695/character-animation-exchange-archer-assassin-719039/#post6106454'>Source</a>)</h1>

<i>This tutorial will show how to exchange skeleton animation of similar characters. In this example i've choosen to replace the female archer running animation with the female assassin running animation, both characters have the same skeleton structure.</i>

<a href='http://www.youtube.com/watch?v=tWmJVw3SUcA&hd=1'>YouTube - Archer with Assassin Run Animation</a>

<b>Requirements:</b>
<ul><li>the models must have the same skeleton structure (number of joints, joint-tree)<br>
</li><li>the ecm files must be fixed with latest sMODfix<br>
</li><li>the smd files version must be 8</li></ul>

<b>Guide:</b>
<ul><li>first extract all required model files of the female assassin and female archer<br>
</li><li>make sure the directory structure is the same as in the pck file (models.pck.files/models/...)<br>
</li><li>if you haven't made a backup yet make one now<br>
</li></ul><blockquote><a href='http://img820.imageshack.us/img820/4374/79778943.gif'><img src='http://img820.imageshack.us/img820/4374/79778943.th.gif' /></a>
</blockquote><ul><li>start sACTedit and load the ecm file of the assassin<br>
</li></ul><blockquote><a href='http://img196.imageshack.us/img196/5716/40847342.gif'><img src='http://img196.imageshack.us/img196/5716/40847342.th.gif' /></a>
</blockquote><ul><li>select the combine act for the running animation (index = 34)<br>
</li><li>in the right textbox the combine act data will be loaded<br>
</li></ul><blockquote><a href='http://img694.imageshack.us/img694/2161/80181126.gif'><img src='http://img694.imageshack.us/img694/2161/80181126.th.gif' /></a>
</blockquote><ul><li>the combine act holds a link to a base act (joint animation), click on this name and sACTedit will automatically jump to the correct base act on the left panel (index = 36)<br>
</li></ul><blockquote><a href='http://img14.imageshack.us/img14/5688/77370101.gif'><img src='http://img14.imageshack.us/img14/5688/77370101.th.gif' /></a>
</blockquote><ul><li>right click on the base act and click export, select a filename i.e. "c:/somewhere.../assassinfrun.act"<br>
</li></ul><blockquote><a href='http://img405.imageshack.us/img405/1101/37992565.gif'><img src='http://img405.imageshack.us/img405/1101/37992565.th.gif' /></a>
</blockquote><ul><li>now open the ecm file for the female archer and repeat the steps like for the assassin<br>
</li><li>select the combine act for the running animation (index = 16)<br>
</li><li>click the base act to jump to the linked base act (index = 33)<br>
</li><li>right click on the base act and click import, select the file you have exported from the female assassin<br>
</li></ul><blockquote><a href='http://img524.imageshack.us/img524/5938/87480624.gif'><img src='http://img524.imageshack.us/img524/5938/87480624.th.gif' /></a>
</blockquote><ul><li>at least click save and add the modified archer model files back to your models.pck<br>
</li><li>start the game and see your archer running like an assassin</li></ul>

<code>*</code>some combine acts have additional gfx, these gfx can be replaced by editing the ecm text field in the combine act section (the gfx part begins with <code>"EventCount: "</code>, each event block is a gfx description)<br>
when replacing text in combine acts make sure it is the same MOXTVersion, or ecm file will be corrupted