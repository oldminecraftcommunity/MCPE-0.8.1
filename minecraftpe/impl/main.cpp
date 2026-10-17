#ifndef ANDROID
#include <_types.h>
#include <cpputils.hpp>
#include <sys/time.h>
#include <util/Random.hpp>
#include <math/Mth.hpp>
#include <AppPlatform.hpp>
#include <App.hpp>
#include <AppPlatform_sdl.hpp>
#include <utf8proc/utf8proc.h>
#include <util/Util.hpp>
#include <unigl.hpp>
#include <RakNetTypes.h>

static AppPlatform_sdl appPlatform;
#ifdef __WIN32__
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
#else
int main(){
#endif
	appPlatform.init();
	return 0;
}
#else

#endif
