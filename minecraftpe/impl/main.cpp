#include <_types.h>
#include <utils.h>
#include <sys/time.h>
#include <util/Random.hpp>
#include <stdio.h>
#include <math/Mth.hpp>
#include <AppPlatform.hpp>
#include <App.hpp>
#include <AppPlatform_sdl.hpp>
#include <GL/gl.h>
#include <utf8proc.h>
#include <util/Util.hpp>

AppPlatform_sdl appPlatform;

int main(){
	struct timeval start;
	gettimeofday(&start, 0);
	startedAtSec = start.tv_sec;
	appPlatform.init();
}
