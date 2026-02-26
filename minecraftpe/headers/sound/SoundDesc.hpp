#pragma once
#include <_types.h>
#include <string>

struct SoundDesc{
	char_t* field_0;
	int32_t field_4;
	int32_t channels;
	int32_t bytesPerSample;
	int32_t sampleRate;
	int32_t length;
	std::string field_18;
	uint8_t* pcmData;

	SoundDesc(char_t* pcmData);
	SoundDesc(const SoundDesc&);
	SoundDesc(); //inlined
	~SoundDesc();
};
