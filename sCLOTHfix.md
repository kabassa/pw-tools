# sCLOTHfix - simple Fashion/Armor fixer #

This tool will fix the tint problem in the new 1.4.2 fashion items and the metallic reflection in new 1.4.2 armor. The output will be 1.3.6 compatible.

![http://pw-tools.googlecode.com/svn/wiki/sclothfix.png](http://pw-tools.googlecode.com/svn/wiki/sclothfix.png)


# Quick Guide #
  * extract your models.pck
  * navigate to "models.pck.files\models\players\装备" and drag this folder onto sCLOTH
  * now sCLOTH searches for all 1.4.2 fashions and armors
  * when finished, you can select a file from the list to see the preview
  * there are two pictures, the large one on the right shows the basic texture and the one at the bottom shows the corresponding new 1.4.2 mask texture
  * now browse through the files and keep looking for those that have a mask texture that contains clear shades of blue, these are the textures we're looking for (the blue told which portions should be tinted when dying the cloth)
  * if a file don't contain blue, then leave it as it is, a fix is unnecessary (some fashion and armor can't be dyed so they don't have a tint mask)
  * if you found a file that needs a fix, click the fix button, a preview appears
  * don't worry if some parts of the texture are now removed from the preview it just means that the disapperad parts will not be dyed (the parts are still there, only hidden in preview)
  * if you're fine with the fix then you can save the changes to a file in the output


**Loaded texture**
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/sclothfix_01.jpg' />

<b>Preview after fixing</b>
<br>
<img src='http://pw-tools.googlecode.com/svn/wiki/sclothfix_02.jpg' />