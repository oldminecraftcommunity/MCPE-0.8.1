#include <sound/SoundDesc.hpp>

SoundDesc::SoundDesc(char_t* pcmPtr) {
	int32_t v2; // r4
	int32_t v3; // r5
	int32_t v4; // r2

	this->pcmData = (uint8_t*) pcmPtr;
	this->field_18 = "";
	v2 = *(int32_t*)pcmPtr;
	this->channels = v2;
	v3 = *((int32_t *)pcmPtr + 1);
	this->bytesPerSample = v3;
	this->sampleRate = *((int32_t *)pcmPtr + 2);
	v4 = *((int32_t*)pcmPtr + 3);
	this->field_0 = pcmPtr + 16;
	this->length = v4;
	this->field_4 = v4 * v2 * v3;
}
SoundDesc::SoundDesc(const SoundDesc& a2){
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->channels = a2.channels;
	this->bytesPerSample = a2.bytesPerSample;
	this->sampleRate = a2.sampleRate;
	this->length = a2.length;
	this->field_18 = a2.field_18;
	this->pcmData = a2.pcmData;
}

SoundDesc::SoundDesc() {
	this->field_18 = "";
	this->pcmData = 0;
}
SoundDesc::~SoundDesc() {
}
