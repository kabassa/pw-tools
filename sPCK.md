# sPCK - simple PCK utility #

Can extract files, compress files and add files from/to angelica file packages.

![http://pw-tools.googlecode.com/svn/wiki/spck.gif](http://pw-tools.googlecode.com/svn/wiki/spck.gif)


# Select Game Mode #
_sPCK supports multiple games so we need to set the first parameter switch to the correct game mode_
  * command line usage: `sPCK.exe -pw <instruction> <path/file>`
  * -pw is the switch for the game mode, valid options:
    1. -pw (Perfect World)
    1. -jd (Jade Dynasty)
    1. -fw (Forsaken World)
    1. -eso (Ether Sage)
    1. -rwpd (Steps / Sincerity Dance Scrambling)


# Decode CUP Patch #

_Extracting all files from file "example.cup" to directory "example.cup.files" and decode to "example.cup.decoded"_
  * command line usage: sPCK.exe -pw -xp "example.cup"
  * -pw is the switch for the game mode (here: Perfect World)
  * -xp is the switch for patch extraction
  * example.cup is the path to the input file that should be extracted
  * the input file must always ends with ".cup"
  * the extracted files are placed in "example.cup.files" root directory
  * the decoded files are placed in "example.cup.decoded" root directory
  * the root directories are placed in the same folder as the input file
  * supported are perfect world angelica file packages v2008


# Extract #

_Extracting all files from file "example.pck" to directory "example.pck.files"_
  * command line usage: sPCK.exe -pw -x "example.pck"
  * -pw is the switch for the game mode (here: Perfect World)
  * -x is the switch for extraction
  * example.pck is the path to the input file that should be extracted
  * the input file must always ends with ".pck"
  * the extracted files are placed in "example.pck.files" root directory
  * the root directory is placed in the same folder as the input file
  * supported are perfect world angelica file packages v2008


# Compress #

_Compressing all files from directory "example.pck.files" to file "example.pck"_
  * command line usage: sPCK.exe -pw -c "example.pck.files"
  * -pw is the switch for the game mode (here: Perfect World)
  * -c is the switch for compression
  * example.pck.files is the root directory containing the files to be compressed
  * the root directory must always ends with ".pck.files"
  * the output file will be named "example.pck" without the tailing ".files"
  * the output file will be placed in the same folder as the root directory
  * the output file is perfect world angelica file packages v2008 compatible


# Add / Replace #

_Adding/Replacing all files from directory "example.pck.files" into file "example.pck"_
  * command line usage: sPCK.exe -pw -a "example.pck.files"
  * -pw is the switch for the game mode (here: Perfect World)
  * -a is the switch for adding files to an exisiting pck package
  * example.pck.files is the root directory containing the files to be added
  * the root directory must always ends with ".pck.files"
  * the exisiting package must be named "example.pck" without the tailing ".files"
  * the exisitng package must be placed in the same folder as the root directory
  * the existing package must be perfect world angelica file packages v2008 compatible

_**Note:**_ When replacing files, the data blocks of the old files stays inside the pck, this means replacing over and over again a lot of files will raise the pck' size
when replacing a lot of files it's strongly recommend to repack the package (this will also remove existing dead data blocks) instead of replacing a large amount of files...


# Add / Replace Base64 encoded Files #

_Adding/Replacing all files from directory "example.pck.b64.files" with base64 encoded names into file "example.pck" (the base64 names are decoded while slipstreaming). This option was designed for sPatch to support OS without chinese character encoding support..._
  * command line usage: sPCK.exe -pw -ap "example.pck.b64.files"
  * -pw is the switch for the game mode (here: Perfect World)
  * -ap is the switch for adding files with base64 naming to an exisiting pck package
  * example.pck.b64.files is the root directory containing the files to be added
  * the root directory must always ends with ".pck.b64.files"
  * the exisiting package must be named "example.pck" without the tailing ".files"
  * the exisitng package must be placed in the same folder as the root directory
  * the existing package must be perfect world angelica file packages v2008 compatible


# Create XUP Patch for sPatch #

_This is a special renaming and compressing option added to create XUP patches for sPatch. Please read the documentation on sPatch for detailed usage_
  * command line usage: sPCK.exe -pw -cp "ec\_patch"
  * -pw is the switch for the game mode (here: Perfect World)
  * -cp is the switch for creating a 7z compressed patch with base64 naming of pck.files
  * ec\_patch is the root directory containing the element folder