#include <cstring>
#include <audiere.h>
#include <algorithm>

#include "HandleMap.hpp"

#define DLLEXPORT extern "C" __declspec(dllexport)

audiere::AudioDevicePtr device;
HandleMap<audiere::OutputStream> outputStreamPointers;

DLLEXPORT double audio_play(const char *filename, double volume, double repeat) {
	if(!device) return -1;
	volume = std::min(1.0, std::max(0.0, volume));
	audiere::OutputStreamPtr sound(audiere::OpenSound(device, filename, true));
	if (!sound) {
		return -1;
	} else {
		sound->setRepeat(repeat);
		sound->setVolume((float)volume);
		sound->play();
		return outputStreamPointers.allocate(sound);
	}
}

DLLEXPORT double audio_stop(double handle) {
	audiere::OutputStreamPtr sound = outputStreamPointers.find(handle);
	if(sound) {
		sound->stop();
		outputStreamPointers.release(handle);
	}
	return 0;
}

DLLEXPORT double dllStartup() {
	device = audiere::OpenDevice();
	return 0;
}

DLLEXPORT double dllShutdown() {
	outputStreamPointers.releaseAll();
	device = NULL;
	return 0;
}
