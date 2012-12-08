#include <cstring>
#include <audiere.h>
#include <algorithm>
#include <windows.h>
#include <sstream>
#include <string>
#include "HandleMap.hpp"

#define DLLEXPORT extern "C" __declspec(dllexport)

audiere::AudioDevicePtr device;
HandleMap<audiere::OutputStream> outputStreamPointers;
HandleMap<audiere::SoundEffect>  soundEffectPointers;
bool debugMode = false;
void MsgBox(const char* caption,const char* message) {
        MessageBox(0, message, caption, MB_OK);
}
DLLEXPORT double fa_set_debugmode(double flag) {
    if (flag)
        debugMode = true;
    else
        debugMode = false;
    return 0;
}
DLLEXPORT double audio_create(const char *filename, double stream) {
	if(!device) return -1;
	audiere::OutputStreamPtr audio(audiere::OpenSound(device, filename, stream));
	if (!audio) {
		return -1;
	} else {
		return outputStreamPointers.allocate(audio);
	}
}
DLLEXPORT double audio_play(double handle) {
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if (!audio) {
		return -1;
	} else {
		audio->play();
		return 0;
	}
}
DLLEXPORT double audio_set_repeat(double handle, double repeat) {
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if (!audio) {
		return -1;
	} else {
	    audio->setRepeat(repeat);
		return 0;
	}
}
DLLEXPORT double audio_set_volume(double handle, double volume) {
	volume = std::min(1.0, std::max(0.0, volume));
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if (!audio) {
		return -1;
	} else {
	    audio->setVolume((float)volume);
		return 0;
	}
}
DLLEXPORT double audio_set_pan(double handle, double pan) {
	pan = std::min(1.0, std::max(-1.0, pan));
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if (!audio) {
		return -1;
	} else {
	    audio->setPan((float)pan);
		return 0;
	}
}
DLLEXPORT double audio_get_volume(double handle) {
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if (!audio) {
		return -1;
	} else {
	    return audio->getVolume();
	}
}
DLLEXPORT double audio_get_pan(double handle) {
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if (audio) {
		return audio->getPan();
	} else {
        if (debugMode) {
            std::ostringstream sstream;
            sstream << "Requested Pan from nonexistiant Handle! "<< std::endl << "Handle: " << handle << std::endl << "Returning 0.";
            std::string message = sstream.str();
            const char * cmessage = message.c_str();
            MsgBox("Error", cmessage);
        }
        return 0;
    }
}
DLLEXPORT double audio_stop(double handle) {
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if(audio) {
		audio->stop();
		return 0;
	}
	return -1;
}
DLLEXPORT double audio_release(double handle) {
	audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
	if(audio) {
		audio->stop();
		outputStreamPointers.release(handle);
	}
	return 0;
}
DLLEXPORT double audio_is_playing(double handle) {
    audiere::OutputStreamPtr audio = outputStreamPointers.find(handle);
    if (!audio) return -1;
    if (audio -> isPlaying()) {
        return 1;
    }
    return 0;
}
DLLEXPORT double sfx_create(const char *filename) {
	if(!device) return -1;
    audiere::SoundEffectPtr sfx(audiere::OpenSoundEffect(device, filename, audiere::SoundEffectType::SINGLE));
	if (!sfx) {
		return -1;
	} else {
		return soundEffectPointers.allocate(sfx);
	}
}
DLLEXPORT double sfx_set_pan(double handle, double pan)  {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
	pan = std::min(1.0, std::max(-1.0, pan));
    if (sfx) {
        sfx->setPan((float)pan);
        return(0);
    }
	return -1;
}
DLLEXPORT double sfx_get_pan(double handle)  {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
    if (sfx) {
        return sfx->getPan();
    }else{
        if (debugMode) {
            std::ostringstream sstream;
            sstream << "Requested Pan from nonexistiant Handle! "<< std::endl << "Handle: " << handle << std::endl << "Returning 0.";
            std::string message = sstream.str();
            const char * cmessage = message.c_str();
            MsgBox("Error", cmessage);
        }
        return 0;
    }
}
DLLEXPORT double sfx_set_volume(double handle, double volume)  {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
	volume = std::min(1.0, std::max(0.0, volume));
    if (sfx) {
        sfx->setVolume((float)volume);
        return 0;
    }
    return -1;
}
DLLEXPORT double sfx_get_volume(double handle)  {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
    if (sfx) {
        return sfx->getVolume();
    }else{
        return -1;
    }
}
DLLEXPORT double sfx_release(double handle)  {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
    if(sfx) {
		sfx->stop();
		soundEffectPointers.release(handle);
		return 0;
	}
	return -1;
}
DLLEXPORT double sfx_play(double handle) {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
    if (sfx) {
        sfx->play();
        return 0;
    }
    return -1;
}
DLLEXPORT double sfx_stop(double handle) {
    audiere::SoundEffectPtr sfx = soundEffectPointers.find(handle);
    if (sfx) {
        sfx->stop();
        return 0;
    }
    return -1;
}

DLLEXPORT double dllStartup() {
	device = audiere::OpenDevice();
	return 0;
}

DLLEXPORT double dllShutdown() {
	outputStreamPointers.releaseAll();
	soundEffectPointers.releaseAll();
	device = NULL;
	return 0;
}
