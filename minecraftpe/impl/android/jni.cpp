#ifdef ANDROID
#include <jni.h>

#include <_pengine.hpp>
ENGINE* pEngine;
bool contextWasLost;
//TODO there is some other one before appPlatform which belongs to std?

#include <main.hpp>
#include <android/log.h>
#include <NinecraftApp.hpp>
#include <input/Keyboard.hpp>
#include <cpputils.hpp>
#include <main.hpp>
#include <android_native_app_glue.h>
#include <android/native_activity.h>
#include <android/JVMAttacher.hpp>
#include <unigl.hpp>
#include <string.h>
#include <android/AndroidRestRequestJob.hpp>
#include <network/mco/MojangConnector.hpp>
#include <RakNetTypes.h>

std::string nativeUtf8Input;
AppPlatform_android23 appPlatform;
static jobject mainActivity_ref;
NinecraftApp* ninecraftApp;

static pthread_mutex_t _D6E04480; //TODO defined in the same file as engine?
extern "C" {




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

	{ //some inlined method?
		JVMAttacher v25(appPlatform.jvm);
		appPlatform.screenWidth = v25.env->CallIntMethod(appPlatform.mainActivityRef, v25.env->GetMethodID(appPlatform.mainActivityReference, "getScreenWidth", "()I"));
		appPlatform.screenHeight = v25.env->CallIntMethod(appPlatform.mainActivityRef, v25.env->GetMethodID(appPlatform.mainActivityReference, "getScreenHeight", "()I"));
	}

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

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	pthread_mutex_init(&_D6E04480, 0);
	pthread_mutex_lock(&_D6E04480);
	pthread_self();
	appPlatform.init(vm);
	return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeBackPressed(JNIEnv* env, jobject dis){
	ninecraftApp->handleBack();
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeBackSpacePressed(JNIEnv* env, jobject dis){
	Keyboard::feed(8, 1);
	Keyboard::feed(8, 0);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeLoginData(JNIEnv* env, jobject dis, jstring a, jstring b, jstring c, jstring d){
	LoginInformation v21;
	const char* tok = env->GetStringUTFChars(a, 0);
	v21.accessToken = tok ? tok : "";
	env->ReleaseStringUTFChars(a, tok);
	const char* cid = env->GetStringUTFChars(b, 0);
	v21.clientId = cid ? cid : "";
	env->ReleaseStringUTFChars(b, cid);
	const char* prof = env->GetStringUTFChars(c, 0);
	v21.profileId = prof ? prof : "";
	env->ReleaseStringUTFChars(c, prof);
	const char* name = env->GetStringUTFChars(d, 0);
	v21.profileName = name ? name : "";
	env->ReleaseStringUTFChars(d, name);
	ninecraftApp->mojangConnector->setLoginInformation(v21);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis(JNIEnv* env, jobject dis){
	pthread_self();
	mainActivity_ref = env->NewGlobalRef(dis);
	pthread_mutex_unlock(&_D6E04480);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeReturnKeyPressed(JNIEnv* env, jobject dis){
	Keyboard::feed(13, 1);
	Keyboard::feed(13, 0);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeSetTextboxText(JNIEnv* env, jobject dis, jstring s){
	const char* utfChars = env->GetStringUTFChars(s, 0);
	DEBUGMSG("NATIVESETTBTEXT %s", utfChars);
	std::string v7 = !utfChars ? "" : utfChars;
	env->ReleaseStringUTFChars(s, utfChars);
	ninecraftApp->setTextboxText(v7);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeStopThis(JNIEnv* env, jobject dis){

}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeSuspend(JNIEnv* env, jobject dis){

}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeTypeCharacter(JNIEnv* env, jobject dis, jstring s){
    const char* utfChars = env-> GetStringUTFChars(s, 0);
	if(utfChars){
		nativeUtf8Input = utfChars;
		Keyboard::feedText(std::string(nativeUtf8Input), 0);
	}
	printf("@nativeTypeCharacter: %s\n", nativeUtf8Input.c_str());
	env->ReleaseStringUTFChars(s, utfChars);

}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeUnregisterThis(JNIEnv* env, jobject dis){
	pthread_self();
	env->DeleteGlobalRef(mainActivity_ref);
	mainActivity_ref = 0;
	pthread_mutex_destroy(&_D6E04480);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeWebRequestCompleted(JNIEnv* env, jobject dis, jint a2, AndroidRestRequestJob* a3, jint a4, jstring a5){
	printf("Entering native web req %d, %lld, %d\n", a2, a3, a4);
    const char* s = env->GetStringUTFChars(a5, 0);
    std::string v10(!s ? "" : s);
    env->ReleaseStringUTFChars(a5, s);
    a3->onRequestComplete(a2, a4, v10);
    puts("native done!");
}
//i suppose it is not needed - there are a lot of RakNet::SystemAddress constructors everywhere, maybe it is defined in header?
//static RakNet::SystemAddress _some_unknown_and_possibly_unused_field;

}
#endif
