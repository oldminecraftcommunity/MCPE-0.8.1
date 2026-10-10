#include <sound/SoundSystemSL.hpp>
#include <util/Mutex.hpp>
#include <sound/SoundDesc.hpp>

#ifdef ANDROID
std::vector<SLObjectItf> SoundSystemSL::toRemove;
Mutex SoundSystemSL::toRemoveMutex;
SLObjectItf SoundSystemSL::objEngine = 0;

//opensl is alternative of openal for android
SoundSystemSL::SoundSystemSL(void) {
	this->field_10 = 0;
	this->field_24 = 0;
	this->field_28 = 1;
	this->init();
}
SoundSystemSL::~SoundSystemSL(){
	pthread_mutex_unlock(&SoundSystemSL::toRemoveMutex.mutex);

	for(auto o : this->field_0){
		(*o)->Destroy(o);
	}

	(*this->field_14)->Destroy(this->field_14);

	if (SoundSystemSL::objEngine){
		(*SoundSystemSL::objEngine)->Destroy(SoundSystemSL::objEngine);
		SoundSystemSL::objEngine = 0;
	}

}
bool_t SoundSystemSL::checkErr(unsigned long a2) {
	if(a2) {
		return 1;
	}
	return 0;
}
void SoundSystemSL::destroy(void) {
}
void SoundSystemSL::init(void) {
	SoundSystemSL::toRemove.clear();
	this->field_2C.resize(4);
	if(SoundSystemSL::objEngine){
		(*SoundSystemSL::objEngine)->Destroy(SoundSystemSL::objEngine);
	}
	SLEngineOption v13{1, 1};
	this->checkErr(slCreateEngine(&SoundSystemSL::objEngine, 1, &v13, 0, 0, 0));
	if(this->checkErr((*SoundSystemSL::objEngine)->Realize(SoundSystemSL::objEngine, 0))){
		this->field_28 = 0;
	}else{
		(*SoundSystemSL::objEngine)->GetInterface(SoundSystemSL::objEngine, SL_IID_ENGINE, &this->field_8);

		SLboolean v11[8];
		SLInterfaceID v12[2];
		this->checkErr((*this->field_8)->CreateOutputMix(this->field_8, &this->field_14, 0, v12, v11));
		this->checkErr((*this->field_14)->Realize(this->field_14, 0));
	}
}
void SoundSystemSL::removePlayer(SLAndroidSimpleBufferQueueItf a1, void* a2) {
	pthread_mutex_lock(&SoundSystemSL::toRemoveMutex.mutex);
	SoundSystemSL::toRemove.push_back((SLObjectItf) a2);
	pthread_mutex_unlock(&SoundSystemSL::toRemoveMutex.mutex);
}
void SoundSystemSL::removeStoppedSounds(void) {
	//XXX this thing might be causing slowdowns?
	pthread_mutex_lock(&SoundSystemSL::toRemoveMutex.mutex);
	int v2 = SoundSystemSL::toRemove.size();
	for(int i = 0; i < v2; ++i){
		this->field_2C[i] = SoundSystemSL::toRemove[i];
	}
	SoundSystemSL::toRemove.clear();
	pthread_mutex_unlock(&SoundSystemSL::toRemoveMutex.mutex);
	for(int v4 = 0; v4 < v2; ++v4){
		SLObjectItf v6 = this->field_2C[v4];
		auto p = this->field_0.begin();
		while(p != this->field_0.end()){
			if(*p == v6){
				this->field_0.erase(p);
				break;
			}
			++p;
		}
		(*v6)->Destroy(v6);
		--this->field_24;
	}
}
void SoundSystemSL::setListenerPos(float x, float y, float z) {
	if(this->field_10){
		SLVec3D vec{(int)(x * 1000), (int)(y * 1000), (int)(z * 1000)};
		this->checkErr((*this->field_10)->SetLocationCartesian(this->field_10, &vec));
	}else{
		this->field_18 = {x, y, z};
	}
}
void SoundSystemSL::setListenerAngle(float a) {
	if(this->field_10){
		this->checkErr((*this->field_10)->SetOrientationAngles(this->field_10, (a * 1000), 0, 0));
	}
}

static SLboolean _d6e04a20[2];
static SLInterfaceID _d6e04a28[2];
void SoundSystemSL::playAt(const struct SoundDesc& a2, float x, float y, float z, float a6, float a7) {
	this->removeStoppedSounds();
	if(this->field_24 <= 3){
		;
		SLDataLocator_AndroidSimpleBufferQueue v34{SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
		SLDataFormat_PCM v38{
			2, (unsigned int) a2.channels,
			(unsigned int) 1000*a2.sampleRate,
			(unsigned int) 8*a2.bytesPerSample,
			(unsigned int) 8*a2.bytesPerSample,
			(unsigned int) (a2.channels == 1 ? 4 : 3),
			2
		};
		SLDataSource v35{&v34, &v38};
		SLDataLocator_OutputMix v36{4, this->field_14};
		SLDataSink v37{&v36, 0};
		_d6e04a20[0] = _d6e04a20[1] = 1;
		_d6e04a28[0] = SL_IID_BUFFERQUEUE;
		_d6e04a28[1] = SL_IID_VOLUME;
		SLObjectItf player;
		this->checkErr((*this->field_8)->CreateAudioPlayer(this->field_8, &player, &v35, &v37, 2, _d6e04a28, _d6e04a20));
		this->checkErr((*player)->Realize(player, 0));
		SLPlayItf v31;
		this->checkErr((*player)->GetInterface(player, SL_IID_PLAY, &v31));
		SLVolumeItf v32;
		this->checkErr((*player)->GetInterface(player, SL_IID_VOLUME, &v32));
		SLmillibel v29;
		(*v32)->GetVolumeLevel(v32, &v29);
		(*v32)->SetVolumeLevel(v32, (SLmillibel)((float)v29 - ((1.0 - a6)*2000)));
		SLAndroidSimpleBufferQueueItf v33;
		this->checkErr((*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &v33));
		this->checkErr((*v33)->RegisterCallback(v33, SoundSystemSL::removePlayer, (void*) player));
		this->checkErr((*v33)->Enqueue(v33, a2.field_0, a2.field_4));
		this->checkErr((*v31)->SetPlayState(v31, SL_PLAYSTATE_PLAYING));
		this->field_0.push_back(player);
		++this->field_24;
	}
}
#endif
