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
audio_create(string filename)
Creates a sound of the given filename, returns a handle of the sound instance
audio_get_pan(handle)
returns the pan of the current handle (pans range between -1.0 to 1.0)

audio_get_volume(handle)
returns the volume of the given handle (volumes range between 0.0 for silence to 1.0 for full volume)

audio_is_playing(handle)
returns whether or not the current handle is playing

audio_play(handle, reset_if_playing)
plays the handle. The sound will reset if it is already playing if reset_if_playing is true

audio_release(handle)
releases the sound from memory

audio_set_pan(handle, pan)
Sets the pan of the sound instance (-1.0 to 1.0)

audio_set_repeat(repeat)
sets whether or not the sound should repeat when its done playing

audio_set_volume(handle, volume)
Sets how loud the sound is (0.0 for complete silence, 1.0 for full volume)

audio_stop(handle)
Stops playing the sound instance. Note that when replaying with audio_play unless reset_if_playing is true, will resume 
from where the sound left off
