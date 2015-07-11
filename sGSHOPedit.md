# sGSHOPedit - simple GSHOP editor #

An editor for gshop.data file of the popular MMORPG Perfect World.


![http://pw-tools.googlecode.com/svn/wiki/sgshopedit.png](http://pw-tools.googlecode.com/svn/wiki/sgshopedit.png)


# Quick Start Tutorial #
_sGSHOPedit uses it's own database file which contains all informations (client and server files complement each other, so they are a inconsistent base for editing...)_

## Create a new Database ##
  1. start sGSHOPedit
  1. import an existing gshop.data (1.4.4 client preferred)
  1. save the file to gshop.db or a name of your choice


## Load & Edit a Database ##
  1. start sGSHOPedit
  1. load your database file (i.e. gshop.db)
  1. edit the categories & items
  * browse through categories, subcategories, items by select them in the lists
  * to rename categories and subcategories select the item in the list and edit them in the textfield below the list
  * re-sort categories, subcategories and items by selecting the item in the list, hold the left mouse button and move them up or down
  * move subcategories or items by selecting the item in the list and select target via context menu -> move to command
  * add subcategories or items by context menu add command
  * delete subcategories or items by selecting the item in the list and using the context menu delete command
  * edit an item by selecting the item in the list and change the property fields
  * use the update button to aquire name and descrition from pwdatabase.com, secondary source for description is the item\_desc.txt
  * file in the application directory, if both don't return result, values leave untouched


## Export a Database ##
  1. start sGSHOPedit
  1. load your database file (i.e. gshop.db)
  1. make sure to get the same timestamp for client & server file
  1. export one client 1.4.4 file
  1. export one server 1.4.4 file
  1. put the client file into your client and the server file on your server