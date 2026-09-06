#ifndef ANDROID
#include <_types.h>
#include <cpputils.hpp>
#include <sys/time.h>
#include <util/Random.hpp>
#include <math/Mth.hpp>
#include <App.hpp>
#include <AppPlatform_sdl.hpp>
#include <utf8proc/utf8proc.h>
#include <util/Util.hpp>
#include <unigl.hpp>

AppPlatform_sdl appPlatform;
#ifdef __WIN32__
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
#else
int main(){
#endif
	appPlatform.init();
	return 0;
}
#else
#include <main.hpp>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/native_activity.h>
#include <_pengine.hpp>
#include <NinecraftApp.hpp>
#include <android/JVMAttacher.hpp>
#include <cpputils.hpp>
#include <cpputils.hpp>
#include <unigl.hpp>
#include <string.h>
#include <RakNetTypes.h>

bool contextWasLost;
ENGINE* pEngine;
//TODO there is some other one before appPlatform which belongs to std?
static RakNet::SystemAddress _some_unknown_and_possibly_unused_field;
AppPlatform_android23 appPlatform;
NinecraftApp* ninecraftApp;
std::string nativeUtf8Input;

pthread_mutex_t _D6E04480; //TODO defined in the same file as engine?


void android_main(struct android_app* state) {
	ENGINE engine;
	pEngine = &engine;

	app_dummy();
	memset((void*) &engine, 0, sizeof(engine));
	state->userData = &engine;
	state->destroyRequested = 0;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input; //XXX doesnt have symbol

	pthread_mutex_lock(&_D6E04480);
	appPlatform.mainActivityRef = mainActivity_ref;
	pthread_mutex_unlock(&_D6E04480);

	JVMAttacher v25(appPlatform.jvm);
	appPlatform.screenWidth = v25.env->CallIntMethod(appPlatform.mainActivityRef, v25.env->GetMethodID(appPlatform.mainActivityReference, "getScreenWidth", "()I"));
	appPlatform.screenHeight = v25.env->CallIntMethod(appPlatform.mainActivityRef, v25.env->GetMethodID(appPlatform.mainActivityReference, "getScreenHeight", "()I"));
	v25.forceDetach();

	NinecraftApp* mc = new NinecraftApp();
	engine.appCtx.field_10 = 1;
	engine.field_1C = 1;
	ANativeActivity* activity = state->activity;
	engine.field_24 = 0;
	engine.minecraft = (Minecraft *)mc;
	engine.appCtx.platform = &appPlatform;
	ninecraftApp = mc;
	engine.state = state;

	JNIEnv* env = activity->env;
	activity->vm->AttachCurrentThread(&env, 0);
	jclass clz = env->FindClass("android/os/Environment");
	jmethodID v9 = env->GetStaticMethodID(clz, "getExternalStorageDirectory", "()Ljava/io/File;");
	if(env->ExceptionOccurred()){
		env->ExceptionDescribe();
	}
	jobject v10 = env->CallStaticObjectMethod(clz, v9);
	jclass v11 = env->GetObjectClass(v10);
	jmethodID mid = env->GetMethodID(v11, "getAbsolutePath", "()Ljava/lang/String;");
	jstring v14 = (jstring)env->CallObjectMethod(v10, mid);
	const char* utfChars = env->GetStringUTFChars(v14, 0);
	mc->dataPathMaybe = utfChars;
	mc->field_CC4 = utfChars;
	env->ReleaseStringUTFChars(v14, utfChars);
	activity->vm->DetachCurrentThread();
	if(state->savedState){
		mc->loadState(state->savedState, state->savedStateSize);
	}
	bool actFinished = 0;
	bool hasInit = 0;
	appPlatform.field_10C = activity;
	//XXX dword_D6E045A0 = (int)appPlatform.field_10C->assetManager;
	while(1){
		int outEvents;
		struct android_poll_source* outData;
		while(ALooper_pollAll(0, 0, &outEvents, (void**) &outData) >= 0){
			if ( outData )
			{
				if ( outData->id == 2 )
				{
					AInputEvent* outEvent = 0;
					if(AInputQueue_getEvent(state->inputQueue, &outEvent) < 0){
						strerror(_errno());
					}else{
						bool v20 = AKeyEvent_getKeyCode(outEvent) == 4 && AKeyEvent_getAction(outEvent) == 0;
						if ( appPlatform.keyboardShown && v20
							 || !AInputQueue_preDispatchEvent(state->inputQueue, outEvent) )
						{
							int handled;
							if(state->onInputEvent){
								handled = state->onInputEvent(state, outEvent);
							}else{
								handled = 0;
							}
							AInputQueue_finishEvent(state->inputQueue, outEvent, handled);
						}
					}

				}else{
					outData->process(state, outData);
				}
			}
		}

		if ( state->destroyRequested )
		{
			__android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP",
								"cro...");
			break;
		}
		if ( !hasInit )
		{
			if ( !engine.field_24 )
			{
				//goto lbl31
				sleepMs(50);
				goto LABEL_32;
			}
			//TODO actually calls App::init(&engine->appCtx);
			/*???????????????????*/
			mc->App::init(engine.appCtx);

			hasInit = 1;
			mc->setSize(engine.width, engine.height);
			__android_log_print(5, "MinecraftPE", "INITINIT!\n");
		}
		if ( !engine.field_24 || !engine.field_1C )
		{
			LABEL_31:
			sleepMs(50);
			goto LABEL_32;
		}

		if ( contextWasLost )
		{
			if ( eglMakeCurrent(
					engine.appCtx.field_0,
					engine.appCtx.field_8,
					engine.appCtx.field_8,
					engine.appCtx.field_4) )
			{
				contextWasLost = 0;
			}
		}
		else
		{
			mc->update();
		}
		LABEL_32:
		if ( !actFinished )
		{
			if ( mc->wantToQuit() )
			{
				actFinished = 1;
				ANativeActivity_finish(state->activity);
			}
		}
	}
	if(mc){
		delete mc;
	}
}
#endif
