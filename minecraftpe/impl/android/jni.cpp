#ifdef ANDROID

#include <_pengine.hpp>
ENGINE* pEngine;
bool contextWasLost;
//TODO there is some other one before appPlatform which belongs to std?

#include <main.hpp>
#include <jni.h>
#include <android/log.h>
#include <NinecraftApp.hpp>
#include <input/Keyboard.hpp>
#include <cpputils.hpp>
#include <main.hpp>
#include <android_native_app_glue.h>
#include <unigl.hpp>
#include <android/AndroidRestRequestJob.hpp>
#include <network/mco/MojangConnector.hpp>
#include <RakNetTypes.h>
#include <input/Controller.hpp>
#include <input/Mouse.hpp>
#include <input/Multitouch.hpp>

std::string nativeUtf8Input;
static AppPlatform_android23 appPlatform;
static jobject mainActivity_ref;
static NinecraftApp* ninecraftApp;

static pthread_mutex_t _D6E04480; //TODO defined in the same file as engine?
extern "C" {

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	pthread_mutex_init(&_D6E04480, 0);
	pthread_mutex_lock(&_D6E04480);
	pthread_self();
	appPlatform.init(vm);
	return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis(JNIEnv* env, jobject dis){
	pthread_self();
	mainActivity_ref = env->NewGlobalRef(dis);
	pthread_mutex_unlock(&_D6E04480);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeUnregisterThis(JNIEnv* env, jobject dis){
	pthread_self();
	env->DeleteGlobalRef(mainActivity_ref);
	mainActivity_ref = 0;
	pthread_mutex_destroy(&_D6E04480);
}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeStopThis(JNIEnv* env, jobject dis){

}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeSuspend(JNIEnv* env, jobject dis){

}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeBackPressed(JNIEnv* env, jobject dis){
	ninecraftApp->handleBack();
}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeSetTextboxText(JNIEnv* env, jobject dis, jstring s){
	const char* utfChars = env->GetStringUTFChars(s, 0);
	DEBUGMSG("NATIVESETTBTEXT %s", utfChars);
	std::string v7 = !utfChars ? "" : utfChars;
	env->ReleaseStringUTFChars(s, utfChars);
	ninecraftApp->setTextboxText(v7);
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

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeWebRequestCompleted(JNIEnv* env, jobject dis, jint a2, AndroidRestRequestJob* a3, jint a4, jstring a5){
	printf("Entering native web req %d, %lld, %d\n", a2, a3, a4);
    const char* s = env->GetStringUTFChars(a5, 0);
    std::string v10(!s ? "" : s);
    env->ReleaseStringUTFChars(a5, s);
    a3->onRequestComplete(a2, a4, v10);
    puts("native done!");
}
}

void engine_term_display(ENGINE* a1) {
	a1->field_1C = 0;
	appPlatform._fireAppSuspended();
	__android_log_print(5, "MinecraftPE", "Native app suspended!\n");
	if(a1->field_8) {
		eglMakeCurrent(a1->field_8, 0, 0, 0);
		if(a1->field_10) {
			eglDestroyContext(a1->field_8, a1->field_10);
		}
		if(a1->surface) {
			eglDestroySurface(a1->field_8, a1->surface);
		}
		eglTerminate(a1->field_8);
	}
	a1->field_8 = 0;
	a1->field_10 = 0;
	contextWasLost = 1;
}

void engine_handle_cmd(android_app* a1, int a2) {
	std::string v26 = "???";
	ENGINE* engine = (ENGINE*)a1->userData;
	DEBUGMSG("cmd: %d", a2);
	switch(a2) {
		case APP_CMD_INIT_WINDOW:
			if(engine->state->window) {
				int v30;
				EGLConfig v31;
				int format;
				EGLint attrs[] = {EGL_SURFACE_TYPE, 4, EGL_DEPTH_SIZE, 16, EGL_STENCIL_SIZE, 8, EGL_RENDERABLE_TYPE, 1, EGL_NONE};
				EGLDisplay display = eglGetDisplay(0);
				eglInitialize(display, 0, 0);
				eglChooseConfig(display, attrs, &v31, 1, &v30);
				eglGetConfigAttrib(display, v31, 12334, &format);
				ANativeWindow_setBuffersGeometry(engine->state->window, 0, 0, format);
				eglChooseConfig(display, attrs, 0, 0, &v30);
				EGLConfig* v9 = new EGLConfig[v30]; //TODO check
				eglChooseConfig(display, attrs, v9, v30, &v30);
				EGLSurface selSurface;
				EGLConfig selConfig;
				for(int v8 = 0; v8 < v30; ++v8) {
					EGLSurface surface = eglCreateWindowSurface(display, v9[v8], engine->state->window, 0);
					if(surface) {
						selSurface = surface;
						selConfig = v9[v8];
						break;
					}
				}
				if(v9) {
					delete[] v9;
				}
				EGLContext ctx = eglCreateContext(display, selConfig, 0, 0);
				if(eglMakeCurrent(display, selSurface, selSurface, ctx)) {
					EGLint width, height;
					eglQuerySurface(display, selSurface, EGL_WIDTH, &width);
					eglQuerySurface(display, selSurface, EGL_HEIGHT, &height);
					EGLint v15 = width;
					EGLint v16 = height;
					engine->appCtx.field_0 = display;
					if(v15 < v16) {
						height = v15;
						width = v16;
					}

					engine->field_8 = display;
					engine->height = height;
					engine->appCtx.field_4 = ctx;
					engine->field_10 = ctx;
					engine->appCtx.field_8 = selSurface;
					engine->surface = selSurface;
					engine->width = width;
					glViewport(0, 0, width, height);
					if(engine->field_24) {
						engine->minecraft->context = engine->appCtx;
						for(auto&& l: AppPlatform::_singleton->listeners) {
							l.second->onAppResumed();
						}

						engine->minecraft->setSize(width, height);
						engine->field_1C = 1;
					}
					eglSwapInterval(eglGetCurrentDisplay(), 2);
					engine->field_24 = 1;
				}
			}
			break;
		case APP_CMD_TERM_WINDOW:
			v26 = "APP_CMD_TERM_WINDOW";
			engine->field_1C = 0;
			engine_term_display(engine);
			break;
		case APP_CMD_GAINED_FOCUS:
			v26 = "APP_CMD_GAINED_FOCUS";
			engine->field_1C = 1;
			break;
		case APP_CMD_LOST_FOCUS:
			v26 = "APP_CMD_LOST_FOCUS";
			engine->field_1C = 1;
			break;
		case APP_CMD_SAVE_STATE:
			{
				void* savedState = 0;
				int savedStateSize = 0;
				engine->minecraft->saveState(&savedState, &savedStateSize);
				if(savedStateSize > 0) {
					a1->savedStateSize = savedStateSize;
					a1->savedState = savedState;
				}
				break;
			}
		default:
			break;
	}
}
//         //67//       //
static int _d6715384[] = {4, 0x13, 0x14, 0x15, 0x16, 0x17, 0x52, 0x63, 0x64, 0x66, 0x67, 0x6C, 0x6D};
static char _D67153B8[] = {0xD, 8};
static int engine_handle_input(struct android_app* app, struct AInputEvent* event) {
	if(AInputEvent_getType(event) != 1) {
		if(((ENGINE*)app->userData)->minecraft->useTouchscreen()) {
			if(AInputEvent_getType(event) == 2 && AInputEvent_getSource(event) != 0x100008) {
				int16_t action = AMotionEvent_getAction(event);
				int v17 = (action & 0xff00) >> 8;
				int8_t v18 = (action & 0x00ff);
				int8_t pointerId = AMotionEvent_getPointerId(event, v17);
				int v20 = (int)AMotionEvent_getX(event, v17);
				int v21 = (int)AMotionEvent_getY(event, v17);
				switch(v18) {
					case 0:
					case 5:
						Mouse::feed(1, 1, v20, v21);
						Multitouch::feed(1, 1, v20, v21, pointerId);
						break;
					case 1:
					case 6:
						Mouse::feed(1, 0, v20, v21);
						Multitouch::feed(1, 0, v20, v21, pointerId);
						break;
					case 2:
						{
							int pointerCount = AMotionEvent_getPointerCount(event);
							for(int v24 = 0; v24 < pointerCount; ++v24) {
								char v26 = AMotionEvent_getPointerId(event, v24);
								int v29 = (int)AMotionEvent_getX(event, v24);
								int v30 = (int)AMotionEvent_getY(event, v24);
								Mouse::feed(0, 0, v29, v30);
								Multitouch::feed(0, 0, v29, v30, v26);
							}
							break;
						}
					default:
						return 0;
				}
			}
			return 0;
		}
		if(AInputEvent_getType(event) != 2) {
			return 1;
		}
		int v31 = AMotionEvent_getPointerCount(event);
		bool v32 = AInputEvent_getSource(event) == 0x100008;
		int v33 = (uint8_t)AMotionEvent_getAction(event);
		int v15 = 0;
		while(1) {
			if(v15 >= v31) return 1;
			AMotionEvent_getPointerId(event, v15);
			if(v32 || (unsigned int)(v33 - 5) > 1) {
				int v34 = (int)AMotionEvent_getX(event, v15);
				int v35 = (int)AMotionEvent_getY(event, v15);
				char v39;
				char v40;
				if(v33 && v33 != 5) {
					if(v33 == 1 || v33 == 6) {
						if(v32) {
							int v36 = 0;
							float v37 = (float)v34 - 483.0;
							float v38 = (float)v35 - 180.0;
							Controller::feed(1, v36, v37 * 0.0020704, v38 * 0.0055556);
							++v15;
							continue;
						}
						v39 = 1;
					} else {
						if(v33 != 2) {
							++v15;
							continue;
						}
						if(v32) {
							int v36 = -1;
							float v37 = (float)v34 - 483.0;
							float v38 = (float)v35 - 180.0;
							Controller::feed(1, v36, v37 * 0.0020704, v38 * 0.0055556);
							++v15;
							continue;
						}
						v39 = 0;
					}
					v40 = 0;
				} else {
					if(v32) {
						int v36 = 1;
						float v37 = (float)v34 - 483.0;
						float v38 = (float)v35 - 180.0;
						Controller::feed(1, v36, v37 * 0.0020704, v38 * 0.0055556);
						++v15;
						continue;
					}
					v39 = 1;
					v40 = 1;
				}
				Mouse::feed(v39, v40, v34, v35);
			}
			++v15;
		}
	}
	if(AInputEvent_getType(event) != 1) {
		return 0;
	}
	int action = AKeyEvent_getAction(event);
	int keyCode = AKeyEvent_getKeyCode(event);
	int metaState = AKeyEvent_getMetaState(event);
	int deviceId = AInputEvent_getDeviceId(event);
	int v9;
	if(keyCode == 4) {
		v9 = ((AKeyEvent_getMetaState(event) ^ 2u) >> 1) & 1;
	} else {
		v9 = 0;
	}
	int v41;
	if(keyCode == 82 && !((ENGINE*)app->userData)->minecraft->useTouchscreen()) {
		v9 = 1;
		v41 = 0;
	} else {
		v41 = 1;
	}
	if(AKeyEvent_getRepeatCount(event) > 0) {
		if(!v9) {
			return (unsigned int)(keyCode - 24) > 1;
		}
	} else {
		//TODO check does this actually work
		bool v11 = action == 0;
		if(v9 == 0) {
			int v12;
			do {
				if(_d6715384[v9] == keyCode) {
					v12 = keyCode;
					goto LABEL_17;
				}
				++v9;
			} while(v9 != 13);
			if((unsigned int)(keyCode - 66) <= 1) { //keycode == 66 or keycode == 67 (evil)
				//v12 = *((char*)&dword_D6715360[5] + keyCode + 2); /* *(char*)(0xD6715374+(66 or 67)+2) */
				//D67153B8 DCB  0xD
				//D67153B9 DCB    8
				v12 = _D67153B8[keyCode - 66];
				goto LABEL_19;
			}
			v12 = 0;
LABEL_17:
			if(keyCode == 82 && v41) {
				/*LOBYTE(*/ v12 /*)*/ = 0xFF;
				goto LABEL_22;
			}
LABEL_19:
			if(!v12) {
				goto LABEL_23;
			}
LABEL_22:
			Keyboard::feed(v12, v11);
LABEL_23:
			if(v11) {
				uint8_t v13 = (uint8_t)((ENGINE*)app->userData)->appCtx.platform->getKeyFromKeyCode(keyCode, metaState, deviceId);
				if(v13 > 0x1Fu) {
					char v42[] = {(char)v13, 0};
					Keyboard::feedText(std::string(v42), 0);
				}
			}
			return (unsigned int)(keyCode - 24) > 1;
		}
		if(!((ENGINE*)app->userData)->minecraft->handleBack(v11)) {
			return 0;
		}
	}
	return 1;
}

extern "C" {
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeReturnKeyPressed(JNIEnv* env, jobject dis){
	Keyboard::feed(13, 1);
	Keyboard::feed(13, 0);
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeBackSpacePressed(JNIEnv* env, jobject dis){
	Keyboard::feed(8, 1);
	Keyboard::feed(8, 0);
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


void android_main(struct android_app* state) {
	ENGINE engine;
	pEngine = &engine;

	app_dummy();
	memset((void*) &engine, 0, sizeof(engine));
	state->userData = &engine;
	state->destroyRequested = 0;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;

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

}
#endif
