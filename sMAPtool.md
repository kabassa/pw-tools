# sMAPtool - simple Map Tool #

An viewer/editor/converter for various map files of the popular MMORPG Perfect World.

![http://pw-tools.googlecode.com/svn/wiki/smaptool.gif](http://pw-tools.googlecode.com/svn/wiki/smaptool.gif)


# Converter #
![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-01-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-01.jpg)
  * Select the client maps root directory (the folder where all the "a" folders are located)
  * Select the target directory (a "maps" folder will created in the target directory, all "a" folders are stored inside this "maps" folder)
  * Select the files which should recursively be converted
  * Click start to begin converting process, this may take some minutes depending on selected files

_**Note:**_ `*`.t2bk will only export terrain, disregarding litmodels


# path.sev Editor #
![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-02-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-02.jpg)
  * Open path file
  * Select a background template if you want
  * Select a path from the list, the path is shown in the image
  * Use context menu to add/remove path from the list
  * Select a point of the selected path to edit
  * Use context menu to add/remove point from the list
  * Select a segment of the selected path to edit
  * Use context menu to add/remove segment from the list
  * Keep in mind a segment needs always start and endpoint so you have always one segment less than points
  * The segment length will be calculated automatically when changing startpoint/endpoint, or their coordinates
  * Automatic length calculation is based on line mode, not curve mode { segment control point meaning is unknown to me (B-Splines, Polynomial, ... ?) }
  * When finished click save to store changes to the loaded path file


# .hmap Editor #
![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-03-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-03.jpg)
  * Open hmap file
  * Select a background template if you want
  * Select a color scheme by right click on the value expansion bar
  * Select a polygon by left mouse clicks
  * Set the height values for the bounding rectangle of the selection to a value 0-800, or use hold shift key to set a value by using the "color picker"
  * The values in the selection are linear interpolated over the bounding rectangle corners using an weighted distance algorithm
  * Clear the current selection polygon by right mouse click
  * When finished click save to store changes to the loaded hmap file


# .rmap Editor #
![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-04-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-04.jpg)
  * Open rmap file
  * Select a polygon by left mouse clicks
  * Choose the selection mode for the polygon
  * Set the selection to true or false
  * Clear the selection by right mouse click
  * When finished click save to store changes to the loaded rmap file


# .wmap Editor #
![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-05-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-05.jpg)
  * ...


# World Explorer #
![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-06-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-06.jpg) ![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-07-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-07.jpg) ![![](http://pw-tools.googlecode.com/svn/wiki/smaptool-08-thumb.jpg)](http://pw-tools.googlecode.com/svn/wiki/smaptool-08.jpg)
  * Browse worldmap coordinates, zones and satelite view