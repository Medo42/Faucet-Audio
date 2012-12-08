Faucet-Audio
============

A Game Maker extension for playing sound

Dependencies
============
This dll requires audiere.lib 
Find that here
http://audiere.sourceforge.net/



Building
============
Audiere should be statically linked while compiling, note that I have this set to a relative import to my computer, so
You will obviously need to change that. See Build Options -> Linker Settings, and link to the .lib file.

Building the Game Maker Extension
============
Using Extension Maker http://sandbox.yoyogames.com/make/extensions, you should be able to open up the .ged file,
However you're going to have to update the path to the .dll file. Find this under Faucet-Audio.dll -> Misc

Functions
============
TBD