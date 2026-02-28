#include <sound/SoundSystemAL.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <sound/SoundDesc.hpp>
#include <math.h>
#include <sounddata.hpp>

SoundSystemAL::SoundSystemAL(void) {
	this->init();
}
SoundSystemAL::~SoundSystemAL() {
	this->destroy();
}

static void _checkErr() {
	ALenum err = alGetError();
	if(err) {
		printf("OpenAL error: %x\n", err);
	}
}

bool_t SoundSystemAL::checkErr(uint32_t a2) {
	if(a2) {
		return 1;
	}
	return 0;
}
void SoundSystemAL::destroy(void) {
	if(this->context) {
		alcMakeContextCurrent(NULL);
		alcDestroyContext(this->context);
		this->context = 0;
	}
	if(this->device) {
		alcCloseDevice(this->device);
		this->device = 0;
	}

	alDeleteBuffers(MAX_PLAYED, this->buffers);
	alDeleteSources(MAX_PLAYED, this->sources);
}

void SoundSystemAL::init(void) {
	this->device = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	if(!this->device) {
		fprintf(stderr, "unable to open default device\n");
		return;
	}
	fprintf(stdout, "Device: %s\n", alcGetString(this->device, ALC_DEVICE_SPECIFIER));

	_checkErr();

	this->context = alcCreateContext(this->device, NULL);
	if(!alcMakeContextCurrent(this->context)) {
		fprintf(stderr, "failed to make default context\n");
		return;
	}

	alGenBuffers(MAX_PLAYED, this->buffers);
	alGenSources(MAX_PLAYED, this->sources);
	alListener3f(AL_POSITION, 0, 0, 0);
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
	float orient[] = {1, 0, 0, 0, 1, 0};
	alListenerfv(AL_ORIENTATION, orient);
}

void SoundSystemAL::removeStoppedSounds(void) {
	this->playedCnt = 0;
	for(int i = 0; i < MAX_PLAYED; ++i) {
		ALint state;
		alGetSourcei(this->sources[i], AL_SOURCE_STATE, &state);
		if(state == AL_PLAYING) {
			++this->playedCnt;
		} else {
			alSourcei(this->sources[i], AL_BUFFER, 0);
		}
	}
}
void SoundSystemAL::setListenerPos(float a, float b, float c) {

}
void SoundSystemAL::setListenerAngle(float a) {
	float r = a * (M_PI / 180.0);
	float orient[] = {-sin(r), 0, cos(r), 0, 1, 0};
	alListenerfv(AL_ORIENTATION, orient);
}
void SoundSystemAL::load(const std::string&) {
}
void SoundSystemAL::play(const std::string&) {
}
void SoundSystemAL::pause(const std::string&) {
}
void SoundSystemAL::stop(const std::string&) {
}

static inline ALenum to_al_format(short channels, short samples) {
	bool stereo = (channels > 1);
	switch(samples) {
		case 16:
			if(stereo) return AL_FORMAT_STEREO16;
			else return AL_FORMAT_MONO16;
		case 8:
			if(stereo) return AL_FORMAT_STEREO8;
			else return AL_FORMAT_MONO8;
		default:
			return -1;
	}
}

void SoundSystemAL::playAt(const struct SoundDesc& a2, float a3, float a4, float a5, float a6, float a7) {
	this->removeStoppedSounds();
	if(this->playedCnt < MAX_PLAYED) {
		for(int i = 0; i < MAX_PLAYED; ++i) {
			ALint state;
			alGetSourcei(this->sources[i], AL_SOURCE_STATE, &state);
			if(state != AL_PLAYING) {
				alSourcef(this->sources[i], AL_PITCH, a7);
				alSourcef(this->sources[i], AL_GAIN, a6);
				alSource3f(this->sources[i], AL_POSITION, 0, 0, 0);
				alSourcei(this->sources[i], AL_LOOPING, AL_FALSE);
				alSource3f(this->sources[i], AL_VELOCITY, 0.0f, 0.0f, 0.0f);
				alSourcef(this->sources[i], AL_REFERENCE_DISTANCE, 5.0f);
				alSourcef(this->sources[i], AL_MAX_DISTANCE, 16.0f);
				alBufferData(this->buffers[i], to_al_format(a2.channels, a2.bytesPerSample * 8), a2.field_0, a2.field_4, a2.sampleRate);
				alSourcei(this->sources[i], AL_BUFFER, this->buffers[i]);
				alSourcePlay(this->sources[i]);
				break;
			}
		}
	}
}
