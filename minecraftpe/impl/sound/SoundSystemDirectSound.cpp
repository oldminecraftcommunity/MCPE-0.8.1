#ifdef __WIN32__
#include <sound/SoundSystemDirectSound.hpp>
#include <sound/SoundDesc.hpp>
#include <math.h>
#include <sounddata.hpp>
#include <windows.h>
#include <SDL/SDL_syswm.h>
#include <unknwn.h>
SoundSystemDirectSound::SoundSystemDirectSound(void) {
	
}
SoundSystemDirectSound::~SoundSystemDirectSound() {
	this->destroy();
}


bool_t SoundSystemDirectSound::checkErr(uint32_t a2) {
	if(a2) {
		return 1;
	}
	return 0;
}
void SoundSystemDirectSound::destroy(void) {
	this->dsound->Release();
}

void SoundSystemDirectSound::init(void) {
	HRESULT hr = DirectSoundCreate8(NULL, &this->dsound, NULL);
	if(FAILED(hr)){
		printf("DirectSoundCreate8 fail: %x\n", hr);
		return;
	}
	HWND wnd;
	SDL_SysWMinfo info;
	if (SDL_GetWMInfo(&info)) {
		wnd = info.window;
	}else{
		printf("GetWMInfo returned <= 0, cant continue\n");
		return;
	}
	hr = this->dsound->SetCooperativeLevel(wnd, DSSCL_NORMAL);
	if(FAILED(hr)){
		printf("SetCooperativeLevel fail: %x\n", hr);
		return;
	}
}

void SoundSystemDirectSound::removeStoppedSounds(void) {
	this->playedCnt = 0;
	for(int i = 0; i < MAX_PLAYED; ++i) {
		if(!this->buffers[i]) continue;
		DWORD status;
		this->buffers[i]->GetStatus(&status);
		if(status == DSBSTATUS_PLAYING){
			++this->playedCnt;
		}else{
			this->buffers[i]->Release();
			this->buffers[i] = 0;
		}
	}
}
void SoundSystemDirectSound::setListenerPos(float a, float b, float c) {

}
void SoundSystemDirectSound::setListenerAngle(float a) {
	//useless cuz mcpe has no 3d sound?
}
void SoundSystemDirectSound::load(const std::string&) {
}
void SoundSystemDirectSound::play(const std::string&) {
}
void SoundSystemDirectSound::pause(const std::string&) {
}
void SoundSystemDirectSound::stop(const std::string&) {
}

void SoundSystemDirectSound::playAt(const struct SoundDesc& a2, float a3, float a4, float a5, float a6, float a7) {
	this->removeStoppedSounds();
	if(this->playedCnt < MAX_PLAYED) {
		for(int i = 0; i < MAX_PLAYED; ++i) {
			if(!this->buffers[i]) {
				
				WAVEFORMATEX wf;
				wf.wFormatTag = WAVE_FORMAT_PCM;
				wf.nSamplesPerSec = a2.sampleRate;
				wf.wBitsPerSample = 8*a2.bytesPerSample;
				wf.nChannels = a2.channels;
				wf.nBlockAlign = a2.channels * a2.bytesPerSample;
				wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
				wf.cbSize = 0;

				DSBUFFERDESC desc;
				desc.dwSize = sizeof(desc);
				desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
				desc.dwBufferBytes = a2.field_4;
				desc.dwReserved = 0;
				desc.lpwfxFormat = &wf;
				desc.guid3DAlgorithm = GUID_NULL;
				
				LPDIRECTSOUNDBUFFER tmp;
				HRESULT hr = this->dsound->CreateSoundBuffer(&desc, &tmp, NULL);
				if(FAILED(hr)){
					printf("temp buffer creation failed\n", hr);
					break;
				}
				hr = tmp->QueryInterface(IID_IDirectSoundBuffer8, &this->buffers[i]);
				if(FAILED(hr)){
					printf("secondary buffer creation failed: %x\n", hr);
					tmp->Release();
					break;
				}
				tmp->Release();
				void* bf;
				DWORD bsize;
				this->buffers[i]->Lock(0, a2.field_4, &bf, &bsize, NULL, 0, 0);
				memcpy(bf, a2.field_0, a2.field_4);
				hr = this->buffers[i]->Unlock(bf, bsize, NULL, 0);
				if(FAILED(hr)){
					printf("Unlock fail: %x\n", hr);
					break;
				}
				LONG volume;
				if(a6 <= 0) volume = DSBVOLUME_MIN;
				else{
					volume = floorf(2000 * log10f(a6 > 1 ? 1 : a6) + 0.5f);
				}
				this->buffers[i]->SetVolume(volume);
				
				this->buffers[i]->Play(0, 0, 0);
				break;
			}
		}
	}
}
#endif
