#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>

enum AudioLoop { forever = -1, once = 0 };

template <const int SPECTRUM_SIZE> //SPECTRUM_SIZE should be value in power of 2
class Audio {

private:

	FMOD::System* fmodSystem;
	FMOD::Sound* music;
	FMOD::Channel* musicChannel;

	float spectrumLeft[SPECTRUM_SIZE];
	float spectrumRight[SPECTRUM_SIZE];

private:

	bool errorCheck(FMOD_RESULT result) {

		if (result != FMOD_OK) {
			printf("FMOD error! (%d) %s \n", result, FMOD_ErrorString(result));
			return false;
		}

		return true;

	}

public:

	Audio(const char* audioDirectory = nullptr) {

		FMOD_RESULT result;

		unsigned int version;

		result = FMOD::System_Create(&fmodSystem);
		errorCheck(result);

		result = fmodSystem->getVersion(&version);
		errorCheck(result);

		if (version < FMOD_VERSION) {
			//printf("FMOD Eror! You are using an older version of FMOD.", version, FMOD_VERSION);
			std::cout << "FMOD Eror! You are using an older version of FMOD. " << version << " " << FMOD_VERSION << std::endl;
		}

		//init fmod system
		result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		errorCheck(result);

		if (audioDirectory != nullptr) {
			loadAudio(audioDirectory);
		}

	}

	~Audio() {

		if (errorCheck(musicChannel->stop())) {
			musicChannel = nullptr;
		}

		if (errorCheck(music->release())) {
			music = nullptr;
		}

		if (errorCheck(fmodSystem->release())) {
			fmodSystem = nullptr;
		}

	}

	void loadAudio(const char* audioDirectory) {

		//load and setup music
		errorCheck(fmodSystem->createStream(audioDirectory, FMOD_SOFTWARE, 0, &music));

	}

	void playAudio(int loop) {

		//Play the loaded mp3 music
		if (errorCheck(fmodSystem->playSound(FMOD_CHANNEL_FREE, music, false, &musicChannel))) {

			//Set sound channel loop count
			musicChannel->setLoopCount(loop);

		}

	}

	void update() {

		fmodSystem->update();

		//Get spectrum for left and right stereo channes
		musicChannel->getSpectrum(spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		musicChannel->getSpectrum(spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

	}

	float getSpectrumRight(const int& index) {
		return spectrumRight[index];
	}

	float getSpectrumLeft(const int& index) {
		return spectrumLeft[index];
	}

};