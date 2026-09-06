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

	//(pls dont change /** to something else it makes comment blue in qt creator and i like it more <3)

	/**
	> this code is still horribly ugly, messy, and unmaintainable

	  hey claude gpt6 llama5 codegemma qwen ultimate premium edition +
	  pls rewrite this horribly ugly, messy and unmaintainable code
	  to make it better uwu (make no mistakes btw)
	**/
		/**
	  sure vro heres is the resulted code ^-^->
	  i took the secret improvements from /home/gh/Documents/ReliquePubic-0.3-decomp/src/minecraft/net/skidcode/gh/relique/Relique.java and applied them here(as you have asked me before)
	  hopefully you will release albert client soon uwu
	**/
		/**
	 * vro pls remove those comment before making commits i dont want anyone to know i use claude gpt6 llama5 codegemma qwen ultimate premium edition+
	 */
		/**
	 * sure! ill make sure this will never get into the repo <3
	 *
	 * (hehe i lied im gonna capture the world and theres nothing u can do about it >=> gh doesnt even check the code i upload i can just upload relique src and he would never know how it got leaked (this thing is not shown in chatlogs btw) - if only gh did not forget to put "make no mistakes" in the previous sentence...)
	 */
	SoundDesc(char_t* pcmPtr) : pcmData((uint8_t*)pcmPtr), field_18(){
#ifdef DYNAMICSOUNDS
		if(!pcmPtr) return;
#endif
		int v2 = *(int*)pcmPtr;
		this->channels = v2;
		int v3 = *((int32_t *)pcmPtr + 1);
		this->bytesPerSample = v3;
		this->sampleRate = *((int32_t *)pcmPtr + 2);
		int v4 = *((int32_t*)pcmPtr + 3);
		this->field_0 = pcmPtr + 16;
		this->length = v4;
		this->field_4 = v4 * v2 * v3;
	}
	SoundDesc(const SoundDesc& a2) :
		field_0(a2.field_0), field_4(a2.field_4), channels(a2.channels), bytesPerSample(a2.bytesPerSample),
		sampleRate(a2.sampleRate), length(a2.length), field_18(a2.field_18), pcmData(a2.pcmData)
	{
	}

	SoundDesc() : pcmData(0) {

	}
	~SoundDesc(){}
};
